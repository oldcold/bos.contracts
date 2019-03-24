URL='-u http://127.0.0.1:9999'

###=============================================== 部署合约
BTC_BOS=btc.bos
ETH_BOS=eth.bos
USDT_BOS=usdt.bos
cleos ${URL} set contract $BTC_BOS /root/boscdt-docker/pegtoken/bos.contracts/build/bos.pegtoken -p $BTC_BOS

###=============================================== create
cleos ${URL} push action $BTC_BOS create '["8,BTC", "boscorepeg11", "bitcoin"]' -p $BTC_BOS

###=============================================== setissuer
cleos ${URL} push action $BTC_BOS setissuer '["BTC", "boscorepeg11"]' -p $BTC_BOS

###=============================================== setlimit
cleos ${URL} push action $BTC_BOS setlimit '["BTC", "100.00000000 BTC","0.00005000 BTC","100.00000000 BTC","100","10"]' -p pegmanager11

###=============================================== setfee
cleos ${URL} push action $BTC_BOS setfee '["BTC", "0.001","0.00005000 BTC", "0.00004000 BTC"]' -p pegmanager11

###=============================================== setvip
cleos ${URL} push action $BTC_BOS setvip '["BTC", "add", "huobihuaping"]' -p pegmanager11
#cleos push action $BTC_BOS setvip '["BTC", "remove", "huobihuaping"]' -p pegmanager11

###=============================================== setviplimit
cleos ${URL} push action $BTC_BOS setviplimit '["BTC", "huobihuaping", "2.00000000 BTC","0.10005000 BTC","10.10000000 BTC","100","10"]' -p pegmanager11

###=============================================== setvipfee
cleos ${URL} push action $BTC_BOS setvipfee '["BTC", "huobihuaping","0.002","0.00015000 BTC", "0.00003000 BTC"]' -p pegmanager11

###=============================================== setcheck
cleos ${URL} push action $BTC_BOS setcheck '["BTC", true, false]' -p pegmanager11
