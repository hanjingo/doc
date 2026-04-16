# CDN

[TOC]



## Intro

![cdn_guide](res/cdn_guide.png)

When a user requests content from a website with a CDN, the CDN identifies the user's location and routes the request to the nearest edge server. The edge server, which stores cached copies of the website's content, quickly delivers the requested content to the user.

### Importance

CDNs offer several key benefits that make them important for delivering content over the internet:

- Faster Content Delivery
- Improved Website Performance
- Scalability
- Redundancy and Reliability
- Cost Saving
- Security

### Benefits

The benefits of incorporating a CDN into your system design can be follows:

- Improved website performance
- Reduced bandwidth costs
- Increased global reach

### Challenges

Below are the challenges of using CDN:

- Cost
- Complexity
- Security considerations



## Types

### Public CDNs

Any CDN that is accessible to everybody online is referred to as a public CDN. These CDNs are used to swiftly and effectively provide content, including pictures, movies, and other static files, to users. They usually consist of a vast global network of servers.

### Private CDNs

A CDN that is only utilized by one firm or organization is known as a private CDN. These CDNs are used to distribute content to internal users or clients, and they are frequently set up on a private cloud or within an organization's own infrastructure. More control over content distribution is possible with private CDNs, which may be customized to satisfy particular performance and security needs.

### P2P CDNs

These CDNs utilize peer-to-peer networking technology to distribute content directly between users, reducing reliance on centralized servers.

### Hybrid CDNs

A hybrid CDN combines elements of both public and private CDNs. In a hybrid CDN, some content is delivered using a public CDN, while other content is delivered using a private CDN. This approach allows organizations to optimize content delivery based on factors such as cost, performance, and security requirements.

### Push CDNs

In a push CDN, content is uploaded or "pushed" to the CDN's servers in advance of when it is needed. This can help improve performance by ensuring that content is available closer to end users when they request it. Push CDNs are often used for caching large files or content that is not frequently updated.

### Pull CDNs

Pull CDNs fetch content from the origin server when requested and are mainly used for caching static or frequently accessed content. Dynamic content may be delivered, but is usually cached selectively or for shorter durations.



## Workflow

![cdn_work](res/cdn_work.png)

Below is the simple step-by-step working of a CDN:

1. User sends a request for content (e.g., an image) from a website.
2. CDN identifies the user's location and routes the request to the nearest edge server.
3. If the content is cached at the edge server, it is delivered directly to the user.
4. If the content is not cached, the edge server retrieves it from the origin server, caches it locally, and delivers it to the user.
5. Cached content is stored at the edge server for future requests, optimizing performance and reducing latency.



## Invalidate Content

TODO



## SSL/TLS

TODO



## Components

A typical CDN consists of the following key elements:

- Edge Servers
- Origin Server
- Content Distribution Nodes
- Control Plane



## Summary

### Usage Of CDN

CDNs are not limited to websites and can be used for various purposes, including:

- Streaming media delivery
- Software Distribution
- E-commerce
- Gaming
- API delivery

### CDN vs Edge Server

|                   CDN                    |                  Edge Server                  |
| :--------------------------------------: | :-------------------------------------------: |
|    Reduces latency for static content    | Reduces latency for processing & dynamic data |
|       Distributes content globally       |           Processes data near users           |
|       Globally distributed servers       |        Located close to users/devices         |
| Best for static content (images, videos) |   Best for real-time processing (IoT, apps)   |
|        Mainly caching & delivery         |         Can process and analyze data          |
|        Subscription-based pricing        |         High setup & maintenance cost         |



## References

[1] [What is Content Delivery Network(CDN) in System Design](https://www.geeksforgeeks.org/system-design/what-is-content-delivery-networkcdn-in-system-design/)

[2] [CDN Vs Edge Server - System Design](https://www.geeksforgeeks.org/system-design/cdn-vs-edge-server-system-design/)

[3] [Content Delivery Network(CDN) in System Design](https://www.geeksforgeeks.org/system-design/what-is-content-delivery-networkcdn-in-system-design/)

