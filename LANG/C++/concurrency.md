English | [中文版](concurrency_zh.md)

# C++ Concurrency — practical summary

[TOC]



This note collects the essential C++ concurrency primitives and patterns (C++11 and later) with pragmatic tips, corrected wording, and small example sketches. It is distilled from Anthony Williams' "C++ Concurrency in Action" and the existing Chinese notes. The objective is a concise, accurate reference covering threads, mutexes, condition variables, futures/promises, atomics, lock‑free considerations, and common performance pitfalls.

## Threads and std::thread

- Creating a thread: construct a `std::thread` with a callable. Arguments are copied into the new thread by default.
	- Prefer brace initialization: `std::thread t{func, arg1, arg2};`.
- Joining and detaching:
	- `t.join()` waits for completion (call once). If an exception may be thrown before join, use RAII (guard) or try/catch to ensure join/detach.
	- `t.detach()` allows the thread to run independently (no direct synchronization with the caller).
- Passing parameters safely: use `std::ref` to pass references, or `std::move` with smart pointers for transfer of ownership.
- Move semantics: `std::thread` is movable but not copyable — transfer ownership with `std::move`.
- Hardware concurrency: `std::thread::hardware_concurrency()` gives a hint for the number of concurrent threads supported.

Minimal RAII guard sketch:

```c++
class thread_guard {
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) : t(t_) {}
	~thread_guard() { if (t.joinable()) t.join(); }
	thread_guard(thread_guard const&)=delete;
};
```

## Mutexes and locks

- `std::mutex` protects shared data; prefer scoped locking (`std::lock_guard` / `std::unique_lock`) to avoid forgetting unlocks.
- `std::lock_guard` is simple RAII for exclusive locks; `std::unique_lock` is more flexible (defer_lock, try_lock, release).
- Avoid deadlocks by locking in a consistent order, minimizing lock scope, and avoiding calling user code while holding locks.
- Use `std::lock` to acquire multiple locks without deadlock.

Example (unique_lock transfer):

```c++
std::unique_lock<std::mutex> get_lock() {
	std::unique_lock<std::mutex> lk(m);
	// ...
	return lk; // moves out the unique_lock
}

void f() {
	auto lk = get_lock();
	// use lk
}
```

## Condition variables

- `std::condition_variable` synchronizes threads by blocking until notified. Use with a `std::unique_lock<std::mutex>`.
- Prefer `cv.wait(lock, predicate)` to avoid spurious wakeups.
- Use `notify_one()` / `notify_all()` depending on the scenario.

Typical pattern:

```c++
std::mutex m;
std::condition_variable cv;
std::deque<Task> q;

void producer() {
	{
		std::lock_guard<std::mutex> lk(m);
		q.push_back(...);
	}
	cv.notify_one();
}

void consumer() {
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk, []{ return !q.empty(); });
	auto item = q.front(); q.pop_front();
}
```

`std::condition_variable_any` allows other lock types but is slower; prefer `std::condition_variable` when possible.

## Futures, promises, and async

- `std::future<T>` provides a single-use handle to a result produced elsewhere (std::async, std::packaged_task, std::promise).
- `std::async` has launch policies: `std::launch::async` (new thread) or `std::launch::deferred` (call on `get()`).
- `std::promise` + `std::future` form a one‑time channel for passing a value or exception between threads.
- `std::packaged_task` wraps a callable and produces a future when invoked.

Prefer `std::async` for simple async tasks; use `std::packaged_task` or explicit thread pools for more control.

## std::atomic and memory ordering

- `std::atomic<T>` provides lock‑free atomic operations for many scalar and pointer types. It is not copyable.
- Common member operations: `load`, `store`, `exchange`, `compare_exchange_weak`, `compare_exchange_strong`, `fetch_add`, `fetch_sub`.
- `std::atomic_flag` is a minimal spinlock primitive with `test_and_set` and `clear`.

Memory orders (brief):
- `memory_order_relaxed`: no synchronization, only atomicity.
- `memory_order_acquire` / `memory_order_release`: establish acquire‑release synchronizes-with relationships.
- `memory_order_acq_rel`: for read‑modify‑write.
- `memory_order_seq_cst`: sequential consistency (strongest).

Use relaxed ordering only with careful reasoning. Default to `seq_cst` or acquire/release unless performance requires weaker orders.

Example CAS:

```c++
std::atomic<int> a{0};
int expected = 0;
if (a.compare_exchange_strong(expected, 1)) {
	// we set a from 0 to 1
} else {
	// expected now holds the observed value
}
```

### Atomics: patterns and pitfalls

- Beware ABA when using CAS on pointers; consider hazard pointers or epoch reclamation for safe memory reclamation.
- Use `std::atomic_thread_fence` to enforce ordering across non‑atomic operations when necessary.

## Lock‑free programming (overview)

- Lock‑free structures (queues, stacks) increase concurrency but are complex and error‑prone. Prefer well‑tested library implementations (Boost.Lockfree, folly, libcds) unless you need a custom solution.
- Key challenges: ABA, safe memory reclamation, and subtle ordering bugs.

## Performance pitfalls and tuning

- False sharing: align hot, frequently written data to separate cache lines to avoid cache ping‑pong.
- Over‑subscription: avoid creating far more active threads than CPU cores; use a thread pool sized to workload and blocking characteristics.
- Cache locality and data layout: prefer contiguous data structures for throughput.
- Measure before optimizing; use profiling and microbenchmarks.

## Common patterns and examples (sketches)

1) Parallel for_each (conceptual): split range, run worker tasks, collect results, and join threads or use a task queue.

2) Parallel find (sketch): have workers search subranges with an atomic flag to stop other threads when a match is found.

See the Chinese note for longer code excerpts; for production code prefer documented, tested implementations.

## Debugging and testing concurrency

- Add deterministic tests when possible (stress tests with reproducible seeds).
- Use ThreadSanitizer (TSAN) to detect data races during testing.
- Log and monitor retry/retransmit metrics to find contention hotspots.

## When to use which primitive

- High‑level tasks / futures: `std::async`, `std::future` for simple cases.
- Low‑level synchronization: `std::mutex`, `std::condition_variable`.
- High‑performance, fine‑grained concurrency: `std::atomic` and lock‑free algorithms (use libraries first).

## References

- Anthony Williams — C++ Concurrency in Action
- cppreference.com — concurrency reference
- Library docs: Boost.Lockfree, Folly, libunifex, Asio (awaitable I/O)
