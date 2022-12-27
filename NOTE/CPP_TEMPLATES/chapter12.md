# Chapter 12. Specialization and Overloading



## 12.1 When "Generic Code" Doesn't Quite Cut It

### 12.1.1 Transparent Customization

### 12.1.2 Semantic Transparency



## 12.2 Overloading Function Templates

In the previous section we saw that two function templates with the same name can coexist, even though they may be instantiated so that both have identical parameter types.

### 12.2.1 Signatures

Two functions can coexist in a program if they have distinct signatures. We define the signature of a function as the following information:

1. The unqualified name of the function (or the name of the function template from which it was generated).
2. The class or namespace scope of that name and, if the name has internal linkageg, the translation unit in which the name is declared.
3. The `const`, `volatile`, or `const volatile` qualification of the function(if it is a member function with such a qualifier).
4. The types of the function parameters (before template parameters are substituted if the function is generated from a function template).
5. Its return type, if the function is generated from a function template.
6. The template parameters and the template arguments, if the function is generated from a function template.

This means that the following templates and their instantiations could, in principle, coexist in the same program:

```c++
template<typename T1, typename T2>
void f1(T1, T2);

template<typename T1, typename T2>
void f1(T2, T1);

template<typename T>
long f2(T);

template<typename T>
char f2(T);
```

### 12.2.2 Partial Ordering of Overloaded Function Templates

### 12.2.3 Formal Ordering Rules

We then synthesize two artificial lists of argument types (or for conversion function templates, a return tyep) by substituting every template parameter as follows:

1. Replace each template type parameter with a unique "made up" type.
2. Replace each template template parameter with a unique "made up" class template.
3. Replace each nontype template parameter with a unique "made up" value of the appropriate type.

### 12.2.4 Templates and Nontemplates

Function templates can be overloaded with nontemplate functions. All else being equal, the nontemplate function is preferred in selecting the actual function being called.



## 12.3 Explicit Specialization

### 12.3.1 Full Class Template Specialization

A full specialization is introduced with a sequence of three tokens: `template`, `<` and `>`. In addition, the class name declarator is followed by the template arguments for which the specialization is declared.

### 12.3.2 Full Function Template Specialization

The syntax and principles behind (explicit) full function template specialization are much the same as those for full class template specialization, but overloading and argument deduction come into play.

The full specialization declaration can omit explicit template arguments when the template being specialized can be determined via argument deduction (using as argument types the parameter types provided in the declaration) and partial ordering.

A full function template specialization cannot include default argument values. However, any default arguments that were specified for the template being specialized remain applicable to the explicit specialization.

A full specialization is in many ways similar to a normal declaration (or rather, a normal redeclaration). In particular, it does not declare a template, and therefore only one definition of a noninline full function template specialization should appear in a program. However, we must still ensure that a declaration of the full specialization follows the template to prevent attempts at using the function generated from the template. The declarations for template `g` in the previous example would therefore typically be organized in two files.

### 12.3.3 Full Member Specialization

Not only member templates, but also ordinary static data members and member functions of class templates, can be fully specialized. The syntax requires `template<>` prefix for every enclosing class templat. If a member template is being specialized, a `template<>` must also be added to denote it is being specialized.

