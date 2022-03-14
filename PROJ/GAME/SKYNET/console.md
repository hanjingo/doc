# skynet控制台

控制台是skynet提供的一个控制和调试的工具；



## 启用

使用控制台之前，需要启动相关服务，在函数`skynet.start`中添加语句`skynet.newservice("debug_console", ip, port)`，即可启动控制台服务；

skynet启动后，用telnet或nc命令就可以进入控制台发送控制命令；



## 命令

| 命令       | 说明                                                         | 示例                                                         |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| help       |                                                              |                                                              |
| list       | 列出所有服务，以及启动服务的命令参数                         | 格式：`list`<br>- `list` 列出所有服务                        |
| stat       | 列出所有lua服务的信息，包括：<br>- `mqlen` 消息队列的长度<br>- `task` 被挂起的请求数量<br>- `message` 处理的消息总数<br>- `cpu` CPU时间(需要config的profile设置为true) | 格式：`stat`<br>- `stat` 列出所有lua服务的信息               |
| info       | 让一个lua服务汇报自己的内部信息                              | 格式：`info 服务地址/ID`<br>- `info 0` 汇报服务0的内部信息   |
| exit       | 退出一个lua服务                                              | 格式：`exit 服务地址/ID`<br>- `exit 0` 退出id为0的服务       |
| kill       | 强行终止一个lua服务                                          | 格式：`kill 服务地址/ID`<br>- `kill 0` 强行终止id为0的服务   |
| mem        | 让所有lua服务汇报自己占用的内存                              | 格式：`mem`<br>- `mem` 列出所有服务站用的内存                |
| gc         | 强制让所有lua服务都执行一次垃圾回收，并报告回收后的内存      |                                                              |
| start      | 用`skynet.newservice`启动一个新的lua服务                     | 格式：`start 服务名`<br>-`start hot` 启动一个新的服务，服务名为hot |
| snax       | 用`snax.newservice` 启动一个新的snax服务                     | 格式：`snax 服务名`<br>- `snax hot`                          |
| clearcache | 清理缓存                                                     |                                                              |
| service    | 列出所有唯一的lua服务，并显示出请求还不存在的服务被挂起的请求 |                                                              |
| task       | 显示一个服务所有被挂起的请求的调用栈                         |                                                              |
| uniqtask   |                                                              |                                                              |
| inject     | 注入代码                                                     | 格式：`inject 服务地址/ID lua文件地址`<br>- `inject 4 ./emamples/hot.lua` 将hot.lua代码注入到服务ID为4的服务 |
| logon      | 记录一个服务所有的输入消息到文件（需要在config中配置logpath） |                                                              |
| logoff     | 关闭输入信息保存功能                                         |                                                              |
| log        |                                                              |                                                              |
| debug      | 正对一个lua服务启动内置的单步调试器                          |                                                              |
| signal     | 向服务发送一个信号，信号值如下：<br>- 0 （默认）当一个服务陷入死循环时，打断正在执行的lua字节码，并抛出error<br>- ... | 格式：`signal 服务地址/ID 信号值`<br>- `signal 0 0`          |
| cmem       |                                                              |                                                              |
| jmem       |                                                              |                                                              |
| ping       |                                                              |                                                              |
| call       | 调用一个服务的lua类型接口                                    | 格式：`call 服务地址/ID "函数" 函数参数...`<br>- `call 8  "hello",1 调用ID=8的服务的函数hello，并传入参数1 |
| trace      |                                                              |                                                              |
| netstat    | 列出网络连接的概况                                           |                                                              |
| profactive |                                                              |                                                              |
| dumpheap   |                                                              |                                                              |
| killtask   |                                                              |                                                              |
| dbgcmd     |                                                              |                                                              |



## 注册服务

TODO



## 查看服务

TODO



## 源码

- `service/debug_console.lua`



## 参考

- [DebugConsole](https://github.com/cloudwu/skynet/wiki/DebugConsole)
- [在线调试 Lua 代码](https://blog.codingnow.com/2015/02/skynet_debugger.html)

