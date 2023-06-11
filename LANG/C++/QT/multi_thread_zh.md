# Qt多线程


<!-- vim-markdown-toc GFM -->

* [线程](#线程)
    - [QThread](#qthread)
    - [创建线程的方法](#创建线程的方法)
    - [示例](#示例)
        + [派生QThread类对象并重写run方法示例](#派生qthread类对象并重写run方法示例)
        + [使用moveToThread示例](#使用movetothread示例)
* [线程安全](#线程安全)
    - [QMutex](#qmutex)
        + [QMutex使用示例](#qmutex使用示例)
    - [QMutexLocker](#qmutexlocker)
        + [QMutexLocker使用示例](#qmutexlocker使用示例)
    - [QWaitCondition](#qwaitcondition)
        + [生产-消费者模式使用QWaitCondition示例](#生产-消费者模式使用qwaitcondition示例)
    - [QReadWriteLock](#qreadwritelock)
        + [QReadLocker](#qreadlocker)
        + [QWriteLocker](#qwritelocker)
        + [QReadWriteLock使用示例](#qreadwritelock使用示例)
        + [QReadLocker, QWriteLocker使用示例](#qreadlocker-qwritelocker使用示例)
    - [QSemaphore](#qsemaphore)
        + [QSemphore使用示例](#qsemphore使用示例)
    - [QAtomicPointer](#qatomicpointer)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 线程

### QThread

```c++
class Q_CORE_EXPORT QThread : public QObject
{
    Q_OBJECT
public:
    static Qt::HANDLE currentThreadId() Q_DECL_NOTHROW Q_DECL_PURE_FUNCTION;
    static QThread *currentThread();              // 返回当前线程的指针
    static int idealThreadCount() Q_DECL_NOTHROW; // 返回可以在本系统上可运行的理想线程数（CPU核数）
    static void yieldCurrentThread();

    explicit QThread(QObject *parent = Q_NULLPTR);
    ~QThread();
    // 线程优先级
    enum Priority {
        IdlePriority,         // 没有其它线程运行时才调度

        LowestPriority,
        LowPriority,
        NormalPriority,       // 操作系统的默认优先级
        HighPriority,
        HighestPriority,

        TimeCriticalPriority, // 尽可能频繁的调度

        InheritPriority       // 使用同创建线程一样的优先级（默认）
    };

    void setPriority(Priority priority); // 设置线程优先级
    Priority priority() const;           // 返回当前线程的优先级

    bool isFinished() const; // 线程中的任务是否完成
    bool isRunning() const;  // 线程是否正在执行任务

    void requestInterruption();           // 请求线程中断（是否中断取决于线程业务逻辑）
    bool isInterruptionRequested() const; // 是否已经请求了线程中断

    void setStackSize(uint stackSize);
    uint stackSize() const;
    // 退出线程的工作函数，停止底层的事件循环
    void exit(int retcode = 0);

    QAbstractEventDispatcher *eventDispatcher() const;
    void setEventDispatcher(QAbstractEventDispatcher *eventDispatcher);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    int loopLevel() const;

public Q_SLOTS:
    void start(Priority = InheritPriority); // (slots) 启动线程（先执行started()，然后执行run()）
    void terminate();                       // (slots) 立即退出线程（不推荐使用这个函数，线程是否终止取决于OS）
    void quit();                            // (slots) 退出线程的工作函数（等效于exit, 后续调用wait等待任务完成）

public:
    // default argument causes thread to block indefinetely // 等待任务完成, 然后退出线程
    bool wait(unsigned long time = ULONG_MAX);
    // 线程休眠函数
    static void sleep(unsigned long);  // 单位：ms
    static void msleep(unsigned long); // 单位：s
    static void usleep(unsigned long); // 单位: us

Q_SIGNALS:
    void started(QPrivateSignal);  // (signals)发送 启动线程实例信号
    void finished(QPrivateSignal); // (signals)发送 终止线程实例运行信号

protected:
    virtual void run(); // 线程的起点（线程子类必须重写它）
    int exec();         // 进入事件循环并等待调用exit()

    static void setTerminationEnabled(bool enabled = true);

protected:
    QThread(QThreadPrivate &dd, QObject *parent = Q_NULLPTR);

private:
    Q_DECLARE_PRIVATE(QThread)

    friend class QCoreApplication;
    friend class QThreadData;
};
```

**注意事项**

1. 推荐使用信号槽的方式来结合多线程使用。
2. 当一个变量需要在多个线程间进行访问时，最好加上voliate关键字。

### 创建线程的方法

- 派生QThread线程类对象，并重写run方法（旧方法，不推荐）。

  Qt提供的线程类：

  | 线程类              | 说明                                          |
  | ------------------- | --------------------------------------------- |
  | QAtomicInt          | 提供了Integer上与平台无关的Qtomic运算         |
  | QAtomicPointer      | 提供了指针上Atomic运算的模板函数              |
  | QFuture             | 显示异步运算结果的类                          |
  | QFutureSynchronizer | QFuture类简化同步而提供的类                   |
  | QFutureWatcher      | 使用信号和槽，允许QFuture监听                 |
  | QMutex              | 访问类之间的同步                              |
  | QMutecLocker        | 简化Lock和Unlock Mutex的类                    |
  | QReadWriteLock      | 控制读写操作的类                              |
  | QReadLocker         | 为了读访问而提供的                            |
  | QWriteLocker        | 为了写访问而提供的                            |
  | QRunnable           | 正在运行的所有对象的父类，且定义了虚函数run() |
  | QSemaphore          | 一般的Count互斥体类                           |
  | QThread             | 提供与平台无关的线程功能的类                  |
  | QThreadPool         | 管理线程的类                                  |
  | QThreadStorage      | 提供每个线程存储区域的类                      |
  | QWaitCondition      | 确认线程间同步的类的状态值                    |

- 使用`moveToThread()`（推荐）。

  QObject中的`moveToThread()`函数通过改变线程关联性，将Worker类对象整体移动到新线程中，可以在不破坏类结构和**所有权**的前提下让其在新线程中运行。

  ```mermaid
  graph LR
  A(Worker类) --moveToThread--> A1
  
  subgraph 新线程
  	A1(Worker类)
  end
  subgraph Controller
  	B1(发送命令)
  	B2(接受结果)
  end
  B1 --signal--> A1
  A1 --signal--> B2
  ```
  
  **注意事项**
  
  1. 如果Worker对象保存在栈上，销毁工作由OS自动完成；如果Worker对象保存在堆上，需要将线程的`finished()`函数关联到QObject的`deleteLater()`上，让其在正确的时机被销毁；
  2. 如果Worker对象中有QTimer等计时器，一旦移动到新线程，计时器将重新启动（待确认）。
  2. 自定义的类不能指定父对象，因为`moveToThread`函数会将线程对象指定为自定义的类的父对象，当自定义的类对象已经有了父对象，就会报错。


### 示例

#### 派生QThread类对象并重写run方法示例

1. 自定义`MyThread`类，继承自QThread，并重写`run`函数；

   ```c++
   // MyThread.h
   #ifndef MYTHREAD_H
   #define MYTHREAD_H
   
   #include <qthread.h>
   
   class MyThread : public QThread
   {
   public:
       explicit MyThread() {};
       void run();
   };
   
   #endif // MYTHREAD_H
   ```
   
   ```c++
   // MyThread.cpp
   #include "MyThread.h"
   #include <qdebug.h>
   
   // rewrite function run
   void MyThread::run()
   {
       qDebug() << "thread start...";
       qDebug() << "current thread id:" << QThread::currentThreadId();
       QThread::sleep(2);
       qDebug() << "thread end!";
   }
   ```
   
2. 新建`Controller`类

   ```c++
   // Controller.h
   #ifndef CONTROLLER_H
   #define CONTROLLER_H
   
   #include "MyThread.h"
   
   class Controller
   {
   public:
       Controller(){};
       void Start()
       {
           t = new MyThread();
           t->start();
       };
   
   private:
       MyThread* t;
   };
   
   #endif // CONTROLLER_H
   ```

3. 新建`main`文件

   ```c++
   #include <QCoreApplication>
   #include "Controller.h"
   
   int main(int argc, char *argv[])
   {
       QCoreApplication a(argc, argv);
   
       Controller ctl{};
       ctl.Start();
   
       return a.exec();
   }
   ```

#### 使用moveToThread示例

1. 新建`Worker`类

   ```c++
   // Worker.h
   #ifndef WORKER_H
   #define WORKER_H
   
   #include <QObject>
   
   class Worker : public QObject
   {
       Q_OBJECT
   public:
       explicit Worker(QObject *parent = nullptr);
   
   signals:
       void resultReady(const QString &str); // -> Controller::on_receivResult
   
   public slots:
       void on_doSomething(); // -> Worker::resultReady
   };
   
   #endif // WORKER_H
   ```

   ```c++
   // Worker.cpp
   #include "Worker.h"
   #include <QDebug>
   #include <QThread>
   
   Worker::Worker(QObject *parent) : QObject(parent){}
   
   void Worker::on_doSomething()
   {
       qDebug() << "Worker's thread id:" << QThread::currentThreadId();
       emit resultReady("Hello");
   }
   ```

2. 新建`Controller`类

   ```c++
   // Controller.h
   #ifndef CONTROLLER_H
   #define CONTROLLER_H
   
   #include <QObject>
   #include <QThread>
   #include "Worker.h"
   
   class Controller : public QObject
   {
       Q_OBJECT
   public:
       explicit Controller(QObject *parent = nullptr);
       ~Controller();
       void start();
   
   signals:
       void startRunning(); // -> Worker::on_doSomething()
   
   public slots:
       // print result :xx
       void on_receivResult(const QString &str); // <- Worker::resultReady()
   
   private:
       QThread t;
       Worker *worker;
   };
   
   #endif
   ```

   ```c++
   // Controller.cpp
   #include "Controller.h"
   #include <QThread>
   #include <QDebug>
   
   Controller::Controller(QObject *parent) : QObject(parent)
   {
       qDebug() << "Controller's thread is :" << QThread::currentThreadId();
       worker = new Worker();
       worker->moveToThread(&t);
   
       connect(this, &Controller::startRunning,
               worker, &Worker::on_doSomething);
       connect(&t, &QThread::finished,
               worker, &QObject::deleteLater);
       connect(worker, &Worker::resultReady,
               this, &Controller::on_receivResult);
   
       t.start(); // start thread
   }
   
   Controller::~Controller()
   {
       t.quit();
       t.wait();
   }
   
   void Controller::start()
   {
       emit startRunning();
   }
   
   void Controller::on_receivResult(const QString &str)
   {
       qDebug() << "print result :" << str;
   }
   ```

3. 新建`main`文件

   ```c++
   // main.cpp
   #include <QCoreApplication>
   #include <QThread>
   #include <QDebug>
   #include "Controller.h"
   
   int main(int argc, char *argv[])
   {
       QCoreApplication a(argc, argv);
   
       qDebug() << "the main thread id :" << QThread::currentThread();
       Controller ctl;
       ctl.start();
   
       return a.exec();
   }
   ```




## 线程安全

互斥锁是一种简单的加锁的方法来控制对共享资源的读写访问。

### QMutex

```c++
// Qt互斥量
class Q_CORE_EXPORT QMutex : public QBasicMutex
{
public:
    enum RecursionMode { NonRecursive, Recursive }; // 重入模式
    explicit QMutex(RecursionMode mode = NonRecursive);
    ~QMutex();

    // BasicLockable concept // 加锁
    void lock() QT_MUTEX_LOCK_NOEXCEPT;
    bool tryLock(int timeout = 0) QT_MUTEX_LOCK_NOEXCEPT;
    // BasicLockable concept
    void unlock() Q_DECL_NOTHROW;

    // Lockable concept // 解锁
    bool try_lock() QT_MUTEX_LOCK_NOEXCEPT { return tryLock(); }

#if QT_HAS_INCLUDE(<chrono>)
    // TimedLockable concept // 超时等待加锁
    template <class Rep, class Period>
    bool try_lock_for(std::chrono::duration<Rep, Period> duration)
    {
        return tryLock(convertToMilliseconds(duration));
    }

    // TimedLockable concept // 超时等待加锁
    template<class Clock, class Duration>
    bool try_lock_until(std::chrono::time_point<Clock, Duration> timePoint)
    {
        // Implemented in terms of try_lock_for to honor the similar
        // requirement in N4606 § 30.4.1.3 [thread.timedmutex.requirements]/12.

        return try_lock_for(timePoint - Clock::now());
    }
#endif
    // 是否可重入
    bool isRecursive() const Q_DECL_NOTHROW
    { return QBasicMutex::isRecursive(); }

private:
    Q_DISABLE_COPY(QMutex)
    friend class QMutexLocker;
    friend class ::tst_QMutex;

#if QT_HAS_INCLUDE(<chrono>)
    template<class Rep, class Period>
    static int convertToMilliseconds(std::chrono::duration<Rep, Period> duration)
    {
        // N4606 § 30.4.1.3.5 [thread.timedmutex.requirements] specifies that a
        // duration less than or equal to duration.zero() shall result in a
        // try_lock, unlike QMutex's tryLock with a negative duration which
        // results in a lock.

        if (duration <= duration.zero())
            return 0;

        // when converting from 'duration' to milliseconds, make sure that
        // the result is not shorter than 'duration':
        std::chrono::milliseconds wait = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        if (wait < duration)
            wait += std::chrono::milliseconds(1);
        Q_ASSERT(wait >= duration);
        const auto ms = wait.count();
        const auto maxInt = (std::numeric_limits<int>::max)();

        return ms < maxInt ? int(ms) : maxInt;
    }
#endif
};
```

**注意事项**

1. 使用QMutex进行`lock()`操作时：代码提前退出（抛出异常），可能并未执行`unlock()`操作，若其它线程采用`lock()`阻塞式上锁时会一直被阻塞，导致资源泄露（所以推荐自定义QMutex的RAII或者QMutexLocker的方式以避免这个问题）。

#### QMutex使用示例

```c++
// main.cpp
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QMutex>

static int NUM = 10;
QMutex mu; // global mutex

class MyThread : public QThread
{
public:
    void run()
    {
        qDebug() << "thread id :" << QThread::currentThreadId() << " start...";
        mu.lock();
        while (NUM > 0)
        {
            NUM--;
            qDebug() << "thread id :" << QThread::currentThreadId() << " NUM :" << NUM;
        }
        mu.unlock();
        qDebug() << "thread id :" << QThread::currentThreadId() << "end!";
    };
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyThread t1{};
    MyThread t2{};

    t1.start();
    t2.start();
    
    t1.wait();
    t2.wait();

    return a.exec();
}
```

### QMutexLocker

```c++
// 带RAII机制的QMutex
class Q_CORE_EXPORT QMutexLocker
{
public:
#ifndef Q_CLANG_QDOC
    inline explicit QMutexLocker(QBasicMutex *m) QT_MUTEX_LOCK_NOEXCEPT
    {
        Q_ASSERT_X((reinterpret_cast<quintptr>(m) & quintptr(1u)) == quintptr(0),
                   "QMutexLocker", "QMutex pointer is misaligned");
        val = quintptr(m);
        if (Q_LIKELY(m)) {
            // call QMutex::lock() instead of QBasicMutex::lock()
            static_cast<QMutex *>(m)->lock();
            val |= 1;
        }
    }
#else
    QMutexLocker(QMutex *) { }
#endif
    inline ~QMutexLocker() { unlock(); }
    // 解锁
    inline void unlock() Q_DECL_NOTHROW
    {
        if ((val & quintptr(1u)) == quintptr(1u)) {
            val &= ~quintptr(1u);
            mutex()->unlock();
        }
    }
    // 重加锁
    inline void relock() QT_MUTEX_LOCK_NOEXCEPT
    {
        if (val) {
            if ((val & quintptr(1u)) == quintptr(0u)) {
                mutex()->lock();
                val |= quintptr(1u);
            }
        }
    }

#if defined(Q_CC_MSVC)
#pragma warning( push )
#pragma warning( disable : 4312 ) // ignoring the warning from /Wp64
#endif
    // 返回原始QMutex
    inline QMutex *mutex() const
    {
        return reinterpret_cast<QMutex *>(val & ~quintptr(1u));
    }

#if defined(Q_CC_MSVC)
#pragma warning( pop )
#endif

private:
    Q_DISABLE_COPY(QMutexLocker)

    quintptr val;
};
```

QMutexLocker是加了RAII功能的QMutex，当函数中途return或抛出异常时，会在离开作用域时调用析构函数释放对象，避免了死锁问题。

**注意事项**

#### QMutexLocker使用示例

```c++
// main.cpp
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QMutex>

static int NUM = 10;
QMutex mu; // global mutex

class MyThread : public QThread
{
public:
    void run()
    {
        qDebug() << "thread id :" << QThread::currentThreadId() << " start...";
        while (NUM > 0)
        {
            QMutexLocker lock{&mu};

            NUM--;
            qDebug() << "thread id :" << QThread::currentThreadId() << " NUM :" << NUM;
            if (NUM < 3) { return; }
        }
        qDebug() << "thread id :" << QThread::currentThreadId() << "end!";
    };
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyThread t1{};
    MyThread t2{};

    t1.start();
    t2.start();
    
    t1.wait();
    t2.wait();

    return a.exec();
}
```

### QWaitCondition

```c++
class Q_CORE_EXPORT QWaitCondition
{
public:
    QWaitCondition();
    ~QWaitCondition();
    // 等待唤醒
    bool wait(QMutex *lockedMutex, unsigned long time = ULONG_MAX);
    bool wait(QReadWriteLock *lockedReadWriteLock, unsigned long time = ULONG_MAX);
    // 唤醒
    void wakeOne();
    void wakeAll();
    // 通知
    void notify_one() { wakeOne(); }
    void notify_all() { wakeAll(); }

private:
    Q_DISABLE_COPY(QWaitCondition)

    QWaitConditionPrivate * d;
};
```

`QWaitCondition（条件变量）`允许线程在某些情况发生时唤醒另外的线程。

#### 生产-消费者模式使用QWaitCondition示例

```c++
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include <vector>

class Producer;
class Consumer;

// channel
class Channel
{
public:
    void put(int n)
    {
        mu.lock();

        v.push_back(n);
        cond.notify_all();

        mu.unlock();
    };
    int get()
    {
        mu.lock();

        cond.wait(&mu);
        auto itr = v.begin();
        v.erase(itr);

        mu.unlock();
        return *itr;
    };

private:
    QWaitCondition cond;
    std::vector<int> v;
    QMutex mu;
};
Channel ch{};

// producer
class Producer : public QThread
{
public:
    void run()
    {
        for (int i = 1; i < 10; i++)
        {
            this->put(i);
        }
    };
    void put(int n)
    {
        qDebug() << "producer product idx :" << n;
        ch.put(n);

        QThread::sleep(1);
        qDebug() << "producer sleep...\n";
    };
};

// consumer
class Consumer : public QThread
{
public:
    void run()
    {
        while (true)
        {
            this->get();
        }
    };
    int get()
    {
        int n = ch.get();
        qDebug() << "consumer consume idx :" << n;
        return n;
    };
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Producer p{};
    Consumer c{};

    p.start();
    c.start();

    p.wait();
    c.wait();

    return a.exec();
}
```

### QReadWriteLock

```c++
// 读写锁
class Q_CORE_EXPORT QReadWriteLock
{
public:
    enum RecursionMode { NonRecursive, Recursive };

    explicit QReadWriteLock(RecursionMode recursionMode = NonRecursive);
    ~QReadWriteLock();
    // 锁住读
    void lockForRead();
    bool tryLockForRead();
    bool tryLockForRead(int timeout);
    // 锁住写
    void lockForWrite();
    bool tryLockForWrite();
    bool tryLockForWrite(int timeout);
    // 解锁
    void unlock();

private:
    Q_DISABLE_COPY(QReadWriteLock)
    QAtomicPointer<QReadWriteLockPrivate> d_ptr;
    // 条件变量{已锁读，已锁写，已解锁，已锁住重入性}
    enum StateForWaitCondition { LockedForRead, LockedForWrite, Unlocked, RecursivelyLocked };
    StateForWaitCondition stateForWaitCondition() const;
    friend class QWaitCondition;
};
```

`QReadWriteMutex读写锁`，允许多个读者同时读数据，但只能有一个写数据，且读写操作不能同时进行，可以使多线程程序更具有并发性。

#### QReadLocker

```c++
// 带有RAII机制的读锁
class Q_CORE_EXPORT QReadLocker
{
public:
    inline QReadLocker(QReadWriteLock *readWriteLock);

    inline ~QReadLocker()
    { unlock(); }
    // 解锁
    inline void unlock()
    {
        if (q_val) {
            if ((q_val & quintptr(1u)) == quintptr(1u)) {
                q_val &= ~quintptr(1u);
                readWriteLock()->unlock();
            }
        }
    }
    // 重新加锁
    inline void relock()
    {
        if (q_val) {
            if ((q_val & quintptr(1u)) == quintptr(0u)) {
                readWriteLock()->lockForRead();
                q_val |= quintptr(1u);
            }
        }
    }
    // 返回读写锁
    inline QReadWriteLock *readWriteLock() const
    { return reinterpret_cast<QReadWriteLock *>(q_val & ~quintptr(1u)); }

private:
    Q_DISABLE_COPY(QReadLocker)
    quintptr q_val;
};
```

带有RAII机制的读锁，用于避免`QReadWriteMutex`读泄露的问题。

#### QWriteLocker

```c++
// 带有RAII机制的写锁
class Q_CORE_EXPORT QWriteLocker
{
public:
    inline QWriteLocker(QReadWriteLock *readWriteLock);

    inline ~QWriteLocker()
    { unlock(); }
    // 解锁
    inline void unlock()
    {
        if (q_val) {
            if ((q_val & quintptr(1u)) == quintptr(1u)) {
                q_val &= ~quintptr(1u);
                readWriteLock()->unlock();
            }
        }
    }
    // 重新加锁
    inline void relock()
    {
        if (q_val) {
            if ((q_val & quintptr(1u)) == quintptr(0u)) {
                readWriteLock()->lockForWrite();
                q_val |= quintptr(1u);
            }
        }
    }
    // 返回读写锁
    inline QReadWriteLock *readWriteLock() const
    { return reinterpret_cast<QReadWriteLock *>(q_val & ~quintptr(1u)); }


private:
    Q_DISABLE_COPY(QWriteLocker)
    quintptr q_val;
};
```

带有RAII机制的写锁，用于避免`QReadWriteMutex`写泄露的问题。

#### QReadWriteLock使用示例

```c++
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QReadWriteLock>

static int NUM = 10;
QReadWriteLock lock; // global mutex

class ReadThread : public QThread
{
public:
    void run()
    {
        qDebug() << "read thread id :" << QThread::currentThreadId() << " start...";
        while (NUM > 0)
        {
            lock.lockForRead();
            qDebug() << "read thread id :" << QThread::currentThreadId() << " read NUM :" << NUM;
            lock.unlock();
        }
        qDebug() << "read thread id :" << QThread::currentThreadId() << " end!";
    };
};

class WriteThead : public QThread
{
public:
    void run()
    {
        qDebug() << "write thread id :" << QThread::currentThreadId() << " start...";
        while (NUM > 0)
        {
            lock.lockForWrite();
            NUM--;
            qDebug() << "write thread id :" << QThread::currentThreadId() << " write NUM :" << NUM;
            lock.unlock();
        }
        qDebug() << "write thread id :" << QThread::currentThreadId() << "end!";
    };
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ReadThread r{};
    WriteThead w{};

    r.start();
    w.start();
    
    r.wait();
    w.wait();

    return a.exec();
}
```

#### QReadLocker, QWriteLocker使用示例

```c++
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QReadWriteLock>

static int NUM = 10;
QReadWriteLock lock; // global read write locker // global write locker

class ReadThread : public QThread
{
public:
    void run()
    {
        qDebug() << "read thread id :" << QThread::currentThreadId() << " start...";
        while (NUM > 0)
        {
            QReadLocker r{&lock};
            qDebug() << "read thread id :" << QThread::currentThreadId() << " read NUM :" << NUM;
        }
        qDebug() << "read thread id :" << QThread::currentThreadId() << " end!";
    };
};

class WriteThead : public QThread
{
public:
    void run()
    {
        qDebug() << "write thread id :" << QThread::currentThreadId() << " start...";
        while (NUM > 0)
        {
            QWriteLocker w{&lock};
            NUM--;
            qDebug() << "write thread id :" << QThread::currentThreadId() << " write NUM :" << NUM;
        }
        qDebug() << "write thread id :" << QThread::currentThreadId() << "end!";
    };
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ReadThread r{};
    WriteThead w{};

    r.start();
    w.start();
    
    r.wait();
    w.wait();

    return a.exec();
}
```

### QSemaphore

```c++
// 信号量
class Q_CORE_EXPORT QSemaphore
{
public:
    explicit QSemaphore(int n = 0); // 新建一个守护n个资源的信号量
    ~QSemaphore();
    // 获取n个资源，阻塞直到要求满足
    void acquire(int n = 1);
    bool tryAcquire(int n = 1);
    bool tryAcquire(int n, int timeout);
    // 释放n个资源，如果资源数目不够就立即返回
    void release(int n = 1);
    // 返回可用资源的数目
    int available() const;

private:
    Q_DISABLE_COPY(QSemaphore)

    QSemaphorePrivate *d;
};
```

`QSemphore（信号量）`实际上是广义的互斥量，一个互斥量只能被锁定一次，一个信号量可以被获取多次，常用于保护多个数目的同类资源。

#### QSemphore使用示例

```c++
#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QSemaphore>
#include <QTime>

int buf[10];
QSemaphore s(10);

void print()
{
    for (int i = 0; i < 10; ++i)
        qDebug() << buf[i];
}

// producer
class Producer : public QThread
{
public:
    void run()
    {
        s.acquire(10);
        qDebug() << "producer thread id :" << QThread::currentThreadId() << " start...";
        for (int i = 0; i < 10; ++i)
        {
            buf[i] = i;
        }
        print();
        s.release(10);
        qDebug() << "producer thread id :" << QThread::currentThreadId() << "end!";
    };
};

// consumer
class Consumer : public QThread
{
public:
    void run()
    {
        s.acquire(10);
        qDebug() << "consumer thread id :" << QThread::currentThreadId() << " start...";
        for (int i = 0; i < 10; ++i)
        {
            buf[i] = 0;
        }
        print();
        s.release(10);
        qDebug() << "consumer thread id :" << QThread::currentThreadId() << "end!";
    };
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Producer p{};
    Consumer c{};

    p.start();
    c.start();

    p.wait();
    c.wait();

    return a.exec();
}
```

### QAtomicPointer

TODO



## 参考

- [QT从入门到入土（五（1））——多线程（QThread） ](https://www.cnblogs.com/xyf327/p/15032670.html)
- [Qt 多线程编程之敲开 QThread 类的大门](https://zhuanlan.zhihu.com/p/53270619)
- [Qt 多线程详解 - 两种线程使用方式](https://blog.csdn.net/qq_27278957/article/details/106018649)
- [Qt多线程基础（一）线程同步之互斥锁同步](https://blog.csdn.net/hechao3225/article/details/53033993)
- [QT学习——QSemaphore](https://blog.csdn.net/zzh_AI/article/details/106425840#:~:text=QSemaphore%3A%E4%B8%80%E4%B8%AA%E9%80%9A%E7%94%A8%E7%9A%84%E5%8F%AF,%E4%B8%80%E5%AE%9A%E6%95%B0%E7%9B%AE%E7%9A%84%E5%90%8C%E7%B1%BB%E8%B5%84%E6%BA%90%E3%80%82)
