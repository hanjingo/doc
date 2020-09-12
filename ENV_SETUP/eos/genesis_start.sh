#!/bin/bash
DATADIR="."
LOG_DIR="./logs"

if [ ! -d $DATADIR/logs ]; then
    mkdir -p $DATADIR/logs;
fi

nodeos \
--genesis-json $"./genesis.json" \
--signature-provider EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV=KEY:5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 \
--plugin eosio::producer_plugin \
--plugin eosio::producer_api_plugin \
--plugin eosio::chain_plugin \
--plugin eosio::chain_api_plugin \
--plugin eosio::http_plugin \
--plugin eosio::history_api_plugin \
--plugin eosio::history_plugin \
--data-dir ${DATADIR}"/data" \
--blocks-dir ${DATADIR}"/blocks" \
--config-dir ${DATADIR}"/config" \
--producer-name eosio \
--http-server-address 127.0.0.1:8888 \
--p2p-listen-endpoint 127.0.0.1:9010 \
--access-control-allow-origin=* \
--contracts-console \
--http-validate-host=false \
--verbose-http-errors \
--enable-stale-production \
--http-max-response-time=1000 \
--max-transaction-time=1000 \
--delete-all-blocks \ #此处建议注释掉，如非必要不建议使用
> ${LOG_DIR}"/genesis."`date +%Y%m%d-%H%M%S`".log" 2>&1 & \
echo $! > ${DATADIR}"/eosd.pid"
