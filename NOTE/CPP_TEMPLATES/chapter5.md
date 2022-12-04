# Chapter5 Tricky Basics



## 5.1 Keyword typename

The keyword `typename` was introduced during the standardization of C++ to clarify that an identifier inside a template is a type. Consider the following example:

```c++
template <typename T>
class MyClass{
    typename T::SubType *ptr;
}
```

Here, the second `typename` is used to clarify that `SubType` is a type defined within class  `T`. Thus, `ptr` is a pointer to the type `T::SubType`.

Without `typename`, `SubType` would be considered a static member. Thus it would be a concrete variable or object As a result, the expression `T::SubType *ptr` would be a multiplication of the static `SubType` member of class `T` with `ptr`.

A very similar problem was discovered after the introduction of `typename`. Consider the following example using the standard `bitset` type:

```c++
template <int N>
void printBitset(std::bitset<N> const& bs)
{
    std::cout << bs.template to_string<char, char_traits<char>, allocator<char> >();
}
```

In conclusion, the `.template` notation (and similar notations such as `->template`) should be used only inside templates and only if they follow something that depends on a template parameter.



## 5.2 Using `this->`

For class templates with base classes, using a name `x` by itself is not always equivalent to `this->x`, even though a member `x` is inherited.

```c++
template <typename T>
class Derived : public Base<T> {...}
```



## 5.3 Member Templates

Class members can also be templtes. This is possible for both nested classes and member functions.

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

