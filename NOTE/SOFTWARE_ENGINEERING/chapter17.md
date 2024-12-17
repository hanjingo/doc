# 17 Component-based software engineering

[TOC]



The essentials of component-based software engineering are:

1. Independent components that are completely specified by their interfaces.
2. Component standards that facilitate the integration of components.
3. Middleware that provides software support for component integration.
4. A development process that is geared to component-based software engineering.

## Components and component models

![17_1](res/17_1.png)

*Component characteristics*

![17_2](res/17_2.png)

*Componenty interfaces*

![17_3](res/17_3.png)

*A model of a data collector component*

### Component models

![17_4](res/17_4.png)

*Basic elements of a component model*

The elements of a component model define the component interfaces, the information that you need to use the component in a program, and how a component should be deployed:

- Interfaces.
- Usage.
- Deployment.

The services provided by a component model implementation fall into two categories:

1. Platform services, which enable components to communicate and interoperate in a distributed environment.
2. Support services, which are common services that are likely to be required by many different components.

![17_5](res/17_5.png)

*Middleware services defined in a component model*



## CBSE processes

At the highest level, there are two types of CBSE processes:

1. Development for reuse.
2. Development with reuse.

![17_6](res/17_6.png)

*CBSE processes*

### CBSE for reuse

Make to a component to make it more reusable include:

- removing application-specific methods;
- changing names to make them more general;
- adding methods to provide more complete functional coverage;
- making exception handling consistent for all methods;
- adding a 'configuration' interface to allow the component to be adapted to different situations of use;
- integrating required components to increase independence.

### CBSE with reuse

![17_7](res/17_7.png)

*CBSE with reuse*



## Component composition

![17_10](res/17_10.png)

*Types of Component Composition*

Three types of incompatibility can occur:

1. `Parameter incompatibility` The operations on each side of the interface have the same name but their parameter types or the number of parameters are different.
2. `Operation incompatibility` The names of the operations in the 'provides' and 'requires' interfaces are different.
3. `Operation incompleteness` The `provides` interface of a component is a subset of the `required` interface of another component or vice versa.

![17_11](res/17_11.png)

*Components with incompatible interfaces*