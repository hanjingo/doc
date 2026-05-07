# System Design Summary

[TOC]



![system_design_blueprint](res/system_design_blueprint.jpg)

## Topics

![system_design_topics](res/system_design_topics.gif)

---



## Design Principle

![system_design_terminology](res/system_design_terminology.png)

### SOLID

![solid_principle](res/solid_principle.png)

The SOLID principles are five essential guidelines that enhance software design, making code more maintainable and scalable.

### DRY

![dry_principle](res/dry_principle.png)

DRY(Don't Repeat Yourself) is a software development principle that says the same logic or knowledge should not be written multiple times in a system.

### KISS

The KISS principle, which stands for "Keep It Simple, Stupid", is a design principle that suggests simplicity should be a key goal in design, development, and other fields, such as engineering, software development, and user interface design.

### YAGNI

![yagni_principle](res/yagni_principle.png)

"YAGNI" stands for "You Aren't Gonna Need It". YAGNI is a software development principle that advises developers to implement only what is required for current needs.

---



## Workflow

![system_design_step](res/system_design_step.png)

---



## Requirements

![system_design_requirements](res/system_design_requirements.png)

### Functional Requirements

Functional requirements are the requirements that the end user specifically demands as basic functionalities that the system should offer. All these functionalities need to be necessarily included in the system as part of the contract.

### Non-Functional Requirements

![non_functional_requirement](res/non_functional_requirement.jpg)

Non-functional Requirements are the quality constraints that the system must satisfy according to the project contract. The priority or extent to which these factors are implemented varies from one project to another. They are also called non-behavioral requirements. For example: portability, maintainability, reliability, scalability, security, etc.

### Extended requirements

These are basically "nice to have" requirements that might be out of the scope of the system.

---



## Cost Estimation

![what_is_performance](res/what_is_performance.png)

Software Cost Estimation is a systematic process used to forecast the amount of effort (person-hours or person-months), duration(calendar time), and financial cost required to develop, deploy, and maintain a software product.

---



## API Design

![api_protocols](res/api_protocols.jpg)

### Best Practices

![api_design_best_practices](res/api_design_best_practices.png)

### Effective API

![api_effective](res/api_effective.jpg)

---



## High Level Design(HLD)

![software_arch_style](res/software_arch_style.jpg)

High-Level Design(HLD) is an initial step in the development of applications where the overall structure of a system is planned.

A diagram representing each design aspect is included in the HLD (which is based on business requirements and anticipated results):

- It contains descriptions of hardware, software interfaces, and also user interfaces.
- It is also known as the macro level/system design.
- It is created by a solution architect.
- The workflow of the user's typical process is detailed in the HLD, along with performance specifications.

---



## Database Design

### DB

![types_of_db](res/types_of_db.png)

### Caching

![caching_arch_example](res/caching_arch_example.png)

### Storage

![object_store_use_case](res/object_store_use_case.png)

---



## Scalability and Performance 

### Scalability Pattern

![scalability_patterns](res/scalability_patterns.png)

### Performance Metrics

![system_performance_metrics](res/system_performance_metrics.png)

### Strategies For System Performance

![strategies_for_system_performance](res/strategies_for_system_performance.png)

### Reduce Latency

![latency_reduce](res/latency_reduce.png)

### Latency vs Throughput

![latency_vs_throughput](res/latency_vs_throughput.jpg)

---



## Reliability and Resiliency

### Strategies For Reliability And Fault Tolerance

![strategies_for_reliability_fault_tolerance](res/strategies_for_reliability_fault_tolerance.png)

---



## Dive In

![system_design_concepts](res/system_design_concepts.jpg)

### Load Balancer

![load_balancer](res/load_balancer.png)

### API Gateway

![api_gateway](res/api_gateway.png)

### MQ

![mq_vs_no_mq](res/mq_vs_no_mq.png)

### CDN

![cdn_work](res/cdn_work.png)

### Circuit Breaker

TODO

### Service Discovery

![service_discovery](res/service_discovery.jpg)

### Scaling

TODO

---



## Other

### General Template

![system_design_general_template](res/system_design_general_template.jpeg)

### Data Pipeline

![data_pipeline_overview](res/data_pipeline_overview.png)

### AI

TODO

### Version Strategies

![common_versioning_strategies](res/common_versioning_strategies.png)



## Reference

[1] Ian Sommerville. SOFTWARE ENGINEERING . 9th Edition

[2] [Cracking the System Design Interview Round](https://www.geeksforgeeks.org/system-design/how-to-crack-system-design-round-in-interviews/)

[3] [Difference between High Level Design(HLD) and Low Level Design(LLD)](https://www.geeksforgeeks.org/system-design/difference-between-high-level-design-and-low-level-design/)

[4] [Data Modeling in System Design](https://www.geeksforgeeks.org/system-design/data-modeling-in-system-design/)

[5] [What is Low Level Design or LLD?](https://www.geeksforgeeks.org/system-design/what-is-low-level-design-or-lld-learn-system-design/)

[6] [System Design Introduction - LLD & HLD](https://www.geeksforgeeks.org/system-design/getting-started-with-system-design/)

[7] [100+ Best System Design Resources for Interview and Learning](https://github.com/javabuddy/best-system-design-resources?tab=readme-ov-file)

[8] [EP56: System Design Blueprint: The Ultimate Guide](https://blog.bytebytego.com/p/ep56-system-design-blueprint-the)

[9] [Top Strategies to Reduce Latency](https://blog.bytebytego.com/p/top-strategies-to-reduce-latency)

[10] [EP160: Top 20 System Design Concepts You Should Know](https://blog.bytebytego.com/p/ep160-top-20-system-design-concepts)

[11] [EP186: Latency vs. Throughput](https://blog.bytebytego.com/p/ep186-latency-vs-throughput)

[12] [EP175: What is the SOLID Principle?](https://blog.bytebytego.com/p/ep175-what-is-the-solid-principle)

[13] [What are some of the most popular versioning strategies?](https://blog.bytebytego.com/p/ep178-the-lifecycle-of-a-kubernetes)

[14] [Non-Functional Requirements: The Backbone of Great Software - Part 1](https://blog.bytebytego.com/p/non-functional-requirements-the-backbone)

[15] [The System Design Topic Map](https://blog.bytebytego.com/p/ep163-12-mcp-servers-you-can-use)
