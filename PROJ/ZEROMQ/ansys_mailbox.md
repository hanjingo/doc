# ZMQ源码分析-mailbox

[TOC]



## mutex_t

```c++
class mutex_t // 同步锁
{
  public:
    mutex_t () { InitializeCriticalSection (&_cs); }
    ~mutex_t () { DeleteCriticalSection (&_cs); }
    void lock () { EnterCriticalSection (&_cs); }   // 加锁（设置临界区为受限状态）
    bool try_lock () { return (TryEnterCriticalSection (&_cs)) ? true : false; }
    void unlock () { LeaveCriticalSection (&_cs); } // 解锁
    CRITICAL_SECTION *get_cs () { return &_cs; }    // 返回临界区
  private:
    CRITICAL_SECTION _cs; // 临界区
    ZMQ_NON_COPYABLE_NOR_MOVABLE (mutex_t)
};
```



## atomic_ptr_t

```c++
// 原子锁
template <typename T> class atomic_ptr_t
{
  public:
    ...
    void set (T *ptr_) ZMQ_NOEXCEPT { _ptr = ptr_; } // 设置指针指向的对象（非原子操作）
    T *xchg (T *val_) ZMQ_NOEXCEPT                   // 设置指针指向对象的值（原子操作）
    T *cas (T *cmp_, T *val_) ZMQ_NOEXCEPT           // 比较并交换，相等即赋值（原子操作）
    ...
};
```



## signaler_t

信号机（signaler_t）用于在两个线程之间传递信号，容量为1（即同一时间信号机内最多只能有1个信号）.

```c++
```





## ypipe_t

```c++
template <typename T, int N> class ypipe_t ZMQ_FINAL : public ypipe_base_t<T>
{
public:
    ypipe_t () {...}
    void write (const T &value_, bool incomplete_) {...} // 写数据
    bool flush () {...}         // 刷入数据
    bool check_read () {...}    // 检查是否可读
    bool read (T *value_) {...} // 读数据
protected:
    yqueue_t<T, N> _queue; // 线程安全的链表（存放数据）
    T *_w;                 // 指向第一个未刷新的元素（只被写线程使用）
    T *_r;                 // 指向第一个还没预提取的元素（只被读线程使用）
    T *_f;                 // 指向下一轮要被刷新的一批元素中的第一个
    atomic_ptr_t<T> _c;    // 指向每一轮刷新的起点（读写线程共享）

    ZMQ_NON_COPYABLE_NOR_MOVABLE (ypipe_t)
}
```

### ypipe_base_t

```c++
template <typename T> class ypipe_base_t
{
  public:
    virtual ~ypipe_base_t () ZMQ_DEFAULT;
    virtual void write (const T &value_, bool incomplete_) = 0;
    virtual bool unwrite (T *value_) = 0;
    virtual bool flush () = 0;
    virtual bool check_read () = 0;
    virtual bool read (T *value_) = 0;
    virtual bool probe (bool (*fn_) (const T &)) = 0;
};
```



## yqueue_t

```c++
// 线程安全的链表
template <typename T, int N> class yqueue_t
{
public:
    inline T &front () { return _begin_chunk->values[_begin_pos]; } // 返回第一个元素的引用
    inline T &back () { return _back_chunk->values[_back_pos]; }    // 返回最后一个元素的引用
    inline void push () {...}   // 添加元素到链表尾
    inline void unpush () {...} // 回滚操作
    inline void pop () {...}    // 弹出头结点

private:
    struct chunk_t
    {
        T values[N];
        chunk_t *prev;
        chunk_t *next;
    };

    static inline chunk_t *allocate_chunk () {...}
    chunk_t *_begin_chunk; // 头结点
    int _begin_pos;
    chunk_t *_back_chunk;  // 尾结点
    int _back_pos;
    chunk_t *_end_chunk;   // 尾边界
    int _end_pos;

    atomic_ptr_t<chunk_t> _spare_chunk; // 最近出队的块（空闲块）

    ZMQ_NON_COPYABLE_NOR_MOVABLE (yqueue_t)
}
```



## mailbox

```c++
class mailbox_t ZMQ_FINAL : public i_mailbox
{
  public:
    mailbox_t ();
    ~mailbox_t ();

    fd_t get_fd () const;
    void send (const command_t &cmd_);
    int recv (command_t *cmd_, int timeout_);

    bool valid () const;

#ifdef HAVE_FORK
    void forked () ZMQ_FINAL { _signaler.forked (); }
#endif

  private:
    typedef ypipe_t<command_t, command_pipe_granularity> cpipe_t;
    cpipe_t _cpipe;       // 管道（无锁队列）
    signaler_t _signaler; // 发送端通知接收端
    mutex_t _sync;        // 用于保护一读（线程）多写（线程）模型数据
    bool _active;         // 管道中是否有命令可读

    ZMQ_NON_COPYABLE_NOR_MOVABLE (mailbox_t)
};
```

### i_mailbox

```c++
class i_mailbox // 邮箱接口类
{
  public:
    virtual ~i_mailbox () ZMQ_DEFAULT;

    virtual void send (const command_t &cmd_) = 0;
    virtual int recv (command_t *cmd_, int timeout_) = 0;

#ifdef HAVE_FORK
    virtual void forked () = 0;
#endif
};
```





## 参考

- [zeromq源码分析笔记之线程间收发命令（2） ](https://www.cnblogs.com/zengzy/p/5132437.html)

- [zeromq源码分析笔记之无锁队列ypipe_t（3）](https://www.cnblogs.com/zengzy/p/5134568.html)
