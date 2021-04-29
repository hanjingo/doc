# 环境配置



## ubuntu18.04

### 依赖包
```sh
sudo apt-get install -y make bzip2 automake libbz2-dev libssl-dev doxygen graphviz libgmp3-dev \
    autotools-dev libicu-dev python2.7 python2.7-dev python3 python3-dev \
    autoconf libtool curl zlib1g-dev sudo ruby libusb-1.0-0-dev \
    libcurl4-gnutls-dev pkg-config patch llvm-7-dev clang-7 vim-common jq
```



### clang

#### clang10

```sh
# 安装clang10
sudo apt-get install clang-10 libclang-10-dev llvm-10-dev libc++-10-dev libc++abi-10-dev clang-tidy clang-tidy-10
# 注册版本，优先级是100
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-10 100 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-10
# 检查版本号是否正确
clang --version
clang++ --version
update-alternatives --display clang 
# 如果其它版本的优先级更高，可以手工切换版本： sudo update-alternatives --config clang
```
#### clang11

```sh
# 修改/etc/apt/sources.list添加源
deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-11 main
deb-src http://apt.llvm.org/bionic/ llvm-toolchain-bionic-11 main
# 更新源
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
sudo apt-get update
sudo apt-get upgrade
# 安装clang11
sudo apt-get install clang-11 libclang-11-dev llvm-11-dev libc++-11-dev libc++abi-11-dev clang-tidy clang-tidy-11
# 注册版本，优先级是110
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-11 110 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-11
# 检查版本号是否正确
clang --version
clang++ --version
update-alternatives --display clang 
# 如果其它版本的优先级更高，可以手工切换版本： sudo update-alternatives --config clang
```



### cmake

#### cmake-3.19.2

```sh
wget https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.sh
sudo bash cmake-3.19.2-Linux-x86_64.sh --prefix=/usr/local --include-subdir --skip-license
CMAKE_DIR="/usr/local/cmake-3.19.2-Linux-x86_64"
export PATH=${CMAKE_DIR}/bin:$PATH
cmake --version
echo -e '\nCMAKE_DIR="/usr/local/cmake-3.19.2-Linux-x86_64"\nexport PATH=${CMAKE_DIR}/bin:$PATH' >> ~/.bashrc
```



### boost

#### boost_1_75_0

```sh
export BOOST_ROOT="/usr/local/boost-1.75"
echo -e '\nexport BOOST_ROOT="/usr/local/boost-1.75"' >> ~/.bashrc
sudo mkdir -p ${BOOST_ROOT}
mkdir -p ~/tmp
cd ~/tmp
wget -c https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
tar -xjf boost_1_75_0.tar.bz2
cd boost_1_75_0
./bootstrap.sh --with-toolset=clang --prefix=${BOOST_ROOT} 
sudo ./b2 toolset=clang --without-graph_parallel --without-mpi -q -j $(nproc) install
```