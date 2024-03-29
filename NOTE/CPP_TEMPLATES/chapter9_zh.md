# Chapter9 模板中的名称


<!-- vim-markdown-toc GFM -->

* [9.1 名称的分类](#91-名称的分类)
* [9.2 名称查找](#92-名称查找)
    - [9.2.1 Argument-Dependent Lookup(ADL)](#921-argument-dependent-lookupadl)
    - [9.2.2 友元名称插入](#922-友元名称插入)
* [9.2.3 插入式类名称](#923-插入式类名称)
* [9.3 解析模板](#93-解析模板)
    - [9.3.1 非模板中的上下文相关性](#931-非模板中的上下文相关性)
    - [9.3.2 依赖型类型名称](#932-依赖型类型名称)
    - [9.3.3 依赖型模板名称](#933-依赖型模板名称)
    - [9.3.4 using-declaration中的依赖型名称](#934-using-declaration中的依赖型名称)
    - [9.3.5 ADL和显式模板实参](#935-adl和显式模板实参)
* [9.4 派生和类模板](#94-派生和类模板)
    - [9.4.1 非依赖型基类](#941-非依赖型基类)
    - [9.4.2 依赖型基类](#942-依赖型基类)
* [9.5 本章后记](#95-本章后记)

<!-- vim-markdown-toc -->



## 9.1 名称的分类

受限名称：一个名称使用域解析运算符（`::`）或者成员访问运算符（`.`或`->`）来显式表明它所属的作用域。

依赖型名称：一个名称（以某种方式）依赖于模板参数。

名称的分类：

| 分类                                   | 说明和要点 |
|----------------------------------------|------------|
| 标识符                                 | -          |
| 运算符id(Operator-function-id)         | -          |
| 类型转换函数id(Conversion-function-id) | -          |
| 模板id(Template-id)                    | -          |
| 非受限id(Unqualified-id)               | -          |
| 受限id(Qualified-id)                   | -          |
| 受限名称(Qualified name)               | -          |
| 非受限名称(Unqualified name)           | -          |



## 9.2 名称查找

依赖于参数的查找（argument-dependent lookup, ADL）只能用于非受限的名称。

### 9.2.1 Argument-Dependent Lookup(ADL)

如果名称后面的括号里面有（一个或多个）实参表达式，那么ADL将会查找这些实参的associated class（关联类）和associated namespace（惯量名字空间）。

对于给定类型，对于由associated class和associated namespace所组成的集合的准确定义，我们可以通过下列规则来确定：

- 对于基本类型，该集合为空集。
- 对于指针和数组类型，该集合是所引用类型的associated class和associated namespace。
- 对于枚举类型，associated namespace指的是枚举声明所在的namespace。对于类成员，associated class指的是它所在的类。
- 对于class类型（包含联合类型），associated class集合包括：该class类型本身，它的外围类型，直接基类和间接基类。
- 对于函数类型，该集合包括所有参数类型和返回类型的associated class和associated namespace。
- 对于类X的成员指针类型，除了包括成员相关的associated namespace和associate class，该集合还包括与X相关的associated namespace和associated class。

### 9.2.2 友元名称插入

在类中的友元函数声明可以是该友元函数的首次声明。

C++标准规定：友元声明在外围（类）作用域中是不可见的。

C++标准规定：如果友元函数所在的类属于ADL的关联类集合，那么我们在这个外围类是可以找到该友元声明的。

## 9.2.3 插入式类名称

如果在类本身的作用域中插入该类的名称，我们就称该名称为插入式类名称。



## 9.3 解析模板

### 9.3.1 非模板中的上下文相关性

maximum munch扫描原则：C++实现应该让一个标记具有尽可能多的字符。

### 9.3.2 依赖型类型名称

模板名称不能有效地确定，尤其是模板中不能引用其它模板的名称，因为其它模板的内容可能会由于显式特化而使原来的名称失效。

依赖型受限名称并不会代表一个类型，除非在该名称的前面有关键字typename前缀。

当类型名称具有以下性质时，就应该在该名称前面添加typename前缀：

1. 名称出现在一个模板中。
2. 名称是受限的。
3. 名称不是用于指定基类继承的列表中，也不是位于引入构造函数的成员初始化列表中。
4. 名称依赖于模板参数。

### 9.3.3 依赖型模板名称

如果限定符号前面的名称（或者表达式）的类型要依赖于某个模板参数，并且紧接着在限定符后面的是一个tempalte-id（就是指一个后面带有尖括号内部实参列表的模板名称），那么就应该使用关键字typename。

```c++
template <typename T>
class Shell {
public:
    template <int N>
    class In {
    public:
        template<int M>
        class Deep{
        public:
            virtual void f();
        };
    };
};

template<typename T, int N>
class Weird {
public:
    void case1(typename Shell<T>::template In<N>::template Deep<N>* p) {
        p->template Deep<6>::f(); // 抑制virtual call
    }
    void case2(typename Shell<T>::template In<N>::template Deep<N>& p) {
        p.template Deep<8>::f(); // 同上，且Deep<8>并不要求依赖于模板参数N
    }
};
```

### 9.3.4 using-declaration中的依赖型名称

从类中引入名称的using-declaration的能力是很有限的：只能把基类中的名称引入到派生类中。

使用using-declaration的漏洞：

```c++
template <typename T>
class BXT {
    public:
        typedef T Mystery;

        template<typename U>
        struct Magic;
};
```

### 9.3.5 ADL和显式模板实参

```c++
template <typename T>
class DXTT : private BXT<T> {
    public:
        using BXT<T>::Mystery;      // 不必再写typename了
        using BXT<T>::Magic;        // 统一了using-declaration写法
        typename BXT<T>::Mystery m; // 使用typename很合情理，BXT<T>是依赖名称
        typename BXT<T>::template Magic<T> *plink; // 用::template显式的表示Magic是一个模板
};
```



## 9.4 派生和类模板

### 9.4.1 非依赖型基类

非依赖型基类：无需知道模板实参就可以完全确定类型的基类。

```c++
template <typename X>
class Base {
    public:
        int basefield;
        typedef int T;
};

template <typename T>
class D2 : public Base<double> {
    public:
        void f() {
            basefield = 7;
        }
        T strange; // 永远都是Base<double>::T即int类型
};

int main() {
    D2<char> d;
    cout << typeid(d.strange).name() << endl; // 永远输出int类型
}
```

### 9.4.2 依赖型基类

C++标准规定：对于模板中的非依赖型名称，将会在看到的第一时间进行查找。

标准C++声明：非依赖型名称不会在依赖型基类中进行查找（但仍然是在看到的时候马上进行查找）。

依赖型名称只有在实例化时才会进行查找。



## 9.5 本章后记


