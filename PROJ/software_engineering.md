# SOFTWARE ENGINEERING

[TOC]



## Requirements Engineering

Software system requirements are often classified as functional requirements or nonfunctional requirements:

1. `Functional requirements:` These are statements of services the system should provide, how the system should react to particular inputs, and how the system should behave in particular situations. In some cases, the functional requirements may also explicitly state what the system should not do.

2. `Non-functional requirements:` These are constraints on the services or functions offered by the system. They include timing constraints, constraints on the development process, and constraints imposed by standards.

   ![non_functional_requirements](res/non_functional_requirements.png)

   *Types of non-functional requirements*

### The Software Requirements Document

| Chapter | Description |
| ------- | ----------- |
|         |             |



---



## Software Process Models

The process models:

- `The waterfall model:` This takes the fundamental process activities of specification, development, validation, and evolution and represents them as separate process phases such as requirements specification, software design, implementation, testing, and so on.
- `Incremental development:` This approach interleaves the activities of specification, development, and validation. The system is developed as a series of versions(increments), with each version adding functionality to the previous version.
- `Reuse-oriented software engineering` This approach is based on the existence of a significant number of reusable components. The system development process focuses on integrating these components into a system rather than developing them from scratch.

### The Waterfall Model

![waterfall_model](res\waterfall_model.png)

*The waterfall model*

The principal stages of the waterfall model directly reflect the fundamental development activities:

1. Requirements analysis and definition
2. System and software design
3. Implementation and unit testing
4. Integration and system testing
5. Operation and maintenance

### Incremental Development

![incremental_development](res\incremental_development.png)

*Incremental development*

Incremental development has three important benefits, compared to the waterfall model:

1. The cost of accommodating changing customer requirements is reduced.
2. It is easier to get customer feedback on the development work that has been done.
3. More rapid delivery and deployment of useful software to the customer is possible, even if all of the functionality has not been included.

From a management perspective, the incremental approach has two problems:

1. The process is not visible.
2. System structure tends to degrade as new increments are added.

### Reuse-Oriented Software Engineering

![reuse_oriented_software_engineering](res\reuse_oriented_software_engineering.png)

*Reuse-oriented software engineering*

The intermediate stages in a reuse-oriented process are different:

- `Component analysis:` Given the requirements specification, a search is made for components to implement that specification.
- `Requirements modification:` During this stage, the requirements are analyzed using information about the components that have been discovered.
- `System design with reuse:` During this phase, the framework of the system is designed or an existing framework is reused.
- `Development and integration:` Software that cannot be externally procured is developed, and the components and COTS systems are integrated to create the new system.

---



## Software Process activities

### Software Specification

Software specification or requirements engineering is the process of understanding and defining what services are required from the system and identifying the constraints on the system's operation and development.

There are four main activities in the requirements engineering process:

1. `Feasibility study:` An estimate is made of whether the identified user needs may be satisfied using current software and hardware technologies. The study considers whether the proposed system will be cost-effective from a business point of view and if it can be developed within existing budgetary constraints.
2. `Requirements elicitation and analysis:` This is the process of deriving the system requirements through observation of existing systems, discussions with potential users and procurers, task analysis, and so on.
3. `Requirements specification:` Requirements specification is the activity of translating the information gathered during the analysis activity into a document that defines a set of requirements.
4. `Requirements validation:` This activity checks the requirements for realism, consistency, and completeness.

![requirement_engineering_proc](res\requirement_engineering_proc.png)

*The requirements engineering process*

### Software Design And Implementation

Four activities that may be part of the design process for information systems:

1. `Architectural design`, where you identify the overall structure of the system, the principal components (sometimes called sub-systems or modules), their relationships, and how they are distributed.
2. `Interface design`, where you define the interfaces between system components.
3. `Component design`, where you take each system component and design how it will operate.
4. `Database design`, where you design the system data structures and how these are to be represented in a database.

![design_proc](res\design_proc.png)

*A general model of the design process*

### Software Validation

The stages in the testing process are:

1. `Development testing` The components making up the system are tested by the people developing the system.
2. `System testing` System components are integrated to create a complete system.
3. `Acceptance testing` This is the final stage in the testing process before the system is accepted for operational use.

![stages_of_testing](res\stages_of_testing.png)

*Stages of testing*

![plan_driven_testing](res\plan_driven_testing.png)

### Boehm's Spiral Model

![boehm_spiral_model](res\boehm_spiral_model.png)

*Boehm's spiral model of the software process*

Each loop in the spiral is split into four sectors:

1. `Objective setting:` Specific objectives for that phase of the project are defined.
2. `Risk assessment and reduction.` For each of the identified project risks, a detailed analysis is carried out. Steps are taken to reduce the risk.
3. `Development and validation.` After risk evaluation, a development model for the system is chosen.
4. `Planning` The project is reviewed and a decision made whether to continue with a further loop of the spiral.

---



## Agile software development

Although there are many approaches to rapid software development, they share some fundamental characteristics:

1. The processes of specification, design, and implementation are interleaved.
2. The system is developed in a series of versions.
3. System user interfaces are often developed using an interactive development system that allows the interface design to be quickly created by drawing and placing icons on the interface.

### Agile methods

The principles of agile methods:

| Principle            | Description                                                  |
| -------------------- | ------------------------------------------------------------ |
| Customer involvement | Customers should be closely involved throughout the development process. Their role is to provide and prioritize new system requirements and to evaluate the iterations of the system. |
| Incremental delivery | The software is developed in increments, with the customer specifying the requirements to be included in each increment. |
| People not process   | The skills of the development team should be recognized and exploited. Team members should be left to develop their ways of working without prescriptive processes. |
| Embrace change       | Expect the system requirements to change and so design the system to accommodate these changes. |
| Maintain simplicity  | Focus on simplicity in both the software being developed and in the development process. Wherever possible, actively work to eliminate complexity from the system. |

### Plan-Driven And Agile Development

![plan_driven_and_agile_specification](res/plan_driven_and_agile_specification.png)

---



## REFERENCE

[1] Ian Sommerville. SOFTWARE ENGINEERING . 9th Edition
