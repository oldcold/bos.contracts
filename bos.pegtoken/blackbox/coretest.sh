URL='-u http://127.0.0.1:9999'

###=============================================== 部署合约
BTC_BOS=btc.bos
ETH_BOS=eth.bos
USDT_BOS=usdt.bos
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
