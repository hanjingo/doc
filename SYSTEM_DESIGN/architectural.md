# Architectural

[TOC]



![software_arch_style](res/software_arch_style.jpg)

## Architectural Design

### MVC Pattern

The MVC pattern is used when there are multiple ways to view and interact with data. Also used when the future requirements for interaction and presentation of data are unknown.

By separating presentation and interaction from the system data. The system is structured into three logical components that interact with each other. The **Model** component manages the system data and associated operations on that data. The **View** component defines and manages how the data is presented to the user. The **Controller** component manages user interaction (e.g., key presses, mouse clicks, etc) and passes these interactions to the view and the Model.

*Notic*:

- The MVC pattern allows the data to change independently of its representation and vice versa. Supports presentation of the same data in different ways, with changes made in one representation shown in all of them.
- It can involve additional code and code complexity when the data model and interactions are simple.

### Layered Architecture Pattern

The Layered Architecture pattern is used when building new facilities on top of existing systems; when the development is spread across several teams, with each responsibility for a layer of functionality; and when there is a requirement for multi-level security.

By organizing the system into layers with related functionality associated with each layer. A layer provides services to the layer above it, so the lowest-level layers represent core services that are likely to be used throughout the system.

*Notice*:

- Layer Architecture Pattern allows replacement of entire layers so long as the interface is maintained. Redundant facilities (e.g., authentication) can be provided in each layer to increase the dependability of the system.
- In practice, providing a clean separation between layers is often difficult, and a high-level layer may have to interact directly with lower-level layers rather than through the layer immediately below it. Performance can be a problem because of multiple levels of interpretation of a service request as it is processed at each layer.

### Repository Architecture Pattern

The Repository Architecture Pattern is used when you have a system in which large volumes of information are generated that have to be stored for a long time. You may also use it in data-driven systems where the inclusion of data in the repository triggers an action or tool.

All data in a system is managed in a central repository that is accessible to all system components. Components do not interact directly, only through the repository.

*Notice*:

- Components can be independent--they do not need to know of the existence of other components. Changes made by one component can be propagated to all components. All data can be managed consistently (e.g., backups done at the same time) as it is all in one place.
- The repository is a single point of failure, so problems in the repository affect the whole system. May be inefficiencies in organizing all communication through the repository. Distributing the repository across several computers may be difficult.

### Client-Server Architecture

The Client-Server Architecture is used when data in a shared database is accessed from a range of locations. Because servers can be replicated, they may be used when the load on a system is variable.

In a client-server architecture, the functionality of the system is organized into services, with each service delivered from a separate server. Clients are users of these services and access servers to make use of them.

*Notice*:

- The principal advantage of this model is that servers can be distributed across a network. General functionality (e.g., a printing service) can be available to all clients and does not need to be implemented by all services.
- Each service is a single point of failure so susceptible to denial of service attacks or server failure. Performance may be unpredictable because it depends on the network as well as the system. May be management problems if servers are owned by different organizations.

### Pipe And Filter Architecture

The Pipe And Filter Architecture Pattern is commonly used in data processing applications (both batch- and transaction-based) where inputs are processed in separate stages to generate related outputs.

The processing of the data in a system is organized so that each processing component (filter) is discrete and carries out one type of data transformation. The data follows (as in a pipe) from one component to another for processing.

*Notice*:

- The Pipe and Filter Architecture is easy to understand and supports transformation reuse.  Workflow style matches the structure of many business processes. Evolution by adding transformations is straightforward. Can be implemented as either a sequential or concurrent system.
- The format for data transfer has to be agreed upon between communicating transformations. Each transformation must parse its input and unparse its output tp the agreed form. This increases system overhead and may mean that it is impossible to reuse functional transformations that use incompatible data structures.



## Event-Driven Architecture(EDA)

![event_driven_architecture](res/event_driven_architecture.png)

Event-Driven Architecture(EDA) is a software design approach where system components communicate by producing and responding to events, such as user actions or system state changes.

### Importance

Event-Driven Architecture(EDA) holds significant importance in system design for several reasons:

- Flexibility and Responsiveness
- Scalability
- Real-time Processing

### Design Pattern

![event_driven_architecture_patterns](res/event_driven_architecture_patterns.png)

Design patterns for Event-Driven APIs in system design provide structured approaches to address common challenges and optimize the implementation of event-driven architectures. Here are several key design patterns relevant to Event-Driven APIs:

- Publish-Subscribe

- Event Sourcing

  ![eda_pattern_event_sourcing](res/eda_pattern_event_sourcing.png)

- CQRS(Command Query Responsibility Segregation)

  ![eda_pattern_cqrs](res/eda_pattern_cqrs.png)

- Saga Pattern

  ![eda_pattern_saga](res/eda_pattern_saga.png)

- Event-Driven Choreography

  ![eda_pattern_choreography](res/eda_pattern_choreography.png)

- Event Collaboration

- Event Versioning

- Event Mesh

- Event-Driven Microservices

### Error Handling

Effective error handling in Event-Driven Architecture(EDA) is crucial for ensuring system reliability, scalability, and data integrity. Here are some key strategies for managing errors in an EDA system:

1. Retry Mechanism
   - Automatic Retries
   - Exponential Backoff
2. Dead-Letter Queues(DLQ)
   - Unprocessable Events Handling
   - Manual Review and Intervention
3. Idempotency
   - Idempotent Event Handlers
   - Unique Event Identifiers
4. Circuit Breakers
   - Failure Isolation
   - Graceful Degradation
5. Event Logging and Monitoring
   - Comprehensive Logging
   - Real-Time Monitoring

### Use Case

Event-Driven Architecture(EDA) is a great choice in below scenarios:

- Real-Time Applications
- Scalability Needs
- Complex Event Processing
- Integration of Diverse Systems

### Challenge

Event-Driven Architecture(EDA) has a few key challenges:

- Increased Complexity
- Event Order and Consistency
- Debugging and Tracing
- Event Latency



## Microservice Architecture

![microservice_arch](res/microservice_arch.png)

Microservice architecture is an approach to system design where a large application is built as a collection of small, loosely coupled, and independently deployable services. Each service, known as a microservice, focuses on a specific business function and can be developed, deployed, and scaled independently of other services.

Advantages:

- Independent Development and Deployment
- Small Focused Team
- Small CodeBase
- Mix of Technologies
- Fault Isolation
- Scalability
- Data Isolation

Disadvantages:

- Complexity
- Testing
- Data Integrity
- Network Latency
- Versioning

### Tech Stack

![microservice_tech_stack](res/microservice_tech_stack.png)

### Design Pattern

![microservice_design_pattern](res/microservice_design_pattern.png)

### APIs

APIs (Application Programming Interfaces) are crucial in microservice architectures for several reasons:

- Communication
- Decoupling
- Scalability
- Interoperability
- Reusability
- Evolvability

### Use Case

Below are the use cases of request-driven microservices:

- User Authentication
- Payment Processing
- APIs for Web Applications
- CRUD Operations

Below are the use cases of event-driven microservices:

- Order Processing
- Notification Systems
- Real-time Analytics
- Microservices Communication

### Data Consistency

![microservice_data_consistency](res/microservice_data_consistency.png)

### Data Sharing

![microservice_data_sharing](res/microservice_data_sharing.png)

### Key Transition Patterns From Monolith

![microservice_key_transition](res/microservice_key_transition.png)

Microservices architecture addresses the challenges of monoliths by breaking the application into smaller, independent services. Each service is responsible for a specific functionality and can be developed, deployed, and scaled independently.

### Best Practice

![microservice_best_practice](res/microservice_best_practice.png)



## SOA Architecture

Service-Oriented Architecture (SOA) is a huge collection of services in which services communicate with each other.

### Roles

![soa_roles](res/soa_roles.png)

- **Service provider:** The service provider is the maintainer of the service and the organization that makes available one or more services for others to use. To advertise services, the provider can publish them in a registry, together with a service contract that specifies the nature of the service, how to use it, the requirements for the service, and the fees charged.
- **Service consumer:** The service consumer can locate the service metadata in the registry and develop the required client components to bind and use the service.

### Components

![soa_components](res/soa_components.png)



## Cell-Based Architecture

![cell_based_arch](res/cell_based_arch.png)

In cell-based architecture, there are multiple isolated instances of a workload, where each instance is known as a cell. There are three properties of a cell:

- Each cell is independent.
- A cell does not share the state with other cells.
- Each cell handles a subset of the overall traffic.



## Domain-Driven Design (DDD)

![domain_driven_design_arch](res/domain_driven_design_arch.png)

Domain-Driven Design (DDD) is an approach to software development that tackles domain complexity by emphasizing the importance of modeling the core domain and business logic and using those models as the foundation for software design.

At its heart, Domain-Driven Design is about:

- Placing the primary focus on the core domain.
- Basing complex designs on a model of the domain
- Building collaboration between technical and domain experts.



## Example 1: Reddit's Go Microservice Migration

### Datastore Solutions

![reddit_sister_datastore_solution](res/reddit_sister_datastore_solution.png)

Reddit’s engineering team came up with a solution they called “sister datastores”. They created three completely separate datastores that mirrored their production infrastructure (Postgres, Memcached, and Redis). The critical difference was that only the new Go microservice would write to these sister stores.

### Verification

![reddit_verification_process](res/reddit_verification_process.png)

Reddit’s engineering team added another verification layer. They ran all tap comparisons through actual CDC event consumers in the legacy Python service. This meant Python code would attempt to deserialize and process events written by Go. If Python could successfully read and handle these events, they knew cross-language compatibility was working. This end-to-end verification ensured not just that Go wrote correct data, but that the entire ecosystem could consume it.



## Summary

### System Integration

![system_integration](res/system_integration.png)

### Handling Growth and Failure

![handling_growth_and_failure](res/handling_growth_and_failure.jpg)

### Monolith vs Microservices vs Modular Monolith

![monolith_vs_microservices_vs_modular_monolith](res/monolith_vs_microservices_vs_modular_monolith.png)

### Microservices vs Monolithic Architecture

![monolith_vs_microservices](res/monolith_vs_microservices.png)

| Monolithic Architecture                                      | Microservice Architecture                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Single-tier architecture                                     | Multi-tier architecture                                      |
| Built as one large application with tightly coupled components | Composed of small, loosely coupled services components       |
| Deployed as a single unit                                    | Individual services can be deployed independently            |
| Horizontal scaling can be challenging                        | Easier to scale horizontally                                 |
| Development is simpler initially                             | Development is more complex due to multiple services         |
| Tehcnology stack choices are usually limited                 | Freedom to choose the best technology for each service       |
| Entire application may fail if a part fails                  | Individual services can fail without affecting others        |
| Easier to maintain due to its simplicity                     | Requires more effort to manage multiple services             |
| Less flexible as all components are tightly coupled          | More flexible as components can be developed, deployed, and scaled independently |
| Communication between components is faster                   | Communication may be slower due to network calls             |

### Microservices vs SOA

![microservices_vs_soa](res/microservices_vs_soa.png)

|                             SOA.                             |                             MSA.                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| It is a huge collection of services in which services communicate with each other. | It is a general architecture that takes a large number of services and break down into small services or shareable components. |
|      It works on a Share-as-much-as-possible approach.       |       It works on a Share-little-as-promise approach.        |
|            It is used to share the data storage.             |               It has independent data storage.               |
|               It supports multiple protocols.                |       It supports the HTTP/REST lightweight protocol.        |
| In service-oriented architecture, there is a multi-threaded system with more handle I/O. | In Micro service Architecture, there is a single-threaded with non-locking I/O handle. |
|          It has a common platform for all services.          | It has a platform like Nodejs is used, and an application server not used. |
|   It uses of containers is less popular with Docker Linux.   |                Its container works very well.                |
|               It uses a traditional database.                |              It uses a non-relational database.              |
|           It uses ESB services for communication.            | It does not use ESB services. It has a simple messaging system. |
|             It has a common governance standard.             |        Relaxed governance with more focus on people.         |

### Orchestraion vs Choreography

![orchestraion_vs_choreography](res/orchestraion_vs_choreography.png)

### Request-Driven vs Event-Driven Microservices

![req_driven_vs_event_driven_microservices](res/req_driven_vs_event_driven_microservices.png)

| Feature             | Request-driven Microservices    | Event-driven microservices                   |
| ------------------- | ------------------------------- | -------------------------------------------- |
| Communication Model | Synchronous(request-response)   | Asynchronous(event-based)                    |
| Coupling            | Tight coupling between services | Loose coupling                               |
| Response Time       | Direct waiting for responses    | Non-blocking; responses occur independently  |
| Scalability         | Can lead to bottlenecks         | High scalability, suitable for many events   |
| Complexity          | Generally simpler to implement  | More complex due to event management         |
| Debugging           | Easier to trace request flows   | Harder to debug; requires tracking events    |
| Use Cases           | APIs, payment processing        | Order management, notifications              |
| Data Consistency    | Easier to ensure consistency    | Requires strategies for eventual consistency |

### Batch vs Stream Processing

![batch_vs_stream_proc](res/batch_vs_stream_proc.png)

### Strategies To Share Data Between Services

![strategies_to_share_data](res/strategies_to_share_data.png)



## Reference

[1] Ian Sommerville. SOFTWARE ENGINEERING. 9th Edition

[2] [Event-Driven APIs in Microservice Architectures](https://www.geeksforgeeks.org/system-design/event-driven-apis-in-microservice-architectures/)

[3] [Monolith vs Microservices vs Modular Monoliths: What's the Right Choice](https://blog.bytebytego.com/p/monolith-vs-microservices-vs-modular)

[4] [A Crash Course on Microservices Design Patterns](https://blog.bytebytego.com/p/a-crash-course-on-microservices-design)

[5] [Mastering Data Consistency Across Microservices](https://blog.bytebytego.com/p/mastering-data-consistency-across)

[6] [Data Sharing Between Microservices](https://blog.bytebytego.com/p/data-sharing-between-microservices)

[7] [Saga Pattern Demystified: Orchestration vs Choreography](https://blog.bytebytego.com/p/saga-pattern-demystified-orchestration)

[8] [EP122: API Gateway 101](https://blog.bytebytego.com/p/ep122-api-gateway-101)

[9] [Consistent Hashing 101: How Modern Systems Handle Growth and Failure](https://blog.bytebytego.com/p/consistent-hashing-101-how-modern)

[10] [Batch vs Stream Processing](https://blog.bytebytego.com/p/ep185-docker-vs-kubernetes)

[11] [How Reddit Migrated Comments Functionality from Python to Go](https://blog.bytebytego.com/p/how-reddit-migrated-comments-functionality)

[12] [2. What Are the Differences Between SOA and Microservices?](https://blog.bytebytego.com/i/139741133/2-what-are-the-differences-between-soa-and-microservices)

[13] [Service-Oriented Architecture](https://www.geeksforgeeks.org/software-engineering/service-oriented-architecture/)

[14] [Top Strategies to Share Data Between Services](https://blog.bytebytego.com/p/top-strategies-to-share-data-between)

[15] [From Monolith to Microservices: Key Transition Patterns](https://blog.bytebytego.com/p/from-monolith-to-microservices-key)

[16] [A Crash Course on Domain-Driven Design](https://blog.bytebytego.com/p/a-crash-course-on-domain-driven-design)