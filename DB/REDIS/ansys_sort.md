English | [中文版](ansys_skiplist_zh.md)

# Redis Source Code Analysis - SORT

[TOC]


Redis's `SORT` command can sort the elements stored in a list, set, or sorted set key.


## Definitions

### `redisSortObject`

```c
typedef struct _redisSortObject {
	 robj *obj; /* the value from the key being sorted */
	 union {
		  double score; /* used when sorting by numeric value */
		  robj *cmpobj; /* used when sorting string values with BY option */
	 } u;
} redisSortObject;
```


## Implementation of the `SORT` command

Sorting a key that contains numeric values:

```sh
SORT <key>
```

When the server executes `SORT numbers`, it performs the following steps:

```mermaid

```

1. Allocate an array with the same length as the `numbers` list; each element of the array is a `redisSortObject`.
2. Iterate the array and point each element's `obj` to the corresponding entry in the `numbers` list, establishing a one-to-one mapping.
3. Convert each object pointed to by `obj` into a `double` and store that value into the corresponding element's `u.score` field.
4. Sort the array by the numeric `u.score` values in ascending order.
5. Iterate the array and return the objects pointed to by each `obj` as the sorted result to the client.


## Implementation of the `ALPHA` option

Using the `ALPHA` option lets `SORT` order elements as strings:

```sh
SORT <key> ALPHA
```

When the server executes `SORT xx ALPHA`, it performs:

```mermaid

```

1. Allocate an array of `redisSortObject` whose length equals the size of the `xx` collection.
2. Iterate the array and point each element's `obj` to the corresponding member of the `xx` collection.
3. Sort the array by the string values of the elements pointed to by `obj` (ascending lexicographic order).
4. Iterate the array and return each element referenced by `obj` to the client in order.


## `ASC` and `DESC` options

By default `SORT` performs ascending order; `ASC` explicitly requests ascending order (the two commands below are equivalent):

```sh
SORT <key>
SORT <key> ASC
```

Use `DESC` to request descending order:

```sh
SORT <key> DESC
```



## Implementation of the `BY` option

By default `SORT` uses the elements in the input key as the sorting weight. With the `BY` option you can specify an external field pattern to be used as weights:

```sh
SORT xx BY xxx
```

Example:

```sh
MSET apple-price 8 banana-price 5.5 cherry-price 7
SORT fruits BY *-price
```

When the server executes `SORT xx BY xxx`, it performs:

```mermaid

```

1. Allocate an array of `redisSortObject` with length equal to the size of `xx`.
2. Iterate the array and point each element's `obj` to the corresponding member of `xx`.
3. For each element, using the `obj` and the `BY` pattern `xxx`, look up the corresponding weight key.
4. Convert each weight value to a `double` and store it into the element's `u.score`.
5. Sort the array by `u.score` in ascending order.
6. Iterate the sorted array and return the elements referenced by `obj` to the client.


## `BY` with `ALPHA`

`BY` assumes weight keys contain numeric values; when weight keys store strings use `ALPHA` together with `BY`:

```sh
SORT xx BY xxx ALPHA
```

Example:

```sh
SADD fruits "apple" "banana" "cherry"
MSET apple-id "FRUIT-25" banana-id "FRUIT-79" cherry-id "FRUIT-13"
SORT fruits BY *-id ALPHA
```

When the server executes `SORT xx BY xxx ALPHA`, it performs:

```mermaid

```

1. Allocate an array of `redisSortObject` whose length equals the size of `fruits`.
2. Point each array element's `obj` to the corresponding element of `fruits`.
3. For each element, using the `obj` and the `BY` pattern `xxx`, find the corresponding weight key.
4. Set each element's `u.cmpobj` to point to the weight object's value.
5. Sort the array by the string values of the referenced weight objects.
6. Iterate the array and return the elements referenced by `obj` to the client.


## `LIMIT` option

`LIMIT` restricts the returned portion of the sorted elements. Format:

```sh
LIMIT <offset> <count>
```

- `offset`: number of sorted elements to skip.
- `count`: number of elements to return after skipping `offset` elements.

Example:

```sh
SADD alphabet a b c d e f
SORT alphabet ALPHA LIMIT 2 3
```

When the server executes `SORT xx ALPHA LIMIT m n`, it performs:

```mermaid

```

1. Allocate an array of `redisSortObject` with length equal to the size of `xx`.
2. Point each `obj` to the corresponding element in `alphabet`.
3. Sort the array by string values.
4. Move the pointer to index `m` and return the elements at `xx[m]`, `xx[m+1]`, ..., up to the requested `count` to the client.


## `GET` option

`GET` lets `SORT` return values from external keys based on the sorted elements and the provided pattern:

```sh
SORT xx ALPHA GET xxx
```

When the server executes `SORT xx ALPHA GET xxx`, it performs:

```mermaid

```

1. Allocate an array of `redisSortObject` sized to `xx`.
2. Point each `obj` to the corresponding element in `xx`.
3. Sort the array by string values.
4. For each sorted element, use the `GET` pattern to look up the requested keys.
5. Return the found keys' values to the client in the order specified by the `GET` patterns.


## `STORE` option

`STORE` persists the sorted result into the specified key so it can be reused later. Format:

```sh
SORT xx ALPHA STORE xxx
```

When the server executes `SORT xx ALPHA STORE xxx`, it performs:

1. Allocate an array of `redisSortObject` sized to `xx`.
2. Point each `obj` to the corresponding element in `xx`.
3. Sort the array by string values.
4. If the `xxx` key exists, delete it.
5. Create `xxx` as an empty list.
6. Push the sorted elements into the tail of the `xxx` list.
7. Return the elements to the client.


## Execution order when multiple options are present

### Execution steps

Execution of a `SORT` command proceeds in the following phases:

1. Sorting

	The server sorts using `ALPHA`, `ASC`/`DESC`, and `BY` options to generate an ordered result set.

2. Limiting the result set

	`LIMIT` is applied to restrict the size of the result set.

3. Fetching external keys

	`GET` patterns are used to retrieve external keys for each element, producing the final result set.

4. Storing the result

	`STORE` writes the result set to the specified key.

5. Returning to the client

	The server iterates the final result set and sends it back to the client.

Example:

```sh
SORT <key> ALPHA DESC BY <by-pattern> LIMIT <offset> <count> GET <get-pattern> STORE <store_key>
```

Steps:

```sh
SORT <key> ALPHA DESC BY <by-pattern>
LIMIT <offset> <count>
GET <get-pattern>
STORE <store_key>
```

### Option placement

Except for `GET`, the textual placement of options in the command does not affect the execution order of the options.

Example:

```sh
SORT <key> ALPHA DESC BY <by-pattern> LIMIT <offset> <count> GET <get-pattern> STORE <store_key>
```

is equivalent to

```sh
SORT <key> LIMIT <offset> <count> BY <by-pattern> ALPHA GET <get-pattern> STORE <store_key> DESC
```

If multiple `GET` options are present, their relative order must be preserved when reordering options; otherwise the resulting output will change.

Example:

```sh
SORT <key> GET <pattern-a> GET <pattern-b> STORE <store_key>
```

is not equivalent to

```sh
SORT <key> STORE <store_key> GET <pattern-b> GET <pattern-a>
```


## References

### Literature

[1] Huang Jianhong. Redis Design and Implementation
