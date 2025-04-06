# 持续集成与交付

[TOC]



## Jekins

### 安装

需要准备一台带公网IP或带内网穿透功能（推荐frp）的服务器。

- ubuntu

  1. 安装jenkins

     ```sh
     wget -q -O - https://pkg.jenkins.io/debian/jenkins-ci.org.key | sudo apt-key add -
     echo deb http://pkg.jenkins.io/debian-stable binary/ | sudo tee /etc/apt/sources.list.d/jenkins.list
     sudo apt-get update
     sudo apt-get install jenkins
     ```

  2. 修改配置

     修改配置文件`/etc/default/jenkins`，修改以下内容：

     ```sh
     NAME=xxx
     HTTP_PORT=xxx
     ```
  
  3. 启动服务
  
     ```sh
     sudo systemctl restart jenkins
     sudo systemctl status jenkins
     ```
  
  4. 后台管理
  
     用浏览器打开jenkins地址：`http://x.x.x.x:xxxx`，根据页面提示找到密码登录。
  
     安装推荐的插件。
  
     创建管理员用户。

### 集成Git

1. 生成github的token。

   进入github --> Settings --> Developer settings --> Personal access tokens -> Generate new token。

   **注意：token只显示一次，注意保存!**

2. 关联github项目

   进入项目-->Settings-->Webhooks-->Add webhook-->



## 参考

- [Jenkins 搭建C++持续集成环境](https://blog.csdn.net/u011304970/article/details/74026147)
- [ubuntu系统安装jenkins并与github实现自动发布功能](https://segmentfault.com/a/1190000023085628)

