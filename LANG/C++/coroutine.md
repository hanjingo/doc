English | [中文版](coroutine_zh.md)

# C++ Coroutines

[TOC]



This note summarizes the C++ coroutine model (C++20 and practical extensions), explains the main concepts (coroutine frame, promise_type, coroutine_handle, awaiter/awaitable), and shows small illustrative patterns: generators and simple asynchronous tasks. It also covers lifetime and resource management, common pitfalls, and best practices for production code. The goal is a compact, practical reference rather than an exhaustive tutorial.

## What is a coroutine?

A coroutine is a function that can suspend execution to be resumed later. In C++, coroutines are "stackless": the compiler transforms a function marked as a coroutine into a coroutine frame that stores local state across suspensions. Coroutines expose three new keywords: co_await, co_yield, and co_return.

Key properties:
- Suspension points: places where execution may suspend (co_await/co_yield).
- Resumability: external code can resume a suspended coroutine via a handle.
- Lazy or eager semantics depending on the promise and awaitable implementations.

## Core types and responsibilities

- coroutine_handle<T>: opaque handle to the coroutine frame; can resume(), destroy(), or access the promise object.
- promise_type: a user‑provided type (nested inside the return type) that controls the coroutine’s behavior. It defines methods like get_return_object(), initial_suspend(), final_suspend(), return_void()/return_value(), and unhandled_exception().
- Awaitable / Awaiter: an awaitable is an expression usable with co_await. The awaiter must provide:
	- await_ready(): bool — whether to suspend immediately.
	- await_suspend(coroutine_handle<>): called if await_ready() is false; may arrange continuation.
	- await_resume(): returns the result after resumption.

The compiler rewrites a coroutine into state machine code that uses these hooks.

## Lifetime and flow (high level)

1. Call to a coroutine creates the coroutine frame; the promise is constructed.
2. Compiler calls promise.initial_suspend(); if it returns suspend_always, the coroutine is suspended immediately (caller receives a handle). If suspend_never, the coroutine runs until the first suspension point.
3. Each co_await expression evaluates its awaitable, calls await_ready(); if false, await_suspend() runs and control returns to the caller (suspension). When resumed, await_resume() provides the awaited value.
4. When coroutine completes, promise.final_suspend() is called; the caller can inspect results via the promise’s get_return_object().
5. The coroutine frame is destroyed either by calling coroutine_handle::destroy() or automatically when the last owner releases it.

## Minimal examples (sketches)

1) Generator (simple, single‑threaded)

// conceptual sketch — real implementations require more boilerplate
struct generator {
	struct promise_type {
		T current;
		generator get_return_object() { return generator{/*...*/}; }
		suspend_always initial_suspend() { return {}; }
		suspend_always final_suspend() noexcept { return {}; }
		suspend_always yield_value(T value) {
			current = value; return {};
		}
		void return_void() {}
		void unhandled_exception() { std::terminate(); }
	};
	// iterator-like interface that resumes the coroutine to obtain next value
};

Usage:
for (auto v : generator_of_ints()) { /* use v */ }

2) Simple task<T> (async result)

// promise_type stores a std::promise/std::future or similar
struct task<T> {
	struct promise_type {
		std::promise<T> p;
		task get_return_object() { return task{p.get_future()}; }
		suspend_never initial_suspend() { return {}; }
		suspend_never final_suspend() noexcept { return {}; }
		void return_value(T v) { p.set_value(std::move(v)); }
		void unhandled_exception() { p.set_exception(std::current_exception()); }
	};
};

Then an async function can co_await other tasks and co_return a value that ends up in the future.

## Awaitables and interoperability

- The standard library provides hooks for awaitables; many libraries expose adapter awaiters to bridge callback APIs to coroutines (e.g., converting an async callback into an awaitable that suspends until the callback fires).
- co_await works with types that implement the awaiter protocol or provide a customization point (operator co_await) that returns an awaiter.

## Resource management and destruction

- Because coroutines allocate frames on the heap (often via operator new for the frame), callers must ensure destroy() is invoked when the coroutine is no longer needed to avoid leaks. Many wrapper types (task, generator) perform RAII to manage the handle lifecycle.
- final_suspend() gives a last chance to schedule cleanup or transfer ownership of the continuation.

## Common pitfalls and best practices

- Don’t let exceptions escape a suspension point unhandled; implement unhandled_exception in promise_type.
- Avoid blocking inside coroutines; use co_await for asynchronous waits to keep the event loop responsive.
- Be explicit about allocation and ownership of the coroutine handle; prefer RAII wrappers that call destroy() automatically.
- Keep the promise_type lightweight; expensive state in the promise increases frame size and allocation cost.
- Use std::suspend_always / std::suspend_never intentionally to control eager vs lazy start behavior.

## Libraries and ecosystem

- Several libraries provide higher‑level coroutine utilities: cppcoro, libunifex, folly (Resume/Executor primitives), Asio with coroutine support (awaitable I/O), and ranges/generator helpers.
- Compiler support: major compilers (gcc, clang, MSVC) provide coroutine support; check versions and flags for production builds.

## When to use coroutines

- Use coroutines to express asynchronous control flow in a linear, readable way (e.g., async I/O, pipelines, generators).
- Prefer coroutines when you need composability of async operations and want to avoid callback hell or complex state machines.

# Further reading

- C++20 standard sections on coroutines (search for "coroutine" and promise_type semantics).
- Lewis Baker — cppcoro examples and documentation.
- Victor Luchangco / Gor Nishanov talks and notes on coroutine design and compiler transformations.
