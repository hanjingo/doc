# ipfs安装教程



## 安装
### linux
```shell
# 下载
wget https://dist.ipfs.io/go-ipfs/v0.7.0/go-ipfs_v0.7.0_linux-amd64.tar.gz

# 解压
tar -xvzf go-ipfs_v0.7.0_linux-amd64.tar.gz

# 执行命令
cd go-ipfs
sudo bash install.sh

# 确认下
ipfs --version
```

### macos
```shell
# 下载
wget https://dist.ipfs.io/go-ipfs/v0.7.0/go-ipfs_v0.7.0_darwin-amd64.tar.gz

# 解压
tar -xvzf go-ipfs_v0.7.0_darwin-amd64.tar.gz

# 执行命令
cd go-ipfs
bash install.sh

# 检查
ipfs --version
```

### windows

todo



## 运行
```shell
# 初始化
ipfs init

# 运行
ipfs daemon

# ipfs swarm peers
```



## 开机启动
```sh
# 创建ipfs.service文件并放入 /etc/systemd/system
vim /etc/systemd/system/ipfs.service
# ipfs.service内容
[Unit]
Description=InterPlanetary File System (IPFS) daemon
After=network.target

[Service]
Environment=IPFS_PATH=这里填.ipfs文件夹地址
Type=notify
StateDirectory=ipfs
ExecStart=/usr/local/bin/ipfs daemon --init --migrate
Restart=on-failure
KillSignal=SIGINT

[Install]
WantedBy=default.target
```



## 搭建私有网络

### 生成swarm.key

下载ipfs的swarm.key生成工具

```sh
git clone git@github.com:hanjingo/go-ipfs-swarm-key-gen.git
```

编译swarm.key生成工具

```sh
go build -o swarm-key-gen main.go
```

生成一个swarm-key

```sh
./swarm-key-gen > ${PWD}/swarm.key
```

## 初始化ipfs

初始化ipfs

```sh
ipfs init
# 对于内存小于4G的设备，用以下命令
ipfs init --profile=lowpower
```

删除默认的启动节点

```sh
ipfs bootstrap rm --all
```

添加我们自己的节点

```sh
ipfs bootstrap add "/ip4/ip地址/tcp/4001/ipfs/root节点id"
# 例
ipfs bootstrap add "/ip4/139.198.126.182/tcp/4001/ipfs/12D3KooWHbWEFVVmf7ca3PNxq9bNisXMugExLTLd1HgRCFmyJHqk"
```

将生成的swarm.key放入ipfs的目录中

```sh
cp swarm.key ~/.ipfs/
```

启动ipfs

```sh
ipfs daemon
```



## 参考
- [ipfs官网](https://docs.ipfs.io/install/command-line/#official-distributions)

