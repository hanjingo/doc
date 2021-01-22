# skynet buffer
## 源码
skynet_buffer.h

## 详情
buffer一共定义了3个类型：
    内存 buffer
    对象 buffer
    rawpoint buffer

buffer主要用于socket发送做缓冲区
在：lua-socket.c, service_harbor.c, skynet_socket.c, socket_server.c中有用到;