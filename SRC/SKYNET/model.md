# skynet模块机制
## 摘要
ksynet模块

## 详情
- skynet_module.h
- skynet_module.c

### 知识点
1. void *dlopen(const char *filename, int flags):
这个函数加载由以null结尾的字符串文件名命名的动态共享对象（共享库）文件，并为加载的对象返回不透明的“句柄”。
此句柄与 dlopen API 中的其他函数一起使用，例如dlsym()，dladdr()，dlinfo()和dlclose()。
如果 filename 为 NULL，则返回的句柄用于主程序。如果 filename 包含斜杠（“/”），则它被解释为（相对或绝对）路径名。否则，动态链接器将按如下方式搜索对象:
> - (仅限ELF)如果调用程序的可执行文件包含 DT_RPATH 标记，并且不包含 DT_RUNPATH 标记，则会搜索 DT_RPATH 标记中列出的目录
> - 如果在程序启动时，环境变量 LD_LIBRARY_PATH 被定义为包含以冒号分隔的目录列表，则会搜索这些目录。 （作为安全措施，set-user-ID 和 set-group-ID程序将忽略此变量。）
> - （仅限ELF）如果调用程序的可执行文件包含　DT_RUNPATH　标记，则搜索该标记中列出的目录
> - 检查缓存文件/etc/ld.so.cache（由ldconfig（8）维护）以查看它是否包含filename的条目
> - 搜索目录 /lib和 /usr/lib（按此顺序）
如果 filename 指定的对象依赖于其他共享对象，则动态链接器也会使用相同的规则自动加载这些对象,
如果这些对象依次具有依赖性，则此过程可以递归地发生）;flags 参数必须包括以下两个值中的一个:
> - RTLD_LAZY: 执行延迟绑定。仅在执行引用它们的代码时解析符号。如果从未引用该符号，则永远不会解析它（只对函数引用执行延迟绑定;在加载共享对象时，对变量的引用总是立即绑定）。自 glibc 2.1.1，此标志被LD_BIND_NOW环境变量的效果覆盖。
> - RTLD_NOW:如果指定了此值，或者环境变量LD_BIND_NOW设置为非空字符串，则在dlopen()返回之前，将解析共享对象中的所有未定义符号。如果无法执行此操作，则会返回错误。
flags 也可以通过以下零或多个值进行或运算设置:
> - RTLD_GLOBAL: 此共享对象定义的符号将可用于后续加载的共享对象的符号解析。
> - RTLD_LOCAL: 这与RTLD_GLOBAL相反，如果未指定任何标志，则为默认值。此共享对象中定义的符号不可用于解析后续加载的共享对象中的引用。
> - RTLD_NODELETE (since glibc 2.2): 在dlclose()期间不要卸载共享对象。因此，如果稍后使用dlopen()重新加载对象，则不会重新初始化对象的静态变量。
> - RTLD_NOLOAD (since glibc 2.2): 不要加载共享对象。这可用于测试对象是否已经驻留（如果不是，则dlopen()返回 NULL，如果是驻留则返回对象的句柄）。此标志还可用于提升已加载的共享对象上的标志。例如，以前使用RTLD_LOCAL加载的共享对象可以使用RTLD_NOLOAD | RTLD_GLOBAL重新打开。
> - RTLD_DEEPBIND (since glibc 2.3.4): 将符号的查找范围放在此共享对象的全局范围之前。这意味着自包含对象将优先使用自己的符号，而不是全局符号，这些符号包含在已加载的对象中。

2. dlmopen()
这个函数除了以下几点与dlopen()有所不同外，都执行同样的任务。dlmopen()与dlopen()的主要不同之处主要在于它接受另一个参数 lmid，它指定应该被加载的共享对象的链接映射列表（也称为命名空间）。对于命名空间，Lmid_t 是个不透明的句柄。lmid 参数要么是已经存在的命名空间的ID（这个命名空间可以通过dlinfo RTLD_DI_LMID请求获得）或者是以下几个特殊值中的其中一个：
> - LM_ID_BASE:在初始命名空间中加载共享对象（即应用程序的命名空间）。
> - LM_ID_NEWLM:创建新的命名空间并在该命名空间中加载共享对象。该对象必须已正确链接到引用 所有其他需要的共享对象，因为新的命名空间最初为空。
如果 filename 是 NULL，那么 lmid 的值只能是LM_ID_BASE。

3. dlclose()
dlclose()减少指定句柄 handle 引用的动态加载共享对象的引用计数。如果引用计数减少为０，那么这个动态加载共享对象将被真正卸载。所有在dlopen()被调用的时候自动加载的共享对象将以相同的方式递归关闭。

dlclose()成功返回并不保证与句柄相关的符号将从调用方的地址空间中删除。除了显式通过dlopen()调用产生的引用之外，一些共享对象作为依赖项可能已被隐式加载（和引用计数）。只有当所有引用都已被释放才可以从地址空间中删除共享对象。

4. void *dlsym(void *handle, const char *symbol)
dlsym()接受由dlopen()返回的动态加载的共享对象的“句柄”，并返回该符号加载到内存中的地址。如果未找到符号，则在加载该对象时，在指定对象或dlopen()自动加载的任何共享对象中，dlsym()将返回NULL。（dlsym()通过这些共享对象的依赖关系树进行宽度优先搜索。）
因为符号本身可能是 NULL（所以dlsym()返回 NULL 并不意味着错误），因此判断是否错误的正确做法是调用dlerror()清除任何旧的错误条件，然后调用dlsym()，并且再次调用dlerror()，保存其返回值，判断这个保存的值是否是 NULL。

可以在句柄中指定两个特殊的伪句柄：
> - RTLD_DEFAULT: 使用默认共享对象搜索顺序查找所需符号的第一个匹配项。搜索将包括可执行文件中的全局符号及其依赖项，以及使用RTLD_GLOBAL 标志动态加载的共享对象中的符号。
> - RTLD_NEXT:在当前对象之后的搜索顺序中查找下一个所需符号。这允许人们在另一个共享对象中提供一个函数的包装器，因此，例如，预加载的共享对象中的函数定义（参见ld.so（8）中的LD_PRELOAD）可以找到并调用在另一个共享对象中提供的“真实”函数（或者就此而言，在存在多个预加载层的情况下，函数的“下一个”定义）。

dlvsym()除了比dlsym()多提供了一个额外的参数外，其余与dlsym()相同。

### 定义全局变量
```c++
//模块集合单例
static struct modules * M = NULL;
//最大模块数量
#define MAX_MODULE_TYPE 32 
```

### 定义全局函数
```c++
//插入模块
void skynet_module_insert(struct skynet_module *mod);
//查询模块
struct skynet_module * skynet_module_query(const char * name);
//创建模块
void * skynet_module_instance_create(struct skynet_module *);
//初始化模块句柄
int skynet_module_instance_init(struct skynet_module *, void * inst, struct skynet_context *ctx, const char * parm);
//释放模块
void skynet_module_instance_release(struct skynet_module *, void *inst);
//处理模块信号
void skynet_module_instance_signal(struct skynet_module *, void *inst, int signal);
//初始化模块
void skynet_module_init(const char *path);
```

### 定义类
```c++
//skynet_module的create函数
typedef void * (*skynet_dl_create)(void);
//skynet_module的init函数；inst：句柄， ctx:上下文, parm:参数
typedef int (*skynet_dl_init)(void * inst, struct skynet_context *ctx, const char * parm);
//skynet_module的release函数； inst：句柄
typedef void (*skynet_dl_release)(void * inst);
//skynet_module的signal函数；    inst：句柄， signal：信号
typedef void (*skynet_dl_signal)(void * inst, int signal);
//skynet模块
struct skynet_module {
    const char * name;            //模块名字
    void * module;                //模块指针
    skynet_dl_create create;      //创建
    skynet_dl_init init;          //初始化
    skynet_dl_release release;    //释放
    skynet_dl_signal signal;      //处理信号
};
 
//模块集合
struct modules {
    int count;                                //模块类型id
    struct spinlock lock;                     //自旋锁
    const char * path;                        //模块集合的公有路径
    struct skynet_module m[MAX_MODULE_TYPE];  //模块集合
};
```

### 定义函数
```c++
//尝试打开dll模块;    m：模块集合， name：模块名字
static void * _try_open(struct modules *m, const char * name)
//根据模块名查找模块;
static struct skynet_module * _query(const char * name)
//根据api拿函数
static void * get_api(struct skynet_module *mod, const char *api_name)
//打开模块
static int open_sym(struct skynet_module *mod)
```