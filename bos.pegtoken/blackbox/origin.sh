# Private key: 5JNzcBuxPGmF3Saw3cedYzE6jL7VksFayxqpjokMTRpARkCwmHa
# Public key: EOS7UCx8GSeEHC4XE8jQ1R5WJqw5Vp2vZqWgQx94obFVbebnYg6eq

PUBKEY=EOS5zhvmicLyPRvvY1a5TbYj1aNfqbMmd1ezgknWLrbR87fMnpnwo
URL='-u http://127.0.0.1:9999'

###=============================================== 创建账号

ACCOUNTS=(
    "eosio.token" "btc.bos" "eth.bos" "usdt.bos"
    "boshuobipool" "huobimanager" "btcbtcbtcbtc" "ethethetheth" "usdtusdtusdt"
    "huobiauditor" "auditorhuobi" "hbhbgatherer" "hbhbbrakeman"
    "hbhbgathere2" "huobimanage2" "hbhbbrakema2" "huobihuaping" "xiaomingming"
    "pegtokenbzsq" "boscorepeg11" "pegauditor11" "peggatherer1" "peggatherer2"
    "pegteller111" "pegteller112" "pegmanager11" "pegbrakeman1"
)
for account in ${ACCOUNTS[*]}
do
    echo -e "\n creating $account \n"; 
    cleos ${URL} system newaccount --stake-cpu "10.0000 BOS" --stake-net "10.0000 BOS" --buy-ram "30.0000 BOS" eosio ${account} ${PUBKEY}; 
    sleep 1; 
done

###=============================================== 部署合约
BTC_BOS=btc.bos
ETH_BOS=eth.bos
USDT_BOS=usdt.bos
cleos ${URL} set contract $BTC_BOS /root/boscdt-docker/pegtoken/bos.contracts/build/bos.pegtoken -p $BTC_BOS

###=============================================== create
cleos ${URL} push action $BTC_BOS create '["8,BTC", "boscorepeg11", "bitcoin"]' -p $BTC_BOS

###=============================================== setissuer
cleos ${URL} push action $BTC_BOS setissuer '["BTC", "boscorepeg11"]' -p $BTC_BOS

###=============================================== PERMISSION
cleos ${URL} set account permission $BTC_BOS active '{"threshold": 1,"keys": [{"key": "EOS5zhvmicLyPRvvY1a5TbYj1aNfqbMmd1ezgknWLrbR87fMnpnwo","weight": 1}],"accounts": [{"permission":{"actor":"btc.bos","permission":"eosio.code"},"weight":1}]}' owner -p $BTC_BOS
# cleos set account permission boscorepeg11 active '{"threshold": 1,"keys": [{"key": "EOS5zhvmicLyPRvvY1a5TbYj1aNfqbMmd1ezgknWLrbR87fMnpnwo","weight": 1}],"accounts": [{"permission":{"actor":"btc.bos","permission":"eosio.code"},"weight":1}]}' owner -p boscorepeg11

###=============================================== setauditor
cleos ${URL} push action $BTC_BOS setauditor '["BTC","add","pegauditor11"]' -p boscorepeg11
# cleos push action $BTC_BOS setauditor '["BTC","remove","pegauditor11"]' -p boscorepeg11

###=============================================== setgatherer
cleos ${URL} push action $BTC_BOS setgatherer '["BTC","peggatherer1"]' -p boscorepeg11
# cleos push action $BTC_BOS setgatherer '["BTC","peggatherer2"]' -p boscorepeg11

###=============================================== setteller
cleos ${URL} push action $BTC_BOS setteller '["BTC","pegteller111"]' -p boscorepeg11
cleos ${URL} push action $BTC_BOS setteller '["BTC","pegteller112"]' -p boscorepeg11

###=============================================== setmanager
cleos ${URL} push action $BTC_BOS setmanager '["BTC","pegmanager11"]' -p boscorepeg11

###=============================================== setbrakeman
cleos ${URL} push action $BTC_BOS setbrakeman '["BTC","pegbrakeman1"]' -p boscorepeg11

###=============================================== setlimit
#cleos ${URL} push action $BTC_BOS setlimit '["BTC", "100.00000000 BTC","0.00005000 BTC","100.00000000 BTC","100","10"]' -p pegmanager11

###=============================================== setfee
#cleos ${URL} push action $BTC_BOS setfee '["BTC", "0.001","0.00005000 BTC", "0.00004000 BTC"]' -p pegmanager11

###=============================================== setvip
#cleos ${URL} push action $BTC_BOS setvip '["BTC", "add", "huobihuaping"]' -p pegmanager11
# cleos push action $BTC_BOS setvip '["BTC", "remove", "huobihuaping"]' -p pegmanager11

###=============================================== setviplimit
#cleos ${URL} push action $BTC_BOS setviplimit '["BTC", "huobihuaping", "2.00000000 BTC","0.10005000 BTC","10.10000000 BTC","100","10"]' -p pegmanager11

###=============================================== setvipfee
#cleos ${URL} push action $BTC_BOS setvipfee '["BTC", "huobihuaping","0.002","0.00015000 BTC", "0.00003000 BTC"]' -p pegmanager11

###=============================================== setcheck
cleos ${URL} push action $BTC_BOS setcheck '["BTC", true, false]' -p pegmanager11

###=============================================== applyaddr
cleos ${URL} push action $BTC_BOS applyaddr '[ "BTC", "peggatherer2" ]' -p peggatherer2
cleos ${URL} push action $BTC_BOS applyaddr '[ "BTC", "huobihuaping" ]' -p huobihuaping

###=============================================== assignaddr
cleos ${URL} push action $BTC_BOS assignaddr '["BTC", "huobihuaping", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6"]' -p pegteller112

###=============================================== resetaddress
# cleos ${URL} push action $BTC_BOS resetaddress '[ "BTC", "huobihuaping" ]' -p pegmanager11

###=============================================== precast
cleos ${URL} push action $BTC_BOS precast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "huobihuaping", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "10000.00100000 BTC", "1","memo"]' -p pegteller112

###=============================================== agreecast
cleos ${URL} push action $BTC_BOS agreecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "huobihuaping", "pegauditor11","fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619", "10000.00100000 BTC", "1","memo"]' -p pegauditor11

###=============================================== melt
cleos ${URL} push action $BTC_BOS melt '["huobihuaping", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "1.00000000 BTC","1","memo"]' -p huobihuaping

###=============================================== denyback
cleos ${URL} push action $BTC_BOS denyback '[ "BTC", "68d24d1753c20b97cc4eb572042f78ff6057e53aec165692553fdbf051506e8b", 0, "BTC回滚" ]' -p pegteller112
cleos ${URL} push action $BTC_BOS denyback '[ "BTC", "ea33c0ec0dc06e7c6d217d4bbf34cf2a3b3de62f8b5af000ff4f124c49bcbdb0", 0, "BTC回滚2" ]' -p pegteller112
cleos ${URL} push action $BTC_BOS denyback '[ "BTC", "96926c93134c9c23d1f4dd5fd2e61a80392a9006cd7ab15d55f3da16f876884e", 0, "BTC回滚3" ]' -p pegteller112
cleos ${URL} push action $BTC_BOS denyback '[ "BTC", "bfe7dc205fa1696d11dd8d3a902ac8b28038aae9275efffa19c31351e275707e", 0, "BTC回滚4" ]' -p pegteller112

cleos ${URL} push action $BTC_BOS denyback '[ "BTC", "4038a3aefbce80149cfefdb9d70c8f6878c09846360f39f9be573832dcbab9ab", 0, "BTC回滚6" ]' -p pegteller112
cleos ${URL} push action $BTC_BOS denyback '[ "BTC", "8ebec144cd355668d27640958be3cf01f08ae5b1c4783f20c34af0d71eee418b", 0, "BTC回滚7" ]' -p pegteller112

###=============================================== confirmback
cleos ${URL} push action $BTC_BOS confirmback '[ "BTC", "5b641b15168df9ce49295c694ed9e77608b0708bc60238b100eb483ec481ead2", "faee959898c691c89fc7497f3ab5ab08c2cc7865f48064b803781efa8958cd65", 1, 1, "BTC反馈" ]' -p pegteller112
###=============================================== Tables

### Token 相关表
cleos ${URL} get table $BTC_BOS BTC symbols
cleos ${URL} get table $BTC_BOS BTC pegs
cleos ${URL} get table $BTC_BOS BTC infos
cleos ${URL} get table $BTC_BOS BTC summaries
cleos ${URL} get table $BTC_BOS BTC limits
cleos ${URL} get table $BTC_BOS BTC fees
cleos ${URL} get table $BTC_BOS BTC checks

### 角色相关表
cleos ${URL} get table $BTC_BOS BTC auditors
cleos ${URL} get table $BTC_BOS BTC gathers
cleos ${URL} get table $BTC_BOS BTC tellers
cleos ${URL} get table $BTC_BOS BTC managers
ceos ${URL} get table $BTC_BOS BTC brakemans

cleos ${URL} get table $BTC_BOS BTC addrs
cleos ${URL} get table $BTC_BOS BTC records
cleos ${URL} get table $BTC_BOS BTC statistics

cleos ${URL} get table $BTC_BOS BTC casts
cleos ${URL} get table $BTC_BOS BTC melts

### VIP 相关表
cleos ${URL} get table $BTC_BOS BTC vips
cleos ${URL} get table $BTC_BOS BTC viplimits
cleos ${URL} get table $BTC_BOS BTC vipfees

### 用户余额
cleos ${URL} get table $BTC_BOS huobihuaping accounts
cleos ${URL} get currency balance $BTC_BOS huobihuaping
