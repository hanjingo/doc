English | [中文版](thread_zh.md)

# Thread

[TOC]



A thread, also called a `Light-Weight Process`, is an entity of a process and the basic unit of CPU scheduling and dispatch. It is lighter than a process, does not own system resources, only some necessary runtime resources (like program counter, registers, and stack). It has function entry and return, and can share all resources of the process with other threads in the same process. Thread communication is mainly via shared memory, context switching overhead is small, but stability is lower.

## Execution States

Three thread states:

- `Running`: The thread has the CPU and is running.
- `Ready`: The thread is ready to run as soon as it gets the CPU.
- `Blocked`: The thread is paused due to some event.



## Thread Control Block (TCB)

- `Thread identifier`: Unique for each thread.
- `Set of registers`: Includes PC, status, and general-purpose registers.
- `Thread state`: Describes the current state.
- `Priority`: Execution priority.
- `Thread private storage`: For saving protection info and statistics during context switch.
- `Signal mask`: Masks certain signals.
- `Stack pointer`: For local variables and return address.



## Thread Implementation

- Kernel Supported Threads (KST)

  ![thread_impl_core](/usr/local/src/github.com/hanjingo/doc/OS/res/thread_impl_core.png)

  *Thread data area space*

- User Level Threads (ULT)

  1. Runtime System

     Functions for thread management, creation, synchronization, communication, and scheduling.

  2. Kernel Control Threads

     Also called `Light Weight Process (LWP)`, each process can have multiple LWPs, each with its own TCB, identifier, priority, state, stack, and local storage.

     ![thread_impl_lwp](/usr/local/src/github.com/hanjingo/doc/OS/res/thread_impl_lwp.png)

    *Using lightweight processes as an intermediate system*

- Combined Models

  1. Many-to-one: Maps user threads to one kernel thread;

     ![thread_impl_comb1](/usr/local/src/github.com/hanjingo/doc/OS/res/thread_impl_comb1.png)

    *Many-to-one model*

  2. One-to-one: Maps each user thread to a kernel thread;

     ![thread_impl_comb2](/usr/local/src/github.com/hanjingo/doc/OS/res/thread_impl_comb2.png)

    *One-to-one model*

  3. Many-to-many: Maps many user threads to the same or fewer kernel threads.

     ![thread_impl_comb3](/usr/local/src/github.com/hanjingo/doc/OS/res/thread_impl_comb3.png)

    *Many-to-many model*



## Thread Creation and Termination

1. Thread creation

   Use a thread creation function (or syscall) with parameters (entry pointer, stack size, priority). Returns a thread ID.

2. Thread termination

   Another thread calls a function to terminate it. Resources are not released until another thread calls a detach function.



## Deadlock

### Definition

A set of processes is deadlocked if each process is waiting for an event that only another process in the set can cause.

### Causes of Deadlock

- Competing for non-preemptible resources

  ![deadlock_reason1](/usr/local/src/github.com/hanjingo/doc/OS/res/deadlock_reason1.png)

  *Deadlock situation when sharing files*

- Competing for consumable resources

  ![deadlock_reason2](/usr/local/src/github.com/hanjingo/doc/OS/res/deadlock_reason2.png)

  *Deadlock during inter-process communication*

- Improper process advancement order

  ![deadlock_reason3](/usr/local/src/github.com/hanjingo/doc/OS/res/deadlock_reason3.png)

    - $D$: Unsafe region
    - $P_1, P_2$: Processes

    When $P_1$ runs to $P_1$:$Request(R_2)$, it will be blocked because $R_2$ is already occupied by $P_2$; when $P_2$ runs to $P_2$:$Request(R_1)$, it will also be blocked because $R_1$ is already occupied by $P_1$, thus a process deadlock occurs.

Necessary conditions for deadlock:

- Mutual exclusion
- Hold and wait
- No preemption
- Circular wait

### Deadlock Handling Methods

#### Deadlock Prevention

Prevent deadlock by breaking one of the four necessary conditions.

- Break "hold and wait":

  1. First protocol

     All processes must request all resources needed for their entire run before starting.

  2. Second protocol

     Processes can request initial resources, run, release used resources, then request new ones.

- Break "no preemption":

  When a process that is already holding some non-preemptible resources makes a new resource request that cannot be satisfied, it must release all the resources it is currently holding and reapply for them when needed later.

- Break "circular wait":

  Each process must request resources in strictly increasing order of their serial numbers. At the beginning, a process can request units of a certain type of resource $R_i$. Later, it can only request units of resource $R_j$ if and only if $F(R_j) > F(R_i)$.

#### Deadlock Avoidance

Dynamically allocate resources to keep the system in a safe state (there exists a sequence $(P_1, P_2, ..., P_n)$ such that each $P_i$ can get its maximum resources and finish).

Using the Banker's algorithm to avoid deadlock

  Let $Request_i$ be the request vector of process $P_i$. If $Request_i[j] = K$, it means process $P_i$ needs $K$ resources of type $R_j$. When $P_i$ makes a resource request, the system checks as follows:

    1. If $Request_i[j] \leqslant Need[i, j]$, go to step 2; otherwise, it is an error because the requested number of resources exceeds the declared maximum.
    
    2. If $Request_i[j] \leqslant Available[j]$, go to step 3; otherwise, there are not enough resources, and $P_i$ must wait.
    
    3. The system tentatively allocates the resources to process $P_i$ and updates the following data structures:
    
    $Available[j] = Available[j] - Request_i[j];$
    
    $Allocation[i, j] = Allocation[i, j] + Request_i[j];$
    
    $Need[i, j] = Need[i, j] - Request_i[j];$
    
    4. The system runs the safety algorithm to check if the system is in a safe state after this allocation. If it is safe, the resources are officially allocated to $P_i$ to complete this allocation; otherwise, the tentative allocation is canceled, the original resource allocation is restored, and $P_i$ must wait.

#### Deadlock Detection

Allow deadlock to occur, but detect it and take action to recover.

- Resource Allocation Graph

  ![deadlock_detect1](/usr/local/src/github.com/hanjingo/doc/OS/res/deadlock_detect1.png)

  System deadlock can be described using a resource allocation graph. This graph is a pair $G=(N,E)$ consisting of a set of nodes $N$ and a set of edges $E$, with the following definitions and constraints:

      1. Divide $N$ into two mutually exclusive subsets: a set of process nodes $P={P_1, P_2, ..., P_n}$ and a set of resource nodes $R={R_1, R_2, ..., R_n}$, so $N = P \cup R$.
      2. Each edge $e \in E$ connects a node in $P$ and a node in $R$. $e={P_i, R_j}$ is a resource request edge, from process $P_i$ to resource $R_j$, indicating that $P_i$ requests one unit of resource $R_j$. $E = {R_j, P_i}$ is a resource allocation edge, from resource $R_j$ to process $P_i$, indicating that one unit of resource $R_j$ is allocated to $P_i$.

- Deadlock Theorem

  ![deadlock_detect2](/usr/local/src/github.com/hanjingo/doc/OS/res/deadlock_detect2.png)

  1. During resource allocation, find a process node $P_i$ that is neither blocked nor isolated. In a smooth scenario, $P_i$ can obtain the required resources and continue running until completion, then release all the resources it holds. This is equivalent to removing $P_i$'s request and allocation edges, making it an isolated node; see Figure b.
  2. After $P_1$ releases resources, $P_2$ can obtain resources and continue running. When $P_2$ finishes and releases all its resources, the situation shown in Figure c is formed, that is, $P_2$'s two request edges and one allocation edge are removed.
  3. After a series of such simplifications, if all edges in the graph can be removed and all process nodes become isolated nodes, the graph is said to be completely reducible; if the graph cannot be completely reduced by any process, it is said to be irreducible.

- Data structures for detection

  - Available resource vector Available, which indicates the number of available resources for each of the $m$ types of resources.
  - Add processes that do not occupy resources (vector Allocation=0) to the L list, i.e., $L_i \cup L$.
  - From the set of processes, find a process such that $Request_i \leqslant Work$, and do the following:
    1. Simplify its resource allocation graph, release its resources, and increase the work vector $Work = Work + Allocation_i$;
    2. Add it to the L list.
  - If not all processes can be added to the L list, it indicates that the resource allocation graph of system state $S$ is not completely reducible. Therefore, a deadlock will occur in this system state.

#### Deadlock Recovery

When deadlock is detected, take measures (e.g., kill processes) to recover.

- Resource preemption
- Terminate (or kill) processes



## POSIX API

### pthread_create

```c++
#include <pthread.h>
int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*func)(void *), void *arg);
```

- `tid`: returned thread ID
- `attr`: attributes
- `func`: function to execute
- `arg`: argument to function
- `return value`: 0 on success, error code on failure

Creates a thread.

### pthread_join

```c++
#include <pthread.h>
int pthread_join(pthread_t *tid, void **status);
```

- `tid`: thread ID
- `status`: thread return value
- `return value`: 0 on success, error code on failure

Waits for thread to terminate.

### pthread_self

```c++
#include <pthread.h>
int pthread_detach(pthread_t tid);
```

- `tid`: thread ID
- `return value`: 0 on success, error code on failure

Detaches the specified thread.

### pthread_exit

```c++
#include <pthread.h>
void pthread_exit(void *status);
```

- `status`: thread exit status

Terminates the thread.

### pthread_once

```c++
#include <pthread.h>
int pthread_once(pthread_once_t *onceptr, void (*init)(void));
```

- `onceptr`: call record pointer
- `init`: initialization function
- `return value`: 0 on success, error code on failure

Ensures init is called only once.

### pthread_key_create

```c++
#include <pthread.h>
int pthread_key_create(pthread_key_t *keyptr, void (*destructor)(void *value));
```

- `keyptr`: created key
- `destructor`: key destructor
- `return value`: 0 on success, error code on failure

Allocates a key for thread-specific data.

### pthread_getspecific

```c++
#include <pthread.h>
void *pthread_getspecific(pthread_key_t key);
```

- `key`: key
- `return value`: pointer to thread-specific data (nullable)

Gets value by key.

### pthread_setspecific

```c++
#include <pthread.h>
int pthread_setspecific(pthread_key_t key, const void *value);
```

- `key`: key
- `value`: value
- `return value`: 0 on success, error code on failure

Sets value by key.

### pthread_mutex_lock

```c++
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mptr);
```

- `mptr`: mutex
- `return value`: 0 on success, error code on failure

Locks the mutex.

### pthread_mutex_unlock

```c++
#include <pthread.h>
int pthread_mutex_unlock(pthread_mutex_t *mptr);
```

- `mptr`: mutex
- `return value`: 0 on success, error code on failure

Unlocks the mutex.

### pthread_cond_wait

```c++
#include <pthread.h>
int pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);
```

- `cptr`: condition variable
- `mptr`: mutex
- `return value`: 0 on success, error code on failure

Waits on a condition variable (single thread).

### pthread_cond_signal

```c++
#include <pthread.h>
int pthread_cond_signal(pthread_cond_t *cptr);
```

- `cptr`: condition variable
- `mptr`: mutex
- `return value`: 0 on success, error code on failure

Wakes up a single thread waiting on the condition variable.

### pthread_cond_timedwait

```c++
#include <pthread.h>
int pthread_cond_timedwait(pthread_cond_t *cptr, pthread_kmutex_t *mptr, 
                           const struct timespec *abstime);
```

- `cptr`: condition variable
- `mptr`: mutex
- `abstime`: absolute wait time (seconds and nanoseconds since 1970-01-01 UTC)
- `return value`: 0 on success, error code on failure

Timeout wait for all threads on the condition variable.

### pthread_cond_broadcast

```c++
#include <pthread.h>
int pthread_cond_broadcast(pthread_cond_t *cptr);
```

- `cptr`: condition variable
- `mptr`: mutex
- `abstime`: absolute wait time (seconds and nanoseconds since 1970-01-01 UTC)
- `return value`: 0 on success, error code on failure

Wakes up all threads waiting on the condition variable.



## References

[1] Tang Xiaodan, Liang Hongbing, Zhe Fengping, Tang Ziying. Computer Operating System. 3rd Edition. P32 - P115

[2] [Wikipedia - Coroutine](https://en.wikipedia.org/wiki/Coroutine)