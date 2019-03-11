#include <bos.pegtoken/bos.pegtoken.hpp>
// #include "../include/bos.pegtoken.hpp"
#include <eosiolib/transaction.hpp>
#include <eosiolib/action.hpp>

#include "bos.pegtoken_v1.cpp"
#include "bos.pegtoken_v2.cpp"

namespace eosio {

////////////////////////
// actions
////////////////////////

    void pegtoken::create(symbol sym, name issuer, name address_style, uint64_t peg) {
        symbol_code sym_code = sym.code();
        switch (getedition(sym_code))
        {
            case 1:
                create_v1(sym,issuer,issuer,address_style,"","");
                break;
            case 2:
                create_v2(sym,issuer,address_style);
                break;
            default:
                eosio_assert(false, "peg should be 1 or 2");
                break;
        }

        auto edtion_table = editions(get_self(),sym_code.raw());
        edtion_table.emplace(get_self(),[&](auto &p) {
            p.sym = sym;
            p.edition = 2;
        });

        auto peg_table = pegs(get_self(),sym_code.raw());
        peg_table.emplace(get_self(),[&](auto &p) {
            p.sym = sym;
            p.peg = peg;
        });
    }


    void pegtoken::setissuer( symbol_code sym_code, name issuer )
    {
        eosio_assert(false, "peg should be 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setissuer_v1(sym_code,issuer);
            break;
        case 2:
            setissuer_v2(sym_code,issuer);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setedition( symbol_code sym_code ) {
        require_auth(get_self());
        auto edtion_table = editions(get_self(),sym_code.raw());
        eosio_assert(edtion_table.begin() == edtion_table.end(), " edition already set" );
        edtion_table.emplace(get_self(),[&](auto &p) {
            p.sym = eosio::symbol(sym_code.raw());
            p.edition = 1;
        });
    }

    // 没有版本名称，通过函数补充设置
    void pegtoken::setpeg( symbol_code sym_code ) {
        require_auth(get_self());
        auto peg_table = pegs(get_self(),sym_code.raw());
        eosio_assert(peg_table.begin() == peg_table.end(), " peg already set" );
        peg_table.emplace(get_self(),[&](auto &p) {
            p.sym = eosio::symbol(sym_code.raw());
            p.peg = 1;
        });
    }

    void pegtoken::update(symbol_code sym_code, string organization, string website) {
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,  "Wrong Edition");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            update_v1(sym_code,organization,website);
            break;
        case 2:
            update_v2(sym_code,organization,website);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setlimit(symbol_code sym_code, asset max_limit, asset min_limit, asset total_limit, uint64_t frequency_limit,
                            uint64_t interval_limit) {
        eosio_assert(is_sym_equal_asset(sym_code, max_limit), "sym_code is not same as max_limit symbol_code.");
        eosio_assert(is_sym_equal_asset(sym_code, min_limit), "sym_code is not same as min_limit symbol_code.");
        eosio_assert(is_sym_equal_asset(sym_code, total_limit), "sym_code is not same as total_limit symbol_code.");
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        eosio_assert(min_limit.amount >= 0 && max_limit >= min_limit && total_limit >= max_limit,  "constrict mismatch: total_limit >= max_limit >= min_limit >= 0");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setlimit_v1(max_limit,min_limit,total_limit,frequency_limit,interval_limit);
            break;
        case 2:
            setlimit_v2(max_limit,min_limit,total_limit,frequency_limit,interval_limit);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setmaxlimit(symbol_code sym_code, asset max_limit ) {
        eosio_assert(is_sym_equal_asset(sym_code, max_limit), "sym_code is not same as asset symbol_code.");
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setmaxlimit_v1(max_limit);
            break;
        case 2:
            setmaxlimit_v2(max_limit);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setminlimit(symbol_code sym_code, asset min_limit ) {
        eosio_assert(is_sym_equal_asset(sym_code, min_limit), "sym_code is not same as asset symbol_code.");
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setminlimit_v1(min_limit);
            break;
        case 2:
            setminlimit_v2(min_limit);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setotalimit(symbol_code sym_code, asset total_limit )
    {
        eosio_assert(is_sym_equal_asset(sym_code, total_limit), "sym_code is not same as asset symbol_code.");
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setotalimit_v1(total_limit);
            break;
        case 2:
            setotalimit_v2(total_limit);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    // void pegtoken::setfrelimit( symbol_code sym_code, uint64_t frequency_limit) {
    //     auto peg_table = pegs(get_self(),sym_code.raw());
    //     auto pegval = peg_table.get(sym_code.raw(),"no such peg");
    //     switch (pegval.peg)
    //     {
    //     case 1:
    //         setfrelimit_v1(sym_code, frequency_limit);
    //         break;
    //     case 2:
    //         setfrelimit_v2(sym_code, frequency_limit);
    //         break;
    //     default:
    //         eosio_assert(false, "peg should be 1 or 2");
    //         break;
    //     }
    // }

    void pegtoken::setintvlimit( symbol_code sym_code, uint64_t interval_limit) {
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setintvlimit_v1(sym_code, interval_limit);
            break;
        case 2:
            setintvlimit_v2(sym_code, interval_limit);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    // void pegtoken::setreslimit( symbol_code sym_code, uint64_t reset_limit) {
    //     auto peg_table = pegs(get_self(),sym_code.raw());
    //     auto pegval = peg_table.get(sym_code.raw(),"no such peg");
    //     switch (pegval.peg)
    //     {
    //     case 1:
    //         setreslimit_v1(sym_code, reset_limit);
    //         break;
    //     case 2:
    //         setreslimit_v2(sym_code, reset_limit);
    //         break;
    //     default:
    //         eosio_assert(false, "peg should be 1 or 2");
    //         break;
    //     }
    // }

    void pegtoken::setviplimit(symbol_code sym_code, name vip, asset max_limit, asset min_limit ,asset total_limit,uint64_t frequency_limit, uint64_t interval_limit,uint64_t reset_limit) {
        eosio_assert(is_sym_equal_asset(sym_code, max_limit), "sym_code is not same as max_limit symbol_code.");
        eosio_assert(is_sym_equal_asset(sym_code, min_limit), "sym_code is not same as min_limit symbol_code.");
        eosio_assert(is_sym_equal_asset(sym_code, total_limit), "sym_code is not same as total_limit symbol_code.");
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setviplimit_v1(vip,max_limit,min_limit,total_limit,frequency_limit,interval_limit,reset_limit );
            break;
        case 2:
            setviplimit_v2(vip,max_limit,min_limit,total_limit,frequency_limit,interval_limit,reset_limit );
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setvipmaxlimit(name vip, asset max_limit ) {
        auto sym_code = max_limit.symbol.code();
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setvipmaxlimit_v1(vip,max_limit );
            break;
        case 2:
            setvipmaxlimit_v2(vip,max_limit );
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

        void pegtoken::setvipminlimit(name vip, asset min_limit ) {
        auto sym_code = min_limit.symbol.code();
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setvipminlimit_v1(vip,min_limit );
            break;
        case 2:
            setvipminlimit_v2(vip,min_limit );
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setviptotallimit(name vip, asset totimum_limit ) {
        auto sym_code = totimum_limit.symbol.code();
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setviptotallimit_v1(vip,totimum_limit );
            break;
        case 2:
            setviptotallimit_v2(vip,totimum_limit );
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setfee(symbol_code sym_code, double service_fee_rate, asset min_service_fee, asset miner_fee) {
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setfee_v1(service_fee_rate,min_service_fee,miner_fee);
            break;
        case 2:
            setfee_v2(service_fee_rate,min_service_fee,miner_fee);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setservicefeerate(symbol_code sym_code, double service_fee_rate) {
        eosio_assert(getedition(sym_code) != 1 && getedition(sym_code) != 2,   "Edition should be either 1 or 2");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setservicefeerate_v1(sym_code,service_fee_rate);
            break;
        case 2:
            setservicefeerate_v2(sym_code,service_fee_rate);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setminservicefee(asset min_service_fee) {
        auto sym_code = min_service_fee.symbol.code();
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setminservicefee_v1(min_service_fee);
            break;
        case 2:
            setminservicefee_v2(min_service_fee);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setminerfee(asset miner_fee) {
        auto sym_code = miner_fee.symbol.code();
        auto editionval = getedition(sym_code);
        switch (editionval){
            case 1:
                setminerfee_v1(miner_fee);
                break;
            case 2:
                setminerfee_v2(miner_fee);
                break;
            default:
                eosio_assert(false, "peg should be 1 or 2");
                break;
        }
    }

    void pegtoken::setvipfee(symbol_code sym_code, name vip, double service_fee_rate, asset min_service_fee, asset miner_fee ){
        eosio_assert(is_sym_equal_asset(sym_code, min_service_fee), "sym_code is not same as min_service_fee symbol_code.");
        eosio_assert(is_sym_equal_asset(sym_code, miner_fee), "sym_code is not same as miner_fee symbol_code.");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setvipfee_v1(vip,service_fee_rate, min_service_fee, miner_fee);
            break;
        case 2:
            setvipfee_v2(vip,service_fee_rate, min_service_fee, miner_fee);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setvipservicefeerate(symbol_code sym_code, name vip,double service_fee_rate){
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setvipservicefeerate_v1(sym_code,vip,service_fee_rate);
            break;
        case 2:
            setvipservicefeerate_v2(sym_code,vip,service_fee_rate);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setvipminfee(name vip, asset min_service_fee ) {
        auto sym_code = min_service_fee.symbol.code();
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setvipminfee_v1(vip,min_service_fee);
            break;
        case 2:
            setvipminfee_v2(vip,min_service_fee);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setvipminerfee(name vip, asset miner_fee ) {
        auto sym_code = miner_fee.symbol.code();
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setvipminerfee_v1(vip,miner_fee);
            break;
        case 2:
            setvipminerfee(vip,miner_fee);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::setdelay(symbol_code sym_code, uint64_t delayday) {
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            setdelay_v1(sym_code,delayday);
            break;
        case 2:
            setdelay_v2(sym_code,delayday);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }


    void pegtoken::issue(asset quantity, string memo) {
        STRING_LEN_CHECK(memo, 256)
        eosio_assert(quantity.is_valid() && quantity.amount > 0, "invalid quantity");
        auto sym_code = quantity.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            issue_v1(quantity,memo);
            break;
        case 2:
            issue_v2(quantity,memo);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::retire(asset quantity, string memo) {
        eosio_assert(quantity.is_valid() && quantity.amount > 0, "invalid quantity");
        STRING_LEN_CHECK(memo, 256)
        auto sym_code = quantity.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            retire_v1(quantity,memo);
            break;
        case 2:
            retire_v2(quantity,memo);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::precast(string to_address, name to_account, string remote_trx_id, uint64_t index, asset quantity, string memo){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getincheck(sym_code), "This action require in_check to be true");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
        precast_v2(to_address,to_account,remote_trx_id,index,quantity,memo);
    }

    void pegtoken::agreecast(name auditor, string to_address, name to_account, string remote_trx_id, uint64_t index, asset quantity, string memo){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getincheck(sym_code), "This action require in_check to be true");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
        agreecast_v2(auditor,to_address,to_account,remote_trx_id,index,quantity,memo);
          
    }

    void pegtoken::refusecast(name auditor, string to_address, name to_account, string remote_trx_id, uint64_t index, asset quantity, string memo){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getincheck(sym_code), "This action require in_check to be true");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
        refusecast_v2(auditor,to_address,to_account,remote_trx_id,index,quantity,memo);
    }

    void pegtoken::cast(symbol_code sym_code, string to_address, name to_account, string remote_trx_id, asset quantity,  uint64_t index, string memo){
        eosio_assert(!getincheck(sym_code), "This action require in_check to be false");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        docast_v2(to_address,to_account,remote_trx_id,index,quantity,memo);
    }
    // 用户转给出纳员
    void pegtoken::melt(name from_account, string to_address, asset quantity, uint64_t index, string memo){
        symbol_code sym_code = quantity.symbol.code();
        eosio_assert(!getoutcheck(sym_code), "This action require out_check to be false");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
        melt_v2(from_account, to_address, quantity,  index,  memo);
    }

    void pegtoken::premelt(name from_account, string to_address, asset quantity, uint64_t index, string memo){
        symbol_code sym_code = quantity.symbol.code();
        // eosio_assert(getoutcheck(sym_code), "This action require out_check to be true");
        eosio_assert(!getoutcheck(sym_code), "This action require out_check to be false");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");

    }

    void pegtoken::agreemelt(name from_account, string to_address, asset quantity, uint64_t index, string memo){
        symbol_code sym_code = quantity.symbol.code();
        eosio_assert(getoutcheck(sym_code), "This action require out_check to be true");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
        // eosio_assert(!getpeg());
    }

    void pegtoken::refusemelt(name from_account, string to_address, asset quantity, uint64_t index, string memo){
        symbol_code sym_code = quantity.symbol.code();
        eosio_assert(getoutcheck(sym_code), "This action require out_check to be true");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
        // eosio_assert(!getpeg());
    }

    //TODO:
    void pegtoken::rm( symbol_code sym_code, uint64_t id, uint64_t type){ 
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");     
    }

    // FIXME: setauditor is removed
    // void pegtoken::setauditor(symbol_code sym_code, string action, name auditor) { }
    void pegtoken::setauditor( symbol_code sym_code, string action, name auditor){

    }

    void pegtoken::setteller( symbol_code sym_code,  name teller){

    }

    void pegtoken::setmanager(symbol_code sym_code,  name manager){
        auto manager_tb = managers(get_self(), sym_code.raw());
        // check_issuer();
        auto mgr_iter = manager_tb.find(manager.value);
        if (mgr_iter == manager_tb.end()) {
            manager_tb.emplace(same_payer, [&](auto &mgr) {
                mgr.manager = manager;
            });
        } else {
            manager_tb.modify(mgr_iter, same_payer, [&](auto &mgr) {
                mgr.manager = manager;
            });
        }
    }

    void pegtoken::setbrakeman( symbol_code sym_code,  name brakeman){

    }



    void pegtoken::applyaddr(symbol_code sym_code, name to) {
        auto editionval = getedition(sym_code);
        switch (editionval){
            case 1:
                applyaddr_v1(sym_code,to);
                break;
            default:
                eosio_assert(false, "peg should be 1 or 2");
                break;
        }
    }

    void pegtoken::assignaddr(symbol_code sym_code, name to, string address) {
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            assignaddr_v1(sym_code,to,address);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }

    void pegtoken::withdraw(name from, string to, asset quantity, uint64_t index, string memo) {
        auto sym_code = quantity.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        eosio_assert(!getoutcheck(sym_code), "This action require out_check to be false");
        auto editionval = getedition(sym_code);
        switch (editionval)
        {
        case 1:
            withdraw_v1(from,to,quantity,memo);
            break;
        case 2:
            withdraw_v2(from,to,quantity, index, memo);
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }


    void pegtoken::prewithdraw( name from, string to, asset quantity, uint64_t index, string memo){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        eosio_assert(!getoutcheck(sym_code), "out_check is true for this symbol");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
    }

    void pegtoken::agreewithdraw( name from, string to, asset quantity, uint64_t index, string memo){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        eosio_assert(!getoutcheck(sym_code), "out_check is true for this symbol");
    }

    void pegtoken::refusewithdraw( name from, string to, asset quantity, uint64_t index, string memo){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        eosio_assert(!getoutcheck(sym_code), "out_check is true for this symbol");
    }

   

    void pegtoken::deposit(name to, asset quantity, string memo) {
        auto sym_code = quantity.symbol.code();
        eosio_assert(!getincheck(sym_code), "This action require in_check to be false");
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        deposit_v1(to,quantity,memo);
    }


    void pegtoken::predeposit( string from, name to, asset quantity, string memo ){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getincheck(sym_code), "This action require in_check to be true");
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
    }


    void pegtoken::agreedeposit( string from, name to, asset quantity, string remote_trx_id, uint64_t index, string memo ){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getincheck(sym_code), "This action require in_check to be true");
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
    }

    void pegtoken::refusedeposit( string from, name to, asset quantity, string remote_trx_id, uint64_t index, string memo ){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getincheck(sym_code), "This action require in_check to be true");
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
    }

    void pegtoken::transfer(name from, name to, asset quantity, string memo) {
        auto sym_code = quantity.symbol.code();
        auto peg_table = pegs(get_self(),sym_code.raw());
        auto pegval = peg_table.get(sym_code.raw(),"no such peg");
        switch (pegval.peg)
        {
        case 1:
            transfer_v1(from,to,quantity,memo);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }
    void pegtoken::remit( name from, asset quantity ){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
    }

     void pegtoken::pay( asset quantity ){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
     }

     void pegtoken::ruin( asset quantity ){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
        ruin_v2(quantity);
    }

    void pegtoken::burn( name from, asset quantity){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
    }

    void pegtoken::retreat(name to, asset quantity){
        auto sym_code = quantity.symbol.code();
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "This action require peg version to be 2.");
    }

    void pegtoken::clear(symbol_code sym_code, uint64_t num) {
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        clear_v1(sym_code,num);
    }

    void pegtoken::publishminerfee( asset miner_fee ){
        auto sym_code = miner_fee.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
    }

    void pegtoken::publishsum( string address, asset sum ){
        auto sym_code = sum.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
    }


    void pegtoken::setgatherer( symbol_code sym_code,  name gatherer){
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "The action require peg to be 2");
    }

    void pegtoken::feedback(symbol_code sym_code, transaction_id_type trx_id, string remote_trx_id, string memo) {
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        feedback_v1(sym_code,trx_id,remote_trx_id,memo);
    }

    void pegtoken::rollback(symbol_code sym_code, transaction_id_type trx_id, string memo) {
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        eosio_assert(getedition(sym_code) == 1 || getedition(sym_code) == 2, "The action require edition to be 1 or 2");
        rollback_v1(sym_code,trx_id,memo);
    }

    void pegtoken::confirmback( symbol_code sym_code, transaction_id_type trx_id, string remote_trx_id, uint64_t index, uint64_t remote_index, string memo ){
        eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
        eosio_assert(getpeg(sym_code) == 2, "The action require peg to be 2");
    }

    void pegtoken::denyback( symbol_code sym_code, transaction_id_type trx_id, uint64_t index,  string memo ){
       eosio_assert(getedition(sym_code) == 2, "The action require edition to be 2");
       eosio_assert(getpeg(sym_code) == 2, "The action require peg to be 2");
    }



    // void pegtoken::setacceptor(symbol_code sym_code, name acceptor) {
    //     auto peg_table = pegs(get_self(),sym_code.raw());
    //     auto pegval = peg_table.get(sym_code.raw(),"no such peg");
    //     switch (pegval.peg)
    //     {
    //     case 1:
    //         setacceptor_v1(sym_code,acceptor);
    //         break;
    //     default:
    //         eosio_assert(false, "peg should be 1 or 2");
    //         break;
    //     }
    // }


    void pegtoken::lockall(symbol_code sym_code, name auditor) {
        eosio_assert(getedition(sym_code) == 1 || getedition(sym_code) == 2, "The action require edition to be 1 or 2");
        lockall_v1(sym_code,auditor);
    }

    void pegtoken::unlockall(symbol_code sym_code, name auditor) {
        auto peg_table = pegs(get_self(),sym_code.raw());
        auto pegval = peg_table.get(sym_code.raw(),"no such peg");
        switch (pegval.peg)
        {
        case 1:
            unlockall_v1(sym_code,auditor);
            break;
        default:
            eosio_assert(false, "peg should be 1 or 2");
            break;
        }
    }



    void pegtoken::sendback(/*name auditor,*/ transaction_id_type trx_id, name to, asset quantity, string memo) {
        auto sym_code = quantity.symbol.code();
        eosio_assert(getpeg(sym_code) == 1, "This action require peg version to be 1.");
        sendback_v1(trx_id,to,quantity,memo);
    }


    // void pegtoken::approve(symbol_code sym_code, name auditor, transaction_id_type trx_id, string memo) {
    //     auto peg_table = pegs(get_self(),sym_code.raw());
    //     auto pegval = peg_table.get(sym_code.raw(),"no such peg");
    //     switch (pegval.peg)
    //     {
    //     case 1:
    //         approve_v1(sym_code,auditor,trx_id,memo);
    //         break;
    //     default:
    //         eosio_assert(false, "peg should be 1 or 2");
    //         break;
    //     }
    // }

    // void pegtoken::unapprove(symbol_code sym_code, name auditor, transaction_id_type trx_id, string memo) {
    //     auto peg_table = pegs(get_self(),sym_code.raw());
    //     auto pegval = peg_table.get(sym_code.raw(),"no such peg");
    //     switch (pegval.peg)
    //     {
    //     case 1:
    //         unapprove_v1(sym_code,auditor,trx_id,memo);
    //         break;
    //     default:
    //         eosio_assert(false, "peg should be 1 or 2");
    //         break;
    //     }
    // }

    // void pegtoken::rmwithdraw(uint64_t id, symbol_code sym_code) {
    //     auto peg_table = pegs(get_self(),sym_code.raw());
    //     auto pegval = peg_table.get(sym_code.raw(),"no such peg");
    //     switch (pegval.peg)
    //     {
    //     case 1:
    //         rmwithdraw_v1(id,sym_code);
    //         break;
    //     default:
    //         eosio_assert(false, "peg should be 1 or 2");
    //         break;
    //     }
    // }
    

} // namespace eosio

// FIXME: setauditor is removed
EOSIO_DISPATCH( eosio::pegtoken, (create)(setissuer)(setedition)(setpeg)(update)
        (setlimit)(setmaxlimit)(setminlimit));
