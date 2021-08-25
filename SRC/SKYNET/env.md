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

### master/slave模式

```sh
# 启动master
./skynet examples/config

# 启动slave
./skynet examples/config_log
```

### cluster模式

```sh
# 启动节点1
./skynet examples/config.c1
# 启动节点2
./skynet examples/config.c2
```



## 退出

目前skynet并没有提供合适的退出工具，需要服务自己实现监听事件退出；



## 参考

- [云风-如何安全的退出 skynet](https://blog.codingnow.com/2013/08/exit_skynet.html)

