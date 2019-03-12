#include <bos.pegtoken/bos.pegtoken.hpp>
// 用于五个set部分的余额检查
#include <eosio.token/eosio.token.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/action.hpp>
#include "def.cpp"

namespace eosio {
    void pegtoken::create_v2( symbol sym, name issuer, name address_style){
        require_auth(get_self());

        ACCOUNT_CHECK(issuer);
        eosio_assert(sym.is_valid(), "invalid symbol");

        eosio_assert(address_style == "bitcoin"_n || address_style == "ethereum"_n || address_style == "tether"_n ||
                     address_style == "other"_n,
                     "address_style must be one of bitcoin, ethereum, tether or other");

        auto info_table = infos(get_self(),sym.code().raw());
        eosio_assert(info_table.find(sym.code().raw()) == info_table.end(), "token with symbol already exists (info)");

        info_table.emplace(get_self(),[&](auto &p) {
            p.supply = eosio::asset(0,sym);
            p.issuer = issuer;
            p.address_style = address_style;
            p.active = true; 
        });

        auto summary_table = summaries(get_self(),sym.code().raw());
        eosio_assert(summary_table.find(sym.code().raw()) == summary_table.end(), "token with symbol already exists (summary)");
        summary_table.emplace(get_self(),[&](auto &p){
            /* do nothing */
        });

        auto limit_table = limits(get_self(),sym.code().raw());
        eosio_assert(limit_table.find(sym.code().raw()) == limit_table.end(), "token with symbol already exists (limit)");
        limit_table.emplace(get_self(),[&](auto &p){
            p.max_limit = eosio::asset(0,sym);
            p.min_limit = eosio::asset(0,sym);
            p.total_limit = eosio::asset(0,sym);

            p.frequency_limit = 0;
            p.interval_limit = 300;
            p.reset_limit = 30 * ONE_DAY;
        });
    }

    void pegtoken::setissuer_v2( symbol_code sym_code, name issuer ) {
        require_auth(get_self());
        ACCOUNT_CHECK(issuer);

        auto sym_raw = sym_code.raw();
        auto info_table = infos(get_self(), sym_raw);
        auto iter = info_table.find(sym_raw);
        eosio_assert(iter != info_table.end(), "token not exist");
        
        info_table.modify(iter,same_payer,[&](auto & p) {
            p.issuer = issuer;
        });
    }

    void pegtoken::update_v2( symbol_code sym_code, string organization, string website ){
        STRING_LEN_CHECK(organization, 256)
        STRING_LEN_CHECK(website, 256)

        auto info_table = infos(get_self(),sym_code.raw());
        auto val = info_table.get(sym_code.raw(), "token with symbol already exists");
        require_auth(val.issuer);

        auto summary_table = summaries(get_self(),sym_code.raw());
        auto iter = summary_table.begin();
        eosio_assert( iter != summary_table.end(), "token with symbol not exists");
        summary_table.modify(iter,same_payer,[&](auto &p){
            p.organization = organization;
            p.website = website;
        });
    }


    void pegtoken::setlimit_v2( asset max_limit, asset min_limit, asset total_limit, uint64_t frequency_limit, uint64_t interval_limit ) {
        eosio_assert(min_limit.amount >= 0 && max_limit >= min_limit && total_limit >= max_limit,
             "constrict mismatch: total_limit >= max_limit >= min_limit >= 0");

        auto sym_raw = max_limit.symbol.code().raw();
        auto manager_table = managers(get_self(), sym_raw);
        auto val = manager_table.get(sym_raw, "No managers table based on symbol");
        require_auth(val.manager);

        auto limit_table = limits(get_self(),sym_raw);
        auto iter = limit_table.find(sym_raw);
        eosio_assert( iter != limit_table.end(), "token with symbol not exists(limit)");
        limit_table.modify(iter,same_payer,[&](auto &p){
            p.max_limit = max_limit;
            p.min_limit = min_limit;
            p.total_limit = total_limit;
            p.frequency_limit = frequency_limit;
            p.interval_limit = interval_limit;
        });
    }

    void pegtoken::setmaxlimit_v2( asset max_limit ){
        auto sym_code = max_limit.symbol.code();
        auto limit_table = limits(get_self(),sym_code.raw());
        auto val = limit_table.get(sym_code.raw(),"token with symbol not exists");
        
        setlimit_v2( max_limit,val.min_limit,val.total_limit,val.frequency_limit,val.interval_limit );
    }

    void pegtoken::setminlimit_v2( asset min_limit ){
        auto sym_code = min_limit.symbol.code();
        auto limit_table = limits(get_self(),sym_code.raw());
        auto val = limit_table.get(sym_code.raw(),"token with symbol not exists");
        
        setlimit_v2( val.max_limit,min_limit,val.total_limit,val.frequency_limit,val.interval_limit );
    }

    void pegtoken::settotalimit_v2( asset total_limit ){
        auto sym_code = total_limit.symbol.code();
        auto limit_table = limits(get_self(),sym_code.raw());
        auto val = limit_table.get(sym_code.raw(),"token with symbol not exists");

        setlimit_v2( val.max_limit,val.min_limit,total_limit,val.frequency_limit,val.interval_limit );    
    }

    void pegtoken::setfreqlimit_v2( symbol_code sym_code, uint64_t frequency_limit) {
        auto limit_table = limits(get_self(),sym_code.raw());
        auto val = limit_table.get(sym_code.raw(),"token with symbol not exists");
        
        setlimit_v2( val.max_limit,val.min_limit,val.total_limit,frequency_limit,val.interval_limit );
    }

    void pegtoken::setintvlimit_v2( symbol_code sym_code, uint64_t interval_limit) {
        auto limit_table = limits(get_self(),sym_code.raw());
        auto val = limit_table.get(sym_code.raw(),"token with symbol not exists");
        
        setlimit_v2( val.max_limit,val.min_limit,val.total_limit,val.frequency_limit, interval_limit );
    }

    // void pegtoken::setreslimit_v2( symbol_code sym_code, uint64_t reset_limit) {
    //     auto info_table = infos(get_self(),sym_code.raw());
    //     auto val = info_table.get(sym_code.raw(), "token with symbol not exists(info)");
    //     require_auth(val.issuer);

    //     auto limit_table = limits(get_self(),sym_code.raw());
    //     auto iter = limit_table.find(sym_code.raw());
    //     eosio_assert( iter != limit_table.end(), "token with symbol not exists(limit)");
    //     limit_table.modify(iter,same_payer,[&](auto &p){
    //         p.reset_limit = reset_limit;
    //     });
    // }

    void pegtoken::setviplimit_v2(name vip, asset max_limit, asset min_limit ,asset total_limit,uint64_t frequency_limit, uint64_t interval_limit,uint64_t reset_limit){
        eosio_assert( max_limit >= min_limit && total_limit >= max_limit && min_limit.amount >=0, "mismatch: total >= max >= min >= 0");

        auto sym_raw = max_limit.symbol.code().raw();
        auto manager_table = managers(get_self(), sym_raw);
        auto val = manager_table.get(sym_raw, "No managers table based on symbol");
        require_auth(val.manager);

        auto vip_table = vips(get_self(),sym_raw);
        auto viplimit_table = viplimits(get_self(),sym_raw);
        auto vipfee_table = vipfees(get_self(),sym_raw);
        
        auto iter_vip = vip_table.find(vip.value);
        if(iter_vip == vip_table.end()){
            vip_table.emplace(get_self(),[&](auto &p){
                p.vip = vip;
                p.create_time = time_point_sec(now());
            });
            viplimit_table.emplace(get_self(),[&](auto &p){
                p.owner = vip;
                p.max_limit = max_limit;
                p.min_limit = min_limit;
                p.total_limit = total_limit;
                p.frequency_limit = frequency_limit;
                p.interval_limit = interval_limit;
                p.reset_limit = reset_limit;
            });
            vipfee_table.emplace(get_self(),[&](auto &p){
                p.owner = vip;
                p.service_fee_rate = 0;
                p.min_service_fee = eosio::asset(0,max_limit.symbol);
                p.miner_fee = eosio::asset(0,max_limit.symbol);
            });
        } else {
            viplimit_table.modify(
                viplimit_table.find(vip.value),
                    same_payer,[&](auto &p){
                p.owner = vip;
                p.max_limit = max_limit;
                p.min_limit = min_limit;
                p.total_limit = total_limit;
                p.frequency_limit = frequency_limit;
                p.interval_limit = interval_limit;
                p.reset_limit = reset_limit;
            });
        }
    }

    void pegtoken::setvipmaxlim_v2(name vip, asset max_limit ) {
        auto sym_raw = max_limit.symbol.code().raw();
        auto viplimit_table = viplimits(get_self(),sym_raw);
        auto iter = viplimit_table.find(vip.value);
        if (iter == viplimit_table.end() ){
            auto zero_asset = eosio::asset(0,max_limit.symbol);
            setviplimit_v2(vip,max_limit,zero_asset,zero_asset,0,0,0);
        } else {
            setviplimit_v2(vip,max_limit,iter->min_limit,iter->total_limit,
            iter->frequency_limit,iter->interval_limit,iter->reset_limit);
        }
    }

    void pegtoken::setvipminlim_v2(name vip, asset min_limit ) {
        auto sym_raw = min_limit.symbol.code().raw();
        auto viplimit_table = viplimits(get_self(),sym_raw);
        auto iter = viplimit_table.find(vip.value);
        if (iter == viplimit_table.end() ){
            auto zero_asset = eosio::asset(0,min_limit.symbol);
            setviplimit_v2(vip,zero_asset,min_limit,zero_asset,0,0,0);
        } else {
            setviplimit_v2(vip,iter->max_limit,min_limit,iter->total_limit,
            iter->frequency_limit,iter->interval_limit,iter->reset_limit);
        }
    }

    void pegtoken::setviptotlim_v2(name vip, asset total_limit ) {
        auto sym_raw = total_limit.symbol.code().raw();
        auto viplimit_table = viplimits(get_self(),sym_raw);
        auto iter = viplimit_table.find(vip.value);
        if (iter == viplimit_table.end() ){
            auto zero_asset = eosio::asset(0,total_limit.symbol);
            setviplimit_v2(vip,zero_asset,zero_asset,total_limit,0,0,0);
        } else {
            setviplimit_v2(vip,iter->max_limit,iter->min_limit,total_limit,
            iter->frequency_limit,iter->interval_limit,iter->reset_limit);
        }
    }

    void pegtoken::setfee_v2(double service_fee_rate, asset min_service_fee, asset miner_fee ){
        eosio_assert(min_service_fee.symbol == miner_fee.symbol, "different symbol");
       // auto info_table = infos(get_self(),sym_raw);
        // auto val = info_table.get(sym_raw, "token with symbol not exists(info)");
        // 直接从位于sym_code scope中的managers中获取
        auto sym_raw = min_service_fee.symbol.code().raw();
        auto manager_table = managers(get_self(), sym_raw);
        auto val = manager_table.get(sym_raw, "No managers table based on symbol");
        require_auth(val.manager);

        auto fee_table = fees(get_self(),sym_raw);
        if( fee_table.begin() == fee_table.end()) {
            fee_table.emplace(get_self(),[&](auto &p){
                p.service_fee_rate = service_fee_rate;
                p.min_service_fee = min_service_fee;
                p.miner_fee = miner_fee;
            });
        } else {
            fee_table.modify(fee_table.begin(), same_payer ,[&](auto &p){
                p.service_fee_rate = service_fee_rate;
                p.min_service_fee = min_service_fee;
                p.miner_fee = miner_fee;
            });
        }
    }

    void pegtoken::setservfeert_v2(symbol_code sym_code, double service_fee_rate){
        auto fee_table = fees(get_self(),sym_code.raw());
        auto iter = fee_table.begin();
        if( iter == fee_table.end()) {
            auto zero_asset = eosio::asset(0,eosio::symbol(sym_code.raw()));
            setfee_v2(service_fee_rate,zero_asset,zero_asset);
        } else {
            setfee_v2(service_fee_rate,iter->min_service_fee,iter->miner_fee);
        }
    }

    void pegtoken::setminserfee_v2(asset min_service_fee){
        auto fee_table = fees(get_self(),min_service_fee.symbol.code().raw());
        auto iter = fee_table.begin();
        if( iter == fee_table.end()) {
            auto zero_asset = eosio::asset(0,min_service_fee.symbol);
            setfee_v2(0,min_service_fee,zero_asset);
        } else {
            setfee_v2(iter->service_fee_rate,min_service_fee,iter->miner_fee);
        }
    }

    void pegtoken::setminerfee_v2(asset miner_fee){
        auto fee_table = fees(get_self(),miner_fee.symbol.code().raw());
        auto iter = fee_table.begin();
        if( iter == fee_table.end()) {
            auto zero_asset = eosio::asset(0,miner_fee.symbol);
            setfee_v2(0,zero_asset,miner_fee);
        } else {
            setfee_v2(iter->service_fee_rate,iter->min_service_fee,miner_fee);
        }
    }
    
    void pegtoken::setvipfee_v2(name vip, double service_fee_rate, asset min_service_fee, asset miner_fee ){
        eosio_assert(min_service_fee.symbol == miner_fee.symbol, "invalid symbol");
        
        auto sym_raw = min_service_fee.symbol.code().raw();
        
        auto info_table = infos(get_self(),sym_raw);
        auto val = info_table.get(sym_raw, "token with symbol not exists(info)");
        require_auth(val.issuer);

        auto vip_table = vips(get_self(),sym_raw);
        auto viplimit_table = viplimits(get_self(),sym_raw);
        auto vipfee_table = vipfees(get_self(),sym_raw);
        
        auto iter_vip = vip_table.find(vip.value);
        if(iter_vip == vip_table.end()){
            auto zero_asset = eosio::asset(0,min_service_fee.symbol);
            vip_table.emplace(get_self(),[&](auto &p){
                p.vip = vip;
                p.create_time = time_point_sec(now());
            });
            viplimit_table.emplace(get_self(),[&](auto &p){
                p.owner = vip;
                p.max_limit = zero_asset;
                p.min_limit = zero_asset;
                p.total_limit = zero_asset;
                p.frequency_limit = 0;
                p.interval_limit = 0;
                p.reset_limit = 0;
            });
            vipfee_table.emplace(get_self(),[&](auto &p){
                p.owner = vip;
                p.service_fee_rate = 0;
                p.min_service_fee = zero_asset;
                p.miner_fee = zero_asset;
            });
        } else {
            vipfee_table.modify(
                vipfee_table.find(vip.value),same_payer,
                [&](auto &p){
                p.service_fee_rate = service_fee_rate;
                p.min_service_fee = min_service_fee;
                p.miner_fee = miner_fee;
            });
        }
    }

    void pegtoken::setvipserfrt_v2(symbol_code sym_code, name vip,double service_fee_rate) {
        auto sym_raw = sym_code.raw();

        auto vipfee_table = vipfees(get_self(), sym_raw);
        auto iter = vipfee_table.find(vip.value);
        if(iter == vipfee_table.end() ) {
            auto zero_asset = eosio::asset(0,eosio::symbol(sym_raw));
            setvipfee_v2(vip,service_fee_rate,zero_asset,zero_asset);
        } else {
            setvipfee_v2(vip,service_fee_rate,iter->min_service_fee ,iter->miner_fee);
        }
    }

    void pegtoken::setvipminfee_v2(name vip, asset min_service_fee ){
        auto sym_raw = min_service_fee.symbol.code().raw();

        auto vipfee_table = vipfees(get_self(), sym_raw);
        auto iter = vipfee_table.find(vip.value);
        if(iter == vipfee_table.end() ) {
            auto zero_asset = eosio::asset(0,eosio::symbol(sym_raw));
            setvipfee_v2(vip,0,min_service_fee,zero_asset);
        } else {
            setvipfee_v2(vip,iter->service_fee_rate,min_service_fee ,iter->miner_fee);
        }
    }

    void pegtoken::setvipminerf_v2(name vip, asset miner_fee ){
        auto sym_raw = miner_fee.symbol.code().raw();

        auto vipfee_table = vipfees(get_self(), sym_raw);
        auto iter = vipfee_table.find(vip.value);
        if(iter == vipfee_table.end() ) {
            auto zero_asset = eosio::asset(0,eosio::symbol(sym_raw));
            setvipfee_v2(vip,0,zero_asset,miner_fee);
        } else {
            setvipfee_v2(vip,iter->service_fee_rate,iter->min_service_fee ,miner_fee);
        }
    }

    void pegtoken::setdelay_v2(symbol_code sym_code, uint64_t delayday) {
        auto sym_raw = sym_code.raw();
        auto info_table = infos(get_self(),sym_raw);
        auto val = info_table.get(sym_raw, "token with symbol not exists(info)");
        require_auth(val.issuer);

        auto delay_table = delays(get_self(),sym_raw);
        if(delay_table.begin()==delay_table.end()){
            delay_table.emplace(get_self(),[&](auto &p){
                p.delay = delayday * ONE_DAY;
            });
        } else {
            delay_table.modify(delay_table.begin(),same_payer,[&](auto &p){
                p.delay = delayday * ONE_DAY;
            });
        }
    }

    void pegtoken::issue_v2(asset quantity, string memo) {
        STRING_LEN_CHECK(memo, 256)
        eosio_assert(quantity.is_valid() && quantity.amount > 0, "invalid quantity");
        auto sym_raw = quantity.symbol.code().raw();
        auto info_table = infos(get_self(),sym_raw);
        auto iter = info_table.find(sym_raw);
        eosio_assert(iter != info_table.end(), "token not exist");
        require_auth(iter->issuer);

        eosio_assert(iter->active, "token is not active");

        auto acceptor_table = acceptors(get_self(),sym_raw);
        eosio_assert(acceptor_table.begin() != acceptor_table.end(), "no acceptor set");
        auto acceptor = acceptor_table.begin()->acceptor;
        ACCOUNT_CHECK(acceptor)
        add_balance(acceptor, quantity, iter->issuer);
        info_table.modify(iter, same_payer, [&](auto &p) {
            p.supply += quantity;
            eosio_assert(p.supply.amount > 0, "supply overflow");
        });

        auto oper = operates(get_self(), quantity.symbol.code().raw());
        oper.emplace(get_self(), [&](auto &p) {
            p.id = oper.available_primary_key();
            p.to = acceptor;
            p.quantity = quantity;
            p.type = 1;
            p.operate_time = time_point_sec(now());
            p.memo = memo;
        });
    }

    void pegtoken::retire_v2(asset quantity, string memo) {
        STRING_LEN_CHECK(memo, 256)

        eosio_assert(quantity.is_valid() && quantity.amount > 0, "invalid quantity");

        auto sym_raw = quantity.symbol.code().raw();
        auto info_table = infos(get_self(),sym_raw);
        auto iter = info_table.find(sym_raw);
        eosio_assert(iter != info_table.end(), "token not exist");
        require_auth(iter->issuer);

        eosio_assert(iter->active, "token is not active");
        eosio_assert(iter->supply >= quantity, "invalid quantity");

        auto acceptor_table = acceptors(get_self(),sym_raw);
        eosio_assert(acceptor_table.begin() != acceptor_table.end(), "no acceptor set");
        auto acceptor = acceptor_table.begin()->acceptor;
        ACCOUNT_CHECK(acceptor)
        sub_balance(acceptor, quantity);
        info_table.modify(iter, same_payer, [&](auto &p) {
            p.supply -= quantity;
        });

        auto oper = operates(get_self(), quantity.symbol.code().raw());
        oper.emplace(get_self(), [&](auto &p) {
            p.id = oper.available_primary_key();
            p.to = acceptor;
            p.quantity = quantity;
            p.type = 0;
            p.operate_time = time_point_sec(now());
            p.memo = memo;
        });
    }

    void pegtoken::precast_v2(symbol_code sym_code, string to_address, name to_account, string remote_trx_id, asset quantity, uint64_t index, string memo) {
        ACCOUNT_CHECK(to_account)
        STRING_LEN_CHECK(memo,256)
        eosio_assert(quantity.amount > 0, "non-positive quantity");

        auto sym_raw = quantity.symbol.code().raw();
        auto info_table = infos(get_self(),sym_raw);
        auto val = info_table.get(sym_raw, "token with symbol not exists(info)");
        eosio_assert(to_account != val.issuer && to_account != get_self(), "invalid to_account");
        require_auth(val.issuer);
        
        // TODO: checks        
        // = checks.find(to_account.value);

        auto addr_table = addrs(get_self(), sym_raw);
        auto iter_addr = addr_table.find(to_account.value);
        eosio_assert(iter_addr != addr_table.end() && iter_addr->address == to_address, "invalid to_address");

        auto cast_table = casts(get_self(), sym_raw);
        
        auto index_str = to_address + to_account.to_string() + remote_trx_id + std::to_string(index) + quantity.to_string();
        cast_table.emplace(get_self(),[&](auto &p){
            p.id = hash64(index_str);
            p.to_account = to_account;
            p.to_address = to_address;
            p.quantity = quantity;
            p.state = 0;
            p.remote_trx_id = remote_trx_id;
            p.index = index;
            p.enable = 0;
            p.msg = memo;

            p.create_time = time_point_sec(now());
            p.update_time = time_point_sec(now());

            p.auditor = NIL_ACCOUNT;
        });
    }

    void pegtoken::agreecast_v2(symbol_code sym_code, string to_address, name to_account, string remote_trx_id, asset quantity, uint64_t index, string memo){
        auto sym_raw = quantity.symbol.code().raw();

        auto addr_table = addrs(get_self(), sym_raw);
        auto iter_addr = addr_table.find(to_account.value);
        eosio_assert(iter_addr != addr_table.end() && iter_addr->address == to_address, "invalid to_address");

        auto cast_table = casts(get_self(), sym_raw);
        auto index_str = to_address + to_account.to_string() + remote_trx_id + std::to_string(index) + quantity.to_string();
        auto iter_cast = cast_table.find(hash64(index_str));
        eosio_assert(iter_cast != cast_table.end()
        && iter_cast -> to_account == to_account
        && iter_cast -> to_address == to_address
        && iter_cast -> remote_trx_id == remote_trx_id
        && iter_cast -> index == index
        && iter_cast -> quantity == quantity
         , "invalid cast");

        cast_table.modify(iter_cast,same_payer,[&](auto &p){
            p.enable = 1;
            p.msg = memo;
            p.update_time = time_point_sec(now());
        });
    }

    void pegtoken::refusecast_v2(symbol_code sym_code, string to_address, name to_account, string remote_trx_id, asset quantity, uint64_t index, string memo){
        auto sym_raw = quantity.symbol.code().raw();
        auto infos_tb = infos(get_self(), sym_raw);
        auto iter_info = infos_tb.find(sym_raw);
        // eosio_assert(iter_info != addr_table.end() && iter_info->address == to_address, "invalid to_address");

        auto cast_table = casts(get_self(), sym_raw);
        auto index_str = to_address + to_account.to_string() + remote_trx_id + std::to_string(index) + quantity.to_string();
        auto iter_cast = cast_table.find(hash64(index_str));
        eosio_assert(iter_cast != cast_table.end()
        && iter_cast -> to_account == to_account
        && iter_cast -> to_address == to_address
        && iter_cast -> remote_trx_id == remote_trx_id
        && iter_cast -> index == index
        && iter_cast -> quantity == quantity
         , "invalid cast");

        cast_table.modify(iter_cast,same_payer,[&](auto &p){
            p.enable = 0;
            p.msg = memo;
            p.update_time = time_point_sec(now());
        });
    }

    void pegtoken::docast_v2(string to_address, name to_account, string remote_trx_id, uint64_t index, asset quantity, string memo) {
        auto sym_raw = quantity.symbol.code().raw();
        auto info_table = infos(get_self(),sym_raw);
        auto iter_info = info_table.find(sym_raw);
        eosio_assert(iter_info != info_table.end(), "token not exist");
        require_auth(iter_info->issuer);

        auto addr_table = addrs(get_self(), sym_raw);
        auto iter_addr = addr_table.find(to_account.value);
        eosio_assert(iter_addr != addr_table.end() && iter_addr->address == to_address, "invalid to_address");

        auto cast_table = casts(get_self(), sym_raw);
        auto index_str = to_address + to_account.to_string() + remote_trx_id + std::to_string(index) + quantity.to_string();
        auto iter_cast = cast_table.find(hash64(index_str));
        eosio_assert(iter_cast != cast_table.end()
        && iter_cast -> to_account == to_account
        && iter_cast -> to_address == to_address
        && iter_cast -> remote_trx_id == remote_trx_id
        && iter_cast -> index == index
        && iter_cast -> quantity == quantity
         , "invalid cast");

        cast_table.modify(iter_cast,same_payer,[&](auto &p){
            p.trx_id = get_trx_id();
            p.msg = memo;
            p.update_time = time_point_sec(now());
        });

        add_balance(to_account, quantity, iter_info->issuer);
        info_table.modify(iter_info,same_payer,[&](auto &p){
            p.supply += quantity;
            eosio_assert(p.supply.amount >0, "supply overflow");
        });
    }

    void pegtoken::melt_v2(name from_account, string to_address, asset quantity, uint64_t index, string memo){
        ACCOUNT_CHECK(from_account);
        // verify_address(to_address);
        is_vip(quantity.symbol.code(), from_account);
        // limits.find()
        // compare the quantity with min_limit and max_limit

        // 当前时间，对比上次提币时间需要大于最小间隔数
        // 距离上个自然日零点到申请提币时，累计金额和次数分别需要小于相关设定：total_limit和frequency_limit

        // 以内联action的方式调用ruin, 减少from_account里面的余额
        // 减小infos表中supply的值，数值为总额减去费用。

        // 在melts添加一条记录，need_check置为false，enable字段置为false。
        auto melt_tb = melts(get_self(), quantity.symbol.code().raw());
        // melts meltss(_self, _self.value); //到底应当事先哪一种呢
        melt_tb.emplace(same_payer, [&](auto& mt){
            mt.id = melt_tb.available_primary_key();
            // mt.trx_id;
            mt.from = from_account;
            mt.to = to_address;
            mt.amount = quantity;
            // mt.amount = ;
            // mt.fee = ;
            // mt.state = 
        });
        // need_check
    }
    void pegtoken::premelt_v2(name from_account, string to_address, asset quantity, uint64_t index, string memo){

    }

    void pegtoken::agreemelt_v2(name from_account, string to_address, asset quantity, uint64_t index, string memo){
    
    }

    void pegtoken::refusemelt_v2(name from_account, string to_address, asset quantity, uint64_t index, string memo){

    }

    void pegtoken::setauditor_v2(symbol_code sym_code, string action, name auditor){
        auto auditor_tb = auditors(get_self(), sym_code.raw());
        auto aud_iter = auditor_tb.find(sym_code.raw());
        if(action.compare("add")){
            auditor_tb.emplace(get_self(), [&](auto& aud){
                aud.auditor = auditor;
            });
        } else if(action == "remove"){
            auditor_tb.erase(aud_iter);
        }
    }

    void pegtoken::setmanager_v2(symbol_code sym_code, name manager){
        auto manager_tb = managers(get_self(), sym_code.raw());
        auto mgr_iter = manager_tb.find(sym_code.raw());
        if(action == "add"_n){
            eosio_assert(mgr_iter != manager_tb.end(), "vip has been assigned based on sym_code");
            manager_tb.emplace(get_self(), [&](auto& mgr){
                mgr.manager = manager;
            });
        } else if(action == "remove"_n){
            manager_tb.erase(mgr_iter);
        }
    }

    void pegtoken::setgatherer_v2(symbol_code sym_code, name gatherer){
        auto gather_tb = gatherers(get_self(), sym_code.raw());
        auto gather_iter = gather_tb.find(sym_code.raw());
        if(action == "add"_n){
            // 检查是否已经绑定地址
            eosio_assert(gather_iter != gather_tb.end(), "This account has been assigned as gatherer based on sym_code");
            gather_tb.emplace(get_self(), [&](auto& gather){
                gather.gatherer = gatherer;
            });
        } else if(action == "remove"_n){
            eosio_assert(gather_iter != gather_tb.end(), "No gatherer can be removed based on sym_code");
            gather_tb.erase(gather_iter);
        }
    }

    void pegtoken::setteller_v2(symbol_code sym_code, name teller){
        //TODO: 检查sym_code的余额，需要使用eosio.token合约
        auto teller_tb = tellers(get_self(), sym_code.raw());
        auto teller_iter = teller_tb.find(sym_code.raw());
        if(action == "add"_n){
            // 检查是否已经绑定地址
            eosio_assert(teller_iter != teller_tb.end(), "This account has been assigned as teller based on sym_code");
            teller_tb.emplace(get_self(), [&](auto& tell){
                tell.teller = teller;
            });
        } else if(action == "remove"_n){
            eosio_assert(teller_iter != teller_tb.end(), "No teller can be removed  based on sym_code");
            teller_tb.erase(teller_iter);
        }
    }

    void pegtoken::setvip_v2(symbol_code sym_code, string action, name vip){
        //TODO: 检查sym_code的余额，需要使用eosio.token合约
        auto vip_tb = vips(get_self(), sym_code.raw());
        auto vip_iter = vip_tb.find(sym_code.raw());
        if(action == "add"_n){
            // 检查是否已经绑定地址
            eosio_assert(vip_iter != vip_tb.end(), "This account has been assigned as vip based on sym_code");
            vip_tb.emplace(get_self(), [&](auto& vp){
                vp.vip = vip;
            });
        } else if(action == "remove"_n){
            eosio_assert(vip_iter != vip_tb.end(), "No vip can be removed based on sym_code");
            vip_tb.erase(vip_iter);
        }
    }

    void pegtoken::resetaddress_v2(symbol_code sym_code, name to ){

    }
    
    void pegtoken::withdraw_v2( name from, string to, asset quantity, uint64_t index, string memo){

    }

    void pegtoken::prewithdraw_v2(name from, string to, asset quantity, uint64_t index, string memo){

    }

    void pegtoken::agrewithdraw_v2( name from, string to, asset quantity, uint64_t index, string memo){

    }

    void pegtoken::refuwithdraw_v2( name from, string to, asset quantity, uint64_t index, string memo){
    
    }

    void pegtoken::remit_v2( name from, asset quantity ){
    
    }

    void pegtoken::pay_v2( asset quantity ){
    
    }

    void pegtoken::ruin_v2( asset quantity ){
    
    }
    

    void pegtoken::burn_v2( name from, asset quantity){

    }

    void pegtoken::retreat_v2(name to, asset quantity ){
         
    }

    void pegtoken::denyback_v2( symbol_code sym_code, transaction_id_type trx_id, uint64_t index,  string memo ){

    }

    void pegtoken::sendback_v2(transaction_id_type trx_id, name to, asset quantity, string memo ){

    }

    void pegtoken::lockall_v2( symbol_code sym_code, name brakeman ){
        require_auth(brakeman);
        auto sym_raw = sym_code.raw();
        auto infos_tb = infos(get_self(), sym_raw);
        auto iter = infos_tb.find(sym_raw);
        eosio_assert(iter != infos_tb.end(), "token not exist");
        {
            auto braks = brakemans(get_self(), sym_raw);
            eosio_assert(braks.find(brakeman.value) != braks.end(), "brakeman not exist");
        }

        eosio_assert(iter->active == false, "this token is not being locked");
        infos_tb.modify(iter, same_payer, [&](auto &p) { p.active = false; });
    }

    void pegtoken::unlockall_v2(symbol_code sym_code, name brakeman ){
        require_auth(brakeman);
        auto sym_raw = sym_code.raw();
        auto infos_tb = infos(get_self(), sym_raw);
        auto iter = infos_tb.find(sym_raw);
        eosio_assert(iter != infos_tb.end(), "token not exist");
        {
            auto braks = brakemans(get_self(), sym_raw);
            eosio_assert(braks.find(brakeman.value) != braks.end(), "brakeman not exist");
        }

        eosio_assert(iter->active == false, "this token is not being locked");
        infos_tb.modify(iter, same_payer, [&](auto &p) { p.active = true; });
    }

 
    // void pegtoken::feedback_v2
}