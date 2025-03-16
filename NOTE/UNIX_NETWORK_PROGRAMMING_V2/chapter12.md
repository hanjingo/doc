# 第12章 共享内存区介绍



## 12.1 概述

![12_1](res/12_1.png)

![12_2](res/12_2.png)

例，父子进程都给同一个全局变量加1：

```c++
#include "unpipc.h"
#define SEM_NAME "mysem"
int count = 0;
int 
main(int argc, char **argv)
{
  int i, nloop;
  sem_t *mutex;
  if (argc != 2)
    	err_quit("usage: incr1 <#loops>");
  nloop = atoi(argv[1]);
  
  /* create, initialize, and unlink semaphore */
  mutex = Sem_open(Px_ipc_name(SEM_NAME), O_CREAT | O_EXCL, FILE_MODE, 1);
  Sem_unlink(Px_ipc_name(SEM_NAME));
  setbuf(stdout, NULL);
  if (Fork() == 0) {
    for (i = 0; i < nloop; i++) {
      Sem_wait(mutex);
      printf("child: %d\n", count++);
      Sem_post(mutex);
    }
    exit(0);
  }
  /* parent */
  for (i = 0; i < nloop; i++) {
    Sem_wait(mutex);
    printf("parent: %d\n", count++);
    Sem_post(mutex);
  }
  exit(0);
}
```

![12_4](res/12_4.png)

![12_5](res/12_5.png)



## 12.2 mmap, munmap和msync函数

```c++
#include <sys/mman.h>
void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
```

- `addr` 被映射到的进程内空间的起始地址；

- `len` 映射到调用进程地址空间中的字节数；

- `prot` 内存映射区操作权限

  | prot       | 说明         |
  | ---------- | ------------ |
  | PROT_READ  | 数据可读     |
  | PROT_WRITE | 数据可写     |
  | PROT_EXEC  | 数据可执行   |
  | PROT_NONE  | 数据不可访问 |

- `flags` 操作标记

  | Flags       | 说明               |
  | ----------- | ------------------ |
  | MAP_SHARED  | 变动是共享的       |
  | MAP_PRIVATE | 变动是私自的       |
  | MAP_FIXED   | 准确地解释addr参数 |

- `fd` 被映射的文件描述符；

- `offset` 被映射文件开头的字节偏移量。

- `返回值`

  - 成功：被映射区的起始地址；
  - 失败：MAP_FAILED。

mmap函数把一个文件或一个Posix共享内存取对象映射到调用进程的地址空间。使用该函数有三个目的：

1. 使用普通文件以提供内存映射I/O；
2. 使用特殊文件以提供匿名内存映射；
3. 使用`shm_open`以提供无亲缘关系进程间的Posix共享内存区。

![12_6](res/12_6.png)

```c++
#include <sys/mman.h>
int munmap(void *addr, size_t len);
```

- `addr` 地址空间；

- `len` 映射区大小。

- `返回值`

  成功：0

  失败：-1

从某个进程的地址空间删除一个映射关系。

```c++
#include <sys/mman.h>
int msync(void *addr, size_t len, int flags);
```

- `addr` 内存映射区；

- `len` 内存映射区大小；

- `flags` 标记

  | 常值          | 说明                 |
  | ------------- | -------------------- |
  | MS_ASYNC      | 执行异步写           |
  | MS_SYNC       | 执行同步写           |
  | MS_INVALIDATE | 使高速缓存的数据失效 |

- 返回值

  成功：0

  失败：-1

同步硬盘上的文件内容与内存映射区中的内容。



## 12.3 在内存映射文件中给计数器持续加1

```c+++
#include "unpipc.h"
#define SEM_NAME "mysem"
int 
main(int argc, char **argv)
{
  int fd, i, nloop, zero = 0;
  int *ptr;
  sem_t *mutex;
  if (argc != 3)
    	err_quit("usage: incr2 <pathname> <#loops>");
  nloop = atoi(argv[2]);
  
  /* create, initialize t 0, map into memory */
  fd = Open(argv[1], O_RDWR | O_CREAT, FILE_MODE);
  Write(fd, &zero, sizeof(int));
  ptr = Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Close(fd);
  /* create, initialize, and unlink semaphore */
  mutex = Sem_open(Px_ipc_name(SEM_NAME), O_CREAT | O_EXCL, FILE_MODE, 1);
  Sem_unlink(Px_ipc_name(SEM_NAME));
  setbuf(stdout, NULL);
  if (Fork() == 0) {
    for (i = 0; i < nloop; i++) {
      Sem_wait(mutex);
      printf("child: %d\n", (*ptr)++);
      Sem_post(mutex);
    }
    exit(0);
  }
  /* parent */
  for (i = 0; i < nloop; i++) {
    Sem_wait(mutex);
    printf("parent: %d\n", (*ptr)++);
    Sem_post(mutex);
  }
  exit(0);
}
```

![12_11](res/12_11.png)

```c++
#include "unpipc.h"
struct shared {
  sem_t mutex;
  int   count;
} shared;
int 
main(int argc, char **argv)
{
  int fd, i, nloop;
  struct sahred *ptr;
  if (argc != 3)
    err_quit("usage: incr3 <pathname> <#loops>");
  nloop = atoi(argv[2]);
  /* open file, initialize to 0, map into memory */
  fd = Open(argv[1], O_RDWR | O_CREAT, FILE_MODE);
  Write(fd, &shared, sizeof(struct shared));
  ptr = Mmap(NULL, sizeof(struct shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Close(fd);
  /* initialize semaphore that is shared between processes */
  Sem_init(&ptr->mutex, 1, 1);
  setbuf(stdout, NULL);
  if (Fork() == 0) {
    for (i = 0; i < nloop; i++) {
      Sem_wait(&ptr->mutex);
      printf("child: %d\n", ptr->count++);
      Sem_post(&ptr->mutex);
    }
    exit(0);
  }
  /* parent */
  for (i = 0; i < nloop; i++) {
    Sem_wait(&ptr->mutex);
    printf("parent: %d\n", ptr->count++);
    Sem_post(&ptr->mutex);
  }
  exit(0);
}
```

![12_13](res/12_13.png)



## 12.4 4.4BSD匿名内存映射

```c++
int 
main(int argc, char **argv)
{
  int i, nloop;
  int *ptr;
  sem_t *mutex;
  if (argc != 2)
    err_quit("usage: incr_map_anon <#loops>");
  nloop = atoi(argv[1]);
  /* map into memory */
  ptr = Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
}
```

*4.4BSD匿名内存映射*



## 12.5 SVR4/dev/zero内存映射

```c++
int 
main(int argc, char **argv)
{
  int fd, i, nloop;
  int *ptr;
  sem_t *mutex;
  if (argc != 2)
    err_quit("usage: incr_dev_zero <#loops>");
  nloop = atoi(argv[1]);
  /* open /dev/zero, map into memory */
  fd = Open("/dev/zero", O_RDWR);
  ptr = Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Close(fd);
}
```

*SVR4 /dev/zero内存映射*



## 12.6 访问内存映射的对象

```c++
#include "unpicp.h"
int 
main(int argc, char **argv)
{
  int fd, i;
  char *ptr;
  size_t filesize, mmapsize, pagesize;
  if (argc != 4)
    err_quit("usage: test1 <pathname> <filesize> <mmapsize>");
  filesize = atoi(argv[2]);
  mmapsize = atoi(argv[3]);
  /* open file: create or truncate; set file size */
  fd = Open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
  Lseek(fd, filesize - 1, SEEk_SET);
  Write(fd, "", 1);
  ptr = Mmap(NULL, mmapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Close(fd);
  pagesize = Sysconf(_SC_PAGESIZE);
  printf("PAGESIZE = %1d\n", (long)pagesize);
  for (i = 0; i < max(filesize, mmapsize); i += pagesize) {
    printf("ptr[%d] = %d\n", i, ptr[i]);
    ptr[i] = 1;
    printf("ptr[%d] = %d\n", i + pagesize - 1, ptr[i + pagesize - 1]);
    ptr[i + pagesize - 1] = 1;
  }
  printf("ptr[%d] = %d\n", i, ptr[i]);
  exit(0);
}
```

*访问其大小可能不同于文件大小的内存映射区*

![12_17](res/12_17.png)

![12_18](res/12_18.png)

```c++
#include "unpipc.h"
#define FILE "test.data"
#define SIZE 32768
int 
main(int argc, char **argv)
{
  int fd, i;
  char *ptr;
  /* open: create or truncate; then mmap file */
  fd = Open(FILE, O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
  ptr = Mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  for (i = 4096; i <= SIZE; i += 4096) {
    printf("setting file size to %d\n", i);
    Ftruncate(fd, i);
    printf("ptr[%d] = %d\n", i - 1, ptr[i - 1]);
  }
  exit(0);
}
```

*允许文件大小增长的内存映射区例子*



## 12.7 小结

