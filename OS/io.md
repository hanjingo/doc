
# Input/Output (I/O)

[TOC]

This note summarizes key concepts about I/O from a programmer's perspective, following the style and emphasis of CS:APP. It explains the Unix I/O abstraction, the kernel data structures used to represent open files, buffering and caching, synchronous vs asynchronous I/O, I/O multiplexing (select/poll/epoll), DMA and interrupts, and practical performance and correctness tips.

## I/O as Files

Unix treats devices and many other communication endpoints as files: a uniform interface for reading and writing data. The common system calls are read, write, open, close, lseek, pread/pwrite, and variants such as readv/writev for scatter/gather.

This single-file abstraction lets programmers manipulate diverse resources (regular files, pipes, sockets, character devices, block devices) with the same basic API, while device-specific behavior is handled inside the kernel or device driver.

## Kernel data structures for open files

When a process opens a file, the kernel builds/links several objects to represent the operation. A simplified view is:

- Process file descriptor table: a per-process array mapping small integers (file descriptors) to pointers to open-file entries.
- System-wide open-file table (open-file entries): each entry holds the current file offset, access mode flags, reference count, and a pointer to an underlying vnode/inode or device object.
- Vnode / inode / file object: represents the underlying filesystem object (inode on Unix), containing metadata (owner, permissions, size, timestamps) and pointers to the on-disk blocks.

The separation makes it possible to have multiple descriptors (possibly in different processes) that share the same open-file entry (e.g., after fork), or to have distinct entries with their own offsets (e.g., after dup2 or separate opens).

Refer to the illustrations in `res/open_file.png` and `res/file_sharing.png` for a visual of these relationships.

## Buffering, caching, and the page cache

To reduce device I/O overhead, modern kernels use buffering and caching layers:

- Page cache (or buffer cache): file data read from disk is cached in memory in pages. Subsequent reads may be satisfied from memory without hitting the disk. Writes are often buffered and flushed later (write-back) unless the file was opened with synchronous flags.
- Block/device buffers: block devices (disks) may have additional buffering inside the driver or hardware.

Important implications:

- Consistency: applications must use fsync or O_SYNC if they require durability guarantees; without that, buffered writes may be lost on crash.
- Memory pressure: the page cache competes with application memory; under memory pressure the kernel reclaims cache pages.
- Direct I/O and O_DIRECT: bypass the page cache to avoid copying and caching for workloads that manage their own buffering (databases, some high-performance apps).

## Blocking vs non-blocking I/O

- Blocking I/O: a read or write call blocks the calling thread until data is available or the operation completes.
- Non-blocking I/O: file descriptors can be configured with O_NONBLOCK; calls return immediately with EAGAIN/EWOULDBLOCK if they would block.

Non-blocking I/O is useful in event-driven programs, but it requires handling partial reads/writes and retry logic.

## I/O Multiplexing: select, poll, epoll

I/O multiplexing lets a single thread wait for events on many descriptors.

- select: portable but has limits (fixed FD_SETSIZE, O(N) scanning). Not suitable for very large numbers of descriptors.
- poll: addresses FD_SET size limits but still O(N) and requires rebuilding event arrays.
- epoll (Linux): scalable, edge-triggered or level-triggered modes, efficient for large numbers of descriptors because it avoids scanning busy lists on every call.

When to use multiplexing vs threads:

- Multiplexing: fits event-driven architectures and avoids per-connection threads; good for workloads with many concurrent, mostly-idle connections.
- Threads: easier to program with blocking I/O; each thread blocks independently. On many-core systems, threads can exploit parallelism but introduce synchronization complexity.

Trade-offs:

- Event-driven code can be more complex (state machines, careful partial I/O handling).
- Thread-per-connection designs can simplify logic but incur higher context-switch and memory costs for many connections.

## Asynchronous I/O and modern interfaces

Historically, POSIX AIO and Linux aio provided kernel-assisted async I/O but had portability and implementation limitations. More recent approaches include:

- io_uring (Linux): a powerful, efficient API based on submission and completion queues that supports true async operations, zero-copy where possible, and reduced syscall overhead.
- platform-specific async frameworks: Windows IOCP, BSD kqueue, etc.

Use cases for async I/O: high-performance servers, storage systems, and programs that want to overlap I/O and computation without many threads.

## DMA, interrupts, and device drivers

At the hardware level, devices often use DMA (Direct Memory Access) to transfer data between device memory and system memory without continuous CPU intervention. Key points:

- Interrupts notify the CPU that an I/O event completed (or needs service). Drivers run interrupt handlers to schedule work and wake blocked processes.
- For high throughput, drivers and hardware use techniques like scatter/gather DMA, NIC receive/transmit rings, and interrupt mitigation (coalescing).

Device drivers abstract these details and present a standardized interface (character/block device semantics, or socket-like APIs for network devices).

## Scatter/gather and vectored I/O

System calls like readv/writev let you perform scatter/gather I/O (read into multiple buffers or write from multiple buffers) in a single syscall. These reduce copies and syscalls for common patterns (e.g., header+payload writes).

## File locking and concurrency

- Advisory locks: fcntl locks are advisory on Unix: cooperating processes must respect them.
- flock is a simpler flock-style lock; semantics differ across systems.

Locks are about coordinating access; they do not replace careful handling of partial I/O or atomicity where required.

## Performance and correctness tips

- Use the right abstraction: regular file I/O, sockets, and device I/O have different performance characteristics.
- Minimize syscalls: batch I/O when possible (writev, readv, sendmmsg, recvmmsg).
- Prefer non-blocking + event-driven or async APIs for high-concurrency servers.
- Measure and tune: use tools like iostat, sar, perf, and strace to find bottlenecks.
- Use O_DIRECT or tuned fsync policies for workloads that need predictable latency (but be careful: O_DIRECT imposes alignment constraints).
- Be explicit about durability: use fsync/fdatasync or O_SYNC when you need crash-consistent behavior.

## I/O multiplexing: pros and cons (summary)

Pros:

- Event-driven designs provide fine-grained control and can be more efficient for many concurrent idle connections.
- Single-threaded event loops avoid many synchronization bugs and reduce context-switch overhead.

Cons:

- Event-driven code is more complex to write and reason about.
- Single-threaded event loops do not automatically utilize multiple CPU cores; combining them with thread pools or multiple event loops is common.

## Additional references

- Randal E. Bryant and David R. O'Hallaron, Computer Systems: A Programmer's Perspective (CS:APP), 3rd ed.
- Linux man pages: open(2), read(2), write(2), select(2), poll(2), epoll(7), aio(7), io_uring(7).

<!-- End of I/O note -->
