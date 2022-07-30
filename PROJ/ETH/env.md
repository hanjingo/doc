# 以太坊环境搭建

[TOC]



## Linux编译安装

### 安装Node.js

1. 下载node.js源码

   ```sh
   git clone git@github.com:nodejs/node.git
   sudo chmod -R 755 node
   cd node 
   git submodule update --recursive --init
   ```

2. 创建编译环境

   ```sh
   sudo ./configure
   ```

3. 编译安装

   ```sh
   sudo make
   sudo make install
   ```

4. 验证

   ```sh
   node -v
   ```

### 安装节点仿真器

1. npm安装`ganache-cli`

   ```sh
   npm install -g ganache-cli
   ```

2. 验证

   ```sh
   ganache-cli
   ```

### 安装solidity编译器

1. npm安装solc

   ```sh
   npm install -g solc
   ```

2. 验证

   ```sh
   solcjs -version
   ```

### 安装truffle

1. npm安装truffle

   ```sh
   npm install -g truffle
   ```

2. 验证

   ```sh
   truffle.cmd version
   ```

### 安装ETH

1. 下载以太坊源码

   ```sh
   git clone git@github.com:ethereum/go-ethereum.git
   cd go-ethereum 
   git submodule update --recursive --init
   ```

2. 构建对象

   - 单独构建geth工具

     ```sh
     make geth
     ```

   - 构建所有的工具

     ```sh
     make all
     ```

3. 测试

   ```sh
   geth console
   ```

   

## 参考

[1] [Github/go-ethereum](https://github.com/hanjingo/go-ethereum)

[2] [以太坊开发环境搭建](https://www.jianshu.com/p/5a569bbf1468)

[3] [Solidity](https://www.osgeo.cn/solidity/index.html)
