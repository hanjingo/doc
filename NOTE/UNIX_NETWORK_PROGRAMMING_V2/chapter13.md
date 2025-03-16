# 第13章 Posix共享内存区



## 13.1 概述

Posix.1提供了两种在无亲缘关系进程间共享内存区的方法：

1. `内存映射文件（memory-mapped file）`由open函数打开，由mmap函数把得到的描述符映射到当前进程地址空间中的一个文件。
2. `共享内存区对象（shared-memory object）`由shm_open打开一个Posix.1 IPC名字，所返回的描述符由mmap函数映射到当前进程的地址空间。

![13_1](res/13_1.png)



## 13.2 shm_open和shm_unlink函数

```c++
#include <sys/mman.h>
int shm_open(const char* name, int oflag, mode_t mode);
```

- `name` 内存区对象名

- `oflag` 标志

- `mode` 权限位

- `返回值`

  成功：非负描述符

  失败：-1

创建一个共享内存区对象的名。

```c++
#include <sys/mman.h>
int shm_unlink(const char* name);
```

- `name` 内存区对象名

删除一个共享内存区对象的名。



## 13.3 ftruncate和fstat函数

```c++
#include <unistd.h>
int ftruncate(int fd, off_t length);
```

- `fd` 文件描述符

- `length` 内存区对象大小

- `返回值`

  成功：0

  失败：-1

修改普通文件或共享内存区对象的大小。

```c++
#include <sys/types.h>
#include <sys/stat.h>
int fstat(int fd, struct stat *buf);

struct stat {
    ...
    mode_t st_mode;
    uid_t  st_uid;
    gid_t  st_gid;
    off_t  st_size;
    ...
}
```

- `fd` 文件描述符

- `buf` 用于返回结果的缓冲区

- `返回值`

  成功：0

  失败：-1

获取共享内存区对象信息。



## 13.4 简单的程序

### 13.4.1 shmcreate程序

```c++
#include "unpipc.h"
int 
main(int argc, char **argv)
{
  int c, fd, flags;
  char *ptr;
  off_t length;
  flags = O_RDWR | O_CREAT;
  while ((c = Getopt(argc, argv, "e")) != -1) {
    switch (c) {
      case 'e':
        flags |= O_EXCL;
        break;
    }
  }
  if (optind != argc - 2)
    err_quit("usage: shmcreate [ -e ] <name> <length>");
  length = atoi(argv[optind + 1]);
  fd = Shm_open(argv[optind], flags, FILE_MODE);
  Ftruncate(fd, length);
  ptr = Mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  exit(0);
}
```

*创建一个具有所指定大小的Posix共享内存区对象*

### 13.4.2 shmunlink程序

```c++
#include "unpipc.h"
int 
main(int argc, char **argv)
{
  if (argc != 2)
    err_quit("usage: shmunlink <name>");
  Shm_unlink(argv[1]);
  exit(0);
}
```

*删除一个共享内存区对象的名字*

### 13.4.3 shmwrite程序

```c++
#include "unpipc.h"
int 
main(int argc, char **argv)
{
  int i, fd;
  struct stat stat;
  unsigned char *ptr;
  if (argc != 2)
    err_quit("usage: shmwrite <name>");
  /* open, get size, map */
  fd = Shm_open(argv[1], O_RDWR, FILE_MODE);
  Fstat(fd, &stat);
  ptr = Mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Close(fd);
  /* set: ptr[0] = 0, ptr[1] = 1, etc. */
  for (i = 0; i < stat.st_size; i++)
    *ptr++ = i % 256;
  exit(0);
}
```

*打开一个共享内存区对象，填写一个数据模式*

### 13.4.4 shmread程序

```c++
#include "unpipc.h"
int 
main(int argc, char **argv)
{
  int i, fd;
  struct stat stat;
  unsigned char c, *ptr;
  if (argc != 2)
    err_quit("usage: shmread <name>");
  /* open, get size, map */
  fd = Shm_open(argv[1], O_RDONLY, FILE_MODE);
  Fstat(fd, &stat);
  ptr = Mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
  Close(fd);
  /* check that ptr[0] = 0, ptr[1] = 1, etc. */
  for (i = 0; i < stat.st_size; i++)
    if ((c = *ptr++) != (i % 256))
      err_ret("ptr[%d] = %d", i, c);
  exit(0);
}
```

*打开一个共享内存区对象，验证其数据模式*

### 13.4.6 例子

```c++
#include "unpipc.h"
int 
main(int argc, char **argv)
{
  int fd1, fd2, *ptr1, *ptr2;
  pid_t childpid;
  struct stat stat;
  if (argc != 2)
    err_quit("usage: test3 <name>");
  shm_unlink(Px_ipc_name(argv[1]));
  fd1 = Shm_open(Px_ipc_name(argv[1]), O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
  Ftruncate(fd1, sizeof(int));
  fd2 = Open("/etc/motd", O_RDONLY);
  Fstat(fd2, &stat);
  if ((childpid = Fork()) == 0) {
    /* child */
    ptr2 = Mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd2, 0);
    ptr1 = Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    printf("child: shm ptr = %p, motd ptr = %p\n", ptr1, ptr2);
    sleep(5);
    printf("shared memory integer = %d\n", *ptr1);
    exit(0);
  }
  /* parent: mmap in reverse order from child */
  ptr1 = Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
  ptr2 = Mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd2, 0);
  printf("parent: shm ptr = %p, motd ptr = %p\n", ptr1, ptr2);
  *ptr1 = 777;
  Waitpid(childpid, NULL, 0);
  exit(0);
}
```

*共享内存区在不同进程中可以出现在不同的地址*



## 13.5 给一个共享的计数器持续加1

```c++
#include "unpipc.h"
struct shmstruct {
  int count;
};
sem_t *mutex;
int 
main(int argc, char **argv)
{
  int fd;
  struct shmstruct *ptr;
  if (argc != 3)
    err_quit("usage: server <shmname> <semname>");
  shm_unlink(Px_ipc_name(argv[1]));
  /* create shm, set its size, map it, close descriptor */
  fd = Shm_open(Px_ipc_name(argv[1]), O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
  Ftruncate(fd, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Close(fd);
  sem_unlink(Px_ipc_name(argv[2]));
  mutex = Sem_open(Px_ipc_name(argv[2]), O_CREAT | O_EXCL, FILE_MODE, 1);
  Sem_close(mutex);
  exit(0);
}
```

*创建并初始化共享内存区和信号量的程序*

```c++
#include "unpipc.h"
struct shmstruct {
  int count;
};
sem_t *mutex;
int 
main(int argc, char **argv)
{
  int fd, i, nloop;
  pid_t pid;
  struct shmstruct *ptr;
  if (argc != 4)
    err_quit("usage: client1 <shmname> <semname> <#loops>");
  nloop = atoi(argv[3]);
  fd = Shm_open(Px_ipc_name(argv[1]), O_RDWR, FILE_MODE);
  ptr = Mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)
  Close(fd);
  mutex = Sem_open(Px_ipc_name(argv[2]), 0);
  pid = getpid();
  for (i = 0; i < nloop; i++) {
    Sem_wait(mutex);
    printf("pid %1d: %d\n", (long)pid, ptr->count++);
    Sem_post(mutex);
  }
  exit(0);
}
```

*给存放在共享内存区中的一个计数器加1的程序*



## 13.6 向一个服务器发送消息

![13_9](res/13_9.png)

```c++
#include "unpipc.h"
#define MESGSIZE 256
#define NMESG    16
struct shmstruct {
  sem_t mutex;
  sem_t nempty;
  sem_t nstored;
  int   nput;
  long  noverflow;
  sem_t noverflowmutex;
  long  msgoff[NMESG];
  char  msgdata[NMESG * MESGSIZE];
};
```

*定义共享内存区布局的头文件*

```c++
#include "cliserv2.h"
int 
main(int argc, char **argv)
{
  int fd, index, lastnoverflow, temp;
  long offset;
  struct shmstruct *ptr;
  if (argc != 2)
    err_quit("usage: server2 <name>");
  /* create shm, set its size, map it, close descriptor */
  shm_unlink(Px_ipc_name(argv[1]));
  fd = Shm_open(Px_ipc_name(argv[1]), O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
  ptr = Mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Ftruncate(fd, sizeof(struct shmstruct));
  Close(fd);
  /* initialize the array of offsets */
  for (index = 0; index < NMESG; index++)
    ptr->msgoff[index] = index * MESGSIZE;
  /* initialize the semaphores in shared memory */
  Sem_init(&ptr->mutex, 1, 1);
  Sem_init(&ptr->nempty, 1, NMESG);
  Sem_init(&ptr->nstored, 1, 0);
  Sem_init(&ptr->noverflowmutex, 1, 1);
  /* this program is the consumer */
  index = 0;
  lastnoverflow = 0;
  for (;;) {
    Sem_wait(&ptr->nstored);
    Sem_wait(&ptr->mutex);
    offset = ptr->msgoff[index];
    printf("index = %d: %s\n", index, &ptr->msgdata[offset]);
    if (++index >= NMESG)
      index = 0;
    Sem_post(&ptr->mutex);
    Sem_post(&ptr->nempty);
    Sem_wait(&ptr->noverflowmutex);
    temp = ptr->noverflow;
    Sem_post(&ptr->noverflowmutex);
    if (temp != lastnoverflow) {
      printf("noverflow = %d\n", temp);
      lastnoverflow = temp;
    }
  }
  exit(0);
}
```

*从共享内存区中取得并输出消息的服务器程序*

```c++
#include "cliserv2.h"
int 
main(int argc, char **argv)
{
  int fd, i, nloop, nusec;
  pid_t pid;
  char mesg[MESGSIZE];
  long offset;
  struct shmstruct *ptr;
  if (argc != 4)
    err_quit("usage: client2 <name> <#loops> <#usec>");
  nloop = atoi(argv[2]);
  nusec = atoi(argv[3]);
  /* open and map shared memory that server must create */
  fd = Shm_open(Px_ipc_name(argv[1]), O_RDWR, FILE_MODE);
  ptr = Mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  Close(fd);
  pid = getpid();
  for (i = 0; i < nloop; i++) {
    Sleep_us(nusec);
    snprintf(mesg, MESGSIZE, "pid %1d: message %d", (long)pid, i);
    if (sem_trywait(&ptr->nempty) == -1) {
      if (errno == EAGAIN) {
        Sem_wait(&ptr->noverflowmutex);
        ptr->noverflow++;
        Sem_post(&ptr->noverflowmutex);
        continue;
      } else
        err_sys("sem_trywait error");
    }
    Sem_wait(&ptr->mutex);
    offset = ptr->msgoff[ptr->nput];
    if (++(ptr->nput) >= NMESG)
      ptr->nput = 0;
    Sem_post(&ptr->mutex);
    strcpy(&ptr->msgdata[offset], mesg);
    Sem_post(&ptr->nstored);
  }
  exit(0);s
}
```

*在共享内存区中给服务器存放消息的客户程序*



## 13.7 小结

