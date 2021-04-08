# lotus安装手册



## 参考

- [Lotus: install and setup](https://docs.filecoin.io/get-started/lotus/installation/#minimal-requirements)



## 最小硬件要求

| 条目     | 要求                                                         |
| -------- | ------------------------------------------------------------ |
| 操作系统 | macos/linux, windows不支持                                   |
| cpu      | 8核cpu，如果支持sha算法,性能会有明显的提升<br>- AMD: Zen microarchitecture及以后的版本<br>- Intel: Ice Lake及以后的版本 |
| 内存     | 32G                                                          |
| 硬盘     | 最好上SSD的硬盘，区块链每周增涨大约12G的数据，为了磁盘空间足够，一年至少需要$$12*4*12=576$$G的空间 |



## 安装

### 安装依赖

#### macos

- 系统依赖

- Rust 

- Go

#### linux

- 系统依赖

  - ubuntu

    ```sh
    sudo apt install mesa-opencl-icd ocl-icd-opencl-dev gcc git bzr jq pkg-config curl clang build-essential hwloc libhwloc-dev wget -y && sudo apt upgrade -y
    ```

- Rust 

  ```sh
  curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
  source $HOME/.cargo/env
  rustup update
  rustc --version
  ```

- Go

  略

### (中国用户专供)

由于伟大的防火墙，需要设置下代理

```sh
export IPFS_GATEWAY=https://proof-parameters.s3.cn-south-1.jdcloud-oss.com/ipfs/

export RUSTUP_DIST_SERVER=https://mirrors.ustc.edu.cn/rust-static

export RUSTUP_UPDATE_ROOT=https://mirrors.ustc.edu.cn/rust-static/rustup

go env -w GOPROXY=https://goproxy.cn,direct
```



## 构建&安装

#### 拉取git

```sh
git clone https://github.com/filecoin-project/lotus.git
cd lotus/
go mod tidy
```

#### 切换版本

```sh
git checkout v1.6.0
```

#### 设置环境变量

开启SHA扩展

- 新机器(**AMD Zen 或 Intel Ice Lake 以后的CPU**)

```sh
export RUSTFLAGS="-C target-cpu=native -g"
export FFI_BUILD_FROM_SOURCE=1
```

- 老机器执行上面的命令可能会报错，试试下面的:

```sh
export CGO_CFLAGS_ALLOW="-D__BLST_PORTABLE__"
export CGO_CFLAGS="-D__BLST_PORTABLE__"
```

#### 编译

```sh
make clean all
```

以下是报错处理方法:

报错

```sh
failed to fetch `https://github.com/rust-lang/crates.io-index`
```

解决方法: 设置crates.io国内代理

`vi ~/.cargo/config`写入以下内容

```ini
[source.crates-io]
registry = "https://github.com/rust-lang/crates.io-index"
replace-with = 'ustc'
[source.ustc]
registry = "git://mirrors.ustc.edu.cn/crates.io-index"
```



#### 安装

```sh
sudo make install
```

### 安装到系统服务

#### 安装daemon到系统

```sh
sudo make install-daemon-service
```

#### 安装miner到系统

```sh
sudo make install-miner-service
```



## 运行

#### 开启lotus进程

```sh
lotus daemon
```

此时日志放在 `~/.lotus` 目录下

记住一些有用的命令:

- lotus --help: 帮助
- lotus client --help: 帮助
- lotus net peers: 检查当前连接的节点数量

### 开机启动

```sh
# 设置开机启动
sudo systemctl enable lotus-daemon

# 开启服务
sudo systemctl start lotus-daemon

# 查看进程
sudo systemctl status lotus-daemon
```





## 停止

如果遇到特殊原因，需要停止lotus，使用以下命令

```sh
lotus daemon stop
```

或

```sh
sudo systemctl stop lotus-daemon
```

