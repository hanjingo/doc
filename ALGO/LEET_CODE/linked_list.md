# Linked List Problems

[TOC]



### Reverses a linked list iteratively using three pointers: current, previous, and next.

```c++
void reverse_linked_list(singly_linked_list& li) 
{
    list_node* previous = nullptr;
    list_node* current = li.head;
    list_node* next = nullptr;
    while (current) 
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    li.head = previous;
}
```

Complexity Analysis:

- Time complexity: $O(n)$
- Space complexity: $O(1)$



### Finds the middle of a linked list using the slow and fast pointer technique.

```c++
int find_linked_list_middle(const singly_linked_list& li)
{
    // calc the length
    int n = 0;
    for (list_node* curr = li.head; curr; curr = curr->next)
        ++n;

    // find middle
    n /= 2;
    for (list_node* curr = li.head; curr; curr = curr->next)
    {
        if (n < 1)
            return curr->val;

        --n;
    }
    return -1;
}

```

Complexity Analysis:

- Time complexity: $O(n)$
- Space complexity: $O(1)$
