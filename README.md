Example of usage:

- Create user `cyber.limit`:
./cleos create account eosio cyber.limit GLS8HJjXzAy6Kg3JJPZ6CWgvABgeucdRHD1kWuckZsXGn7FVQMRvK

- Set code to `cyber.limit`:
./cleos set contract cyber.limit ./reslimit --abi reslimit.abi

- Show records from system table with resource limits:
./cleos push action cyber.limit show '[]' -p eosio

- Add object to resource limits:
./cleos push action cyber.limit add '[hero]' -p eosio

- Show records from system table with resource limits:
./cleos push action cyber.limit show '[]' -p eosio

