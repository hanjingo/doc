[中文版](lru_zh.md) | English

# LRU Algorithm

[TOC]



`LRU (Least Recently Used) algorithm` is a cache eviction policy. This algorithm assumes that recently used data is hot data and is likely to be used again soon; while data that has not been used recently is less likely to be used next time. When the cache is full, the least recently used data is evicted first.

## Implementation

### Doubly Linked List

Maintain a doubly linked list to store cached data, placing the most recently used data at the head of the list.

#### Insert

Before inserting data, if the key exists, update the value and move it to the head of the list.

If the key does not exist, check the list capacity:

- If the list is full, delete the last element and insert the new node at the head of the list
- If the list is not full, add the data to the head of the list

#### Query

When querying data, traverse the entire list. If the corresponding data is found, move it to the head of the list; if not found, return null.


## LRU Cache in Go

```go
TODO
```



## References

TODO
