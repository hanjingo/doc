English | [中文版](ansys_ziplist_zh.md)

# Redis Source Code Analysis - Ziplist

[TOC]


Ziplist is one of the compact encodings Redis uses for list and hash objects. When a list contains few elements and each element is either a small integer or a short string, Redis uses ziplist as the underlying representation.

Example: the following commands produce a list stored as a ziplist:

```sh
redis> RPUSH lst 1 3 5 10086 "hello" "world"
redis> OBJECT ENCODING lst
```


## Ziplist layout

A ziplist is laid out as:

`|zlbytes|zltail|zllen|entry1|entry2|...|entryN|zlend|`

| field   | type     | length (bytes) | description |
|---------|----------|----------------|-------------|
| zlbytes | uint32_t | 4              | total number of bytes used by the ziplist (used when reallocating or finding `zlend`) |
| zltail  | uint32_t | 4              | offset to the last entry from the start of the ziplist (allows locating tail without traversal) |
| zllen   | uint16_t | 2              | number of entries when < UINT16_MAX; if equal to UINT16_MAX the real length must be computed by traversal |
| entryX  | element  | variable       | entries; each entry length depends on its content |
| zlend   | uint8_t  | 1              | termination byte 0xFF |

Example (three entries):

| zlbytes | zltail | zllen | entry1 | entry2 | entry3 | zlend |
| ------- | ------ | ----- | ------ | ------ | ------ | ----- |
| 0x50    | 0x3c   | 0x3   |        |        |        | 0xFF  |

- `zlbytes = 0x50 (80)` total bytes
- `zltail = 0x3c (60)` offset from start to entry3
- `zllen = 0x3 (3)` number of entries


## Entry layout

Each entry consists of three parts:

| previous_entry_length | encoding | content |
| ---------------------: | -------: | ------- |
| 1~5 bytes              | variable | variable |

- `previous_entry_length` records the length (in bytes) of the previous entry:
	- If the previous entry length < 254, this field is 1 byte.
	- If the previous entry length >= 254, this field is 5 bytes: first byte = 0xFE, next 4 bytes store the length.

- `encoding` describes the type and length of `content`.

String encodings:

| encoding pattern           | header length | content |
| -------------------------: | ------------: | ------- |
| `00bbbbbb`                 | 1             | string up to 63 bytes |
| `01bbbbbb xxxxxxxx`        | 2             | string up to 16383 bytes |
| `10_____ aaaaaaaa bbbbbbbb cccccccc dddddddd` | 5 | string up to 4294967295 bytes |

Integer encodings:

| encoding | length (bytes) | content |
|---------:|---------------:|-------- |
| `11000000` | 1 | int16_t |
| `11010000` | 1 | int32_t |
| `11100000` | 1 | int64_t |
| `11110000` | 1 | 24-bit signed integer |
| `11111110` | 1 | 8-bit signed integer |
| `1111xxxx` | 1 | immediate integer encoded in the lower 4 bits (value 0..12) — no content bytes |

- `content` holds either the byte array or integer value as indicated by `encoding`.

Example: an entry storing the string "hello world":

| previous_entry_length | encoding | content       |
| --------------------- | -------- | ------------- |
| ...                   | 00001011 | "hello world" |


## Cascade update

If multiple consecutive entries have `previous_entry_length` encoded as 1 byte (previous entry < 254 bytes), inserting a new entry whose size is >= 254 will require the subsequent entries' `previous_entry_length` fields to expand from 1 to 5 bytes. This can trigger a chain of reallocations and updates called a "cascade update".

Both insertions and deletions can trigger cascade updates.

Worst-case complexity: a cascade update may perform up to N reallocations, each costing up to $O(N)$, so worst-case complexity is $O(N^2)$. In practice this is rare because it requires many consecutively-sized entries near the 254-byte threshold.


## Ziplist API

| Function              | Purpose                                                          | Complexity |
|----------------------:|------------------------------------------------------------------|------------:|
| `ziplistNew`          | Create a new empty ziplist                                        | $O(1)$      |
| `ziplistPush`         | Create a new entry with the given value and push to head or tail | average $O(N)$, worst $O(N^2)$ |
| `ziplistInsert`       | Insert a new entry after a given entry                            | average $O(N)$, worst $O(N^2)$ |
| `ziplistIndex`        | Return entry at a given index                                     | $O(N)$      |
| `ziplistFind`         | Find an entry containing the given value                          | value compare is $O(N)$; full scan worst $O(N^2)$ |
| `ziplistNext`         | Return the next entry of a given entry                             | $O(1)$      |
| `ziplistPrev`         | Return the previous entry of a given entry                         | $O(1)$      |
| `ziplistGet`          | Extract the value stored in an entry                               | $O(1)$      |
| `ziplistDelete`       | Delete a given entry from the ziplist                              | average $O(N)$, worst $O(N^2)$ |
| `ziplistDeleteRange`  | Delete a range of consecutive entries                              | average $O(N)$, worst $O(N^2)$ |
| `ziplistBlobLen`      | Return total size in bytes of the ziplist                          | $O(1)$      |
| `ziplistLen`          | Return number of entries (if < 65535 $O(1)$, otherwise $O(N)$)     | -           |

Note: `ziplistPush`, `ziplistInsert`, `ziplistDelete`, and `ziplistDeleteRange` may trigger cascade updates.


## References

[1] Huang Jianhong. Redis Design and Implementation
