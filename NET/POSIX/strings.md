# `strings.h`

- [bzero](#bzero)

- [bcopy](#bcopy)

- 【bcmp](#bcmp)

    

### bzero

`void bzero(void *dest, size_t nbytes)` 

- dest: 被设置的字符串
- nbytes: 要设置的字节数

 设置字符串的值为0

---

### bcopy

`void bcopy(const void *src, void *dest, size_t nbytes)` 

- src: 源字符串
- dest: 目标字符串
- nbytes: 要复制的数量

复制字符串

---

### bcmp

`int bcmp(const void *ptr1, const void *ptr2, size_t nbytes)` 

- ptr1: 字符串1
  
- ptr2: 字符串2
  
- nbytes: 要比较的字符长度

比较字符串

---

