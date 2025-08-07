# Exceptional Control Flow

[TOC]



An `exception` is an abrupt change in the control flow in response to some change in the processor's state.

## ECF

In general, we refer to these abrupt changes as `exceptional control flow` (ECF). ECF occurs at all levels of a computer system.

![anatomy_of_exception](res/anatomy_of_exception.png)



## Exception table

In any case, when the processor detects that the event has occurred, it makes an indirect procedure call (the exception), through a jump table called an `exception table`, to an operating system subroutine (the `exception handler`) that is specifically designed to process this particular kind of event. When the exception handler finishes processing, one of three things happens, depending on the type of event that caused the exception:

1. The handler returns control to the current instruction $I_{curr}$, the instruction that was executing when the event occurred.
2. The handler returns control to $I_{next}$, the instruction that would have executed next had the exception not occurred.
3. The handler aborts the interrupted program.

![exception_tbl](res/exception_tbl.png)

An exception is akin to a procedure call, but with some important differences:

- As with a procedure call, the processor pushes a return address on the stack before branching to the handler. However, depending on the class of exception, the return address is either the current instruction (the instruction that was executing when the event occurred) or the next instruction (the instruction that would have executed after the current instruction had the event not occurred).
- The processor also pushes some additional processor state onto the stack that will be necessary to restart the interrupted program when the handler returns.
- When control is being transferred from a user program to the kernel, all of these items are pushed onto the kernel's stack rather than onto the user's stack.
- Exception handlers run in `kernel mode`, which means they have complete access to all system resources.



## Logical control flow

![logic_ctl_flow](res/logic_ctl_flow.png)

A logical flow whose execution overlaps in time with another flow is called a `concurrent flow`, and the two flows are said to `run concurrently`. More precisely, flows $X$ and $Y$ are concurrent with respect to each other if and only if $X$ begins after $Y$ begins and before $Y$ finishes, or $Y$ begins after $X$ begins and before $X$ finishes.