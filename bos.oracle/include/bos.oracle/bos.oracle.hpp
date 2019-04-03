/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;
   using eosio::public_key;

   class [[eosio::contract("bos.oracle")]] oracle : public contract {
      public:
         using contract::contract;

         [[eosio::action]]
         void hi();

      private:
         enum data_service_fee_type: uint8_t {
            FEE_COUNT = 0,
            FEE_MONTH = 1
         };
        
         enum data_service_data_type: uint8_t {
            DATA_DETERMINISTIC     = 0,
            DATA_NON_DETERMINISTIC = 1
         };

         enum data_service_injection_method: uint8_t {
            CHAIN_DIRECT   = 0,
            CHAIN_INDIRECT = 1,
            OUTSIDE_CHAIN  = 2
         };

         enum arbitrator_status: uint8_t {
            STOPED   = 0,
            SERVING  = 1
         };

         struct [[eosio::table]] data_service {
            uint64_t          service_id;
            uint8_t           fee_type;
            uint8_t           data_type;
            uint8_t           status;
            uint8_t           injection_method;
            uint64_t          acceptance;
            time_point_sec    duration;
            uint64_t          provider_limit;
            uint64_t          update_cycle;
            time_point_sec    update_start_time;
            uint64_t          appeal_freeze_period;
            uint64_t          exceeded_risk_control_freeze_period;
            uint64_t          guarantee_id;
            asset             service_price;
            asset             stake_amount;
            asset             risk_control_amount;
            asset             pause_service_stake_amount;
            bool              freeze_flag;
            bool              emergency flag;
            std::string       data_format;
            std::string       criteria;
            std::string       declaration;

            uint64_t primary_key() const { return service_id; }
         };
         
         struct [[eosio::table]] data_service_fee {
            uint64_t          id;
            uint64_t          service_id;
            asset             service_price;
            uint8_t           fee_type;

            uint64_t primary_key() const { return id; }
         };

         struct [[eosio::table]] data_user {
            name                  account;
            public_key            pubkey;
            uint8_t               status;
            time_point_sec        create_time;

            uint64_t primary_key() const { return account.value; }
         };

         struct [[eosio::table]] data_provider {
            name                  account;
            public_key            pubkey;
            asset                 total_stake_amount;
            asset                 unconfirmed_amount;

            uint64_t primary_key() const { return account.value; }
         };

         struct [[eosio::table]] data_service_provision {
            uint64_t              service_id;
            name                  account;
            public_key            pubkey;
            asset                 stake_amount;
            asset                 service_income;
            std::string           public_information;
            bool                  stop_service;

            uint64_t primary_key() const { return service_id; }
         };

         struct [[eosio::table]] data_service_usage {
            uint64_t              service_id;
            name                  contract_account;
            name                  action_name;
            asset                 payment;
            asset                 consumption;

            uint64_t primary_key() const { return service_id; }
         };

         struct [[eosio::table]] svc_provision_cancel_apply {
            uint64_t              apply_id;
            uint64_t              service_id;
            name                  provider;
            uint64_t              status;
            time_point_sec        cancel_time;
            time_point_sec        finish_time;

            uint64_t primary_key() const { return apply_id; }
         };

         struct [[eosio::table]] data_service_request {
            uint64_t              request_id;
            uint64_t              service_id;
            signature             request_sig;
            
            time_point_sec        request_time;
            std::string           request_content;

            uint64_t primary_key() const { return request_id; }
         };

         struct [[eosio::table]] data_service_provision_log {
            uint64_t              service_id;
            uint64_t              update_number;
            uint64_t              status;
            std::string           data_json;
            signature             provider_sig;
            time_point_sec        update_time;

            uint64_t primary_key() const { return service_id; }
         };

         struct [[eosio::table]] data_service_usage_record {
            uint64_t              usage_id;
            uint64_t              update_number;
            signature             user_sig;
            uint64_t              request_id;
            time_point_sec        usage_time;

            uint64_t primary_key() const { return usage_id; }
         };

         struct [[eosio::table]]  complainant {
            uint64_t              appeal_id;
            uint64_t              service_id;
            uint64_t              status;
            uint64_t              arbitration_method;
            bool                  is_sponsor;
            name                  appellant;
            time_point_sec        appeal_time;
            std::string           reason;
            
            uint64_t primary_key() const { return appeal_id; }
         };

         struct [[eosio::table]]  arbitrator {
            name                  account;
            public_key            pubkey;
            uint8_t               type;
            uint8_t               status;
            uint64_t              correct_rate;
            uint64_t              invitations;
            uint64_t              responses;
            asset                 stake_amount;
            std::string           public_info;
            bool                  is_malicious;
            
            uint64_t primary_key() const { return account.value; }
         };

         struct [[eosio::table]]  arbitration_case_application {
            uint64_t              arbitration_id;
            uint64_t              service_id;
            uint64_t              update_number;
            uint64_t              arbitration_step;
            uint64_t              final_results;
            std::string           evidence_info;
            
            uint64_t primary_key() const { return arbitration_id; }
         };

         struct [[eosio::table]]  arbitration_process {
            uint64_t              process_id;
            uint64_t              arbitration_id;
            uint64_t              num_id;
            std::vector<name>     applicants;
            std::vector<name>     responders;
            std::vector<name>     arbitrators;
            asset                 stake_amount;
            std::string           arbitrator_arbitration_results;
            uint64_t              arbitration_results;
            uint64_t              arbitration_method;

            uint64_t primary_key() const { return process_id; }
         };

         struct [[eosio::table]]  arbitration_result {
            uint64_t              result_id;
            uint64_t              arbitrator_id;
            uint64_t              arbitration_id;
            uint64_t              arbitrator_arbitration_result;
            uint64_t              process_id;
            
            uint64_t primary_key() const { return result_id; }
         };

         struct [[eosio::table]]  fair_award {
            uint64_t              service_id;
            uint64_t              arbitration_id;
            std::string           arbitrator_evidence;
            
            uint64_t primary_key() const { return service_id; }
         };

         struct [[eosio::table]]  transfer_freeze {
            uint64_t              freeze_id;
            uint64_t              service_id;
            time_point_sec        start_time;
            time_point_sec        freezing_duration;
            asset                 freeze_amount;
            uint64_t              status;
            
            uint64_t primary_key() const { return freeze_id; }
         };

         // TODO: transfer_delay

         typedef eosio::multi_index< "dataservices"_n, data_service > data_services;
         typedef eosio::multi_index< "datausers"_n, data_user > data_users;
         typedef eosio::multi_index< "servicefees"_n, data_service_fee > data_service_fees;
         typedef eosio::multi_index< "dataprovides"_n, data_provider > data_providers;
         typedef eosio::multi_index< "datasvcprovs"_n, data_service_provision > data_service_provisions;
         typedef eosio::multi_index< "datasvcusage"_n, data_service_usage > data_service_usages;
         typedef eosio::multi_index< "cancelappys"_n, svc_provision_cancel_apply > svc_provision_cancel_applys;
         typedef eosio::multi_index< "svcrequest"_n, data_service_request > data_service_requests;
         typedef eosio::multi_index< "svcprovilogs"_n, data_service_provision_log > data_service_provision_logs;
         typedef eosio::multi_index< "usagerecords"_n, data_service_usage_record > data_service_usage_records;
         typedef eosio::multi_index< "complainants"_n, complainant > complainants;
         typedef eosio::multi_index< "arbitrators"_n, arbitrator > arbitrators;
         typedef eosio::multi_index< "arbicaseapp"_n, arbitrator > arbitration_case_applications;
         typedef eosio::multi_index< "arbiprocess"_n, arbitration_process > arbitration_processs;
         typedef eosio::multi_index< "arbiresults"_n, arbitration_result > arbitration_results;
         typedef eosio::multi_index< "fairawards"_n, fair_award > fair_awards;
         typedef eosio::multi_index< "tffreezes"_n, transfer_freeze > transfer_freezes;
   };

} /// namespace eosio
