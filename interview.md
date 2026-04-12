English | [中文版](interview_zh.md)

# Interview

[TOC]



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

#### What is the difference between `const` and `#define`?

`const` and `#define` are used to define constants, but `const` is a type-safe variable checked at compile-time with scope, while `#define` is a preprocessor macro that performs simple text substitution before compilation.

#### What are default arguments?

Default arguments are values that are used when a function is called without some parameters.

#### Discuss the difference between prefix and postfix?

Prefix and postfix operators differ primarily in the timing of their operation relative to expression evaluation. Prefix(`++x`) increments the variable first and returns the updated value, while postfix(`x++`) returns the original value before incrementing. Both increment the variable by 1, but prefix affects the current expression immediately.

#### What are the different data tyeps present in C++

C++ data types are divided into 4 main categories: primitive(built-in) types, derived types, enumeration and user-defined types.

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

#### Can virtual functions be `constexpr`?

No! Virtual dispatch requires a runtime.

#### What is C++ storage class?

Storage class is used to defines the scope(visibility), lifetime, and linkage of variables or functions. These features usually help in tracing the existence of a variable during the runtime of a program.

#### What is a mutable storage class specifier? How can they be used?

The `mutable` keyword is a storage class specifier used only with non-static data members of a class. It allows a member of a const object to be modified. Normally, if an object is declared const, you cannot modify any of its members, but mutable makes an exception.

For more info, see: [C++ Features#mutable](LANG/C++/feature.md)

#### What's the difference between `override` and `final`?

`override` tells the compiler this function is meant to override a base virtual function (catches signature errors). `fina` prevents further overriding in derived classes.

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

#### Can you have a virtual function with default arguments?

Yes, but DANGEROUS! Default arguments are determined at compile-time based on the static type.

For more info, see: [C++ Object Oriented Programming#Virtual Inheritance](LANG/C++/oop.md)

#### Can static functions be virtual?

No, Virtual dispatch requires a `this` pointer (object instance). Static functions belong to the class, not objects.

For more info, see: [C++ Object Oriented Programming#Virtual functions](LANG/C++/oop.md)

#### What happens when we override a function but forget to use `virtual` in the base class?

Function overriding won't work as runtime polymorphism, instead, function hiding occurs when the base class function is hidden by the derived class function if called through a derived object.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

#### What is polymorphism in C++?

Polymorphism means one interface, multiple implementations. It allows the same function or operator to behave differently depending on the context.

For more info, see: [C++ Object Oriented Programming](LANG/C++/oop.md)

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

#### Can we call a virtual function from a constructor?

Yes, we can call a virtual function from a constructor, but during base class construction, the derived part of the object is not yet initialized.

For more info, see: [C++ Object Oriented Programming#Construction and Destruction](LANG/C++/oop.md)

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

Depends on inheritance depth.

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

#### What are iterators in STL?

An iterator is an object(like a pointer) used to traverse containers. STL uses iterators to access elements in a uniform manner, regardless of the container. Iterators help in writing generic algorithms that work across differnt container types.

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

TODO

#### What are the methods of exporting a function from a DLL?

TODO


---



## DB

### SQL

#### What is the difference between CHAR and VARCHAR2?

CHAR stores fixed-length data and pads extra spaces; VARCHAR2 stores variable-length data, saving storage space.

#### What is a view in SQL?

A view is a virtual table created by a `SELECT` query. It does not store data itself, but presents data from one ore more tables in a structured way. Views simplify complex queries, improve readability, and enhance security by restricting access to specific rows or columns.

For more info, see: [SQL Language#Views](DB/sql.md)

#### What is the purpose of the UNIQUE constraint?

The UNIQUE constraint ensures that all values in a column (or combination of columns) are distinct. This prevents duplicate values and helps maintain data integrity.

For more info, see: [SQL Language#Unique constraint](DB/sql.md)

#### Explain the difference between the `WHERE` and `HAVING` clauses

`WHERE` filters individual rows before grouping or aggregation, so it can't use aggregate functions like SUM or COUNT; it's best for narrowing raw data early (e.g., a date range or status).

`HAVING` filters the resulting groups after `GROUP BY`, so it's meant for conditions on aggregates (e.g., groups with totals above a threshold).

#### What are SQL joins, and what are the differences between `INNER`, `LEFT`, `RIGHT`, and `FULL` joins?

SQL joins combine rows from two tables based on a matching condition (typically keys) to answer questions that span both tables...

For more info, see: [SQL Language#Joins](DB/sql.md)

#### What is a CTE (Common Table Expression) and when would you use it?

A CTE (Common Table Expression) is a temporary, named result set defined with `WITH` that exists only for the duration of a single statement. You use CTEs to break complex logic into steps, avoid repeating the same subquery, improve readability/maintenance, enable recursion, and make debugging easier.

#### What is the difference between `UNION` and `UNION ALL`?

`UNION` combines results from two (or more) `SELECT`s and removes duplicates (it performs a `DISTINCT` across all columns), which adds sorting/hash work and can be slower.

`UNION ALL` keeps duplicates and usually runs faster because it simply appends result sets.

#### How would you calculate the running total of sales for each product?

Use a window (analytic) function: compute `SUM(amount)` over rows of the same product, ordered by time, accumulating from the start up to the current row.

#### What are EXISTS and NOT EXISTS and how do they differ from IN

`EXISTS` checks whether a correlated subquery returns at least one row; `NOT EXISTS` checks that it returns none. They return boolean and stop at the first match, ignoring what the subquery selects. `IN` compares a value against a list/set (literal list or subquery output).

#### Explain the difference between `RANK()`, `DENSE_RANK()` and `ROW_NUMBER()`

`ROW_NUMBER()` assigns a unique sequential number to each row within a partition based on the order--no ties share a number (ties are broken arbitrarily by the `ORDER BY`).

`RANK()` assigns the same rank to tied rows but leaves gaps after ties.

`DENSE_RANK()` also assigns the same rank to ties but doesn't leave gaps.

#### Explain the purpose of LAG and LEAD functions.

LAG and LEAD are window functions that let you look at values from previous (LAG) or next (LEAD) rows in the same result set without self-joins. They're used for comparisons across rows e.g., changes yesterday to today, detecting trends, or filling forward/backward values.

#### What is a cross join and how does it differ from an inner join?

A `CROSS JOIN` returns teh cartesian product of two tables--every row from A paired with every row from B so the result size is `rows(A) x rows(B)`, and it doesn't use a join condition.

An `INNER JOIN` returns only the rows where the specified join condition matches between the two tables, so its result is a filtered subset, not every combination.

#### Explain foreign keys and how they enforce referential integrity.

A foreign key (FK) is a column (or set of columns) in a child table taht references a primary/unique key in a parent table to ensure the child's values actually exist in the parent. This enforces referential integrity by preventing actions that would create "orphan" rows.

#### Describe set operations like UNION, INTERSECT and EXCEPT and when each is useful.

`UNION`, `INTERSECT`, and `EXCEPT` are SQL set operations that combine results from two queries with the same number of columns and compatible data types. `UNION` returns the distinct union of both result sets (removes duplicates).

#### What are the main types of SQL commands?

SQL commands are broadly classified into:

- DDL(Data Definition Language)
- DML(Data Manipulation Language)
- DCL(Data Control Language)
- TCL(Transaction Control Language)

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

For more info, see: [SQL Language](DB/sql.md)

### Query

#### What is a query in SQL?

A query is a SQL statement used to retrieve, update, or manipulate data in a database. The most common type of query is a `SELECT` statement, which fetches data from one or more tables based on specified conditons.

For more info, see: [DB Query](DB/query.md)

#### What is a subquery?

A subquery is a query nested within another query. It is often used in the `WHERE` clause to filter data based on the results of another query, making it easier to handle complex conditons.

For more info, see: [DB Query](DB/query.md)

#### How would you optimize a slow query?

1. measure: reproduce the issue, capture timings, and run `EXPLAIN/EXPLAIN ANALYZE` to see teh plan, row estimates, and bottlenecks;
2. fix fundamentals
3. sargable predicates: avoid functions on columns, leading `%` wildcards, or expressions that prevent;
4. Reduce data early with selective `WHERE` filters, fetch only needed columns (no `SELECT *`), and prefer `EXISTS` over `IN` for semi-joins;
5. Tame row explosion by checking `JOIN` selectivity, deduplicating before joins, and pre-aggregating where helpful;
6. Rewrite problematic patterns: split wide ORs into `UNION ALL`, replace correlated subqueries with joins, consider window functions carefully;
7. For large sets, use keyset pagination (seek method) instead of `OFFSET`, and consider materialized views, caching, or partitioning for heavy, recurring analytics.

For more info, see: [Database Best Practice#Optimization](DB/best_practice.md)

#### Write a SQL query to retrieve all employees from the "Employees" table who work in the "Engineering" department, assuming there's a "Department" table.

```sql
SELECT E.* FROM Employees AS E JOIN Departments AS D ON E.DepartmentID = D.DepartmentID WHERE D.DepartmentName = 'Engineering';
```

### Index

#### What are indexes, and why are they used?

Indexes are database objects that improve query performance by allowing faster retrieval of rows. They function like a book's index, making it quicker to find specific data without scanning the entire table. However, indexes require additional storage and can slightly slow down data modification operations.

For more info, see: [SQL Language#Indexes](DB/sql.md)

#### How do clustered and non‑clustered indexes differ?

A clustered index stores table rows in the physical order of the index key, so you can have only one; by contrast, A `non-clustered` index is a separate structure and you can have many.

For more info, see: [SQL Indexing And Hashing#Terminology](DB/index.md)

#### How do you perform pattern matching in SQL?

SQL supports pattern matching mainly with `LIKE` (and `NOT LIKE`) using wildcards `%` for any-length string and `_` for a single character.

### Cursor

#### What is a cursor in SQL?

A cursor is a database object used to retrieve, manipulate, and traverse through rows in a result set one row at a time.

For more info, see: [SQL Language](DB/sql.md)

### Trigger

#### What is a trigger in SQL?

A trigger is a set of SQL statemetns that automatically execute in response to certain events on a table, such as `INSERT`, `UPDATE`, or `DELETE`. Triggers help maintain data consistency, enforce business rules, and implement complex integrity constraints.

For more info, see: [SQL Language](DB/sql.md)

### Table

#### What is a table in SQL?

A table is a structured collection of related data organized into rows and columns. Columns define the type of data stored, while rows contain individual records.

For more info, see: [SQL Language#Table operations](DB/sql.md)

#### What is a composite primary key?

A composite primary key uses two or more columns together to uniquely identify each row when one column alone isn't sufficient.

#### Describe a `PRIMARY KEY` and how it differs from a `UNIQUE` key

A `PRIMARY KEY` uniquely identifies each row in a table: it combines `UNIQUE + NOT NULL`, there can be only one per table, and it's the default target for foreign keys.

A `UNIQUE` key also enforces uniqueness, but doesn't require `NOT NULL` and you can have many `UNIQUE` constraints per table.

#### Explain the difference between a primary key and a foreign key in a relational database.

A primary key uniquely identifies each record within a table, while a foreign key links two table together by referencing the primary key of another table.

For more info, see: [DB Table#Compare Primary Key And Foreign Key](DB/table.md)

### Stored Procedure

#### What is a stored procedure?

A stored procedure is a precompiled set of SQL statements stored in the database. It can take input parameters, perform logic and queries, and return output values or result sets.

For more info, see: [SQL Language#Stored Procedures](DB/sql.md)

### Partitioning

#### Explain database partitioning

Database partitioning is the practice of splitting a large table (and its indexes) into smaller, more manageable pieces called partitions while keeping it logically a single table. This improves query performance, eases maintenance, and enhances availability.

For more info, see: [Database Best Practice#Partitioning](DB/best_practice.md)

### Normalization

#### Explain normalization and briefly describe the different normal forms.

Normalization organizes relational data to minimize redundancy and prevent `update/insert/delete` anomalies by splitting tables based on dependencies while preserving meaning.

For more info, see: [Relational Model#Normalization and functional dependencies](DB/relational_model.md)

#### What is denormalization, and when is it used?

Denormalization is the process of combining normalized tables into larger tables for performance reasons. It is used when complex queries and joins slow down data retrieval, and the performance benefits outweigh the drawbacks of redundancy.

For more info, see: [Relational Model#Normalization and functional dependencies](DB/relational_model.md)

### Safety

#### What strategies can protect a web application from SQL injection?

The primary defense against SQL injection is to use parameterized queries (prepared statements) everywhere never build SQL with string concatenation. Combines this with allow-list input validation, least-privilege DB account, and safe stored procedures that don't assemble dynamic SQL.

For more info, see: [Database Best Practice#Parameterized Query](DB/best_practice.md)

### NoSQL

#### What are the differences between SQL and NoSQL databases?

SQL is best for structured, reliable transactions, while NoSQL shines in handling massive, fast-changing, and unstructured data.

For more info, see: [SQL Language](DB/sql.md)

---



## Network

### TCP

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

### Linked List

#### What are the differences between an `array` and a `list`?

The main differences are in the memory layout. Arrays store elements contiguously in memory, providing random access. List store elements non-continuously via pointers, **not providing** random access.

For more info, see: [Linked List#Diagrams](ALGO/link_list.md)

#### Reverses a linked list iteratively using three pointers: current, previous, and next.

At each step, point the current node to its previous node and then move all three pointers forward until the list is fully reversed.

For more info, see: [Linked List#Reverse](ALGO/link_list.md), [Linked List Problems](ALGO/LEET_CODE/linked_list.md)

#### Finds the middle of a linked list using the slow and fast pointer technique.

The idea is to traverse the entire linked list once to count the total number of nodes. After determining the total count, traverse the list again and stop the middle node to return its value.

For more info, see: [Linked List#Reverse](ALGO/link_list.md), [Linked List Problems](ALGO/LEET_CODE/linked_list.md)

#### Detecting a cycle in a linked list.

Using Floyd's Algorithm is the best choice with average time complexity equal to O(n).

For more info, see: [Linked List](ALGO/link_list.md), [Linked List Problems](ALGO/LEET_CODE/linked_list.md)

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

Dijkstra's algorithm finds the shortest path from a starting node to all other nodes in a weighted graph. It's commonly used in routing and network optimization problems.

For more info, see: [Shortest-Path Algorithms#Dijkstra's algorithm ](ALGO/shortest_path_problem.md)

#### What is Huffman coding and how does it utilize a greedy strategy to compress data?

Huffman coding is a technique for lossless data compression where characters are represented by variable-length codes. It uses a greedy strategy to assign shorter codes to more frequent characters.

For more info, see: [Huffman Codes](ALGO/huffman.md)

### Recursive Algorithm

#### What is recursion and how does it work?

Recursion is a programming technique where a function calls itself to solve a problem.

For more info, see: [Recursion](ALGO/recursion.md)

### Divide and Conquer Algorithm

#### Split the array in half, sort both halves, then merge them back.

We use the two positions (left, right) divide the array continuously, until array's size equal to 2; then sorted it.

For more info, see: [Sorting Algorithm Summary](ALGO/sort.md), [Divide and Conquer Algorithm](ALGO/LEET_CODE/divide_and_conquer.md)

### Backtracking Algorithm

#### Generates all permutations of a string using recursion and backtracking.

First initialize an array of string `arr[]` to store all the permutations. Start from the 0th index and for each index `i`, swap the value `str[i]` with all the lememts in its right i.e. From `i + 1` to `n - 1`, and recur to the index `i + 1`. If the index `i` is equal to `n`, store the resultant string in `arr[]`, else keep operating similarly for all other indices. Thereafter, swap back the values to original values to initiate backtracking. At last sort the array `arr[]`.

For more info, see: [Backtracking Problem](ALGO/LEET_CODE/backtracking.md)

### Searching

#### What is a searching algorithm?

A searching algorithm is a method used to find a specific item within a collection of data. Searching Algorithms are designed to check for an element or retrieve an element from any data structure where it is stored.

#### What are the different types of searching algorithms?

Searching algorithms include Linear Search, Binary Search, Depth-First Search (DFS), Breadth-First Search(BFS) and Hashing, each with its own approach to find elements.

For more info, see: [Searching Algorithm Summary](ALGO/search.md)

#### When is each searching algorithm most appropriate to use?

Choose the appropriate searching algorithm based on factors like data structure, data size and desired search efficiency, such as Binary Search for sorted arrays and Hashing for constant-time searches.

For more info, see: [Searching Algorithm Summary](ALGO/search.md)

#### Explain Linear Search and its time complexity.

Linear Search checks each element in a list one by one until finding the target or reaching the end. Its time complexity is $O(n)$ in the worst case.

For more info, see: [Searching Algorithm Summary#Linear Search](ALGO/search.md)

#### How does Binary Search work?

Binary Search divides a sorted array in half repeatedly, narrowing down the search space by comparing the target with the mid until finding the target or exhausting the elements.

For more info, see: [Searching Algorithm Summary#Binary Search](ALGO/search.md)

#### Recursive and Iterative Binary Search: Which one is more efficient and why?

Iterative Binary Search is typically more efficient than Recursive Binary Search. This is because iterative binary search avoids teh overhead of recursive function calls and tasks space consumption, resulting in lower memory usage and potentially faster execution, especially for large datasets.

For more info, see: [Searching Algorithm Summary#Binary Search](ALGO/search.md)

#### What are the requirements for using Binary Search?

Binary Search requires a sorted array and the ability to access elements by index for efficient traversal.

For more info, see: [Searching Algorithm Summary](ALGO/search.md)

#### How deos Hashing work in searching?

Hashing uses a hash function to compute an index for each element, allowing for constant-time search operations in the average case by storing elements in a hash table.

For more info, see: [Searching Algorithm Summary#Hash-Based Search](ALGO/search.md)

#### Compare Linear Search and Binary Search

Linear Search checks elements sequentially, while Binary Search halves teh search space with each step, making it more efficient for sorted data with a time complexity of $O(\log n)$.

For more info, see: [Searching Algorithm Summary#Complixity Analysis](ALGO/search.md)

#### Recursive and Iterative Binary Search: Which one is more efficient and why?

Iterative Binary Search is typically more efficient than Recursive Binary Search. This is because iterative binary search avoids the overhead of recursive function calls and stack space consumption, resulting in lower memory usage and potentially faster execution, especially for large datasets.

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

The algorithm maintains two variables: `max_ending_here` to track teh maimum sum ending at the current position, and `max_so_far` for the overall maximum sum found so far.

For more info, see: [Search Algorithm Summary#Kadane's Algorithm](ALGO/search.md), [Search Problem](ALGO/LEET_CODE/search.md)

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

#### Why is Merge sort preferred over Quick Sort for sorting linked lists?

Merge Sort is preferred fro sorting linked lists because its divide-and-conquer approach easily divides the list into halves and merges them efficiently without requiring random access, which is difficult in linked lists. Quick Sort's reliance on random access and potential worst-case time complexity makes it less suitable for linked lists.

For more info, see: [Sorting Algorithm Summary#Merge Sort](ALGO/sort.md)

#### What is Stability in sorting algorithm and why it is important?

Stability in sorting algorithms means that the relative order of equal elements remains unchanged after sorting. Stable sorting algorithms ensure that equal elements maintain their original positions in the sorted sequence.

#### What is the best sorting algorithm for large datasets?

For large datasets, efficient sorting algorithms like Merge Sort, Quick Sort or Heap Sort are commonly used due to their average time complexity of $O(n \log n)$, which performs well even with large amounts of data.

#### How does Quick Sort work?

Quick Sort is a Divide and Conquer sorting algorithm. It chooses a pivot element and rearrange the array so that elements smaller than the pivot are on the left and elements greater are on the right. Then, recursively apply the partitioning process to the left and right subarrays. Subarrays of size one or zero are considered sorted.

For more info, see: [Sorting Algorithm Summary#Quick Sort](ALGO/sort.md)

#### What is the worst-case time complexity of Quick Sort?

In the worst case, Quick Sort may take $O(N^2)$ time to sort the array. The worst case will occur when every time the problem of size $N$, get divided into 2 subproblems of size 1 and $N - 1$.

---



## OS

### Process, Thread, and Coroutine

#### Explain the difference between a process and a thread in operating systems.

A process is an independent, executing program with its own dedicated memory space, while a thread is a smaller, lightweight unit of execution within a process that shares the parent process's memory and resources.

For more info, see: [Process, Thread, and Coroutine#Summary](OS/progress_thread_coroutine.md)

#### Explain what a deadlock is and describe two conditions that must hold for a deadlock to occur.

A deadlock is a computing state where two or more processes are permanently blocked because each holds a resource the other needs, resulting in an indefinite wait. It requires four conditions: Mutual Exclusion, Hold and Wait, No Preemption, and Circular Wait.

For more info, see: [Process, Thread, and Coroutine#Deadlock](OS/progress_thread_coroutine.md)

### Memory Management

#### Explain how virtual memory works and why it's essential for modern operating systems.

Virtual memory gives each process the illusion of a large, private, contiguous address space. Provide an efficient use of physical memory by keeping only active page in RAM; Simpler programming model; Isolate processes from each other and from the kernel.

For more info, see: [Memory Management#Virtual memory](OS/mem_mgr.md)

#### Explain how page faults occur and what the OS does when a page fault happens.

A page fault occurs when a program tries to access data on a page not currently mapped to physical RAM. The OS handles this by pausing the process, fetching the required page from disk into a free RAM frame, updating the page table, and resuming the process.

For more info, see: [Memory Management#Virtual memory](OS/mem_mgr.md)

#### How the OS manages the page replacement algorithm? using LRU as an example.

The OS manges the page replacement strategies include: LRU, FIFO, Working-set algorithms. For example, When physical memory is full and a new page needs to be loaded, the LRU algorithm selects the page that has not been used for the longest period of time and replaces it.

For more info, see: [Memory Management#Page replacement policies](OS/mem_mgr.md)

### IO

#### Why is exclusive ownership important when managing a file handle?

Exclusive ownership in file handle managment ensures data integrity, prevents resource leaks, and guarantees that only one process can safely modify a file, mitigating risks of corruption.

For more info, see: [Multiprocessor Systems#Process Synchronization](PROJ/design_pattern.md)

---



## System Design

### Base

#### What is difference between API Gateway and Load Balancer?

An API Gateway is an intelligent entry point that manages, secures, and routes API requests to specific microservices, while a Load Balancer focuses on distributing traffic across multiple servers to ensure high availability and prevent overload.

For more info, see: [Load Balancing#API Gateway vs Load Balancer](SYSTEM_DESIGN/load_balance.md)

#### What is difference between Reverse Proxy and Forward Proxy?

A forward proxy acts on behalf of the client while a reverse proxy acts on behalf of the server.

For more info, see: [Proxy#Proxy Vs Reverse Proxy](SYSTEM_DESIGN/proxy.md)

#### What is difference between Horizontal scaling and vertical scaling?

Horizontal scaling adds more machines to your pool of resources(scaling out), while vertical scaling adds more power(CPU, RAM) to an existing machine(scaling up).

For more info, see: [System Dependabilityy#Horizontal vs Vertical Scaling](SYSTEM_DESIGN/system_dependability.md)

#### What is difference between Microservices and Monolithic architecture?

A Monolithic architecture is a single, unified unit where all functions are tightly coupled, while a Microservices architecture is a collection of small, independent services that communicate via APIs.

For more info, see: [Architectural#Microservices vs Monolithic Architecture](SYSTEM_DESIGN/architectural.md)

#### What is difference between vertical and horizontal partitioning?

Horizontal partitioning splits a table by its rows(reducing table size), while Vertical partitioning splits it by its columns(reducing table width).

For more info, see: [Database Designl#Horizontal Partitioning vs Vertical Partitioning](SYSTEM_DESIGN/db.md)

#### What is rate limiter? How does it work?

A Rate Limiter is a tool used to control the rate of traffic sents by a client or received by a server. It acts as a "gatekeeper" that defines how many requests a user can make within a specific timeframe. Rate limiters track requests using specific logic to decide whether to allow, drop, or delay a request.

For more info, see: [Rate Limiting](SYSTEM_DESIGN/rate_limiting.md)

#### How does Single Sign On(SSO) works?

Single Sign-On(SSO) is an authentication method that allows users to log in once and gain access to multiple independent software systems. It works by establishing a trust relationship between an Identity Provider (IdP) and various Service Providers (SPs).

For more info, see: [Security#SSO(Single Sign-On)](SYSTEM_DESIGN/security.md)

#### How does Apache Kafka works? why it so fast?

Apache Kafka is a distributed event streaming platform designed to handle trillions of events a day. At its core, it is a distributed commit log--an immutable, append-only sequence of records spread across multiple servers.

For more info, see: [Message Queues#Why is Kafka Fast](SYSTEM_DESIGN/mq.md)

#### Difference between Kafka, ActiveMQ, and RabbitMQ?

Kafka is a distributed streaming platform, RabbitMQ is a versatile message broker, and ActiveMQ is a traditional enterprise-grade broker.

For more info, see: [Message Queues#RabbitMQ vs Apache Kafka vs ActiveMQ](SYSTEM_DESIGN/mq.md)

#### Difference between JWT, OAuth, and SAML?

JWT is a data format(like a passport), while OAuth and SAML are protocols (the rules for checking that passport).

For more info, see: [Security#Difference between JWT, OAuth and SAML](SYSTEM_DESIGN/security.md)

### Design Pattern

#### What is the Singleton Design Pattern?

The Singleton Pattern ensures that only one instance of a class is created throughout the program and it provides a global point of access to that instance...

For more info, see: [Design Pattern#SINGLETON](SYSTEM_DESIGN/design_pattern.md)

#### What is the Observer Design Pattern?

The Observer Pattern defines a one-to-many dependency so that when one object (subject) changes, all dependent objects(observers) are notified...

For more info, see: [Design Pattern#OBSERVER](SYSTEM_DESIGN/design_pattern.md)

### Optimize

#### Tell me about a time you had to optime C++ Code for performance; what was the bottleneck and how did you improve it?

In my last company, a teammate committed a function that I found to be qutie resource-intensive. During a code review, I noticed he had used pass by value, whereas I would have used pass by reference.

For more info, see: [C++ Best Practice](LANG/C++/best_practice.md)

### Practice

#### Facebook

For more info, see: EXAMPLE/facebook.drawio

#### Drop Box

For more info, see: EXAMPLE/drop_box.drawio

#### Uber

For more info, see: EXAMPLE/uber.drawio

---



## Tool

### ROS

TODO

### GDB

For more info, see: [Development Tools#GDB](PROJ/dev_tool.md)

### Valgrind

For more info, see: [Development Tools#Valgrind](PROJ/dev_tool.md)

### Google Breakpad

#### What specific crash data did Google Breakpad help you capture, and how did you use it to identify and fix the bug?

The Google Breakpad will storage the core file when application crashed. It contains the runtime values, environment setting and source code. It will help you a lot by checkout the core file.

For more info, see: [Development Tools#Breakpad](PROJ/dev_tool.md)
