# skynet环境搭建



## 依赖库

```sh
sudo apt-get install build-essential libssl-dev libcurl4-gnutls-dev libexpat1-dev gettext unzip autoconf libreadline-dev
```



## 编译

```sh
# 拉取项目
git clone https://github.com/cloudwu/skynet.git
```

### linux

```sh
# 编译
cd skynet && sudo make linux
```



## 运行

### 单点

```sh
# 运行服务端
./skynet examples/config

# 运行客户端
./3rd/lua/lua examples/client.lua
```

### 集群

TODO

