## 装环境
```
sudo apt-get install -y make bzip2 automake libbz2-dev libssl-dev doxygen graphviz libgmp3-dev \
    autotools-dev libicu-dev python2.7 python2.7-dev python3 python3-dev \
    autoconf libtool curl zlib1g-dev sudo ruby libusb-1.0-0-dev \
    libcurl4-gnutls-dev pkg-config patch llvm-7-dev clang-7 vim-common jq
```

### 编译eos源码报错:gmp未安装
Could NOT find GMP (missing: GMP_LIBRARIES GMP_INCLUDE_DIR)

```
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

```
sudo apt-get install openssl
sudo apt-get install libssl-dev
```

### 编译eos源码报错:libcurl未安装
None of the required 'libcurl' found
```
sudo apt-get install libcurl4-openssl-dev
```