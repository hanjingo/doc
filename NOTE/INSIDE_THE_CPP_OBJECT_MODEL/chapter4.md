# 第四章 function语意学

## Nonstatic Member Functions(非静态成员函数)

准则：非静态成员函数至少和一般的非成员函数有相同的效率。编译器内部已经将成员函数转化为非成员函数。

转化流程：

1. 添加this指针作为函数的第一个参数，如果成员函数是const,那么this指针的类型为:`const className* const`；并且对每一个`nonstatic data member`的存取改经由this指针来存取。

2. 函数名处理,"name mangling"，函数名称+参数链表+参数类型的形式进行重新编码命名，使其成为一个独一无二的名称。

3. "NRV"优化，`Name Return Value`，如果有返回值的话，添加一个引用类型的参数来代替返回值。

例：

```c++
Point setPoint(const Point& point);
```

可能会被转化成:

```c++
void setPoint_crefpoint(const Point* this, const Point& point, Point& __result);
```



## Virtual Member Functions(虚成员函数)

`virtual function`一般实现模型：每一个class都有且仅有一个virtual table(虚表)，内含虚函数的地址，每个Object都有一个vptr(虚表指针)指向虚表所在。

例：假设normalize()是Point的一个虚函数，ptr是Point类型的指针，那么`ptr->normalize()`在内部转换为：`(*ptr->vptr[1])(ptr);`;

1是`virtual table slot`的索引值，关联到`normalize`函数，第二个ptr表示this指针。

执行期的额外信息来支持多态，对于每一个class object增加两个members(在编译期就确定了):
- 一个字符串或者数字来表示class的类型。
- 一个指针(vptr)指向持有程序的虚函数的执行期地址的表格（虚表）.

`virtual table`中的`active virtual function`包括:
- class本省定义的函数实例,重写了(overriding)了`base class virtual functions`;
- 继承自`base class`的函数实例
- `pure_virtual_called()`纯虚函数实例

### 单一继承的情况:

对于`base class Point`的声明如下:

```c++
class Point {
public:
    virtual ~Point();
    virtual Point& mult(float) = 0;
    float x() const { return _x; }
    virtual float y() const { return 0; }
}
```
