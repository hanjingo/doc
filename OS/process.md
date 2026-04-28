English | [中文版](process_zh.md)

# Process

[TOC]



A process is an independent unit for resource allocation and scheduling in the system. Each process has its own independent memory space, and different processes communicate via inter-process communication. Processes are relatively heavy, context switching overhead is large, but they are more stable than threads.

## Definition

Definition:

- A process is an execution of a program.
- A process is the activity of a program and its data being executed sequentially on a processor.
- A process is a program with independent functionality running on a data set; it is an independent unit for resource allocation and scheduling in the system.

Characteristics:

- Dynamic: The essence of a process is the execution of a process entity, so dynamicity is the most fundamental characteristic.
- Concurrency: Multiple process entities coexist in memory and can run simultaneously within a period.
- Independence: A process entity can run independently, obtain resources independently, and accept investigation independently.
- Asynchrony: Processes run asynchronously, i.e., they progress at their own unpredictable speeds.

### Precedence Graph

A `Precedence Graph` is a directed acyclic graph (DAG) used to describe the execution order between processes.

The precedence relationship between processes (or programs) can be denoted as "$\rightarrow$". If there is a precedence relationship between $P_i$ and $P_j$, it can be written as $(P_i, P_j)\in \rightarrow$ or $P_i \rightarrow P_j$, meaning $P_i$ must complete before $P_j$ starts. $P_i$ is the direct predecessor of $P_j$, and $P_j$ is the direct successor of $P_i$.



## Process Allocation Methods

1. In symmetric multiprocessor systems:

   - Static assignment: A process is fixed to a processor from start to finish.
   - Dynamic assignment: All ready processes are in a common queue; any processor can pick up any process.

   |         | Advantages                                                   | Disadvantages                                    |
   | ------- | ------------------------------------------------------------ | ------------------------------------------------ |
   | Static  | - Low overhead                                               | - May cause processor imbalance                  |
   | Dynamic | - Avoids imbalance<br>- No extra overhead for tightly coupled systems | - Increases overhead for loosely coupled systems |

2. In asymmetric MPS:
   The OS core resides on a master; slaves only run user programs, and scheduling is done by the master.

   | Advantages      | Disadvantages                               |
   | --------------- | ------------------------------------------- |
   | - Simple system | - Low reliability<br>- Bottleneck at master |



## Process Management

### Data Structures

![progress_mgr_datastruct](res/progress_mgr_datastruct.png)

*General structure of OS control tables*

### Process Control Block (PCB)

![pcb_usage](res/pcb_usage.png)

Role:

- Marks the basic unit of independent operation
- Enables intermittent operation
- Provides information needed for process management
- Provides information needed for process scheduling
- Enables synchronization and communication with other processes

PCB organization:

- Linear

  ![progress_pcb_sequential_way](res/progress_pcb_sequential_way.png)

  *Linear representation of PCB*

- Linked

  ![progress_pcb_link_way](res/progress_pcb_link_way.png)

  *Linked queue representation of PCB*

- Indexed

  ![progress_pcb_index_way](res/progress_pcb_index_way.png)

  *Indexed organization of PCB*

### Process Attributes

The PCB keeps all the key information about the process, including:

1. Process ID (PID): A unique number assigned to each process so the operating system can identify it.
2. Process State: This shows the current status of the process, like whether it is running, waiting, or ready to execute.
3. Priority and other CPU Scheduling Information: Data that helps the operating system decide which process should run next, like priority levels and pointers to scheduling queues.
4. I/O Information: Information about input/output devices the process is using.
5. File Descriptors: Information about open files and network connections.
6. Accounting Information: Tracks how long the process has run, the amount of CPU time used, and other resource usage data.
7. Memory Management Information: Details about the memory space allocated to the process, including where it is loaded in memory and the structure of its memory layout (stack, heap, etc.).

### Process Create

![proc_creation](res/proc_creation.png)

Operating systems like Windows and Linux maintain a parent–child hierarchy of processes. Every new process is created by an already running process using system calls, making the creator the parent and the newly formed one the child.

Steps involved in creating a new process:

1. PID Assignment
2. Memory Allocation
3. PCB Initialisation

### Process Delete

Processes terminate themselves when they finish executing their last statement, after which the operating system uses the `exit()` system call to delete their context. 

A parent may terminate a process due to one of the following reasons:

1. When a task is given to the child is not required now.
2. When the child has taken more resources than their limit.
3. The parent of the process is exiting; as a result, all its children are deleted. This is called cascaded termination.

A process can be terminated/deleted in many ways:

1. Normal termination
2. Abnormal termination/Error exit
3. Termination by parent process
4. Termination by signal



## Process Execution Order

- Sequential Execution

  ![](https://g.gravizo.com/svg?
  	digraph G{
          nodesep=2;
          ranksep=1;
          rankdir=LR;
      	S1 -> S2 -> S3;
      }
  )

  In the above statements, there is the following precedence relationship: $S_1 \rightarrow S_2 \rightarrow S_3$.

- Concurrent Execution

  ![](https://g.gravizo.com/svg?
  	digraph G{
          nodesep=2;
          ranksep=1;
          rankdir=LR;
      	S1 -> S3;
      	S2 -> S3;
      	S3 -> S4;
      }
  )

  In the above statements, $S_3$ must be executed after both $S_1$ and $S_2$ have finished; $S_4$ must be executed after $S_3$; but $S_1$ and $S_2$ can be executed concurrently because they are independent of each other.



## Process Structure

![process_structure](res/process_structure.png)

- Text Section: A text or code segment contains executable instructions. It is typically a read-only section
- Stack: The stack contains temporary data, such as function parameters, returns addresses, and local variables. 
- Data Section: Contains the global variable. 
- Heap Section: Dynamically allocated memory to process during its run time.



## States

### Two-State Model

![process_two_state_model](res/process_two_state_model.png)

### Five-State Model

![process_five_state_model](res/process_five_state_model.png)

### Seven-State Model

![process_seven_state_model](res/process_seven_state_model.png)

### State Transitions

A process transitions between different states depending on its progress and the availability of system resources:

- New -> Ready

  A process is created, resources are allocated, and it is loaded into main memory.

- Ready -> Running

  The scheduler selects a ready process and assigns the CPU to it.

- Running -> Blocked(Waiting)

  The process must wait for an event or resource(e.g., I/O, user input, system call).

- Blocked -> Ready

  The event completes, or the needed resource becomes available, so the process is ready to run again.

- Running -> Ready

  The OS preempts the running process--often because a higher-priority process becomes ready.

- Blocked -> Terminated

  The process waiting for an event is aborted or killed by the OS or another process.

- (General Rule)

  A process may move between ready, running, and blocked many times, but new and terminated happen only once in its lifetime.

### Zombie Process

![zombie_process](res/zombie_process.png)

A `zombie process` is a process that has completed its execution but still remains in the process table because its parent process has not yet read its exit status.

### Orphan Process

![orphan_process](res/orphan_process.png)

An `orphan process` is a process in an operating system whose parent process has terminated or exited while the child process is still running. In simple terms, the parent process is no longer available to manage the child process, leaving it "orphaned."

### Daemon Process

![daemon_process](res/daemon_process.png)

A `daemon process` is a background process that runs independently of any user control and performs specific tasks for the system. Daemons are usually started when the system starts, and they run until the system stops.



## Process Scheduling

![process_cpu_scheduling](res/process_cpu_scheduling.png)

 - Nonpreemptive

   Once the processor is assigned to a process, it continues to run without being preempted by clock interrupts or any other reason until the process completes.

 - Preemptive

   The scheduler is allowed to suspend a running process according to certain rules and reassign the processor to another process.

### Scheduling Performance Metrics

- `Task flow time`: Time required to complete a task.
- `Scheduling flow time`: In multiprocessor systems, tasks are assigned to multiple processors; scheduling flow time is the sum of all processors' task flow times.
- `Average flow`: Scheduling flow time divided by the number of tasks. Lower average flow means higher resource utilization and throughput, and lower cost per task.
- `Processor utilization`: Sum of task flows on a processor divided by the maximum effective time unit.
- `Speedup`: Sum of busy times of all processors divided by parallel work time. More processors increase speedup and throughput, but fewer processors reduce cost and may improve overall system performance by freeing processors for other tasks.
- `Throughput`: Number of tasks completed per unit time, measured by the minimum completion time of task flows; it depends on the scheduling algorithm efficiency.

### Priority Scheduling

The process with the highest priority is selected for execution first. If there are multiple processes sharing the same priority, they are scheduled in the order they arrived, following a First-Come, First-Served approach. The chosen process is then executed, either until completion or until it is preempted, depending on whether the scheduling is preemptive or non-preemptive.

### Shortest Job First Scheduling(SJF)

The pre-emptive version of Shortest Job First (SJF) scheduling is called Shortest Remaining Time First (SRTF). In SRTF, the process with the least time left to finish is selected to run. The running process continues until it finishes or a new process with a shorter remaining time arrives, ensuring the fastest finishing process always gets priority.

### Round Robin Scheduling(RR)

![process_round_robin_scheduling](res/process_round_robin_scheduling.png)

Round Robin Scheduling is a method used by operating systems to manage the execution time of multiple processes that are competing for CPU attention.

### First Come First Serve CPU Scheduling(FCFS)

First Come, First Serve(FCFS) is one of the simplest types of CPU scheduling algorithms. The mechanics of FCFS are straightforward:

1. Arrival: Processes enter the system and are placed in a queue in the order they arrive.
2. Execution: The CPU takes the first process from the front of the queue, executes it until it is complete, and then removes it from the queue.
3. Repeat: The CPU takes the next process in the queue and repeats the execution process.

### Shortest Job First Scheduling(SJF)

Shortest Job First (SJF) or Shortest Job Next (SJN) is a scheduling process that selects the waiting process with the smallest execution time to execute next.

![process_sjf_scheduling](res/process_sjf_scheduling.png)

Estimation Formula:
$$
T_{n + 1} = \alpha \cdot t_n + (1 - \alpha) \cdot T_n
$$

- $T_{n + 1}$: Predicted burst time for the next process.
- $T_n$: Previously predicted burst time.
- $t_n$: Actual burst time of the previous process.
- $\alpha$: Smoothing factor ($0 \leq \alpha \leq 1$).

### Highest Response Ratio Next CPU Scheduling(HRRN)

This algorithm is a non-preemptive algorithm in which, HRRN scheduling is done based on an extra parameter, which is called Response Ratio. Given N processes with their Arrival times and Burst times, the task is to find the average waiting time and an average turnaround time using the HRRN scheduling algorithm.

### Multilevel Queue Scheduling(MLQ)

![process_mlq_scheduling](res/process_mlq_scheduling.png)

Multilevel Queue(MLQ) CPU Scheduling is a type of scheduling that is applied at the operating system level with the aim of sectioning types of processes and then being able to manage them properly.

### Multilevel Feedback Queue Scheduling(MLFQ)

![process_mlfq_scheduling](res/process_mlfq_scheduling.png)

Multilevel Feedback Queue Scheduling (MLFQ) CPU Scheduling is like Multilevel Queue(MLQ) Scheduling but in this process can move between the queues. And thus, much more efficient than multilevel queue scheduling.

### Conext Switch

![context_switching](res/context_switching.png)

Context switching is the process where the CPU stops running one process, saves its current state, and loads the saved state of another process so that multiple processes can share the CPU effectively.

Context switching trigger conditions:

- When a high-priority process comes to a ready state (i.e. with higher priority than the running process). 
- An Interrupt occurs.
- User and kernel-mode switch (It is not necessary though) 
- Preemptive CPU scheduling is used. 



## Inter Process Communication(IPC)

Inter-Process Communication or IPC is a mechanism that allows processes to communicate and share data with each other while they are running.

### Shared Memory

![ipc_shared_memory](res/ipc_shared_memory.png)

Processes can use shared memory for extracting information as a record from another process as well as for delivering any specific information to other processes.

### Pipe Communication

A pipe connects a reading process and a writing process for communication.

### Message Passing

![ipc_msg_passing](res/ipc_msg_passing.png)

On process sends a message and the other process receives it, allowing them to share information.

### Classical IPC Problems

1. Dining Philosophers Problem
2. Producer-Consumer Problem
3. Readers-Writers Problem
4. Sleeping Barber Problem

### Role of Synchronization in IPC

1. Preventing Race Conditions
2. Mutual Exclusion
3. Process Coordination
4. Deadlock Prevention
5. Safe Communication
6. Fairness



## Summary

### Preemptive vs Non-Preemptive Scheduling

![preemptive_vs_non_preemptive_scheduling](res/preemptive_vs_non_preemptive_scheduling.png)

| Preemptive Scheduling                                        | Non-Preemptive Scheduling                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| In this resources(CPU Cycle) are allocated to a process for a limited time. | Once resources(CPU cycles) are allocated to a process, the process holds it till it completes its burst time or switches to a waiting state. |
| The process can be interrupted in between.                   | Process can not be interrupted until it terminates itself or its time is up. |
| If a process having a high priority frequently arrives in the ready queue, a low-priority process may starve. | If a process with a long burst time is running on the CPU, then a later-coming process with less CPU burst time may starve. |
| It has overheads of scheduling the processes.                | It does not have overheads.                                  |
| Average process response time is less.                       | Average process response time is high.                       |
| Decisions are made by the scheduler and are based on priority and time slice allocation. | Decisions are made by the process itself and the OS just follows the process's instructions. |
| More a a process might be preempted when it was accessing a shared resource. | Less as a process is never preempted.                        |
| Examples of preemptive scheduling are Round Robin and Shortest Remaining Time First. | Examples of non-preemptive scheduling are First Come First Serve and Shortest Job First. |

### Comparison of CPU Scheduling Algorithms

|          Algorithm          |                          Allocation                          |                          Complexity                          |                  Average waiting time (AWT)                  | Preemption | **Starvation** |                    Performance                    |
| :-------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :--------: | :------------: | :-----------------------------------------------: |
|          **FCFS**           | According to the arrival time of the processes, the CPU is allocated. |                 Simple and easy to implement                 |                            Large.                            |     No     |       No       |                 Slow performance                  |
|           **SJF**           |          Based on the lowest CPU burst time  (BT).           |                    More complex than FCFS                    |                      Smaller than FCFS                       |     No     |      Yes       |           Minimum Average Waiting Time            |
|          **SRTF**           | Same as SJF the allocation of the CPU is based on the lowest CPU burst time (BT). But it is preemptive. |                    More complex than FCFS                    | Depending on some measures e.g., arrival time, process size, etc |    Yes     |      Yes       |     The preference is given to the short jobs     |
|           **RR**            | According to the order of the process arrives with fixed time quantum (TQ) |         The complexity depends on Time Quantum size          |      Large as compared to SJF and Priority scheduling.       |    Yes     |       No       |    Each process has given a fairly fixed time     |
|  **Priority Pre-emptive**   | According to the priority. The bigger priority task executes first |                  This type is less complex                   |                      Smaller than FCFS                       |    Yes     |      Yes       | Well performance but contain a starvation problem |
| **Priority non-preemptive** | According to the priority with monitoring the new incoming higher priority jobs |      This type is less complex than Priority preemptive      |                 Preemptive Smaller than FCFS                 |     No     |      Yes       |        Most beneficial with batch systems         |
|           **MLQ**           | According to the process that resides in the bigger queue priority |     More complex than the priority scheduling algorithms     |                      Smaller than FCFS                       |     No     |      Yes       | Good performance but contain a starvation problem |
|          **MFLQ**           |     According to the process of a bigger priority queue.     | It is the most Complex but its complexity rate depends on the TQ size |       Smaller than all scheduling types in many cases        |     No     |       No       |                 Good performance                  |



## References

[1] Tang Xiaodan, Liang Hongbing, Zhe Fengping, Tang Ziying. Computer Operating System. 3rd Edition. P32 - P115

[2] [Wikipedia - Coroutine](https://en.wikipedia.org/wiki/Coroutine)

[3] [Process Control Block in OS](https://www.geeksforgeeks.org/operating-systems/process-control-block-in-os/)

[4] [States of a Process in Operating Systems](https://www.geeksforgeeks.org/operating-systems/states-of-a-process-in-operating-systems/)

[5] [FCFS - First Come First Serve CPU Scheduling](https://www.geeksforgeeks.org/dsa/first-come-first-serve-cpu-scheduling-non-preemptive/)

[6] [Shortest Job First or SJF CPU Scheduling](https://www.geeksforgeeks.org/operating-systems/shortest-job-first-or-sjf-cpu-scheduling/)

[7] [Shortest Remaining Time First (Preemptive SJF) Scheduling Algorithm](https://www.geeksforgeeks.org/dsa/shortest-remaining-time-first-preemptive-sjf-scheduling-algorithm/)

[8] [Round Robin Scheduling in Operating System](https://www.geeksforgeeks.org/operating-systems/round-robin-scheduling-in-operating-system/)

[9] [Priority Scheduling in Operating System](https://www.geeksforgeeks.org/operating-systems/priority-scheduling-in-operating-system/)

[10] [Highest Response Ratio Next (HRRN) CPU Scheduling](https://www.geeksforgeeks.org/operating-systems/highest-response-ratio-next-hrrn-cpu-scheduling/)

[11] [Multilevel Queue (MLQ) CPU Scheduling](https://www.geeksforgeeks.org/operating-systems/multilevel-queue-mlq-cpu-scheduling/)

[12] [Multilevel Feedback Queue Scheduling (MLFQ) CPU Scheduling](https://www.geeksforgeeks.org/operating-systems/multilevel-feedback-queue-scheduling-mlfq-cpu-scheduling/)

[13] [Inter Process Communication (IPC)](https://www.geeksforgeeks.org/operating-systems/inter-process-communication-ipc/)

[14] [Introduction to Process Synchronization](https://www.geeksforgeeks.org/operating-systems/introduction-of-process-synchronization/)

[15] [Context Switching in Operating System](https://www.geeksforgeeks.org/operating-systems/context-switch-in-operating-system/)

[16] [Zombie Processes and their Prevention](https://www.geeksforgeeks.org/operating-systems/zombie-processes-prevention/)

[17] [What is an Orphan Processes?](https://www.geeksforgeeks.org/operating-systems/orphan-processes/)

[18] [Process Creation and Deletions in Operating Systems](https://www.geeksforgeeks.org/operating-systems/process-creation-and-deletions-in-operating-systems/)

[19] [Process in Operating System](https://www.geeksforgeeks.org/operating-systems/process-in-operating-system/)