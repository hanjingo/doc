# `string.h`

- [memset](#memset)
- [memcpy](#memcpy)
- [memcmp](#memcmp)



### memset

`void *memset(void *dest, int c, size_t len)`

- dest: 被设置的字符串
- c: 要设置的值
- len: 要设置的字节数

设置字符串为指定值

---

### memcpy

`void *memcpy(void *dest, const void *src, size_t nbytes)`

- dest: 目标字符串
- src: 源字符串
- nbytes: 要复制的字节数

复制字符串

**注意：当dest和src重叠时，memcpy操作结果无法预料**

---

### memcmp

`int memcmp(const void *ptr1, const void *ptr2, size_t nbytes)`

- ptr1: 字符串1
- ptr2: 字符串2
- nbytes: 要比较的字符串长度

比较字符串

---

