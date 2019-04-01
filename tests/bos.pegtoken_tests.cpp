#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include "eosio.system_tester.hpp"

#include "Runtime/Runtime.h"

#include <fc/variant_object.hpp>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

class bos_pegtoken_tester : public tester {
public:

   bos_pegtoken_tester() {
      produce_blocks( 2 );

      create_accounts( { N(alice), N(bob), N(eosio.token),N(btc.bos) } );
      produce_blocks( 2 );

      set_code( N(btc.bos), contracts::pegtoken_wasm() );
      set_abi( N(btc.bos), contracts::pegtoken_abi().data() );

      produce_blocks(2);

      const auto& accnt = control->db().get<account_object,by_name>( N(btc.bos) );
      abi_def abi;
      BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
      abi_ser.set_abi(abi, abi_serializer_max_time);
   }

   action_result push_action( const account_name& signer, const action_name &name, const variant_object &data ) {
      string action_type_name = abi_ser.get_action_type(name);

      action act;
      act.account = N(btc.bos);
      act.name    = name;
      act.data    = abi_ser.variant_to_binary( action_type_name, data,abi_serializer_max_time );

      return base_tester::push_action( std::move(act), uint64_t(signer));
   }

    fc::variant get_symbols( const string& symbolname ){
      auto symb = eosio::chain::symbol::from_string(symbolname);
      auto symbol_code = symb.to_symbol_code().value;
                                            // 
      vector<char> data = get_row_by_account( N(btc.bos), N(btc.bos), N(symbols), symbol_code );
      return data.empty() ? fc::variant() : abi_ser.binary_to_variant( "symbol_ts", data, abi_serializer_max_time );
   }


   fc::variant get_issuers( const string& symbolname ){
      auto symb = eosio::chain::symbol::from_string(symbolname);
      auto symbol_code = symb.to_symbol_code().value;
                                            // 
      vector<char> data = get_row_by_account( N(btc.bos), N(btc.bos), N(symbols), symbol_code );
      return data.empty() ? fc::variant() : abi_ser.binary_to_variant( "symbol_ts", data, abi_serializer_max_time );
   }

   fc::variant get_nian( const string& symbolname )
   {
      auto symb = eosio::chain::symbol::from_string(symbolname);
      auto symbol_code = symb.to_symbol_code().value;
      vector<char> data = get_row_by_account( N(btc.bos), symbol_code, N(niao), symbol_code );
      return data.empty() ? fc::variant() : abi_ser.binary_to_variant( "sscc_ts", data, abi_serializer_max_time );
   }

   fc::variant get_addrs( const name act, symbol_code sym ) {
      vector<char> data = get_row_by_account( N(btc.bos), act, N(addrs), act.value );
      return abi_ser.binary_to_variant( "personal", data, abi_serializer_max_time );
   }

    fc::variant get_statistics( const name act, symbol_code sym  ) {
      vector<char> data = get_row_by_account( N(btc.bos), act, N(statistics), act.value );
      return abi_ser.binary_to_variant( "personal", data, abi_serializer_max_time );
   }

   action_result create( symbol sym, name issuer, name address_style ){
        return push_action( N(btc.bos), N(create), mvo()
           ( "sym", sym)
           ( "issuer", issuer)
           ( "address_style", address_style)
      );
   }


   action_result specialcret( account_name issuer,
                asset        maximum_supply ) {
      return push_action( N(btc.bos), N(specialcret), mvo()
           ( "issuer", issuer)
           ( "maximum_supply", maximum_supply)
      );
   }


    action_result setissuer( symbol_code sym_code, name issuer )  {
      return push_action( N(btc.bos), N(setissuer), mvo()
           ( "sym_code", sym_code)
           ( "issuer", issuer)
      );
    }
   abi_serializer abi_ser;
};

BOOST_AUTO_TEST_SUITE(bos_pegtoken_tests)



BOOST_FIXTURE_TEST_CASE( pp_tests, bos_pegtoken_tester ) try {

   auto token = specialcret( N(alice), asset::from_string("1000.000 TKN"));
   auto nian = get_nian("3,TKN");
   REQUIRE_MATCHING_OBJECT( nian, mvo()
      ("supply", "0.000 TKN")
      ("max_supply", "1000.000 TKN")
      ("issuer", "alice")
   );
   produce_blocks(1);

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( create_tests, bos_pegtoken_tester ) try {
   auto token = create( symbol(SY(8,BTC)), N(btc.bos), "bitcoin");
   auto syms = get_symbols("8,BTC");
   REQUIRE_MATCHING_OBJECT( syms, mvo()
      ("sym", symbol(SY(8,BTC)))
      // ("sym", eosio::chain::symbol::from_string("8,BTC"))
   );
   produce_blocks(1);

} FC_LOG_AND_RETHROW()


// BOOST_FIXTURE_TEST_CASE( create_wrong_style, bos_pegtoken_tester ) try {
//    auto token = create( symbol(SY(8, BTC)), "btc.bos", "fdsf");
//    auto syms = get_symbols("8,BTC");
//    REQUIRE_MATCHING_OBJECT( syms, mvo()
//       ("symbol", symbol(SY(8, BTC)))
//       ("issuer", "btc.bos")
//       ("address_style", "bitcoin")
//    );
//    produce_blocks(1);

//    BOOST_REQUIRE_EQUAL( wasm_assert_msg( "address_style must be one of bitcoin, ethereum, tether or other" ),
//                         create( symbol(SY(8, BTC)), "btc.bos", "fdsf"));
// } FC_LOG_AND_RETHROW()



BOOST_AUTO_TEST_SUITE_END()

