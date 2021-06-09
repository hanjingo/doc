# 第九章 高级线程管理



## 线程池

### 最简单的线程池

拥有固定数量的工作线程的简单线程池，例：

```c++
class thread_pool
{
    std::atomic_bool done;
    thread_safe_queue<std::function<void()> > work_queue; // 线程安全队列
    std::vector<std::thread> threads; // 工作线程
    join_thread joiner; // 用来汇聚所有线程
    
    void worker_thread()
    {
        while(!done) // 4
        {
            std::function<void()> task;
            if (work_queue.try_pop(task)) // 获取任务
            {
                task(); // 执行任务
            }
            else
            {
                std::this_thread::yield(); //没有任务，线程休息
            }
        }
    }
public:
    thread_pool() : done(false), joiner(threads)
    {
        unsigned const thread_count = std::thread::hardware_concurrency(); // 获得硬件支持的并发线程数
        try
        {
            for (unsigned i = 0; i < thread_count; ++i)
            {
                threads.push_bask(std::thread(&thread_pool::worker_thread, this)); // 执行
            }
        }
        catch(...)
        {
            done = true; // 标记运行结束
            throw;
        }
    }
    
    ~thread_pool()
    {
        done = true;
    }
    
    template<typename FunctionType>
    void submit(FunctionType f)
    {
        work_queue.push(std::function<void()>(f)); // 入队
    }
};
```

### 等待提交到线程池中的任务

可等待任务的线程池，例：

```c++
class function_wrapper
{
    struct impl_base {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };
    
    std::unique_ptr<impl_base> impl;
    template<typename F>
    struct impl_type : impl_base
    {
        F f;
        impl_type(F&& f_) : f(std::move(f_)) {}
        void call() { f(); }
    };
public:
    template<typename F>
    function_wrapper(F&& f) : impl(new impl_type<F>(std::move(f))) {}
    void operator()() { impl->call(); }
    function_wrapper() = default;
    function_wrapper() = default;
    function_wrapper(function_wrapper&& other) : impl(std::move(other.impl)) {}
    function_wrapper& operator=(function_wrapper&& other)
    {
        impl = std::move(other.impl);
        return *this;
    }
    
    function_wrapper(const function_wrapper&) = delete;
    function_wrapper(function_wrapper&) = delete;
    function_wrapper& operator=(const function_wrapper&) = delete;
};

class thread_pool
{
    thread_safe_queue<function_wrapper> work_queue;
    void worker_thread()
    {
        while(!done)
        {
            function_wrapper task;
            if(work_queue.try_pop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }
public:
    template<typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f) // 1
    {
        typedef typename std::result_of<FunctionType()>::type result_type; // 2
        
        std::packaged_task<result_type()> task(std::move(f)); // 3
        std::future<result_type> res(task.get_future()); // 4
        work_queue.push(std::move(task)); // 5
        return res; // 6
    }
}
```

