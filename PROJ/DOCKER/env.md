# Docker环境搭建

[TOC]

## 版本选择

| 平台    | 版本                                                         | 备注   |
| ------- | ------------------------------------------------------------ | ------ |
| Windows | + [Docker Community Edition 18.06.1-ce](https://download.docker.com/win/stable/19507/Docker%20for%20Windows%20Installer.exe) | + 推荐 |
| Macos   | + [Docker Community Edition 18.06.1-ce](https://download.docker.com/mac/stable/26764/Docker.dmg) | + 推荐 |
| Linux   |                                                              |        |



## 镜像选择

| 镜像 | 备注 |
| ---- | ---- |
|      |      |



## Linux

TODO



## Macos

TODO



## Windows

### 安装

**注意：如果需要使用WSL2运行Docker，请升级win10到v1903 及以上版本**

#### win10

1. 前往官方下载[DockerForWindows](https://docs.docker.com/desktop/windows/release-notes/)并安装；
2. 开启Hyper-V虚拟机；

   - 设置-->应用-->程序和功能-->启用或关闭Windows功能-->勾选“适用于Linux的Windows子系统”和“虚拟机平台”；

   - 打开任务管理器-->选择性能栏-->看看“Hyper-V支持”是否为“是”；

   - 右击"Windows开始“按钮，打开”Windows PowerShell（管理员）“控制台，输入`bcdedit /set hypervisorlaunchtype auto`；
   - 重启系统
3. 检测是否安装成功；
   - 右击"Windows开始“按钮，打开”Windows PowerShell（管理员）“控制台，输入`docker run hello-world`，看看是否安装成功；
2. 拉取官方镜像/导入个人镜像；

#### win7,win8

1. 前往阿里云下载[DockerToolbox-18.03.0-ce.exe](http://mirrors.aliyun.com/docker-toolbox/windows/docker-toolbox/DockerToolbox-18.03.0-ce.exe)并安装（用默认配置即可）；
2. 开启Hyper-V虚拟机；
3. 

### 运行

#### win10

- 在wsl2运行Docker

  TODO

- 点击运行Docker

  1. 直接在菜单栏中点击`Docker Desktop`开始运行；

#### win7,win8

### 使用镜像

1. 配置镜像加速器；

   由于墙的问题，国内从 Docker Hub 拉取镜像有时会遇到困难，可以配置镜像加速器绕过这个问题；

   - [网易云](https://sf.163.com/help/documents/56918246390157312)
   - [百度云](https://cloud.baidu.com/doc/CCE/s/Yjxppt74z#%E4%BD%BF%E7%94%A8dockerhub%E5%8A%A0%E9%80%9F%E5%99%A8)

2. 拉取镜像

   ```sh
   docker pull
   ```



## 参考

- [Docker官网](https://docs.docker.com/)
- [Docker--从入门到实践](https://yeasy.gitbook.io/docker_practice/)
- [【docker系列4】docker版本及内核兼容性选择](https://www.cnblogs.com/yoyoma0355/p/14503758.html)
- [镜像加速器](https://yeasy.gitbook.io/docker_practice/install/mirror)
- [Windows Docker 安装](https://www.runoob.com/docker/windows-docker-install.html)