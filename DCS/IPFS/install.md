# ipfs安装教程
## 参考
- [ipfs官网](https://docs.ipfs.io/install/command-line/#official-distributions)

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

### windows todo

## 运行
```shell
# 初始化
ipfs init

# 运行
ipfs daemon

# ipfs swarm peers
```

## 开机启动
```shell
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