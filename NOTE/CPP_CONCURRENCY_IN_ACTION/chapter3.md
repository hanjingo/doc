# 第3章 在线程间共享数据



## 线程之间共享数据的问题

如果所有的共享数据都是只读的，就没有问题，因为一个线程所读取的数据不受另一个线程是否正在读取相同的数据而影响。

### 竞争条件

**竞争条件（racecondition）**：用来表示**有问题的（problematic）**竞争条件。

**数据竞争（datarace）**：表示因对单个对象的并发修改而产生的特定类型的竞争条件，数据竞争造成可怕的**未定义行为（undefined behavior）**

### 避免有问题的竞争条件

**无锁编程（lock-free programming）**：修改数据结构的设计及其不变量，从而令修改作为一系列不可分割的变更来完成，每个修改均保留其不变量。

**事务（transaction）**：所需的一系列数据修改和读取被存储在一个事务日志中，然后在单个步骤中进行提交。

**软件事务内存（software transactional memory, STM）**：事务步骤的提交因为数据结构已被另一个线程修改而无法进行，该事务将重新启动。



## 用互斥元保护共享数据
