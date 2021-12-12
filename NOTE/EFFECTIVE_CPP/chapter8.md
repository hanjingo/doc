# 8 Customizing new and delete

[TOC]

## 条款49 了解new-handler的行为

一个设计良好的new-handler函数具备以下特征：

- 让更多内存可被使用；
- 安装另一个new-handler；
- 卸除new-handler；
- 抛出bad_alloc（或派生自bad_alloc）的异常；
- 不返回；

通用new-handler模版；例：

```c++
template<typename T>
class NewHandlerSupport {
public:
    static std::new_handler set_new_handler(std::new_handler p) throw();
    static void* operator new(std::size_t size) throw(std::bad_alloc);
private:
    static std::new_handler currentHandler;
};

template<typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
{
    std::new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}

template<typename T>
void* NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc)
{
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new(size);
}

// 以下将每一个currentHandler初始化为null
template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = 0;
```

总结：

- set_new_handler允许客户指定一个函数，在内存分配无法获得满足时被调用；
- Nothrow new是一个颇为局限的工具，因为它只适用于内存分配，后继的构造函数调用还是可能抛出异常；


## 条款50 了解new和delete的合理替换时机

替换编译器的operator new和operator delete的理由：

- 用来检测运用上的错误（主要是内存泄漏）
- 为了收集动态分配内存之使用统计信息
- 为了增加分配和归还的速度
- 为了降低缺省内存管理器带来的空间额外开销
- 为了弥补缺省分配器中的非最佳齐位（suboptimal alignment）
- 为了将相关对象成簇集中
- 为了获得非传统的行为

总结：

- 有许多理由需要写个自定的new和delete，包括改善性能，对heap运用错误进行调试，手机heap使用信息；


## 条款51 编写new和delete时需固守常规

C++保证删除null指针永远安全；例：

```c++
class Base {
public:
    static void* operator new(std::size_t size) throw(std::bad_alloc);
    static void operator delete(void* rawMemory, std::size_t size) throw();
};
void* Base::operator new(std::size_t size) throw(std::bad_alloc)
{
    if (size != sizeof(Base))
        return ::operator new(size);
}
void Base::operator delete(void* rawMemory, std::size_t size) throw()
{
    if (rawMemory == 0) return; // 检查null指针
    if（size != sizeof(Base)）{
        ::operator delete(rawMemory);
        return;
    }
    return;
}
```

总结：

- operator new应该内含一个无穷循环，并在其中尝试分配内存，如果它无法满足内存需求，就该调用new-handler；它也应该有能力处理0bytes申请；class专属版本则还应该处理“比正确大小更大的（错误）申请”；
- operator delete应该在收到null指针时不做任何事，class专属版本则还应该处理“比正确大小更大的（错误）申请”；


## 条款52 写了placement new也要写placement delete

```c++
class StandardNewDeleteForms {
public:
    // normal new/delte
    static void* operator new(std::size_t size) throw(std::bad_alloc) { return ::operator new(size); }
    static void oeprator delete(void* pMemory) throw() { ::operator delete(pMemory); }

    // placement new/delete
    static void* operator new(std::size_t size, void* ptr) throw() { return ::operator new(size, ptr); }
    static void operator delete(void* pMemory, void* ptr) throw() { return ::operator delete(pMemory, ptr); }

    // nothrow new/delete
    static void* operator new(std::size_t size, const std::nothrow_t& nt) throw() { return ::operator new(size, nt); }
    static void operator delete(void *pMemory, const std::nothrow_t&) throw() { ::operator delete(pMemory); }
};

class Widget: public StandardNewDeleteForms {
public:
    using StandardNewDeleteForms::operator new;
    using StandardNewDeleteForms::operator delete;
    static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc); // 添加一个自定义的placement new
    static void operator delete(void* pMemory, std::ostream& logStream) throw(); // 添加一个placement delete
};
```

总结：

- 当你写一个placement operator new，请确定也写出对应的placement operator delete；如果没有这样做，你的程序可能会发生隐晦而时断时续的内存泄漏；
- 当你声明placement new和placement delete，请确定不要无意识（非故意）地遮掩了他们的正常版本；
