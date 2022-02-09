# FFmpeg安装教程

## 命令行安装



---

### linux平台

- 安装第三方库

  ```sh
  sudo apt-get update -qq && sudo apt-get -y install \
  >   autoconf \
  >   automake \
  >   build-essential \
  >   cmake \
  >   git-core \
  >   libass-dev \
  >   libfreetype6-dev \
  >   libsdl2-dev \
  >   libtool \
  >   libva-dev \
  >   libvdpau-dev \
  >   libvorbis-dev \
  >   libxcb1-dev \
  >   libxcb-shm0-dev \
  >   libxcb-xfixes0-dev \
  >   pkg-config \
  >   texinfo \
  >   wget \
  >   zlib1g-dev
  ```

- 安装yasm和nasm

  ```sh
  sudo apt-get install nasm
  sudo apt-get install yasm
  ```

  

- 安装libx264,libx265和libnuma

  ```sh
  sudo apt-get install libx264-dev -y
  sudo apt-get install libx265-dev libnuma-dev -y
  ```

- 安装vpx

  ```sh
  sudo apt-get install libvpx-dev -y
  ```

- 安装libfdk-aac

  ```sh
  sudo apt-get install libfdk-aac-dev -y
  ```

- 安装libmp3lame

  ```sh
  sudo apt-get install libmp3lame-dev -y
  ```

- 安装libopus

  ```sh
  sudo apt-get install libopus-dev -y
  ```

- 编译

  ```sh
  ./configure
  make
  make install
  ```

  