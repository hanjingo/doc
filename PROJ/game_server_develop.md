# 游戏服务器开发

[TOC]

## 术语

- Application Server 应用服务器
- Cache Server 缓存服务器
- Chat Server 聊天服务器
- Client 客户端
- DB Server 数据服务器
- Game Server 游戏服务器
- Gate Server 网关服务器
- Scene Server 场景服务器
- Login Server 登录服务器
- Match Server 匹配服务器
- Room Server 房间服务器
- Web Server 网页服务器
- World Server 世界服务器



## 1总体架构

### 1.1房间类游戏

```mermaid
graph LR
Client1 --> LoginServer --> MatchServer --> DBServer
LoginServer --> ChatServer --> DBServer
Client2 --> RoomServer --> DBServer
```

### 1.2弱交互游戏

```mermaid
graph LR

Client --HTTP/HTTPS--> WebServer --> ApplicationServer --> CacheServer
ApplicationServer --> DBServer
```

### 1.3简单的分区分服游戏

```mermaid
graph LR
Client1 --socket--> GameServer1
Client2 --socket--> GameServer2
Client3 --socket--> GameServer3
```

### 1.4数据共享游戏服务器

```mermaid
graph LR
Client --socket--> GateServer --> GameServer --> DBServer
GateServer --> LoginServer
LoginServer --> GameServer
GameServer --> WorldServer --> DBServer
GameServer --> ChatServer --> DBServer
GameServer --> ScenceServer --> DBServer
LoginServer --> DBServer
```



## 2登录系统

### 2.1认证与授权

- `认证(Authentication)` 用于鉴别访问者是否为合法用户；
- `授权(Authorisation)` 用于决定访问者有访问哪些资源的权限；

### 2.2单点登录

单点登录（Single sign-on, SSO），当用户登录时，就可以获取所有系统的访问权限，不用对每个单一系统都逐一登录；

SSO有以下2种协议：

1. SAML 2.0
2. OAuth 2.0

#### 2.2.1SAML 2.0

SAML 2.0时序图如下：

```sequence
Title:SAML 2.0
Client->Resource Server/SP: 用户获取资源
Note right of Resource Server/SP: >>> 生成认证请求
Resource Server/SP->Authorization Server/IdP: 认证请求
Authorization Server/IdP-->Client: 通知客户端提供账号和密码用于认证
Client->Authorization Server/IdP: [user, passwd]
Note left of Authorization Server/IdP: 生成 SAML token <<<
Authorization Server/IdP-->Resource Server/SP: [SAML token]
Note right of Resource Server/SP: >>> 解析[SAML token]
```

- `Authorization Server/Identity Provider` (IdP)负责认证的服务
- `Resource Server/Service Provider` (SP)负责提供资源（API调用）的服务器

1. 尚未登录的客户端访问SP；
2. SP向IdP发送了一个SAML认证请求；
3. IdP验证SAML请求，验证成功，通知客户端提供账号和密码到IdP进行登录；
4. 用户提供账号和密码进行登录；
5. 登录成功，IdP根据用户名和密码生成SAML token；
6. IdP将SAML token发送给SP；
7. SP解析SAML token，得到账号，密码，权限...等信息。

#### 2.2.2OAuth 2.0

OAuth（开放授权）是一个开放标准，允许用户授权第三方移动应用访问他们存储在另外的服务提供者上的信息，而不需要将用户名和密码提供给第三方移动应用或分享他们数据的所有内容，OAuth2.0是OAuth协议的延续版本，但不向后兼容OAuth 1.0即完全废止了OAuth1.0。

OAuth 2.0的认证流程如下：

```sequence
Title:SAML 2.0
Client->Resource Server/SP: Authorization Request
Resource Server/SP-->Client: Authorization Grant

Client->Authorization Server/IdP: Authorization Grant
Note left of Authorization Server/IdP: Generated Access Token <<<
Authorization Server/IdP-->Client: Access Token

Client->Resource Server/SP: Access Token
Resource Server/SP-->Client: Protected Resource
```

- `Authorization Server/Identity Provider` (IdP)负责授权的服务
- `Resource Server/Service Provider` (SP)负责提供资源（API调用）的服务器

1. Client访问SP；
2. SP引导Client重定向到IdP；
3. Client同意给与SP授权；
4. IdP生成一个Access Token，并返回给Client；
5. Client使用Access Token访问资源；
6. SP返回资源。



## 3存储系统

TODO



## 4帧同步机制

TODO



## 5热更新机制

### 5.1作用

1. 上线需求（审核）
2. 快节奏的版本迭代
3. 节约网络资源

### 5.2Lua方案

TODO

### 5.3动态链接库方案

TODO

### 5.4RPC

TODO



## 6断线重连

TODO



## 7日志系统

TODO



## 8全球同服

### 8.1难点

- 网络延迟

  需要解决因为网路传输的延迟造成不同国家的玩家公平性问题，以及由于延迟造成不同国家的客户体验不一致的问题，同时由于国际网络运营商(ISP)之间的互通性问题；

- 数据读写

  需要保持不同地区的数据一致性；

- 资源管理

  如何统一，高效的进行游戏运维与资源管理；

### 8.2设计方案

TODO

### 8.3游戏加速

TODO



## 参考

- [云风-LoginServer](https://github.com/cloudwu/skynet/wiki/LoginServer)
- [云风-MsgServer](https://github.com/cloudwu/skynet/wiki/MsgServer)
- [游戏服务器架构设计](https://www.cnblogs.com/panchanggui/p/9841768.html)
- [游戏服务器的常用架构](https://blog.csdn.net/u011308294/article/details/78627540)
- [不要用JWT替代session管理（上）：全面了解Token,JWT,OAuth,SAML,SSO](https://zhuanlan.zhihu.com/p/38942172)
- [Oauth2详解-介绍(一)](https://www.jianshu.com/p/84a4b4a1e833)
- [理解OAuth2](https://zhuanlan.zhihu.com/p/84670338)
- [游戏开发中的ECS架构实用性如何？](https://www.zhihu.com/question/455479955/answer/2143570061)
- [阿里云-全球同服手游解决方案](https://help.aliyun.com/document_detail/63554.html?utm_content=g_1000230851&spm=5176.20966629.toubu.3.f2991ddcpxxvD1#title-gv4-rr3-pf2)
- [网络游戏-断线重连](https://blog.csdn.net/qq_28098067/article/details/86712592)
- [MMORPG游戏开发入门（转）](https://www.cnblogs.com/faeriesoft/p/4156070.html)
- [MMORPG大型游戏设计与开发（构架](https://blog.csdn.net/erlib/article/details/40949227)
- [MMORPG大型游戏设计与开发（服务器 游戏场景 地图和区域）](https://www.shuzhiduo.com/A/gVdnej85Wl/)
- [MMORPG大型游戏设计与开发（服务器 AI 概述）](https://www.shuzhiduo.com/A/x9J2N9gJ6o/)

