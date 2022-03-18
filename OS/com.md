# COM技术

[TOC]



## HRESULT和GUID

### HRESULT

HRESULT用来返回函数调用的相关信息，其结构如下：

`|重要位|设备代码|返回代码|`

- `重要位` (1bit)本次调用是否成功；
- `设备代码` (15bit)由微软定义，以`FACILITY_`开头；
- `返回代码` (16bit)函数调用返回结果。

例，HRESULT使用：

```c++
HRESULT hr = CoCreateInstance(...);
if (FAILED(hr)) // 调用FAILED宏而不是直接比较hr的值
    ...
    
hr = pI->QueryInterface(...); // 调用SUCCEEDED宏
if (SUCCEEDED(hr))
    ...
```

HRESULT支持用户自定义，但是需要满足以下规则：

- 不要将`0x0000`及`0x01FF`范围内的值作为返回代码（COM保留）；
- 不要传播`FACILITY_ITF`错误代码；
- 尽可能地使用通用的COM成功及失败代码；
- 避免定义自己的HRESULT，而可以在函数中使用一个输出参数。

例，自定义HRESULT：

```c++
MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 100);
MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 101);
```

### GUID

GUID（Globally Unique Identifier，全局唯一标识符）长度为16字节，用于标识全局唯一资源。

一些用于CLSID与GUID之间转换的函数：

| 函数            | 说明                                                     |
| --------------- | -------------------------------------------------------- |
| StringFromCLSID | 将CLSID转化为文本串                                      |
| StringFromIID   | 将IID转化为文本串                                        |
| StringFromGUID2 | 将GUID转化为文本串，此串将被存放在调用者所分配的缓冲区中 |
| CLSIDFromString | 将一个文本串转化为CLSID                                  |
| IIDFromString   | 将一个文本串转化为IID                                    |

**注意：GUID做参数时建议传引用而不是传值**。

#### ProgID

ProgID指的是由程序员给某个CLSID定义的标识符，其格式如下（非强制）：

`<Program>.<Component>.<Version>`

COM提供函数：`CLSIDFromProgID`，`ProgIDFromCLSID`用于ProgID和CLSID之间的转换。



## 创建组件

### IUnknown

客户同组件的交互都是通过IUnknown接口完成，其定义如下：

```c++
// msvc2015 64bit
IUnknown
        {
        public:
            BEGIN_INTERFACE
            virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
                /* [in] */ REFIID riid, // 标识客户所需的接口
                /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) = 0; // 所请求接口指针的地址

            virtual ULONG STDMETHODCALLTYPE AddRef( void) = 0; // 引用计数+1

            virtual ULONG STDMETHODCALLTYPE Release( void) = 0; // 引用计数-1

            template<class Q>
            HRESULT
#ifdef _M_CEE_PURE
            __clrcall
#else
            STDMETHODCALLTYPE
#endif
            QueryInterface(_COM_Outptr_ Q** pp)
            {
                return QueryInterface(__uuidof(Q), (void **)pp);
            }

            END_INTERFACE
        };
```

- `QueryInterface` 用来决定组件是否支持某个特定的接口。

例，QueryIntrface的使用：

```c++
void foo(IUnknown* pI)
{
    IX* pIX = NULL;
    
    HRESULT hr = pI->QueryInterface(IID_IX, (void**)&pIX); // 查询pIX是否支持IID_IX所标识的接口
    
    if (SUCCEEDED(hr))
    {
        pIX->Fx();
    }
}
```

**特性**

- QueryInterface返回的总是同一IUnknown指针；
- 若客户曾经获取过某个接口，那么它将总能获取此接口；
- 客户可以再次获取已经拥有的接口；
- 客户可以返回到起始接口；
- 若能够从某个接口获取某特定接口，那么可以从任意接口都将可以获取此接口。

**引用计数**

`QueryInterface::AddRef`和`QueryInterface::Release`用于实现对引用计数的管理，引用计数使用规则如下：

- 在返回之前调用`AddRef`；
- 使用完接口之后调用`Release`；
- 在赋值之后调用`AddRef`。

例，引用计数的使用：

```c++
IUnknown* pIUnknown = CreateInstance();
IX* pIX = NULL;
HRESULT hr = pIUnknown->QueryInterface(IID_IX, (void**)&pIX);
pIUnknown->Relase();
if (SUCCEEDED(hr))
{
    pIX->Fx();
    IX* pIX2 = pIX;
    pIX2->AddRef();
    pIX2->Fx();
    pIX2->Release();
    pIX->Release();
}
```

**注意：为每个接口单独维护一个引用计数而不是针对整个组件维护引用计数；原因如下：**

1. 这样可以使程序调试更为方便；
2. 支持资源的按需获取。

### CoCreateInstance

CoCreateInstance函数用于创建组件的实例，并返回此组件实例的某个接口。

```c++
// msvc2015 64bit
__inline _Check_return_ HRESULT CoCreateInstance(
    _In_     REFCLSID rclsid,
    _In_opt_ LPUNKNOWN pUnkOuter,
    _In_     DWORD dwClsContext,
    _In_     REFIID riid,
    _COM_Outptr_ _At_(*ppv, _Post_readable_size_(_Inexpressible_(varies))) LPVOID FAR* ppv)
```

- `rclsid` 待创建的CLSID；
- `pUnkOuter` 用于聚合组件；
- `dwClsContext` 限定所创建的组件的执行上下文，可以为以下值：
  - CLSCTX_INPROC_SERVER 客户希望创建在同一个进程中运行的组件。
  - CLSCTX_INPROC_HANDLER 客户希望创建进程中处理器。
  - CLSCTX_LOCAL_SERVER 客户希望创建一个在同一机器上的另外一个进程中运行的组件。
  - CLSCTX_REMOTE_SERVER 客户希望创建一个在远程机器上运行的组件。
- `riid` 组件上待使用的接口的IID；
- `ppv` 返回接口的指针。

例，CoCreateInstance的使用：

```c++
IX* pIX = NULL;
HRESULT hr = ::CoCreateInstance(CLSID_Component1,     // 标识
                                NULL,                 // 不需要聚合组件
                                CLSCTX_INPROC_SERVER, // 只装载包含进程中服务器或DLL中的组件
                                (void**)&pIX);
if (SUCCEEDED(hr))
{
    pIX->Fx();
    pIX->Release();
}
```

### CoGetClassObject

`CoGetClassObject`函数接收一个CLSID作为参数，并返回相应类厂中某个接口指针（功能类似于CoCreateInstance）；其声明如下：

```c++
// msvc2015 64bit
_Check_return_ WINOLEAPI
CoGetClassObject(
    _In_ REFCLSID rclsid,
    _In_ DWORD dwClsContext,
    _In_opt_ LPVOID pvReserved,
    _In_ REFIID riid,
    _Outptr_ LPVOID FAR * ppv
    );
```

- `rclsid` 组建的CLSID
- `dwclsContext` 上下文
- `pvReserved` 
- `riid`
- `ppv` 类厂中接口的指针

类厂所支持的用于创建组件的标准接口是IClassFactory，其声明如下：

```c++
// msvc2015 64bit
IClassFactory : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [annotation][unique][in] */ 
            _In_opt_  IUnknown *pUnkOuter,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE LockServer( 
            /* [in] */ BOOL fLock) = 0;
        
    };
```

在大多数情况下应优先使用`CoCreateInstance`而不是`CoGetClassObject`，但是以下情况例外：

- 需要用不同于IClassFactory的某个创建接口来创建组件；
- 需要创建同一个组件的多个实例。



## 组件注册

`DllRegisterServer`和`DllUnregisterServer`用于注册/解除组件在Windows注册表中的登记。



## 组件使用

### 组件的装载与卸载

TODO

### 进程通讯

COM采用的进程间通信方法：

本地过程调用（Local Procedure Call，LPC），用于同一机器的不同进程间通信。

远程调用（Remote Procedure Call，RPC），用于不同机器的进程间通信。

### 组件复用

TODO



## 参考

[1] Dale Rogerson.COM技术内幕.1th Edition
