# Memory Manage

[TOC]



## Virtual Memory

`Virtual memory` is an abstraction that provides each process with the illusion that it has exclusive use of the main memory. Each process has the same uniform view of memory, which is known as its `virtual address space`.

![virtual_addr](res/virtual_addr.png)

- `Program code and data`. Code begins at the same fixed address for all processes, followed by data locations that correspond to global C variables.
- `Heap`. Unlike the code and data areas, which are fixed in size once the process begins running, the heap expands and contracts dynamically at run time as a result of calls to C standard library routines such as `malloc` and `free`.
- `Shared libraries`. It is an area that holds the code and data for `shared libraries` such as the C standard library and the math library.
- `Stack`. At the top of the user's virtual address space is the `user stack` that the compiler uses to implement function calls.
- `Kernel virtual memory`. It is reserved for the kernel. Application programs are not allowed to read or write the contents of this area or to directly call functions defined in the kernel code. Instead, they must invoke the kernel to perform these operations.



## Reference

[1] Randal E. Bryant, David R. O'Hallaron . COMPUTER SYSTEMS: A PROGRAMMER'S PERSPECTIVE . 3ED
