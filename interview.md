English | [中文版](interview_zh.md)

# Interview

[TOC]



## AI

TODO

---



## C/C++

### Base

#### What is C++? How is it different from C?

c++ is a general-purpose, object-oriented programming language built as a extension of C. While C focuses on structred programming, C++ adds OOP features like classes, inheritance, poolymorphism, and encapsulation. It also supports function and operator overloading, plus templates, making code more reusable, efficient, and flexible.

For more info, see: [C++ Features](LANG/C++/feature.md), [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What are access modifiers in C++?

Access modifiers control who can access class members and data members. They help encorce object oriented programming principles like encapsulation. There are three access modifieers in C++: public, private, protected.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is the purpose of comments in C++?

The purpose is to provide information about code lines.

#### What is the difference between a declaration and a definition of a variable used in C++?

A declaration introduces a variable's name and type to the compiler, while a definition goes further by allocating storage(memory) for that variable.

For more info, see: [C++ Feature](LANG/C++/feature.md)

#### Can you discuss the difference between a local and global scope of a variable?

Local variables are declared inside functions, existing only temporarily within that block. Global variables are declared outside functions and are accessible throughout the entire program.

#### What is the difference between pass by value and pass by reference?

In pass-by-value, only a copy of the data is sent, keeping the original safe. In pass-by-reference, the actual data is shared, so any changes affect the original.

#### Explain Shallow Copy, Deep Copy?

A shallow copy means copying an object in a way that only the outer structure is duplicated. A deep copy, on the other hand, makes a full, independent copy of the object, including any data the object points to. Deep copying takes more time and memory, but it is safer.

####  What is the difference between stack memory and heap memory?

Stack memory handles static allocation(local variables, function calls), while heap memory manages dynamic allocation(objects).

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is a recursive function? 

A recursive function calls itself to solve a problem by breaking it into smaller subproblems, with at least one base case to stop recursion.

#### What is Function Overriding in C++ and How Does the Base Class Affect It?

In function overriding, a derived class provides a new implementation for a virtual function with the same signature as in the base. Resolution happens at runtime (dynamic dispatch).

For more info, see: [C++ Object Oriented Programming#Function Overriding](LANG/C++/oop.md)

#### What is Function Overloading in C++ (Compile Time Polymorphism)?

Function overloading allows multiple functions with the same name but different parameter lists(types or arity). The compiler will pick the best match at compile-time.

For more info, see: [C++ Feature#Function Overloading](LANG/C++/feature.md)

#### Can `main()` be overloaded?

No! The C++ standard requires exactly one `main()` function. Overloading `main()` is not allowed.

For more info, see: [C++ Feature#Function Overloading](LANG/C++/feature.md)

#### Can overloaded functions have default arguments?

Yes! but be careful of ambiguity.

For more info, see: [C++ Feature#Function Overloading](LANG/C++/feature.md)

#### Why can't overloading be based on return type along?

Because the return type is not included in the function call, the compiler won't be able to distinguish between them, resulting in an ambiguity issue.

For more info, see: [C++ Feature#Function Overloading](LANG/C++/feature.md)

#### Is destructor overloading possible?

Destructor overloading is not possible in C++. A class can have only one destructor, and it cannot take parameters or have a return type.

For more info, see: [C++ Object Oriented Programming#Destruction#Notice](LANG/C++/oop.md)

#### What's the difference between function overloading and templates?

Overloading creates multiple distinct functions. Templates generate functions as needed. Use overloading for specific type handling, templates for generic algorithms.

#### What is the difference between function overriding, function overloading?

Function overloading allows you to define multiple functions in the same scope with the same name but different parameters. Function overriding occurs in inheritance hierarchies when a derived class provides a specific implementation for a function that is already defined in its base class.

For more info, see: [C++ Feature#Function Overloading vs Overriding](LANG/C++/feature.md)

#### What is the difference between function overloading and operator overloading?

Function overloading is about having multiple versiosn of a function with the same name but different signatures, while operator overloading is about giving new meaning to existing operators for user-defined types.

For more info, see: [C++ Feature#Function Overloading vs Overriding](LANG/C++/feature.md)

#### What is the difference between static data members and non-static data members?

static data member shared among all instances; by contrast, each object has its own copy of non-static member .

For more info, see: [C++ Features#static](LANG/C++/feature.md)

#### Can static member functions be virtual?

No, virtual functions require `this` pointer (dynamic dispatch), static functions have no `this`.

For more info, see: [C++ Features#static](LANG/C++/feature.md)

#### When are static variables initialized?

Before `main()` (static initialization) or on first use (dynamic initialization). Can lead to static initialization order fiasco.

For more info, see: [C++ Features#static](LANG/C++/feature.md)

#### How to fix static initialization order fiasco?

Use Meyers Singleton pattern(function-local static)

For more info, see: [C++ Features#static](LANG/C++/feature.md)

#### What is a pointer in C++, and how is it different from a reference?

A pointer stores the memory address of a variable. Each pointer has a unique memory address and can directly access the value it points to. Reference, on the other hand, is an alias to an existing variable. The main difference between the two is that the pointer can be null and can also be reassigned, while reference can not.

For more info, see: [C++ Features#Pointers](LANG/C++/feature.md)

#### What happens if you return a pointer to a local variable from a function?

The pointer becomes dangling because the variable's lifetime ends when the function exits. Accessing it causes undefined behavior.

#### What is the “this” pointer, and how is it used?

Inside a non-static member function, this is a pointer to the current object.

#### What is a function pointer, and how do you use it?

A function pointer stores the address of a function with a specific signature, which lets you call it indirectly or pass it around (callbacks, table-driven code).

#### In the line "int* a, b;", how many pointers are declared?

Only `a` is a pointer, `b` is just an int.

#### How does pointer arithmetic lead to undefined behavior if misused?

Pointer arithmetic allows direct memory access, but accessing out-of-bounds memory is undefined. Compiler may not throw errors, but program may crash or show garbage.

#### Is the inline keyword mandatory for inlining?

No! modern compilers aggressively inline functions even without the inline keyword, especially with optimization flags like `-O2` or `-O3`.

#### How does inline expansion of functions affect performance?

Inline expansion replaces a function call with the function body, potentially reducing call overhead and enabling further optimizations (constant propagation, loop unrolling).

For more info, see: [C++ Features#inline](LANG/C++/feature.md)

#### What's the difference between `#define` and `inline`?

inlie is a C++ keyword with proper scoping, type checking, and no side-effect issues. Macros are preprocessor text substitution with none of these benefits.

For more info, see: [C++ Features#inline vs macros](LANG/C++/feature.md)

#### Can we have a recursive inline function in C++?

Typically no! An inline function suggests to the compiler that function calls may be replaced with the function body to reduce overhead. Recursive functions can technically be marked inline, but in practice, the compiler will inline only a limited number of calls(if any). For deep recursion, inlining is not practical.

For more info, see: [C++ Features#inline](LANG/C++/feature.md)

#### Does inline guarantee no function call?

No! It's a request. The compiler can ignore it. Conversely, compilers can inline functions without the inline keyword.

For more info, see: [C++ Features#inline](LANG/C++/feature.md)

#### What does the Scope Resolution operator do?

A scope resolution operator (::) is used to reference a member function or a global variable out of their scope furthermore to which it can also access the concealed variable or function in a program.

#### What is an Overflow Error?

An overflow occurs when a calculation produces a result outside the range representable by a data type. In C++, signed integer overflow leads to undefined behavior, while unsigned integer overflow wraps around modulo the maximum value.

For more info, see: [C++ Exception#Overflow Error](LANG/C++/exception.md)

#### What is the difference between `const` and `#define`?

`const` and `#define` are used to define constants, but `const` is a type-safe variable checked at compile-time with scope, while `#define` is a preprocessor macro that performs simple text substitution before compilation.

For more info, see: [C++ Features#const](LANG/C++/feature.md)

#### What's the difference between const parameters and non-const parameters?

Const parameters promise not to modify the argument, while non-const parameters allow modification. For value parameters, const affects only the function's local copy and doesn't impact the caller. For reference/pointer parameters, const prevents modification fo the original object, enabling safer interfaces, better documentation, and allowing the function to accept both const and non-const arguments, including temporaries and literals.

For more info, see: [C++ Features#const](LANG/C++/feature.md)

#### What's the difference between `const T&` and `T&&`?

`const T&` is a const lvalue reference--it binds to anything and promises not to modify. `T&&` is an rvalue reference--it bidns only to rvalues and indicates the function may 'steal' resource. They serve different purposes: const& for ready-only access, && for move optimization.

For more info, see: [C++ Features#const](LANG/C++/feature.md)

#### Can you modify a const reference parameter using const_cast?

Yes! but it's undefined behavior if the original object was actually const. If you cast away constness on a reference that refers to a truly const object, modifying it is UB. Only use const_cast when you're certain the underlying object isn't const.

For more info, see: [C++ Features#const](LANG/C++/feature.md)

#### Should I pass `std::unique_ptr` by const reference?

Usually, no. `std::unique_ptr` represents ownership. If you just need to access the object, pass a raw pointer or reference. If you need to transfer ownership, pass by value. Pass const reference to `unique_ptr` only if you need to inspect the pointer itself without modifying it.

For more info, see: [STL#Smart pointers](LANG/C++/stl.md)

#### What are default arguments?

Default arguments are values that are used when a function is called without some parameters.

#### Discuss the difference between prefix and postfix?

Prefix and postfix operators differ primarily in the timing of their operation relative to expression evaluation. Prefix(`++x`) increments the variable first and returns the updated value, while postfix(`x++`) returns the original value before incrementing. Both increment the variable by 1, but prefix affects the current expression immediately.

#### What are the different data types present in C++

C++ data types are divided into 4 main categories: primitive(built-in) types, derived types, enumeration and user-defined types.

For more info, see: [C++ Features#data types](LANG/C++/feature.md)

#### What's the difference between static binding and dynamic binding?

Static binding resolves function calls at compile time based on the static type of the object, while dynamic binding resolves them at runtime based on the dynamic type. Static binding is used for non-virtual functions, overloaded functions, and templates, offering better performance. Dynamic binding is used for virtual functions, enabling runtime polymorphism through vtable lookup, with a small performance cost.

For more info, see: [C++ Features#overload](LANG/C++/feature.md), [C++ Object Oriented Programming#Polymorphism](LANG/C++/oop.md)

#### What about `typedef` versus macros in C++?

`typedef` creates type aliases at the compiler level with proper scope and type safelty, while macros are preprocessor text substitutions that happen before compilation with no type checking. In modern C++, macros should be avoided for type aliasing due to their global scope, lack of type safety, and debugging difficulties.

For more info, see: [C++ Best Practice#Prefer alias declarations (using) to typedefs](LANG/C++/best_practice.md)

### New Feature

#### Can you explain move semantics and why they are important in modern C++?

Move semantics allow resources to be transferred (moved) from temporaries or expiring objects instead of expensive deep copies, enabling performance gains and exception safety improvements.

For more info, see: [C++ Features#Move](LANG/C++/feature.md)

#### Explain how `std::move` and `std::forward` differ in perfect forwarding?

In C++, the key difference is that `std::move` unconditionally casts its argument to an rvalue reference to enable move semantics, while `std::forward` conditionally casts it argument to preserve its original value category in generic code. This preservation of the value category is the core of perfect forwarding.

For more info, see: [C++ Features#Move](LANG/C++/feature.md)

#### What is lvalue and rvalue?

An lvalue is an object that occupies a specific memory location and can be referred to by name. An rvalue is a temporary value that does not have a persistent memory address.

For more info, see: [C++ Features#Move](LANG/C++/feature.md)

#### What is SFINAE? How does it relate to template specialization?

SFINAE stands for Substitution Failure is not an error. It is a C++ template metaprogramming rule where, if template substitution fails, the compiler does not throw an error but instead removes that candidate from consideration.

For more info, see: [C++ Template#SFINAE](LANG/C++/template.md)

#### What is Perfect Forwarding in C++ and how is it achieved?

Perfect forwarding is a technique to pass arguments to another function without losing their value category (lvalue or rvalue). It's essential in generic programming to write functions that forward arguments efficiently.

#### Can `auto` be used in function parameters?

Yes, `auto` can used in generic lambdas (e.g., `[](auto x){}`).

For more info, see: [C++ Features#auto](LANG/C++/feature.md)

#### What's the difference between `auto` and `template` type deduction?

Almost identical, except that `auto` assumes `std::initializer_list` for braced initializer, while template don't.

For more info, see: [C++ Features#auto vs template type deduction](LANG/C++/feature.md)

#### What are `decltype` and `auto` keywords used for?

`auto` deduces the variable type from the initializer. It's great for long iterator types, lambdas, and templates. `decltype(expr)` yields the exact type of an expression(including references and cv-qualifiers) without evaluating it.

For more info, see: [C++ Features#decltype](LANG/C++/feature.md)

#### What's the difference between `auto` and `decltype`?

`auto` deduces type from an initializer value, stripping references and `const`/`volatile` qualifiers. `decltype` examines the declared type of an expression without evaluating it, preserving all qualifiers.

For more info, see: [C++ Features#decltype](LANG/C++/feature.md)

#### How does type deduction using auto and decltype in C++ enhance type safety and flexibility?

Instead of manually specifying data types, C++ allows the compiler to deduce the type using:

- auto: Deduces the type from initializer.
- decltype: Infers type from an expression.

For more info, see: [C++ Features#decltype](LANG/C++/feature.md)

#### When would `decltype((x))` be different from `decltype(x)`?

`decltype(x)` gives the exact type of variable `x`. `decltype((x))` treats `(x)` as an expression - if `x` is an lvalue, it yields `T&`. This is known as the "parentheses trick".

For more info, see: [C++ Features#decltype#Notice](LANG/C++/feature.md)

#### What is `decltype(auto)` and when would you use it?

`decltype(auto)` deduces a type using `auto`'s syntax but `decltype`'s rules. It's perfect for forwarding return types in wrapper functions, especially when you need to preserve references.

For more info, see: [C++ Features#decltype(auto)](LANG/C++/feature.md)

#### What are lambda expressions in C++11 and later?

Lambdas are inline, anonymous function objects with optional captures. They enable concise callbacks and algorithms.

#### What is the main use of the keyword “Volatile”?

The volatile keyword prevents teh compiler from performing optimization on the code.

For more info, see: [C++ Features#volatile](LANG/C++/feature.md)

#### What Is `constexpr` and Why Is It Significant?

`constexpr` is used to define expressions or functions that are evaluated at compile-time, ensuring greater efficiency by precomputing values wherever possible.

For more info, see: [C++ Features#constexpr](LANG/C++/feature.md)

#### What happens if a `constexpr` function is called with non-constant arguments?

It falls back to runtime evaluation (unless `consteval`(C++20 above)).

For more info, see: [C++ Features#The Dual Nature of constexpr Functions](LANG/C++/feature.md)

#### Can `constexpr` functions be recursive?

Yes, but watch for compile-time recursion limits, and no dynamic memory in recursion.

For more info, see: [C++ Features#constexpr](LANG/C++/feature.md)

#### When should I use `constexpr` vs `templates`?

Use `constexpr` for numeric computations, use `if constexpr` for conditional compilation. `Templates` for type-based dispatch.

#### What is C++ storage class?

Storage class is used to defines the scope(visibility), lifetime, and linkage of variables or functions. These features usually help in tracing the existence of a variable during the runtime of a program.

#### What is a mutable storage class specifier? How can they be used?

The `mutable` keyword is a storage class specifier used only with non-static data members of a class. It allows a member of a const object to be modified. Normally, if an object is declared const, you cannot modify any of its members, but mutable makes an exception.

For more info, see: [C++ Features#mutable](LANG/C++/feature.md)

#### What's the difference between `override` and `final`?

`override` tells the compiler this function is meant to override a base virtual function (catches signature errors). `final` prevents further overriding in derived classes.

For more info, see: [C++ Features#override](LANG/C++/feature.md), [C++ Features#final](LANG/C++/feature.md)

### Smart Point

#### Explain Smart Pointers in C++?

Smart pointers are template classes in `<memory>` that automate memory management and prevent leaks by destroying objects when they go out of scope.

For more info, see: [C++ STL#Smart pointers](LANG/C++/stl.md)

#### Explain the differences between `unique_ptr`, `shared_ptr`, and `weak_ptr` in terms of ownership and use cases?

`unique_ptr` provides exclusive ownership of a resource, `shared_ptr` enables shared ownership via reference counting, and `weak_ptr` observes a `shared_ptr` without managing its lifetime, preventing circular dependencies. 

For more info, see: [C++ STL#unique_ptr vs shared_ptr vs weak_ptr](LANG/C++/stl.md)

#### Can you clarify how `shared_ptr` handles reference counting and why `weak_ptr` is used to break circular references?

`std::shared_ptr` manages object lifetimes using an atomically updated reference cout stored in a shared control block.

`std::weak_ptr` is used to break circular references because it observes the object without contributing to this count, preventing memory leaks.

For more info, see: [C++ STL#Smart pointers](LANG/C++/stl.md)

#### In a `std::shared_ptr` cycle, how does `std::weak_ptr` help avoid memory leaks when one object references another?

It observes the object without contributing to its reference count, thus allowing the memory to be deallocated when all strong references are gone.

For more info, see: [C++ STL#weak_ptr](LANG/C++/stl.md)

#### How do you safely pass a `std::shared_ptr` to a thread?

To safely pass a `std::shared_ptr` to a thread, you should pass it by value. This ensures the new thread gets its own copy, making the shared pointer's reference count management thread-safe and guaranteeing the object's lifetime extends as long as the thread is running.

For more info, see: [C++ STL#shared_ptr](LANG/C++/stl.md)

#### What's a potential issue when passing `std::shared_ptr` to a thread, and how can you avoid it?

The main issue when using `std::shared_ptr` in a multithreaded environment is the potential for data races on the managed object and, less commonly, data races on the `std::shared_ptr` instance itself.

For more info, see: [C++ STL#shared_ptr](LANG/C++/stl.md)

#### Can you explain what a dangling pointer is and how smart pointers help prevent it?

A dangling pointer generally occurs when we use the `delete` to deallocate memory that was previously allocated, and the pointer that was pointing to that memory still points to the same address.

Smart pointers implement RAII (Resource Acquisition Is Initialization), they automatically manage object lifetime.

For more info, see: [C++ Feature#Dangling Pointer](LANG/C++/feature.md)

### Exception & Error

#### How do you handle errors in C++? Are you mostly using exceptions, return codes, or something else?

I use a hybrid approach based on the context: exception for truly exceptional, rare errors that should propagate up, return codes for expected, recoverable failures, and assertions for catching programming bugs during development. The key is matching the error handling strategy to the error's severity and frequency.

For more info, see: [C++ Exception#Exception Handling](LANG/C++/exception.md)

#### How is exception handling implemented in C++?

Exception handling in C++ is implemented using three keywords: `try`, `catch` and `throw`. This mechanism allows a program to deal with runtime errors in a a structured way so that it doesn't stop abruptly.

For more info, see: [C++ Exception#Exception Handling](LANG/C++/exception.md)

#### What is the use of the `catch(...)` block? How is it different from specific catch blocks?

The `catch(...)` block is used to catch any type of exception, regardless of its data type or class. It acts as a generic fallback handler.

For more info, see: [C++ Exception#Exception Handling#Notice](LANG/C++/exception.md)

#### How do you create a custom exception in C++?

You can create a custom exception by defining a class that inherits from the `std::exception` class and overriding its `what()` method, which returns an error message.

For more info, see: [C++ Exception#Exception Handling#Throwing Exceptions](LANG/C++/exception.md)

#### What is the difference between std::exception and user-defined exceptions?

`std::exception` is the root of the standard hierarchy and provides a virtual `what()` string. Standard library errors derive from it. User-defined exceptions let you encode domain context. As long as they ultimately derive from `std::exception`, callers can catch generically while still matching specific types when desired.

For more info, see: [C++ Exception#Exception Handling](LANG/C++/exception.md)

#### What happens if an exception is thrown but not caught?

If an exception is thrown but not caught anywhere in the call stack, the program calls `std::terminate()`, which by default aborts execution. Exceptions can propagate up the call stack until a suitable catch block is found. If none is found, the program terminates.

For more info, see: [C++ Exception#Exception Handling](LANG/C++/exception.md)

#### What is stack unwinding in exception handling? Explain its role.

Stack unwinding is the process of cleaning up the call stack after an exception is thrown and before it is caught. During unwinding, destructors of all local objects are called in reverse order of construction, ensuring proper cleanup. This prevents resource leaks and enforces RAII(Resoruce Acquistition Is Initialization).

For more info, see: [C++ Exception#Exception Handling#Exception Propagation](LANG/C++/exception.md)

#### What is the use of noexcept in C++ exception handling?

The `noexcept` keyword specifies that a function does not throw exceptions. It makes intent clear to both the compiler and developers. If a nonexcept function does throw, `std::terminate()` is called. noexcept is especially important for move constructors and destructors, where it enables optimizations such as exception-safe move operations in standard containers.

For more info, see: [C++ Exception#Exception Handling](LANG/C++/exception.md)

#### What will happen if you throw an exception from a destructor?

Throwing an exception from a destructor during stack unwinding results in a call to `std::terminate()`, which aborts the program.

For more info, see: [C++ Exception#Exception Handling](LANG/C++/exception.md)

#### What happens when you throw a pointer and throw an object in C++?

Throwing a pointer means you're throwing an address. It won't trigger automatic destruction of the object pointed to, and catching it requires catching the same pointer type. Throwing by value creates a copy, and cleanup is automatic.

For more info, see: [C++ Exception#Exception Handling](LANG/C++/exception.md)

#### How can RAII (Resource Acquisition is Initialization) help in exception safety?

Yes. RAII binds a resource's lifetime to an object's lifetime so that destructors perform cleanup automatically during normal execution and during exception unwinding. This prevents leaks and makes code exception-safe.

For more info, see: [C++ Best Practice#Ensure thread safety](LANG/C++/best_practice.md)

#### What is an Overflow Error?

An overflow error happens when a value is too large (or too small in magnitude) to be represented in the allocated memory. These errors can cause crashes, incorrect calculations, security vulnerabilities, and hard-to-find bugs.

For more info, see: [C++ Exception#Overflow](LANG/C++/exception.md)

#### Is signed integer overflow undefined behavior in C++?

Yes! Signed integer overflow is undefined behavior - the compiler can assume it never happens and optimize accordingly. Unsigned overflow is well-defined (wraps modulo $2^n$, not an error or undefined behavior).

For more info, see: [C++ Exception#Overflow](LANG/C++/exception.md)

#### Why is signed overflow UB while unsigned wraps?

Historical: Different hardware (ones' complement, sign-magnitude) handled overflow differently. C++ standard chose to allow flexibility. Modern CPUs use two's complement, but UB remains for optimization opportunities.

For more info, see: [C++ Exception#Overflow](LANG/C++/exception.md)

#### How can buffer overflows be prevented in C++?

Enable compiler warnings, Use safe functions/containers.

For more info, see: [C++ Exception#Overflow#Compile-Time Prevention](LANG/C++/exception.md)

#### What's the difference between overflow and underflow?

Overflow exceeds maximum representable value, Underflow exceeds minimum (negative) value.

For more info, see: [C++ Exception#Overflow](LANG/C++/exception.md)

#### Can floating-point overflow be detected?

Yes! using `std::isinf()` to check for infinity, or enabling floating-point exceptiosn with `std::fenv`.

For more info, see: [C++ Exception#Overflow](LANG/C++/exception.md)

#### What's integer promotion and how does it affect overflow?

Small integers (`char`, `short`) are promoted to `int` before arithmetic. This can prevent overflow in the smaller type but cause overflow in `int`.

### OOP

#### What is Object Oriented Progamming (OOP)?

Object-Oriented Programming is a programming paradigm that organizes code around objects(data + behavior) rather than functions and data separately.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is a class and object in C++?

A class is a blueprint or template that defines the properties(data members) and behaviors(member functions/methods) that all objects of that specific type will have. 

An object is a real-world instance of a class that occupies memory and can perform the actions defined by the class.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is the difference between structures and class

The only technical difference between `struct` and `class` in C++ is the default access specifier; `struct`'s members and base classes are `public` by default, `class`'s members and base classes are `private` by default.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What are the C++ Access Specifiers?

In C++, the access specifiers are used to define how the functions and variables can be accessed outside the class. There are three access specifiers: `public`, `protected`, and `private`. `public` members are accessible from anywhere. `private` members are only accessible within the same class. `protected` members are accessible within the class and its derived classes.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What are type modifiers in C++?

Modifiers like signed, unsigned, long, short change the size or sign of basic data types.

#### What is a friend function?

A friend function (or class) has access to a class's private and protected members. It can be used sparingly to implement symmetric operators or tightly coupled utilities without exposing internals publicly.

For more info, see: [C++ Object Oriented Programming#Access Specifiers](LANG/C++/oop.md)

#### What is a friend class?

A friend class is a class that can access the private and protected members of another class. The friendship is declared inside the class using friend class.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is object slicing in C++? How can you avoid it?

Object slicing occurs when a derived object is copied by value into a base object, losing the derived part. During this process, the extra data members fo the derived class are "sliced off" or lost, leaving only the base class's members. We can avoid slicing by: passing by pointer or reference, use smart pointers, use `std::variant`, ...

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What do you mean by abstraction in C++?

Abstraction means hiding complex implementation details and showing only the essential features to the user. It's about focusing on what domething does rather than how it does it.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is the difference between an abstract class and an interface in C++? How do you implement an interface-like behavior in C++?

An abstract class is a class with **at least** one pure virtual function. An interface is a class with **only** pure virtual functions, it is a contract that defines a set of methods that a class must implement, without providing any implementation details ...

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### Explain the concept of encapsulation

Encapsulation is one of the core principles of OOP. It bundles data(member variables) with the methods (member functions) that operate on that data inside a single unit, called a class. It restricts direct access to some parts of an object and hides the data to protect its integrity.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is inheritance in C++?

Inheritance is a machanism in which a class(derived class) acquires the properties and behaviors of another class(base class).

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is multiple inheritance, and what problems can it cause?

Multiple inheritance (MI) lets a class inherit from more than one base. Here are the common issues that result from MI: Ambiguity, Diamond problem, complexity.

For more info, see: [C++ Object Oriented Programming#Multiple Inheritance](LANG/C++/oop.md)

#### When should we use multiple inheritance?

In C++, multiple Inheritance should be used when a class is required to inherit features (data members and member functions) from more than one base class, and each base class offers a different functionality or behavior that is logically required in the derived class.

For more info, see: [C++ Object Oriented Programming#Multiple Inheritance](LANG/C++/oop.md)

#### What is a virtual function?

A virtual function is a member function declared with the `virtual` keyword that can be overridden in derived classes. When you call a virtual function through a base class pointer or reference, C++ determines at runtime which function to execute based on the actual object type - not the pointer type. Virtual functions are implemented via a vtable (virtual table) - an array of function pointers, and each object contains a vptr (virtual pointer) to its class's vtable.

For more info, see: [C++ Object Oriented Programming#Virtual functions](LANG/C++/oop.md)

#### What's the size overhead of a virtual function?

Each object gets one `vptr` (8bytes on 64-bit os) regardless of how many virtual functions. Each class gets one vtable (shared across all instances).

For more info, see: [C++ Object Oriented Programming#Object Model](LANG/C++/oop.md)

#### Can you have a virtual function with default arguments?

Yes, but DANGEROUS! Default arguments are determined at compile-time based on the static type.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance](LANG/C++/oop.md)

#### Can we call a virtual function from a constructor?

Yes, we can call a virtual function from a constructor, but during base class construction, the derived part of the object is not yet initialized.

For more info, see: [C++ Object Oriented Programming#Construction and Destruction](LANG/C++/oop.md)

#### When should you use templates vs virtual functions?

Use templates when types are known at compile time and you need maximum performance. Use virtual functions when you need runtime polymorphism.

For more info, see: [C++ Object Oriented Programming#Virtual functions](LANG/C++/oop.md), [C++ Templates](LANG/C++/template.md)

#### What's the performance cost of virtual functions?

Virtual functions add 2-3 extra instructions per call: load vptr, load function pointer, indirect call. This prevents inlining and may hurt branch prediction. However, the cost is typically 5-15% and only matters in tight loops. For most applications, the flexibility is worth the small overhead.

For more info, see: [C++ Object Oriented Programming#Virtual functions](LANG/C++/oop.md)

#### Can virtual functions be `constexpr`?

No! Virtual dispatch requires a runtime.

For more info, see: [C++ Object Oriented Programming#Virtual functions](LANG/C++/oop.md)

#### What's the difference between virtual functions and pure virtual functions?

A virtual function has an implementation in the base class and can be overridden in derived classes, making the base class concrete and instantiable. A pure virtual function has no implementation in the base class, forcing dervied classes to provide an implementation and making the base class abstract--you cannot create objects of that class. Pure virtual functions are used to define interfaces.

For more info, see: [C++ Object Oriented Programming#Polymorphism](LANG/C++/oop.md)

#### What is virtual inheritance?

Virtual inheritance is a C++ mechanism used to solve the diamond problem in multiple inheritance.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance](LANG/C++/oop.md)

#### What's the diamond problem with virtual inheritance?

When a class inherits from two classes that share a common base, virtual inheritance ensures only one copy of the base class exists.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance](LANG/C++/oop.md)

#### What's the cost of virtual inheritance?

Additional memory per object (virtual base pointer), slower member access (indirection), more complex construction/destruction, and larger object code.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance](LANG/C++/oop.md)

#### Can a class be both virtual and non-virtually inherited?

Yes! but it creates separate instance.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance](LANG/C++/oop.md)

#### How deos `dynamic_cast` work with virtual inheritance

`dynamic_cast` is essential for navigating virtual inheritance hierarchies because offsets aren't fixed at compile time. By contrast, `static_cast` may fail.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance#Notice](LANG/C++/oop.md)

#### Why must the most derived class initialize virtual bases?

Because the virtual base is shared and constructed once. Only the most derived class knows the entire hierarchy and can ensure the virtual base is onstructed before any intermediate classes use it.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance#Notice](LANG/C++/oop.md)

#### Can static functions be virtual?

No, Virtual dispatch requires a `this` pointer (object instance). Static functions belong to the class, not objects.

For more info, see: [C++ Object Oriented Programming#Virtual functions](LANG/C++/oop.md)

#### What happens when we override a function but forget to use `virtual` in the base class?

Function overriding won't work as runtime polymorphism, instead, function hiding occurs when the base class function is hidden by the derived class function if called through a derived object.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is polymorphism in C++?

Polymorphism means one interface, multiple implementations. It allows the same function or operator to behave differently depending on the context.

For more info, see: [C++ Object Oriented Programming#Polymorphism](LANG/C++/oop.md)

#### Can you explain the difference between compile-time and run-time polymorphism in C++?

Compile-time polymorphism is resolved during compilation using templates and function overloading, resulting in no runtime overhead but less flexibility. Runtime polymorphism is resolved during execution using virtual functions and inheritance, providing flexibility through dynamic dispatch but with a small performance cost (vtable lookup). The choice depends on whether you need the type to be determined at compile time (templates) or at runtime (virtual functions).

For more info, see: [C++ Object Oriented Programming#Polymorphism](LANG/C++/oop.md)

#### What's a constructor

In C++, a constructor is a special method that initializes an object. Its name must be the same as the class name. These constructors are called automatically whenever we create an object of a class.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### Can constructors be private in C++?

Yes, constructors can be private in C++. When a constructor is private, objects of the class cannot be created directly outside the class.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### Can we have static constructors in C++?

No, but you can use static initialization blocks.

For more info, see: [C++ Features#static](LANG/C++/feature.md)

#### Can constructors be private?

Yes! used in singleton pattern or factory methods.

#### Can constructors be virtual?

No. Constructors are called before the object exists - no vpt yet. The virtual mechanism requires a fully constructed object with a valid vtable.

For more info, see: [C++ Object Oriented Programming#Virtual functions](LANG/C++/oop.md)

#### Can constructors of virtual base classes have parameters?

Yes! but they must be explicitly called from the most derived class constructuctor.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance#Notice](LANG/C++/oop.md)

#### What happens if you don't define any constructor?

Compiler generates a default constructor automatically.

For more info, see: [C++ Object Oriented Programming#Default Constructor](LANG/C++/oop.md)

#### Can a constructor throw exceptions?

Yes! but be careful about resource leaks. Use RAII or try-catch blocks.

#### What's an explicit constructor?

Prevents implicit conversions.

For more info, see: [C++ Object Oriented Programming#Default Constructor](LANG/C++/oop.md)

#### Can a derived class access private members of the base class?

A derived class cannot directly access private members of a base class.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### How do you free memory allocated with new?

Use `delete` for single values, and `delete[]` for arrays.

For more info, see: [C++ Object Oriented Programming#new and delete Operators](LANG/C++/oop.md)

#### How we can make custom delete?

You can overload operator delete or operator delete[] in your class:

```c++
void operator delete(void* ptr){
    ...
    ::operator delete(ptr);
}
```

#### What is the difference between `new` and `malloc()`

`new` is a C++ operator that allocates memory and calls constructors, while `malloc()` is a C function that only allocates raw memory. `new` returns the correct typed pointer; `malloc()` returns `void*`. `new` throws `std::bad_alloc` on failure, `malloc()` return `NULL`. Memory allocated with `new` must be freed with `delete`, memory from `malloc()` with `free()`, mixing them is undefined behavior.

For more info, see: [C++ Object Oriented Programming#Summary](LANG/C++/oop.md)

#### What is a destructor in C++?

A destructor is a special member function that cleans up resources when an object is destroyed. It has the same name as the class, takes no parameters, and has no return type. Its primary job is to release resources like dynamically allocated memory, file handles, database connections, or mutex locks to prevent resource leaks.

For more info, see: [C++ Object Oriented Programming#Destructor](LANG/C++/oop.md)

#### Do I always need to write a destructor?

NO! If your class does not allocate resources, or manage resources by using RAII. Let the compiler generate the destructor.

For more info, see: [C++ Object Oriented Programming#Destructor](LANG/C++/oop.md)

#### Why can't destructor take parameters?

Destructors are called implicitly during object destruction; there's no way to pass arguments.

For more info, see: [C++ Object Oriented Programming#Destructor](LANG/C++/oop.md)

#### Can I call a destructor explicitly?

Yes, to destroy an object created with the placement new operator, you can explicitly call the object's destructor.

For more info, see: [C++ Object Oriented Programming#Destructor#Notice](LANG/C++/oop.md)

#### Why should base class destructors be virtual?

If the base class destructor is not virtual, deleting a derived object through a base pointer calls only the base destructor, which can cause memory leaks or incomplete destruction, and can ensure the derived destructor is called first.

For more info, see: [C++ Object Oriented Programming#Construction and Destruction](LANG/C++/oop.md)

#### Can a destructor be private?

Yes, this prevents stack allocation (automatic destruction) and forces heap allocation with manual deletion, often used in singleton patterns or reference-counted objects.

For more info, see: [C++ Object Oriented Programming#Destruction#Notice](LANG/C++/oop.md)

#### Can a destructor be pure virtual?

Yes! but you must still provide a body for it because base class destructors are always called during derived object destruction.

For more info, see: [C++ Object Oriented Programming#Private Destructor#Notice](LANG/C++/oop.md)

#### What's the order of destruction for member objects?

Members are destroyed in reverse of their declaration order.

For more info, see: [C++ Object Oriented Programming#Destruction Order](LANG/C++/oop.md)

#### What happens if a destructor throws an exception?

If another exception is already propagating, `std::terminate()` is called. Please always mark destructors `noexcept` and never throw from them.

For more info, see:  [C++ Object Oriented Programming#Destruction#Notice](LANG/C++/oop.md)

#### What is a virutal destructor?

A virtual destructor is a destructor declared with the `virtual` keyword. It ensures that when you delete a derived class object through a base class pointer, the correct destructor (starting from the derived class all the way up to the base class) gets called.

For more info, see:  [C++ Object Oriented Programming#Destruction#Notice](LANG/C++/oop.md)

#### Why use `static_cast` over C-style cast?

`static_cast` provides compile-time type safety, code clarity, and reduced risk of unintended conversions.

For more info, see: [C++ Object Oriented Programming#static_cast](LANG/C++/oop.md)

#### Can `dynamic_cast` be used with non-ploymorphic types?

No. Compiler error (no vtable).

For more info, see: [C++ Object Oriented Programming#dynamic_cast](LANG/C++/oop.md)

#### What's the cost of `dynamic_cast`?

`dynamic_cast` for polymorphic types requires runtime type information (RTTI). It's slower than `static_cast` because it needs to traverse the inheritance hierarchy.

For more info, see: [C++ Object Oriented Programming#dynamic_cast](LANG/C++/oop.md)

#### How does `dynamic_cast` work internally?

Each polymorphic class has a vtable. The compiler stores the RTTI pointer in the vtable. `dynamic_cast` traverses the inheritance graph by following these pointers and comparing `type_info` objects.

For more info, see: [C++ Object Oriented Programming#dynamic_cast](LANG/C++/oop.md)

#### Explain the difference between `static_cast`, `dynamic_cast` and `reinterpret_cast`.

`static_cast` does compile-time checked conversions between related types. `dynamic_cast` does runtime-checked downcasting. `reinterpret_cast` does dangerous bit-level reinterpretation with no checks whatsoever.

For more info, see: [C++ Object Oriented Programming#`static_cast` vs `dynamic_cast` vs `reinterpret_cast`](LANG/C++/oop.md)

### Template

#### Explain templates in C++?

Templates enable generic programming by parameterizing code over types. The compiler generates concrete instantiations on use.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### What is Template Metaprogramming in C++?

Template Metaprogramming (TMP) is a technique where templates are used to compute values at compile time, enabling optimization and stack checks.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### What Is Template Specialization, and How Is It Useful?

Template specialization allows you to create a customized version of a template for a specific data type or condition. It's useful when the generic template does not fit all data types or when you want optimized behavior for a particular type.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### Can function templates be partially specialized in C++?

Function templates cannot be partially specialized, only fully specialized. Partial specialization is only supported for class templates.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### What Are Variadic Templates in C++?

Variadic templates are an extension to C++ templates that allow them to accept a variable number of template arguments. This feature is invaluable for creating more flexible and reusable code structures, such as wrappers around existing functionality.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### What is a class template?

A `class template` is a blueprint for creating classes that work with different data types without rewriting the code for each type. It allows you to define a generic class where the data types are specified as parameters.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### What is a function template in C++?

A function template allows a function to operate on generic data types. It provides a way to write one function for multiple types, which is resolved at compile-time.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### How are class templates different from function templates?

Class templates require explicit template arguments when instantiating objects (until C++ 17 CTAD), while function templates can often deduce types from arguments.

For more info, see: [C++ Templates#Function Template vs Class Template](LANG/C++/template.md)

#### What is CTAD(Class Template Argument Deduction)?

Allows the compiler to deduce template arguments from constructor arguments.

For more info, see: [C++ Templates#Class Template Arguments Deduction(CTAD)](LANG/C++/template.md)

#### Can class templates be virtual?

Class templates can have virtual functions, but template functions cannot be (virtual functions must be known at compile time for vtable layout).

For more info, see: [C++ Templates#Class templates](LANG/C++/template.md)

#### What's the difference between `typename` and `class` in templates?

No difference. `typename` and `class` are identical, but `typename` is preferred to avoid confusion with class keyword.

#### What is template specialization?

Defining a different implementation for specific template arguments, useful for optimization or handling special cases.

For more info, see: [C++ Templates#Template Specialization](LANG/C++/template.md)

#### Can a function template throw an exception based on the type it is instantiated with?

Yes. Templates can use static_assert or if constexpr to control logic at compile-time based on type, and can throw exceptions conditionally at runtime.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### How would you write a generic function to swap two values by using template for different kinds of parameter.

write a template function that takes two references to the same type `T` and swaps their values using a temporary variable. The template allows the function to work with any type (int, float, string, custom classes) as long as that type supports copy assignment.

For more info, see: [C++ Templates](LANG/C++/template.md)

### Concurrency

#### What are the major multithreading features introduced in C++11 and later?

Modern C++ provides a full-fledged standard threading library with: `std::thread`, `std::mutex`, `std::lock_guard`, `std::condition_variable`, `std::atomic`, `std::async`, `std::future`.

For more info, see: [C++ Concurrency Programming#std::thread](LANG/C++/concurrency.md)

#### What's the major challenges when sharing data between threads in C++?

The major challenges when sharing data between threads in C++ include race conditions, data corruption, deadlocks, and performance overhead from synchroniation, all of which can lead to unpredictable behavior and program crashes.

For more info, see: [C++ Concurrency Programming](LANG/C++/concurrency.md)

#### What is a race condition, and how can you prevent it in C++?

A race conditon is a bug occuring when multiple threads access shared data simultaneously, and the final outcome depends on the unpredictable timing or sequence of their execution, leading to data corruption or inconsistent behavior. In C++, it is prevented by synchronizing access to shared data, ensuring only one thread accesses the critical section at a time.

For more info, see: [C++ Concurrency Programming#Race Condition](LANG/C++/concurrency.md)

#### How do you ensure thread safety when multiple threads access shared data in C++?

In C++, thread safety for shared data access is primarily ensured using synchronization primitives like mutexes and atomic operations. These mechanisms prevent data races, which lead to undefined behavior when multiple threads concurrently read and write to the same memory location.

For more info, see: [C++ Concurrency Programming](LANG/C++/concurrency.md)

#### Can you explain when you'd choose `std::atomic` over a mutex for thread-safe operations?

You should choose `std::atomic` for simple, single-variable operations where maximum performance is critical, and a mutex for complex operations involving multiple variables or where blocking is acceptable.

For more info, see: [C++ Concurrency Programming#std::atomic](LANG/C++/concurrency.md)

#### can you briefly explain how `std::atomic` helps prevents race conditions in a simple counter increment

`std::atomic` prevents race conditions by ensuring that operations on a shared variable, such as incrementing a counter, are indivisible and uniterruptible. This means the entire "read-modify-write" sequence is completed as a single, atomic step, without interference from other threads.

For more info, see: [C++ Concurrency Programming#std::atomic](LANG/C++/concurrency.md)

#### Can you write a small example where `std::atomic` safely signals a thread to stop?

A `std::atomic<bool>` provides a lightweight, thread-safe mechanism to signal a worker thread to stop. The main thread sets the atomic flag, which the worker thread periodically checks.

For more info, see: [C++ Concurrency Programming#std::atomic](LANG/C++/concurrency.md)

#### Describe a real-world scenario where thread safety is critical in C++ and how you'd ensure it.

A critical real-world scenario where thread safety is vital in C++ is a financial trading system, specifically in managing shared resources like an account balance or order book. A race condition could lead to lost updates, data corruption, and incorrect financial calculations, with significant real-world monetary consequences.

#### Describe a situation where `std::shared_mutex` is better than `std::mutex` for shared access.

`std::shared_mutex` is better than `std::mutex` in read-heavy scenarios where multiple threads read data frequently, but write are infrequent. It boosts performance by allowing concurrent reads, while `std::mutex` unnecessarily serializes all accesses, causing bottlenecks.

For more info, see: [C++ Concurrency Programming#shared_mutex](LANG/C++/concurrency.md)

#### Explain the difference between `std::thread::join` and `std::thread::detach()`

The primary difference is that `std::thread::join()` blocks the calling thread until the spawned thread finishes, which `std::thread::detach()` separates the spawned thread from its `std::thread` object, allowing it to run independently in the background.

For more info, see: [C++ Concurrency Programming#Waiting for Thread Completion, Detaching Threads](LANG/C++/concurrency.md)

### STL

#### What is 'namespace'?

Namespace is a feature that provides a way to group related identifiers such as variables, functions, and classes under a single name.

#### What is std in C++?

`std` is a namespace in C++ that stands fro standard. It contains the most standard library, including essential components like input/output streams, string manipulation, and various data structures and algorithms.

For more info, see: [C++ STL](LANG/C++/stl.md)

#### How Do `std::function` and `std::bind` Work in C++?

`std::function` is a polymorphic wrapper used to store and invoke any callable object, such as functions, lambdas, or bind expressions. `std::bind` allows you to bind specific arguments to a function, creating a new function object.

#### How is the vector container implemented in STL?

The vector container in C++ STL is a dynamic array that can grow or shrink in size at runtime. It provides random access to elements and stores them in contiguous memory locations, like traditional arrays.

For more info, see: [C++ STL#vector](LANG/C++/stl.md)

#### What happens if you modify a vector while iterating through it using a rang-based for loop?

If you modify a `std::vector` while iterating through it using a rang-based for loop, the behavior can be unpredictable and often unsafe.

For more info, see: [C++ STL#vector](LANG/C++/stl.md)

#### How can you safely erase elements from a vector or set while iterating?

To safely erase elements during iteration, we must avoid incrementing the iterator manually after erase(use returned iterator), or use remove-erase idiom(for vector), or use post-increment technique in containers like set.

For more info, see: [C++ STL#vector](LANG/C++/stl.md)

#### How do you pick between  vector, list, and deque for a dynamic container?

Choose vector for most use cases due to cache locality and low overhead. Use list when you need frequent insertions/deletions in the middle and iterator stability is critical. Use deque when you need efficient push/pop at both ends and random access, but can aacept slightly slower random access than vector. The default should always be vector unless you have a specific rason to choose otherwise.

For more info, see: [C++ STL#Container](LANG/C++/stl.md), [C++ Best Practice#Choose the Right Container](LANG/C++/best_practice.md)

#### What are iterators in STL?

An iterator is an object(like a pointer) used to traverse containers. STL uses iterators to access elements in a uniform manner, regardless of the container. Iterators help in writing generic algorithms that work across different container types.

For more info, see: [C++ STL](LANG/C++/stl.md)

#### What are allocators in STL? Can they be customized?

Allocators define how memory is allocated and deallocated for STL containers. By default, containers use `std::allocator<T>` which uses `new/delete`. Custom allocators can be provided for special needs such as memory pools, shared memory, or tracking.

For more info, see: [C++ STL](LANG/C++/stl.md)

#### What happens if you insert a duplicate key in `std::set` or `std::map`? How do you detect insertion success?

`std::set` and `std::map` do not allow duplicate keys. The `insert()` method returns a pair `<iterator, bool>`, where bool indicates success.

For more info, see: [C++ STL](LANG/C++/stl.md)

#### How do you sort a `vector<pair<int, int>>` by second element using STL?

To sort a `vector<pair<int, int>>` by the second element of the pairs using STL, you can use `std::sort` with a custom comparator.

For more info, see: [C++ STL](LANG/C++/stl.md)

#### What happens if you use a vector as a key in an unordered_map?

Using a `std::vector` as a key in an `unordered_map` is not allowed by default because unordered_map requires the key type to be hashable.

For more info, see: [C++ STL](LANG/C++/stl.md)

#### Write a function that takes a vector of integers and returns the sum of all even numbers using `std::transform` and `std::accumulate`.

```c++
#include <algorithm>
#include <vector>
#include <numeric>

int sum(const std::vector<int>& arr)
{
	std::vector<int> evens(arr.size());
	std::transform(arr.begin(), arr.end(), evens.begin(), [](int x) {
		return (x % 2 == 0) ? x : 0;
	});
	return std::accumulate(evens.begin(), evens.end(), 0);
}
```

For more info, see: [C++ STL](LANG/C++/stl.md)

### Boost

TODO

### Compile & Link

#### What is token in C++?

A token in C++ is the smallest individual unit of a program that the compiler recognizes. Tokens are the building blocks of C++ source code. The compiler breaks source code into tokens during lexical analysis before parsing.

#### What are the methods of exporting a function from a DLL?

There are two primary methods to export functions from a DLL: using `__declspec(dllexport)` at the function declaration, or using a `.def` (Module Definition File) listing exported functions. `__declspec(dllexport)` is simpler and most common. For importing in client code, use `__declspec(dllimport)`.


---



## DB

### Base

#### What is ACID properties?

ACID is a set of properties that guarantee reliable processing of database transactions, ensuring data integrity even in the case of errors, power failures, or concurrent access. A standard for Atomicity, C standards for Consistency, I standards for Isolation, and D standards for Durability.

For more info, see: [DB Summary#ACID](DB/summary.md)

#### What is OLTP?

OLTP stands for Online Transaction Processing, is a class of software applications capable of supporting transaction-oriented programs. An essential attribute of an OLTP system is its ability to maintain concurrency. To avoid single points of failure, OLTP systems are often decentralized. 

For more info, see: [Transactions#Online Analytical Processing (OLAP)](DB/transaction.md)

#### What are the differences between OLTP and OLAP?

OLTP stands for Online Transaction Processing, is a class of software applications capable of supporting transaction-oriented programs. An important attribute of an OLTP system is its ability to maintain concurrency. OLTP systems often follow a decentralized architecture to avoid single points of failure. These systems are generally designed for a large audience of end-users who conduct short transactions.

For more info, see: [Transactions#OLAP vs OLTP](DB/transaction.md)

#### What is Data Integrity?

Data Integrity is the assurance of accuracy and consistency of data over its entire life-cycle and is a critical aspect of the design, implementation, and usage of any system that stores, processes, or retrieves data. It also defines integrity constraints to enforce business rules on the data when it is entered into an application or a database.

For more info, see: [Transactions#Data Integrity](DB/transaction.md)

#### What is DBMS?

DBMS stands for Database Management System. DBMS is a system software responsible for the creation, retrieval, updation, and management of the database. It ensures that our data is consistent, organized, and is easily accessible by serving as an interface between the database and its end-users or application software.

For more info, see: [DB Summary#DBMS Intro](DB/summary.md)

#### What is RDBMS? How is it different from DBMS?

RDBMS stands for Relational Database Management System. Compared to DBMS, is that RDBMS stores data in the form of a collection of tables, and relations can be defined between the common fields of these tables.

For more info, see: [DB Summary#DBMS vs RDBMS](DB/summary.md)

#### What are Entities and Relationships?

Entities are distinct objects or things in the real world that have a physical or conceptual existence, like a customer or product. Relationships are the associations or connections between those entities, like a customer placing an order.

For more info, see: [Relational Model](DB/relational_model.md)

#### List the different types of relationships in SQL.

The three main types of relationships are One-to-One, One-to-Many, and Many-to-Many. One-to-Many is the most common, while Many-to-Many requires a junction table.

For more info, see: [Relationship](DB/relational_model.md)

### SQL

#### What is SQL?

SQL stands for Structured Query Language. It is the standard language for relational database management systems. It is especially useful in handling organized data comprised of entities (variables) and relations between different entities of the data.

For more info, see: [SQL](DB/sql.md)

#### What is the difference between CHAR and VARCHAR2?

CHAR stores fixed-length data and pads extra spaces; VARCHAR2 stores variable-length data, saving storage space.

For more info, see: [SQL#Data Types](DB/sql.md)

#### What is a view in SQL?

A view is a virtual table created by a `SELECT` query. It does not store data itself, but presents data from one or more tables in a structured way. Views simplify complex queries, improve readability, and enhance security by restricting access to specific rows or columns.

For more info, see: [SQL#Views](DB/sql.md)

#### What is the purpose of the UNIQUE constraint?

The UNIQUE constraint ensures that all values in a column (or combination of columns) are distinct. This prevents duplicate values and helps maintain data integrity.

For more info, see: [SQL#Unique constraint](DB/sql.md)

#### Explain the difference between the `WHERE` and `HAVING` clauses

WHERE filters individual rows BEFORE aggregation, while HAVING filters groups AFTER aggregation. WHERE cannot use aggregate functions (like SUM, AVG, COUNT), but HAVING can. Use WHERE to filter raw data, and HAVING to filter grouped results.

For more info, see: [SQL#WHERE#HAVING](DB/sql.md)

#### What are SQL joins, and what are the differences between `INNER`, `LEFT`, `RIGHT`, and `FULL` joins?

SQL joins combine rows from two tables based on a matching condition (typically keys) to answer questions that span both tables...

For more info, see: [SQL#Joins](DB/sql.md)

#### What is a Cross-Join?

Cross join can be defined as a cartesian product of the two tables included in the join. The table after join contains the same number of rows as in the cross-product of the number of rows in the two tables. If a `WHERE` clause is used in cross join then the query will work like an `INNER JOIN`.

For more info, see: [SQL#Cross Join](DB/sql.md)

#### What is a Self-Join?

A `Self JOIN` is a case of a regular join where a table is joined to itself based on some relation between its own column(s). Self-join uses the `INNER JOIN` or `LEFT JOIN` clause, and a table alias is used to assign different names to the table within the query.

For more info, see: [SQL#Self Join](DB/sql.md)

#### What is a CTE (Common Table Expression) and when would you use it?

A CTE (Common Table Expression) is a temporary, named result set defined with `WITH` that exists only for the duration of a single statement. You use CTEs to break complex logic into steps, avoid repeating the same subquery, improve readability/maintenance, enable recursion, and make debugging easier.

#### What is the difference between `UNION` and `UNION ALL`?

UNION removes duplicate rows from the combined result set, while UNION ALL retains all rows including duplicates. UNION ALL is faster because it doesn't perform the expensive duplicate check. Use UNION when you need distinct results, but use UNION ALL when you know there are no duplicates or when duplicates are acceptable.

For more info, see: [SQL#UNION#UNION ALL](DB/sql.md)

#### How would you calculate the running total of sales for each product?

Use a window (analytic) function: compute `SUM(amount)` over rows of the same product, ordered by time, accumulating from the start up to the current row.

For more info, see: [SQL#SUM()](DB/sql.md)

#### What are EXISTS and NOT EXISTS, and how do they differ from IN

`EXISTS` checks whether a correlated subquery returns at least one row; `NOT EXISTS` checks that it returns none. They return boolean and stop at the first match, ignoring what the subquery selects. `IN` compares a value against a list/set (literal list or subquery output).

For more info, see: [SQL#EXISTS](DB/sql.md)

#### Explain the difference between `RANK()`, `DENSE_RANK()` and `ROW_NUMBER()`.

ROW_NUMBER() assigns a unique sequential number to each row, even with ties. RANK() assigns the same rank to ties but leaves gaps in subsequent ranks. DENSE_RANK() assigns the same rank to ties but without gaps.

For more info, see: [SQL](DB/sql.md)

#### Explain the purpose of LAG and LEAD functions.

LAG and LEAD are window functions that let you look at values from previous (LAG) or next (LEAD) rows in the same result set without self-joins. They're used for comparisons across rows e.g., changes yesterday to today, detecting trends, or filling forward/backward values.

#### What is a cross join and how does it differ from an inner join?

A CROSS JOIN returns the Cartesian product — every row from the first table combined with every row from the second table. No join condition is needed. An INNER JOIN returns only matching rows based on a condition. CROSS JOIN without a WHERE clause produces all combinations, while INNER JOIN filters to only related rows.

For more info, see: [SQL#Cross Join#INNER JOIN](DB/sql.md)

#### Explain foreign keys and how they enforce referential integrity.

A foreign key (FK) is a column (or set of columns) in a child table taht references a primary/unique key in a parent table to ensure the child's values actually exist in the parent. This enforces referential integrity by preventing actions that would create "orphan" rows.

For more info, see: [SQL#Foreign Key Constraints](DB/sql.md)

#### Describe set operations like UNION, INTERSECT and EXCEPT and when each is useful.

`UNION`, `INTERSECT`, and `EXCEPT` are SQL set operations that combine results from two queries with the same number of columns and compatible data types. `UNION` returns the distinct union of both result sets (removes duplicates).

#### What are the main types of SQL commands?

SQL commands are divided into five main types based on their function, include: DDL (Data Definition Language), DQL (Data Query Language), DML (Data Manipulation Language), DCL (Data Control Language), TCL (Transaction Control Language).

For more info, see: [SQL#Commands](DB/sql.md)

#### What is the purpose of the DEFAULT constraint?

The `DEFAULT` constraint assigns a default value to a column when no value is provided during an `INSERT` operation. This helps maintain consistent data and simplifies data entry.

#### What is the purpose of the GROUP BY clause?

The `GROUP BY` clause is used to ararnge identical data into groups. It is typically used with aggregate functions to perform calculations on each group rather than on the entire dataset.

#### What is the purpose of the ALTER command in SQL?

The ALTER command is used to modify the structure of an existing database object. This command is essential for adapting our database schema as requirements evolve.

#### What are aggregate functions in SQL?

Aggregate functions perform calculations on a set of values and return a single value.

#### What is the difference between DELETE and TRUNCATE commands?

`TRUNCATE` is a DDL command, while `DELETE` is a DML command, which is why they differ in speed and logging behavior. `DELETE` removes rows one at a time and records each deletion in the transaction log, allowing rollback. It can have a `WHERE` clause. `TRUNCATE` removes all rows at once without logging individual row deletions.

For more info, see: [SQL#TRUNCATE vs DELETE](DB/sql.md)

#### What is the difference between DROP and TRUNCATE statements?

TRUNCATE removes all rows from a table but keeps the table structure intact for future use. DROP removes the entire table including its structure, indexes, constraints, and data — the table ceases to exist. TRUNCATE resets identity counters while DROP requires recreating the table from scratch.

For more info, see: [SQL#TRUNCATE vs DROP](DB/sql.md)

#### What is Collation? What are the different types of Collation Sensitivity?

Collation refers to a set of rules that determine how data is sorted and compared. Rules defining the correct character sequence are used to sort the character data. It incorporates options for specifying case sensitivity, accent marks, kana character types, and character width.

For more info, see: [SQL](DB/sql.md)

#### What are Aggregate and Scalar functions?

Aggregate functions perform calculations across multiple rows and return a single value per group. Scalar functions operate on each row individually and return one value per row. Aggregate examples include SUM, COUNT, AVG, MIN, MAX. Scalar examples include UPPER, LOWER, ROUND, LEN, DATEADD, and GETDATE.

For more info, see: [SQL#Aggregation Functions](DB/sql.md)

#### What is User-defined function? What are its various types?

A **User-Defined Function** is a reusable database routine that accepts parameters, performs calculations or data manipulation, and returns a value. Unlike stored procedures, UDFs can be used inline in SQL statements (e.g., `SELECT`, `WHERE`).

For more info, see: [SQL#User-Defined Function (UDF)](DB/sql.md)

#### What are UNION, MINUS and INTERSECT commands?

UNION, MINUS (called EXCEPT in some databases), and INTERSECT are set operators that combine results from two or more SELECT statements. UNION returns all distinct rows from both queries. INTERSECT returns only rows common to both queries. MINUS/EXCEPT returns rows from the first query that are not in the second. All require the same number and compatible types of columns.

For more info, see: [SQL#UNION](DB/sql.md)

#### What is an Alias in SQL?

An alias is a temporary, alternate name assigned to a table or column for the duration of a query. It improves readability, simplifies complex queries, and is essential for self-joins or subqueries. It does not permanently rename the database object.

For more info, see: [SQL#ALIASES](DB/sql.md)

### Query

#### What is a query in SQL?

A query is a SQL statement used to retrieve, update, or manipulate data in a database. The most common type of query is a `SELECT` statement, which fetches data from one or more tables based on specified conditons.

For more info, see: [SQL#SELECT](DB/sql.md)

#### What is a subquery?

A subquery is a query nested within another query. It is often used in the `WHERE` clause to filter data based on the results of another query, making it easier to handle complex conditons.

For more info, see: [SQL#Subquery](DB/sql.md)

#### How would you optimize a slow query?

I follow a systematic approach: First, identify the slow query using slow query logs or EXPLAIN. Then analyze the execution plan to find bottlenecks like full table scans or filesort. Next, optimize by adding indexes, rewriting the query, or adjusting schema design. Finally, measure the improvement. The most common fix is adding a covering index on columns used in WHERE, JOIN, ORDER BY, or GROUP BY clauses.

For more info, see: [Database Best Practice#Optimization](DB/best_practice.md)

#### What is the SELECT statement?

The SELECT operator in SQL is used to select data from a database. The data returned is stored in a result table, called the result-set.

For more info, see: [SQL#SELECT](DB/sql.md)

#### What are some common clauses used with SELECT query in SQL?

Some common SQL clauses used in conjuction with a SELECT query are:WHERE, ORDER BY, GROUP BY, HAVING.

For more info, see: [SQL#SELECT](DB/sql.md)

#### What is Pattern Matching in SQL?

Pattern matching in SQL is the ability to search for specific patterns within string data using special operators and wildcard characters. The most common approach is the `LIKE` operator with `%` and `_` wildcards, but modern SQL also offers `REGEXP`, `RLIKE`, and full-text search for more complex scenarios.

For more info, see: [SQL#Wildcards](DB/sql.md)

#### How do you perform pattern matching in SQL?

SQL supports pattern matching mainly with `LIKE` (and `NOT LIKE`) using wildcards `%` for any-length string and `_` for a single character.

For more info, see: [SQL#LIKE](DB/sql.md)

### Index

#### What are indexes, and why are they used?

Indexes are database objects that improve query performance by allowing faster retrieval of rows. They function like a book's index, making it quicker to find specific data without scanning the entire table. However, indexes require additional storage and can slightly slow down data modification operations.

For more info, see: [SQL#Indexes](DB/sql.md)

#### How do clustered and non‑clustered indexes differ?

A clustered index stores table rows in the physical order of the index key, so you can have only one; by contrast, A `non-clustered` index is a separate structure and you can have many.

For more info, see: [SQL#Clustered and Non-Clustered Indexing](DB/sql.md)

### Cursor

#### What is a cursor in SQL?

A cursor is a database object used to retrieve, manipulate, and traverse through rows in a result set one row at a time.

For more info, see: [SQL#Cursor](DB/sql.md)

### Trigger

#### What is a trigger in SQL?

A trigger is a set of SQL statemetns that automatically execute in response to certain events on a table, such as `INSERT`, `UPDATE`, or `DELETE`. Triggers help maintain data consistency, enforce business rules, and implement complex integrity constraints.

For more info, see: [SQL#Trigger](DB/sql.md)

### Table

#### What is a table in SQL?

A table is a structured collection of related data organized into rows and columns. Columns define the type of data stored, while rows contain individual records.

For more info, see: [SQL#Table operations](DB/sql.md)

#### How to create empty tables with the same structure as another table?

Use `CREATE TABLE new_table LIKE old_table` to copy only the structure, or `CREATE TABLE new_table AS SELECT * FROM old_table` for a condition-based approach that works across more databases.

For more info, see: [SQL#COPY TABLE](DB/sql.md)

#### What is a composite primary key?

A composite primary key uses two or more columns together to uniquely identify each row when one column alone isn't sufficient.

For more info, see: [SQL#Composite Key Constraints](DB/sql.md)

#### Describe a `PRIMARY KEY` and how it differs from a `UNIQUE` key

Both PRIMARY KEY and UNIQUE KEY enforce uniqueness on a column or set of columns. However, a PRIMARY KEY cannot contain NULL values, and a table can have only one PRIMARY KEY. A UNIQUE KEY can have multiple per table and allows a single NULL value (or multiple NULLs depending on the database). PRIMARY KEY also creates a clustered index by default in most databases, while UNIQUE creates a non-clustered index.

For more info, see: [SQL#Primary Key Constraints](DB/sql.md)

#### Explain the difference between a primary key and a foreign key in a relational database.

A primary key uniquely identifies each record within a table, while a foreign key links two table together by referencing the primary key of another table.

For more info, see: [SQL#Primary Key vs Foreign Key](DB/sql.md)

#### What are Constraints in SQL?

Constraints are used to specify the rules concerning data in the table. It can be applied for single or multiple fields in an SQL table during the creation of the table or after creating using the `ALTER TABLE` command.

For more info, see: [SQL#Constraints](DB/sql.md)

### Stored Procedure

#### What is a stored procedure?

Stored procedures are used to group SQL statements and business logic into a single reusable unit that runs inside the database.

For more info, see: [SQL#Stored Procedures](DB/sql.md)

#### What is a recursive stored procedure?

A stored procedure that calls itself until a boundary condition is reached, is called a recursive stored procedure. 

For more info, see: [SQL#Stored Procedures](DB/sql.md)

### Partitioning

#### Explain database partitioning

Database partitioning is the practice of splitting a large table (and its indexes) into smaller, more manageable pieces called partitions while keeping it logically a single table. This improves query performance, eases maintenance, and enhances availability.

For more info, see: [Database Best Practice#Partitioning](DB/best_practice.md)

### Normalization

#### Explain normalization and briefly describe the different normal forms.

Normalization is the process of organizing data to minimize redundancy and avoid anomalies (insertion, update, deletion). It involves breaking tables into smaller, related tables and defining relationships. The main normal forms are 1NF, 2NF, 3NF, and BCNF — with 3NF being the standard for most production databases.

For more info, see: [Normalization#Normal Forms](DB/normalization.md)

#### What is denormalization, and when is it used?

Denormalization is the process of combining normalized tables into larger tables for performance reasons. It is used when complex queries and joins slow down data retrieval, and the performance benefits outweigh the drawbacks of redundancy.

For more info, see: [Normalization#Denormalization](DB/normalization.md)

#### What are the various forms of Normalization?

The main normal forms are 1NF, 2NF, 3NF, and BCNF, with 4NF and 5NF as advanced forms for specialized scenarios. 1NF eliminates repeating groups, 2NF eliminates partial dependencies, 3NF eliminates transitive dependencies, and BCNF handles overlapping candidate keys. Most production databases are normalized to 3NF.

For more info, see: [Normalization#Normal Forms](DB/normalization.md)

### Safety

#### What strategies can protect a web application from SQL injection?

The primary defense against SQL injection is to use parameterized queries (prepared statements) everywhere never build SQL with string concatenation. Combines this with allow-list input validation, least-privilege DB account, and safe stored procedures that don't assemble dynamic SQL.

For more info, see: [Database Best Practice#Parameterized Query](DB/best_practice.md)

### NoSQL

#### What are the differences between SQL and NoSQL databases?

SQL is best for structured, reliable transactions, while NoSQL shines in handling massive, fast-changing, and unstructured data.

For more info, see: [SQL](DB/sql.md)

### MySQL

#### What is the difference between SQL and MySQL?

SQL is the language. MySQL is one of many systems that implements it. While MySQL follows most SQL standards, it has proprietary extensions like storage engines and the `LIMIT` clause.

For more info, see: [SQL](DB/sql.md)

#### What are the String Data Types in MySQL?

MySQL provides several string data types that differ in storage, performance, and behavior. The main categories are: CHAR, VARCHAR, TEXT, BLOB, and ENUM/SET. Choosing the right one is critical for performance and storge efficiency.

For more info, see: [MySQL Data Types](DB/MYSQL/data_type.md)

#### How to add users in MySQL?

Users are added in MySQL using the `CREATE USER` command, specifying a username, host, and password. For example: `CREATE USER 'name'@'localhost' IDENTIFIED BY 'password';` The 'host' part is critical because in MySQL, a user is identified by both the username AND the host they connect from. After creating a user, you grant privileges with `GRANT` and apply changes with `FLUSH PRIVILEGES`.

---



## Network

### Base

#### How are Network types classified?

Network types can be classified along several dimensions. At the area of the distribution level, we divided personal area network, local area network, metropolitan area network, wide area network and the internet. At the protocol level, we distinguish TCP from UDP. At the communication behavior level, we consider whether a connection is established, whether data delivery is guaranteed, and whether transmission unicast, multicast or broadcast.

#### Describe the OSI Reference Model.

The OSI (Open Systems Interconnection) Reference Model is a conceptual framework that standardizes network communication into seven layers. Each layer serves a specific function and communicates only with the layer directly above and below it. From bottom to top: Physical, Data Link, Network, Transport, Session, Presentation, and Application.

For more info, see: [Network Summary#OSI Reference Model](NET/summary.md)

#### What is the network topology?

Network topology is a physical layout of the network, connecting the different nodes using the links. It depicts the connectivity between the computers, devices, cables, etc.

For more info, see: [Network Summary#Network Topology](NET/summary.md)

#### Which topology is used in modern Ethernet networks?

Physical star (all devices connect to a central switch), but switched Ethernet creates a logical star with microsegmentation--each port is its own collision domain. This gives dedicated bandwidth to each device.

For more info, see: [Network Summary#Network Topology](NET/summary.md)

#### What's the main disadvantage of bus topology?

Single point of failure. If the backbone cable breaks anywhere, the entire network goes down. Also, performance collapses under heavy load due to collisions.

For more info, see: [Network Summary#Bus Topology](NET/summary.md)

#### Why don't we use full mesh for everything?

Cost and complexity. For n devices, you need n(n - 1) / 2 connections. It's impractical for most networks. We use partial mesh or hybrid designs instead.

For more info, see: [Network Summary#Mesh Topology](NET/summary.md)

#### What topology does the internet use?

The internet backbone uses a partial mesh of routers, with multiple redundant paths. At the edge, it uses various topologies--star in homes, tree in enterprises, etc. It's a massive hybrid topology.

#### How does ring topology handle a break?

Single ring fails completely. Dual ring (like FDDI) wraps around: when a break occurs, the two rings combine into a single ring that includes all working nodes, maintaining connectivity.

For more info, see: [Network Summary#Ring Topology](NET/summary.md)

#### Which topology is best for fault tolerance?

Full mesh provides the highest fault tolerance--every device has multiple paths. If any single connection fails, traffic reroutes automatically. For most real applications, a partial mesh offers good tolerance at lower cost.

For more info, see: [Network Summary#Mesh Topology](NET/summary.md)

#### What is the difference between a switch, router, and bridge?

A bridge connects two network segments and forwards frames based on MAC addresses (Layer 2). A switch is a multiport bridge that connects many devices, learns MAC addresses, and forwards frames only to the destination port (Layer 2). A router connects different networks and forwards packets based on IP addresses, performing routing and network address translation (Layer 3). Bridges and switches are mostly obsolete for modern networks; switches replaced bridges, and routers connect networks (including to the internet).

For more info, see: [Routing](NET/routing.md)

#### What is the use of a router and how is it different from a gateway?

A router forwards data between different networks by directing traffic based on IP addresses. A gateway is a broader term--it's any device that acts as an entry/exit point between networks. While a router can function as a gateway, a gateway isn't necessarily a router; it could be a firewall, proxy server, or NAT device. The key difference: routers always operate at Layer 3 (network layer), while gateways can operate at any layer and often perform protocol translation.

For more info, see: [Routing#Router](NET/routing.md)

#### Can a switch function as a gateway?

Generally no! Switches operate at Layer 2 and don't understand IP addresses. A gateway needs to operate at Layer 3 or higher. However, a 'layer 3 switch' (multilayer switch) can perform routing functions and could serve as a gateway.

For more info, see: [Routing#Gateway](NET/routing.md)

#### What happens when i remove the default gateway from my device?

Your device can only communicate within its local subnet. Any attempt to reach a different subnet (including the internet) will fail because the device doesn't know where to send packets destined outside its networks.

For more info, see: [Routing#Gateway](NET/routing.md)

#### What's the difference between a gateway and a proxy?

A proxy operates at the application layer (Layer 7) and is application-specific (HTTP proxy, SOCKS proxy). A gateway can operate at multiple layers. All proxies are a type of gateway, but not all gateways are proxies. A router acting as a default gateway is NOT a proxy.

For more info, see: [Routing#Gateway](NET/routing.md)

#### What are the different types of network delays?

Network delays fall into four main categories: Processing delay (time to process packet header), Queuing delay (time waiting in output queue), Transmission delay (time to push bits onto wire), and Propagation delay (time for signal to travel the physical medium). Total delay = Processing + Queuing + Transmission + Propagation.

For more info, see: [Network Delay](NET/delay.md)

#### How does SSL/TLS work? What happens during a TLS handshake?

TLS (Transport Layer Security) is a cryptographic protocol that provides encryption, authentication, and integrity for network communications. During the TLS handshake, client and server negotiate cipher suites, exchange certificates for authentication, and generate session keys using asymmetric cryptography (RSA or ECDHE). The handshake establishes a shared secret without exposing it, then switches to symmetric encryption (AES) for bulk data transfer. This entire process happens in milliseconds before any application data is sent.

For more info, see: [SSL/TLS](NET/ssl.md)

#### What is a VLAN (Virtual LAN)?

A VLAN (Virtual LAN) is a logical segmentation of a physical network into multiple isolated broadcast domains. Devices in different VLANs cannot communicate directly without a router or Layer 3 switch, even if they're connected to the same physical switch. VLANs improve security by isolating traffic, reducing broadcast storms, simplifying network management, and helping enforce security policies.

For more info, see: [Virtual LAN (VLAN)](NET/vlan.md)

### IP

#### What are private and special IP addresses?

Private IP addresses are reserved ranges used exclusively within internal networks and cannot be routed on the public internet. Special IP addresses serve specific purposes like loopback testing, broadcasting, or automatic configuration.

For more info, see: [Internet Protocol (IP)#Special IP Addresses](NET/ip.md)

#### What is an IPv4 address?

An IPv4 address is a 32-bit numerical identifier assigned to devices on a network, written in dotted-decimal notation as four 8-bit octets. It has two main parts: the network portion (identifies the subnet) and the host portion (identifies the specific device).

For more info, see: [Internet Protocol (IP)#IPv4](NET/ip.md)

#### How many IPv4 addresses exist?

$2^{32} = 4,294,967,296$. But subtract special addresses (loopback, private ranges, multicast, broadcast), and about 3.7 billion are potentially usable for public internet.

For more info, see: [Internet Protocol (IP)#IPv4](NET/ip.md)

#### What does the 255 in subnet masks represent?

255 in decimal equals 11111111 in binary--all 8 bits set to 1. In a subnet mask, each 255 means 'these bits belong to the network portion'.

For more info, see: [Internet Protocol (IP)](NET/ip.md)

#### What's the difference between IPv4 and IPv6?

IPv4 uses 32-bit addresses written in dotted-decimal, while IPv6 uses 128-bit addresses written in hexadecimal. IPv6 eliminates NAT, has built-in security (IPsec), simpler headers for faster routing, and autoconfiguration capabilities. The transition is necessary due to IPv4 exhaustion.

For more info, see: [Internet Protocol (IP)#IPv4 vs IPv6](NET/ip.md)

#### What is NAT (Network Address Translation)?

NAT (Network Address Translation) is a technique that maps private IP addresses to public IP addresses, allowing multiple devices on a private network to share a single public IP address when accessing the internet. It operates at the network layer, modifying IP headers in transit.

For more info, see: [Network Address Translation (NAT)](NET/nat.md)

#### How does IPv6 solve the NAT problem?

IPv6 doesn't need NAT because there are enough addresses for every device to have a globally unique public IP. This restores end-to-end connectivity, making peer-to-peer applications, VoIP, and gaming work nativelly without complex NAT traversal techniques.

For more info, see: [Network Address Translation (NAT)](NET/nat.md)

#### What are port numbers?

Port numbers are 16-bit identifiers (0-65535) that allow multiple network services to run on the same IP address. They differentiate between different applications or services on the same host. Ports are divided into Well-Known Ports, Registered Ports, and Dynamic/Private Ports.

For more info, see: [Internet Protocol (IP)#IPv6](NET/ip.md)

#### What's the equivalent of 127.0.0.1 in IPv6?

`::1`. It's a 128-bit address with 127 zeros and a single 1 at the end.

For more info, see: [Internet Protocol (IP)#IPv6](NET/ip.md)

#### What are the differnt types of VPN?

VPNs are broadly classified into three main types by deployment: Remote Access VPN, Site-to-Site VPN, and Personal VPN. By protocol, common types include IPsec, SSL/TLS, OpenVPN, WireGuard, and IKEv2. The right choice depends on use case, security requirements, and platform compatibility.

For more info, see: [Network Address Translation (NAT)#Types of VPN](NET/nat.md)

#### What are the advantages of using a VPN?

The primary advantages of using a VPN are security, privacy, and access control. It creates an encrypted tunnel between a user's device and a remote network, protecting data from interception, masking the user's real IP address, and allowing secure access to private network resources from untrusted locations like public Wi-Fi or the internet.

For more info, see: [Network Address Translation (NAT)#Virtual Private Networks (VPNs)](NET/nat.md)

#### What is TTL?

TTL (Time To Live) is an 8-bit field in the IP header that prevents packets from circulating forever in the network. Each router decrements the TTL by 1 when forwarding a packet. If TTL reaches 0, the router discards the packet and sends an ICMP Time Exceeded message back to the sender. This mechanism limits the packet's lifetime, typically to 64 or 128 hops, preventing infinite loops due to routing errors.

For more info, see: [Internet Protocol (IP)#IPv4 header](NET/ip.md)

#### Explain subnetting and CIDR notation.

Subnetting divides a large IP network into smaller, manageable sub-networks by borrowing bits from the host portion of the IP address for the network portion. CIDR (Classless Inter-Domain Routing) notation represents IP addresses with a suffix indicating the number of network bits.

For more info, see: [Internet Protocol (IP)#Classless Inter-Domain Routing (CIDR)](NET/ip.md)

### TCP

#### Explain the TCP three-way handshake in detail.

The TCP three-way handshake establishes a reliable connection between client and server. Step 1: Client sends SYN (synchronize) packet with a random sequence number (client_isn). Step 2: Server responds with SYN-ACK, acknowledging client's sequence number (ACK = client_isn + 1) and sending its own random sequence number (server_isn). Step 3: Client sends ACK, acknowledging server's sequence number (ACK = server_isn + 1). After this, both sides can send data. The handshake synchronizes sequence numbers and negotiates TCP options like window scaling.

For more info, see: [TCP Protocol#Connection Establishment and Termination](NET/tcp.md)

#### Explain how to create a simple TCP server that accepts one client connection and sends msg back.

Creating a simple TCP server involves a standard sequence of steps: creating a socket, binding it to an address and port, listening for incoming connections, accepting a client, communicating and closing the connection.

For more info, see: [TCP Protocol](NET/tcp.md), [Socket Programming](NET/socket.md)

#### How to use `select()` to handle multiple client connections in a non-blocking TCP server.

Set all sockets (listening and client) to non-blocking mode and use an event loop to monitor their activity. The `select()` call blocks the server until an event occurs on one or more of the monitored file descriptors.

For more info, see: [TCP Protocol](NET/tcp.md), [Socket Programming](NET/socket.md)

#### How to handle connection timeout in a TCP client by using `setsockopt()` and `select()`.

Setting explicit timeouts on connection(example for linux: `setsockopt(..., SO_RCVTIMEO/SO_SNDTIMEO)`), and use `select(..., timeval)` to wait with a timeout.

For more info, see: [Socket Programming#Timeout Handling](NET/socket.md)

### UDP

#### How to implement a UDP client-server communication for sending and receiving messages.

Creating a connectionless link using datagram sockets. The server bind port and listen for incoming packets, and the client sends datagrams to the server's address and port without formally establishing a connection first.

For more info, see: [UDP Protocol](NET/udp.md), [Socket Programming#UDP Socket Programming](NET/socket.md)

### HTTP/HTTPS

#### What are the HTTP and the HTTPS protocol?

HTTP (HyperText Transfer Protocol) is the foundational protocol for web communication, defining how clients (browsers) request resources from servers. It operates on port 80 and transmits data in plain text, making it vulnerable to eavesdropping. HTTPS (HTTP Secure) adds a TLS/SSL encryption layer on top of HTTP, running on port 443. HTTPS provides confidentiality (encryption), integrity (can't be altered), and authentication (verifies server identity via certificates).

For more info, see: [HTTP Protocol#HTTP vs HTTPS](NET/http.md)

### DNS

#### What is the DNS?

DNS (Domain Name System) translates human-readable domain names into machine-readable IP addresses. It's a distributed, hierarchical database that acts as the internet's phonebook, allowing users to access websites without memorizing numeric IP addresses.

For more info, see: [Domain Name System (DNS)](NET/dns.md)

#### What happens when you type a URL into a browser?

First, the browser checks its DNS cache. If not found, it asks the OS resolver, which checks `/etc/hosts` and its own cache. Then the request goes to the configured DNS resolver. That resolver performs iterative queries starting at the root servers, then the TLD servers, then the authoritative nameservers for the domain, and finally returns the IP address. The browser then opens a TCP connection to that IP.

For more info, see: [Domain Name System (DNS)#Workflow](NET/dns.md)

#### What's the difference between A and CNAME records?

An A record maps a domain directly to an IPv4 address. A CNAME maps a domain to another domain name (an alias). CNAME can't be used for the root domain (apex) of a zone.

For more info, see: [Domain Name System (DNS)#DNS Record Types](NET/dns.md)

#### Why is DNS distributed instead of centrialized?

Centralized DNS would be a single point of failure, couldn't handle billions of queries per second, and one organization would control the entire internet's naming system. Distribution provides redundancy, load balancing, and allows organizations to manage their own domains.

For more info, see: [Domain Name System (DNS)](NET/dns.md)

#### What's DNS propagation?

DNS doesn't actually 'propagate'--it's not a push system. When you change DNS records, caches expire based on their TTL values. 'Propagation' refers to the time it takes for all caches around the world to expire and fetch the new record. Maximum propagation time is the old TTL value, typically 24-48 hours.

For more info, see: [Domain Name System (DNS)](NET/dns.md)

#### What happens when a DNS server goes down?

Cached records continue to work until they expire. If the authoritative server for a domain goes down, existing caches still serve the domain for the remaining TTL period. Once caches expire, the domain becomes unreachable. This is why we use multiple authoritative nameserver for reduendancy.

For more info, see: [Domain Name System (DNS)](NET/dns.md)

#### What's split-horizon DNS?

Different DNS answers based on the requester's location. Internal users get private IP addresses for internal servers, external users get public IPs. This allows using the same domain name internally and externally with different resolutions.

For more info, see: [Domain Name System (DNS)](NET/dns.md)

### SMTP

#### What is the SMTP protocol?

SMTP (Simple Mail Transfer Protocol) is the standard protocol for sending email between servers on the internet. SMTP is a push protocol that transfers outgoing mail from a client to a server and between servers, but it cannot receive messages — that's handled by POP3 or IMAP.

For more info, see: [SMTP Protocol](NET/smtp.md)

### IO

#### How to use `poll()` instead of `select()` for handling multiple connections, and what advantages it offers.

First define a struct `pollfd` array, then initialize the structures, then pass the array to `poll()`, finally check `revents`.

`poll()` offering better scalability and efficiency than `select()`, and not file descriptor limit.

For more info, see: [Network I/O](NET/tcp.md)

#### How to use non-blocking I/O with `epoll` for handling high-concurrency network connections.

Configure all sockets as non-blocking, create an `epoll` instance to monitor events, and use an event loop with `epoll_wait()` to handle I/O on ready socket without blocking.

For more info, see: [Network I/O#epoll](NET/tcp.md)

---



## Algorithm

### Base

#### How can we compare between two algorithmns written for the same problem?

We compare algorithms primarily by their complexity and space complexity. But for real-world decisions, we also consider constants, input characteristics, implementation ease, and data cache behavior.

For more info, see: [Algorithm Summary#Complexity Analysis](ALGO/summary.md), [Big O Notation](ALGO/list.md)

#### What do you understand by the Asymptotic Notations?

Asymptotic notations are mathematical tools used to describe the limiting behavior of algorithm's time or space complexity as input size grows to infinity. The three main notations are: Big-O (O) - upper bound (worst-case), Omega (Ω) - lower bound (best-case), and Theta (Θ) - tight bound (average).

For more info, see: [Algorithm Summary#Complexity Analysis](ALGO/summary.md), [Big O Notation](ALGO/list.md)

#### What do you understand by the best case, worst case and average case scenario of an algorithm?

Best case, worst case, and average case describe algorithm performance under different input conditions. Best case is the minimum time for the most favorable input (e.g., already sorted array for sorting). Worst case is the maximum time for the worst possible input (e.g., reverse sorted for sorting). Average case considers typical input distribution (e.g., random order). These analyses help choose algorithms based on guaranteed performance (worst case) or expected performance (average case).

For more info, see: [Algorithm Summary#Complexity Analysis](ALGO/summary.md)

### Linked List

#### What are the differences between an `array` and a `list`?

The main differences are in the memory layout. Arrays store elements contiguously in memory, providing random access. List store elements non-continuously via pointers, **not providing** random access.

For more info, see: [Linked List#Diagrams](ALGO/list.md)

#### Reverses a linked list iteratively using three pointers: current, previous, and next.

At each step, point the current node to its previous node and then move all three pointers forward until the list is fully reversed.

For more info, see: [Linked List#Reverse](ALGO/list.md), [Linked List Problems](ALGO/LEET_CODE/linked_list.md)

#### Finds the middle of a linked list using the slow and fast pointer technique.

The idea is to traverse the entire linked list once to count the total number of nodes. After determining the total count, traverse the list again and stop the middle node to return its value.

For more info, see: [Linked List#Reverse](ALGO/list.md), [Linked List Problems](ALGO/LEET_CODE/linked_list.md)

#### Detecting a cycle in a linked list.

Using Floyd's Algorithm is the best choice with average time complexity equal to O(n).

For more info, see: [Linked List](ALGO/list.md), [Linked List Problems](ALGO/LEET_CODE/linked_list.md)

### Binary Tree

#### Checks if a binary tree is balanced using a recursive approach.

Define a function that simultaneously calculates the height of the tree and checks for the balance condition. Calculate the absolute difference between left height and right heigh, if the difference is greater than 1, it is unbalanced. otherwise, it is balanced.

For more info, see: [Binary Tree#Balanced Binary Tree](ALGO/binary_tree.md), [Binary Tree Problem](ALGO/LEET_CODE/binary_tree.md)

#### Find the lowest common ancestor in a binary search tree.

We just recursively traverse the BST(binary search tree), if node's value is greater than both n1 and n2 then our LCA lies in the left side of the node, if it is smaller than both n1 and n2, then LCA lies on the right side. Otherwise, the root is LCA.

For more info, see: [Binary Tree](ALGO/binary_tree.md), [Binary Tree Problem](ALGO/LEET_CODE/binary_tree.md)

#### Check if a binary tree is a valid binary search tree using in-order traversal.

Traverse the tree and verify that each element encountered is greater than the previous one.

For more info, see: [Binary Tree](ALGO/binary_tree.md), [Binary Tree Problem](ALGO/LEET_CODE/binary_tree.md)

#### Level-Order traversal of a binary tree. Process each level layer by layer, storing nodes in a list. Classic for breadth-first search.

Using BFS(Breadth First Search) level order raversal a binary tree, using a linked list container to save the node value.

For more info, see: [Binary Tree](ALGO/binary_tree.md), [Binary Tree Problem](ALGO/LEET_CODE/binary_tree.md)

#### Counting the number of leaf nodes in a binary tree.

Count leaf nodes by traversing the tree and incrementing a counter whenever we find a node with no children. Both recursive and iterative approaches work in O(n) time with O(h) space, where h is the tree height.

For more info, see: [Binary Tree](ALGO/binary_tree.md), [Binary Tree Problem](ALGO/LEET_CODE/binary_tree.md)

#### Define tree traversal and list some of the algorithms to traverse a binary tree.

Tree traversal is the process of visiting each node in a tree exactly once. For binary trees, the main traversal algorithms are: Depth-First Search (DFS) and Breadth-First Search (BFS) or Level Order traversal.

For more info, see: [Binary Tree](ALGO/binary_tree.md)

### Dynamic Programming

#### What is dynamic programming and how does it differ from other methods?

Dynamic programming breaks down complex problems into smaller, simpler subproblems and stores solutions to avoid repeating calculations, unlike other methods that may solve problems directly without reusing solutions.

For more info, see: [Dynamic Programming Algorithm](ALGO/dynamic_programming.md)

#### What kinds of problems are suitable for dynamic programming solutions?

Dynamic programming works well for problems with overlapping subproblems and optimal substructure, meaning solutions can be built from smaller optimal solutions.

For more info, see: [Dynamic Programming Algorithm](ALGO/dynamic_programming.md)

#### What is memoization in dynamic programming and why is it useful?

Memoization involves storing previously calculated results to avoid redundant computations in recursive algorithms, saving time and improving efficiency. Memoization is used in Top-Down approach.

For more info, see: [Dynamic Programming Algorithm](ALGO/dynamic_programming.md)

#### What's the difference between top-down and bottom-up dynamic programming?

Top-down starts from the top and breaks down the problem recursively, while bottom-up builds solutions iteratively from the smallest subproblems.

#### Given an array and a target, how'd you use dynamic programming to find the two numbers that add up to the target?

Using dynamic programming to fix this problem is **NOT RECOMMEND**, it's the worst choice with time complexity = O(n × target) in average case.

For more info, see: [Dynamic Programming](ALGO/LEET_CODE/dynamic_programming.md)

### Greedy Algorithm

#### What is a greedy algorithm?

A greedy algorithm makes locally optimal choices at each step with the hope of finding a global optimum solution.

For more info, see: [Greedy Algorithm](ALGO/greedy_algorithm.md)

#### What is greedy algorithm used for?

Greedy algorithms are primarily used for optimization problems where making locally optimal choices at each step leads to finding a globally optimal solution. They find applications in various domains such as scheduling, routing, resource allocation and combinatorial optimization.

For more info, see: [Greedy Algorithm#Suitcase](ALGO/greedy_algorithm.md)

#### Explain Dijkstra's algorithm and its application.

Dijkstra's algorithm finds the shortest path from a source node to all other nodes in a weighted graph with non-negative edge weights. It works by greedily selecting the unvisited node with the smallest known distance, updating its neighbors' distances, and marking it as visited. This process repeats until all nodes are visited.

For more info, see: [Shortest-Path Algorithms#Dijkstra's algorithm ](ALGO/shortest_path_problem.md)

#### What is Huffman coding and how does it utilize a greedy strategy to compress data?

Huffman coding is a technique for lossless data compression where characters are represented by variable-length codes. It uses a greedy strategy to assign shorter codes to more frequent characters.

For more info, see: [Huffman Codes](ALGO/huffman.md)

### Recursive Algorithm

#### What is recursion and how does it work?

Recursion is a programming technique where a function calls itself to solve a problem.

For more info, see: [Recursion](ALGO/recursion.md)

#### State the important rules which every recursive algorithm must follow.

Every recursive algorithm must follow three essential rules: First, it must have a base case that terminates the recursion (no further recursive calls). Second, it must make progress toward the base case with each recursive call (typically by reducing the problem size). Third, it must call itself recursively to solve smaller subproblems. Additionally, for efficiency, avoid overlapping subproblems (use memoization) and ensure the recursion depth doesn't exceed stack limits.

For more info, see: [Recursion](ALGO/recursion.md)

### Divide and Conquer Algorithm

#### Explain the Divide and Conquer Algorithmic Paradigm. Also list a few algorithms which use this paradigm.

Divide and Conquer is an algorithmic paradigm that solves a problem by breaking it into smaller, independent subproblems of the same type, recursively solving each subproblem, and then combining their results to solve the original problem. Classic examples include Merge Sort, Quick Sort, Binary Search, etc.

For more info, see: [Search Algorithm Summary](ALGO/search.md), [Divide and Conquer Algorithm](ALGO/LEET_CODE/divide_and_conquer.md)

#### Split the array in half, sort both halves, then merge them back.

We use the two positions (left, right) divide the array continuously, until array's size equal to 2; then sorted it.

For more info, see: [Search Algorithm Summary](ALGO/search.md), [Divide and Conquer Algorithm](ALGO/LEET_CODE/divide_and_conquer.md)

### Backtracking Algorithm

#### Generates all permutations of a string using recursion and backtracking.

First, initialize an array of strings `arr[]` to store all the permutations. Start from the 0th index and for each index `i`, swap the value `str[i]` with all the elements in its right i.e. From `i + 1` to `n - 1`, and recur to the index `i + 1`. If the index `i` is equal to `n`, store the resultant string in `arr[]`, else keep operating similarly for all other indices. Thereafter, swap back the values to original values to initiate backtracking. At last sort the array `arr[]`.

For more info, see: [Backtracking Problem](ALGO/LEET_CODE/backtracking.md)

### Searching

#### What is a searching algorithm?

A searching algorithm is a method used to find a specific item within a collection of data. Searching Algorithms are designed to check for an element or retrieve an element from any data structure where it is stored.

For more info, see: [Searching Algorithm Summary](ALGO/search.md)

#### What are the different types of searching algorithms?

Searching algorithms include Linear Search, Binary Search, Depth-First Search (DFS), Breadth-First Search(BFS) and Hashing, each with its own approach to find elements.

For more info, see: [Searching Algorithm Summary](ALGO/search.md)

#### When is each searching algorithm most appropriate to use?

Choose the appropriate searching algorithm based on factors like data structure, data size and desired search efficiency, such as Binary Search for sorted arrays and Hashing for constant-time searches.

For more info, see: [Searching Algorithm Summary](ALGO/search.md)

#### How deos Hashing work in searching?

Hashing uses a hash function to compute an index for each element, allowing for constant-time search operations in the average case by storing elements in a hash table.

For more info, see: [Searching Algorithm Summary#Hash-Based Search](ALGO/search.md)

#### What do you understand about the DFS(Depth First Search) algorithm.

DFS is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It uses a stack (explicitly or via recursion) and has $O(V + E)$ time complexity. It's particularly useful for pathfinding in mazes, topological sorting, detecting cycles, and solving puzzles.

For more info, see: [Searching Algorithm Summary#Depth-First Search (DFS)](ALGO/search.md)

#### Can DFS get stuck in infinite loops?

Only if we forget to mark nodes as visited. With proper visit tracking, it terminates in $O(V + E)$ time.

For more info, see: [Searching Algorithm Summary#Depth-First Search (DFS)](ALGO/search.md)

#### What do you understand about the BFS (Breadth First Search) algorithm?

BFS is a graph traversal algorithm that explores vertices in layers, visiting all neighbors at the current depth before moving to the next level. It uses a queue (FIFO) and has $O(V + E)$ time complexity. BFS guarantees the shortest path in unweighted graphs and is ideal for finding minimum steps, web crawling, and social network analysis.

For more info, see: [Searching Algorithm Summary#Breadth-First Search (BFS)](ALGO/search.md)

#### How to find the shortest path in a grid with obstacles using BFS?

Treat each cell as a node, with edges to adjacent open cells. BFS guarantees the shortest path because all edges have uniform weight (1 step). Track parent pointers to reconstruct path.

For more info, see: [Searching Algorithm Summary#Breadth-First Search (BFS)](ALGO/search.md)

#### What's the space complexity of BFS on a complete binary tree of height h?

$O(2^h)$ in worst case because the last level has $2^h$ nodes, all potentially in the queue simultaneously. This is why BFS is memory-intensive for deep trees.

For more info, see: [Searching Algorithm Summary#Breadth-First Search (BFS)](ALGO/search.md)

#### How to optimize BFS for very large graphs?

Use bidirectional BFS(search from both ends), use bitsets for visited tracking, consider IDDFS if depth is known, or use `A*` with a heuristic if applicable.

For more info, see: [Searching Algorithm Summary#Breadth-First Search (BFS)](ALGO/search.md)

#### When would you choose DFS over BFS?

DFS when memory is constrained (depth < width), when finding any path (not shortest), for topological sorting, or when solving puzzles like Sudoku. BFS when finding shortest path in unweighted graphs or when the graph is wide but shallow.

For more info, see: [Searching Algorithm Summary#DFS vs BFS](ALGO/search.md)

#### Explain Linear Search and its time complexity.

Linear Search checks each element in a list one by one until finding the target or reaching the end. Its time complexity is $O(n)$ in the worst case.

For more info, see: [Searching Algorithm Summary#Linear Search](ALGO/search.md)

#### Describe the Binary Search Algorithm.

Binary search is an efficient algorithm for finding a target value within a sorted array. It works by repeatedly dividing the search interval in half. It compares the target to the middle element; if they are not equal, it eliminates the half where the target cannot lie and continues searching the remaining half. Binary search requires the array to be sorted and can be implemented both iteratively and recursively.

For more info, see: [Searching Algorithm Summary#Binary Search](ALGO/search.md)

#### How does Binary Search work?

Binary Search divides a sorted array in half repeatedly, narrowing down the search space by comparing the target with the mid until finding the target or exhausting the elements.

For more info, see: [Searching Algorithm Summary#Binary Search](ALGO/search.md)

#### Recursive and Iterative Binary Search: Which one is more efficient and why?

Iterative Binary Search is typically more efficient than Recursive Binary Search. This is because iterative binary search avoids teh overhead of recursive function calls and tasks space consumption, resulting in lower memory usage and potentially faster execution, especially for large datasets.

For more info, see: [Searching Algorithm Summary#Binary Search](ALGO/search.md)

#### Can we use the binary search algorithm for linked lists?

No, standard binary search cannot be applied to singly linked lists because binary search requires O(1) random access to find the middle element.

For more info, see: [Searching Algorithm Summary#Binary Search](ALGO/search.md)

#### What are the requirements for using Binary Search?

Binary Search requires a sorted array and the ability to access elements by index for efficient traversal.

For more info, see: [Searching Algorithm Summary](ALGO/search.md)

#### Compare Linear Search and Binary Search

Linear Search checks elements sequentially, while Binary Search halves teh search space with each step, making it more efficient for sorted data with a time complexity of $O(\log n)$.

For more info, see: [Searching Algorithm Summary#Complixity Analysis](ALGO/search.md)

#### Recursive and Iterative Binary Search: Which one is more efficient and why?

Iterative Binary Search is typically more efficient than Recursive Binary Search. This is because iterative binary search avoids the overhead of recursive function calls and stack space consumption, resulting in lower memory usage and potentially faster execution, especially for large datasets.

For more info, see: [Searching Algorithm Summary#Complixity Analysis](ALGO/search.md)

#### What's the worst scenario in Binary Search?

Binary search's worst-case time complexity is $O(\log n)$, which is excellent. However, the worst-case scenario occurs when the target element is not in the array (or is at the first/last position requiring full search depth), requiring approximately $\log_2{(n)}$ comparisons. The real 'worst case' for binary search is when it's applied incorrectly--on unsorted data, on linkede lists, or with integer overflow bugs in mid-point calculation.

For more info, see: [Searching Algorithm Summary#Complixity Analysis](ALGO/search.md)

#### Why use binary search if there is a ternary search?

Binary search is preferred for finding specific values in sorted arrays, as it divides the search space in half with each step, resulting in efficient searches with a time complexity of $O(\log_2 n)$. Binary Search is useful for finding maximum or minimum value in a Monotonic function whereas Ternary search is useful for finding the maximum or minimum value in a unimodal function. Also, the time complexity of Ternary Search is $O(2 * \log_3 N)$ which is greater than $O(\log_2 n)$.

For more info, see: [Searching Algorithm Summary#Ternary Search](ALGO/search.md)

#### Can you write a function that finds the first non-repeating character in a string?

Using a container to count character times.

For more info, see: [Search Problem](ALGO/LEET_CODE/search.md)

#### Given a sorted array, find two numbers that add up to a target. Write the code using two pointers.

Using a container(e.g. unordered_map) to cache parameters.

For more info, see: [Search Problem](ALGO/LEET_CODE/search.md)

#### Write a function that checks if a string is a palindrome using two iterators.

Using a index move from begin to end, another index move from end to begin; compare two index, if not equal, it's not palindrome, eitherwise, it's palindrome.

For more info, see: [Search Problem](ALGO/LEET_CODE/search.md)

#### Write a function that removes duplicates from a sorted vector using the two-pointer technique.

Using a index move from o to end, another index move from 1 to end; compare two index, if not equal, move two index; else, erase the right index position.

For more info, see: [Search Problem](ALGO/LEET_CODE/search.md)

#### Checks if two strings are anagrams using character frequency counting.

Use either a fixed-size array or a `std::unordered_map` to storage character frequency counting.

For more info, see: [Search Problem](ALGO/LEET_CODE/search.md)

#### Finds the maximum sum of any contiguous subarray using Kadane's algorithm.

Kadane's algorithm finds the maximum sum of any contiguous subarray in O(n) time. It works by keeping track of the current subarray sum and resetting it to 0 if it becomes negative because a negative prefix only reduces future sums. The maximum sum seen so far is tracked separately. This elegantly handles all negative numbers by always keeping at least one element.

For more info, see: [Search Algorithm Summary#Kadane's Algorithm](ALGO/search.md), [Search Problem](ALGO/LEET_CODE/search.md)

#### Given an unsorted array of integers, how would you find the kth smallest element efficiently?

The most efficient average-case solution is Quick Select (a variation of Quick Sort), which offers O(n) average time complexity and O(1) space. For guaranteed worst-case performance, you can use Median of Medians (O(n) worst-case) or a Min-Heap of size k (O(n log k)).

For more info, see: [Search Algorithm Summary](ALGO/search.md), [Search Problem](ALGO/LEET_CODE/search.md)

#### Given a stream of integers, how would you efficiently find the median of the elements seen so far at any given time?

To efficiently find the median of a **dynamic stream** of integers, use the **Two-Heap (or Median Heap)** approach: maintain a **max-heap** for the lower half and a **min-heap** for the upper half. Ensure the heap sizes differ by at most 1, with the max-heap containing the lower half. The median is the top of the larger heap (odd total) or the average of both tops (even total).

For more info, see: [Heap](ALGO/heap.md), [Search Problem](ALGO/LEET_CODE/search.md)

### Sorting

#### What is a sorting algorithm?

A sorting algorithm is a method used to arrange elements in a specific order, often from smallest to largest or vice versa, making data easier to manage and search.

For more info, see: [Sorting Algorithm Summary](ALGO/sort.md)

#### Why Sorting algorithms are important?

The effectiveness of other algorithms that depend on input data being in sorted lists is enhanced by efficient sorting. Sorting is also frequently helpful for generating output that is readable by humans. Sorting is directly used in divide-and-conquer strategies, database algorithms, data structure algorithms and many other applications.

For more info, see: [Sorting Algorithm Summary](ALGO/sort.md)

#### What are the different types of sorting algorithms?

There are two types of Sorting algorithms: Comparison based sorting algorithms and non-comparison-based sorting algorithms. Comparison based sorting algorithms include: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort, Heap Sort, etc. and non-comparison-based sorting algorithms include Radix Sort, Counting Sort and Bucket Sort.

For more info, see: [Sorting Algorithm Summary](ALGO/sort.md)

#### What is the difference between comparison-based and non-comparison-based sorting algorithms

Comparison-based sorting algorithms compare elements to determine their order, while non-comparison-based algorithms use other techniques, like counting or bucketing, to sort elements without direct comparisons.

For more info, see: [Sorting Algorithm Summary](ALGO/sort.md)

#### Which sort algorithm works best on mostly sorted data?

For mostly sorted data, Insertion Sort typically works best. It's efficient when elements are mostly in order because it only needs to make small adjustments to place each element in its correct position, making it faster than other sorting algorithm like Quick Sort or Merge Sort.

For more info, see: [Sorting Algorithm Summary#Insertion Sort](ALGO/sort.md)

#### What is the insertion sort algorithm?

Insertion sort is a simple sorting algorithm that builds the final sorted array one element at a time. It works by taking each element from the unsorted portion and inserting it into its correct position in the already-sorted portion, shifting larger elements to the right.

For more info, see: [Sorting Algorithm Summary#Insertion Sort](ALGO/sort.md)

#### What is the space complexity of the insertion sort algorithm?

Insertion Sort has a space complexity of O(1), or constant space. It sorts the array in-place, using only a handful of extra variables regardless of input size. The algorithm maintains a 'key' variable for the element being inserted, along with loop counters and an index variable for shifting elements. No additional data structures are allocated that grow with the input size.

For more info, see: [Sorting Algorithm Summary#Insertion Sort](ALGO/sort.md)

#### Describe the merge sort algorithm.

Merge sort is a divide-and-conquer sorting algorithm that recursively divides the array into halves until each subarray has one element, then merges them back together in sorted order.

For more info, see: [Sorting Algorithm Summary#Merge Sort](ALGO/sort.md)

#### Why is Merge sort preferred over Quick Sort for sorting linked lists?

Merge Sort is preferred fro sorting linked lists because its divide-and-conquer approach easily divides the list into halves and merges them efficiently without requiring random access, which is difficult in linked lists. Quick Sort's reliance on random access and potential worst-case time complexity makes it less suitable for linked lists.

For more info, see: [Sorting Algorithm Summary#Merge Sort](ALGO/sort.md)

#### What is Stability in sorting algorithm and why it is important?

Stability in sorting algorithms means that the relative order of equal elements remains unchanged after sorting. Stable sorting algorithms ensure that equal elements maintain their original positions in the sorted sequence.

For more info, see: [Sorting Algorithm Summary#Complexity](ALGO/sort.md)

#### What is the best sorting algorithm for large datasets?

For large datasets, efficient sorting algorithms like Merge Sort, Quick Sort or Heap Sort are commonly used due to their average time complexity of $O(n \log n)$, which performs well even with large amounts of data.

For more info, see: [Sorting Algorithm Summary#Complexity](ALGO/sort.md)

#### How does Quick Sort work?

Quick Sort is a Divide and Conquer sorting algorithm. It chooses a pivot element and rearrange the array so that elements smaller than the pivot are on the left and elements greater are on the right. Then, recursively apply the partitioning process to the left and right subarrays. Subarrays of size one or zero are considered sorted.

For more info, see: [Sorting Algorithm Summary#Quick Sort](ALGO/sort.md)

#### What is the worst-case time complexity of Quick Sort?

In the worst case, Quick Sort may take $O(N^2)$ time to sort the array. The worst case will occur when every time the problem of size $N$, get divided into 2 subproblems of size 1 and $N - 1$.

For more info, see: [Sorting Algorithm Summary#Quick Sort](ALGO/sort.md)

#### Explain the worst-case scenario for Quick Sort and how you might avoid it?

Quick Sort's worst-case time complexity is $O(n^2)$, which occurs when the pivot selection consistently results in highly unbalanced partitions--specifically, when the array is already sorted (or reverse sorted) and the pivot is always chosen as the first or last element. This can be avoided by using randomized pivot selection.

For more info, see: [Sorting Algorithm Summary#Quick Sort](ALGO/sort.md)

#### What is the selection sort algorithm?

Selection sort is a simple sorting algorithm that repeatedly finds the minimum element from the unsorted portion and swaps it with the first unsorted element. It works in-place and runs in O(n²) time for all cases (best, average, worst) because it always scans the entire unsorted portion to find the minimum. Selection sort is not stable by default but can be made stable with modifications. It's easy to implement and has minimal writes (n swaps), making it good for data where writes are expensive.

For more info, see: [Sorting Algorithm Summary#Selection Sort](ALGO/sort.md)

#### What is the space complexity of the selection sort algorithm?

Selection Sort has a space complexity of O(1), or constant space. It operates in-place, meaning it sorts the array by swapping elements without requiring additional data structures that grow with input size. Regardless of whether you're sorting 10 elements or 10 million elements, Selection Sort only uses a few extra variables (like indices for tracking min/max positions and temporary swap storage).

For more info, see: [Sorting Algorithm Summary#Selection Sort](ALGO/sort.md)

#### Describe the heap sort algorithm.

Heap sort is a comparison-based sorting algorithm that uses a binary heap data structure. It works in two phases: First, build a max heap from the input array ($O(n)$). Second, repeatedly extract the maximum element (the root) and place it at the end of the array, then heapify the remaining elements ($O(n \log n)$). Heap sort is in-place, not stable, and guarantees $O(n \log n)$ time in all cases (best, average, worst), unlike Quick Sort, which can degrade to $O(n^{2})$.

For more info, see: [Sorting Algorithm Summary#Heap Sort](ALGO/sort.md)

#### Describe the bubble sort algorithm.

Bubble sort repeatedly steps through a list, compares adjacent elements, and swaps them if they're in the wrong order. Each pass through the list 'bubbles' the largest unsorted element to its correct position at the end.

For more info, see: [Sorting Algorithm Summary#Bubble Sort](ALGO/sort.md)

### Encryption

#### How do the encryption algorithms work?

Encryption algorithms transform plaintext into ciphertext using mathematical operations and a secret key. They work in two main categories: Symmetric encryption (AES, ChaCha20) uses the same key for encryption and decryption, relying on substitution, permutation, and key expansion. Asymmetric encryption (RSA, ECC) uses a key pair: public for encryption, private for decryption, relying on mathematical problems like prime factorization or discrete logarithms. Hashing (SHA-256) is one-way encryption for integrity verification.

---



## OS

### Base

#### Explain the main purpose of an operating system?

The operating system serves two main purposes: First, as a resource manager that allocates CPU, memory, I/O devices, and storage among competing programs efficiently and fairly. Second, as a virtual machine that provides a clean, abstract interface to hardware, hiding complexity and providing services like file systems, networking, and process management. In essence, the OS is an intermediary between user applications and computer hardware.

#### What do you mean by RTOS?

RTOS (Real-Time Operating System) is an operating system designed to process data and respond to events within strict, predictable time constraints (deadlines). Unlike general-purpose OSes that optimize for average throughput, RTOS prioritizes deterministic behavior and worst-case execution time. RTOS is used in systems where timing is critical, such as medical devices, automotive airbags, industrial robots, and avionics.

For more info, see: [OS Summary#Real-Time Operating System](OS/summary.md)

#### What is the main objective of multiprogramming?

The main objective of multiprogramming is to maximize CPU utilization by keeping the CPU busy at all times. It achieves this by having multiple programs loaded in memory simultaneously, so when one program waits for I/O (slow operation), the CPU can switch to another program. Without multiprogramming, the CPU sits idle during I/O, wasting expensive computing resources.

For more info, see: [Multiprocessor Systems#Multi Programming](OS/multi_processor.md)

#### What is time sharing, and how does it help users?

Time-sharing is a technique that allows multiple users to interact with a computer simultaneously by rapidly switching the CPU between their tasks. Each user gets a small time slice (quantum), creating the illusion that they have dedicated access to the computer. Time-sharing provides interactive response, resource sharing, and fair CPU allocation, replacing batch processing where users had to wait hours or days for results.

For more info, see: [Multiprocessor Systems#Time-Sharing System](OS/multi_processor.md)

#### What is latency, and why does it matter in an operating system?

Latency is the time delay between initiating an operation and getting the first response. In operating systems, low latency matters for interactive responsiveness, real-time guarantees, database performance, and user experience. High latency makes systems feel sluggish, while unpredictable latency (jitter) breaks real-time applications. OS latency comes from interrupt handling, scheduling delays, I/O waits, and synchronization overhead.

#### What is the difference between an interrupt, a trap, and an exception?

An interrupt is an asynchronous event triggered by external hardware (I/O devices, timers). A trap is a synchronous, software-generated interrupt caused by intentional events like system calls or breakpoints. An exception is a synchronous event caused by error conditions during instruction execution, such as division by zero or page faults. Interrupts are asynchronous (can happen anytime), while traps and exceptions are synchronous (occur at specific instructions).

For more info, see: [I/O#Interrupt](OS/io.md)

#### What do you mean by asymmetric clustering?

Asymmetric clustering is a high-availability architecture where one node (the active primary) runs applications while other nodes (standby) remain idle, ready to take over if the primary fails. The standby nodes constantly monitor the primary's health via heartbeat signals. If the primary fails, a standby node detects the failure, acquires shared resources (disk LUNs, IP addresses), and restarts the applications. This provides failover capability but leaves standby resources idle, making it less efficient than symmetric clustering.

For more info, see: [Multiprocessor Systems#Asymmetric Multiprocessing (AMP)](OS/multi_processor.md)

#### What is SMP (Symmetric Multiprocessing)?

SMP (Symmetric Multiprocessing) is an architecture where two or more identical processors share a single main memory and are controlled by a single OS instance. All processors have equal access to memory and I/O, and the OS can run any process on any CPU. Symmetric means all CPUs are peers — no master-slave relationship. Modern multi-core processors are SMP systems: each core is symmetric to others.

For more info, see: [Multiprocessor Systems#Symmetric Multiprocessing (SMP)](OS/multi_processor.md)

#### What is NUMA architecture, and how is it different from SMP?

NUMA (Non-Uniform Memory Access) is a multiprocessing architecture where each CPU has its own local memory (fast access) and also can access memory attached to other CPUs (slower access). This contrasts with SMP (Symmetric Multiprocessing) which is UMA (Uniform Memory Access) — all CPUs access all memory at the same speed.

For more info, see: [Multiprocessor Systems#Symmetric Multiprocessing (SMP)](OS/multi_processor.md)

#### What is spooling in OS?

Spooling (Simultaneous Peripheral Operation On-Line) is a technique that uses a buffer (usually on disk) to hold data for slow I/O devices, allowing faster programs to continue without waiting. The classic example is print spooling: programs write output to disk (fast), and a background printer daemon prints from the disk (slow). This decouples programs from slow devices, allowing both to work simultaneously.

For more info, see: [Multiprocessor Systems#Spooling](OS/storage.md)

### Kernel

#### What is a kernel?

The kernel is the core, privileged component of an operating system that manages system resources and provides a secure interface between hardware and user applications. It runs in protected kernel mode with full hardware access, handling CPU scheduling, memory management, I/O operations, and inter-process communication. The kernel acts as a bridge between user programs and hardware, ensuring security and resource sharing.

For more info, see: [OS Kernel](OS/kernel.md)

#### What are different types of Kernel?

There are basically five types of Kernels as given: Monolithic Kernel, Micro Kernel, Hybrid Kernel, Nano Kernel, Exo Kernel.

For more info, see: [OS Kernel#Kernel Types](OS/kernel.md)

#### What is difference between Kernel and OS?

The kernel is the core, privileged component of an operating system that manages CPU, memory, and devices. It's the lowest layer of the OS. The operating system includes the kernel plus system libraries, system utilities (shell, file managers), configuration files, and often applications (browser, text editor).

For more info, see: [OS Kernel](OS/kernel.md)

#### What are different between micro kernel and monolithic kernel?

A monolithic kernel runs all OS services in kernel space, making it fast but less stable—a driver crash can crash the whole system. A microkernel runs only essential services in kernel space, moving drivers and file systems to user space as separate processes. This makes microkernels more stable and secure, but slower due to IPC overhead.

For more info, see: [OS Kernel#Micro Kernel vs Monolithic Kernel](OS/kernel.md)

#### What is a bootstrap program in OS?

A bootstrap program (or bootloader) is the first code that runs when a computer powers on. It initializes the system hardware, locates and loads the operating system kernel into memory, and transfers control to it. The bootstrap program is stored in ROM/EPROM (firmware) because RAM is empty at startup. Modern systems use a two-stage boot process: the primary bootloader in firmware loads a secondary bootloader (like GRUB) which then loads the OS.

For more info, see: [OS Kernel#Boot Manager](OS/kernel.md)

#### What is a system call, and why is it needed?

A system call is a controlled, kernel-mode entry point that allows user programs to request services from the operating system, such as file I/O, process creation, or network communication. System calls are needed because user programs run in restricted user mode and cannot directly access hardware or kernel memory. They provide a secure, controlled interface between applications and the OS, ensuring protection, stability, and abstraction.

For more info, see: [OS Kernel#System Call](OS/kernel.md)

#### What is the difference between a system call and a library call?

A system call is a request from a user program to the kernel for a service (file I/O, process control, networking), requiring a mode switch from user to kernel mode. A library call is a function call within a library (like printf, strcpy, malloc) that executes entirely in user mode. System calls are more expensive (mode switch overhead) but provide access to OS resources. Many library calls use system calls internally—for example, printf eventually calls write().

For more info, see: [OS Kernel#System Call](OS/kernel.md)

#### What is the difference between user mode and kernel mode?

User mode and kernel mode are privilege levels enforced by the CPU. User mode has restricted access to hardware and memory, while kernel mode has full, unrestricted access. User programs run in user mode; the OS kernel runs in kernel mode. Switching from user mode to kernel mode requires a system call, interrupt, or exception. This separation prevents user programs from crashing the system or accessing protected resources.

For more info, see: [OS Kernel#Kernel Mode vs User Mode](OS/kernel.md)

### Process, Thread, and Coroutine

#### What is a process and a process table?

A process is an independent unit for resource allocation and scheduling in the system. Each process has its own independent memory space, and different processes communicate via inter-process communication. Processes are relatively heavy, context switching overhead is large, but they are more stable than threads.

For more info, see: [Process](OS/process.md)

#### What are the different states of the process?

A process moves through five primary states: New (being created), Ready (waiting for CPU), Running (executing on CPU), Waiting/Blocked (waiting for I/O or event), and Terminated (finished execution). The OS scheduler moves processes between these states based on events like timer interrupts, I/O completion, and resource availability.

For more info, see: [Process#States](OS/process.md)

#### What are various sections of the process?

A process is divided into several memory sections: Text (code) — contains executable instructions, read-only; Data — initialized global and static variables; BSS — uninitialized global and static variables (zero-initialized); Heap — dynamically allocated memory (grows upward); Stack — local variables, function parameters, return addresses (grows downward). Additionally, there may be memory-mapped regions for shared libraries.

For more info, see: [Process#Process Structure](OS/process.md)

#### What is a Thread? 

A thread is the smallest unit of execution within a process. It represents a single sequence of instructions that can run independently. Multiple threads within the same process share the process's memory space, file descriptors, and other resources, but each has its own program counter, stack, and registers. This makes threads lightweight compared to processes — faster to create and switch between.

For more info, see: [Thread](OS/thread.md)

#### What are the benefits of multithreaded programming? 

Multithreaded programming improves performance through parallelism, resource sharing, and responsiveness. Benefits include: utilizing multiple CPU cores, keeping applications responsive during long operations, sharing memory efficiently (faster than inter-process communication), and reducing overhead compared to multiple processes.

For more info, see: [Thread](OS/thread.md)

#### Explain the difference between a process and a thread in operating systems.

A process is an independent, executing program with its own dedicated memory space, while a thread is a smaller, lightweight unit of execution within a process that shares the parent process's memory and resources.

For more info, see: [Summary#Process vs Thread vs Coroutine](OS/summary.md)

#### Explain what a deadlock is and describe two conditions that must hold for a deadlock to occur.

A deadlock is a computing state where two or more processes are permanently blocked because each holds a resource the other needs, resulting in an indefinite wait. It requires four conditions: Mutual Exclusion, Hold and Wait, No Preemption, and Circular Wait.

For more info, see: [Synchronization#Deadlock](OS/sync.md)

#### How does the OS handle deadlock detection vs deadlock prevention?

Deadlock prevention ensures that at least one of the four necessary conditions (mutual exclusion, hold-and-wait, no preemption, circular wait) never occurs, making deadlocks impossible. Deadlock detection allows deadlocks to occur, but periodically checks for them and then recovers by aborting processes or preempting resources. Prevention is safer but can reduce resource utilization; detection allows more concurrency but requires recovery overhead.

For more info, see: [Synchronization#Deadlock](OS/sync.md)

#### What is a Scheduling Algorithm?

A scheduling algorithm is the method an operating system uses to select which process or thread runs next on the CPU. It balances competing goals like fairness, response time, throughput, and resource utilization.

For more info, see: [Process#Process Scheduling](OS/process.md)

#### What are the different scheduling algorithms?

CPU scheduling algorithms determine which process runs next on the CPU. The main algorithms are: FCFS (First Come First Serve) — simple but suffers from convoy effect; SJF (Shortest Job First) — optimal for average wait time but needs job length prediction; Round Robin — fair with time slices; Priority Scheduling — supports importance but can starve low-priority processes; and Multilevel Queue — separates processes into priority groups. Modern systems use multilevel feedback queues that adapt to process behavior.

For more info, see: [Process#Comparison of CPU Scheduling Algorithms](OS/process.md)

#### What is preemptive vs non-preemptive scheduling?

In preemptive scheduling, the OS can forcibly take the CPU away from a running process at any time (typically via timer interrupts). In non-preemptive scheduling, a process keeps the CPU until it voluntarily yields (by waiting for I/O, calling sleep, or exiting). Preemptive scheduling provides better responsiveness and fairness but adds overhead; non-preemptive scheduling is simpler but can freeze the system if a process doesn't yield.

For more info, see: [Process#Process Scheduling](OS/process.md)

#### Briefly explain FCFS?

FCFS (First Come First Serve) is the simplest CPU scheduling algorithm, where processes are executed in the exact order they arrive. It's implemented using a FIFO queue. The first process to request the CPU gets it first and runs to completion without preemption. FCFS is non-preemptive, easy to understand, but suffers from the convoy effect where short jobs get stuck behind long ones, leading to poor average waiting time.

For more info, see: [Process#First Come First Serve CPU Scheduling(FCFS)](OS/process.md)

#### What is the RR scheduling algorithm?

Round Robin (RR) is a preemptive CPU scheduling algorithm where each process gets a fixed time slice (quantum) to execute. Processes are arranged in a circular ready queue. When a process's quantum expires, it's preempted and moved to the end of the queue, and the next process gets the CPU. This ensures fair CPU distribution and excellent response time for interactive users. The performance heavily depends on choosing the right quantum size.

For more info, see: [Process#Round Robin Scheduling(RR)](OS/process.md)

#### Describe the objective of multi-programming?

The primary objective of multi-programming is to maximize CPU utilization and system throughput by keeping the CPU busy at all times. It achieves this by having multiple programs loaded in memory simultaneously, so when one program waits for I/O, the CPU can switch to another program. This prevents the CPU from sitting idle while waiting for slow I/O operations.

#### What is process context switching?

Context switching is the process of saving the state of a currently executing process or thread and restoring the state of another, allowing the CPU to switch between multiple tasks. The saved state includes the program counter, CPU registers, stack pointer, and memory management information. Process context switching enables multitasking by giving each process a slice of CPU time, but it has overhead and impacts performance.

For more info, see: [Process#Conext Switch](OS/process.md)

#### What is the difference between a process context switch and a thread context switch?

A process context switch switches the entire address space, including page tables and memory mappings, while a thread context switch switches only CPU registers and stack within the same address space. Process switches require flushing the TLB (Translation Lookaside Buffer) and changing page tables, making them more expensive than thread switches. Thread switches are lightweight because threads share the same memory space, so no TLB flush is needed.

For more info, see: [OS Summary#Thread Context Switch vs Process Context Switch](OS/summary.md), [Process#Conext Switch](OS/process.md), [Thread#Conext Switch](OS/thread.md)

#### What is IPC? What are the different IPC mechanisms?

IPC (Inter-Process Communication) refers to the mechanisms that allow processes to exchange data and synchronize their actions. The main IPC mechanisms include: Pipes (anonymous and named) for unidirectional data flow, Message Queues for structured messages, Shared Memory for fast data sharing, Semaphores for synchronization, Signals for asynchronous notifications, and Sockets for network communication. Each mechanism offers different trade-offs between speed, complexity, and use cases.

For more info, see: [Process#Inter Process Communication(IPC)](OS/process.md)

#### What is a Pipe and when it is used?

A pipe is a unidirectional communication channel that allows data to flow from one process to another, typically connecting the standard output of one process to the standard input of another. Pipes are used for inter-process communication (IPC) between related processes, especially parent-child processes. In the shell, the pipe symbol (|) chains commands together. Anonymous pipes exist only while processes run, while named pipes (FIFOs) persist in the filesystem for unrelated processes to communicate.

For more info, see: [Process#Pipe Communication](OS/process.md)

#### Explain zombie process?

A zombie process is a process that has terminated but still has an entry in the process table because its parent hasn't read its exit status. Zombies consume no CPU or memory (except the process table entry), but they cannot be killed because they're already dead. They remain until the parent calls `wait()` to reap them. If the parent dies first, the zombie is adopted by `init` (PID 1), which automatically reaps it.

For more info, see: [Process#Zombie Process](OS/process.md)

#### What do you mean by cascading termination?

Cascading termination occurs when the operating system automatically terminates all child processes when their parent process terminates. This prevents orphaned processes and ensures proper resource cleanup. However, children can continue running if the parent allows it (detached processes) or if 'init' (PID 1) adopts them. Cascading termination is the default behavior in most OSes for all child processes unless the parent explicitly prevents it.

For more info, see: [Process#Process Delete](OS/process.md)

#### What is priority inversion, and how can it be solved?

Priority inversion occurs when a low-priority task holds a lock needed by a high-priority task, and a medium-priority task preempts the low-priority task. The high-priority task ends up waiting for the low-priority task, which can't run because the medium-priority task is running. This violates priority ordering. The solution is priority inheritance, where the low-priority task temporarily inherits the high priority of the waiting task, preventing medium-priority tasks from preempting it.

For more info, see: [Synchronization#Priority Inversion](OS/sync.md)

#### What is starvation and aging in OS?

Starvation occurs when a low-priority process is indefinitely denied access to a required resource (like CPU time or a lock) because higher-priority processes keep using it. Aging is the solution: gradually increasing the priority of waiting processes over time, ensuring they eventually get the resource. Without aging, starvation can cause indefinite postponement; with aging, even the lowest priority process will eventually get CPU time.

For more info, see: [Synchronization#Starvation](OS/sync.md)

#### What happens inside the OS when a process crashes unexpectedly?

When a process crashes, the CPU traps to kernel mode via an exception (page fault, division by zero, illegal instruction). The OS identifies the faulting process, saves its crash state (core dump optional), releases all resources (memory, file descriptors, locks), removes the process from the scheduler, and notifies the parent process via SIGCHLD. Other processes continue running unaffected. Critical system processes may trigger a kernel panic if they crash.

For more info, see: [Process](OS/process.md)

#### How does an operating system ensure memory protection between processes?

Operating systems ensure memory protection through hardware support from the Memory Management Unit (MMU). Each process has its own virtual address space with a page table that maps virtual addresses to physical frames. Processes cannot access addresses outside their allocated pages. Page table entries include protection bits (read, write, execute) that the CPU checks on every memory access. The OS also uses privilege levels (user vs kernel mode) to prevent user processes from accessing kernel memory.

For more info, see: [Process#MMU](OS/mem_mgr.md)

#### What is Multi-Level Feedback Queue (MLFQ) scheduling?

MLFQ (Multi-Level Feedback Queue) is a scheduling algorithm that uses multiple priority queues and learns from process behavior. Interactive/I/O-bound processes get high priority (quick response), while CPU-bound processes get low priority (longer quanta). Processes automatically 'feedback' between queues: if they use their full time slice, they move down; if they yield (I/O), they stay or move up. Aging prevents starvation. This adaptive approach balances responsiveness for interactive tasks with throughput for CPU-intensive tasks.

For more info, see: [Process#Multilevel Feedback Queue Scheduling(MLFQ))](OS/process.md)

### Sync

#### What is Reentrancy?

Reentrancy is a property of a function or code block that allows multiple invocations to run concurrently without interfering with each other. A reentrant function can be called before its previous invocation has completed, even by different threads or interrupt handlers, and still produce correct results. Reentrant functions avoid using static/global data, do not call non-reentrant functions, and properly manage their own state—typically by using local variables or protecting shared data with synchronization.

For more info, see: [Synchronization#Reentrant Function](OS/sync.md)

#### What do you mean by process synchronization?

Process synchronization coordinates the execution of concurrent processes to ensure they access shared resources in a controlled manner, preventing race conditions, data inconsistency, and deadlocks. It ensures that when multiple processes access shared data, only one process at a time can modify the data (mutual exclusion), and processes can coordinate their execution order when needed. Common synchronization mechanisms include mutexes, semaphores, monitors, and critical sections.

For more info, see: [Synchronization#Process Synchronization](OS/sync.md)

#### What do you mean by Semaphore in OS?

A semaphore is a synchronization primitive that uses an integer counter to control access to shared resources. It supports two atomic operations: wait() and signal(). Semaphores can be binary (0/1) for mutual exclusion or counting (0..N) for managing multiple identical resources.

For more info, see: [Synchronization#Semaphore](OS/sync.md)

#### What are the different kinds of operations that are possible on semaphore?

Semaphore supports two atomic operations: wait() (also called P or down) and signal() (also called V or up). wait() decrements the semaphore value and blocks if the value becomes negative. signal() increments the semaphore value and wakes up any waiting process. Additionally, semaphores can be initialized with a value, but there are no other operations. These two operations must be atomic to prevent race conditions.

For more info, see: [Synchronization#Semaphore](OS/sync.md)

#### What is the difference between mutex and lock-free containers?

A mutex-based container uses locks to protect shared data, causing threads to block (sleep) when waiting for access. Lock-free containers use atomic operations (CAS - Compare-And-Swap) to update data without blocking, guaranteeing that at least one thread makes progress. Lock-free containers avoid deadlocks, priority inversion, and have better scalability under high contention, but are much harder to implement correctly.

For more info, see: [Synchronization#Thread Synchronization](OS/sync.md)

#### What is the difference between a mutex and a semaphore?

A mutex is a binary lock with ownership — only the thread that locked it can unlock it. A semaphore is a counter that can be incremented (signal) and decremented (wait) by any thread. Mutexes are for mutual exclusion (protecting critical sections), while semaphores are for signaling and resource counting. Counting semaphores can allow multiple threads to access a resource pool, whereas mutexes allow only one.

For more info, see: [Synchronization#Mutex vs Semaphore](OS/sync.md)

#### What is the difference between multitasking and multiprocessing OS?

Multitasking OS runs multiple tasks on a single CPU by rapidly switching between them (concurrency). Multiprocessing OS uses multiple physical CPUs/cores to run tasks simultaneously (parallelism). Multitasking gives the illusion of parallelism through time-sharing, while multiprocessing provides true simultaneous execution. Modern OSes combine both: they use multiprocessing on multiple cores and multitasking within each core.

For more info, see: [OS Summary#Multitasking vs Multiprocessing](OS/summary.md)

#### What is a monitor in operating systems?

A monitor is a high-level synchronization construct that encapsulates shared data, operations on that data, and mutual exclusion. Only one process can execute inside a monitor at a time, automatically providing mutual exclusion. Monitors also provide condition variables that allow processes to wait for specific conditions (like 'buffer not empty') and signal other processes when conditions change. Monitors are implemented in programming languages (Java's `synchronized`, C#'s `lock`) rather than the OS kernel.

For more info, see: [Synchronization#Monitor](OS/sync.md)

### Memory Management

#### What is virtual memory?

Virtual memory is a memory management technique that gives each process the illusion of having its own large, contiguous address space, while physically the data may be scattered across RAM and disk. It allows programs to run even if their total memory requirements exceed physical RAM by swapping pages between RAM and disk (swap space). Virtual memory provides isolation between processes, simplifies memory management for programmers, and enables efficient use of limited physical memory through demand paging.

For more info, see: [Memory Management#Virtual memory](OS/mem_mgr.md)

#### Explain how virtual memory works and why it's essential for modern operating systems.

Virtual memory gives each process the illusion of a large, private, contiguous address space. Provide an efficient use of physical memory by keeping only the active page in RAM; Simpler programming model; Isolate processes from each other and from the kernel.

For more info, see: [Memory Management#Virtual memory](OS/mem_mgr.md)

#### What is Thrashing? 

Thrashing occurs when a system spends more time swapping pages between RAM and disk than executing actual instructions. It happens when the working set of all active processes exceeds available physical memory, causing constant page faults. The CPU becomes highly utilized (but on swapping, not computation), throughput drops dramatically, and the system becomes unresponsive.

For more info, see: [Memory Management#Page Replacement & Thrashing](OS/mem_mgr.md)

#### Explain how page faults occur and what the OS does when a page fault happens.

A page fault occurs when a program tries to access data on a page not currently mapped to physical RAM. The OS handles this by pausing the process, fetching the required page from disk into a free RAM frame, updating the page table, and resuming the process.

For more info, see: [Memory Management#Virtual memory](OS/mem_mgr.md)

#### How the OS manages the page replacement algorithm? using LRU as an example.

The OS manges the page replacement strategies include: LRU, FIFO, Working-set algorithms. For example, When physical memory is full and a new page needs to be loaded, the LRU algorithm selects the page that has not been used for the longest period of time and replaces it.

For more info, see: [Memory Management#Page replacement policies](OS/mem_mgr.md)

#### What is demand paging and how it works?

Demand paging is a virtual memory technique where pages are loaded into physical memory only when they are actually accessed (on demand), not when the process starts. When a program accesses an address not in physical memory, a page fault occurs, the OS loads the required page from disk, updates the page table, and restarts the instruction. This allows processes to run with less physical memory than their total size, reduces I/O, and enables faster process startup.

For more info, see: [Memory Management#Demand paging and page faults](OS/mem_mgr.md)

#### What is different between main memory and secondary memory.

Main memory in a computer is RAM (Random Access Memory). It is also known as primary memory or read-write memory or internal memory. The programs and data that the CPU requires during the execution of a program are stored in this memory. Secondary memory in a computer are storage devices that can store data and programs. It is also known as external memory or additional memory or backup memory or auxiliary memory. Such storage devices are capable of storing high-volume data. Storage devices can be hard drives, USB flash drives, CDs, etc. 

For more info, see: [Memory Management#Main Memory vs Secondary Memory](OS/mem_mgr.md)

#### What is the difference between paging and segmentation?

Paging divides memory into fixed-size blocks called frames (physical) and pages (virtual), using a page table for mapping. Segmentation divides memory into variable-sized logical segments (code, data, stack) based on program structure, using a segment table. Paging is invisible to the programmer and eliminates external fragmentation, while segmentation is visible, allows sharing and protection per segment, but suffers from external fragmentation.

For more info, see: [Memory Management#Paging vs Segmentation](OS/mem_mgr.md)

#### What do you mean by overlays in OS?

Overlays are a memory management technique that allows a program larger than physical memory to run by keeping only the currently needed code and data in memory, while the rest remains on disk. The program is divided into logical segments called overlays. When a segment not in memory is needed, it 'overlays' (replaces) an existing segment in memory.

For more info, see: [Memory Management#Overlays](OS/mem_mgr.md)

#### What is thrashing in OS?

Thrashing occurs when a system spends more time swapping pages between RAM and disk than executing actual instructions. It happens when the working set of all active processes exceeds available physical memory, causing constant page faults. CPU utilization drops dramatically (often below 20%) while disk I/O maxes out. The system becomes unresponsive. Solutions include reducing the number of running processes, adding more RAM, or adjusting the swappiness parameter.

For more info, see: [Memory Management#Page Replacement & Thrashing](OS/mem_mgr.md)

#### What is the difference between page size and frame size?

Page size and frame size are always equal. A page is the fixed-size block of virtual memory (the logical view), while a frame is the same-size block of physical memory (the hardware view). The OS maps pages to frames of identical size. Having equal sizes allows the MMU to simply replace the page number with a frame number while keeping the offset unchanged.

For more info, see: [Memory Management#MMU](OS/mem_mgr.md)

#### What is copy-on-write, and where is it used?

Copy-on-write (COW) is a memory management technique where multiple processes initially share the same memory pages, and a copy is created only when one process tries to modify the data. This approach improves performance and reduces memory usage because unnecessary copying is avoided.

For more info, see: [Memory Management#Copy-on-write and shared mappings](OS/mem_mgr.md)

#### What is internal vs external fragmentation?

Internal fragmentation is wasted space inside an allocated memory block because the allocated block is larger than the requested memory. External fragmentation is wasted space between allocated blocks that is too small to satisfy any allocation request. Paging causes internal fragmentation (unused space at the end of the last page), while segmentation causes external fragmentation (small unusable holes between segments).

For more info, see: [Memory Management#Fragmentation](OS/mem_mgr.md)

#### What do you mean by Belady’s Anomaly?

Belady's Anomaly is a counterintuitive phenomenon where increasing the number of page frames in memory can actually cause MORE page faults, not fewer. This anomaly occurs with FIFO (First-In-First-Out) page replacement algorithms, but not with optimal or LRU algorithms. It demonstrates that for some algorithms, more memory doesn't always mean better performance.

For more info, see: [Memory Management#Belady's Anomaly](OS/mem_mgr.md)

#### How does a Translation Lookaside Buffer (TLB) improve performance?

The TLB (Translation Lookaside Buffer) is a hardware cache that stores recent virtual-to-physical address mappings, avoiding the need for expensive page table walks. Without a TLB, every memory access would require multiple memory accesses to traverse the page table. With a TLB hit, translation takes 1 cycle. With a TLB miss, the CPU must perform a page table walk. This speedup makes virtual memory feasible.

For more info, see: [Memory Management#Translation Lookaside Buffer (TLB)](OS/mem_mgr.md)

### Storage

#### Why is exclusive ownership important when managing a file handle?

Exclusive ownership in file handle managment ensures data integrity, prevents resource leaks, and guarantees that only one process can safely modify a file, mitigating risks of corruption.

For more info, see: [Storage](OS/storage.md)

#### Enumerate the different RAID levels?

RAID (Redundant Array of Independent Disks) combines multiple physical disks into logical units for redundancy and performance. The main RAID levels are: RAID 0 (striping, no redundancy, max performance), RAID 1 (mirroring, 100% redundancy, good read performance), RAID 5 (striping with distributed parity, good balance), RAID 6 (dual parity, tolerates two disk failures), and RAID 10 (mirrored stripes, best performance and redundancy). Each level offers different trade-offs between cost, performance, and fault tolerance.

For more info, see: [Storage#RAID](OS/storage.md)

#### What is the difference between a hard link and a soft link?

A hard link is a directory entry that points directly to the inode, effectively creating another name for the same file. All hard links are equal; deleting one doesn't affect others. A soft/symbolic link is a special file that stores the pathname of another file. Deleting the target file breaks the soft link, but deleting the soft link itself doesn't affect the target. Hard links cannot span filesystems or link to directories, while soft links can.

For more info, see: [File System#Hard Link vs Soft Link](OS/file_system.md)

#### What is an inode in a file system?

An inode (index node) is a data structure that stores all metadata about a file except its name and content. This includes file size, permissions, timestamps, ownership, and pointers to the disk blocks where the file's data is stored. Each file and directory has a unique inode number. The filename is stored in directory entries that map filenames to inode numbers. Inodes are stored in a special area of the disk called the inode table.

For more info, see: [File System#](OS/file_system.md)

---



## System Design

### Base

#### What are the key principles you follow for maintainability and code quality in C++?

I use the principle of DRY in keeping projects maintainable and high code quality. DRY(Don't Repeat Yourself) is a software development principle that says the same logic or knowledge should not be written multiple times in a system.

For more info, see: [System Design Summary](SYSTEM_DESIGN/summary.md)

#### Are there any specific areas you find challenging in maintaining code quality?

The most challenging areas in maintaining code quality are managing technical debt in legacy code without tests, resisting over-engineering while keeping code extensible, balancing performance with readability in hot paths, maintaining discipline when deadlines are tight, and evolving interfaces without breaking dependent code. Each challenge requires judgment and trade-offs rather than absolute rules.

#### What do you understand by latency, throughput, and availability of a system?

Latency is the time it takes to complete a single operation. Throughput is the number of operations a system can handle per unit of time. Availability is the percentage of time a system is operational and accessible. They're interconnected trade-offs: optimizing for one often impacts the others. A system can have low latency but low throughput, or high throughput with higher latency.

For more info, see: [System Metrics#Availability](SYSTEM_DESIGN/system_metrics.md)

#### What is a proxy server?

A proxy server is an intermediary that sits between clients and servers, forwarding requests and responses. It can modify traffic, cache content, filter requests, anonymize clients, or load balance servers.

For more info, see: [Proxy#Proxy Server](SYSTEM_DESIGN/proxy.md)

#### What is the difference between Reverse Proxy and Forward Proxy?

A forward proxy sits in front of clients, intercepting outbound requests to external servers on behalf of internal users. It hides client identities, bypasses restrictions, and caches content. A reverse proxy sits in front of servers, intercepting inbound requests from external clients to internal servers. Forward proxies protect clients; reverse proxies protect servers.

For more info, see: [Proxy#Proxy Vs Reverse Proxy](SYSTEM_DESIGN/proxy.md)

#### What is rate limiter? How does it work?

A Rate Limiter is a tool used to control the rate of traffic sents by a client or received by a server. It acts as a "gatekeeper" that defines how many requests a user can make within a specific timeframe. Rate limiters track requests using specific logic to decide whether to allow, drop, or delay a request.

For more info, see: [Rate Limiting](SYSTEM_DESIGN/rate_limiting.md)

#### How does Apache Kafka works? why it so fast?

Apache Kafka is a distributed event streaming platform designed to handle trillions of events a day. At its core, it is a distributed commit log--an immutable, append-only sequence of records spread across multiple servers.

For more info, see: [Message Queues#Why is Kafka Fast](SYSTEM_DESIGN/mq.md)

#### Difference between Kafka, ActiveMQ, and RabbitMQ?

Kafka is a distributed streaming platform, RabbitMQ is a versatile message broker, and ActiveMQ is a traditional enterprise-grade broker.

For more info, see: [Message Queues#RabbitMQ vs Apache Kafka vs ActiveMQ](SYSTEM_DESIGN/mq.md)

### Consistency

#### What are the various Consistency patterns available in system design?

Consistency from the CAP theorem states that every read request should get the most recently written data. When there are multiple data copies available, there arises a problem of synchronizing them so that the clients get fresh data consistently. There are the consistency patterns available: Weak consistency, Eventual Consistency, and Strong consistency.

For more info, see: [System Metrics#Consistency](SYSTEM_DESIGN/system_metrics.md)

#### What's the differnce between strong and eventual consistency?

Strong consistency guarantees that after a write, all subsequent reads return that value. Eventual consistency guarantees that if no new writes happen, all replicas will eventually converge, but reads may see stale data temporarily. Strong consistency has higher latency and lower availability; eventual consistency is faster and more available.

For more info, see: [System Metrics#Consistency](SYSTEM_DESIGN/system_metrics.md)

#### When would you choose eventual over strong consistency?

Choose eventual consistency when: 1. Stale data is acceptable, 2. High write throughput is critical, 3. System must remain available during network partitions, 4. Cross-region replication is needed. Choose strong consistency for financial transactions, inventory, locks, and system where inconsistency has high cost.

For more info, see: [System Metrics#Consistency](SYSTEM_DESIGN/system_metrics.md)

#### How does causal consistency differ from eventual?

Causal consistency preserves cause-and-effect relationships. If operation B depends on operation A, any node that sees B must also see A. Unrelated operations can be seen in any order. Eventual consistency makes no such guarantees--a user could see a reply without seeing the original comment.

For more info, see: [System Metrics#Consistency](SYSTEM_DESIGN/system_metrics.md)

#### What are CRDTs and how do they help with consistency?

CRDTs (Conflict-free Replicated Data Types) are data structures that guarantee eventual consistency without complex coordination. They have merge functions that are commutative, associative, and idempotent, allowing concurrent updates to be merged deterministically.

For more info, see: [Consistency#CRDTs (Conflict-free Replicated Data Types)](SYSTEM_DESIGN/system_metrics.md)

#### How do you choose consistency levels in a distributed database?

Based on your application's requirements: For critical writes (e.g., payment), use strong consistency. For non-critical writes, use ONe. For reads, use ONE for non-critical reads, QUORUM for reads that affect user experience. Monitor performance and consistency violations in productions.

For more info, see: [Consistency](SYSTEM_DESIGN/system_metrics.md)

### Scalability

#### How is performance and scalability related to each other?

Performance and scalability are related but distinct concepts. Performance is about response time for a single user or operation. Scalability is about the system's ability to handle increased load by adding resources. A system can have great performance for one user but fail to scale to many users. Conversely, a system can scale well but have poor baseline performance. The relationship is that poor performance limits scalability, and good scalability preserves performance under load.

For more info, see: [System Metrics#Scalability](SYSTEM_DESIGN/system_metrics.md)

#### Can a system have good scalability but poor performance?

Yes. For example, a system that uses a heavy framework with 500ms baseline latency, but is stateless and horizontally scalable. Adding servers increases throughput linearly, but every individual request is still slow. Users will be unhappy despite good scalability.

For more info, see: [System Metrics#Scalability](SYSTEM_DESIGN/system_metrics.md)

#### How do you identify if a problem is performance or scalability related?

Test at different loads. If it's slow with one user, it's a performance problem. If it's fast with one user but slows down with many, it's a scalability problem.

For more info, see: [System Metrics#Scalability](SYSTEM_DESIGN/system_metrics.md)

#### What's the relationship between Amdahl's law and scalability?

Amdahl's law states that the serial portion of your application limits maximum speedup. If 10% of the work is serial, you can't get more than 10x speedup regardless of how many servers you add. This is the fundamental limit of scalability--improving performance directly improves scalability.

For more info, see: [System Metrics#Scalability#Amdahl’s law](SYSTEM_DESIGN/system_metrics.md)

#### What is the difference between vertical and horizontal partitioning?

Horizontal partitioning splits a table by its rows(reducing table size), while Vertical partitioning splits it by its columns(reducing table width).

For more info, see: [Database Designl#Horizontal Partitioning vs Vertical Partitioning](SYSTEM_DESIGN/db.md)

#### How does horizontal scaling relate to performance?

Horizontal scaling improves throughput but doesn't necessarily improve latency. In fact, adding servers can increase latency slightly due to netowrk hops. The goal is to keep latency constant while increasing throughput--that's good scalability.

For more info, see: [Database Designl#Horizontal Partitioning vs Vertical Partitioning](SYSTEM_DESIGN/db.md)

### Load Balancing

#### What do you understand by load balancing? Why is it important in system design?

Load balancing is the practice of distributing incoming network traffic across multiple backend servers to ensure no single server bears too much load. It's crucial in system design because it prevents any server from becoming a bottleneck, and provides high availability by rerouting traffic when servers fail, enables horizontal scaling, and improves user experience by reducing response times. Without load balancing, a single server failure or traffic spike can bring down an entire system.

For more info, see: [Load Balancing](SYSTEM_DESIGN/load_balance.md)

#### What happens if your load balancer becomes the bottleneck?

If a single load balancer becomes the bottleneck, I'd first switch to a multi-tiered or distributed load-balancing architecture. I'd also implement DNS round-robin to distribute traffic before reaching the bottleneck, enable direct server return (DSR) for heavy outbound traffic, and use anycast IP to route clients to the nearest balancer. Failing that, I'd move logic to the client side (smart clients) or use a service mesh with client-side load awareness.

For more info, see: [Load Balancing](SYSTEM_DESIGN/load_balance.md)

#### Can you use multiple load balancing algorithms together?

Yes! Common pattern: Use DNS GSLB for geographic distribution (round robin), then Layer 7 with proper timeout configuration. Ensure sticky sessions (by IP hash or cookie) so all messages from a client go to the same server. Most modern L7 LBs (Nginx, HAProxy) support WebSocket upgrades.

For more info, see: [Load Balancing#Algorithms](SYSTEM_DESIGN/load_balance.md)

#### How does load balancing work with WebSockets?

WebSockets are long-lived persistent connections. Use Layer 4 (TCP) load balancing or Layer 7 with proper timeout configuration. Ensure sticky sessions (by IP hash or cookie) so all messages from a client go to the same server. Most modern L7 LBs support WebSocket upgrades.

For more info, see: [Load Balancing#Stateless And Stateful Load Balancing](SYSTEM_DESIGN/load_balance.md)

#### What's the difference between hardware and software load balancers?

Hardware LBs are appliances with specialized ASICs--extremely fast but expensive and less flexible. Software LBs run on commodity hardware-slower but cheaper, more configurable, and cloud-friendly. Most modern systems use software LBs in the cloud.

For more info, see: [Load Balancing](SYSTEM_DESIGN/load_balance.md)

#### What is the difference between API Gateway and Load Balancer?

An API Gateway is an intelligent entry point that manages, secures, and routes API requests to specific microservices, while a Load Balancer focuses on distributing traffic across multiple servers to ensure high availability and prevent overload.

For more info, see: [Load Balancing#API Gateway vs Load Balancer](SYSTEM_DESIGN/load_balance.md)

### CDN

#### What do you understand by CDN(Content Delivery Network)?

A Content Delivery Network (CDN) is a geographically distributed network of proxy servers that cache content closer to end users to reduce latency, improve availability, and lower bandwidth costs. Instead of all users fetching content from a single origin server, a CDN serves static assets from edge servers located near each user, dramatically reducing load times and origin server load.

For more info, see: [CDN](SYSTEM_DESIGN/cdn.md)

#### What happens when a user requests a file not in the CDN cache?

The CDN edge server forwards the request to the origin server (or upstream cache), fetches the file, stores it in its local cache according to cache headers, then serves it to the user. Subsequent requests for the same file will be served from cache. This first request is called a 'cache miss' or 'cold start' and will have higher latency.

For more info, see: [CDN#Workflow](SYSTEM_DESIGN/cdn.md)

#### How do you invalidate content on a CDN?

There are several methods: 1. Set short TTLs in Cache-Control headers, 2. use versioned URLs, 3. Explicit purge API calls (by URL or wildcard), 4. Use tag-based purging, 5. Wait for natural TTL expiration. For production, versioned URLs are best--they avoid invalidation entirely.

For more info, see: [CDN#Invalidate Content](SYSTEM_DESIGN/cdn.md)

#### Can a CDN serve dynamic content?

Yes, but with caveats. Edge computing platforms can generate dynamic content at the edge. You can also cache dynamic content with short TTLs for semi-dynamic data like leaderborads or news headlines. True real-time data (e.g., stock prices, chat) isn't suitable for CDN caching.

For more info, see: [CDN](SYSTEM_DESIGN/cdn.md)

#### How does a CDN handle SSL/TLS?

CDNs terminate SSL/TLS at the edge. The user connects to the CDN edge via HTTPS, and the CDN typically connects to the origin via HTTPS as well. CDNs manage SSL certificates for your domains, including automatic renewal. This offloads SSL processing from your origin servers.

For more info, see: [CDN#SSL/TLS](SYSTEM_DESIGN/cdn.md)

#### What's the difference between a CDN and a reverse proxy?

A reverse proxy sits in front of one or more origin servers, typically in the same data center, for load balancing, caching, and security. A CDN is a globally distributed network of reverse proxies. All CDNs use reverse proxy technology, but not all reverse proxies are CDNs. CDNs add geopgraphic distribution, DDoS protection, and global routing.

For more info, see: [CDN](SYSTEM_DESIGN/cdn.md)

### Distributed System

#### What is CAP theorem?

The CAP theorem states that in a distributed system, you can only guarantee two of three properties simultaneously: Consistency, Availability, and Partition tolerance. Since network partitions are unavoidable in distributed systems, you must choose between Consistency and Availability when a partition occurs.

For more info, see: [CAP Theorem](DCS/cap.md), [Database Design#CAP Theorem In Database Designing](SYSTEM_DESIGN/dcs.md)

#### What do you understand by Leader Election?

Leader Election is the process by which a distributed system selects a single node to act as the primary coordinator, decision-maker, or master. This leader is responsible for making critical decisions, coordinating tasks, or managing shared rexources while other nodes (followers) wait for instructions. When the leader fails, the system automatically elects a new leader to maintain availability.

For more info, see: [Database Design#Consensus Algorithms](SYSTEM_DESIGN/dcs.md)

#### Imaging you're designing a distributed key-value store. How do you handle data replication across multiple nodes, and how do you ensure consistency in the face of network partitions?

In a distributed key-value store, the CAP theorem with C stands for consistency, A stands for Availability, P stands for Partition Tolerance, which forces you to choose two of three. Since network partitions are unavoidable, you must choose between CP (Consistency + Partition tolerance) or AP (Availability + Partition tolerance). For data replication, I'd use quorum-based replication (`W + R > N`, `W > N/2`). 

### Design Pattern

#### What are design patterns?

Design patterns are the reusable solutions that solve common problems of software development. These problems include repetitive code, redundant functions, and logic etc. These help to save considerable effort and time required for the developers while developing software. Design patterns are commonly used in object-oriented software products by incorporating best practices and promoting reusability for developing robust code.

For more info, see: [Design Pattern](SYSTEM_DESIGN/design_pattern.md)

#### What's the difference between a design pattern and a framework?

A design pattern is a reusable solution to a problem--it's an idea or template. A framework is an actual code that provides a structure for applications. Frameworks use design patterns internally. For example, Spring is a framework; Dependency Injection is a pattern that Spring implements.

For more info, see: [Design Pattern](SYSTEM_DESIGN/design_pattern.md)

#### How are design pattern different from algorithms?

Both Design Patterns and Algorithms describe typical solutions to any given problem. But the main difference is that the algorithm defines a clear set of actions for achieving a goal and a design pattern provides a high-level description of any solution. Design patterns applied to two different problems might be the same but the logic of implementation would be different and is based on the requirements.

For more info, see: [Design Pattern](SYSTEM_DESIGN/design_pattern.md)

#### What is the main advantage of using a prototype design pattern over object creation using a new keyword?

The main advantage of the Prototype pattern is that it clones existing objects rather than creating new instances from scratch, which avoids the cost of repeated initialization, complex construction logic, or expensive resource acquisition. This is particularly valuable when object creation is costly, when objects have many configuration parameters, or when you need to create many similar objects with slight variations.

For more info, see: [Design Pattern#PROTOTYPE](SYSTEM_DESIGN/design_pattern.md)

#### What is the Singleton Design Pattern?

The Singleton Pattern ensures that only one instance of a class is created throughout the program and it provides a global point of access to that instance...

For more info, see: [Design Pattern#SINGLETON](SYSTEM_DESIGN/design_pattern.md)

#### How would you implement a singleton in C++11?

In C++ 11 and later, the simplest and most robust way to implement a Singleton is using a static local variable inside a static method. This is thread-safe due to C++11's guarantee that static local variables are initialized in a thread-safe manner. I'd delete the copy constructor, assignment operator, and optionally the move operations to prevent copying.

For more info, see: [Design Pattern#SINGLETON](SYSTEM_DESIGN/design_pattern.md)

#### What would happen if we do not have a synchronized method for returning Singleton instance in a multi-threaded environment?

If we don't synchronize the Singleton instance creation method in a multi-threaded environment, we can end up with multiple instances of what should be a single-instance class--completely breaking the Singleton pattern. Worse, we might get partially constructed objects or even crashes.

For more info, see: [Design Pattern#SINGLETON](SYSTEM_DESIGN/design_pattern.md)

#### What is the Observer Design Pattern?

The Observer Pattern defines a one-to-many dependency so that when one object (subject) changes, all dependent objects(observers) are notified...

For more info, see: [Design Pattern#OBSERVER](SYSTEM_DESIGN/design_pattern.md)

#### What is Decorator Design Pattern?

The Decorator pattern is a structural design pattern that allows behavior to be added to individual objects dynamically, without affecting the behavior of other objects from the same class. It wraps an object inside another object that adds the new behavior, following the Open-Closed Principle. This is often a more flexible alternative to subclassing for extending functionality, especially when you need combinations of features.

For more info, see: [Design Pattern#DECORATOR](SYSTEM_DESIGN/design_pattern.md)

#### What is a Command Pattern?

The Command pattern encapsulates a request as an object, thereby allowing you to parameterize clients with different requests, queue or log requests, and support undoable operations. It decouples the object that invokes an operation from the one that knows how to perform it, turning method calls into first-class objects that can be stored, passed around, and executed later.

For more info, see: [Design Pattern#COMMAND](SYSTEM_DESIGN/design_pattern.md)

#### What problem does Builder Pattern try to solve?

The Builder pattern solves the problem of constructing complex objects with many optional parameters, especially when the construction process involves multiple steps or when objects need to be created in different representations. it separates the construction of a complex object from its representation, allowing the same construction process to create different variations of the object. This avoids telescoping constructors, improves code readability, and ensures object validity.

For more info, see: [Design Pattern#BUILDER](SYSTEM_DESIGN/design_pattern.md)

#### What do you understand by the Null Object pattern?

The Null Object Pattern is a design pattern that replaces null references with a special, inert object that implements the expected interface but does nothing.

For more info, see: [Design Pattern](SYSTEM_DESIGN/design_pattern.md)

#### What is the MVC design pattern?

MVC is an architectural pattern that separates an application into three interconnected components: Model, View, and Controller. This separation promotes organized code, easier maintenance, and parallel development.

For more info, see: [Design Pattern](SYSTEM_DESIGN/design_pattern.md)

#### What are the components of the Composite Entity pattern?

The Composite Entity Pattern is a structural design pattern used in enterprise applications to represent a graph of related objects as a single, coarse-grained entity. It's particularly useful for persisting complex object graphs without exposing the internal details to clients.

For more info, see: [Design Pattern](SYSTEM_DESIGN/design_pattern.md)

#### What is a Chain of Responsibility pattern? In what scenarios to apply this pattern?

The Chain of Responsibility pattern decouples the sender of a request from its receiver by giving multiple objects a chance to handle the request. The request passes along a chain of handlers until one handles it--or reaches the end of the chain.

For more info, see: [Design Pattern](SYSTEM_DESIGN/design_pattern.md)

#### What is a Bridge Design Pattern?

The Bridge pattern decouples an abstraction from its implementation so that the two can vary independently. Instead of creating a static inheritance hierarchy that combines both, you use composition to separate 'what something does' from 'how it does it'.

For more info, see: [Design Pattern#BRIDGE](SYSTEM_DESIGN/design_pattern.md)

#### What is a Proxy Design Pattern?

The Proxy pattern provides a surrogate or placeholder for another object to control access to it. The proxy acts as an intermediary, adding a layer of indirection that can handle things like lazy loading, access control, logging, or caching without modifying the original object.

For more info, see: [Design Pattern#PROXY](SYSTEM_DESIGN/design_pattern.md)

#### What is an Adapter Design Pattern?

The Adapter pattern converts the interface of a class into another interface that clients expect. It allows classes to work together that couldn't otherwise because of incompatible interfaces--like a real-world electrical plug adapter.

For more info, see: [Design Pattern#ADAPTER](SYSTEM_DESIGN/design_pattern.md)

#### What is a Factory Design Pattern?

The Factory pattern is a creational design pattern that provides an interface for creating objects without exposing the instantiation logic to the client. It delegates the responsibility of 'which class to instantiate' to a separate factory object or method.

For more info, see: [Design Pattern#FACTORY METHOD](SYSTEM_DESIGN/design_pattern.md)

### Design Principles

#### What is Inversion of Control?

Inversion of Control (IoC) is a design principle where the control flow of a program is inverted: instead of your code calling into libraries or frameworks, the framework calls your code. This shifts the responsibility of managing components, their lifecycle, and dependencies away from your application code to a container or framework. IoC enables better decoupling, testability, and flexibility, with Dependency Injection being the most common implementation.

For more info, see: [System Design Summary](SYSTEM_DESIGN/summary.md)

#### What are the SOLID principles?

SOLID is an acronym for five design principles that make software more maintainable, flexible, and understandable. They are: Single Responsibility, Open-Closed, Liskov Substitution, Interface Segregation, and Dependency Inversion. These principles guide object-oriented design to reduce coupling, increase cohesion, and manage complexity.

For more info, see: [System Design Summary#SOLID](SYSTEM_DESIGN/summary.md)

#### How are design principles different from design patterns?

Design principles are high-level, language-agnostic guidelines that inform good software design, while design patterns are concrete, reusable solutions to specific recurring problems. Principles are the 'why' and 'what' of good design--the foundational beliefs; patterns are the 'how'--proven implementation recipes that embody those principles.

For more info, see: [Design Pattern](SYSTEM_DESIGN/design_pattern.md), [System Design Summary#Design Principle](SYSTEM_DESIGN/summary.md)

#### What do you understand by the Open-Closed Principle (OCP)?

The Open-Closed Principle (OCP) states that software entities should be open for extension but closed for modification. This means you should be able to add new functionality without changing existing code. OCP is typically achieved through abstraction, polymophism, and design patterns likt Strategy, Template Method, and Observer. It's the 'O' in SOLID and is crucial for creating maintainable systems that can evolve without breaking existing features.

For more info, see: [System Design Summary](SYSTEM_DESIGN/summary.md)

### Optimize

#### Tell me about a time you had to optime C++ Code for performance; what was the bottleneck and how did you improve it?

In my last company, a teammate committed a function that I found to be qutie resource-intensive. During a code review, I noticed he had used pass by value, whereas I would have used pass by reference.

For more info, see: [C++ Best Practice](LANG/C++/best_practice.md)

#### What is sharding?

Sharding is a database partitioning technique that splits a large dataset across multiple servers horizontally, with each shard holding a subset of the data. This allows the database to scale horizontally beyond the limits of a single machine. Each shard is an independent database, and together they form a single logical database. The key challenge is choosing a shard key to distribute data evenly while supporting efficient queries.

For more info, see: [Database Design#Data Sharding And Partitioning](SYSTEM_DESIGN/db.md)

#### How is sharing different from partitioning?

Partitioning splits data within a single database server, while sharding distributes data across multiple servers. Partitioning is about organization and performance on one machine; sharding is about horizontal scalabilty across many machines. You can partition within a shard, and you can share a partitioned table--they're complementary, not mutually exclusive.

For more info, see: [Database Design#Data Sharding And Partitioning](DB/best_practice.md)

#### How do you handle a 'hot partition' where one server gets all traffic?

A hot partition happens when load distribution isn't uniform--usually due to a popular key, poor hashing, or sticky sessions. I'd first identify if it's logical or pathological. For logical hotspots, I'd use shard splitting or read replicas with write partitioning. For pathological, I'd switch to consistent hashing with virtual nodes or use two-level routing. Failing that, I'd move to client-side random partitioning or write-ahead logging with batching.

#### What is the difference between Horizontal scaling and vertical scaling?

Horizontal scaling adds more machines to your pool of resources(scaling out), while vertical scaling adds more power(CPU, RAM) to an existing machine(scaling up).

For more info, see: [System Dependability#Horizontal vs Vertical Scaling](SYSTEM_DESIGN/system_metrics.md)

#### Can you partition a sharded table?

Yes! In fact, this is common in large systems. Each shard is a separate database server, and each server can partition its data locally. For example, a social media platform might shard by `user_id` across 100 servers, then within each server partition posts by month for efficient querying and archiving.

For more info, see: [Database Design#Data Sharding And Partitioning](SYSTEM_DESIGN/db.md)

#### Is harding just partitioning across servers?

Conceptually yes, but practically no. Partitioning is transparent to the application and maintains ACID properties across partitions. Sharding introduces network latency, partial failures, cross-shard query complexity, and distributed transaction challenges. The operational reality is very different.

For more info, see: [Database Design#Data Sharding And Partitioning](SYSTEM_DESIGN/db.md)

#### When should you choose partitioning over sharding?

Choose partitioning when your data fits on a single server, but you need better query performance or easier data management. Choose sharding when you've exhausted vertical scaling and need to scale horizontally. Start with partitioning, add sharding only when necessary.

For more info, see: [Database Design#Data Sharding And Partitioning](SYSTEM_DESIGN/db.md)

#### Does sharding eliminate the need for partitioning?

No, they solve different problems. Sharding handles scale-out across servers. Partitioning handles data organization within a server. A sharded system can still benefit from partitioning within each shard for better query performance and easier data lifecyle management.

For more info, see: [Database Design#Data Sharding And Partitioning](SYSTEM_DESIGN/db.md)

### Caching

#### What is caching? what are the various cache update strategies available in caching?

Caching is the temporary storage of frequently accessed data in a high-speed storage layer to reduce latency and database load. Cache update strategies determine how the cache stays synchronized with the source of truth. The main strategies are Cache-Aside, Read-Through, Write-Behind, and Write-Around. Each makes different trade-offs between consistency, performance, and complexity.

For more info, see: [Caching Design#Caching Strategy](SYSTEM_DESIGN/caching.md)

### Auth

#### Difference between JWT, OAuth, and SAML?

JWT is a data format(like a passport), while OAuth and SAML are protocols (the rules for checking that passport).

For more info, see: [Security#Difference between JWT, OAuth and SAML](SYSTEM_DESIGN/security.md)

#### How does Single Sign On(SSO) works?

Single Sign-On(SSO) is an authentication method that allows users to log in once and gain access to multiple independent software systems. It works by establishing a trust relationship between an Identity Provider (IdP) and various Service Providers (SPs).

For more info, see: [Security#SSO(Single Sign-On)](SYSTEM_DESIGN/security.md)

### Microservices

#### What Are Microservices?

Microservices is an architectural style where an application is composed of small, independent services, each running in its own process and communicating via lightweight mechanisms like HTTP/REST or messaging. Each service focuses on a specific business capability, can be developed, deployed, and scaled independently, and uses its own database. This contrasts with monolithic architecture where all components are tightly coupled in a single deployment unit.

For more info, see: [Architectural#Microservice Architecture](SYSTEM_DESIGN/architectural.md)

#### What Are the Differences Between SOA and Microservices?

SOA typically uses an Enterprise Service Bus (ESB) for centralized communication and often shares a single database, while microservices use lightweight protocols (HTTP/gRPC) directly between services and mandate database-per-service. SOA services are generally larger (coarser-grained) and deployed as monolithic applications, while microservices are smaller (finer-grained), independently deployable, and organized around business capabilities. SOA emphasizes integration of legacy systems; microservices emphasize agility and modern cloud-native development.

For more info, see: [Architectural#Microservice Architecture](SYSTEM_DESIGN/architectural.md)

#### What is the difference between Microservices and Monolithic architecture?

A Monolithic architecture is a single, unified unit where all functions are tightly coupled, while a Microservices architecture is a collection of small, independent services that communicate via APIs.

For more info, see: [Architectural#Microservices vs Monolithic Architecture](SYSTEM_DESIGN/architectural.md)

### Practice

#### Facebook

For more info, see: EXAMPLE/facebook.drawio

#### Drop Box

For more info, see: EXAMPLE/drop_box.drawio

#### Uber

For more info, see: EXAMPLE/uber.drawio

---



## Tool

### Base

#### What's your go-to method for profiling a slow C++ function?

My go-to approach is a systematic process. First, I use sampling profiler (e.g., perf) to get a high-level view without slowing down the code too much. Then I add targeted instrumentation around the suspect function using Google benchmark. Finally, I use micro-benchmarking to test hypotheses. The key is to measure before optimizing--never guess where the bottleneck is.

#### How do you handle a memory leak in a long-running C++ service?

To handle a memory leak in a long-running C++ service, I follow a systematic process: First, I confirm it's actually a leak using monitoring tools (e.g., RSS). Then I use Valgrind or AddressSanitizer to identify the soruce. For production systems where I can't run heavy tools, I use runtime instrumentation, custom allocator tracking, or restart strategies as a temporary mitigation while investigating the root cause.

### ROS

TODO

### GDB

For more info, see: [Development Tools#GDB](PROJ/dev_tool.md)

### Perf

TODO

### Valgrind

For more info, see: [Development Tools#Valgrind](PROJ/dev_tool.md)

### Google Breakpad

#### What specific crash data did Google Breakpad help you capture, and how did you use it to identify and fix the bug?

The Google Breakpad will storage the core file when application crashed. It contains the runtime values, environment setting and source code. It will help you a lot by checkout the core file.

For more info, see: [Development Tools#Breakpad](PROJ/dev_tool.md)

#### Google Benchmark

TODO
