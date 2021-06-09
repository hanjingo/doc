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
    std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f) // 返回一个std::future<>保存任务的返回值
    {
        typedef typename std::result_of<FunctionType()>::type result_type; 
        
        std::packaged_task<result_type()> task(std::move(f)); // 包装函数f
        std::future<result_type> res(task.get_future());      // 异步获取future
        work_queue.push(std::move(task));                     // 任务入队 
        return res;                                           // 返回
    }
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	unsigned long const length = std::distance(first, last);

	if (!length)
			return init;

	unsigned long const block_size = 25;
	unsigned long const num_blocks = (length+block_size - 1)/block_size;
	
	std::vector<std::future<T> > futures(num_blocks - 1);
	thread_pool pool;

	Iterator block_start = frist;
	for (unsigned long i = 0; i < (num_blocks - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);
		futures[i] = pool.submit(accumulate_block<Iterator, T>());
		block_start = block_end;
	}
	T last_result = accumulate_block<Iterator, T>()(block_start, last);
	T result = init;
	for (unsigned long i = 0; i < (num_blocks - 1); ++i)
	{
			result += futures[i].get();
	}
	result += last_result;
	return result;
}
```

### 等待依赖任务

例，基于线程池的快速排序的实现：

```c++
tempalte <typename T>
struct sorter // 1
{
	thread_pool pool; // 2

	std::lsit<T> do_sort(std::list<T>& chunk_data)
	{
		if(chunk_data.empty())
		{
			return chunk_data;
		}

		std::list<T> result;
		result.splice(result.begin(), chunk_data, chunk_data.begin());
		T const& partition_value = *result.begin();

		typename std::list<T>::iterator divide_point = std::partition(
						chunk_data.begin(), chunk_data.end(),
						[&](T const& val){return val<partition_val>;});

		std::list<T> new_lower_chunk;
		new_lower_chunk.splice(new_lower_chunk.end(),
						       chunk_data, chunk_data.begin(),
							   divide_point);

		std::future<std::list<T> > new_lower = pool.submit(
						std::bind())
	}
}
```
