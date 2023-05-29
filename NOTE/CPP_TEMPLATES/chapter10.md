# Chapter 10. Instantiation



## 10.1 On-Demand Instantiation

When a C++ compiler encounters the use of a template specialization, it will create that specialization by substituting the required arguments for the template parameters.

The need to access a member of a class template is not always very explicitly visible in the source code. For example, C++ overload resolution requires visibility into class types for parameters of candidate functions:

```c++
template <typename T>
class C {
    public:
        C(int); // 具有单参数的构造函数，可以被用于隐式类型转换
};

void candidate(C<double> const&);
void candidate(int) {}

int main()
{
    candidate(42); // 前面两个函数声明都可以被调用
}
```



## 10.2 Lazy Instantiation



## 10.3 The C++ Instantiation Model

### 10.3.1 Two-Phase Lookup

`two-phase lookup`: The first phase is the parsing of a template, and the second phase is its instantiation.

### 10.3.2 Points of Instantiation

The POI is a point in the source where the substituted template could be inserted.

### 10.3.3 The Inclusion and Separation Models

For nonclass POIs an alternative exists: The nonclass template can be declared using `export` and defined in another translation unit.

### 10.3.4 Looking Across Translation Units

### 10.3.5 Examples

```c++
template <typename T>
void f1(T x) {
    g1(x); // x是依赖名称，它依赖于T
    // g1(6); // 如果换成这样写，6是非依赖的，所以它应该查找不到g1。gcc正确抱错"错误：'g1'的实参不依赖模版参数，所以'g1'的声明必须可用[-fpermissive]"，VC++却通过编译并调用了后面的g1，这是不符合标准的。
}

int main() {
    f1(7);
}

void g1(int) {
    std::cout << "g1(int)" << std::endl;
}
```



## 10.4 Implementation Schemes

All these implementations rely on two classic components: a compiler and a linker. The compiler translates source code to object files, which contain machine code with symbolic annotations (cross-referencing other object files and libraries). The linker creates executable program or libraries by combining the object files and resolving the symbolic cross-references they contain.

### 10.4.1 Greedy Instantiation

Greedy instantiation assumes that the linker is aware that certain entities -- linkable template instantiations in particular -- may in fact appear in duplicate across the various object files and libraries. The compiler will typically mark these entities in a special way. When the linker finds multiple instances, it keeps one and discards all the others. There is not much more to it than that.

In theory, greedy instantiation has some serious drawbacks:

- The compiler may be wasting time on generating and optimizing N instantiations, of which only one will be kept.
- Linkers typically do not check that two instantiations are identical because some insignificant differences in generated code can validly occur for multiple instances of one template specialization. These small differences should not cause the linker to fail. (These differences could result from tiny differences in the state of the compiler at the instantiation time.) However, this often also results in the linker not noticing more substantial differences, such as when one instantiation was compiled for maximum performance whereas the other was compiled for most convenient debugging.
- The sum of all the object files could potentially be much larger than with alternatives because the same code may be duplicated many times.

### 10.4.2 Queried Instantiation

1. No specialization is avaliable: In this case, instantiation occurs, and the resulting specialization is entered in th edatabase.
2. A specialization is available but is out of date because source changes have occurred since it was generated. Here, too, instantiation occurs, but the resulting specialization replaces the one previously stored in the database.
3. An up-to-date specialization is available in the database. Nothing needs to be done.

Although conceptually simple, this design presents a few implementation challenges:

- It is not trivial to maintain correctly the dependencies of the database contents with respect to the state of the source code. Although it is not incorrect to mistake the third case for the second, doing so increases the amount of work done by the compiler(and hence overall build time).
- It is quite common to compile multiple source files concurrently. Hence, an industrial-strength implementation needs to provide the appropriate amount of concurrency control in the database.

### 10.4.3 Iterated Instantiation



## 10.5 Explicit Instantiation

It is possible to create explicitly a pointer of instantiation for a template specialization. The construct that achieves this is called an explicit instantiation directive. Syntactically, it consists of the keyword `template` followed by a declaration of the specialization to be instantiated.



## 10.6 Afternotes



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
