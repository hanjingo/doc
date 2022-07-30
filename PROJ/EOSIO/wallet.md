# EOS钱包

[TOC]

## 前提

钱包的自动锁定时间缺省为900秒

```shell
grep -n -B 1 unlock-timeout ~/eosio-wallet/config.ini
```

改为864000秒
```shell
echo -e "\nunlock-timeout = 864000" >> ~/eosio-wallet/config.ini
```

