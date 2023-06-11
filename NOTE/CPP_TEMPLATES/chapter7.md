# Chapter 7. Basic Template Terminology

<!-- vim-markdown-toc GFM -->

<!-- vim-markdown-toc -->



There is some confusion about how a class that is a template is called:

- The term class template states that the class is a template. That is, it is a parameterized description of a family of classes.
- The term template class on the other hand has been used
    + as a synonym for class template.
    + to refer to classes generated from templates.
    + to refer to classes with a name that is a template-id.

The process of creating a regular class, function, or member function from a template by substituting actual values for its arguments is called template instantiation. This resulting entity(class, function, or member function) is generically called a specialization.

partial specializations example:

```c++
template<typename T>
class MyClass<T, T> {...};

template<typename T> 
class MyClass<bool, T> {...};
```

A declaration is a C++ construct that introduces or reintroduces a name into a C++ scope. This introduction always includes a partial classification of that name, but the details are not required to make a valid declaration. 

the declaration of a class template or function template is called a definition if it has a body.

The One-Definition Rule(ODR):

- Noninline functions and member functions, as well as global variables and static data members, should be defined only once across the whole program.
- Class types(including struct and unions) and inline functions should be defined at most once per translation unit, and all these definitions should be identical.

A translation unit is what results from preprocessing a source file; that is, it includes the contents named by `#include` directives.

Template Arguments versus Template Parameters:

- Template parameters are those names that are listed after the keyword `template` in the template declaration or definition (`T` and `N` in our example).
- Template arguments are the items that are substituted for template parameters (`double` and `10` in our example). Unlike template parameters, template arguments can be more than just "names".



## Glossary

<div style="width: 50%; float:left;">synonym `/ˈsɪnənɪm/` 同义词</div>
<div style="width: 50%; float:left;">tied `/taɪd/` 系，打结，约束</div>
<div style="width: 50%; float:left;">substitution `/ˌsʌbstɪ'tjuːʃ(ə)n/` 置换，取代，代入</div>
<div style="width: 50%; float:left;">dramatic `/drəˈmætɪk/` 戏剧性的，巨大的，突然的，令人吃惊的</div>
<div style="width: 50%; float:left;">complex `/ˈkɒmplɛks/` 复杂的，难懂的</div>
