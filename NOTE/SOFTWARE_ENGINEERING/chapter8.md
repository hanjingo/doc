# 8 Software testing

[TOC]



The testing process has two distinct goals:

1. To demonstrate to the developer and the customer that the software meets its requirements.
2. To discover situations in which the behavior of the software is incorrect, undesirable, or does not conform to its specification.

![8_1](res/8_1.png)

*An input-output model of program testing*

![8_2](res/8_2.png)

*Inspections and testing*

![8_3](res/8_3.png)

*A model of the software testing process*

Typically, a commercial software system has to go through three stages of testing:

1. Development testing, where the system is tested during development to discover bugs and defects.
2. Release testing, where a separate testing team tests a complete version of the system before it is released to users.
3. User testing, where users or potential users of a system test the system in their own environment.



## Development testing

During development, testing may be carried out at three levels of granularity:

1. Unit testing, where individual program units or object classes are tested.
2. Component testing, where several individual units are integrated to create composite components.
3. System testing, where some or all of the components in a system are integrated and the system is tested as a whole.

### Unit testing

When you are testing object classes, you should design your tests to provide coverage of all of the features of the object. This means that you should:

- test all operations associated with the object;
- set and check the value of all attributes associated with the object;
- put the object into all possible states. This means that you should simulate all events that cause a state change.

An automated test has three parts:

1. A setup part, where you initialize the system with the test case, namely the inputs and expected outputs.
2. A call part, where you call the object or method to be tested.
3. An assertion part where you compare the result of the call with the expected result.

### Choosing unit test cases

Testing is expensive and time-consuming, so it is important that you choose effective unit test cases. Effectiveness, in this case, means two things:

1. The test cases should show that, when used as expected, the component that you are testing does what it is supposed to do.
2. If there are defects in the component, these should be revealed by test cases.

Two possible strategies here that can be effective in helping you choose test cases. There are:

1. Partition testing, where you identify groups of inputs that have common characteristics and should be processed in the same way.
2. Guideline-based testing, where you use testing guidelines to choose test cases.

![8_5](res/8_5.png)

*Equivalence partitioning*

### Component testing

There are different types of interfaces between program components and, consequently, different types of interface errors that can occur:

1. `Parameter interfaces` These are interfaces in which data or sometimes function references are passed from one component to another.
2. `Shared memory interfaces` These are interfaces in which a block of memory is shared between components.
3. `Procedural interfaces` These are interfaces in which one component encapsulates a set of procedures that can be call ed by other components.
4. `Message passing interfaces` These are interfaces in which one component requests a service from another component by passing a message to it.

Interface errors are one of the most common forms of error in complex systems. These errors fall into three classes:

- `Interface misuse` A calling component calls some other component and makes an error in the use of its interface.
- `Interface misunderstanding` A calling component misunderstands the specification of the interface of the called component and makes assumptions about its behavior.
- `Timing errors` These occur in real-time systems that use a shared memory or a message-passing interface.

Some general guidelines for interface testing are:

1. Examine the code to be tested and explicitly list each call to an external component.
2. Where pointers are passed across an interface, always test the interface with null pointer parameters.
3. Where a component is called through a procedural interface, design tests that deliberately cause the compoonent to fail.
4. Use stress testing in message-passing systems.
5. Where several components interact through shared memory, design tests that vary the order in which these components are activated.



## Test-driven development

![8_9](res/8_9.png)

*Test-driven development*

As well as better problem understanding, other benefits of test-driven development are:

1. `Code coverage` In principle, every code segment that you write should have at least one associated test.
2. `Regression testing` A test suite is developed incrementally as a program is developed.
3. `Simplified debugging` When a test fails, it should be obvious where the problem lies.
4. `System documentation` The tests themselves act as a form of documentation that describes what the code should be doing.



## Release testing

There are two important distinctions between release testing and system testing during the development process:

1. A separate team that has not been involved in the system development should be responsible for release testing.
2. System testing by the development team should focus on discovering bugs in the system (defect testing). The objective of release testing is to check that the system meets its requirements and is good enough for external use (validation testing).



## User testing

In practice, there are three different types of user testing:

1. Alpha testing, where users of the software work with the development team to test the software at the developer's site.
2. Beta testing, where a release of the software is made available to users to allow them to experiment and to raise problems that they discover with the system developers.
3. Acceptance testing, where customers test a system to decide whether or not it is ready to be accepted from the system developers and deployed in the customer environment.

![8_11](res/8_11.png)

*The acceptance testing process*

There are six stages in the acceptance testing process:

1. `Define acceptance criteria` This stage should, ideally, take place early in the process before the contract for the system is signed.
2. `Plan acceptance testing` This involves deciding on the resources, time, and budget for acceptance testing and establishing a testing schedule.
3. `Derive acceptance tests` Once acceptance criteria have been established, tests have to be designed to check whether or not a system is acceptable.
4. `Run acceptance tests` The agreed acceptance tests are executed on the system.
5. `Negotiate test results` It is very unlikely that all of the defined acceptance tests will pass and that there will be no problems with the system.
6. `Reject/accept system` This stage involves a meeting between the developers and the customer to decide on whether or not the system should be accepted.