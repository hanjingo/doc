# C++ Template

[TOC]



Templates are a solution to the problem that there are functions or classes written for one or more types not yet specified. When you use a template, you pass the types as arguments, explicitly or implicitly. Because templates are language features, you have full support for type checking and scope.

## Function Templates

Function templates provide a functional behavior that can be called for different types.

Function templates have two kinds of parameters:

1. Template parameters, which are declared in angle brackets before the function template name:

   ```c++
   template<typename T>
   ```

2. Call parameters, which are declared in parentheses after the function template name:

   ```c++
   max(T const& a, T const& b)
   ```

specify the template argument list explicitly:

1. in function templates(unlike class templates) no default template arguments can be specified.

   ```c++
   template <typename T1, typename T2, typename RT>
   inline RT max(T1 const& a, T2 const& b);
   max<int, double, double>(4, 4, 2);
   ```

2. Instantiate a template explicitly for certain types:

   ```c++
   template<typename RT, typename T1, typename T2>
   inline RT max(T1 const& a, T2 const& b);
   max<double>(4, 4.2);
   ```

Like ordinary functions, function templates can be overloaded. That is, you can have different function definitions with the dame function name so that when that name is used in a function call, a C++ compiler must decide which one of the various candidates to call:

```c++
inline int const& max(int const& a, int const& b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c)
{
    return ::max(::max(a, b), c);
}
```

---



## Class Templates

Declaration of Class Templates:

```c++
template<typename T>
class Stack{
    Stack(Stack<T> const&);
    ~Stack();
    Stack<T> operator=(Stack<T> const &);
};
```


To use an object of a class template, you must specify the template arguments explicitly.

Template arguments may be any type:

1. The only requirement is that any operation that is called is possible according to this type.
2. Note that you have to put whitespace between the two closing template brackets.

You can specialize a class template for certain template arguments. Similar to the overloading of function templates, specializing class templates allows you to optimize implementations for certain types or to fix a misbehavior of certain types for an instantiation of the class template.

```c++
template<>
class Stack<std::string> {
    ...
}
```

**warning:**

1. If you specialize a class template, you must also specialize all member functions.
2. It does demonstrate that the implementation of specialization might look very different from the implementation of the primary template.

Class templates can be partially specialized. You can specify special implementations for particular circumstances, but some template parameters must still be defined by the user:

```c++
template <typename T>
class MyClass<T, int> {
    ...
};

template<typename T>
class MyClass<T, T> {
    ...
};

template <typename T>
class MyClass<T*, T*> {
    ...
};

MyClass<int, int> m;
MyClass<int*, int*> m;
```

For class templates you can also define default values for template parameters. These values are called `default template arguments`. They may even refer to previous template parameters:

```c++
tempalte <typename T, typename CONT = std::vector<T> >
class Stack {
    private:
        CONT elems;
    ...
};

template <typename T, typename CONT>
void Stack<T, CONT>::push(T const& elem)
{
    elems.push_back(elem);
}

Stack<double, std::deque<double> > s;
s.push(1.1);
```

---



## Template Paramters

There are three kinds of template parameters:

1. Type parameters(these are by far the most common)
2. Nontype parameters
3. Template template parameters

### Type parameters

Type parameters are introduced with either the keyword `typename` or the keyword `class`: The two are entirely equivalent. The keyword must be followed by a simple identifier, and that identifier must be followed by a comma to denote the start of the next parameter declaration, a closing angle bracket (>) to denote the end of the parameterization clause, or an equal sign (=) to denote the beginning of a default template argument.

### Nontype Template Paramters

Nontype template parameters stand for constant values that can be determined at compile or link time. The type of such a parameter(in other words, the type of the value for which it stands) must be one of the following:

- An integer type or an enumeration type
- A pointer type(including regular object pointer types, function pointer types, and pointer-to-member types)
- A reference type(both references to objects and references to functions are acceptable)

Default values for the template parameters can be specified:

```c++
template <typename T, int MAXSIZE=66>
class Stack{
    ...
}
```

You can also define nontype parameters for function templates. For example, the following function template defines a group of functions for which a certain value can be added:

```c++
template <typename T, int VAL = 6>
T addValue(T const& x) {
    return x + VAL;
}
```

Note that nontype template parameters carry some restrictions. In general, they may be constant integral values(including enumerations) or pointers to objects with external linkage.

Floating-point numbers and class-type objects are not allowed as nontype template parameters:

```c++
// error
template <double VAT>
double f(double d)
{
    return d * VAT;
}

// error
template <std::string name>
class MyClass {
    ...
};

// error
template <char const* name>
class MyClass {
    ...
};
```

### Template template parameters

---



## Names in Templates

| Classification         | Explanation and Notes                                        |
| ---------------------- | ------------------------------------------------------------ |
| Identifier             | A name that consists solely of an uninterrupted sequence of letters, underscores(`_`), and digits. It cannot start with a digit, and some identifiers are reserved for the implementation: You should not introduce them in your programs(as a rule of thumb, avoid leading underscores and double underscores). The concept of "letter" should be taken broadly and includes special universal character names (UCNs) that encode glyphs from non-alphabetical languages. |
| Operator-function-id   | The keyword `operator` followed by the symbol for an operator -- for example, `operator new` and `operator []`. Many operators have alternative representations. For example, `operator &` can equivalently be written as `operator bit and` even when it denotes the unary address of operator. |
| Conversion-function-id | Used to denote user-defined implicit conversion operator -- for example, `operator int &`, which could also be obfuscated as `operator int bit and`. |
| Template-id            | The name of a template followed by template arguments enclosed in angle brackets; for example, `List<T, int, 0>`(Strictly speaking, the C++ standard allows only simple identifiers for the template name of a template-id. However, this is probably an oversight and an operator-function-id should be allowed too; e.g. `operator+<X<int>>`.) |
| Unqualified-id         | The generalization of an identifier. It can be any of the above(identifier, operator-function-id, conversion-function-id or template-id) or a "destructor name"(for example, notations like `~Data` or `~List<T, T, N>`). |
| Qualified-id           | An unqualified ID that is qualified with the name of a class or namespace, or just with the global scope resolution operator. Note that such a name itself can be qualified. Examples are `::X`, `S::x`, `Array<T>::y`, and `::N::A<T>::z`. |
| Qualified name         | This term is not defined in the standard, but we use it to refer to names that undergo so-called `qualified lookup`. Specifically, this is a qualified-id or an unqualified-id that is used after an explicit member access operator (`.` or `->`). Examples are `S::x`, `this->f`, and `p->A::m`. However, just `class_mem` in a context that is implicitly equivalent to `this->class_mem` is not a qualified name: The member access must be explicit. |
| Unqualified name       | An unqualified-id that is not a qualified name. This is not a standard term but corresponds to names that undergo what the standard call `unqualified lookup`. |
| Dependent name         | A name that depends in some way on a template parameter. Certainly any qualified or unqualified name that explicitly contains a template parameter is dependent. Furthermore, a qualified name that is qualified by a member access operator (`.` or `->`) is dependent if the type of the expression on the left of the access operator depends on a template parameter. In particular, `b` in `this->b` is a dependent name when it appears in a template. Finally, the identifier `ident` in a call of the form `ident(x, y, z)` is a dependent name if and only if any of the argument expressions has a type that depends on a template parameter. |
| Nondependent name      | A name that is not a dependent name by the above description. |

The precise definition of the set of associated namespaces and associated classes for a given type is determined by the following rules:

- For built-in types, this is the empty set.
- For pointer and array types, the set of associated namespaces and classes is that of the underlying type.
- For enumeration types, the associated namespace is the namespace in which the enumeration is declared. For class members, the enclosing class is the associated class.
- For class types (including union types) the set of associated classes is the type itself, the enclosing class, and any direct and indirect base classes. The set of associated namespaces is the namespaces in which the associated classes are declared. If the class is a class template instantiation, then they types of the template type arguments and the classes and namespaces in which the template arguments are declared are also included.
- For function types, the sets of associated namespaces and classes comprise the namespaces and classes associated with all the parameter types and those associated with the return type.
- For pointer-to-member-of-class-X types, the sets of associated namespaces and classes include those associated with `X` in addition to those associated with the type of the member. (If it is a pointer-to-member-function type, then the parameter and return types can contribute too.)

The name of a class is "injected" inside the scope of that class itself and is therefore accessible as an unqualified name in that scope.(However, it is not accessible as a qualified name because this is the notation used to denote the constructors.

This is a consequence of the so-called `maximum munch` tokenization principle: A C++ implementation must collect as many consecutive characters as possible into a token.

The typename prefix to a name is required when the name:

1. Appears in template
2. Is qualified
3. Is not used as in a list of base class specifications or in a list of member initializers introducing a constructor definition
4. Is dependent on a template parameter

---



## Template Argument Deduction

If the parameter is declared with a reference declarator, P is taken to be the type referenced, and A is the type of the argument. Otherwise, however, P is the declared parameter type, and A is obtained from the type of the argument by `decaying` array and function types to pointer types, ignoring top-level `const` and `volatile` qualifiers.

However, a few constructs are not deduced from contexts:

- Qualified type names. A type name like `Q<T>::X` will never be used to deduce a template parameter `T`.
- Non-type expressions that are not just a nontype parameter. A type name like `S<I+1>` will never be used to deduce `I`.

There are two situations in which the pair `(A, P)` used for deduction is not obtained from the arguments to a function call and the parameters of a function template:

- The First situation occurs when the address of a function template is taken:

  ```c++
  template<typename T>
  void f(T, T);
  void (*pf)(char, char) = &f;
  ```

- The other special situation occurs with conversion operator templates:

  ```c++
  struct S {
      public:
          template<typename T, int N> operator T[N]&(){...}
  };
  
  void f(int (&)[20]){...}
  void g(S s) {
      f(s);
  }
  ```

Normally, template deduction attempts to find a substitution of the function template parameters that makes the parameterized type `P` identical to type `A`. However, when this is not possible, the following differences are tolerable:

- If the original parameter was declared with a reference declarator, the substituted `P` type may be more `const/volatile` qualified than the `A` type.
- If the `A` type is a pointer or pointer-to-member type, it may be convertible to the substituted `P` type by a qualification conversion (int other words, a conversion that adds `const` and/or `volatile` qualifiers).
- Unless deduction occurs for a conversion operator template, the substituted `P` type may be a base class type of the `A` type, or a pointer to a base class type of the class type for which `A` is a pointer type.

---



## Instantiation

When a C++ compiler encounters the use of a template specialization, it will create that specialization by substituting the required arguments for the template parameters.

`two-phase lookup`: The first phase is the parsing of a template, and the second phase is its instantiation.

The POI is a point in the source where the substituted template could be inserted. For nonclass POIs, an alternative exists: The nonclass template can be declared using `export` and defined in another translation unit.

In theory, greedy instantiation has some serious drawbacks:

- The compiler may be wasting time on generating and optimizing N instantiations, of which only one will be kept.
- Linkers typically do not check that two instantiations are identical because some insignificant differences in generated code can validly occur for multiple instances of one template specialization. These small differences should not cause the linker to fail. (These differences could result from tiny differences in the state of the compiler at the instantiation time.) However, this often also results in the linker not noticing more substantial differences, such as when one instantiation was compiled for maximum performance, whereas the other was compiled for the most convenient debugging.
- The sum of all the object files could potentially be much larger than with alternatives because the same code may be duplicated many times.

Queried Instantiation:

1. No specialization is available: In this case, instantiation occurs, and the resulting specialization is entered in the database.
2. A specialization is available, but it is out of date because source changes have occurred since it was generated. Here, too, instantiation occurs, but the resulting specialization replaces the one previously stored in the database.
3. An up-to-date specialization is available in the database. Nothing needs to be done.

---



## Specialization and Overloading

Two functions can coexist in a program if they have distinct signatures. We define the signature of a function as the following information:

1. The unqualified name of the function (or the name of the function template from which it was generated).
2. The class or namespace scope of that name and, if the name has internal linkage, the translation unit in which the name is declared.
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

We then synthesize two artificial lists of argument types (or for conversion function templates, a return type) by substituting every template parameter as follows:

1. Replace each template type parameter with a unique "made-up" type.
2. Replace each template parameter with a unique "made-up" class template.
3. Replace each nontype template parameter with a unique "made up" value of the appropriate type.

Function templates can be overloaded with nontemplate functions. All else being equal, the nontemplate function is preferred in selecting the actual function being called.

A full specialization is introduced with a sequence of three tokens: `template`, `<` and `>`. In addition, the class name declarator is followed by the template arguments for which the specialization is declared.

The syntax and principles behind (explicit) full function template specialization are much the same as those for full class template specialization, but overloading and argument deduction come into play.

The full specialization declaration can omit explicit template arguments when the template being specialized can be determined via argument deduction (using as argument types the parameter types provided in the declaration) and partial ordering.

A full function template specialization cannot include default argument values. However, any default arguments that were specified for the template being specialized remain applicable to the explicit specialization.

A full specialization is in many ways similar to a normal declaration (or rather, a normal redeclaration). In particular, it does not declare a template, and therefore, only one definition of a non-inline full function template specialization should appear in a program. However, we must still ensure that a declaration of the full specialization follows the template to prevent attempts at using the function generated from the template. The declarations for template `g` in the previous example would therefore typically be organized in two files.

Not only member templates, but also ordinary static data members and member functions of class templates, can be fully specialized. The syntax requires `template<>` prefix for every enclosing class template. If a member template is being specialized, a `template<>` must also be added to denote that it is being specialized.

```c++
template<>
class Outer<bool>::Inner<wchar_t>{
    public:
    	enum{count = 2};
};
```

There exists a number of limitations on the parameter and argument lists of partial specialization declarations. Some of them are as follows:

1. The arguments of the partial specialization must match in kind (type, nontype, or template) the corresponding parameters of the primary template.
2. The parameter list of the partial specialization cannot have default arguments; the default arguments of the primary class template are used instead.
3. The nontype arguments of the partial specialization should either be nondependent values or plain nontype template parameters. They cannot be more complex dependent expressions like `2*N` (where `N` is a template parameter).
4. The list of template arguments of the partial specialization should not be identical (ignoring renaming) to the list of parameters of the primary template.

```c++
template<typename T, int I = 3>
class S;

template<typename T>
class S<int, T>;   // error

template<typename T = int>
class S<T, 10>;    // error

template<int I>
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

---



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

---



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

---



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

---



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

---



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

---



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

  


---



## Reference

[1] C++ Templates: The Complete Guide. David Vandevoorde, Nicolai M. Josuttis . 2004
