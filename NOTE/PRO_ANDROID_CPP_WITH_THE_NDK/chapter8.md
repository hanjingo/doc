# 第八章 POSIX Socket API 面向连接的通信



## Echo_Socket示例应用

### 抽象echo_activity

```java
// AbstractEchoActivity.java
package com.apress.echo;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;

// 抽象echo activity对象
public abstract class AbstractEchoActivity extends Activity implements OnClickListener {
  // 端口号
  protected EditText portEdit;
  // 服务按钮
  protected Button startButton;
  // 日志滚动
  protected ScrollView logScroll;
  // 日志视图
  protected TextView logView;
  // 布局ID
  private final int layoutID;
  // 构造函数
  public AbstractEchoActivity(int layoutID) {
    this.layoutID = layoutID;
  }
  
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(layoutID);
    
    portEdit = (EditText) findViewById(R.id.port_edit);
    startButton = (Button) findViewById(R.id.start_button);
    logScroll = (ScrollView) findViewById(R.id.log_scroll);
    logView = (TextView) findViewById(R.id.log_view);
    
    startButton.setOnClickListener(this);
  }
  
  public void onClick(View view) {
    if (view == startButton) {
      onStartButtonClicked();
    }
  }
  
  // 在开始按钮上单击
  protected abstract void onStartButtonClicked();
  
  // 以整型获取端口号
  protected Integer getPort() {
    Integer port;
    
    try {
      port = Integer.valueOf(portEdit.getText().toString());
    } catch (NumberFormatException e) {
      port = null;
    }
    
    return port;
  }
  
  // 记录给定的消息
  protected void logMessage(final String message) {
    runOnUiThread(new Runnable() {
      public void run() {
        logMessageDirect(message);
      }
    });
  }
  
  // 直接记录给定的消息
  protected void logMessageDirect(final String message) {
    logView.append(message);
    logView.append("\n");
    logScroll.fullScroll(View.FOCUS_DOWN);
  }
  
  // 抽象异步echo任务
  protected abstract class AbstractEchoTask extends Threads {
    // Handler对象
    private final Handler handler;
    // 构造函数
    public AbstractEchoTask() {
      handler = new Handler();
    }
    // 在调用线程中先执行回调
    protected void onPreExecute() {
      startButton.setEnabled(false);
      logView.setText("");
    }
    
    public synchronized void start() {
      onPreExecute();
      super.start();
    }
    
    public void run() {
      onBackground();
      handler.post(new Runnable() {
        public void run() {
          onPostExecute();
        }
      });
    }
    
    // 新线程中的背景回调
    protected abstract void onBackground();
    
    // 在调用线程中后执行回调
    protected void onPostExecute() {
      startButton.setEnabled(true);
    }
  }
  
  static {
    System.loadLibrary("Echo");
  }
}
```

### 原生echo模块

```c++
// Echo.cpp
#include <jni.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stddef.h>

#include "com_apress_echo_EchoServerActivity.h"

// 最大日志消息长度
#define MAX_LOG_MESSAGE_LENGTH 256
// 最大数据缓冲区大小
#define MAX_BUFFER_SIZE 80

// 将给定的消息记录到应用程序
static void LogMessage(
	JNIEnv* env,
	jobject obj,
	const char* format,
	...)
{
  // 缓存日志方法ID
  static jemthodID methodID = NULL;
  // 如果方法ID未缓存
  if (NULL == methodID)
  {
    // 从对象获取类
    jclass clazz = env->GetObjectClass(obj);
    // 从给定方法获取方法ID
    methodID = env->GetMethodID(clazz, "logMessage",
    	"(Ljava/lang/String;)V");
    // 释放类引用
    env->DeleteLocalRef(clazz);
  }
  // 如果找到方法
  if (NULL != methodID)
  {
    // 格式化日志消息
    char buffer[MAX_LOG_MESSAGE_LENGTH];
    
    
    va_list ap;
    va_start(ap, format);
    vsnprintf(buffer, MAX_LOG_MESSAGE_LENGTH, format, ap);
    va_end(ap);
    
    // 将缓冲区转换为Java字符串
    jstring message = env->NewStringUTF(buffer);
    // 如果字符串构造正确
    if (NULL != message)
    {
      // 记录消息
      env->CallVoidMethod(obj, methodID, message);
      // 释放消息引用
      env->DeleteLocalRef(message);
    }
  }
}

// 用给定的异常类和异常消息抛出新的异常
static void ThrowException(
	JNIEnv* env,
	const char* className,
	const char* message)
{
  // 获取异常类
  jclass clazz = env->FindClass(className);
  // 如果异常未找到
  if (NULL != clazz)
  {
    // 抛出异常
    env->ThrowNew(clazz, message);
    // 释放原生类引用
    env->DeleteLocalRef(clazz);
  }
}

// 用给定异常类和基于错误号的错误消息抛出新异常
static void ThrowErrnoException(
	JNIEnv* env,
	const char* className,
	int errnum)
{
  char buffer[MAX_LOG_MESSAGE_LENGTH];
  // 获取错误号消息
  if (-1 == strerror_r(errnum, buffer, MAX_LOG_MESSAGE_LENGTH))
  {
    strerror_r(errno, buffer, MAX_LOG_MESSAGE_LENGTH);
  }
  // 抛出异常
  ThrowException(env, className, buffer);
}

// 构造新的TCP socket
static int NewTcpSocket(JNIEnv* env, jobject obj)
{
  // 构造socket
  LogMessage(env, obj, "Constructing a new TCP socket...");
  int tcpSocket = socket(PF_INET, SOCKET_STREAM, 0);
  
  // 检查socket构造是否正确
  if (-1 == tcpSocket)
  {
    // 抛出带错误号的异常
    ThrowErrnoException(env, "java/io/IOException", errno);
  }
  return tcpSocket;
}

// 将socket绑定到端口
static void BindSocketToPort(
	JNIEnv* env,
	jobject obj,
	int sd,
	unsigned short port)
{
  struct sockaddr_in address;
  
  // 绑定socket的地址
  memset(&address, 0, sizeof(address));
  address.sin_family = PF_INET;
  
  // 绑定到所有地址
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  
  // 将端口转换成网络字节顺序
  address.sin_port = htons(port);
  
  // 绑定socket
  LogMessage(env, obj, "Binding to port %hu.", port);
  if (-1 == bind(sd, (struct sockaddr*) &address, sizeof(address)))
  {
    // 抛出带错误号的异常
    ThrowErrnoException(env, "java/io/IOException", errno);
  }
}

// 获取当前绑定的端口号socket
static unsigned short GetSocketPort(
	JNIEnv* env,
	jobject obj,
	int sd)
{
  unsigned short port = 0;
  struct sockaddr_in address;
  socklen_t addressLength = sizeof(address);
  
  // 获取socket地址
  if (-1 == getsockname(sd, (struct sockaddr*) &address,
                        &addressLength)) 
  {
    // 抛出带错误号的异常
    ThrowErrnoException(env, "java/io/IOException", errno);
  }
  else
  {
    // 将端口转换为主机字节顺序
    port = ntohs(address.sin_port);
    LogMessage(env, obj, "Binded to random port %hu.", port);
  }
  return port;
}

// 监听指定的待处理连接的backlog的socket，当backlog已满时拒绝新的连接
static void ListenOnSocket(
	JNIEnv* env,
	jobject obj,
	int sd,
	int backlog)
{
  // 监听给定backlog的socket
  LogMessage(env, obj, 
  	"Listening on socket with a backlog of %d pending connections.", backlog);
  if (-1 == Listen(sd, backlog))
  {
    // 抛出带错误号的异常
    ThrowErrnoException(env, "java/io/IOException", errno);
  }
}

// 记录给定地址的IP地址和端口号
static void LogAddress(
	JNIEnv* env,
	jobject obj,
	const char* message,
	const struct sockaddr_in* address)
{
  char ip[INET_ADDRSTRLEN];
  // 将IP地址转换为字符串
  if (NULL == inet_ntop(PF_INET, &(address->sin_addr), ip, INET_ADDRSTRLEN))
  {
    // 抛出带错误号的异常
    ThrowErrnoException(env, "java/io/IOException", errno);
  }
  else
  {
    // 将端口转换为主机字节序顺序
    unsigned short port = ntohs(address->sin_port);
    // 记录地址
    LogMessage(env, obj, "%s %s:%hu.", message, ip, port);
  }
}

// 在给定的socket上阻塞和等待进来的客户连接
static int AcceptOnSocket(
	JNIEnv* env,
	jobject obj,
	int sd)
{
  struct sockaddr_in address;
  socklen_t addressLength = sizeof(address);
  // 阻塞和等待进来的客户，连接且接受
  LogMessage(env, obj, "Waiting for a client connection...");
  int clientSocket = accept(sd, (struct sockaddr*)&address, &addressLength);
  // 如果客户socket无效
  if (-1 == clientSocket)
  {
    // 抛出带错误号的异常
    ThrowErrnoException(env, "java/io/IOException", errno);
  }
  else
  {
    // 记录地址
    LogAddress(env, obj, "Client connection from ", &address);
  }
  return clientSocket;
}

// 阻塞并接受来自socket的数据放到缓冲区
static ssize_t ReceiveFromSocket(
	JNIEnv* env,
	jobject obj,
	int sd,
	char* buffer,
	size_t bufferSize)
{
  // 阻塞并接受来自socket的数据放到缓冲区
  LogMessage(env, obj, "Receiving from the socket...");
  ssize_t recvSize = recv(sd, buffer, bufferSize - 1, 0);
  
  // 如果接收失败
  if (-1 == recvSize)
  {
    // 抛出带错误号的异常
    ThrowErrnoException(env, "java/io/IOException", errno);
  }
  else
  {
    // 以NULL结尾缓冲区形成一个字符串
    buffer[recvSize] = NULL;
    
    // 如果数据接收成功
    if (recvSize > 0)
    {
      LogMessage(env, obj, "Received %d bytes: %s", recvSize, buffer);
    }
    else
    {
      LogMessage(env, obj, "Client disconnected.");
    }
  }
  return recvSize;
}

// 将数据缓冲区发送到socket
static ssize_t SendToSocket(
	JNIEnv* env,
	jobject obj,
	int sd,
	const char* buffer,
	size_t bufferSize)
{
  // 将数据缓冲区发送到socket
  LogMessage(env, obj, "Sending to the socket...");
  ssize_t sentSize = send(sd, buffer, bufferSize, 0);
  
  // 如果发送失败
  if (-1 == sentSize)
  {
    // 抛出带错误号的异常
    ThrowErrnoException(env, "java/io/IOException", errno);
  }
  else
  {
    if (sentSize > 0)
    {
      LogMessage(env, obj, "Sent %d bytes: %s", sentSize, buffer);
    }
    else
    {
      LogMessage(env, obj, "Client disconnected.");
    }
  }
  return sentSize;
}

void Java_com_apress_echo_EchoServerActivity_nativeStartTcpServer(
	JNIEnv* env,
	jobject obj,
	jint port)
{
  // 构造新的TCP socket
  int serverSocket = NewTcpSocket(env, obj);
  if (NULL == env->ExceptionOccurred())
  {
    // 将socket绑定到某端口号
    BindSocketToPort(env, obj, serverSocket, (unsigned short) port);
    if (NULL != env->ExceptionOccurred())
      goto exit;
  	// 如果请求了随机端口号
  	if (0 == port)
  	{
    	// 获取当前绑定的端口号socket
    	GetSocketPort(env, obj, serverSocket);
    	if (NULL != env->ExceptionOccurred())
      	goto exit;
  	}
  
  	// 监听有4个等待连接的backlog的socket
  	ListenOnSocket(env, obj, serverSocket, 4);
  	if (NULL != env->ExceptionOccurred())
    	goto exit;
  
  	// 接收socket的一个客户连接
  	int clientSocket = AcceptOnSocket(env, obj, serverSocket);
  	if (NULL != env->ExceptionOccurred())
    	goto exit;
  
  	char buffer[MAX_BUFFER_SIZE];
  	ssize_t recvSize;
  	ssize_t sentSize;
  
  	// 接收并发送回数据
  	while (1)
  	{
    	// 从socket中接收
    	recvSize = ReceiveFromSocket(env, obj, clientSocket, 
                                 	 buffer, MAX_BUFFER_SIZE);
    	if ((0 == recvSize) || (NULL != env->ExceptionOccurred()))
      	break;
    
    	// 发送给socket
    	sentSize = SendToSocket(env, obj, clientSocket,
                            	buffer, (size_t) recvSize);
    	if ((0 == sentSize) || (NULL != env->ExceptionOccurred()))
      	break;
  	}
  	// 关闭客户端socket
  	close(clientSocket);
	}
exit:
  if (serverSocket > 0)
  {
    close(serverSocket);
  }
}
```



## 用TCP_sockets实现面向连接的通信

### Echo_Server_Activity

```java
// EchoServerActivity.java
package com.apress.echo;

public class EchoServerActivity extends AbstractEchoActivity {
  // 构造函数
  public EchoServerActivity() {
    super(R.layout.activity_echo_server);
  }
  
  protected void onStartButtonClicked() {
    Integer port = getPort();
    if (port != null) {
      ServerTask serverTask = new ServerTask(port);
      serverTask.start();
    }
  }
  
  // 根据给定端口启动TCP服务器
  private native void nativeStartTcpServer(int port) throws Exception;
  
  // 根据给定端口启动UDP服务
  private native void nativeStartUdpServer(int port) throws Exception;

  // 服务器端任务
  private class ServerTask extends AbstractEchoTask {
	// 端口号
	private final int port;
	// 构造函数
	public ServerTask(int port) {
		this.port = port;
	}

	protected void onBackground() {
		logMessage("Starting server.");

		try {
			nativeStartTcpServer(port);
		} catch(Exception e) {
			logMessage(e.getMessage());
		}

		logMessage("Server terminated.");
	}
  }
}
```

### 实现原生TCP_Server

- `int socket(int domain, int type, int protocol)` 创建新的socket

  - domain: 指定socket域
    - PF_LOCAL: 主机内部通信协议族，该协议族使物理上运行在同一台设备上的应用程序可以用Socket API彼此通信。
    - PF_INET: Internet第四版协议族，该协议族使应用程序可以与网络上其他地方运行的应用程序进行通信。

  - type: 指定通信的语义
    - SOCK_STREAM: 提供使用TCP协议的，面向连接的通信Stream socket类型
    - SOCK_DGRAM: 提供使用UDP协议的，无连接的通信Datagram socket类型

  - ptorocol: 指定协议
- `int bind(int socketDescriptor, const struct sockaddr* address, socklen_t addressLength)` 绑定socket与地址
  
  - socketDescriptor: socket描述符
  
  - address: 协议地址
  
    不同的协议族使用不同的地址。PF_INET使用以下地址结构:
  
    ```c
    struct sockaddr_in {
      sa_family_t 				sin_family;
      unsigned short int 	sin_port;
      struct in_addr 			sin_addr;
    }
    ```
  
  - addressLength: 协议地址长度

网络字节排序:

1. Big-endian:  大端

   使用大端的有:

   - java
   - MIPS机器
   - ...

2. Little-endian: 小端

   使用小端的有:

   - ARM机器
   - x86机器
   - ...

头文件`sys/endian.h`提供了以下函数进行字节序转换:

- htons: 将unsigned short从主机字节排序转换到网络字节排序
- ntohs: 和htons函数相反，将unsigned short从网络字节排序转换到主机字节排序
- htonl: 将unsigned integer从主机字节排序转换到网络字节排序
- ntohl: 和htonl函数相反，将unsigned integer从网络字节排序转换到主机字节排序



- `int listen(int socketDescriptor, int backlog)` 监听socket
  - socketDescriptor: socket描述符
  - backlog: 连接请求队列最大值，超过此值的新入连接会被拒绝。

- `int accpet(int socketDescriptor, struct sockaddr* address, socklen_t* addressLength)` 显式地将输入连接从监听队列里取出并接受（阻塞）
  - socket descriptor: 指定应用程序想要从其上接受输入连接的socket实例
  - address pointer: 提供一个地址结构，在该结构中填入被连接的客户协议地址。如果应用程序不需要该信息，他可以被设置为NULL
  - address length pointer: 为要填入的连接客户协议地址提供指定大小的内存空间。如果不需要该信息，它可以被设置为NULL

- `ssize_t recv(int socketDescriptor, void* buffer, size_t bufferLength, int flags)` 接收数据（阻塞）
  - socketDescriptor: socket描述符
  - buffer: 缓冲区，用来存放接收到的数据
  - bufferLength: 缓冲区长度，指定接收到数据的长度
  - flags: 额外标记

- `ssize_t send(int socketDescriptor, void* buffer, size_t bufferLength, int flags)` 发送数据（阻塞）
  - socketDescriptor: socket描述符
  - buffer: 缓冲区
  - bufferLength: 缓冲区长度
  - flags: 标记

### Echo客户端Activity

```java
// EchoClientActivity.java
package com.apress.echo;
import android.os.Bundle;
import android.widget.EditText;

// 客户端
public class EchoClientActivity extends AbstractEchoActivity {
  
}
```

