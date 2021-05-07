# 字符串处理

## `strings.h`

- `void bzero(void *dest, size_t nbytes)` 设置字符串的值为0

  - dest: 被设置的字符串
  - nbytes: 要设置的字节数

- `void bcopy(const void *src, void *dest, size_t nbytes)` 复制字符串

  - src: 源字符串
  - dest: 目标字符串
  - nbytes: 要复制的数量

- `int bcmp(const void *ptr1, const void *ptr2, size_t nbytes)` 比较字符串

  - ptr1: 字符串1

  - ptr2: 字符串2

  - nbytes: 要比较的字符长度

    

## `string.h`

- `void *memset(void *dest, int c, size_t len)` 设置字符串为指定值

  - dest: 被设置的字符串
  - c: 要设置的值
  - len: 要设置的字节数

- `void *memcpy(void *dest, const void *src, size_t nbytes)` 复制字符串

  - dest: 目标字符串
  - src: 源字符串
  - nbytes: 要复制的字节数

  **注意：当dest和src重叠时，memcpy操作结果无法预料**

- `int memcmp(const void *ptr1, const void *ptr2, size_t nbytes)` 比较字符串

  - ptr1: 字符串1
  - ptr2: 字符串2
  - nbytes: 要比较的字符串长度

