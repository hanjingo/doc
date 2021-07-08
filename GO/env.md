# go环境配置



## 安装golang

```sh
wget https://golang.google.cn/dl/go1.16.5.linux-amd64.tar.gz
tar -zxvf go1.16.5.linux-amd64.tar.gz

sudo mv go /usr/local/
```



## 配置

```sh
echo -e '\nexport GOROOT=/usr/local/go \nexport GOPATH=$HOME/go \nexport GOBIN=$GOPATH/bin \nexport PATH=$GOPATH:$GOBIN:$GOROOT/BIN:$PATH' >> /etc/profile
```



## 启用

```sh
source /etc/profile && go env
```



## 配置国内代理

