English | [中文版](feature_zh.md)

# C++ Features

[TOC]



## new

### new operator

The **new operator** is an operator and cannot be overloaded. If `A` is a class, then:

```cpp
A* a = new A;
```

Actually performs the following three steps:

1. Calls `operator new` to allocate enough memory, equivalent to:

   ```cpp
   operator new(sizeof(A));
   ```

2. Calls the constructor to create the object: `A::A()`.

3. Returns the corresponding pointer.

In fact, memory allocation is done by `operator new(size_t)`. If class `A` overloads `operator new`, then `A::operator new(size_t)` is called; otherwise, the global `::operator new(size_t)` provided by C++ is used.

### operator new

`operator new` is a function and has three forms (the first two only allocate memory and do **not** call constructors, which distinguishes them from the new operator):

```cpp
void* operator new(std::size_t size) throw(std::bad_alloc);
```

- Can be overloaded
- Allocates `size` bytes with proper alignment
- Returns a non-null pointer on success
- Throws `std::bad_alloc` on failure

```cpp
void* operator new(std::size_t size, const std::nothrow_t&) throw();
```

- Can be overloaded
- Returns `NULL` instead of throwing on failure

```cpp
void* operator new(std::size_t size, void* ptr) throw();
```

- Cannot be overloaded
- Placement new version, defined in `<new>`
- Does not allocate memory; only constructs the object

### placement new

Placement new is an overloaded form of `operator new`. It allows constructing an object in already-allocated memory (stack or heap).

Using the new operator requires searching the heap for free memory, which is slow and may fail. Placement new avoids this by constructing objects in a pre-allocated buffer:

- Constant-time allocation
- No allocation failure during runtime
- Avoids memory fragmentation

#### Advantages

- Suitable for real-time or long-running applications
- Reusable memory buffers

#### Usage

1. **Allocate buffer in advance**

```cpp
A* a = new A;                 // normal new
A* a = new(std::nothrow) A;   // nothrow new
new (p) A();                  // placement new
```

2. **Object construction**

Placement new calls the constructor at address `p`.

3. **Object destruction**

You must explicitly call the destructor:

```cpp
p->~A();
```

4. **Memory release**

- Heap buffer: `delete[] buf`
- Stack buffer: released automatically when scope ends

#### Notes

- Placement `new[]` requires extra space to store array size
- Placement new does not allocate memory, so `delete` must not be used
- `<new>` must be included

[Top](#C++ Features)

---



## explicit

The `explicit` keyword is used to modify constructors with a single parameter, preventing implicit conversions.

### Implicit conversion risk

Implicit conversions may create temporary objects that are discarded immediately, which is error-prone.

Using `explicit` suppresses such conversions.

```cpp
explicit BOOK(string ISBN, float price = 0.0f);
```

With `explicit`, implicit conversion like `string -> BOOK` is forbidden.

### Rules

- Only applies to constructors
- Only meaningful for constructors callable with one argument
- Still applies if other parameters have default values

### Recommendations

- Prefer `explicit` unless implicit conversion is clearly desired
- Improves code safety and readability

[Top](#C++ Features)

---



## const

The `const` keyword improves robustness and prevents accidental modification.

### Basic usage

```cpp
const int a = 100;
int const b = 100; // same meaning
```

### const pointers

```cpp
const int* p;      // pointer to const
int* const p;      // const pointer
const int* const p; // const pointer to const
```

### Key rules

- `const` on the left modifies the pointed value
- `const` on the right modifies the pointer itself
- References cannot be `const` themselves (`int& const` is invalid)

### Notes

1. Casting away `const` may cause undefined behavior
2. `const` objects cannot be assigned
3. `const` objects cannot bind to non-const references
4. `const` member functions are required for const objects

[Top](#C++ Features)

---



## volatile

`volatile` indicates that a variable may be changed by factors unknown to the compiler (hardware, OS, other threads).

The compiler will not optimize accesses to volatile variables.

### Multithreading

Without `volatile`, variables may be cached in registers, causing incorrect behavior in multi-threaded code.

```cpp
volatile bool bStop = false;
while (!bStop) { }
```

### Notes

- `volatile` does not guarantee atomicity or thread safety
- Applies to user-defined types
- Propagates similarly to `const`

[Top](#C++ Features)

---



## virtual

### Virtual functions

- Enable runtime polymorphism
- Default arguments are statically bound

### Pure virtual functions

```cpp
virtual void func() = 0;
```

- Must be overridden
- Base class becomes abstract

### Abstract classes

- Cannot be instantiated
- May have constructors and destructors

### Notes

1. Avoid calling virtual functions in constructors/destructors
2. Constructors, static functions, friends cannot be virtual
3. Base classes intended for polymorphic deletion must have virtual destructors

[Top](#C++ Features)

---



## static

`static` controls storage duration and visibility.

### Usage

- **Local variables**: initialized once, lifetime = program
- **Global variables**: file scope only
- **Functions**: file scope only
- **Class members**: shared across instances

### Notes

- Static data members must be defined outside the class
- Cannot access non-static members from static functions

[Top](#C++ Features)

---



## namespace

Namespaces prevent name collisions in large projects.

### Types

1. Named namespaces
2. Inline namespaces (C++11)
3. Anonymous namespaces
4. Namespace aliases

### Notes

- Avoid `using namespace` in headers

[Top](#C++ Features)

---



## union

A `union` can hold only one non-static data member at a time.

### Characteristics

- All members share memory
- Size equals largest member
- Cannot contain references or virtual functions
- Anonymous unions have special rules

[Top](#C++ Features)

---



## Pointers in C++

### Pointer to const

```cpp
const int* p;
```

- Cannot modify value through pointer
- Can point to different objects

### Const pointer

```cpp
int* const p = &x;
```

- Cannot change address
- Can modify value

### Const pointer to const

```cpp
const int* const p = &x;
```

[Top](#C++ Features)

---



## Pointer vs Reference

| Pointer                  | Reference                  |
| ------------------------ | -------------------------- |
| Can be null              | Cannot be null             |
| Can change target        | Fixed after initialization |
| Needs dereference        | No dereference             |
| Supports multiple levels | Single level only          |

[Top](#C++ Features)

---



## Summary

This document summarizes essential C++ language features, emphasizing correctness, safety, and best practices.

