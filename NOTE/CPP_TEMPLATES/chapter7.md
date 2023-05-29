# Chapter 7. Basic Template Terminology


<!-- vim-markdown-toc GFM -->

* [7.1 "Class Template" or "Template Class"?](#71-class-template-or-template-class)
* [7,2 Instantiation and Specialization](#72-instantiation-and-specialization)
* [7.3 Declarations versus Definitions](#73-declarations-versus-definitions)
* [7.4 The One-Definition Rule](#74-the-one-definition-rule)
* [7.5 Template Arguments versus Template Parameters](#75-template-arguments-versus-template-parameters)

<!-- vim-markdown-toc -->



## 7.1 "Class Template" or "Template Class"?

There is some confusion about how a class that is a template is called:

- The term class template states that the class is a template. That is, it is a parameterized description of a family of classes.
- The term template class on the other hand has been used
    + as a synonym for class template.
    + to refer to classes generated from templates.
    + to refer to classes with a name that is a template-id.



## 7,2 Instantiation and Specialization

The process of creating a regular class, function, or member function from a template by substituting actual values for its arguments is called template instantiation. This resulting entity(class, function, or member function) is generically called a specialization.

partial specializations example:

```c++
template<typename T>
class MyClass<T, T> {...};

template<typename T> 
class MyClass<bool, T> {...};
```



## 7.3 Declarations versus Definitions

A declaration is a C++ construct that introduces or reintroduces a name into a C++ scope. This introduction always includes a partial classification of that name, but the details are not required to make a valid declaration. 

the declaration of a class template or function template is called a definition if it has a body.



## 7.4 The One-Definition Rule

- Noninline functions and member functions, as well as global variables and static data members should be defined only once across the whole program.
- Class types(including struct and unions) and inline functions should be defined at most once per translation unit, and all these definitions should be identical.

A translation unit is what results from preprocessing a source file; that is, it includes the contents named by `#include` directives.



## 7.5 Template Arguments versus Template Parameters

- Template parameters are those names that are listed after the keyword `template` in the template declaration or definition (`T` and `N` in our example).
- Template arguments are the items that are substituted for template parameters (`double` and `10` in our example). Unlike template parameters, template arguments can be more than just "names".



## Glossary

<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
