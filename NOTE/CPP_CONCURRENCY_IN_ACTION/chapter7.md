# 第七章 设计无锁的并发数据结构



## 定义和结果

阻塞（blocking）：使用互斥元，条件变量以及future来同步。

非阻塞（nonblocking）：不使用阻塞库函数的数据结构和算法。

### 无锁数据结构的优点和缺点

使用无锁数据结构的原因：

1. 为了实现最大程度的并发
2. 健壮性



## 无锁数据结构的例子

### 编写不用锁的线程安全栈

```c++
template<typename T>
class lock_free_stack
{
private:
  struct node
  {
    std::shared_ptr<T> data;
    node* next;
    
    node(T const& data_) : data(std::make_shared<T>(data_)) {}
  };
  std::atomic<node*> head;
public:
  void push(T const& data)
  {
    node* const new_node = new node(data); // 创建节点
    new_node->next = head.load(); // 将next指针指向head
    while(!head.compare_exchange_weak(new_node->next, new_node)); // 将head指向新节点
  }
  std::shared_ptr<T> pop()
  {
    node* old_head=head.load();
    while (old_head &&
          !head.compare_exchange_weak(old_head, old_head->next));
    return old_head ? old_head->data : std::shared_ptr<T>(); 
  }
};
```

