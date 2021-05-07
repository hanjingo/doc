# skynet内存分配
## 摘要
内存分配机制

## 详情
- skynet_malloc.h
- malloc_hook.h
- malloc_hook.c
- jemalloc

### 知识点
1. malloc，calloc，realloc的区别:

   malloc需要手动计算需要分配的空间大小，分配后不做初始化

   calloc不需要手动计算，分配后初始化为0

   realloc重新分配已申请的空间，用来缩/扩容
2. ssize_t和size_t的区别

   ssize_t:有符号

   size_t:无符号
### 定义全局变量
```c++

#define SLOT_SIZE 0x10000                     //槽大小 65536
#define PREFIX_SIZE sizeof(struct mem_cookie) //内存句柄大小
 
static size_t _used_memory = 0; 	//记录已分配块的大小
static size_t _memory_block = 0; 	//记录已分配块的数量
static struct mem_data mem_stats[SLOT_SIZE]; //内存数据集合
```

### 定义函数
```c++
//分配内存
#define skynet_malloc malloc
void * skynet_malloc(size_t sz);
//分配内存，不需要手动计算
#define skynet_calloc calloc
void * skynet_calloc(size_t nmemb,size_t size);
//调整大小
#define skynet_realloc realloc
void * skynet_realloc(void *ptr, size_t size);
//释放内存
#define skynet_free free
void skynet_free(void *ptr);
//复制str
char * skynet_strdup(const char *str);
//???
void * skynet_lalloc(void *ptr, size_t osize, size_t nsize);	// use for lua
//分配大内存
#define skynet_memalign memalign
void * skynet_memalign(size_t alignment, size_t size);
//分派对齐内存
#define skynet_aligned_alloc aligned_alloc
void * skynet_aligned_alloc(size_t alignment, size_t size);
//内存对齐
#define skynet_posix_memalign posix_memalign
int skynet_posix_memalign(void **memptr, size_t alignment, size_t size);
```