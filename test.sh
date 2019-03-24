cleos push action pegtokenl323 create '["8,BTC", "boscorepeg11",  "bitcoin"]' -p pegtokenl323
cleos push action pegtokenl323 setissuer '["BTC", "boscorepeg11"]' -p pegtokenl323
cleos push action pegtokenl323 setauditor '["BTC","add","pegauditor11"]' -p boscorepeg11
cleos push action pegtokenl323 setauditor '["BTC","add","pegauditor12"]' -p boscorepeg11
cleos push action pegtokenl323 setauditor '["BTC","remove","pegauditor11"]' -p boscorepeg11
cleos push action pegtokenl323 setauditor '["BTC","add","pegauditor12"]' -p boscorepeg11
cleos push action pegtokenl323 setauditor '["BTC","add","pegauditor12"]' -p pegbrakeman1
cleos push action pegtokenl323 setgatherer '["BTC","peggatherer1"]' -p boscorepeg11
cleos push action pegtokenl323 setgatherer '["BTC","peggatherer2"]' -p boscorepeg11
cleos push action pegtokenl323 setgatherer '["BTC","peggatherer1"]' -p boscorepeg11
cleos push action pegtokenl323 setgatherer '["BTC","peggatherer3"]' -p boscorepeg11
cleos push action pegtokenl323 setgatherer '["BTC","peggatherer2"]' -p pegmanager11
cleos push action pegtokenl323 setteller '["BTC","pegteller111"]' -p boscorepeg11
cleos push action pegtokenl323 setteller '["BTC","pegteller112"]' -p boscorepeg11
cleos push action pegtokenl323 setteller '["BTC","pegteller113"]' -p boscorepeg11
cleos push action pegtokenl323 setteller '["BTC","pegteller113"]' -p peggatherer1

cleos push action pegtokenl323 setmanager '["BTC","pegmanager11"]' -p boscorepeg11
cleos push action pegtokenl323 setmanager '["BTC","pegmanager12"]' -p boscorepeg11
cleos push action pegtokenl323 setmanager '["BTC","pegteller112"]' -p boscorepeg11
cleos push action pegtokenl323 setmanager '["BTC","pegbrakeman2"]' -p boscorepeg11
cleos push action pegtokenl323 setmanager '["BTC","pegbrakeman1"]' -p pegauditor11
cleos push action pegtokenl323 setbrakeman '["BTC","pegbrakeman1"]' -p boscorepeg11
cleos push action pegtokenl323 setbrakeman '["BTC","pegbrakeman2"]' -p boscorepeg11
cleos push action pegtokenl323 setbrakeman '["BTC","pegbrakeman3"]' -p boscorepeg11
cleos push action pegtokenl323 setbrakeman '["BTC","pegbrakeman2"]' -p pegteller112

cleos push action pegtokenl323 setlimit '["BTC", "1.00000000 BTC","0.00005000 BTC","10.00000000 BTC","3","300"]' -p pegmanager11
cleos push action pegtokenl323 setlimit '["BTC", "2.00000000 BTC","0.00010000 BTC","11.00000000 BTC","3","300"]' -p pegmanager11
cleos push action pegtokenl323 setlimit '["BTC", "1.00000000 BTC","0.00005000 BTC","10.00000000 BTC","3","300"]' -p zhangshiqi11
cleos push action pegtokenl323 setlimit '["BTC", "1.00000000 BTC","0.00005000 BTC","10.00000000 BTC","3","300"]' -p pegbrakeman1
cleos get table pegtokenl323 BTC fee
cleos push action pegtokenl323 setfee '["BTC", "0.001","0.00005000 BTC", "0.00004000 BTC"]' -p pegmanager11
cleos push action pegtokenl323 setfee '["BTC", "0.002","0.00006000 BTC", "0.00005000 BTC"]' -p pegmanager11
cleos push action pegtokenl323 setfee '["BTC", "0.001","0.00005000 BTC", "0.00004000 BTC"]' -p zhangshiqi11
cleos push action pegtokenl323 setfee '["BTC", "0.001","0.00005000 BTC", "0.00004000 BTC"]' -p pegbrakeman1
cleos push action pegtokenl323 setvip '["BTC", "add", "vipaccount11"]' -p pegmanager11
cleos push action pegtokenl323 setvip '["BTC", "add", "zhangshiqi11"]' -p pegmanager11
cleos push action pegtokenl323 setvip '["BTC", "remove", "zhangshiqi11"]' -p pegmanager11
cleos push action pegtokenl323 setvip '["BTC", "remove", "huobihuaping"]' -p pegmanager11

cleos push action pegtokenl323 setviplimit '["BTC", "vipaccount11", "2.00000000 BTC","0.10005000 BTC","10.10000000 BTC","3","300"]' -p pegmanager11
cleos push action pegtokenl323 setviplimit '["BTC", "vipaccount11", "3.00000000 BTC","0.10005000 BTC","13.10000000 BTC","3","300"]' -p pegmanager11
cleos push action pegtokenl323 setviplimit '["BTC", "zhangshiqi11", "2.00000000 BTC","0.00006000 BTC","11.00000000 BTC","3","300"]' -p pegmanager11

cleos push action pegtokenl323 setvipfee '["BTC", "huobihuaping","0.002","0.00015000 BTC", "0.00003000 BTC"]' -p pegmanager11
cleos push action pegtokenl323 setvipfee '["BTC", "boscorebos11","0.002","0.00015000 BTC", "0.00003000 BTC"]' -p pegmanager11
cleos push action pegtokenl323 setcheck '["BTC", true,false]' -p pegmanager11
cleos push action pegtokenl323 applyaddr '[ "BTC", "ordaccount11" ]' -p ordaccount11
cleos push action pegtokenl323 assignaddr '["BTC", "ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6"]' -p pegteller111
cleos push action pegtokenl323 assignaddr '["BTC", "ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6"]' -p pegteller111
cleos push action pegtokenl323 assignaddr '["BTC", "ordaccount11", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB"]' -p pegteller111
cleos push action pegtokenl323 assignaddr '["BTC", "vipaccount11", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB"]' -p pegteller111
cleos push action pegtokenl323 resetaddress '[ "BTC", "ordaccount11" ]' -p pegmanager11
cleos push action pegtokenl323 cast '["BTC", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "huobihuaping", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "10000.00100000 BTC", "1","memo"]' -p pegmanager11
cleos push action pegtokenl323 precast '["BTC", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "ordaccount11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "10000.00100000 BTC", "1","memo"]' -p pegteller111
cleos push action pegtokenl323 precast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "huobihuaping", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "10000.00100000 BTC", "1","memo"]' -p pegteller112
cleos push action pegtokenl323 precast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "10000.00100000 BTC", "1","memo"]' -p pegteller11

cleos push action pegtokenl323 precast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "100.00100000 BTC", "1","memo"]' -p pegteller11

cleos push action pegtokenl323 precast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "10000.00100000 BTC", "2","memo"]' -p pegteller11



cleos push action pegtokenl323 agreecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11",  "ordaccount12","fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 agreecast '["BTC", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "ordaccount11", "pegauditor11","fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 agreecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "pegauditor11","fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652621",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 agreecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "pegauditor11","fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "1000.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 agreecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "peggatherer2", "pegmanager11","fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "10000.00100000 BTC", "1","memo"]' -p pegmanager11
cleos push action pegtokenl323 agreecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "pegauditor11","fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652619",  "10000.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 refusecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "huobihuaping", "pegauditor11","fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652618",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 refusecast '["BTC", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "ordaccount11","pegauditor11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652618",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 refusecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11","pegauditor11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652518",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 refusecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11","pegauditor11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652618",  "10000.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 refusecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11","pegauditor12", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652618",  "100.00100000 BTC", "1","memo"]' -p pegauditor12
1.cleos push action pegtokenl323 precast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652618",  "100.00100000 BTC", "1","memo"]' -p pegteller11
.cleos push action pegtokenl323 refusecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11","pegauditor11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652618",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "2.00000000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "30036.00000000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.20000000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "9957.00000000 BTC","1","memo"]' -p vipaccount11



cleos push action pegtokenl323 confirmback '[ "BTC", "5b641b15168df9ce49295c694ed9e77608b0708bc60238b100eb483ec481ead2", "faee959898c691c89fc7497f3ab5ab08c2cc7865f48064b803781efa8958cd65","1","1", "BTC反馈" ]' -p pegteller111
cleos push action pegtokenl323 denyback '[ "BTC", "72e82e0829087619b97358921e6e4e4826a3469e669a000411be49a783c890b8", 0, "BTC回滚" ]' -p pegteller111
cleos push action pegtokenl323 lockall '["BTC","pegbrakeman1"]' -p pegbrakeman1
cleos push action pegtokenl323 precast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652616",  "100.00100000 BTC", "1","memo"]' -p pegteller111
cleos push action pegtokenl323 agreecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11","pegauditor11" "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652616",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 refusecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11","pegauditor11" "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652616",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 confirmback '[ "BTC", "5b641b15168df9ce49295c694ed9e77608b0708bc60238b100eb483ec481ead2", "faee959898c691c89fc7497f3ab5ab08c2cc7865f48064b803781efa8958cd65","1","1", "BTC反馈" ]' -p pegteller111
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "100.00100000 BTC","1","memo"]' -p peggatherer1
cleos push action pegtokenl323 unlockall '["BTC","pegbrakeman1"]' -p pegbrakeman1
cleos push action pegtokenl323 precast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11", "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652616",  "100.00100000 BTC", "1","memo"]' -p pegteller111
cleos push action pegtokenl323 agreecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11","pegauditor11" "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652616",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323 refusecast '["BTC", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "ordaccount11","pegauditor11" "fe2f90783080925ef63b9369f3e00df6860d921806655543f582e869e4652616",  "100.00100000 BTC", "1","memo"]' -p pegauditor11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "100.00100000 BTC","1","memo"]' -p ordaccount11

cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00001000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "11.00100000 BTC","1","memo"]' -p ordaccount11
300s内重复一个操作：cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00060000 BTC","1","memo"]' -p ordaccount11
执行三次cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00100000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00100000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00001000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "11.00100000 BTC","1","memo"]' -p ordaccount11
3s内重复一个操作：cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00060000 BTC","1","memo"]' -p ordaccount11
3s后重复一个操作：cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00060000 BTC","1","memo"]' -p ordaccount11
执行三次cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00100000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00005000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00060000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "2.00000000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00005000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "0.00060000 BTC","1","memo"]' -p ordaccount11
cleos push action pegtokenl323  melt '["ordaccount11", "1F7XiwJTfZEpFDGikNC71U6MBBeLsrsDd6", "2.00000000 BTC","1","memo"]' -p ordaccount11

cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.00004000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "5.00000000 BTC","1","memo"]' -p vipaccount11
3s内重复执行cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.00600000 BTC","1","memo"]' -p vipaccount11
执行三次cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.00500000 BTC","1","memo"]' -p vipaccount11

cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.00100000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "11.00100000 BTC","1","memo"]' -p vipaccount11
300s内重复执行cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "4.00100000 BTC","1","memo"]' -p vipaccount11
执行三次cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.00100000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount12", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "0.000040000 BTC","1","memo"]' -p vipaccount12
cleos push action pegtokenl323  melt '["vipaccount12", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "2.000000000 BTC","1","memo"]' -p vipaccount12
300s内重复执行cleos push action pegtokenl323  melt '["vipaccount12", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "0.00100000 BTC","1","memo"]' -p vipaccount12
执行三次cleos push action pegtokenl323  melt '["vipaccount12", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "0.00100000 BTC","1","memo"]' -p vipaccount12
 cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.00006000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.01000000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.20000000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.05000000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "0.10000000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount11", "18gbTSgKDsodCeTZAMnR82BcGbnBfU61yW", "1.00000000 BTC","1","memo"]' -p vipaccount11
cleos push action pegtokenl323  melt '["vipaccount12", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "0.00500000 BTC","1","memo"]' -p vipaccount12
cleos push action pegtokenl323  melt '["vipaccount12", "3JQSigWTCHyBLRD979JWgEtWP5YiiFwcQB", "0.20000000 BTC","1","memo"]' -p vipaccount12
