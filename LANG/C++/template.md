# C++ Templates

[TOC]



Templates are C++'s mechanism for generic, compile-time polymorphism. They let you write functions and classes that operate on unspecified types. Unlike run-time polymorphism (virtual functions), templates are resolved at compile time, enabling highly optimized and type-safe code.

## Quick summary (contract)
- Inputs: type and value template parameters; function/class usage sites.
- Outputs: compiler-generated instantiations of functions/classes.
- Error modes: failed deduction, substitution failure (SFINAE), ambiguous overloads, two-phase lookup surprises.



## Function templates

Function templates define families of functions parametrized by types (and sometimes values). Key points:

- Declare template parameters with `template<>`, e.g. `template<typename T>`.
- Template arguments are usually deduced from call arguments; you can also explicitly provide them (`f<int>(...)`).
- Function templates can be overloaded; non-template overloads are preferred when equally viable.

Example:

```c++
inline int const& max(int const& a, int const& b) { return a < b ? b : a; }

template <typename T>
inline T const& max(T const& a, T const& b) { return a < b ? b : a; }

template <typename T>
inline T const& max(T const& a, T const& b, T const& c) { return max(max(a, b), c); }
```

Notes:
- Default template arguments are common for class templates; for function templates, template-argument deduction typically makes defaults unnecessary.
- Prefer `typename` for type template parameters in modern code for clarity.



## Class templates

Class templates parametrize classes by types or values. You instantiate them by supplying template arguments (`Stack<int>`).

Example:

```c++
template<typename T, typename Container = std::vector<T>>
class Stack {
public:
  void push(T const& elem) { elems.push_back(elem); }
  void pop() { elems.pop_back(); }
  T& top() { return elems.back(); }
private:
  Container elems;
};
```

Key points:
- Class templates may have default template arguments.
- You can fully specialize a class template for a particular argument list: `template<> class Stack<std::string> { ... };` (specialized members must be provided).
- Partial specialization is allowed for class templates (not for function templates): `template<typename T> class MyClass<T*, T*> { ... };`.



## Kinds of template parameters

1. Type parameters: `template<typename T>`.
2. Non-type parameters: compile-time constants like `int N` or pointers; e.g. `template<typename T, int N>`.
3. Template-template parameters: parameters that accept other templates, e.g. `template<template<typename> class C>`.

Restrictions:
- Non-type parameters are typically integral values, pointers, references, or enums. Floating-point and class-type nontype parameters are not supported.



## Dependent names and `typename`

When a name depends on a template parameter (dependent name) and denotes a type, prefix it with `typename`: `typename T::value_type`.

Use `template` to disambiguate dependent template members when necessary: `X<T>::template rebind<U>`.

## Template argument deduction

Deduction rules in brief:

- Arrays and functions decay to pointers during deduction.
- Top-level `const`/`volatile` qualifiers are ignored.
- Qualified type names and certain non-type expressions are not deduced.

If deduction fails, provide explicit template arguments or use overloads. SFINAE enables graceful exclusion of templates during overload resolution.



## Instantiation and two-phase lookup

Instantiation substitutes template arguments to produce concrete code. Two-phase lookup means:

1. First phase: parse template and perform non-dependent name lookup.
2. Second phase: at instantiation, resolve dependent names.

This separation can cause surprising lookup behaviour; use explicit qualification, `this->`, or `typename`/`template` to resolve ambiguities.



## Specialization and overloading

- Full specialization: provide an alternative implementation for specific template arguments: `template<> class Foo<int> { ... };`.
- Partial specialization: adjust class-template behavior for a range of argument patterns.
- Function templates: prefer overloads or SFINAE over explicit specializations in most cases.

Overload resolution prefers non-template functions when they are otherwise equally good matches.



## Practical tips and pitfalls

- Use `typename` correctly for dependent types; missing `typename` is a common compile error.
- Remember two-phase lookup; qualifying dependent names can avoid subtle errors.
- Keep templates readable: prefer clear naming and small responsibilities.
- Use standard library traits and helper utilities (e.g., `<type_traits>`) rather than reinventing type checks.



## Short examples

Function with a nontype default:

```c++
template<typename T, int VAL = 6>
T addValue(T const& x) { return x + VAL; }

int x = addValue<int, 3>(4); // 7
```

Template-template parameter:

```c++
template<template<typename, typename> class Container, typename T>
class Wrapper { Container<T, std::allocator<T>> c; };
```

Edited for clarity, corrected typos (e.g., `tempalte` → `template`), and reorganized topics for easier reading.

```c++
class S<int, I*2>; // error

template<typename U, int K>
class S<U, K>;     // error
```

---



## Polymorphic Templates

Dynamic and static polymorphism provide support for different C++ programming idioms:

- Polymorphism implemented via inheritance is bounded and dynamic:
  - Bounded means that the interfaces of the types participating in the polymorphic behavior are predetermined by the design of the common base class (other terms for this concept are invasive)。
  - Dynamic means that the binding of the interfaces is done at run time (dynamically).
- Polymorphism implemented via templates is unbounded and static:
  - Unbounded means that the interfaces of the types participating in the polymorphic behavior are not predetermined (other terms for this concept are noninvasive or nonintrusive).
  - Static means that the binding of the interfaces is done at compile time (statically).

Dynamic polymorphism in C++ exhibits the following strengths:

- Heterogeneous collections are handled elegantly.
- The executable code size is potentially smaller (because only one polymorphic function is needed, whereas distinct template instances must be generated to handle different types).
- Code can be entirely compiled; hence, no implementation source must be published (distributing template libraries usually requires distribution of the source code of the template implementations).

In contrast, the following can be said about static polymorphism in C++:

- Collections of built-in types are easily implemented. More generally, the interface commonality need not be expressed through a common base class.
- Generated code is potentially faster (because no indirection through pointers is needed a priori, and non-virtual functions can be inlined much more often).
- Concrete types that provide only partial interfaces can still be used if only that part ends up being exercised by the application.

Generic programming is a subdiscipline of computer science that deals with finding abstract representations of efficient algorithms, data structures, and other software concepts, and with their systematic organization... Generic programming focuses on representing families of domain concepts.



## Templates and Inheritance

The designers of C++ had various reasons to avoid zero-size classes.

However, even though there are no zero-size types in C++, the C++ standard does specify that when an empty class is used as a base class, no space needs to be allocated for it, provided that it does not cause it to be allocated to the same address as another object or subobject of the same type.

empty base class optimization (or EBCO) means in practice:

```c++
#include <iostream>

class Empty{
    typedef int Int;
};

class EmptyToo : public Empty {
};

class EmptyThree : public EmptyToo {
};
```

*Curiously Recurring Template Pattern (CRTP)*: This oddly named pattern refers to a general class of techniques that consists of passing a derived class as a template argument to one of its own base classes. In it's simplest form, C++ code for such a pattern looks as follows:

```c++
template <typename Derived>
class CuriousBase {
    ...
};

class Curious : public CuriousBase<Curious> {
    ...
};
```

C++ allows us to parameterize directly three kinds of entities through templates: types, constants("nontypes"), and templates. However, indirectly, it also allows us to parameterize other attributes such as the virtuality of a member function.



## Type Classification

It is sometimes useful to be able to know whether a template parameter is a built-in type, a pointer type, or a class type, and so forth. 

The problem with function types is that, because of the arbitrary number of parameters, there isn't a finite syntactic construct using template parameters that describes them all:

- provide partial specializations for functions with a template argument list that is shorter than a chosen limit

  ```c++
  template<typename R>
  class Compoud<R()>{...}
  
  template<typename R, typename P1>
  class Compoud<R(P1, ...)>{...}
  ```

- uses the SFINAE(substitution-failure-is-not-an-error) principle: An overloaded function template can be followed by explicit template arguments that are invalid for some of the templates:

  ```c++
  template<typename U> static char test(...);
  template<typename U> static int test(U(*)[1]);
  enum {Yes = sizeof(test<T>(0) == 1)};s
  ```



## Smart Pointers

In C++, smart pointers are classes that behave somewhat like ordinary pointers(in that they provide the dereferencing operators `->` and `*`) but in addition, encapsulate some memory or resource management policy.


two different ownership models:

- `exclusive`: Exclusive ownership can be enforced with little overhead, compared with handling raw pointers. Smart pointers that enforce such a policy are useful to deal with exceptions thrown while manipulating dynamically allocated objects.
- `shared`: Shared ownership can sometimes lead to excessively complicated object lifetime situations. In such cases, it may be advisable to move the burden of the lifetime decisions from the programmer to the program.

Built-in pointers are subject to several implicit conversions:

- Conversion to `void*`
- Conversion to a pointer to a base subobject of the object pointed to
- Conversion to `bool`(`false` if the pointer is null, `true` otherwise)

Other drawbacks to implicit conversions to built-in pointer types include(assume `cp` is a counting pointer):

- `delete cp;` and `::delete cp;` become valid
- All sort of meaningless pointer arithmetic goes undiagnosed (for example, `cp[n], cp2 - cp1`, and so forth)



## Functor

The outline is not sufficient when it comes to virtual functions, and in practice, many implementations use a three-word structure for pointers to member functions:

1. The address of the member function, or `NULL` if it is a virtual function
2. The required `this` adjustment
3. A virtual function index

pass functors as function call arguments, this allows the caller to construct the function object(possibly using a nontrivial constructor) at run time.

In our framework, we handle only class-type functors and require them to provide the following information:

- The number of parameters of the functor(as a member enumerator constant `NumParams`)
- The type of each parameter(through member typedefs `Param1T, Param2T, Param3T, ...`)
- The return type of the functor(through a member typedef `Return T`)

The argument to be passed to the underlying functor can be one of three different values:

- The corresponding parameter of the bound functor
- The bound value
- The parameter of the bound functor is one position to the left of the argument we must pass



## Tricky Basics

The keyword `typename` was introduced during the standardization of C++ to clarify that an identifier inside a template is a type. Consider the following example:

```c++
template <typename T>
class MyClass{
    typename T::SubType *ptr;
    ...
};
```

Here, the second `typename` is used to clarify that `SubType` is a type defined within class  `T`. Thus, `ptr` is a pointer to the type `T::SubType`.

Without `typename`, `SubType` would be considered a static member. Thus it would be a concrete variable or object As a result, the expression 

`T::SubType *ptr` 

would be a multiplication of the static `SubType` member of class `T` with `ptr`.

A very similar problem was discovered after the introduction of `typename`. Consider the following example using the standard `bitset` type:

```c++
template <int N>
void printBitset(std::bitset<N> const& bs)
{
    std::cout << bs.template to_string<char, char_traits<char>, allocator<char> >();
}
```

In conclusion, the `.template` notation (and similar notations such as `->template`) should be used only inside templates and only if they follow something that depends on a template parameter.

For class templates with base classes, using a name `x` by itself is not always equivalent to `this->x`, even though a member `x` is inherited.

```c++
template <typename T>
class Derived : public Base<T> {...}
```

Class members can also be templates. This is possible for both nested classes and member functions.

```c++
template <typename T>
class Stack {
    template<typename T2>
    Stack<T>& operator=(Stack<T2> const& );
};

template <typename T>
template <typename T2>
Stack<T>& Stack<T>::operator=(Stack<T2> const& op2) {
    ...
}
```

Template template parameters examples:

```c++
template <typename T, 
    template<typeanme ELEM, 
    typename ALLOC = std::allocator<ELEM>>
    class CONT> // class only
class Stack{
    public:
        Stack(){}
        Stack(Stack<T, CONT> const &);
        ~Stack(){}
        Stack<T, CONT> operator=(Stack<T, CONT> const &);
    private:
        CONT<T> elems;
};
```

For funcamental types such as `int`, `double`, or pointer types, there is no default constructor that initializes them with a useful default value. Instead, any noninitialized local variable has a undefined value:

```c++
template <typename T>
void foo()
{
    T x = T();
}

```

The explanation for this behavior is that during argument deduction array-to-pointer conversion(often called decay) occurs only if the parameter does not have a reference type. This is demonstrated by the following program:

```c++
template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b ? b : a;
}

std::string s;
::max("apple", "peach");  // OK
::max("apple", "tomato"); // ERROR
::max("apple", s);        // ERROR

```

- use nonreferences instead of references (however, this can lead to unnecessary copying)

- overload using both reference and nonreference parameters(however, this might lead to ambiguities)

- overload with concrete types(such as `std::string`)

- overload with array types types, for example:

  ```c++
  template<typename T, int N, int M>
  T const* max(T const (&a)[N], T const (&b)[M])
  {
      return a < b ? b : a;
  } 
  ```

- force application programmers to use explicit conversions



## Notice

- All three correspond to definitions of members of class templates:

  1. Definitions of member functions of class templates
  2. Definitions of nested class members of class templates
  3. Definitions of static data members of class templates

- Member function templates cannot be declared virtual. This constraint is imposed because the usual implementation of the virtual function call mechanism uses a fixed-size table with one entry per virtual function. However, the number of instantiations of a member function template is not fixed until the entire program has been translated.

- Every template must have a name and that name must be unique within its scope, except that function templates can be overloaded. Note especially that, unlike class types, class templates cannot share a name with a different kind of entity:

  ```C++
  int c;
  class c; // correct
  
  int x;
  template <typename T>
  class x; // error
  
  struct s;
  template <typename T>
  class s; // error
  ```

- Template names have linkage, but they cannot have C linkage.

- Normal declarations of templates declare so-called primary templates. Such template declarations are declared without adding template arguments in angle brackets after the template name:

  ```c++
  template <typename T> class Box;    // correct
  
  template <typename T> class Box<T>; // error
  
  template <typename T> void translate(T*);    // correct
  
  template <typename T> void translate<T>(T*); // error
  ```
  
- Nontype template parameters are declared much like variables, but they cannot have nontype specifiers like `static`, `mutable`, and so forth. They can have `const` and `volatile` qualifiers, but if such a qualifier appears at the outermost level of the parameter type, it is simply ignored.
- Non-type parameters are always rvalues: Their address cannot be taken, and they cannot be assigned to.
- Template template parameters are placeholders for class templates. They are declared much like class templates, but the keywords `struct` and `union` cannot be used.
- Template arguments for a function template can be specified explicitly or deduced from the way the template is used.

  ```c++
  template <typename Func, typename T>
  void apply(Func f, T x) {
      f(x);
  }
  
  template <typename T> void multi(T t) {
      cout << 1 << ": " << t << endl;
  }
  
  template <typename T> void multi(T *t) {
      cout << 2 << ": " << *t << endl;
  }
  
  int i = 3;
  apply(&multi<int>, i); // SFINAE
  ```

  This "substitution-failure-is-not-an-error"(SFINAE) principle is clearly an important ingredient to make the overloading of function templates practical. However, it also enables remarkable compile-time techniques.
- Template type arguments are the "values" specified for template type parameters. Most commonly used types can be used as template arguments, but there are two exceptions:

  - Local classes and enumerations(in other words, types declared in a function definition) cannot be involved in template type arguments.
  - Types that involve unnamed class types or unnamed enumeration types cannot be template type arguments(unnamed classes or enumerations that are given a name through a typedef declaration are OK).
- Nontype template arguments are the values substituted for nontype parameters. Such a value must be one of the following things:

  - Another nontype template parameter that has the right type
  - A compile-time constant value of integer(or enumeration) type. This is acceptable only if the corresponding parameter has a type that matches that of the value, or a type to which the value can be implicitly converted(for example, a `char` can be provided for an `int` parameter).
  - The name of an external variable or function preceded by the built-in unary `&` ("address of") operator. For functions and array variables, `&` can be left out. Such template arguments match nontype parameters of a pointer type.
  - The previous kind of argument, but without a leading `&` operator, is a valid argument for a non-type parameter of reference type.
  - A pointer-to-member constant; in other words, an expression of the form `&C::m` where `C` is a class type and `m` is a nonstatic member (data or function). This matches nontype parameters of a pointer-to-member type only.
- there are some constant values that are, perhaps surprisingly, not currently valid:

  - Null pointer constants
  - Floating-point numbers
  - String literals
- Two sets of template arguments are equivalent when values of the arguments are identical one-for-one.
- This has two important consequences for class members:

  1. A function generated from a member function template never overrides a virtual function.
  2. A constructor generated from a constructor template is never a default copy constructor.(Similarly, an assignment generated from an assignment template is never a copy-assignment operator. However, this is less prone to problems because unlike copy constructors, assignment operators are never called implicitly.)
- Friends:

  1. A friend declaration may be the only declaration of an entity.
  2. A friend function declaration can be a definition.
- If the name is not followed by angle brackets, there are two possibilities:

  1. If the name isn't qualified (in other words, it doesn't contain a double colon), it never refers to a template instance. If no matching nontemplate function is visible at the point of the friend declaration, the friend declaration is the first declaration of that function. The declaration could also be a definition.
  2. If the name is qualified (it contains `::`), the name must refer to a previously declared function or function template. A matching function is preferred over a matching function template. However, such a friend declaration cannot be a definition.

  ```c++
  void multiply(void*);
  template<typename T>
  void multiply(T);
  class Comrades {
     friend void multiply(int){}
     friend void ::multiply(void*);
     friend void ::multiply(int);
     friend void ::multiply<double*>(double*);
     friend void ::error(){}
  };
  ```

  two different instantiations create two identical definitions-a direct violation of the ODR。

  Friend Templates:

  ```c++
  class Manager{
      template<typename T>
      friend int ticket(){}
  };
  ```
  
- Template argument deduction applies exclusively to function and member function templates. In particular, the arguments for a class template are not deduced from the arguments to a call of one of its constructors. For example:

  ```c++
  template<typename T>
  class S {
      public:
      	S(T b) : a(b) {}
      private:
      	T a;
  };
  
  S x(12); // error
  ```

- Even when a default call argument is not dependent, it cannot be used to deduce template arguments. This means that the following is invalid C++:

  ```c++
  template<typename T>
  void f(T x = 42){...}
  int main()
  {
      f<int>(); // correct；T=int
      f();      // error
  }
  ```




## Reference

[1] C++ Templates: The Complete Guide. David Vandevoorde, Nicolai M. Josuttis . 2004
