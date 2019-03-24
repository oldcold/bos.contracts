URL='-u http://127.0.0.1:9999'

###=============================================== 部署合约
BTC_BOS=btc.bos
ETH_BOS=eth.bos
USDT_BOS=usdt.bos

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
