# circular_buffer
circular_buffer位于名字空间boost,需要包含的头文件如下:
```c++
#include <boost/circular_buffer.hpp>
using namespace boost;
```

## 类摘要
```c++
template <class T, class Alloc>
class circular_buffer
{
public:
    explicit circular_buffer();                     // 构造函数
    explicit circular_buffer(capacity_type capacity);
    circular_buffer(size_type n, const_reference item);
    circular_buffer(InputIterator first, InputIterator last);
    ~circular_buffer();

    iterator    begin();                            // 迭代器操作
    iterator    end();
    reference   operator[](size_type index);        // 操作符重载
    reference   at(size_type index);
    reference   front();                            // 访问元素
    reference   back();

    size_type   size() const;                       // 容量操作
    size_type   max_size() const;
    bool        empty() const;
    bool        full() const;

    pointer     linearize();                        // 线性化
    void        rotate(const_iterator new_begin);   // 旋转容器
    void        assign(size_type n, const_reference item);
    void        push_back(const_reference item = value_type());
    void        push_front(const_reference item = value_type());
    void        pop_back();
    void        pop_front();
    iterator    insert(iterator pos, const_reference item);
    iterator    erase(iterator pos);
};
```

## 用法
```c++
circular_buffer<int> cb(5);
assert(cb.empty());

cb.push_back(1);
cb.push_front(2);
assert(cb.front() == 2);
cb.insert(cb.begin(), 3);

// 可以使用迭代器遍历容器
for (auto pos = cb.begin(); pos != cb.end(); ++pos)
{ cout << * pos << ","; }
cout << endl;

cb.pop_front();
assert(cb.size() == 2);
cb.push_back();
assert(cb[0] = 2);

// circular_buffer还重载了比较操作符，可以对2个同样大小的对象进行字典序比较:
using namespace boost::assign;
circular_buffer<int> cb1 = (list_of(1), 2, 3);
circular_buffer<int> cb2 = (list_of(3), 4, 5);
circular_buffer<int> cb3 = cb1;

assert(cb1 < cb2);  // 比较操作
assert(cb1 == cb3);
```

## 环形结构
```c++
template<typename T>
void print(T& cb)
{
    for (auto& x: cb)
    { cout << x << ","; }
    cout << endl;
}
```
下面的代码声明了一个大小为3的circular_buffer,使用print()来输出循环缓冲区内部元素的变化情况:
```c++
using namespace boost::assign;

// circular_buffer可以使用assign库初始化
circular_buffer<int> cb = (list_of(1), 2, 3);
print(cb);

cb.push_back(4);
print(cb);

cb.push_bck(5);
print(cb);

cb.pop_front();
print(cb);
```
circular_buffer为这种环形结构提供了以下几个特殊的操作函数:
- full()            判断缓冲区是否已满。
- linearize()       可以把缓冲区线性化成一个连续的普通数组。
- is_linearized()   检测缓冲区是否已经线性化。
- rotate()          从指定的迭代器位置旋转整个缓冲区。
例:
```c++
using namespace boost::assign;
circular_buffer<int> cb = (list_of(1), 2, 3, 4, 5);

assert(cb.full());
print(cb);

int *p = cb.linearize(); // 已经线性化

cb.rotate(cb.begin() + 2);
print(cb);
```
*在使用circular_buffer时需要注意一点:虽然circular_buffer的内部存储是循环的，但它的迭代器不是循环的，其迭代器仅在begin()和end()区间有效，超过这个区间迭代器就会失效。*
例:
```c++
using namespace boost::assign;
circular_buffer<int> cb = (list_of(0), 1, 2, 3, 4, 5, 6, 7, 8, 9);

auto pos = cb.begin();
assert( *(pos + 3) == 3 );      // 正常
cout << *(pos + 10) << endl;    // 迭代器失效，引发断言异常
```

## 空间优化
circular_buffer在创建时一次性分配所需的内存，这是标准容器的通常做法，但对于循环缓冲区数据结构，这种做法不一定最合适。因此，circular_buffer库还提供了一个circular_buffer_space_optimized类，它是circular_buffer的适配器，只有在确实需要时才分配内存空间，