# chapter10 Testing and debugging multithreaded applications


<!-- vim-markdown-toc GFM -->

* [10.1 Types of concurrency-related bugs](#101-types-of-concurrency-related-bugs)
    - [10.1.1 Unwanted blocking](#1011-unwanted-blocking)
    - [10.1.2 Race conditions](#1012-race-conditions)
* [10.2 Techniques for locating concurrency-related bugs](#102-techniques-for-locating-concurrency-related-bugs)
    - [10.2.1 Reviewing code to locate potential bugs](#1021-reviewing-code-to-locate-potential-bugs)
    - [10.2.2 Locating concurrency-related bugs by testing](#1022-locating-concurrency-related-bugs-by-testing)
    - [10.2.3 Designing for testability](#1023-designing-for-testability)
    - [10.2.4 Multithreaded testing techniques](#1024-multithreaded-testing-techniques)
    - [10.2.5 Structuring multithreaded test code](#1025-structuring-multithreaded-test-code)
    - [10.2.6 Testing the performance of multithreaded code](#1026-testing-the-performance-of-multithreaded-code)
* [10.3 Summary](#103-summary)

<!-- vim-markdown-toc -->



## 10.1 Types of concurrency-related bugs

Typically, these concurrency-related bugs fall into two primary categories:

- Unwanted blocking
- Race conditions

### 10.1.1 Unwanted blocking

- `Deadlock`
- `Livelock`
- `Blocking on I/O or other external input`

### 10.1.2 Race conditions

many concurrency bugs are due to race conditions. In particular, race conditions often cause the following types of problems:

- `Data races` 
- `Broken invariants` 
- `Lifetime issues` 



## 10.2 Techniques for locating concurrency-related bugs

### 10.2.1 Reviewing code to locate potential bugs

**QUESTIONS TO THINK ABOUT WHEN REVIEWING MULTITHREADED CODE**

- Which data needs to be protected from concurrent access?
- How do you ensure that the data is protected?
- Where in the code could other threads be at this time?
- Which mutexes does this thread hold?
- Which mutexes might other threads hold?
- Are there any ordering requirements between the operations done in this threed and those done in another?How are those requirements enforced?
- Is the data loaded by this thread still valid? could it have been modified by other threads?
- If you assume that another thread could be modifying the data, what would that mean and how could you ensure that this never happens?

### 10.2.2 Locating concurrency-related bugs by testing

Having thought about all these scenarios and more, you then need to consider additional factors about the test environment:

- What you mean by "multiple threads" in each case;
- Whether there are enough processing cores in the system for each thread to run on its own core
- Which processor architectures the tests should be run on;
- How you ensure suitable scheduling for the "while" parts of your test.

### 10.2.3 Designing for testability

In general, code is easier to test if the following factors apply:

- The responsibilities of each function and class are clear.
- The functions are short and to the point.
- Your tests can take complete control of the environment surrounding the code being tested.
- The code that performs the particular operation being tested is close together rather than spread throughout the system.
- You thought about how to test the code before you wrote it.

### 10.2.4 Multithreaded testing techniques

**BRUTE-FORCE TESTING**

The downside to brute-force testing is that it might give you flase confidence.

**COMBINATION SIMULATION TESTING**

**DETECTING PROBLEMS EXPOSED BY TESTS WITH A SPECIAL LIBRARY**

### 10.2.5 Structuring multithreaded test code

you need to identify the distinct parts of each test:

- The general setup code that must be executed before anything else;
- The thread-specific setup code that must run on each thread;
- The actual code for each thread that you desire to run concurrently;
- The code to be run after the concurrent execution has finished, possibly including assertions on the state of the code.

### 10.2.6 Testing the performance of multithreaded code



## 10.3 Summary


