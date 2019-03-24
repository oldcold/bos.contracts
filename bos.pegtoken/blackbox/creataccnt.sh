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

