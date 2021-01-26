# optional
std::optional可以接受对象或者nullopt(表示为空值)

例:
```c++
#include <iostream>
#include <optional>
using namespace std;

// pp用来存放int的对象，初始化为1，判断pp是否包含值，可以输出1，
// 将nullopt赋值后，判断时为false，自然也不会输出。
int main()
{
  std::optional<int> pp = 1;
  if (pp) {
      cout << *pp << endl; // 1
  }

  pp = nullopt;
  if (pp) {
      cout << *pp << endl; // 不输出
  }
}
```

另一种用法:
```c++
#include <iostream>
using namespace std;

optional<Some> 
getSome(const std::vector<Some>& svec, int i)
{
  auto iter = std::find_if(svec.begin(), svec.end(), [i](const Some& s) {
      return s.some_i_ == i;
  });

  if (iter != svec.end()) {
      return *iter;
  }

  return nullopt;
}

int main()
{
  vector<Some> someVec;
  someVec.push_back({1, "11"});
  auto s_ptr = getSome(someVec, 1);
  if (s_ptr) {
      cout << s_ptr->some_str_ << endl; // “11”
  }

  s_ptr = getSome(someVec, 2);
  if (s_ptr) {
      cout << s_ptr->some_str_ << endl; // 不输出
  }
  return 0;
}
```

## 创建optinal
有几种方式创建optional，我们具体看下例子：
- 直接创建或者用nullopt赋值
```c++
std::optional<int> empty;
std::optional<int> opt = std::nullopt;
```
- 使用对象初始化
```c++
std::optional<int> opt = 1;

struct Some
{
  int some_i_ = 0;
  std::string some_str_;
};
Some s;
std::optional<Some> opt = s;
```
- 使用 std::make_optional构造,类似std::make_shared可以传递参数原地构造optional包含的对象
```c++
struct Some
{
  Some(int i, std::string str):
          some_i_(i),
          some_str_(std::move(str)) {}

  int some_i_ = 0;
  std::string some_str_;
};
using namespace std;
optional<Some> opt = make_optional<Some>(1, "1");
auto opt = make_optional(1); // optional<int>
```
- 使用std::in_place构造：
其实使用std::in_place和使用std::make_optional 用法相近，都是原地构造对象，避免使用对象初始化进行的一次拷贝等。std::in_place只是一个tag，用来表示我们使用std::optional的那个构造函数。
optional的构造函数是这样：
```c++
//
template <class... _Args, class = enable_if_t<
      is_constructible_v<value_type, _Args...>>>
constexpr explicit 
optional(in_place_t, _Args&&... __args)
      : __base(in_place, _VSTD::forward<_Args>(__args)...) {}

//
template <class _Up, class... _Args, class = enable_if_t<
      is_constructible_v<value_type, initializer_list<_Up>&, _Args...>>>
constexpr explicit 
optional(in_place_t, initializer_list<_Up> __il, _Args&&... __args)
      : __base(in_place, __il, _VSTD::forward<_Args>(__args)...) {}
```

## 和指针比较
- 如果我们和普通的指针相比，即用指针指向对象，如果为空的时候使用nullptr来代替，对于我们第一个例子可以达到相似的效果，因为我们的vector的生命周期时在使用指针之后销毁，因为指针只是简单指向，对于指向已经析构的对象，无疑是一场灾难。
- 如果和我们智能指针比较，例如第一个例子中，第一种实现我们需要vector存放shared_ptr才能进行拷贝：
```c++
shared_ptr<Some> getSome(
    const vector<shared_ptr<Some>>& svec, 
    int i)
{
    auto iter = std::find_if(svec.begin(), svec.end(), [i](const Some& s) {
        return s.some_i_ == i;
    });

    if (iter != svec.end()) {
        return *iter;
    }

    return nullptr;
}
```