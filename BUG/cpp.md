# c++ 常见bug

[TOC]



## c++不允许内部类在类外前置声明

### 问题描述

c++不允许内部类在类外前置声明：

```c++
class B; // 错误
class A {
    public:
        int64_t Age;
        class B {};
};
```

### 解决办法

- 方法一

  只能放到类的内部进行前置声明：

  ```c++
  class A {
      public:
          class B: // 正确
          int64_t Age;
          class B {};
  };
  ```

  

## 动态链接库链接不上

### 问题描述

如果`make`老是编译不过，用`ldd`命令查看缺少一些动态链接库；但是在`/usr/local/lib`或其他目录里面又能找到这些动态链接库；

### 解决方法

- 方法一

  在linux下用命令`ldconfig`来更新环境依赖；
  
  在macos下用命令`update_dyld_shared_cache`来更新环境以来



## Lambda引用捕获的悬挂引用问题

### 问题描述

Lambda引用捕获局部变量时，由于离开作用域导致局部变量释放，从而导致“悬挂引用”问题。

```c++
std::function<void()> f()
{
    int a = 1;
    auto bak = [&](){
        a++;
        std::cout << a << std::endl;
    };
    return bak;
}
int main()
{
    auto bak = f();
    bak();
}
```

### 解决方法

- 方法一

  禁用引用捕获局部变量。

  
  
## 模板类函数

### 问题描述

TODO
