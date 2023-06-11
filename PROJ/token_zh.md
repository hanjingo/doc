# Token机制

<!-- vim-markdown-toc GFM -->

    * [知识点](#知识点)
        - [同源策略](#同源策略)
        - [跨站请求伪造](#跨站请求伪造)
        - [无状态登录](#无状态登录)
        - [重放攻击](#重放攻击)
        - [对称加密](#对称加密)
        - [非对称加密](#非对称加密)
        - [不可逆加密](#不可逆加密)
        - [单点登录](#单点登录)
    * [作用](#作用)
    * [JWT](#jwt)
        - [结构](#结构)
        - [优缺点](#优缺点)
    * [Token续签](#token续签)
        - [服务端推迟token过期时间](#服务端推迟token过期时间)
        - [客户端主动刷新token](#客户端主动刷新token)
            + [缺点](#缺点)
    * [Token注销](#token注销)
+ [参考](#参考)

<!-- vim-markdown-toc -->



Token是一个用于身份认证的凭据；



## 知识点

### 同源策略

定义：两个URL的protocol, port和host都相同；

用途：1. 严格分离应用资源，防止恶意应用访问其它应用的敏感数据；

### 跨站请求伪造

跨站请求伪造（Cross-site request forgery），通常缩写为 CSRF 或者 XSRF；

### 无状态登录

服务端不保存任何客户端信息，客户端每次请求都必须自备描述信息，通过这些信息是被客户端身份；

### 重放攻击

TODO

### 对称加密

TODO

### 非对称加密

TODO

### 不可逆加密

TODO

### 单点登录

单点登录（Single sign-on, SSO），当用户登录时，就可以获取所有系统的访问权限，不用对每个单一系统都逐一登录；



## 作用

1. 用作身份验证时不需要暴露用户信息（账号，密码...），服务端也无需存储这些个人信息，减少服务器存储压力，同时更加安全；
2. token缓存在客户端，服务重启时，登陆状态不会失效；
3. 无状态登录便于服务的负载均衡和伸缩；
4. token自带的过期时间信息，可以让服务器有效地对token的生命周期进行管理；
5. 避开[同源策略](#同源策略)的限制；



## JWT

JWT(Json Web Token)，是为了在网络应用环境间传递声明而执行的一种基于JSON的开放标准（[**RFC 7519**](res/rfc7519.pdf))，JWT官网在[这里](https://jwt.io/)。

### 结构

JWT由3部分组成，他们之间用圆点`.`连接，其结构如下：

`header.playload.signature`

- `header` 头部（base64编码）

  包含以下两部分信息：

  - 类型(jwt, ...)
  - 加密算法(HMAC SHA256, ...)

- `playload` 载荷（有效数据部分，base64编码）

  包含以下信息：

  - 标准RFC7519中注册的声明（建议但不强制使用）

    | 条目 | 说明                                                         |
    | ---- | ------------------------------------------------------------ |
    | iss  | JWT签发者                                                    |
    | sub  | JWT所面向的用户                                              |
    | aud  | 接收JWT的一方                                                |
    | exp  | JWT的过期时间（此时间必须要大于签发时间）                    |
    | nbf  | 定义在什么时间之前，该JWT都是不可用的                        |
    | iat  | JWT签发时间                                                  |
    | jti  | JWT的唯一身份标识（主要用来作为一次性token，从而回避[重放攻击](#重放攻击)） |

  - 公共地声明

    可以添加任何的信息，一般添加用户的相关信息或其他业务需要的必要信息.但不建议添加敏感信息，因为该部分在客户端可解密.

  - 私有地声明

    提供者和消费者所共同定义的声明，一般不建议存放敏感信息

- `signature` 签名，用于验证整个JWT数据的完整性和可靠性

  服务端通过流程`HMACSHA256(base64(header) + . + base64(payload), secret)` 对前两部分加盐组合加密，来完成对token的签名；

  - `secret` 用来加密header和payload的私钥（保存在服务端，不允许客户端知悉，否则客户端就可以自我签名了）

### 优缺点

| 优点                                                         | 缺点                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1. 标准化：因为JSON的通用性，所以JWT可以进行跨语言支持；<br>2. 解耦：不需要在特定服务端保存会话信息，易于服务伸缩；<br>3. 支持跨域访问；<br/>4. 无状态； | 1. 如果在payload部分存放敏感信息可能会造成信息泄露；<br>2. 服务端需要消耗资源来维护secret私钥；<br>3. 无法注销token；<br>4. 带宽占用比session要大；<br>5. 对signature签名部分的加密会造成比较大的性能问题。 |



## Token续签

由于Token有时效性，如果用户在正常操作的过程中，Token过期失效了，此时的用户体验必然很差；有以下方法可以避免这类问题：

### 服务端推迟token过期时间

在token过期时间到来之前，自动刷新（推迟）Token的过期时间；如图所示：

```sequence
Title: 推迟token过期时间
客户端->服务端: 请求登录 [user, passwd]
服务端->服务端: 创建token
服务端-->客户端: [token]

客户端->服务端: 业务请求[data, token]
服务端->服务端: 认证token
服务端-->客户端: 请求成功

服务端->服务端: 等待过期时间
服务端->服务端: 修改逻辑代码的token的过期时间
```

### 客户端主动刷新token

一旦Token过期，客户端申请一个新的`token'`继续使用；如图所示：

```sequence
Title: 客户端主动刷新token
客户端->服务端: 请求登录 [user, passwd]
服务端-->客户端: 请提供token和refreshToken
客户端->服务端: [token, refreshToken]
服务端->服务端: 绑定token和refreshToken
服务端-->客户端: 登录成功

客户端->服务端: 业务请求[data, token]
服务端->服务端: 认证token
服务端-->客户端: 错误:token过期
客户端->服务端: 重新申请token[refreshToken]
服务端->服务端: 认证regreshToken
服务端->服务端: 生成新的token'
服务端->客户端: [token']
客户端->服务端: 业务请求(重发)[data, token']
服务端->服务端: 认证token'
服务端-->客户端: 请求成功
```

#### 缺点

1. refreshToken也过期了怎么办



## Token注销

对于Session方案来说，删除session意味着注销了授权；但是对于tokne方案，token一旦派发出去，除非他过期失效，否则会一直有效；对于这个问题，有以下几种办法处理：

1. 借助内存数据库存放token

   借助内存数据库存放token，如果需要让token失效，直接删除这个token即可。（此举违背了JWT的无状态原则）

2. 黑名单机制

   维护一个黑名单，如果需要让token失效，直接将这个token加入到黑名单，下次请求时判断在不在黑名单中。

3. 修改密钥（secret）

   每个用户都创建一个专属secret，如果需要让token失效，直接修改secret。（带来了2个问题：1. 如果是分布式服务，则每次修改secret都需要在节点间同步secret；2. 如果在多个终端登录了系统，从一个地方退出，其它地方都要重新进行登录）

4. 保持token的有效期短并经常轮换

   给token设置较短的有效期，可能会导致频繁生成token，造成性能问题。

# 参考

- [维基百科-同源策略](https://zh.wikipedia.org/wiki/%E5%90%8C%E6%BA%90%E7%AD%96%E7%95%A5)
- [维基百科-跨站请求伪造](https://zh.wikipedia.org/wiki/%E8%B7%A8%E7%AB%99%E8%AF%B7%E6%B1%82%E4%BC%AA%E9%80%A0)
- [维基百科-JSON Web Token](https://en.wikipedia.org/wiki/JSON_Web_Token)
- [维基百科-单点登录](https://zh.wikipedia.org/wiki/%E5%96%AE%E4%B8%80%E7%99%BB%E5%85%A5)
- [mozilla-同源策略](https://developer.mozilla.org/zh-CN/docs/Web/Security/Same-origin_policy)
- [深入理解token](https://www.cnblogs.com/xuxinstyle/p/9675541.html)
- [token的作用及实现原理](https://blog.csdn.net/qq_32784541/article/details/79655146)
- [Token的作用及原理](https://blog.csdn.net/qq_34803821/article/details/84980270?utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1.no_search_link)
- [什么是同源策略？](https://zhuanlan.zhihu.com/p/66047383)
- [Token无状态登录验证](https://www.jianshu.com/p/7c34b78f1675)
- [什么是有状态登录和无状态登录](https://www.pianshen.com/article/7383407604/)
- [什么是 JWT -- JSON WEB TOKEN](https://www.jianshu.com/p/576dbf44b2ae)

