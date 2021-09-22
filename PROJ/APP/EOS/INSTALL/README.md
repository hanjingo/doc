# eos环境安装
## 装依赖包
```sh
sudo apt-get install -y make bzip2 automake libbz2-dev libssl-dev doxygen graphviz libgmp3-dev \
    autotools-dev libicu-dev python2.7 python2.7-dev python3 python3-dev \
    autoconf libtool curl zlib1g-dev sudo ruby libusb-1.0-0-dev \
    libcurl4-gnutls-dev pkg-config patch llvm-7-dev clang-7 vim-common jq
```
### 装clang-10
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
### 装cmake
```sh
wget https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.sh
sudo bash cmake-3.19.2-Linux-x86_64.sh --prefix=/usr/local --include-subdir --skip-license
CMAKE_DIR="/usr/local/cmake-3.19.2-Linux-x86_64"
export PATH=${CMAKE_DIR}/bin:$PATH
cmake --version
echo -e '\nCMAKE_DIR="/usr/local/cmake-3.19.2-Linux-x86_64"\nexport PATH=${CMAKE_DIR}/bin:$PATH' >> ~/.bashrc
```

### 装boost
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

### 拉取代码
```sh
mkdir -o ~/eos
git clone --recursive git@github.com:EOSIO/eos.git
git fetch --all
git submodule update --init --recursive
```

### 编译
```sh
EOS_DIR="/usr/local/eos"
sudo mkdir -p ${EOS_DIR}
echo -e '\nexport EOS_DIR="/usr/local/eos"\nexport PATH=${EOS_DIR}/bin:$PATH' >> ~/.bashrc
mkdir -p ~/eos/build
rm -rf ~/eos/build/*
cd ~/eos/build
BOOST_ROOT="${BOOST_ROOT}" cmake \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_CXX_COMPILER="clang++" \
    -DCMAKE_C_COMPILER="clang" \
    -DLLVM_DIR="/usr/lib/llvm-10/lib/cmake/llvm" \
    -DCMAKE_INSTALL_PREFIX="${EOS_DIR}" \
    ..
make -j $(nproc) && sudo make install

BOOST_ROOT="${BOOST_ROOT}" cmake \
    -DCMAKE_BUILD_TYPE="Release" \
    -DCMAKE_CXX_COMPILER="clang++" \
    -DCMAKE_C_COMPILER="clang" \
    -DLLVM_DIR="/usr/lib/llvm-10/lib/cmake/llvm" \
    -DCMAKE_INSTALL_PREFIX="${BAOZI_DIR}" \
    ..

```

## 报错处理

### 编译eos源码报错:gmp未安装
Could NOT find GMP (missing: GMP_LIBRARIES GMP_INCLUDE_DIR)

```sh
wget https://gmplib.org/download/gmp/gmp-6.2.0.tar.lz
tar -xjvf gmp-6.2.0.tar.lz
cd gmp-6.2.0.tar.lz
./configure
make
sudo make install
```

### 编译eos源码报错:openssl未安装
Could NOT find OpenSSL, try to set the path to OpenSSL root folder in the
  system variable OPENSSL_ROOT_DIR (missing: OPENSSL_CRYPTO_LIBRARY
  OPENSSL_INCLUDE_DIR)

```sh
sudo apt-get install openssl
sudo apt-get install libssl-dev
```

### 编译eos源码报错:libcurl未安装
None of the required 'libcurl' found
```sh
sudo apt-get install libcurl4-openssl-dev
```