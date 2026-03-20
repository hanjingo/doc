English | [中文版](ansys_sds_zh.md)

# Redis Source Code Analysis - SDS

[TOC]


## Definition

```c
struct sdshdr { /* Redis self-implemented string */
		unsigned int len;  /* number of used bytes */
		unsigned int free; /* number of free bytes */
		char buf[];        /* byte array holding the string */
};
```


## Functions

| Function     | Description                                                         | Time Complexity                                            |
| ------------ | ------------------------------------------------------------------- | ---------------------------------------------------------- |
| `sdsnew`     | Create an SDS containing the given C string                         | $O(N)$, N = length of the given C string                   |
| `sdsempty`   | Create an empty SDS                                                  | $O(1)$                                                     |
| `sdsfree`    | Free the given SDS                                                   | $O(N)$, N = length of the SDS being freed                  |
| `sdslen`     | Return number of used bytes in SDS                                   | $O(1)$ (reads the `len` field)                             |
| `sdsavail`   | Return number of free bytes in SDS                                   | $O(1)$ (reads the `free` field)                            |
| `sdsdup`     | Create a copy of the given SDS                                       | $O(N)$, N = length of the source SDS                       |
| `sdsclear`   | Clear SDS contents                                                   | $O(1)$ (lazy free semantics)                               |
| `sdscat`     | Concatenate a C string to the end of an SDS                          | $O(N)$, N = length of the appended C string                |
| `sdscatsds`  | Concatenate one SDS to another                                       | $O(N)$, N = length of the appended SDS                     |
| `sdscpy`     | Copy a C string into an SDS (overwrite existing content)             | $O(N)$, N = length of the copied C string                  |
| `sdsgrowzero`| Expand SDS to the given length and zero the new bytes                | $O(N)$, N = number of newly allocated bytes                |
| `sdsrange`   | Keep the specified range of the SDS, overwrite/clear others          | $O(N)$, N = number of kept bytes                           |
| `sdstrim`    | Remove from SDS all characters appearing in the given C string       | $O(N^2)$, N = length of the given C string                |
| `sdscmp`     | Compare two SDS strings for equality                                 | $O(N)$, N = length of the shorter SDS                      |


## Memory allocation

### Pre-allocation strategy

When an SDS operation needs to grow the buffer, Redis allocates not only the required bytes but also additional free bytes according to a growth policy:

- If the SDS length (`len`) is less than 1MB, Redis allocates an extra amount equal to `len` (double the current size).

	Example: if `len = 13`, the allocated buffer becomes `13 + 13 + 1 = 27` bytes (the extra `+1` is for the terminating NUL).

- If the SDS length is >= 1MB, Redis allocates an extra 1MB of free space.

	Example: if `len = 30MB`, Redis adds `1MB` free space and the total buffer is `30MB + 1MB + 1 byte`.


### Lazy free of unused space

When an SDS operation shortens the stored string, Redis does not immediately shrink the allocation. Instead it updates the `free` field to record unused bytes and postpones actual memory reallocation until needed.


## Differences vs C strings

| C string                                 | SDS                                        |
| ---------------------------------------- | ------------------------------------------ |
| Getting length costs $O(N)$               | Getting length costs $O(1)$                |
| Unsafe APIs (risk of buffer overflow)     | Safe APIs (no buffer overflow)             |
| Reallocating N times for N length changes | At most N reallocations for N changes      |
| Stores only text                          | Stores text or binary data                 |
| Compatible with all `<string.h>` ops      | Compatible only with a subset of them     |


## References

[1] Huang Jianhong. Redis Design and Implementation
