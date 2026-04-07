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



#### Detecting a cycle in a linked list.

```c++
struct node
{
    int val;
    node* next;
    node(int x) : val{x}, next{nullptr} {}
};

bool is_cycled(node* head)
{
    if (!head || !head->next)
        return false;

    node* slow = head;
    node* fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;       // move 1 step
        fast = fast->next->next; // move 2 step
        if (slow == fast)
            return true;
    }

    return false;
}
```

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | O(1)            | O(1)             |
| Average Case | O(n)            | O(1)             |
| Worst Case   | O(n)            | O(1)             |
