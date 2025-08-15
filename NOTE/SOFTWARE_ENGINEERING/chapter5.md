# 5 System modeling

[TOC]



## Behavioral models

Behavioral models are models of the dynamic behavior of the system as it is executing. They show what happens or what is supposed to happen when a system responds to a stimulus from its environment. You can think of these stimuli as being of two types:

1. `Data` Some data arrives that has to be processed by the system.
2. `Events` Some event happens that triggers system processing. Events may have associated data but this is not always the case.



## Model-driven engineering

## Model-driven architecture

The MDA(model-driven architecture) method recommends that three types of abstract system models should be produced:

1. A computation-independent model (CIM) that models the important domain abstractions used in the system.
2. A platform-independent model (PIM) that models the operation of the system without reference to its implementation.
3. Platform-specific models (PSM) which are transformations of the platform-independent model, with a separate PSM for each application platform.

![5_19](res/5_19.png)

*Multiple platform-specific models*

### Executable UML

To create an executable sub-set of UML, the number of model types has therefore been dramatically reduced to three key model types:

1. Domain models identify the principal concerns in the system. These are defined using UML class diagrams that include objects, attributes, and associations.
2. Class models, in which classes are defined, along with their attributes and operations.
3. State models, in which a state diagram is associated with each class and is used to describe the lifecycle of the class.
