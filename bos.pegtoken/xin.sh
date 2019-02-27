rm /data3/flash/bos.pegtoken/bos.pegtoken.abi
eosio-cpp -abigen /data3/flash/build/bos.pegtoken/src/bos.pegtoken.cpp --contract=bos.pegtoken -abigen_output=/data3/flash/build/bos.pegtoken/bos.pegtoken.abi -I=/data3/flash/build/bos.pegtoken/include/ -DTESTNET


rm /data3/flash/build/bos.pegtoken/bos.pegtoken.wast
eosio-cpp -I=/data3/flash/build/bos.pegtoken/include/ -o /data3/flash/build/bos.pegtoken/bos.pegtoken.wast /data3/flash/build/bos.pegtoken/src/bos.pegtoken.cpp -DTESTNET

rm /data3/flash/build/bos.pegtoken/bos.pegtoken.wasm
eosio-cpp -I=/data3/flash/build/bos.pegtoken/include/ -o /data3/flash/build/bos.pegtoken/bos.pegtoken.wasm /data3/flash/build/bos.pegtoken/src/bos.pegtoken.cpp -DTESTNET

