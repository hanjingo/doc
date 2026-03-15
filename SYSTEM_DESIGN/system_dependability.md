# System Dependability

[TOC]



There are some principal dimensions to dependability:

1. Availability.
2. Reliability.
3. Safety.
4. Security.
5. Repairability.
6. Maintainability.
7. Survivability.
8. Error tolerance.

To develop dependable software, you therefore need to ensure that:

1. You avoid the introduction of accidental errors into the system during software specification and development.
2. You design verification and validation processes that are effective in discovering residual errors that affect the dependability of the system.
3. You design protection mechanisms that guard against external attacks that can compromise the availability or security of the system.
4. You configure the deployed system and its supporting software correctly for its operating environment.

![principal_depend_property](res/principal_depend_property.png)

*Principal dependability properties*



## Availability

System **availability** defined as: The probability that a system, at a point in time, will be operational and able to deliver the requested services.

System faults do not always result in system errors and system errors do not necessarily result in system failures. The reasons for this are as follows:

1. Not all code in a program is executed.
2. Errors are transient.
3. The system may include fault detection and protection mechanisms.

### Measured

Availability is measured as the percentage of time a system or service is operational and accessible to users over a specific period. It is expressed using the formula:
$$
Availability(\%) = ((Uptime) / (Uptime + Downtime)) * 100;
$$

- $Uptime$: The total time a system is operational and functioning as expected.
- $Downtime$: The total time the system is unavailable due to failures, maintenance, or other issues.

For example: 

If a system has 99.9% availability in a year:

- Total time in a year: $365 \times 24 \times 60 = 525,600$ minutes
- Downtime allowed: $0.1\% \times 525,600 = 525.6$ minutes

### Achieve High Availability

System designers implement various strategies and technologies to achieve high availability, such as:

- Redundancy: Use redundant servers or components so that, in the event of a failure, another can take over without any problems.
- Load balancing: Incoming requests are divided among several servers or resources to enhance system performance and fault tolerance while avoiding overload on any one part.
- Failover mechanisms: Implementing automated processes to detect failures and switch to redundant systems without manual intervention.
- Disaster Recovery(DR): Having a comprehensive plan is place to recover the system in case of a catastrophic event that affects the primary infrastructure.
- Monitoring and Alerting: putting in place reliable monitoring systems that can identify problems instantly and alert administrators so they can act quickly.
- Performance optimization: Lowering the possibility of bottlenecks and breakdowns by making sure the system is built and adjusted to efficiently manage the expected load.
- Scalability: Designing the system to scale easily by adding more resources when needed to accommodate increased demand.

---



## Consistency

Consistency plays a crucial role in system design for several reasons:

- Correctness
- Reliability
- Data Integrity
- Concurrency Control
- User Experience

### Types

![consistency](res/consistency.png)

- Strong Consistency

  ![strong_consistency_example](res/strong_consistency_example.png)

  It guarantees that every read operation receives the most recent write operation's value or an error.

- Eventual Consistency

  ![eventual_consistency_example](res/eventual_consistency_example.png)

  It guarantees that data replicas will eventually converge to the same value even while it permits them to diverge briefly.

- Causal Consistency

  It ensures that clients observing concurrent events maintain a consistent view of their causality relationship, which is essential for maintaining application semantics and correctness.

- Weak Consistency

  ![weak_consistency_example](res/weak_consistency_example.png)

  It just ensures that updates will eventually spread to every duplicate, even though it permits significant differences between them.

- Read-your-Writes Consistency

  It guarantees that after a client writes a value to a data item, it will always be able to read that value or any subsequent value it has written.

- Monotonic Consistency

  It ensures that if a client observes a particular order of updates (reads or writes) to a data item, it will never observe a conflicting order of updates.

- Monotonic Reads and Writes

  It guarantees that if a client performs a sequence of reads or writes, it will observe a monotonically increasing sequence of values or updates.

### Strategies for achieving Consistency

Design Patterns and Best Practices

- Single Source of Truth
- Unchanged Operations
- Versioning
- Asynchronous Updates

Consistency Models:

- Eventual Consistency
- Strong Consistency
- Causal Consistency

Conflict Resolution Techniques:

- Last-Writer-Wins(LWW)
- Merge Strategies

---



## Reliability

System **reliability** may be defined more precisely as: The probability of failure-free operation over a specified time, in a given environment, for a specific purpose.

Identify three complementary approaches that are used to improve the reliability of a system:

- Fault avoidance.
- Fault detection and removal.
- Fault tolerance.

### Specification

Reliability requirements are, therefore, of two kinds:

1. Non-functional requirements, which define the number of failures that are acceptable during normal use of the system, or the time in which the system is unavailable for use. These are quantitative reliability requirements.
2. Functional requirements, which define system and software functions that avoid, detect, or tolerate faults in the software and so ensure that these faults do not lead to system failure.

### Non-functional reliability requirements

There are several advantages in deriving quantitative reliability specifications:

1. The process of deciding what required level of the reliability helps to clarify what stakeholders really need. It helps stakeholders understand that there are different types of system failure, and it makes clear to them that high levels of reliability are very expensive to achieve.
2. It provides a basis for assessing when to stop testing a system. You stop when the system has achieved its required reliability level.
3. It is a means of assessing different design strategies intended to improve the reliability of a system. You can make a judgment about how each strategy might lead to the required levels of reliability.
4. If a regulator has to approve a system before it goes into service (e.g., all systems that are critical to flight safety on an aircraft are regulated), then evidence that a required reliability target has been met is important for system certification.

### Functional reliability specification

There are three types of functional reliability requirements for a system:

1. Checking requirements
2. Recovery requirements
3. Redundancy requirements

### Factors that affect Reliability

- Design Quality
- Hardware Quality
- Software Bugs
- Maintenance
- Workload
- External Conditions
- Redundancy

### Metrics

The choice of metric depends on the type of system that is being specified and the requirements of the application domain. The metrics are:

1. `Probability of failure on demand (POFOD)` If you use this metric, you define the probability that a demand for service from a system will result in a system failure.
2. `Rate of occurrence of failures (ROCOF)` This metric sets out the probable number of system failures that are likely to be observed relative to a certain time period (e.g., an hour), or to the number of system executions.
3. `Availability (AVAIL)` The availability of a system reflects its ability to deliver services when requested.

### Achieve high reliability

![achieve_high_reliability](res/achieve_high_reliability.png)

- Scalability and Maintainability: Scalability and Maintainability ensure the system continues to work efficiently as it grows and evolves over time.
- Fault Tolerance: Fault Tolerance enables the system to detect errors and recover automatically without failure.
- Load Balancing: Load Balancing distributes traffic across systems to avoid overload and handle high demand smoothly.
- Monitoring and Analytics: Monitoring and analytics track performance and help detect issues early.
- Redundancy: Redundancy duplicates critical components so the system keeps running even if one fails.

### Testing

![reliability_measurement](res/reliability_measurement.png)

*Reliability measurement*

This conceptually attractive approach to reliability measurement is not easy to apply in practice. The principal difficulties that arise are:

1. Operational profile uncertainty.
2. High costs of test data generation.
3. Statistical uncertainty when high reliability is specified. 
4. Recognizing failure.

### Measure Reliability

Here's how reliability can be measured with formulas for better clarity:

- Uptime Percentage
  $$
  \text{Uptime Percentage} = ((TotalTime - Downtime) / TotalTime) * 100
  $$

- Mean Time Between Failures(MTBF)
  $$
  MTBF = (\text{Total Operational Time} / \text{Number of Failures})
  $$

- Mean Time to Repair(MTTR)
  $$
  MTTR = \text{Total Repair Time} / \text{Number of Failures}
  $$

- Error Rate
  $$
  \text{Error Rate} = (\text{Number of Errors} / \text{Total Transactions or Operations}) * 100
  $$

### Single Point of Failure(SPOF)

A single point of failure(SPOF) is a system component that, if it fails, can cause the entire system to stop working, making the system less reliable.

To avoiding single points of failure(SPOFs), here are several strategies to help mitigate or eliminate SPOFs:

- Redundancy
- Load Balancing
- Failover
- Regular Testing
- Monitoring & Alerts
- Documentation
- Continuous Improvement

---



## Safety

Safety-critical software falls into two classes:

1. Primary safety-critical software.
2. Secondary safety-critical software.

The key to assuring safety is to ensure either that accidents do not occur or that the consequences of an accident are minimal. This can be achieved in three complementary ways:

1. `hazard avoidance` The system is designed so that hazards are avoided.
2. `hazard detection and removal` The system is designed so that hazards are detected and removed before they result in an accident.
3. `Damage limitation` The system may include protection features that minimize the damage that may result from an accident.

### Safety specification

#### Hazard assessment

![risk_triangle](res/risk_triangle.png)

*The risk triangle*

There are three risk categories that you can use in hazard assessment:

1. Intolerable risks in safety-critical systems are those that threaten human life.
2. As low as reasonably practicable (ALARP) risks are those that have less serious consequences or that are serious but have a very low probability of occurrence.
3. Acceptable risks are those where the associated accidents normally result in minor damage.

#### Hazard analysis

![fault_tree](res/fault_tree.png)

### Risk reduction

1. Once potential risks and their root cause have been identified, you are then able to derive safety requirements that manage the risks and ensure that incidents or accidents do not occur. There are three possible strategies that you can use:

   1. `Hazard avoidance:` The system is designed so that the hazard cannot occur.
   2. `Hazard detection and removal:` The system is designed so that hazards are detected and neutralized before they result in an accident.
   3. `Damage limitation:` The system is designed so that the consequences of an accident are minimized.

### Structured safety arguments

![safety_argument](res/safety_argument.png)

*Informal safety argument based on demonstrating contradictions*

---



## Security

In any networked system, there are three main types of security threats:

1. Threats to the confidentiality of the system and its data.
2. Threats to the integrity of the system and its data.
3. Threats to the availability of the system and its data.

The controls that you might put in place to enhance system security are comparable to those for reliability and safety:

1. Vulnerability avoidance.
2. Attack detection and neutralization.
3. Exposure limitation and recovery.

### Security risk management

Risk assessment stage:

1. Preliminary risk assessment.
2. Life-cycle risk assessment.
3. Operational risk assessment.

### Life-cycle Secure Software Development

![life_cycle_secure_software_dev](res/life_cycle_secure_software_dev.png)

### Life-cycle risk assessment

![life_cycle_risk_analysis](res/life_cycle_risk_analysis.png)

*Life-cycle risk analysis*

![vulnerability_tech_choice](res/vulnerability_tech_choice.png)

*Vulnerabilities associated with technology choices*

### Design for security

#### Architectural design

In designing a system architecture that maintains security, you need to consider two fundamental issues:

1. Protection--how should the system be organized so that critical assets can be protected against external attack?
2. Distribution--how should system assets be distributed so that the effects of a successful attack are minimized?

![layer_protection_arch](res/layer_protection_arch.png)

*A layered protection architecture*

#### Design guidelines

Design guidelines for secure systems engineering:

1. Base security decisions on an explicit security policy.
2. Avoid a single point of failure.
3. Fail securely.
4. Balance security and usability.
5. Log user actions.
6. Use redundancy and diversity to reduce risk.
7. Validate all inputs.
8. Compartmentalize your assets.
9. Design for deployment.
10. Design for recoverability.

#### Design for deployment

![software_deploy](res/software_deploy.png)

*Software deployment*

Four ways to incorporate deployment support in a system:

1. Include support for viewing and analyzing configurations.
2. Minimize default privileges.
3. Localize configuration settings.
4. Provide easy ways to fix security vulnerabilities.

### Security testing

Fundamentally, there are two reasons why security testing is so difficult:

1. Security requirements, like some safety requirements, are `shall not` requirements.
2. The people attacking a system are intelligent and are actively looking for vulnerabilities that they can exploit.

---



## Maintainability

Maintainability determines how easy and profitable it will be to maintain, update, and do upgrades in that software system. A largely maintainable system contains the following characteristics:

- Modularity
- Readability
- Error Handling
- Utilizes VCS
- Testability

### Measure

![maintanability_measure](res/maintanability_measure.png)

- Maintainability Index

  It provides an overall score that represents the maintainability of a specific component/Code module/Entire system.

- Code Churn

  It measures the frequency of changes to a code module over time using Version Control's data.

- Cyclomatic Complexity

  It measures the complexity of a code module.

- Time and Resource constraints

  It's important to balance between speed of development as well as speed of maintainability.

- Team Collaboration

- Documentation

  Good documentation reduces the learning curve for new Devs and helps the existing team understand it better during maintenance.

- Test Coverage

  It measures the extent to which automated tests cover the codebase, It helps prevent regressions from being introduced.

- Code Duplication

  The Percentage of duplicated code present in the system can be an indicator of maintainability.

### Achieve High Maintainability

![achieve_high_maintainability](res/achieve_high_maintainability.png)

- Follow Design Patterns

  Design patterns and SOLID principle promote modularity and flexibility.

- Code Consistency

  Well-written, readable code with meaningful variables, comments, and documentation makes maintenance tasks even smoother.

- Conduct Code Review

  Code reviews by peers, and maintainers can help in identifying potential issues early on, while making sure that code adheres to maintainability standards and preferred code style or not.

- Test-Driven Development(TDD)

  Adopting TDD ensures that test cases are written before the code implementation, helping developers understand the codebase easily while troubleshooting an issue.

- Documentation

  Good documentation reduces the learning curve for new Devs and helps the existing team understand it better during maintenance.

- Plan for Change

  Design the system in such a way, that makes it easier to add new features and adapt to evolving requirements of daily enhancements.

- Automate Testing and Deployment 

  Automating testing and deployment processes reduces the chance of human error helps maintain the stability of the system during updates and also save time and effort of team members, allowing them to work on important issues.

---



## Dependable Programming

There are some good practice guidelines for dependable programming:

1. Limit the visibility of information in a program.
2. Check all inputs for validity.
3. Provide a handler for all exceptions.
4. Minimize the use of error-prone constructs.
5. Provide restart capabilities.
6. Check array bounds.
7. Include timeouts when calling external components.
8. Name all constants that represent real-world values.

---



## REFERENCE

[1] Ian Sommerville. SOFTWARE ENGINEERING . 9th Edition

[2] [Availability in System Design](https://www.geeksforgeeks.org/system-design/availability-in-system-design/)

[3] [Reliability in System Design](https://www.geeksforgeeks.org/system-design/reliability-in-system-design/)

[4] [Essential Security Measures in System Design](https://www.geeksforgeeks.org/system-design/essential-security-measures-in-system-design/)
