# HTTP Protocol

[TOC]



## Message

### Request Message

![http_req_msg](res/http_req_msg.png)

For example:

```http
GET /hello.txt HTTP/1.1
User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3
Host: www.example.com
Accept-Language: en, mi
...
```

### Response Message

![http_resp_msg](res/http_resp_msg.png)

For example:

```http
HTTP/1.1 200 OK
Date: Mon, 27 Jul 2009 12:28:53 GMT
Server: Apache
Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
ETag: "34aa387-d-1568eb00"
Accept-Ranges: bytes
Content-Length: 51
Vary: Accept-Encoding
Content-Type: text/plain
...
```



## Cookie

Cookies allow sites to keep track of users. Cookie technology has four components:

1. a cookie header line in the HTTP response message;
2. a cookie header line in the HTTP request message;
3. a cookie file kept on the user's end system and managed by the user's browser;
4. a back-end database at the website.

For example:

![keep_state_with_cookie](res/keep_state_with_cookie.png)



## Disadvantage

Non-persistent connections have some shortcomings:

- First, a brand-new connection must be established and maintained for `each requested object`.
- Second, as we just described, each object suffers a delivery delay of two RTTs, one RTT to establish the TCP connection and one RTT to request and receive an object.



## Reference

[1] James F. Kurose, Keith W. Ross . Computer Networking: A Top-Down Approach . 6ED