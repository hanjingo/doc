# 代理设置



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



## Windows下设置代理

新建环境变量：

| 环境变量    | 值                      |
| ----------- | ----------------------- |
| http_proxy  | socks5://127.0.0.1:7890 |
| https_proxy | socks5://127.0.0.1:7890 |

