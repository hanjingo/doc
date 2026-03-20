English | [中文版](ansys_linklist_zh.md)

# Redis Source Code Analysis - Linked List

[TOC]


## API

| Function             | Purpose                                                           | Time Complexity                                |
| -------------------- | ----------------------------------------------------------------- | ----------------------------------------------- |
| listSetDupMethod     | Set the list node value duplication function                      | Dup function is available via the list's `dup` property, $O(1)$ |
| listGetDupMethod     | Return the currently used node value duplication function         | $O(1)$                                        |
| listSetFreeMethod    | Set the list node value deallocation function                     | Free function is available via the list's `free` property, $O(1)$ |
| listGetFree          | Return the currently used node value deallocation function        | $O(1)$                                        |
| listGetMatchMethod   | Return the currently used node value comparison function         | $O(1)$                                        |
| listLength           | Return the length of the list (number of nodes)                   | Length is available via the list's `len` property, $O(1)$        |
| listFirst            | Return the head node of the list                                  | Head is available via the list's `head` property, $O(1)$        |
| listLast             | Return the tail node of the list                                  | Tail is available via the list's `tail` property, $O(1)$        |
| listPrevNode         | Return the previous node of a given node                          | Prev is available via node's `prev` property, $O(1)$            |
| listNextNode         | Return the next node of a given node                              | Next is available via node's `next` property, $O(1)$            |
| listNodeValue        | Return the value currently stored in a given node                 | Value is available via node's `value` property, $O(1)$          |
| listCreate           | Create a new empty list                                            | $O(1)$                                        |
| listAddNodeHead      | Add a new node containing the given value to the list head        | $O(1)$                                        |
| listAddNodeTail      | Add a new node containing the given value to the list tail        | $O(1)$                                        |
| listInsertNode       | Insert a new node with the given value before or after a node     | $O(1)$                                        |
| listSearchKey        | Find and return the node that contains the given value           | $O(N)$, N = list length                        |
| listIndex            | Return the node at the given index in the list                    | $O(N)$, N = list length                        |
| listDelNode          | Delete the given node from the list                               | $O(N)$, N = list length                        |
| listRotate           | Pop the tail node and insert it at the head (new head)           | $O(1)$                                        |
| listDup              | Duplicate a given list                                            | $O(N)$, N = list length                        |
| listRelease          | Free the given list and all its nodes                             | $O(N)$, N = list length                        |


## Definition

### Node

```c
typedef struct listNode { // list node
	struct listNode *prev; // previous node
	struct listNode *next; // next node
	void *value;           // node value
} listNode;
```

### Iterator

```c
typedef struct listIter { // list iterator
	listNode *next; // pointer to next
	int direction;  // direction
} listIter;

// iterator directions
#define AL_START_HEAD 0 // from head
#define AL_START_TAIL 1 // from tail
```

### List

```c
typedef struct list { // doubly linked list
	listNode *head;                     // head node
	listNode *tail;                     // tail node
	void *(*dup)(void *ptr);            // node value duplication function
	void (*free)(void *ptr);            // node value free function
	int (*match)(void *ptr, void *key); // node value comparison function
	unsigned long len;                  // number of nodes
} list;
```


## References

[1] Huang Jianhong. Redis Design and Implementation
