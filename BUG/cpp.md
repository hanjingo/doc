# c++ 常见bug



## c++不允许内部类前置声明

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



## 动态链接库链接不上

如果make老是编译不过，用ldd命令查看缺少一些动态链接库；但是在/usr/local/lib或其他目录里面又能找到这些动态链接库，可以试试以下命令来更新下环境:

```sh
ldconfig
```
