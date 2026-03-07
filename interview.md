English | [中文版](interview_zh.md)

# Interview

[TOC]



## C/C++

### Base

#### What is C++? How is it different from C?

c++ is a general-purpose, object-oriented programming language built as a extension of C. While C focuses on structred programming, C++ adds OOP features like classes, inheritance, poolymorphism, and encapsulation. It also supports function and operator overloading, plus templates, making code more reusable, efficient, and flexible.

For more info, see: [C++ Features](LANG/C++/feature.md), [C++ Object](LANG/C++/object.md)

#### What are access modifiers in C++?

Access modifiers control who can access class members and data members. They help encorce object oriented programming principles like encapsulation. There are three access modifieers in C++: public, private, protected.

For more info, see: [C++ Object](LANG/C++/object.md)

#### Can you describe what the basic structure of a C++ program is?

TODO

#### What is the purpose of comments in C++?

TODO

#### What is the difference between a declaration and a definition of a variable used in C++?

TODO

#### Can you discuss the difference between a local and global scope of a variable?

TODO

#### What is a pointer in C++, and how is it different from a reference?

A pointer stores the memory address of a variable. Each pointer has a unique memory address and can directly access the value it points to. Reference, on the other hand, is an alias to an existing variable. The main difference between the two is that the pointer can be null and can also be reassigned, while reference can not.

For more info, see: [C++ Features#Pointers](LANG/C++/feature.md)

#### What is the difference between pass by value and pass by reference?

In pass-by-value, only a copy of the data is sent, keeping the original safe. In pass-by-reference, the actual data is shared, so any changes affect the original.

#### Explain Shallow Copy, Deep Copy?

A shallow copy means copying an object in a way that only the outer structure is duplicated. A deep copy, on the other hand, makes a full, independent copy of the object, including any data the object points to. Deep copying takes more time and memory, but it is safer.

####  What is the difference between stack memory and heap memory?

Stack memory handles static allocation(local variables, function calls), while heap memory manages dynamic allocation(objects).

For more info, see: [C++ Objects](LANG/C++/object.md)

#### What is a recursive function? 

A recursive function calls itself to solve a problem by breaking it into smaller subproblems, with at least one base case to stop recursion.

#### What is Function Overloading in C++ (Compile Time Polymorphism)?

Function overloading allows multiple functions with the same name but different parameter lists(types or arity). The compiler will pick the best match at compile-time.

#### What is Function Overriding in C++ and How Does the Base Class Affect It?

In function overriding, a derived class provides a new implementation for a virtual function with the same signature as in the base. Resolution happens at runtime (dynamic dispatch).

#### What is the difference between function overriding, function overloading and function overwriting?

Function overloading allows you to define multiple functions in the same scope with the same name but different parameters. Function overriding occurs in inheritance hierarchies when a derived class provides a specific implementation for a function that is already defined in its base class. Function overwrite occurs in inhertitance hierarchies when a derived class hides base class method.

#### What is a friend function?

A friend function (or class) has access to a class's private and protected members. It can be used sparingly to implement symmetric operators or tightly coupled utilities without exposing internals publicly.

For more info, see: [C++ Objects](LANG/C++/object.md)

#### What is object slicing in C++? How can you avoid it?

Object slicing occurs when a derived object is copied by value into a base object, losing the derived part. During this process, the extra data members fo the derived class are "sliced off" or lost, leaving only the base class's members. We can avoid slicing by: passing by pointer or reference, use smart pointers, use `std::variant`, ...

For more info, see: [C++ Objects](LANG/C++/object.md)

#### What is the difference between an abstract class and an interface in C++? How do you implement an interface-like behavior in C++?

An abstract class is a class with **at least** one pure virtual function. An interface is a class with **only** pure virtual functions, it is a contract that defines a set of methods that a class must implement, without providing any implementation details ...

For more info, see: [C++ Objects](LANG/C++/object.md)

#### Explain the concept of encapsulation

Encapsulation is one of the core principles of OOP. It bundles data(member variables) with the methods (member functions) that operate on that data inside a single unit, called a class. It restricts direct access to some parts of an object and hides the data to protect its integrity.

For more info, see: [C++ Objects](LANG/C++/object.md)

#### What is multiple inheritance, and what problems can it cause?

Multiple inheritance (MI) lets a class inherit from more than one base. Here are the common issues that result from MI: Ambiguity, Diamond problem, complexity.

For more info, see: [C++ Objects](LANG/C++/object.md)

#### What is the difference between static data members and non-static data members?

static data member shared among all instances, by contrast, each object has its own copy of non-static member .

#### What is the “this” pointer, and how is it used?

Inside a non-static member function, this is a pointer to the current object.

#### What is a function pointer, and how do you use it?

A function pointer stores the address of a function with a specific signature, which lets you call it indirectly or pass it around (callbacks, table-driven code).

#### How does inline expansion of functions affect performance?

Inline expansion replaces a function call with the function body, potentially reducing call overhead and enabling further optimizations (constant propagation, loop unrolling).

#### How is exception handling implemented in C++?

Exception handling in C++ is implemented using three keywords: `try`, `catch` and `throw`. This mechanism allows a program to deal with runtime errors in a a structured way so that it doesn't stop abruptly.

#### What is the difference between std::exception and user-defined exceptions?

`std::exception` is the root of the standard hierarchy and provides a virtual `what()` string. Standard library errors derive from it. User-defined exceptions let you encode domain context. As long as they ultimately derive from `std::exception`, callers can catch generically while still matching specific types when desired.

#### How can RAII (Resource Acquisition is Initialization) help in exception safety?

RAII binds a resource's lifetime to an object's lifetime so that destructors perform cleanup automatically during normal execution and during exception unwinding. This prevents leaks and makes code exception-safe.

#### Explain templates in C++?

Templates enable generic programming by parameterizing code over types. The compiler generates concrete instantiations on use.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### What is Template Metaprogramming in C++?

Template Metaprogramming (TMP) is a technique where templates are used to compute values at compile time, enabling optimization and stack checks.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### What Is Template Specialization, and How Is It Useful?

Template specialization allows you to create a customized version of a template for a specific data type or condition. It's useful when the generic template does not fit all data types or when you want optimized behavior for a particular type.

For more info, see: [C++ Templates](LANG/C++/template.md)

#### What Are Variadic Templates in C++?

Variadic templates are an extension to C++ templates that allow them to accept a variable number of template arguments. This feature is invaluable for creating more flexible and reusable code structures, such as wrappers around existing functionality.

For more info, see: [C++ Templates](LANG/C++/template.md)

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

#### In the line "int* a, b;", how many pointers are declared?

Only `a` is a pointer, `b` is just an int.

### New Feature

#### Can you explain move semantics and why they are important in modern C++?

Move semantics allow resources to be transferred (moved) from temporaries or expiring objects instead of expensive deep copies, enabling performance gains and exception safety improvements.

For more info, see: [C++ Features#Move](LANG/C++/feature.md)

#### What is lvalue and rvalue?

An lvalue is an object that occupies a specific memory location and can be referred to by name. An rvalue is a temporary value that does not have a persistent memory address.

For more info, see: [C++ Features#Move](LANG/C++/feature.md)

#### What is SFINAE? How does it relate to template specialization?

SFINAE stands for Substitution Failure is not an error. It is a C++ template metaprogramming rule where, if template substitution fails, the compiler does not throw an error but instead removes that candidate from consideration.

For more info, see: [C++ Template#SFINAE](LANG/C++/template.md)

#### What is Perfect Forwarding in C++ and how is it achieved?

Perfect forwarding is a technique to pass arguments to another function without losing their value category (lvalue or rvalue). It's essential in generic programming to write functions that forward arguments efficiently.

#### What are decltype and auto keywords used for?

`auto` deduces the variable type from the initializer. It's great for long iterator types, lambdas, and templates. `decltype(expr)` yields the exact tyep of an expression(including references and cv-qualifiers) without evaluating it.

For more info, see: [C++ Features#decltype](LANG/C++/feature.md)

#### What are lambda expressions in C++11 and later?

Lambdas are inline, anonymous function objects with optional captures. They enable concise callbacks and algorithms.

#### What is the main use of the keyword “Volatile”?

The volatile keyword prevents teh compiler from performing optimization on the code.

For more info, see: [C++ Features#volatile](LANG/C++/feature.md)

#### What Is `constexpr` and Why Is It Significant?

`constexpr` is used to define expressions or functions that are evaluated at compile-time, ensuring greater efficiency by precomputing values wherever possible.

For more info, see: [C++ Features#constexpr](LANG/C++/feature.md)

#### What is C++ storage class?

Storage class is used to defines the scope(visibility), lifetime, and linkage of variables or functions. These features usually help in tracing the existence of a variable during the runtime of a program.

#### What is a mutable storage class specifier? How can they be used?

The `mutable` keyword is a storage class specifier used only with non-static data members of a class. It allows a member of a const object to be modified. Normally, if an object is declared const, you cannot modify any of its members, but mutable makes an exception.

For more info, see: [C++ Features#mutable](LANG/C++/feature.md)

### STL

#### What is 'namespace'?

Namespace is a feature that provides a way to group related identifiers such as variables, functions, and classes under a single name.

#### What is std in C++?

`std` is a namespace in C++ that stands fro standard. It contains the most standard library, including essential components like input/output streams, string manipulation, and various data structures and algorithms.

For more info, see: [C++ STL](LANG/C++/stl.md)

#### Explain Smart Pointers in C++?

Smart pointers are template classes in `<memory>` that automate memory management and prevent leaks by destroying objects when they go out of scope.

For more info, see: [C++ STL#Smart pointers](LANG/C++/stl.md)

#### How Do `std::function` and `std::bind` Work in C++?

`std::function` is a polymorphic wrapper used to store and invoke any callable object, such as functions, lambdas, or bind expressions. `std::bind` allows you to bind specific arguments to a function, creating a new function object.

---



## DB

TODO

---



## Network

TODO

---



## Algorithm

### Complexity Analysis

TODO

### Array

TODO

### Dynamic Programming

TODO

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

#### Compare Linear Search and Binary Search.

Linear Search checks elements sequentially, while Binary Search halves the search space with each step, making it more efficient for sorted data.

For more info, see: [Searching Algorithm Summary](ALGO/search.md)

#### How deos Hashing work in searching?

Hashing uses a hash function to compute an index for each element, allowing for constant-time search operations in the average case by storing elements in a hash table.

For more info, see: [Searching Algorithm Summary#Hash-Based Search](ALGO/search.md)

### Sorting

#### What is a sorting algorithm?

A sorting algorithm is a method used to arrange elements in a specific order, often from smallest to largest or vice versa, making data easier to manage and search.

For more info, see: [Sorting Algorithm Summary](ALGO/sort.md)

#### Why Sorting algorithms are important?

The effectiveness of other algorithms that depend on input data being in sorted lists is enhanced by efficient sorting. Sorting is also frequently helpful for generating output that is readable by humans. Sorting is directly used in divide-and-conquer strategies, database algorithms, data structure algorithms and many other applications.

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

TODO

---



## System Design

### Design Pattern

#### What is the Singleton Design Pattern?

The Singleton Pattern ensures that only one instance of a class is created throughout the program and it provides a global point of access to that instance...

For more info, see: [Design Pattern#SINGLETON](PROJ/design_pattern.md)

#### What is the Observer Design Pattern?

The Observer Pattern defines a one-to-many dependency so that when one object (subject) changes, all dependent objects(observers) are notified...

For more info, see: [Design Pattern#OBSERVER](PROJ/design_pattern.md)
