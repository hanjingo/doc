# 第五章 标准I/O库

[TOC]



## 5.1 引言



## 5.2 流和FILE对象

```c++
#include <stdio.h>
#include <wchar.h>
int fwide(FILE *fp, int mode);
```

- `fp` 文件流

- `mode` 模式

  - `< 0` 试图使指定的流是字节定向的；
  - `= 0` 将不试图设置流的定向，但返回标识该流定向的值；
  - `> 0` 试图使指定的流是宽定向的。

- `返回值`

  流是宽定向的：`> 0`

  流是未定向的：`0`

  流是字节定向的：`< 0`

*设置流的定向*



## 5.3 标准输入，标准输出和标准错误

```c++
#include <stdio.h>
```

- `stdin` 标准输入
- `stdout` 标准输出
- `stderr` 标准错误



## 5.4 缓冲

标准I/O提供了以下3种类型的缓冲：

- `全缓冲` 在填满标准I/O缓冲区后才进行实际I/O操作；
- `行缓冲` 当输入/输出中遇到换行符时，标准I/O执行I/O操作；
- `不带缓冲` 标准I/O库不对字符进行缓冲存储。

```c++
#include <stdio.h>
void setbuf(FILE *restrict fp, char *restrict buf);
int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
```

- `fp` 文件流

- `buf` 缓冲区（长度为BUFSIZ）

- `mode` 缓冲类型

  - `_IOFBF` 全缓冲
  - `_IOLBF` 行缓冲
  - `_IONBF` 不带缓冲

- `size` 缓冲区长度

- `返回值`

  成功：0

  失败：非0

*设置缓冲区属性*

![5_1](res/5_1.png)

*setbuf和setvbuf函数*

```c++
#include <stdio.h>
int fflush(FILE *fp);
```

- `fp` 文件流

- `返回值`

  成功：0

  失败：EOF

*强制刷出一个流*



## 5.5 打开流

```c++
#include <stdio.h>
FILE *fopen(const char *restrict pathname, const char *restrict type);
FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);
FILE *fdopen(int fd, const char *type);
```

- `pathname` 路径

- `type` 打开模式

  | type         | 说明                                     | open(2)标志                     |
  | ------------ | ---------------------------------------- | ------------------------------- |
  | r或rb        | 为读而打开。                             | O_RDONLY                        |
  | w或wb        | 把文件截断至0长，或为写而创建。          | O_WRONLY \| O_CREAT \| O_TRUNC  |
  | a或ab        | 追加：为在文件尾写而打开，或为写而创建。 | O_WRONLY \| O_CREAT \| O_APPEND |
  | r+或r+b或rb+ | 为读和写而打开。                         | O_RDWR                          |
  | w+或w+b或wb+ | 把文件截断至0长，或为读和写而打开。      | O_RDWR \| O_CREAT \| O_TRUNC    |
  | a+或a+b或ab+ | 为在文件尾读和写而打开或创建。           | O_RDWR \| O_CREAT \| O_APPEND   |

  *打开标准I/O流的type参数*

- `fd` 文件描述符

- `返回值`

  成功：文件指针

  失败：NULL

*fopen：打开一个标准I/O流*

*freopen：重新打开一个标准I/O流*

*fdopen：使一个标准的I/O流与已有的文件描述符结合*

![5_3](res/5_3.png)

*打开一个标准I/O流的6种不同方式*

`POSIX.1`要求实现使用如下的权限位集来创建文件：`S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH`。

```c++
#include <stdio.h>
int fclose(FILE *fp);
```

- `fp` 流

- `返回值`

  成功：0

  失败：EOF

*关闭流*



## 5.6 读和写流

读/写不同类型的I/O：

- 每次一个字符的I/O；
- 每次一行的I/O；
- 直接I/O。

```c++
#include <stdio.h>
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);
```

- `fp` 流

- `返回值`

  成功：下一个字符

  到达文件尾或出错：EOF

*一次读一个字符*

```c++
#include <stdio.h>
int ferror(FILE *fp);
int feof(FILE *fp);
```

- `fp` 流

- `返回值`

  条件为真：非0

  条件为假：0

*判断错误类型/文件结束*

```c++
#include <stdio.h>
void clearerr(FILE *fp);
```

- `fp` 流

*清空错误标记*

```c++
#include <stdio.h>
int ungetc(int c, FILE *fp);
```

- `c` 字符

- `fp` 流

- `返回值`

  成功：c

  失败：EOF

*将从流中读取的字符再退回流中*

```c++
#include <stdio.h>
int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int putchar(int c);
```

- `c` 字符

- `fp` 流

- `返回值`

  成功：c

  失败：EOF

*写单个字符到流中*



## 5.7 每次一行I/O

```c++
#include <stdio.h>
char *fgets(char *restrict buf, int n, FILE *restrict fp);
char *gets(char *buf);
```

- `buf` 缓冲区

- `n` 缓冲区长度

- `fp` 流

- `返回值`

  成功：buf

  到达文件尾或出错：NULL

*从流中读一行字符串*

```c++
#include <stdio.h>
int fputs(const char *restrict str, FILE *restrict fp);
int puts(const char *str);
```

- `str` 字符串

- `fp` 流

- `返回值`

  成功：非负值

  失败：EOF

*将一行字符串（null结尾）写入到流*



## 5.8 标准I/O的效率

例：

```c++
#include "apue.h"

int 
main(void)
{
    int c;
    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            err_sys("output error");
    
    if (ferror(stdin))
        err_sys("input error");
    exit(0);
}
```

*用getc和putc将标准输入复制到标准输出*

例：

```c++
#include "apue.h"

int 
main(void)
{
    char buf[MAXLINE];
    while (fgets(buf, MAXLINE, stdin) != NULL)
        if (fputs(buf, stdout) == EOF)
            err_sys("output error");
    
    if (ferror(stdin))
        err_sys("input error");
    
    exit(0);
}
```

*用fgets和fputs将标准输入复制到标准输出*

![5_4](res/5_4.png)

*使用标准I/O例程得到的计时结果*



## 5.9 二进制I/O

```c++
#include <stdio.h>
size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
```

- `ptr` 缓冲区
- `size` 缓冲区长度
- `nobj` 要读/写的数据长度
- `fp` 流
- `返回值`对象数

*读/写二进制数据*



## 5.10 定位流

定位标准I/O流的方法：

- `ftell`和`fseek`函数；
- `ftello`和`fseeko`函数；
- `fgetpos`和`fsetpos`函数。

```c++
#include <stdio.h>
long ftell(FILE *fp);
```

- `fp` 流

- `返回值`

  成功：当前文件位置指示

  失败：-1

*定位标准I/O流*

```c++
#include <stdio.h>
int fseek(FILE *fp, long offset, int whence);
```

- `fp` 流

- `offset` 偏移量

- `whence` 位置

  - `SEEK_SET` 将文件的偏移量设置为距文件开始处offset个字节
  - `SEEK_CUR` 将文件偏移量设置为其当前值加offset，offset可正可负
  - `SEEK_END` 将文件的偏移量设置为文件长度加offset，offset可正可负

- `返回值`

  成功：0

  失败：非0

*定位标准I/O流*

```c++
#include <stdio.h>
void rewind(FILE *fp);
```

- `fp` 流

*将流设置到文件的起始位置*

```c++
#include <stdio.h>
off_t ftello(FILE *fp);
```

- `fp` 流

- `返回值`

  成功：当前文件位置

  失败：(off_t)-1

*定位标准I/O流*

```c++
#include <stdio.h>
int fseeko(FILE *fp, off_t offset, int whence);
```

- `fp` 流

- `offset` 偏移量

- `whence` 位置

  - `SEEK_SET` 将文件的偏移量设置为距文件开始处offset个字节
  - `SEEK_CUR` 将文件偏移量设置为其当前值加offset，offset可正可负
  - `SEEK_END` 将文件的偏移量设置为文件长度加offset，offset可正可负

- `返回值`

  成功：0

  失败：-1

*定位标准I/O流*

```c++
#include <stdio.h>
int fgetpos(FILE *restrict fp, fpos_t *restrict pos);
int fsetpos(FILE *fp, const fpos_t *pos);
```

- `fp` 流

- `pos` 当前位置

- `返回值`

  成功：0

  失败：非0

*获取/设置流的当前位置*



## 5.11 格式化I/O

```c++
#include <stdio.h>
#include <stdarg.h>
int printf(const char *restrict format, ...);
int vprintf(const char *restrict format, va_list arg);

int fprintf(FILE *restrict fp, const char *restrict format, ...);
int vfprintf(FILE *restrict fp, const char *restrict format, va_list arg);
```

- `format` 格式化字符串

- `fp` 流

- `返回值`

  成功：字符数

  失败：负数

*格式化输出字符到流*

```c++
#include <stdio.h>
#include <stdarg.h>
int sprintf(char *restrict buf, const char *restrict format, ...);
int vsprintf(char *restrict buf, const char *restrict format, va_list arg);

int snprintf(char *restrict buf, size_t n, const char *restrict format, ...);
int vsnprintf(char *restrict buf, size_t n, const char *restruct format, va_list arg);
```

- `buf` 缓冲区

- `format` 格式化字符串

- `n` 缓冲区长度

- `返回值`

  成功：存入数组的字符数

  失败：负数

*格式化输出字符串到缓冲区*

| 标志       | 说明                                                     |
| ---------- | -------------------------------------------------------- |
| `-`        | 在字段内左对齐输出                                       |
| `+`        | 总是显示带符号转换的符号                                 |
| `（空格）` | 如果一个字符不是符号，则在其前面加上一个空格             |
| `#`        | 指定另一种转换形式（例如，对于十六进制格式，加`0x`前缀） |
| `0`        | 添加前导0（而非空格）进行填充                            |

*转换说明中的标志部分*

| 长度修饰符 | 说明                           |
| ---------- | ------------------------------ |
| `hh`       | 有符号或无符号的char           |
| `h`        | 有符号或无符号的short          |
| `l`        | 有符号或无符号的long或者宽字符 |
| `ll`       | 有符号或无符号的long long      |
| `j`        | intmax_t或uintmax_t            |
| `z`        | size_t                         |
| `t`        | ptrdiff_t                      |
| `L`        | long double                    |

*转换说明中的长度修饰符*

| 转换类型 | 说明                                                     |
| -------- | -------------------------------------------------------- |
| `d, i`   | 有符号十进制                                             |
| `o`      | 无符号八进制                                             |
| `u`      | 无符号十进制                                             |
| `x, X`   | 无符号十六进制                                           |
| `f, F`   | double精度浮点数                                         |
| `e, E`   | 指数格式的double精度浮点数                               |
| `g, G`   | 解释为`f, F, e`或`E`, 取决于被转换的值                   |
| `a, A`   | 十六进制指数格式的double精度浮点数                       |
| `c`      | 字符（若带长度修饰符`l`，则为宽字符）                    |
| `s`      | 字符串（若带长度修饰符`l`，则为宽字符）                  |
| `p`      | 指向void的指针                                           |
| `n`      | 将到目前为止，所写的字符数写入到指针所指向的无符号整型中 |
| `%`      | `%`字符                                                  |
| `C`      | 宽字符（XSI扩展，等效于`1c`）                            |
| `S`      | 宽字符串（XSI扩展，等效于`1s`）                          |

*转换说明中的转换类型部分*

```c++
#include <stdio.h>
#include <stdarg.h>
int scanf(const char *restrict format, ...);
int vscanf(const char *restrict format, va_list arg);

int fscanf(FILE *restrict fp, const char *restrict format, ...);
int vfscanf(FIEL *restrict fp, const char *restrict format, va_list arg);

int sscanf(const char *restrict buf, const char *restrict format, ...);
int vsscanf(const char *restrict buf, const char *restrict format, va_list arg);
```

- `format` 格式化字符串

- `fp` 流

- `buf` 缓冲区

- `返回值`

  成功：输入的项数

  出错或再任意变换前已到达文件结尾：EOF

*格式化输入*

| 转换类型                 | 说明                                                   |
| ------------------------ | ------------------------------------------------------ |
| `d`                      | 有符号十进制，基数为10                                 |
| `i`                      | 有符号十进制，基数由输入格式决定                       |
| `o`                      | 无符号八进制（输入可选地有符号）                       |
| `u`                      | 无符号十进制，基数为10（输入可选地有符号）             |
| `x`                      | 无符号十进制（输入可选地有符号）                       |
| `a, A, e, E, f, F, g, G` | 浮点数                                                 |
| `c`                      | 字符（若带长度修饰符`l`，则为宽字符）                  |
| `s`                      | 字符串（若带长度修饰符`l`，则为宽字符串）              |
| `[`                      | 匹配列出的字符序列，以`]`终止                          |
| `[^`                     | 匹配除列出的字符以外的所有字符，以`]`终止              |
| `p`                      | 指向void的指针                                         |
| `n`                      | 将到目前为止读取的字符数写入到指针所指向的无符号整形中 |
| `%`                      | `%`字符                                                |
| `C`                      | 宽字符（XSI扩展，等效于`lc`）                          |
| `S`                      | 宽字符串（XSI扩展，等效于`ls`）                        |

*转换说明中的转换类型*



## 5.12 实现细节

```c++
#include <stdio.h>
int fileno(FILE *fp);
```

- `fp` 流
- `返回值` 与流相关联的文件描述符

*获得流的描述符*

例：

```c++
#include "apue.h"

void pr_stdio(const char *, FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);

int 
main(void)
{
    FILE *fp;
    
    fputs("enter any character\n", stdout);
    if (getchar() == EOF)
        err_sys("getchar error");
    fputs("one line to standard error\n", stderr);
    
    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr" stderr);
    
    if ((fp = fopen("/etc/passwd", "r")) == NULL)
        err_sys("fopen error");
    if (getc(fp) == EOF)
        err_sys("getc error");
    pr_stdio("/etc/passwd", fp);
    exit(0);
}

void 
pr_stdio(const char *name, FILE *fp)
{
    printf("stream = %s, ", name);
    if (is_unbuffered(fp))
        printf("unbuffered");
    else if (is_linebuffered(fp))
        printf("line buffered");
    else 
        printf("fully buffered");
    printf(", buffer size = %d\n", buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)

int 
is_unbuffered(FILE *fp)
{
    return(fp->_flags & _IO_UNBUFFERED);
}

int 
is_linebuffered(FILE *fp)
{
    return(fp->_flags & _IO_LINE_BUF);
}

int 
buffer_size(FILE *fp)
{
    return(fp->_IO_buf_end - fp->_IO_buf_base);
}

#elif defined(__SNBF)

int 
is_unbuffered(FILE *fp)
{
    return(fp->_flags & __SNBF);
}

int 
is_linebuffered(FILE *fp)
{
    return(fp->_flags & __SLBF)；
}

int 
buffer_size(FILE *fp)
{
    return(fp->_bf._size);
}

#elif defined(_IONBF)

#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif

int 
is_unbuffered(FILE *fp)
{
    return(fp->_flag & _IONBF);
}

int 
is_linebuffered(FILE *fp)
{
    return(fp->_flag & _IOLBF);
}

int 
buffer_size(FILE *fp)
{
#ifdef _LP64
    return(fp->_base - fp->_ptr);
#else
    return(BUFSIZ);
#endif
}

#else

#error unknown stdio implementation!

#endif
```

*对各个标准I/O流打印缓冲状态信息*



## 5.13 临时文件

```c++
#include <stdio.h>
char *tmpnam(char *ptr);
```

- `ptr` 文件路径
- `返回值` 创建的临时文件路径

*创建一个与现有文件名不同的临时文件路径（此函数最多调用`TMP_MAX`次）*

```c++
#include <stdio.h>
FILE *tmpfile(void);
```

- `返回值`

  成功：文件指针

  失败：NULL

*创建临时文件*

例：

```c++
#include "apue.h"

int 
main(void)
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;
    printf("%s\n", tmpnam(NULL));
    tmpnam(name);
    printf("%s\n", name);
    if ((fp = tmpfile()) == NULL)
        err_sys("tmpfile errorr");
    fputs("one line of output\n", fp);
    rewind(fp);
    if (fgets(line, sizeof(line), fp) == NULL)
        err_sys("fgets error");
    fputs(line, stdout);
    exit(0);
}
```

*tmpnam和tmpfile函数实例*

```c++
#include <stdio.h>
char *tempnam(const char *directory, const char *prefix);
```

- `directory` 目录
- `prefix` 前缀
- `返回值` 指向唯一路径名的指针

*是tmpnam的一个变体，它允许调用者为所产生的路径名指定目录和前缀，按下列顺序判断其条件并使用第一个为真的作为目录：*

*1. 如果定义了环境变量TMPDIR，则用其作为目录；*

*2. 如果参数directory非NULL，则用其作为目录；*

*3. 将`<stdio.h>`中的字符串`P_tmpdir`用作目录；*

*4. 将本地目录（通常是/tmp）用作目录。*

例：

```c++
#include "apue.h"
#include <errno.h>

void make_temp(char *template);

int 
main()
{
    char good_template[] = "/tmp/dirxxxx";
    char *bad_template = "/tmp/dirxxxx";
    
    printf("try to create first temp file...\n");
    make_temp(good_template);
    printf("trying to create second temp file...\n");
    make_temp(bad_template);
    exit(0);
}

void 
make_temp(char *template)
{
    int fd;
    struct stat sbuf;
    if ((fd = mkstemp(template)) < 0)
        err_sys("can't create temp file");
    printf("temp name = %s\n", template);
    close(fd);
    if (stat(template, &sbuf) < 0) {
        if (errno == ENOENT)
            printf("file doesn't exist\n");
        else
            err_sys("stat failed");
    } else {
        printf("file exists\n");
        unlink(template);
    }
}
```

*mkstemp函数的应用*

```c++
#include <stdlib.h>
int mkstemp(char *template);
```

- `template` 字符串模板

- `返回值`

  成功：文件描述符

  失败：-1

*创建临时文件*



## 5.14 标准I/O的替代软件



## 5.15 小结

