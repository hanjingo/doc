# URL Shorter

[TOC]



## Understand The Requirement

### Functional Requirements

- Given a long URL, the service should generate a shorter and unique alias for it.
- When the user hits a short link, the service should redirect to the original link.
- Links will expire after a standard default time span.

### Non-Functional Requirements

- The system should be highly available.
- URL redirection should happen in real-time with minimal latency.
- Shortened links should not be predictable.



## Cost Estimation

### Capacity

Let's assume our service has 30M new URL shortenings per month. Let's assume we store every URL shortening request (and associated shortened link) for 5 years. For this period the service will generate about 1.8B records.
$$
30million * 5years * 12monthes = 1.8B
$$

### Data Capacity Modeling

- Consider the average long URL size of 2KB ie for 2048 characters.
- Short URL size: 17Bytes for 17 characters.
- Created at -7 bytes.
- Expiration length in minutes -7 bytes.



## High-Level Design



## Data Model Design



## API Design



## Detailed Design



## Identify And Resolve Bottlenecks



## References

[1] [URL Shortner System Design](https://www.geeksforgeeks.org/system-design/system-design-url-shortening-service/)