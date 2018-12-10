#include "../include/bos.issuance.hpp"
#include "bos.helper.cpp"
#include <stdexcept>

using namespace eosio;
namespace bos {
    // available refund percentage
    uint64_t bosio_issuance::get_bought_period(uint64_t day) {
        if (day <= 90) {
            return 1;
        } else if (day <= 180) {
            return 2;
        } else if (day <= 270) {
            return 3;
        } else if (day <= 300) {
            return 4;
        } else {
            eosio::print("bidding has ended");
            return 5;
        }
    }

    double bosio_issuance::avarefundpert(uint64_t symday) {
        std::tuple <uint64_t, uint64_t> tu_symday = index_decode(symday);
        uint64_t boughtDay = std::get<1>(tu_symday);

        uint64_t boughtPeriod = get_bought_period(boughtDay);
        uint64_t bought_elapseday =  _curday.today - boughtDay;
        eosio_assert(bought_elapseday > 0, "unable to refund on today");
        if(bought_elapseday == 1){
            eosio_assert(now()-(boughtDay * _istate.oneday+_istate.startbidtime) > _istate.refundbuffertime, "You need to wait at least 12 hours after the bidding day");
        }
        // from day to
        switch (boughtPeriod) {
            case 1:
                if( bought_elapseday <= 90) {
                    return 1;
                } else if (bought_elapseday <= 180) {
                    return 0.5;
                } else if (bought_elapseday <= 270) {
                    return 0.25;
                }
                break;
            case 2:
                if (bought_elapseday <= 60) {
                    return 1;
                } else if (bought_elapseday <= 120) {
                    return 0.5;
                } else if (bought_elapseday <= 180) {
                    return 0.25;
                }
                break;
            case 3:
                if (bought_elapseday <= 30) {
                    return 1;
                } else if (bought_elapseday <= 60) {
                    return 0.5;
                } else if (bought_elapseday <= 90) {
                    return 0.25;
                }
                break;
            case 4:
                if (bought_elapseday <= 20) {
                    return 1;
                } else if (bought_elapseday <= 40) {
                    return 0.5;
                } else if (bought_elapseday <= 60) {
                    return 0.25;
                }
                break;
        }

    }


    symbol bosio_issuance::raw_to_symbol(uint64_t symraw){
        if(symraw == symbol_code("EOSHB").raw()){
            return symbol("EOSHB", 4);
        } else if(symraw == symbol_code("ETHHB").raw()){
            return symbol("ETHHB", 8);
        }else if (symraw == symbol_code("BTCHB").raw()){
            return symbol("BTCHB", 8);
        }
    }

    // refundtoken and modify userorders and dailyorders table [bosrefund 代表refund的bos数量]
    void bosio_issuance::refundtoken(name owner, uint64_t symday, asset bosrefund) {
        print("bosrefund: ", bosrefund);
        userorders_table
        _userorders(_self, owner.value);
        uint64_t symraw = std::get<0>(index_decode(symday));
        symbol refund_symbol = raw_to_symbol(symraw);

        auto userorders_lookup = _userorders.find(symday);
        if (userorders_lookup != _userorders.end()) {
            asset ava_token_to_refund = userorders_lookup->masset * avarefundpert(symday);
            double price_of_bos = userorders_lookup->bosasset / userorders_lookup->masset;
            print("price_of_bos", price_of_bos);
            print("bosrefund.amount*1000: ", bosrefund.amount/1000);
//            asset refund_asset = {static_cast<int64_t>(bosrefund.amount/1000/price_of_bos), refund_symbol};
////            bool availability = refund_asset < ava_token_to_refund;
//            print("refund_asset:", refund_asset);
            print("ava_token_to_refund:", ava_token_to_refund);

//            ceosio_assert(availability, "in userorders, overdrawn available refund");

            INLINE_ACTION_SENDER(eosio::token, transfer)(
                    bostoken_account, {{_self, active_permission}},
                    {_self, owner, tokenrefund, std::string("send bos to refund to receiver on day x")}
            );

//            _userorders.modify(userorders_lookup, _self, [&](auto &update_user_order) {
//                update_user_order.bosasset = update_user_order.bosasset - bosrefund;
//                update_user_order.masset = update_user_order.masset - tokenrefund;
//
//            });
        }

        // modify dailyorder table
//        auto dailyorder_lookup = _dailyorders.find(symday);
//        if (dailyorder_lookup != _dailyorders.end()) {
//            _dailyorders.modify(dailyorder_lookup, _self, [&](auto &update_daily_order) {
//                update_daily_order.bosasset = update_daily_order.bosasset - bosrefund;
//                update_daily_order.masset = update_daily_order.masset - tokenrefund;
//            });
//        }
    }

    // day-sym
    // 仅当，严格限制返回BOS的条件
    std::tuple<uint64_t, uint64_t> bosio_issuance::validaterefundmemo(name from,  const std::string& memo) {
        print("memo.length() ", memo.length());
//        print("memo", memo);
        // 1. format validation
        eosio_assert(memo.length() != 0, "Empty memo !");
        eosio_assert(memo.length() < 11, "Memo too long !");        // 232-EOSBTFX
        eosio_assert(memo.length() > 7, "Memo too short !");         // 063-BTC
        eosio_assert(memo.at(3) == '-', "Wrong Format !");
        string strday = memo.substr(0, 3);

        for(char& c : strday) {
            if( c < '0' && c > '9' ) {
                eosio_assert(false, "Invalid Day !");
            }
        }
        uint64_t day = static_cast<uint64_t>(std::stoi(memo.substr(0, 3)));
        uint64_t symraw;
        std::string strsymcd = memo.substr(4, memo.length()-4);
        for( auto itr = strsymcd.rbegin(); itr != strsymcd.rend(); ++itr ) {
            if( *itr < 'A' || *itr > 'Z') {
                eosio_assert( false, "only uppercase letters allowed in symbol_code string" );
            }
            symraw <<= 8;
            symraw |= *itr;
        }


        // 2.
        uint64_t symday = index_encode(symraw, day);
        print("symday in validate: ", symday);
        userorders_table _userorder(_self, from.value);
        auto it = _userorder.find(symday);
        if(it != _userorder.end()){
            print("Thrilled validate refund for user: ", from);
        }else{
            print("cannot find the refund record for user: ", from);
        }

        return {symraw, day};

        /*
            memo like:
            day-sym
            typeof(day) == int
            1<= day <=10
            sym.length <=7
            sym == EOS,BTC,ETH ?
         */
//        bool memoformat = true; //TODO: validate memo format, boost and jsoncpp cannot be used
        // TODO: CSDN: https://blog.csdn.net/hzyong_c/article/details/7163589
    }
}
