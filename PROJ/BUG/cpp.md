[TOC]

# c++ 常见bug



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

  用命令`ldconfig`来更新环境依赖；
