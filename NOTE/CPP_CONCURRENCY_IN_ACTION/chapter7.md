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
  std::atomic<unsigned> thread_in_pop;
  std::atomic<node*> to_be_deleted;
  
  void try_reclaim(node* old_head);
  static void delete_nodes(node* nodes)
  {
    while(nodes)
    {
      node* next = nodes->next;
      delte nodes;
      nodes = next;
    }
  }
  void try_reclaim(node* old_head)
  {
    if (threads_in_pop == 1)
    {
      node* nodes_to_delete = to_be_deleted.exchange(nullptr); // 列出将要被删除的节点清单
      if (!--threads_in_pop)
      {
        delete_nodes(nodes_to_delete);
      }
      else if (nodes_to_delete)
      {
        chain_pending_nodes(nodes_to_delete);
      }
      delete old_head;
    }
    else
    {
      chain_pending_node(old_head);
      --threads_in_pop;
    }
  }
  void chain_pending_nodes(node* nodes)
  {
    node* last = nodes;
    while (node* const next = last->next) // 跟随下一个指针，链至末尾
    {
      last = next;
    }
    chain_pending_nodes(nodes, last);
  }
  void chain_pending_nodes(node* first, node* last)
  {
    last->next = to_be_deleted;
    while (!to_be_deleted.compare_exchange_weak(last->next, first)); // 循环以保证last->next正确
  }
  void chain_pending_node(node* n)
  {
    chain_pending_nodes(n, n);
  }
public:
  void push(T const& data)
  {
    node* const new_node = new node(data); // 创建节点
    new_node->next = head.load(); // 将next指针指向head
    while(!head.compare_exchange_weak(new_node->next, new_node)); // 将head指向新节点
  }
  std::shared_ptr<T> pop()
  {
    std::atomic<void*>& hp = get_hazard_pointer_for_current_thread(); // 返回风险指针的引用
    node* old_head=head.load(); // 读取旧指针
    do 
    {
      node* temp;
      do	// 一直循环到将风险指针设置到head上
      {
        temp = old_head;
        hp.store(old_head); // 设置风险指针
        old_head = head.load();
      } while(old_head != temp);
    }
    while (old_head && // 在解引用之前检查old_head不是一个空指针
          !head.compare_exchange_weak(old_head, old_head->next));
    hp.store(nullptr)
    std::shared_ptr<T> res;
    if (old_head)
    {
      res.swap(old_head->data); // 如果可能，回收删除的节点
      if (outstanding_hazard_pointers_for(old_head))
      {
        reclaim_later(old_head);
      }
      else
      {
        delete old_head;
      }
    	delete_nodes_with_no_hazards();
  }
  return res;
};
```

![7-1](res/7-1.png)
