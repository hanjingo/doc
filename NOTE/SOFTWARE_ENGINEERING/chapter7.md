# 7 Design and implementation

[TOC]



## Object-oriented design using the UML

To develop a system design from concept to detailed, object-oriented design, there are several things that you need to do:

1. Understand and define the context and the external interactions with the system.
2. Design the system architecture.
3. Identify the principal objects in the system.
4. Develop design models.
5. Specify interfaces.

### System context and interactions

System context models and interaction models present complementary views of the relationships between a system and its environment:

1. A system context model is a structural model that demonstrates the other systems in the environment of the system being developed.
2. An interaction model is a dynamic model that shows how the system interacts with its environment as it is used.

### Design models

When you use the UML to develop a design, you will normally develop two kinds of design models:

1. Structural models, which describe the static structure of the system using object classes and their relationships.
2. Dynamic models, which describe the dynamic structure of the system and show the interactions between the system objects.

In the early stages of the design process, I think there are three models that are particularly useful for adding detail to use case and architectural models:

1. Subsystem models, which that show logical groupings of objects into coherent subsystems. These are represented using a form of class diagram with each subsystem shown as a package with enclosed objects. Subsystem models are static (structural) models.
2. Sequence models, which show the sequence of object interactions. These are represented using a UML sequence or a collaboration diagram. Sequence models are dynamic models.
3. State machine model, which show how individual objects change their state in response to events. There are represented in the UML using state diagrams. State machine models are dynamic models.



## Implementation issues

### Reuse

Software reuse is possible at a number of different levels:

1. The abstraction level
2. The object level
3. The component level
4. The system level

There are costs associated with reuse:

1. The costs of the time spent in looking for software to reuse and assessing whether or not it meets your needs.
2. Where applicable, the costs of buying the reusable software.
3. The costs of adapting and configuring the reusable software components or systems to reflect the requirements of the system that you are developing.
4. The costs of integrating reusable software elements with each other (if you are using software from different sources) and with the new code that you have developed.

### Configuration management

Three fundamental configuration management activities:

1. Version management
2. System integration
3. Problem tracking

### Host-target development

For distributed systems, you need to decide on the specific platforms where the components will be deployed. Issues that you have to consider in making this decision are:

1. The hardware and software requirements of a component.
2. The availability requirements of the system.
3. Component communications.



## Open source development

Most open-source licenses are derived from one of three general models:

1. The GNU General Public License (GPL).
2. The GNU Lesser General Public License (LGPL).
3. The Berkley Standard Distribution (BSD) License.

