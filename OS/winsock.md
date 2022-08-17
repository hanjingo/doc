# Window网络编程

[TOC]



## API

### WSAStartup

TODO

加载winsock DLL。

### socket

TODO

### inet_pton

TODO

### connect

TODO

### bind

TODO

### listen

TODO

### accept

TODO

### closesocket

TODO



## 示例

- client.cpp

  ```c++
  #include <winsock2.h>
  #include <WS2tcpip.h>
  #include <iostream>
  #include <stdlib.h>
  
  // 链接WS2_32
  #pragma comment(lib, "ws2_32.lib")
  
  #define BUFSIZE 4096 // 缓冲区大小
  
  int main(int argc, char *argv[])
  {
  	WSADATA wsd;
  	SOCKET sock;
  	char buf[BUFSIZE];
  	int ret;
  	struct sockaddr_in serv_addr;
  	unsigned short port;
  	struct hostent *host = NULL;
  
  	// 加载指定版本的dll
  	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
  		std::cout << "初始化失败!!!" << std::endl;
  		return 1;
  	}
  
  	// 创建socket
  	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  	if (sock == INVALID_SOCKET) {
  		std::cout << "创建socket失败" << std::endl;
  		return 1;
  	}
  
  	// 指定服务器地址
  	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(10086);
  	inet_pton(AF_INET, "localhost", (void*)&serv_addr.sin_addr.S_un.S_addr);
  	//serv_addr.sin_addr.s_addr = inet_addr("localhost"); // inet_addr已废弃
  
  	// 与服务器建立连接
  	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
  		std::cout << "connect()失败" << std::endl;
  		return 1;
  	}
  
  	// 收发消息
  	for (;;) {
  		gets_s(buf);
  		// 向服务器发送消息
  		ret = send(sock, buf, strlen(buf), 0);
  		if (ret == 0)
  			break;
  		else if (ret == SOCKET_ERROR) {
  			std::cout << "send()失败" << std::endl;
  		}
  		buf[ret] = '\0';
  		std::cout << "recv :" << ret << " bytes:" << buf;
  	}
  
  	// 关闭socket，释放资源
  	closesocket(sock);
  	WSACleanup();
  	system("pause");
  
      return 0;
  }
  ```

- serv.cpp

  ```c++
  #include <winsock2.h>
  #include <WS2tcpip.h>
  #include <iostream>
  #include <stdlib.h>
  
  #pragma comment(lib, "ws2_32.lib")
  
  #define DEFAULT_BUFFER 4096 // 缓冲区大小
  
  // 与客户机通信的线程函数
  DWORD WINAPI ClientThread(LPVOID lpParam)
  {
  	SOCKET sock = (SOCKET)lpParam;
  	char buf[DEFAULT_BUFFER];
  	int ret, nleft, idx;
  	while (true) {
  		// 接收消息
  		ret = recv(sock, buf, DEFAULT_BUFFER, 0);
  		if (ret == 0)
  			break;
  		else if (ret == SOCKET_ERROR) {
  			std::cout << "recv() 失败：" << WSAGetLastError();
  			break;
  		}
  		buf[ret] = '\0';
  		std::cout << "recv: " << buf; // 打印消息
  
  		nleft = ret;
  		idx = 0;
  		while (nleft > 0) {
  			// 发送回应消息
  			ret = send(sock, &buf[idx], nleft, 0);
  			if (ret == 0)
  				break;
  			else if (ret == SOCKET_ERROR) {
  				std::cout << "send() 失败：" << WSAGetLastError();
  				break;
  			}
  			nleft -= ret;
  			idx += ret;
  		}
  	}
  	return 0;
  }
  
  int main()
  {
  	WSADATA wsd;
  	HANDLE hThread;
  	DWORD dwThread;
  	SOCKET sListen, sClient;
  	int AddrSize;
  	unsigned short port;
  	struct sockaddr_in local, client;
  
  	// 加载winsock dll
  	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
  		std::cout << "winsock 初始化失败" << std::endl;
  		return 1;
  	}
  
  	// 创建socket
  	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  	if (sListen == SOCKET_ERROR) {
  		std::cout << "socket() 失败:" << WSAGetLastError();
  		return 1;
  	}
  	local.sin_family = AF_INET;
  	local.sin_addr.s_addr = htonl(INADDR_ANY);
  	port = 10086;
  	local.sin_port = htons(port);
  
  	// 绑定socket
  	if (bind(sListen,
  		(struct sockaddr*)&local,
  		sizeof(local)) == SOCKET_ERROR) {
  		std::cout << "bind() 失败:" << WSAGetLastError();
  		return 1;
  	}
  	// 打开监听
  	listen(sListen, 0);
  
  	// 监听端口，创建线程
  	while (true) {
  		AddrSize = sizeof(client);
  		// 监听是否有连接请求
  		sClient = accept(sListen, (struct sockaddr*)&client, &AddrSize);
  		if (sClient == INVALID_SOCKET) {
  			std::cout << "accept() 失败：" << WSAGetLastError();
  			break;
  		}
  		// 创建线程
  		hThread = CreateThread(NULL, 0, ClientThread, (LPVOID)sClient, 0, &dwThread);
  		if (hThread == NULL) {
  			std::cout << "CreateThread() 失败：" << GetLastError();
  			break;
  		}
  		// 处理完后关闭
  		CloseHandle(hThread);
  	}
  	closesocket(sListen);
  	WSACleanup();
  
  	system("pause");
  
      return 0;
  }
  ```



## 参考

[1] [美].Anthony Jones, Jim Ohlund . windows网络编程 . 2ED

[2] [windows下的socket网络编程](https://www.cnblogs.com/oloroso/p/4613296.html)