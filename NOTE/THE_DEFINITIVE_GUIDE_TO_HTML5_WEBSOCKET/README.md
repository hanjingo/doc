# websocket权威指南
1. http是无状态的，并不适合有状态的场景

2. websocket api
> - 2-1. WebSocket(url, protocol) 
> > - url:地址 
> > - protocol:协议(1.注册协议 2.开放协议 3.自定义协议)
> - 2-2. open
> - 2-3. message
> - 2-4. error
> - 2-5. close
> - 2-6. send
> - 2-7. read

3. readyState
> - 3-1. CONNECTING:0 
> - 3-2. OPEN:1
> - 3-3. CLOSING:2
> - 3-4. CLOSED:3

4. bufferedAmount:缓冲区数据字节数

5. 握手
> - 5-1.websocket sec:
> > - Sec-WebSocket-Key:只能在HTTP请求中出现一次
            (用与从客户端到服务器的websocket初始握手,避免跨协议攻击)
> > - Sec-WebSocket-Accept:只能在HTTP请求中出现一次
            (用于从客户端到服务器的WebSocket初始握手,确认服务器理解WebSocket协议)
> > - Sec-WebSocket-Extensions:可能在HTTP请求中出现多次，在HTTP响应中只出现一次
            (用于从客户端到服务期的WebScoekt初始握手,然后用于从服务器到客户端的响应,
            这个首标帮助客户端和服务器约定一组连接期间使用的协议级扩展)
> > - Sec-WebSocket-Protocol:
            (用于从客户端到服务器的WebSocket初始握手，然后用于从服务器到客户端的响应.
            这个首标通告客户端应用程序可使用的协议.服务器使用相同的首标,在这些协议中的最多选择一个)
> > - Sec-WebSocket-Version:
            (用于从客户端到服务器的WebSocket初始握手,表示版本兼容性, RFC 6455的版本总是13.
            服务器如果不支持客户端请求的协议版本，则用这个首标响应.在那种情况下,
            服务器发送的首标中列出了它支持的版本.这只发生在RFC 6455之前的客户端中)
    5-2.websocket http 请求:
        相比普通的的http请求多了"Upgrade: websocket"选项

6. 帧
> - 6-1.帧头:
> > 操作码(1byte) + 长度(1byte:1bit是否屏蔽 + 7bit长度) + 扩展长度(0/2/8byte) + 
            屏蔽(4byte,仅客户端) + 数据
> - 6-2.操作码:
> > 类型:
> > - 1: 文本
> > - 2: 二进制
> > - 8: 关闭
> > - 9: ping
> > - 10:pong
> - 6-3.utf-8是websocket文本消息中允许的唯一编码
> - 6-4.websocket要求客户端屏蔽发送的所有帧,一般用4byte做屏蔽码

7. 关闭握手
> 关闭代码:
> > - 1000：正常关闭
> > - 1001：离开
> > - 1002：协议错误
> > - 1003：不可接受的数据类型
> > - 1004,1005,1006：保留
> > - 1007：无效数据
> > - 1008：消息违反政策
> > - 1009：消息过大
> > - 1010：需要扩展
> > - 1011：意外情况
> > - 1012：TLS失败(不要用这个代码)
> 关闭代码范围解释：
> > - 0~999：禁止使用当前范围的代码
> > - 1000~2999：保留
> > - 3000~3999：需要注册
> > - 4000~4999：私有