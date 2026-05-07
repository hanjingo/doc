# Gateway

[TOC]



![api_gateway_summary](res/api_gateway_summary.png)

## API Gateway

An API Gateway is a key component in system design, particularly in microservices architectures and modern web applications. It serves as a centralized entry point for managing and routing requests from clients to the appropriate microservices or backend services within a system.

![api_gateway](res/api_gateway.png)

### Methods Of Authentication

- API Keys
- OAuth
- JWT(JSON Web Tokens)
- LDAP(Lightweight Directory Access Protocol)

### Work Flow

![working_of_api_gateway](res/working_of_api_gateway.png)

- Routing

  Directs client requests to the appropriate service based on URL, method, or headers.

- Protocol Translation

  Converts requests between protocols (e.g., HTTP -> gRPC/WebSocket).

- Request Aggregation

  Combines multiple backend class into one to reduce round trips.

- Authentication & Authorization

  Verifies client identity and access permissions.

- Rate Limiting & Throttling

  Controls request rates to prevent abuse and ensure resource balance.

- Load Balancing

  Distributes requests across service instances for scalability and availability.

- Caching

  Stores backend responses to speed up repeated requests.

- Monitoring & Logging

  Tracks metrics and logs for performance and usage insights.

### API Gateway with Microservices

![api_gateway_with_microservices](res/api_gateway_with_microservices.png)

- The web application communicates with the API Gateway.
- The API Gateway routes requests to the appropriate microservices.
- It handles authentication, rate limiting, caching, and other functions.
- Error responses are also standardized by the API Gateway.

### API Gateway with Monolith

![api_gateway_with_monolith](res/api_gateway_with_monolith.png)

- The web application communicates with the API Gateway.
- The API Gateway simplifies client interactions and provides security and caching and other features.
- It also manages API versioning and error handling.

### Advantage

- Centralized Entry Point
- Routing & Load Balancing
- Authentication & Authorization
- Request & Response Transformation

### Use Cases

![api_gateway_use_case](res/api_gateway_use_case.jpg)



## Example 1: Tinder’s API Gateway

### High-Level Design

![tinder_api_gateway_high_lvl_design](res/tinder_api_gateway_high_lvl_design.png)

(TAG: Tinder API Gateway)

This design unlocks three critical outcomes:

- Faster developer workflows, since most changes require no code, only config.
- Stronger security boundaries, because teams own and isolate their gateway instances.
- Better reuse, through shared filters and common middleware patterns.

### Boot Flow

![tinder_proc_flow](res/tinder_proc_flow.png)

This design ensures that routing logic executes with minimal overhead. Every decision has already been made. Every route, predicate, and filter is compiled into the runtime graph.

### Request Lifecycle

![tinder_request_lifecycle](res/tinder_request_lifecycle.png)

When a request hits a TAG-powered gateway, it passes through a well-defined pipeline of filters, transformations, and lookups before reaching the backend.



## Summary

### API Gateway vs Service Mesh

![api_gateway_vs_service_mesh](res/api_gateway_vs_service_mesh.png)



## Reference

[1] [What is API Gateway?](https://www.geeksforgeeks.org/system-design/what-is-api-gateway-system-design/)

[2] [API Gateway](https://blog.bytebytego.com/p/api-gateway)

[3] [API Gateway vs Service Mesh - Which One Do You Need](https://blog.bytebytego.com/p/api-gateway-vs-service-mesh-which)

[4] [How Tinder’s API Gateway Handles A Billion Swipes Per Day](https://blog.bytebytego.com/p/how-tinders-api-gateway-handles-a)

[5] [Top 4 API Gateway Use Cases](https://blog.bytebytego.com/p/ep205-cpu-vs-gpu-vs-tpu?utm_source=publication-search)