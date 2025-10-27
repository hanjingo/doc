[中文版](link_list_zh.md) | English

# Linked List

[TOC]

A linked list is a linear collection of nodes where each node holds a value and references (pointers) to other nodes. Linked lists are a fundamental building block for many data structures (stacks, queues, adjacency lists) and are useful when you need constant-time insertions and deletions at known positions.

This note focuses on doubly linked lists (each node has pointers to both predecessor and successor). It provides a C++-style implementation sketch, explains common operations (insert/erase), lists complexity, and gives practical advice.

## Diagrams

![doubly_linked_list](res/doubly_linked_list.png)

![empty_doubly_linked_list](res/empty_doubly_linked_list.png)

## C++ implementation sketch

Below is a compact but practical implementation sketch for a templated doubly linked list using sentinel head/tail nodes and simple iterator support. The code emphasizes clarity over full STL compatibility.

```c++
template <typename Object>
class List {
private:
    struct Node {
        Object data;
        Node* prev;
        Node* next;
        Node(const Object& d = Object(), Node* p = nullptr, Node* n = nullptr)
            : data(d), prev(p), next(n) {}
    };

public:
    class const_iterator {
    public:
        const_iterator() : current(nullptr) {}
        const Object& operator*() const { return retrieve(); }
        const_iterator& operator++() { current = current->next; return *this; }
        const_iterator operator++(int) { const_iterator old = *this; ++(*this); return old; }
        bool operator==(const const_iterator& rhs) const { return current == rhs.current; }
        bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }

    protected:
        Node* current;
        Object& retrieve() const { return current->data; }
        const_iterator(Node* p) : current(p) {}
        friend class List<Object>;
    };

    class iterator : public const_iterator {
    public:
        iterator() {}
        Object& operator*() { return this->retrieve(); }
        const Object& operator*() const { return const_iterator::operator*(); }
        iterator& operator++() { this->current = this->current->next; return *this; }
        iterator operator++(int) { iterator old = *this; ++(*this); return old; }

    protected:
        iterator(Node* p) : const_iterator(p) {}
        friend class List<Object>;
    };

    List() { init(); }
    List(const List& rhs) { init(); *this = rhs; }
    ~List() { clear(); delete head; delete tail; }

    const List& operator=(const List& rhs) {
        if (this == &rhs) return *this;
        clear();
        for (const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
            push_back(*itr);
        return *this;
    }

    iterator begin() { return iterator(head->next); }
    const_iterator begin() const { return const_iterator(head->next); }
    iterator end() { return iterator(tail); }
    const_iterator end() const { return const_iterator(tail); }

    int size() const { return theSize; }
    bool empty() const { return size() == 0; }
    void clear() { while (!empty()) pop_front(); }

    Object& front() { return *begin(); }
    const Object& front() const { return *begin(); }
    Object& back() { return *--end(); }
    const Object& back() const { return *--end(); }

    void push_front(const Object& x) { insert(begin(), x); }
    void push_back(const Object& x) { insert(end(), x); }
    void pop_front() { erase(begin()); }
    void pop_back() { erase(--end()); }

private:
    int theSize;
    Node* head;
    Node* tail;

    void init() {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};
```

Notes: sentinel head/tail nodes simplify insertion and deletion at boundaries. `begin()` points to the first real node (head->next). `end()` returns the tail sentinel and must not be dereferenced.

## Insert (example)

![link_list_insert](res/link_list_insert.png)

Insert a new element before the node referenced by `itr`:

```c++
iterator insert(iterator itr, const Object& x) {
    Node* p = itr.current;
    theSize++;
    p->prev = p->prev->next = new Node(x, p->prev, p);
    return iterator(p->prev);
}
```

Explanation: the new node is created and linked between `p->prev` and `p`; the expression assigns the new node to both `p->prev->next` and `p->prev` and returns an iterator to it.

## Erase (example)

![link_list_delete](res/link_list_delete.png)

Remove the node at `itr` and return an iterator to the following node:

```c++
iterator erase(iterator itr) {
    Node* p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
}

iterator erase(iterator start, iterator end) {
    for (iterator itr = start; itr != end; )
        itr = erase(itr);
    return end;
}
```

## Complexity

- Moving an iterator to the next/previous node: O(1).
- Insertion or deletion given an iterator: O(1).
- Random access by index: O(n) — linked lists are not suitable for constant-time indexing.

## Practical considerations

- Prefer linked lists when you need many insertions/removals in the middle of a sequence and you have direct pointers/iterators to those positions.
- For stacks/queues or when locality matters, `vector` or `deque` often perform better due to cache friendliness and lower per-node overhead.
- Avoid linked lists when you need frequent random access or tight memory/cache performance.

## Reference

1. Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein. Introduction to Algorithms. 3rd ed.