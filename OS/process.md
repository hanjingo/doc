English | [中文版](process_zh.md)

# Process

[TOC]



A process is an independent unit for resource allocation and scheduling in the system. Each process has its own independent memory space, and different processes communicate via inter-process communication. Processes are relatively heavy, context switching overhead is large, but they are more stable than threads.

## Definition and Characteristics

Definition:

- A process is an execution of a program.
- A process is the activity of a program and its data being executed sequentially on a processor.
- A process is a program with independent functionality running on a data set; it is an independent unit for resource allocation and scheduling in the system.

Characteristics:

- Dynamic: The essence of a process is the execution of a process entity, so dynamicity is the most fundamental characteristic.
- Concurrency: Multiple process entities coexist in memory and can run simultaneously within a period.
- Independence: A process entity can run independently, obtain resources independently, and accept investigation independently.
- Asynchrony: Processes run asynchronously, i.e., they progress at their own unpredictable speeds.



## Precedence Graph

A `Precedence Graph` is a directed acyclic graph (DAG) used to describe the execution order between processes.

The precedence relationship between processes (or programs) can be denoted as "$\rightarrow$". If there is a precedence relationship between $P_i$ and $P_j$, it can be written as $(P_i, P_j)\in \rightarrow$ or $P_i \rightarrow P_j$, meaning $P_i$ must complete before $P_j$ starts. $P_i$ is the direct predecessor of $P_j$, and $P_j$ is the direct successor of $P_i$.



## Execution Order

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



## Process Management

### Data Structures

![progress_mgr_datastruct](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_mgr_datastruct.png)

*General structure of OS control tables*

### Process Control Block (PCB)

Role:

- Marks the basic unit of independent operation
- Enables intermittent operation
- Provides information needed for process management
- Provides information needed for process scheduling
- Enables synchronization and communication with other processes

PCB organization:

- Linear

  ![progress_pcb_sequential_way](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_pcb_sequential_way.png)

  *Linear representation of PCB*

- Linked

  ![progress_pcb_link_way](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_pcb_link_way.png)

  *Linked queue representation of PCB*

- Indexed

  ![progress_pcb_index_way](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_pcb_index_way.png)

  *Indexed organization of PCB*



## State Management

### Basic States

![progress_base_stat_transform](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_base_stat_transform.png)

 *Five basic states and transitions of a process*

- `Ready` state
- `Running` state
- `Blocked` state
- `Created` state
- `Terminated` state

### State Transitions

![progress_stat_transform](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_stat_transform.png)

*Process state diagram with create, terminate, and suspend states*

- Creation

  1. Request a blank PCB, obtain a unique identifier for the new process, and get a blank PCB from the PCB pool.
  2. Allocate the resources needed for the new process to run, including various physical and logical resources such as memory, files, I/O devices, and CPU time.
  3. Initialize the process control block (PCB), including:
     - Initialize identification information
     - Initialize processor state information
     - Initialize processor control information
  4. If the ready queue can accept a new process, insert the new process into the ready queue.

- Termination

  1. According to the identifier of the terminated process, retrieve its PCB from the PCB pool and read its state.
  2. If the terminated process is in the running state, immediately terminate its execution and set the scheduling flag to true, indicating that rescheduling should occur after the process is terminated.
  3. If the process has child or descendant processes, terminate all of them as well to prevent them from becoming uncontrollable processes.
  4. Return all resources owned by the terminated process either to its parent process or to the system.
  5. Remove the terminated process (PCB) from its queue (or list) and wait for other programs to collect information.

- Blocking

  1. Immediately stop execution, change the previous state in the PCB from running to blocked, and insert the PCB into the blocked queue.
  2. If the system has multiple blocked queues for different events, insert the process into the blocked queue corresponding to the same event.
  3. Reschedule, assign the processor to another ready process, and perform a context switch.

- Wakeup

  1. Remove the blocked process from the blocked queue for the event it was waiting for, change its state in the PCB from blocked to ready, and insert the PCB into the ready queue.

- Suspend

  1. If the process is in the active ready state, change it to suspended ready.
  2. For a process in the active blocked state, change it to suspended blocked.
  3. To facilitate inspection by the user or parent process, copy the PCB of the process to a specified memory area.
  4. If the suspended process is running, switch to the scheduler for rescheduling.

- Activate

  1. Load the process from external storage into memory, check its current state, and if it is suspended ready, change it to active ready; if it is suspended blocked, change it to active blocked.
  2. If preemptive scheduling is used, whenever a suspended ready process is activated and inserted into the ready queue, check whether rescheduling is needed.



## Process Scheduling

 - Nonpreemptive Mode

   Once the processor is assigned to a process, it continues to run without being preempted by clock interrupts or any other reason until the process completes.

 - Preemptive Mode

   The scheduler is allowed to suspend a running process according to certain rules and reassign the processor to another process.

### Round Robin Scheduling Algorithm

All ready processes are arranged in a ready queue according to the FCFS (First-Come, First-Served) policy. An interrupt is set to occur at regular intervals to activate the process scheduler, which assigns the CPU to the process at the head of the queue and lets it execute for a time slice. When it finishes its time slice, the CPU is assigned to the new head of the ready queue, which also executes for a time slice. This ensures that all processes in the ready queue can obtain a time slice of CPU time within a defined period.

![progress_schedule_RR](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_schedule_RR.png)

*Effect of time slice size on response time*

### Priority Scheduling Algorithm

 - Nonpreemptive priority scheduling algorithm

   After the processor is assigned to the highest-priority process in the ready queue, that process continues to execute until it completes.

 - Preemptive priority scheduling algorithm

   The processor is assigned to the highest-priority process in the ready queue. If another process with a higher priority appears, the scheduler will assign the processor to the newly arrived highest-priority process.

### Multiqueue Scheduling Algorithm

The multiqueue scheduling algorithm splits the system's single ready queue into several queues, with different types or categories of processes fixed in different ready queues. Different ready queues use different scheduling algorithms. Processes in a single ready queue can have different priorities, and the ready queues themselves can also have different priorities.

### Multilevel Feedback Queue Scheduling Algorithm

![progress_schedule_mfq](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_schedule_mfq.png)

*Multilevel feedback queue scheduling algorithm*

1. Set up multiple ready queues, each with decreasing priority.
2. Each queue uses FCFS.
3. Schedule by queue priority.

### Fairness-based Scheduling Algorithm

Ensures all users get the same CPU time or the required time proportion.



## Real-time Process Scheduling

1. Nonpreemptive scheduling algorithms

   - Nonpreemptive round robin
   - Nonpreemptive priority

2. Preemptive scheduling algorithms

   - Clock-interrupt-based preemptive priority

    After a real-time task arrives, if its priority is higher than the current task's priority, the processor is not immediately preempted from the current task. Instead, the scheduler waits until a clock interrupt occurs to preempt the current task and assign the processor to the newly arrived higher-priority task.

   - Immediate preemption priority

    Once an external interrupt occurs, as long as the current task is not in a critical section, the execution of the current task can be immediately preempted, and the processor is assigned to the urgent task requesting the interrupt.

### Earliest Deadline First (EDF) Algorithm

- Nonpreemptive for aperiodic real-time tasks

  ![progress_schedule_EDF1](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_schedule_EDF1.png)

  *EDF algorithm for nonpreemptive scheduling*

- Preemptive for periodic real-time tasks

  ![progress_schedule_EDF2](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_schedule_EDF2.png)

  *Example of earliest deadline first algorithm for preemptive scheduling*

### Least Laxity First (LLF) Algorithm

The priority of a task is determined based on its urgency (or laxity).

![progress_schedule_ELLF](/usr/local/src/github.com/hanjingo/doc/OS/res/progress_schedule_ELLF.png)

*Scheduling with the ELLF algorithm*



## Process Synchronization

Rules for synchronization mechanisms:

- `Enter when idle`: If no process is in the critical section, a requesting process should be allowed to enter immediately.
- `Wait when busy`: If a process is in the critical section, others must wait to ensure mutual exclusion.
- `Bounded waiting`: Every process should be able to enter its critical section within a bounded time.
- `Yield while waiting`: A process unable to enter its critical section should release the CPU immediately.

### Hardware Synchronization

Disable interrupts before lock testing, enable after lock acquired.

### Semaphore Mechanism

- Integer semaphore
- Record semaphore
- AND-type semaphore
- Semaphore set



## Process Communication

### Shared-Memory System

TODO

### Pipe Communication System

A pipe connects a reading process and a writing process for communication.

### Message Passing System

Message passing is a high-level communication method.

### Client-Server System

TODO



## References

[1] Tang Xiaodan, Liang Hongbing, Zhe Fengping, Tang Ziying. Computer Operating System. 3rd Edition. P32 - P115

[2] [Wikipedia - Coroutine](https://en.wikipedia.org/wiki/Coroutine)

[3] [Process Control Block in OS](https://www.geeksforgeeks.org/operating-systems/process-control-block-in-os/)