# 第3章 内核对象

[TOC]



## 3.1 何为内核对象

内核对象的数据结构只能由操作系统内核访问，应用程序不能再内存中定位这些数据结构并直接更改其内容（但是可以通过Windows提供的函数来访问）。

### 3.1.1 使用计数

内核对象的所有者是操作系统内核而非进程，内核对象的生命期可能长于创建它的那个进程。

操作系统内核用`计数（usage count）`来标记使用内核对象的进程数量，当计数为0时，销毁内核对象。

### 3.1.2 内核对象的安全性

内核对象使用`安全描述符（security descriptor, SD）`来保护，SD描述了以下内容：

- 对象拥有者。
- 被允许访问或使用此对象的用户。
- 被拒绝访问或使用此对象的用户。

```c++
HANDLE CreateFileMapping(
	HANDLE hFile,
	PSECURITY_ATTRIBUTES psa,
	DWORD flProtect,
 	DWORD dwMaximumSizelligh,
	DWORD dwMaximumSizeLow,
	PCTSTR pszName);
```

- `hFile`

- `psa`安全性

  ```c++
  typedef struct _SECURITY_ATTRIBUTES {
      DWORD nLength;
      LPVOID lpSecurityDescriptor;
      BOOL bInheritHandle;
  } SECURITY_ATTRIBUTES;
  ```

- `flProtect`

- `dwMaximumSizelligh`

- `dwMaximumSizeLow`

- `pszName`

TODO
