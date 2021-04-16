# 第九章 POSIX Socket API 无连接的通信

## 将UDPServer方法添加到EchoServerActivity中

### 从Socket接受数据报: recvfrom
- `ssize_t recvfrom(int socketDescriptor, void* buffer, size_t bufferLength, int flags, struct sockaddr* address, socklen_t* addressLength)` 从UDP socket接受数据（阻塞）
    - socketDescriptor: socket描述符
    - buffer: 缓冲区
    - bufferLength: 缓冲区长度
    - flags: 标记
    - address: 发送方的地址
    - addressLength: 发送方地址长度
- `ssize_t sendto(int socketDescriptor, const void* buffer, size_t bufferSize, int flags, const struct sockaddr* address, socklen_t addressLength)`
    - socketDescriptor: 套接字描述符
    - buffer: 缓冲区
    - bufferSize: 缓冲区大小
    - flags: 标记
    - address: 接收方地址
    - addressLength: 接收方地址长度