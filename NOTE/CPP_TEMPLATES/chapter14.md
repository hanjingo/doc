# Chapter 14. The Polymorphic Power of Templates



## 14.1 Dynamic Polymorphosm

`bastract base class (ABC)`



## 14.2 Static Polymorphism



## 14.3 Dynamic versus Static Polymorphism

**Terminology**

Dynamic and static polymorphism provide support for different C++ programming idioms:

- Polymorphism implemented via inheritance is bounded and dynamic:
  - Bounded means that the interfaces of the types participating in the polymorphic behavior are predetermined by the design of the common base class (other terms for this concept are invasive)。
  - Dynamic means that the binding of the interfaces is done at run time (dynamically).
- Polyporphism implemented via templates is unbounded and static:
  - Unbounded means that the interfaces of the types participating in the polymorphic behavior are not predetermined (other terms for this concept are noninvasive or nonintrusive).
  - Static means that the binding of the interfaces is done at compile time (statically).

**Strengths and Weaknesses**

Dynamic polymorphism in C++ exhibits the following strengths:

- Heterogeneous collections are handled elegantly.
- The executable code size is potentially smaller (because only one polymorphic function is needed, whereas distinct template instances must be generated to handle different types).
- Code can be entirely compiled; hence no implementation source must be published (distributing template libraries usually requires distribution of the source code of the template implementations).

In contrast, the following can be said about static polymorphism in C++:

- Collections of built-in types are easily implemented. More generally, the interface commonality need not be expressed through a common base class.
- Generated code is potentially faster (because no indirection through pointers is needed a priori and novirtual functions can be inlined much more often).
- Concrete types that provide only partial interfaces can still be used if only that part ends up being exercised by the application.



## 14.4 New Forms of Design Patterns



## 14.5 Generic Programming

Generic programming is a subdiscipline of computer science that deals with finding abstract representations of efficient algorithms, data structures, and other software concepts, and with their systematic organization... Generic programming focuses on representing families of domain concepts.



## 14.6 Afternotes

National Institutes of Health Class Library (NIHCL)

