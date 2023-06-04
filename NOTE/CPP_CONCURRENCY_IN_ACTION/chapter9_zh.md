# 第九章 高级线程管理

[TOC]



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
						std::bind(&sorter::do_sort, this,
								  std::move(new_lower_chunk))); // 3

		std::list<T> new_higher(do_sort(chunk_data));

		result.splice(result.end(), new_higher);
		while(!new_lower.wait_for(std::chrono::seconds(0)) == std::future_status::timeout)
		{
		    pool.run_pending_task(); // 4
		}

		result.splice(result.begin(), new_lower.get());
		return result;
	}
};

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if(input.empty())
	{
        return input;
	}
	sorter<T> s;
	return s.do_sort(input);
}
```

### 避免队列中的任务竞争

线程池，线程具有本地任务队列：

```c++
class thread_pool
{
    thread_safe_queue<function_wrapper> pool_work_queue;

	typedef std::queue<function_wrapper> local_queue_type; // 1
	static thread_local std::unique_ptr<local_queue_type>
			local_work_queue; // 指向工作队列

	void worker_thread()
	{
        local_work_queue.reset(new local_queue_type); // 初始化指针
		while(!done)
		{
			run_pending_task();
		}
	}

public:
	template<typename FunctionType>
	std::future<typename std::result_of<FunctionType()>::type> submit(FuntionType f)
	{
		typedef typename std::result_of<FunctionType()>::type result_type;
		std::packaged_task<result_type()> task(f);
		std::future<result_type> res(task.get_future());
		if (local_work_queue) // 判断是否是一个工作队列
		{
			local_work_queue->push(std::move(task));
		}
		else
		{
			pool_work_queue.push(std::move(task)); // 将这个任务放在线程池中的全局对队列中
		}
		return res;
	}

	void run_pending_task()
	{
		function_wrapper task;
		if (local_work_queue && !local_work_queue->empty()) // 是否是本地任务队列
		{
			task = std::move(local_work_queue->front());
			local_work_queue->pop();
			task();
		}
		else if (pool_work_queue.try_pop(task)) // 从全局工作列表中获取任务
		{
			task();
		}
		else
		{
			std::this_thread::yield();
		}
	}
	// rest as before
}
```

### 窃取任务
基于锁的任务窃取队列，例:

```c++
class work_stealing_queue
{
private:
		typedef function_wrapper data_type;
		std::deque<data_type> the_queue;
		mutable std::mutex the_mutex;

public:
		work_stealing_queue() {}
		work_stealing_queue(const work_stealing_queue& other) = delete;
		work_stealing_queue& operator=(const work_stealing_queue& other)=delete;

		bool push(data_type data)
		{
			std::lock_guard<std::mutex> lock(the_mutex);
			return the_queue.empty();
		}

		bool try_pop(data_type& res) 
		{
			std::lock_guard<std::mutex> lock(the_mutex);
			if(the_queue.empty())
			{
				return false;
			}

			res = std::move(the_queue.front());
			the_queue.pop_front();
			return true;
		}

		bool try_steal(data_type& res) 
		{
			std::lock_guard<std::mutex> lock(the_mutex);
			if (the_queue.empty())
			{
				return false;
			}

			res = std::move(the_queue.back());
			the_queue.pop_back();
			return true;
		}
}

class thread_pool
{
	typedef function_wrapper task_type;
	std::atomic_bool done;
	thread_safe_queue<task_type> pool_work_queue;
	std::vector<std::unique_ptr<work_stealing_queue> > queues; // 1
	std::vector<std::thread> threads;
	join_threads joiner;

	static thread_local work_stealing_queue* local_work_queue; // 2
	static thread_local unsigned my_index;

	void worker_thread(unsigned my_index_)
	{
		my_index = my_index_;
		local_work_queue=queues[my_index].get(); // 3
		while(!done)
		{
			run_pending_task();
		}
	}

	bool pop_task_from_local_queue(task_type& task)
	{
		return local_work_queue && local_work_queue->try_pop(task);
	}

	bool pop_task_from_pool_queue(task_type& task) 
	{
		return pool_work_queue.try_pop(task);
	}

	bool pop_task_from_other_thread_queue(task_type& task) // 遍历池中所有线程的任务队列，然后尝试窃取任务。
	{
		for(unsigned i = 0; i < queues.size(); ++i)
		{
			unsigned const index=(my_index+i+1)%queues.size(); // 5
			if(queues[index]->try_steal(task))
			{
				return true;
			}
		}
		return false;
	}

public:
	thread_pool() : done(false), joiner(threads)
		{
			unsigned const thread_count = std::thread::hardware_concurrency();

			try
			{
				for(unsigned i = 0; i < thread_count; ++i)
				{
					queues.push_bask(std::unique_ptr<work_stealing_queue>(new work_stealing_queue)); // 创建一个属于自己的工作队列
					threads.push_back(std::thread(&thread_pool::worker_thread, this, i));
				}
			}
			catch(...)
			{
				done = true;
				throw;
			}
		}

		~thread_pool()
		{
			done = true;
		}

		template<typename FunctionType>
		std::future<typename std::result_of<FunctionType()>::type> submit FunctionType f)
		{
			typedef typename std::result_of<FunctionType()>::type result_type;
			std::packaged_task<result_type()> task(f);
			std::future<result_type> res(task.get_future());
			if(local_work_queue)
			{
				local_work_queue->push(std::move(task));
			}
			else
			{
				pool_work_queue.push(std::move(task));
			}
			return res;
		}

		void run_pending_task()
		{
			task_type task;
			if(pop_task_from_local_queue(task) || // 从线程的任务队列中取出一个任务来执行
				pop_task_from_pool_queue(task) || // 从线程池队列中获取一个任务
				pop_task_from_other_thread_queue(task)) // 从其他线程的队列中获取一个任务
			{
				task();
			}
			else
			{
				std::this_thread::yield();
			}
		}
};
```

## 中断线程
interrupt()函数,例：

```c++
class interruptible_thread
{
public:
	template<typename FunctionType>
	interruptible_thread(FunctionType f);
	void join();
	void detach();
	bool joinable() const;
	void interrupt();
};
```

```c++
class interrupt_flag
{
public:
		void set();
		bool is_set() const;
};
thread_local interrupt_flag this_thread_interrupt_flag; // 1

class interruptible_thread
{
	std::thread internal_thread;
	interrupt_flag* flag;
public:
	template<typename FunctionType>
	interruptible_thread(FunctionType f)
	{
		std::promise<interrupt_flag*> p; // 2
		internal_thread = std::thread([f, &p]{ // 包装了一个lambda函数
			p.set_value(&this_thread_interrupt_flag);
			f(); // 让线程能够调用提供函数的副本
		});
		flag = p.get_future().get(); // 将结果存入flag成员变量中 
	}
	void interrupt()
	{
		if(flag)
		{
			flag->set(); // 设置标志
		}
	}
};
```

```c++
void interruption_point()
{
	if(this_thread_interrupt_flag.is_set())
	{
		throw thread_interrupted();
	}
}
```

```c++
void foo()
{
	while(!done)
	{
		interruption_point();
		process_next_item();
	}
}
```
### 中断等待-条件变量

为`std::condition_variable`在interruptible_wait中使用超时，例：

```c++
class interrupt_flag
{
	std::atomic<bool> flag;
	std::condition_variable* thread_cond;
	std::mutex set_clear_mutex;

public:
	interrupt_flag() : thread_cond(0) {}

	void set()
	{
		flag.store(true, std::memory_order_relaxed);
		std::lock_guard<std::mutex> lk(set_clear_mutex);
		if(thread_cond)
		{
			thread_cond->notify_all();
		}
	}

	bool is_set() const
	{
		return flag.load(std::memory_order_relaxed);
	}

	void set_condition_variable(std::condition_variable& cv)
	{
		std::lock_guard<std::mutex> lk(set_clear_mutex);
		thread_cond = &cv;
	}

	void clear_condition_variable()
	{
		std::lock_guard<std::mutex> lk(set_clear_mutex);
		thread_cond = 0;
	}

	struct clear_cv_on_destruct
	{
		~clear_cv_on_destruct()
		{
			this_thread_interrupt_flag.clear_condtion_variable();
		}
	};
};

void interruptible_wait(std::condition_variable& cv, std::unique_lock<std::mutex>& lk)
{
	interruption_point();
	this_thread_interrupt_flag.set_condtion_variable(cv);
	interrupt_flag::clear_cv_on_destruct guard;
	interruption_point();
	cv.wait_for(lk, std::chrono::milliseconds(1));
	interruption_point();
}
```

### 使用`std::condition_variable_any`中断等待

为`std::condtion_variable_any`设计的interruptible_wait，例：

```c++
class interrupt_flag
{
	std::atomic<bool> flag;
	std::condition_variable* thread_cond;
	std::condition_variable_any* thread_cond_any;
	std::mutex set_clear_mutex;

public:
	interrupt_flag() : thread_cond(0), thread_cond_any(0) {}

	void set()
	{
		flag.store(true, std::memory_order_relaxed);
		std::lock_guard<std::mutex> lk(set_clear_mutex);
		if (thread_cond)
		{
			thread_cond->notify_all();
		}
		else if(thread_cond_any)
		{
			thread_cond_any->notify_all();
		}
	}

	template<typename Lockable>
	void wait(std::condition_variable_any& cv, Lockable& lk)
	{
		struct custom_lock
		{
			interrupt_flag* self;
			Lockable& lk;

			custom_lock(interrupt_flag* self_,
					    std::condition_variable_any& cond,
						Lockable& lk_):
					self(self_), lk(lk_)
				{
					self->set_clear_mutex.lock();  // 锁住内部 
					self->thread_cond_any = &cond; // 传入锁的构造函数中 
				} 

			void unlock() // 解锁 
			{
				lk.unlock();
				self->set_clear_mutex.unlock();
			}

			void lock()
			{
				std::lock(self->set_clear_mutex, lk); // 继续锁柱set_clear_mutex
			}

			~custom_lock()
			{
				self->thread_cond_any = 0; // 清理thread_cond_any
				self->set_clear_mutex.unlock();
			}
		};
		custom_lock cl(this, cv, lk);
		interruption_point();
		cv.wait(cl);
		interruption_point();
	}
	// rest as before
};

template <typename Lockable>
void interrruptible_wait(std::condition_variable_any& cv, Lockable& lk)
{
	this_thread_interrupt_flag.wait(cv, lk);
}
```

### 应用退出时中断后台任务

在后台监视文件系统，例：

```c++
std::mutex config_mutex;
std::vector<interruptible_thread> background_threads;

void background_thread(int disk_id)
{
	while(true)
	{
		interruption_point(); 
		fs_change fsc = get_fs_changes(disk_id); // 检查磁盘的变化
		if (fsc.has_changes())
		{
			update_index(fsc); 
		}
	}
}

void start_background_processing()
{
	background_threads.push_back(
					interruptible_thread(background_thread, disk_1));
	background_threads.push_back(
					interruptible_thread(background_thread, disk_2));
}

int main()
{
	start_background_processing(); // 启动时，后台线程已经启动
	process_gui_until_exit(); // 处理GUI 
	std::unique_lock<std::mutex> lk(config_mutex);
	for (unsigned i = 0; i < background_threads.size(); ++i)
	{
		background_threads[i].interrupt(); // 中断后台进程
	}
	for (unsigned i = 0; i < background_threads.size(); ++i)
	{
		background_threads[i].join(); // 等待后台线程结束后才退出
	}
}
```





