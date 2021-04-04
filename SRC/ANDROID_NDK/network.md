# 安卓NDK network

## 源码:

- multinetwork.h



## 详情

### 定义枚举

#### ResNsendFlags

| 名称                            | 注释 |
| ------------------------------ | ---- |
| ANDROID_RESOLV_NO_RETRY        | 请求错误，不要重试 |
| ANDROID_RESOLV_NO_CACHE_STORE  | 不要缓存请求结果 |
| ANDROID_RESOLV_NO_CACHE_LOOKUP | 不要查找缓存中的请求 |



### 定义类型

| 名称                | 类型              | 注释               |
| ------------------- | ----------------- | ------------------ |
| net_handle_t        | Uint64_t          | 网络回调函数句柄id |
| NETWORK_UNSPECIFIED | ((net_handle_t)0) | 网络回调函数类型   |



### 定义全局函数

| 函数                                                         | 注释                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Int android_setsocketnetwork(net_handle_t network, int fd) __INTRODUCED_IN(23) | Api >= 23<br/>清空当前的其他绑定，重新绑定套接字到新的回调<br>network:回调id<br>fd:套接字 |
| Int android_setprocnetwork(net_handle_t network) __INTRODUCED_IN(23) | Api >= 23<br/>绑定当前进程;<br>network:                      |
| Int android_getaddrinfofornetwork(net_handle_t network, const char *node, const char *service, const struct Daddrinfo *hints, struct Daddrinfo **res) __INTRODUCED_IN(23) | Api >= 23<br/>域名解析,hints可为空,node和service二者有一个可为空,res非空<br>network:回调句柄<br>node:<br>service:<br>hints:<br>res: |
| int android_res_nquery(net_handle_t network, chonst char *dname, int ns_class, int ns_type, uint32_t flags) __INTRODUCED_IN(29) | Api >= 29<br/>资源域名解析,返回文件描述符;<br>network:回调句柄<br>danme:域名<br>ns_class:<br>ns_type:<br>flags:标记 |
| int android_res_nsend(net_handle_t network, const uint8_t *msg, size_t maglev, uint32_t flags) __INTRODUCED_IN(29) | Api >= 29;<br>提交查询;<br>network:网络句柄<br>msg:消息内容<br>msglen:消息长度<br>flags:标签 |
| Int android_res_nresult(int fd, int *rcode, uint8_t *answer, size_t anslen) __INTRODUCED_IN(29) | Api >= 29<br/>读取文件描述符的查询结果;<br>fd:文件描述符<br>rcode:<br>answer:<br>anslen: |
| Void android_res_cancel(int nsend_fd) __INTRODUCED_IN(29)    | Api >= 29<br>尝试取消查询任务;<br>nsend_fs:任务句柄          |

