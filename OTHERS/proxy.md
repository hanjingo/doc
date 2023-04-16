# 代理设置

[TOC]



## 在终端中使用/取消代理

设置代理：

```sh
# http
export http_proxy=http://127.0.0.1:7890
export https_proxy=http://127.0.0.1:7890

# socks
export http_proxy=socks5://127.0.0.1:7890
export http_proxy=socks5://127.0.0.1:7890
```

取消代理：

```sh
TODO
```



## Windows下设置/取消代理

新建环境变量：

| 环境变量    | 值                      |
| ----------- | ----------------------- |
| http_proxy  | socks5://127.0.0.1:7890 |
| https_proxy | socks5://127.0.0.1:7890 |



## 使用frp

### frps

1. 安装frps

   - `unix/linux`

     ```sh
     wget https://github.com/fatedier/frp/releases/download/v0.47.0/frp_0.47.0_linux_amd64.tar.gz
     tar -zxf frp_0.47.0_linux_amd64.tar.gz
     sudo cp -r frp_0.47.0_linux_amd64 /usr/local/bin/
     link /usr/local/bin/frp_0.47.0_linux_amd64/frps /usr/local/bin/frps
     ```

   - `windows` 略

2. 新建/修改配置文件，添加以下内容：

   ```ini
   bind_port = xx # frp服务器的对外端口
   subdomain_host = xx # 主机IP或域名(如：google.com)
   vhost_http_port = xx # http web端口
   vhost_https_port = xx # https web端口
   dashboard_port = xx # Web管理页面端口
   dashboard_user = xx # web管理页面登录名
   dashboard_pwd = xx # web管理页面登录密码
   log_file = /var/frp/frps.log # 日志输出路径
   token = xx # 连接的密码
   ```

3. 创建/修改开机启动配置文件，添加以下内容

   - `unix/linux`

     配置文件`/etc/systemd/system/frps.service`：

     ```txt
     [Unit]
     Description=Frp Server Service
     After=network.target
     
     [Service]
     Type=simple
     Restart=on-failure
     RestartSec=5s
     ExecStart=/usr/local/bin/frps -c /etc/frps.ini
     ExecReload=/usr/local/bin/frps reload -c /etc/frps.ini
     
     [Install]
     WantedBy=default.target
     ```

   - `macos`

     使用launchagent，具体略。

4. 设置开启启动

   - `unix/linux`

     ```sh
     systemctl enable frps.service
     systemctl restart frps
     ```


### frpc

1. 安装frpc

   - unix/linux

     ```sh
     wget https://github.com/fatedier/frp/releases/download/v0.47.0/frp_0.47.0_linux_amd64.tar.gz
     tar -zxf frp_0.47.0_linux_amd64.tar.gz
     sudo cp -r frp_0.47.0_linux_amd64 /usr/local/bin/
     link /usr/local/bin/frp_0.47.0_linux_amd64/frpc /usr/local/bin/frpc
     ```
     
   - macos

     ```sh
     wget https://github.com/fatedier/frp/releases/download/v0.47.0/frp_0.47.0_darwin_amd64.tar.gz
     tar -zxf frp_0.47.0_darwin_amd64.tar.gz
     sudo cp -r frp_0.47.0_darwin_amd64 /usr/local/bin/
     link /usr/local/bin/frp_0.47.0_darwin_amd64/frpc /usr/local/bin/frpc
     ```

   - windows

     略

2. 新建/修改配置文件，添加以下内容：

   ```ini
   [common]
   server_addr = x.x.x.x # frps服务器ip或域名
   server_port = xx # frps服务器端口
   privilege_token = xxx # 此处根据实际情况修改
   log_file = /var/log/frpc.log # 日志存放位置
   
   [xxx] # 主机名
   type = tcp # 联网方式
   local_ip = 127.0.0.1 # 本地IP
   local_port = 22 # 本地端口
   remote_port = xx # 远程服务器上的映射端口
   privilege_node = true
   ```

   - `unix/linux` 放到`/etc/frp/frpc.ini`。
   - `windows` 略

3. 创建/修改开机启动配置文件，添加以下内容

   - `unix/linux`

     配置文件`/etc/systemd/system/frpc.service`：

     ```txt
     [Unit]
     Description=Frp Client Service
     After=network.target
     
     [Service]
     Type=simple
     Restart=on-failure
     RestartSec=5s
     ExecStart=/usr/local/bin/frpc -c /etc/frpc.ini
     ExecReload=/usr/local/bin/frpc reload -c /etc/frpc.ini
     
     [Install]
     WantedBy=default.target
     ```

4. 设置开启启动

   - `unix/linux`

     ```sh
     systemctl enable frpc.service
     systemctl restart frpc
     ```

     

   
