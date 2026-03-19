# Recursion

[TOC]



The process in which a function calls itself directly or indirectly is called recursion and the corresponding function is called a recursive function.

## Benefit

- Recursion helps in logic building. Recursive thinking helps in solving complex problems by breaking them into smaller subproblems.
- Recursive solutions work as a basic for Dynamic Programming and Divide and Conquer algorithms.
- Certain problem can be solved quite easily using recursion.



## Base Condition

A recursive program stops at a base condition. There can be more than one base conditions in a recursion.



## Direct And Indirect Recursive Function

A function is called **direct recursive** if it calls itself directly during its execution. 



## Disadvantage

### Stack Overflow Error

If the base case is not reached or not defined, then the stack overflow problem may arise. For example:

```c++
int fact(int n)
{
    if(n == 100) // if n < 100 at the first time, n will never reach 100
        return 1;
    else
        return n * fact(n - 1);
}
```





## Reference

[1] [Introduction to Recursion](https://www.geeksforgeeks.org/dsa/introduction-to-recursion-2/)