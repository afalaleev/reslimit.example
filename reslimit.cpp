// Allow to edit tables from another contracts
#undef CHAINDB_ANOTHER_CONTRACT_PROTECT
#define CHAINDB_ANOTHER_CONTRACT_PROTECT(_CHECK, _MSG)

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/name.hpp>
#include <eosiolib/singleton.hpp>

using account_name = eosio::name;

class reslimit : public eosio::contract {

    using name = eosio::name;

    struct [[eosio::table]] resource_limit {

        int64_t id;
        account_name owner;
        bool pending = false;

        int64_t net_weight = -1;
        int64_t cpu_weight = -1;
        int64_t ram_bytes = -1;

        uint64_t primary_key() const { return id;  }
        uint64_t owner_key() const { return owner.value; }

    };

    using reslimits = eosio::multi_index<"reslimit"_n, resource_limit,
        eosio::indexed_by<"owner"_n, eosio::const_mem_fun<resource_limit, uint64_t, &resource_limit::owner_key>>>;

public:
    reslimit(name s, name code, eosio::datastream<const char*> ds)
    : eosio::contract(s, code, ds) {
    }

    [[eosio::action]]
    void show() {
        reslimits limits(name(0), scope_t(0));
        for (auto& r: limits) {
            eosio::print("Owner: ", r.owner, ", net: ", r.net_weight, ", cpu: ", r.cpu_weight, ", ram_bytes: ", r.ram_bytes, "\n");
        }
    }

    [[eosio::action]]
    void add(account_name owner) {
        reslimits limits(name(0), scope_t(0));
        limits.emplace(get_self(), [&] (resource_limit& limit) {
            limit.id = limits.available_primary_key();
            limit.owner = owner;
            limit.net_weight = 10;
            limit.cpu_weight = 10;
            limit.ram_bytes  = 1024;
        });
    }
};

EOSIO_DISPATCH(reslimit, (show)(add))
