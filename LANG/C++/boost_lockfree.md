# Boost::LockFree



boost::lockfree是boost1.53引入的无锁数据结构，包括：boost::lockfree::stack, boost::lockfree::queue, boost::lockfree::spsc_queue。

## boost::lockfree:stack

TODO



## boost::lockfree::queue

TODO



## boost::lockfree::spsc_queue

TODO



## 总结

| 无锁结构                      | 用途                                                         |
| ----------------------------- | ------------------------------------------------------------ |
| `boost::lockfree:stack`       | 多个生产者和多个消费者线程的无锁队列。                       |
| `boost::lockfree::queue`      | 多个生产者和多个消费者线程的无锁栈。                         |
| `boost::lockfree::spsc_queue` | 单个生产者和单个消费者线程的无锁队列，效率高于`boost::lockfree::queue`。 |

