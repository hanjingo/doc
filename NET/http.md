English | [中文版](http_zh.md)

# HTTP Protocol

[TOC]



`HyperText Transfer Protocol (HTTP)` is an application-layer protocol for distributed, collaborative, hypermedia information systems.

## URI

Resources requested over HTTP or HTTPS are identified by a Uniform Resource Identifier (URI).

A Uniform Resource Locator (URL) is a specific type of URI used to locate a resource.

### Format

Standard format:

`[scheme]://[host]:[port]/[path/to/resource][filename]?[query]#[fragment]`

Full format (with credentials):

`[scheme]://[user:password]@[host]:[port]/[path/to/resource][filename]?[query]#[fragment]`

Example:

`http://joe:passwd@www.joes-hardware.com:443/tools.html;type=d?item=123#drills`

- `http`: scheme
- `joe:passwd`: credentials (username `joe`, password `passwd`)
- `www.joes-hardware.com`: host
- `443`: port (common HTTPS port; `80` for HTTP, `8080` often used for proxies)
- `tools.html`: path/filename
- `;type=d`: parameter
- `?item=123`: query
- `#drills`: fragment inside `tools.html`

### URL forms

URLs can be absolute (full) or relative (partial). Relative URLs must be resolved against a base URL.

#### Relative URL resolution

![http_url_parse](res/http_url_parse.png)

This diagram shows converting a relative URL to an absolute URL.

### Differences: URI / URL / URN

- URI: a unique identifier for a resource.
- URL: a URI that also specifies how to locate the resource.
- URN: a persistent, location-independent resource name.



## HTTP Messages

### Request Message

```http
<method> <request-URL> <version>
<headers>

<entity-body>
```

- Request line

  - `method`: action the client wants the server to perform

    | Method  | HTTP Version | Has Body | Description |
    | ------- | ------------ | -------- | ----------- |
    | GET     | 1.0          | No       | Retrieve the specified resource; response includes entity body |
    | HEAD    | 1.0          | No       | Same as GET but returns only headers (no body) |
    | POST    | 1.0          | Yes      | Submit data to the resource; may create or modify resources |
    | PUT     | 1.1          | Yes      | Replace the target resource with the request payload |
    | DELETE  | 1.1          | No       | Delete the specified resource |
    | CONNECT | 1.1          |          | Reserved for proxy servers that can convert the connection to a tunnel |
    | OPTIONS | 1.1          | No       | Describe communication options for the target resource |
    | TRACE   | 1.1          | No       | Echo the received request for diagnostic purposes |
    | PATCH   | 1.1          |          | Partially modify a resource (complements PUT) |

  - `request-URL`: the requested resource path
  - `version`: HTTP version in the form `HTTP/<major>.<minor>`

- Headers: see the "Headers" section below
- Entity-body: optional request payload

Example request:

```http
GET /hello.txt HTTP/1.1
User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3
Host: www.example.com
Accept-Language: en, mi
...
```


### Response Message

```http
<version> <status> <reason-phrase>
<headers>

<entity-body>
```

- Status line

  - `version`: HTTP version, `HTTP/<major>.<minor>`
  - `status`: numeric status code grouped by class:

    | Class | Meaning |
    | ----- | ------- |
    | 1xx   | Informational — request received, continuing process |
    | 2xx   | Success — request successfully received, understood, and accepted |
    | 3xx   | Redirection — further action required to complete the request |
    | 4xx   | Client Error — request contains bad syntax or cannot be fulfilled |
    | 5xx   | Server Error — server failed to fulfill a valid request |

    Common status codes and descriptions are listed in the original Chinese source (100, 101, 200, 201, ..., 505).

  - `reason-phrase`: human-readable description of the status code

- Headers: see the "Headers" section below
- Entity-body: the response payload

Example response:

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



## Headers

### General headers

| Header | Description |
| ------ | ----------- |
| Connection | Options related to the connection for this request/response |
| Date | Date and time the message was created |
| MIME-Version | MIME version used by the sender |
| Trailer | Lists header fields present in the trailer when using chunked transfer encoding |
| Transfer-Encoding | Encoding applied to the message body for safe transfer |
| Upgrade | Indicates protocol(s) the sender would like to switch to |
| Via | Shows intermediate proxies or gateways the message passed through |

Common cache-related general headers:

| Header | Description |
| ------ | ----------- |
| Cache-Control | Caching directives transmitted with the message |
| Pragma | Legacy directive header (not exclusively for caching) |

### Request headers

| Header | Description |
| ------ | ----------- |
| Client-IP | IP address of the client machine |
| From | Email address of the user making the request |
| Host | Hostname and port of the server receiving the request |
| Referer | URL of the resource that referred the current request |
| User-Agent | Identifies the client application |

Accept-related headers:

| Header | Description |
| ------ | ----------- |
| Accept | Media types acceptable for the response |
| Accept-Charset | Character sets acceptable for the response |
| Accept-Encoding | Content-codings acceptable in the response |
| Accept-Language | Preferred languages for the response |
| TE | Transfer-encoding extensions the client is willing to accept |

Conditional request headers:

| Header | Description |
| ------ | ----------- |
| Expect | Lists server behaviors required by the client for this request |
| If-Match | Only perform the request if the entity-tag matches |
| If-Modified-Since | Only perform the request if resource modified since given date |
| If-None-Match | Only perform the request if entity-tag does not match |
| If-Range | Conditional range requests |
| If-Unmodified-Since | Only perform the request if resource has not been modified since date |
| Range | Request a specific byte range if the server supports it |

Security-related request headers:

| Header | Description |
| ------ | ----------- |
| Authorization | Credentials for authenticating the client to the server |
| Cookie | Client-side token sent to server (not strictly a security header but carries auth data) |
| Cookie2 | Indicates cookie version supported by the client |

Proxy-related request headers:

| Header | Description |
| ------ | ----------- |
| Max-Forwards | Limits the number of times a request can be forwarded by proxies |
| Proxy-Authorization | Authorization credentials for proxy authentication |
| Proxy-Connection | Similar to Connection but used with proxies |

### Response headers

| Header | Description |
| ------ | ----------- |
| Age | Time in seconds since the response was generated at the origin server |
| Allow | Methods supported for the resource |
| Retry-After | Retry time if the resource is temporarily unavailable |
| Server | Server application name and version |
| Title | Suggested title for HTML documents |
| Warning | Additional information about the status beyond the reason-phrase |

Negotiation-related headers:

| Header | Description |
| ------ | ----------- |
| Accept-Ranges | Range types the server supports for the resource |
| Vary | List of request headers that determine the response variation |

Security-related response headers:

| Header | Description |
| ------ | ----------- |
| Proxy-Authenticate | Auth challenges from proxies |
| Set-Cookie | Set a client-side token; not strictly security but used for session identification |
| Set-Cookie2 | RFC 2965 cookie specification |
| WWW-Authenticate | Auth challenges from the origin server |

### Entity headers

| Header | Description |
| ------ | ----------- |
| Allow | Methods allowed on this entity |
| Location | Indicates the new location for a resource (used with 201 Created, redirects) |

Content headers:

| Header | Description |
| ------ | ----------- |
| Content-Base | Base URL for resolving relative URLs in the body |
| Content-Encoding | Any encodings applied to the body |
| Content-Language | Natural language(s) of the body |
| Content-Length | Size of the body in bytes |
| Content-Location | Alternate location for the resource represented by the body |
| Content-MD5 | MD5 checksum of the body |
| Content-Range | Byte range represented by the body in a partial response |
| Content-Type | Media type of the body |

Entity cache headers:

| Header | Description |
| ------ | ----------- |
| ETag | Entity tag associated with the entity |
| Expires | Date/time after which the entity is considered stale |
| Last-Modified | Last modification date of the entity |



## Versions

| Version | Notes |
| ------- | ----- |
| HTTP/0.9 |  |
| HTTP/1.0 |  |
| HTTP/1.1 |  |
| HTTP/2   |  |



## References

[1] RFC 2616 — Hypertext Transfer Protocol -- HTTP/1.1

[2] Wikipedia — Hypertext Transfer Protocol (Chinese)

[3] Wikipedia — URL (Chinese)

[4] "HTTP interview questions most interviewers ask" (Chinese)

[5] "HTTP introduction" (Chinese blog)

[6] "HTTP tutorial" (runoob)

[7] David Gourley, Brian Totty, Marjorie Sayer, Sailu Reddy, Anshu Aggarwal. HTTP: The Definitive Guide (3rd ed.)
