# c++ 常见bug
## c++ 不允许内部类前置声明
```c++
class B; // 错误
class A {
    public:
        int64_t Age;
        class B {};
};

class A {
    public:
        class B: // 正确
        int64_t Age;
        class B {};
}
```