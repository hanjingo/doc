# 基于锁的并发数据结构设计

[TOC]



## 为并发设计的意义何在

- 多个线程可以并发的访问这个数据结构，线程可以对这个数据结构做相同或不同的操作，并且每一个线程都能在自己的自治域中看到该数据结构。
- 在多线程环境下，无数据丢失和损毁，所有的数据需要维持原样，且无条件竞争。

序列化（serialzation）:线程轮流访问被保护的数据。

### 数据结构并发设计指南

如何保证数据结构是线程安全的：

- 确保无线程能够看到，数据结构的“不变量”破坏时的状态。
- 小心那些会引起条件竞争的接口，提供完整操作的函数，而非操作步骤。
- 注意数据结构的行为是否会产生异常，从而确保“不变量”的状态稳定。
- 将死锁的概率降到最低。使用数据结构时，需要限制锁的范围，且避免嵌套锁的存在。

在设计数据结构时，需要自行考虑以下问题：

- 锁的范围中的操作，是否允许在锁外执行
- 数据结构中不同的区域是否能被不同的互斥量所保护
- 所有操作都需要同级互斥量保护
- 能否对数据结构进行简单的修改，以增加并发访问的概率，且不影响操作语义



## 基于锁的并发数据结构

### 线程安全栈

线程安全栈的类定义：

```c++
#include <exception>
struct empty_stack : std::exception
{
    const char* what() const throw();
};

template<typename T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;
    
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    
    threadsafe_stack& operator=(const threadsafe_stack&)=delete;
    
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }
    
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }
    
    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack();
        value = std::move(data.top());
        data.pop();
    }
    
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};
```

### 线程安全队列

使用条件变量实现的持有`std::shared_ptr<>`实例的线程安全队列：

```c++
template <typename T>
class threadsafe_queue
{
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T> > data_queue;
    std::condition_variable data_cond;
    
public:
    threadsafe_queue(){}
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(std::move(data));
        data_cond.notify_one();
    }
    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{ return !data_queue.empty(); });
        std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return res;
    }
    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = std::move(*data_queue.front());
        data_queue.pop();
        return true;
    }
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }
    void push(T new_value)
    {
        std::shared_ptr<T> data(
        	std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
}
```

使用细粒度锁和条件变量实现的线程安全队列：

```c++
template<typename T>
class threadsafe_queue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    
    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    node* tail;
    std::condition_variable data_cond;
    
    node* get_tail()
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }
    std::unique_ptr<node> pop_head()
    {
        std::unique_ptr<node> old_head=std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }
    std::unique_lock<std::mutex> wait_for_data()
    {
        std::unique_lock<std::mutex> head_lock(head_mutex);
        data_cond.wait(head_lock, [&]{return head.get() != get_tail();});
        return std::move(head_lock);
    }
    std::unique_ptr<node> wait_pop_head()
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        return pop_head();
    }
    std::unique_ptr<node> wait_pop_head(T& value)
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        value = std::move(*head->data);
        return pop_head();
    }
    
public:
    threadsafe_queue():
    	head(new node), tail(head.get())
    {}
    threadsafe_queue(const threadsafe_queue& other)=delete;
    threadsafe_queue& operator=(const threadsafe_queue& other) = delete;
    
    std::shared_ptr<T> try_pop();
    bool try_pop(T& value);
    std::shared_ptr<T> wait_and_pop();
    void push(T new_value);
    void empty();
    
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_ptr<node> const old_head=wait_pop_head();
        return old_head->data;
    }
    void wait_and_pop(T& value)
    {
        std::unique_ptr<node> const old_head=wait_pop_head(value);
    }
    std::unique_ptr<node> try_pop_head()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if (head.get() == get_tail())
        {
            return std::unique_ptr<node>();
        }
        return pop_head();
    }
    std::unique_ptr<node> try_pop_head(T& value)
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if (head.get()==get_tail())
        {
            return std::unique_ptr<node>();
        }
        value=std::move(*head->data);
        return pop_head();
    }
};

template<typename T>
void threadsafe_queue<T>::push(T new_value)
{
    std::shared_ptr<T> new_data(
    	std::make_shared<T>(std::move(new_value)));
    std::unique_ptr<node> p(new node);
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        tail->data = new_data;
        node* const new_tail=p.get();
        tail->next=std::move(p);
        tail=new_tail;
    }
    data_cond.notify_one();
}

template<typename T>
std::unique_ptr<T> threadsafe_queue<T>::try_pop()
{
    std::unique_ptr<node> old_head=try_pop_head();
    return old_head?old_head->data:std::shared_ptr<T>();
}

template<typename T>
bool threadsafe_queue<T>::trty_pop(T& value)
{
    std::unique_ptr<node> const old_head=try_pop_head(value);
    return old_head;
}

void threadsafe_queue::empty()
{
    std::lock_guard<std::mutex> head_lock(head_mutex);
    return (head.get() == get_tail());
}
```



## 基于锁设计更加复杂的数据结构

使用锁的线程安全查询表：

```c++
template<typename key, typename Value, typename Hash=std::hash<key> >
class threadsafe_lookup_table
{
private:
    class bucket_type
    {
    private:
        typedef std::pair<Key, Value> bucket_value;
        typedef std::list<bucket_value> bucket_data;
        typedef typename bucket_data::iterator bucket_iterator;
        
        bucket_data data;
        mutable boost::shared_mutex mutex;
        std::vector<std::unique_ptr<bucket_type> > buckets; // 桶子
    	Hash hasher;
    
   	 	bucket_type& get_bucket(Key const& key) const
    	{
       	 	std::size_t const bucket_index=hasher(key)%buckets.size();
        	return *buckets[bucket_index];
    	}
    
public:
    	typedef Key key_type;
        typedef Value mapped_type;
        
        typedef Hash hash_type;
        threadsafe_lookup_table(
        	unsigned num_buckets=19, Hash const& hasher_=Hash()) :
        	buckets(num_buckets), hasher(hasher_)
        {
                for(unsigned i=0; i<num_buckets; ++i)
                {
                    buckets[i].reset(new bucket_type);
                }
        }
        
        threadsafe_lookup_table(threadsafe_lookup_table const& other)=delete;
        threadsafe_lookup_table& operator=(
        	threadsafe_lookup_table const& other)=delete;
        
        Value value_for(Key const& key, Value const& default_value=Value()) const
        {
            return get_bucket(key).value_for(key, default_value);
        }
        
        void add_or_update_mapping(Key const& key, Value const& value)
        {
            get_bucket(key).add_or_update_mapping(key, value);
        }
        
        void remove_mapping(Key const& key)
        {
            get_bucket(key).remove_mapping(key);
        }
        
        bucket_iterator find_entry_for(Key const& key) const
        {
            return std::find_if(data.begin(), data.end(), [&](bucket_value const& item){
                return item.first == key;
            });
        }
        
public:
        Value value_for(Key const& key, Value const& default_value) const
        {
            boost::shared_lock<boost::shared_mutex> lock(mutex);
            bucket_iterator const found_entry=find_entry_for(key);
            return (found_entry==data.end()) ? default_value:found_entry->second;
        }
        void add_or_update_mapping(Key const& key, Value const& value)
        {
            std::unique_lock<boost::shared_mutex> lock(mutex);
            bucket_iterator const found_entry=find_entry_for(key);
            if (found_entry==data.end())
            {
                data.push_back(bucket_value(key, value));
            }
            else
            {
                found_entry->second=value;
            }
        }
        void remove_mapping(Key const& key)
        {
            std::unique_lock<boost::shared_mutex> lock(mutex);
            bucket_iterator const found_entry=find_entry_for(key);
            if(found_entry != data.end())
            {
                data.erase(found_entry);
            }
        }
    }
}

std::map<Key, Value> threadsafe_lookup_table::get_map() const
{
    std::vector<std::unique_lock<boost::shared_mutex> >locks;
    for (unsigned i = 0; i<buckets.size(); ++i)
    {
        locks.push_back(
        	std::unique_lock<boost::shared_mutex>(buckets[i].mutex));
    }
    std::map<Key, Value> res;
    for (unsigned i=0; i<buckets.size(); ++i)
    {
        for (bucket_iterator it=buckets[i].data.begin();
            	it != buckets[i].data.end();
            	++it)
        {
            res.insert(*it);
        }
    }
    return res;
}
```

线程安全链表：

```c++
template<typename T>
class threadsafe_list
{
    struct node
    {
        std::mutex m;
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
        node() : next(){}
        node(T const& value) : data(std::make_shared<T>(value)){}
    };
    
    node head;
    
public:
    threadsafe_list(){}
    ~threadsafe_list(){ remove_if([](node const&){return true;}); }
    threadsafe_list(threadsafe_list const& other)=delete;
    threadsafe_list& operator=(threadsafe_list const& other)=delete;
    
    void push_front(T const& value)
    {
        std::unique_ptr<node> new_node(new node(value));
        std::lock_guard<std::mutex> lk(head.m);
        new_node->next = std::move(head.next);
        head.next = std::move(new_node);
    }
    
    template<typename Function>
    void for_each(Function f)
    {
        node* current=&head;
        std::unique_lock<std::mutex> lk(head.m);
        while(node* const next=current->next.get())
        {
            std::unique_lock<std::mutex> next_lk(next->m);
            lk.unlock();
            f(*next->data);
            current=next;
            lk=std::move(next_lk);
        }
    }
    
    template<typename Predicate>
    std::shared_ptr<T> find_first_if(Predicate p)
    {
        node* current=&head;
        std::unique_lock<std::mutex> lk(head.m);
        while (nod* const next=current->next.get())
        {
            std::unique_lock<std::mutex> next_lk(next->m);
            lk.unlock();
            if (p(*next->data))
            {
                return next->data;
            }
            current = next;
            lk = std::move(next_lk);
        }
        return std::shared_ptr<T>();
    }
    
    template<typename Predicate>
    void remove_if(Predicate p)
    {
        node* current=&head;
        std::unique_lock<std::mutex> lk(head.m);
        while(node* const next=current->next.get())
        {
            std::unique_lock<std::mutex> next_lk(next->m);
            if(p(*next->data))
            {
                std::unique_ptr<node> old_next=std::move(current->next);
                current->next=std::move(next->next);
                next_lk.unlock();
            }
            else
            {
                lk.unlock();
                current = next;
                lk=std::move(next_lk);
            }
        }
    }
    
}
```



