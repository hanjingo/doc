# 第十章 使用数值，时间和复数

[TOC]



## 10.1 数值计算



## 10.2 数值算法

### 10.2.1 保存序列中的增量值

```c++
// 使用iota生成一个有连续的浮点值元素的vector容器
std::vector<double> data(9);
double initial{-4};
std::iota(std::begin(data), std::end(data), inital); // -4.0 -3.0 -2.0 -1.0 0.0 1.0 2.0 3.0 4.0
std::copy(std::begin(data), std::end(data),
          std::osream_iterator<double>{
              std::cout << std::fixed << std::setprecision(1), " "
          });
std::cout << std::endl; 
```

```c++
// 使用非整数作为iota的初始值
std::iota(std::begin(data), std::end(data), -2.5); // -2.5 -1.5 -0.5 0.5 1.5 2.5 3.5 4.5 5.5
```

```c++
// 将iota应用到任意类型的序列上（只要它有自增运算符）
string text{"This is text"};
std::iota(std::begin(text), std::end(text), 'K'); // KLMNOPQRSTUV
```

### 10.2.2 求序列的和

```c++
// 使用accumulate和自定义方法求和
std::vector<int> values{2, 0, 12, 3, 5, 0, 2, 7, 0, 8};
int min{3};
auto sum = std::accumulate(std::begin(values), std::end(values), 0,
                           [min](int sum, int v){
                               if (v < min)
                                   return sum;
                               return sum + v;
                           });
std::cout << "The sum of the elements greater than " << min - 1
          << " is " << sum << std::endl;
```

```c++
// 生成元素的乘积
std::vector<int> values{2, 3, 5, 7, 11, 13};
auto product = std::accumulate(std::begin(values), std::end(values), 1
                               std::multiplies<int>()); // 30030
```

```c++
// 将accumulate应用到string对象的序列上
std::vector<string> numbers{"one", "two", "three", "five", 
                            "six", "seven", "eight", "nine", "ten"};
auto s = std::accumulate(std::begin(numbers), std::end(numbers), string{}, 
                         [](string& str, string& element){
                             if (element[0] == 't')
                                 return str + ' ' + element;
                             return str;
                         }); // " two three ten"
```

```c++
// 将accumulate应用到int对象的序列上
std::vector<int> numbers{1, 2, 3, 10, 11, 12};
auto s = std::accumulate(std::begin(numbers), std::end(numbers), string{"The numbers are"}, 
                         [](string& str, int n){
                             return str + ":" + std::to_string(n);
                         });
std::cout << s << std::endl;
```

### 10.2.3 内积

两个vector的内积是对应元素的乘积之和；两个矩阵的乘积是一个矩阵。

![10_1](res/10_1.png)

*矩阵乘法和内积运算*

```c++
// 使用inner_product计算vector的内积
std::vector<int> v1(10);
std::vector<int> v2(10);
std::iota(std::begin(v1), std::end(v1), 2); // [2, 3, 4, 5, 6, 7, 8, 9,  10, 11]
std::iota(std::begin(v2), std::end(v2), 3); // [3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
std::cout << std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 0)
          << std::endl;
```

```c++
// 不同类型对inner_product精度的影响
std::vector<double> data{0.5, 0.75, 0.85}
auto result1 = std::inner_product(std::begin(data), std::end(data), std::begin(data), 0);   // 0
double result2 = std::inner_product(std::begin(data), std::end(data), std::begin(data), 0); // 0
auto result3 = std::inner_product(std::begin(data), std::end(data), std::begin(data), 0.0); // 1.535
std::cout << result << " " << result2 << " " << result3 << std::endl;
```

1. 应用内积

   给定$n$个点$(x_i, y_i)$，求解下面的等式：

   $nb + a\sum x_i = \sum y_i$

   $b\sum x_i + a \sum x_i^2 = \sum x_i y_i$

   解出等式的系数$a$和$b$：

   $a = \frac{\sum{x_i y_i} - \sum{x_i} \sum{y_i}}{n\sum{x_i^2} - (\sum{x_i})^2}$

   $b = \mu_y - a\mu_x$

   变量$x$的$n$个值的平均值$\mu$的等式为：

   $\mu_x = \frac{\sum x_i}{n}$

   ```c++
   // Ex10_01.cpp
   #include <numeric>
   #include <vector>
   #include <iostream>
   #include <iomanip>
   #include <fstream>
   #include <iterator>
   #include <string>
   using std::string;
   
   int main()
   {
       // File contains country_name renewables_per_person kwh_cost
       string file_in{"007.txt"};
       std::ifstream in{file_in};
       
       if (!in)
       {
           std::cerr << file_in << " not open." << std::endl;
           exit(1);
       }
       
       std::vector<double> x;
       std::vector<double> y;
       
       std::count << " Country " << " Watts per Head " << " kwh cost(cents) "
                  << std::endl;
       while(true)
       {
           string country;
           double renewables{};
           double kwh_cost{};
           
           if ((in >> country).eof()) break;
           in >> renewables >> kwh_cost;
           x.push_back(renewables);
           y.push_back(kwh_cost);
           std::cout << std::left << std::setw(12) << country << std::right 
                     << std::fixed << std::setprecision(2) << std::setw(12)
                     << renewables << std::setw(16) << kwh_cost << std::endl;
       }
       auto n = x.size();
       auto sx = std::accumulate(std::begin(x), std::end(x), 0.0);
       auto sy = std::accumulate(std::begin(y), std::end(y), 0.0);
       auto mean_x = sx/n;
       auto mean_y = sy/n;
       
       // Sum of x*y values and sum of x-squared
       auto sxy = std::inner_product(std::begin(x), std::end(x), std::begin(y), 0.0);
       auto sx_2 = std::inner_product(std::begin(x), std::end(x), std::begin(x), 0.0);
       
       double a{}, b{};
       auto num = n * sxy - sx * sy;
       auto denom = n * sx_2 - sx * sx;
       a = num / denom;
       b = men_y - a * mean_x;
       std::cout << std::fixed << std::setprecision(3) << "\ny = "
                 << a << "*x + " << b << std::endl;
   }
   ```

   ![10_2](res/10_2.png)
   
   *最小二乘线性回归的结果*
   
2. 定义内积运算

   ```c++
   // 生成和的积而不是积的和
   std::vector<int> v1(5);
   std::vector<int> v2(5);
   std::iota(std::begin(v1), std::end(v1), 2); // 2, 3, 4, 5, 6
   std::iota(std::begin(v2), std::end(v2), 3); // 3, 4, 5, 6, 7
   std::cout << std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 1, 
                                   std::multiplies<>(), std::plus<>())
             << std::endl;
   ```

### 10.2.4 相邻差

```c++
// 使用adjacent_difference计算输入序列中相邻元素对的差
std::vector<int> data{2, 3, 5, 7, 11, 13, 17, 19};
std::cout << "Differences: ";
std::adjacent_difference(std::begin(data), std::end(data), 
                         std::ostream_iterator<int>{ std::cout, " " });
std::cout << std::endl; // 2 1 2 2 4 2 4 2
```

```c++
// 使用adjacent_difference和自定义减法运算，计算输入序列中相邻元素对的差
std::vector<int> data{2, 3, 5, 7, 11, 13, 17, 19};
std::cout << "Differences: ";
std::adjacent_difference(std::begin(data), std::end(data), 
                         std::ostream_iterator<int>{ std::cout, " " },
                         std::multiplies<>());
std::cout << std::endl; // 2 6 15 35 77 143 221 323
```

```c++
// 使用adjacent_difference和plus来计算Fibonacci数列
std::vector<size_t> fib(15, 1);
std::adjacent_difference(std::begin(fib), std::end(fib) - 1, std::begin(fib) + 1, 
                         std::plus<size_t>());
std::copy(std::begin(fib), std::end(fib), 
          std::ostream_iterator<size_t>{ std::cout, " " });
std::cout << std::endl; // 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610
```

### 10.2.5 部分和

```c++
// 使用partial_sum计算输入序列中元素的部分和
std::vector<int> data{2, 3, 5, 7, 11, 13, 17, 19};
std::cout << "Partial sums: ";
std::partial_sum(std::begin(data), std::end(data), 
                 std::ostream_iterator<int>{std::cout, " "});
std::cout << std::endl;
```

```c++
// 使用partial_sum和minus计算部分减法和
std::vector<int> data{2, 3, 5, 7, 11, 13, 17, 19};
std::cout << "Partial sums: ";
std::partial_sum(std::begin(data), std::end(data),
                 std::ostream_iterator<int>{std::cout, " "}, std::minus<int>());
std::cout << std::endl; // 2 -1 -6 -13 -24 -37 -54 -73
```

### 10.2.6 极大值和极小值

```c++
// 使用min_element返回最小元素的迭代器
// 使用max_element返回最大元素的迭代器
// 使用minmax_element返回最小，最大元素的迭代器
std::vector<int> data{2, 12, 3, 5, 17, -11, 113, 117, 19};
std::cout << "From values ";
std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{std::cout, " "});
std::cout << "\n Min = " << *std::min_element(std::begin(data), std::end(data))
          << " Max = " << *std::max_element(std::begin(data), std::end(data))
          << std::endl;

auto start_iter = std::begin(data) + 2;
auto end_iter = std::end(data) - 2;
auto pr = std::minmax_element(start_iter, end_iter);

std::cout << "From values ";
std::copy(start_iter, end_iter, std::ostream_iterator<int>{std::cout, " "});
std::cout << "\n Min = " << *pr.first << " Max = " << *pr.second << std::endl;
```

```c++
// 将min, max, minmax用于初始化列表
auto words = {string{"one"}, string{"two"}, string{"three"}, string{"four"}, string{"five"},
              string{"six"}, string{"seven"}, string{"eight"}};
std::cout << "Min = " << std::min(words) << std::endl;
auto pr = std::minmax(words, [](const string& s1, const string& s2){
    return s1.back() < s2.back(); });
std::cout << "Min = " << pr.first << " Max = " << pr.second << std::endl;
```



## 10.3 保存和处理数值

valarray类模板定义了保存和操作数值序列的对象的类型，用来处理整数和浮点数，保存类类型的对象，需要满足以下条件：

- 类不能是抽象的。
- public构造函数必须包含默认的构造函数和拷贝构造函数。
- 析构函数必须是public。
- 类必须定义赋值运算符，而且必须是public。
- 类不能重载operator&()。
- 成员函数不能抛出异常。

不能保存引用或valarray中用const, volatile修饰的对象。

```c++
// 生成一个valarray对象
std::valarray<int> numbers(15);
std::valarray<size_t> sizes{1, 2, 3};
std::valarray<size_t> copy_sizes{sizes};
std::valarray<double> values;
std::valarray<double> data(3.14, 10);
```

```c++
// 从普通数组得到的一定个数的值来初始化valarray对象
int vals[]{2, 4, 6, 8, 10, 12, 14};
std::valarray<int> vals1{vals, 5};     // 2 4 6 8 10
std::valarray<int> vals2{vals + 1, 4}; // 4 6 8 10
```

### 10.3.1 valarray对象的基本操作

```c++
// 改变valarray容器中元素个数
data.resize(50, 1.5);
```

```c++
// 交换两个valarray对象的元素
std::valarray<size_t> sizes_3{1, 2, 3};
std::valarray<size_t> sizes_4{2, 3, 4, 5};
sizes_3.swap(sizes_4);

std::swap(sizes_3, sizes_4); // 另一种方式
```

```c++
// 调用min和max来查找元素的的最小值和最大值
std::cout << "The elements are from " << sizes_4.min() << " to " << sizes_4.max() << '\n';
```

```c++
// 移位操作
std::valarray<int> d1{1, 2, 3, 4, 5, 6, 7, 8, 9};
auto d2 = d1.shift(2);
for (int n : d2) std::cout << n << ' ';
std::cout << '\n';      // 3 4 5 6 7 8 9 0 0
auto d3 = d1.shift(-3);
std::copy(std::begin(d3), std::end(d3), 
          std::ostream_iterator<int>{ std::cout, " " });
std::cout << std::endl; // 0 0 0 1 2 3 4 5 6
```

```c++
// 使用 = 为valarray对象赋值
d1 =d1.shift(2);
```

```c++
// 将元素序列循环移动
std::valarray<int> d1{1, 2, 3, 4, 5, 6, 7, 8, 9};
auto d2 = d1.cshift(2);  // 3 4 5 6 7 8 9 1 2
auto d3 = d1.cshift(-3); // 7 8 9 1 2 3 4 5 6 
```

apply()函数可以将一个函数应用到每个元素上，并返回一个新的valarray对象。valarray类模板中定义了两个函数模板：

```c++
valarray<T> apply(T func(T)) const;
valarray<T> apply(T func(const T&)) const;
```

**使用apply注意事项:**

1. 所有版本都是const，所以函数不能修改原始元素。
2. 参数是一个有特定形式的函数，这个函数以T类型或T的const引用为参数，并返回T类型的值；如果apply()使用的参数不符合这些条件，将无法通过编译。
3. 返回值是`valarray<T>`类型，因此返回值总是一个和原序列相同类型和大小的数组。

```c++
// apply示例
std::valarray<double> time{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
auto distances = time.apply([](double t){
  const static double g{32.0};
  return 0.5 * g * t * t;
}); // 0 16 64 144 256 400 576 784 1024 1296
```

```c++
// Ex10_02.cpp
#include <numeric>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <valarray>
const static double g{32.0};

int main()
{
	double height{};
  std::cout << "Enter the approximate height of the building in feet: ";
  std::cin >> height;
  // Calculate brick flight time in seconds
  double end_time{std::sqrt(2 * height / g)};
  size_t max_time{1 + static_cast<size_t>(end_time + 0.5)};
  
  std::valarray<double> times(max_time + 1);
  std::iota(std::begin(times), std::end(times), 0);
  *(std::end(times) - 1) = end_time;
  
  // Calculate distances each second
  auto distances = times.apply([](double t){ return 0.5 * g * t * t; });
  
  // Calculate speed each second
  auto v_fps = sqrt(distances.apply([](double d){ return 2 * g * d; }));
  
  // Lambda expression to output results
  auto print = [](double v){ std::cout << std::setw(6) << static_cast<int>(std::round(v)); };
  
  // Output the times - the last is a special case...
  std::cout << "Time (seconds): ";
  std::for_each(std::begin(times), std::end(times) - 1, print);
  std::cout << std::setw(6) << std::fixed << std::setprecision(2) << *(std::end(times) - 1);
  std::cout << "\nDistances(feet):";
  std::for_each(std::begin(distances), std::end(distances), print);
  
  std::cout << "\nVelocity(fps): ";
  std::for_each(std::begin(v_fps), std::end(v_fps), print);
  
  // Get velocities in mph and output them
  auto v_mph = v_fps.apply([](double v){ return v * 60 / 88; });
  std::cout << "\nVelocity(mph): ";
  std::for_each(std::begin(v_mph), std::end(v_mph), print);
  std::cout << std::endl;
}
```

### 10.3.2 一元运算符

```c++
// !运算符
std::valarray<int> data{2, 0, -2, 4, -4};
auto result = !data;
std::copy(std::begin(result), std::end(result), 
          std::ostream_iterator<bool>{ std::cout << std::boolalpha, " "});
std::cout << std::endl; // false true false false false
```

```c++
// ~运算符
std::valarray<int> data{2, 0, -2, 4, -4};
auto result = ~data;
std::copy(std::begin(result), std::end(result), std::ostream_iterator<int>{std::cout, " "});
std::cout << std::endl; // -3 -1 1 -5 3
```

```c++
// +运算符
std::valarray<int> data{2, 0, -2, 4, -4};
auto result = -data;
std::copy(std::begin(result), std::end(result), std::ostream_iterator<int>{std::cout, " "});
std::cout << std::endl; // -2 0 2 -4 4
```

### 10.3.3 用于valarray对象的复合赋值运算符

- 复合算术赋值运算符`+=`, `-=`, `*=`, `/=`, `%=`

  ```c++
  valarray<int> v1{1, 2, 3, 4};
  valarray<int> v2{3, 4, 3, 4};
  v1 += 3;  // v1: 4 5 6 7
  v1 -= v2; // v1: 1 1 3 3
  ```

- 符合位操作赋值运算符`&=`, `|=`, `^=`

  ```c++
  valarray<int> v1{1, 2, 4, 8};
  valarray<int> v2{4, 8, 16, 32};
  v1 |= 4;  // v1: 5 6 4 12
  v1 &= v2; // v1: 4 0 0 0
  v1 ^= v2; // v1: 0 8 16 32
  ```

- 符合移位赋值运算符`>>=`, `<<=`

  ```c++
  valarray<int> v1{1, 2, 3, 4};
  valarray<int> v2{4, 8, 16, 32};
  v2 <<= v1; // v2: 8 32 128 512
  v2 >>= 2;  // v2: 2 8  32  128
  ```

### 10.3.4 valarray对象的二元运算

TODO
