English | [中文版](com_zh.md)

# COM Technology

[TOC]



## HRESULT and GUID

### HRESULT

HRESULT is used to return information about function calls. Its structure is as follows:

`|Significant Bit|Device Code|Return Code|`

- `Significant Bit` (1 bit): Whether the call succeeded;
- `Device Code` (15 bits): Defined by Microsoft, starts with `FACILITY_`;
- `Return Code` (16 bits): The result of the function call.

Example, using HRESULT:
```c++
HRESULT hr = CoCreateInstance(...);
if (FAILED(hr)) // Use the FAILED macro instead of directly comparing hr
	...
    
hr = pI->QueryInterface(...); // Use the SUCCEEDED macro
if (SUCCEEDED(hr))
	...
```

HRESULT supports user customization, but the following rules must be met:
- Do not use values in the range `0x0000` to `0x01FF` as return codes (reserved by COM);
- Do not propagate `FACILITY_ITF` error codes;
- Use common COM success and failure codes as much as possible;
- Avoid defining your own HRESULT; instead, use an output parameter in the function.

Example, custom HRESULT:
```c++
MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 100);
MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 101);
```

### GUID

GUID (Globally Unique Identifier) is 16 bytes long and is used to identify globally unique resources.

Some functions for converting between CLSID and GUID:

| Function         | Description                                                  |
| ---------------- | ------------------------------------------------------------ |
| StringFromCLSID  | Converts CLSID to a string                                   |
| StringFromIID    | Converts IID to a string                                     |
| StringFromGUID2  | Converts GUID to a string, stored in a buffer allocated by the caller |
| CLSIDFromString  | Converts a string to CLSID                                   |
| IIDFromString    | Converts a string to IID                                     |

**Note: When passing GUID as a parameter, it is recommended to pass by reference rather than by value.**

#### ProgID

ProgID refers to an identifier defined by the programmer for a CLSID, usually in the following format (not mandatory):

`<Program>.<Component>.<Version>`

COM provides functions: `CLSIDFromProgID`, `ProgIDFromCLSID` for conversion between ProgID and CLSID.



## Creating Components

### IUnknown

Clients interact with components through the IUnknown interface, defined as follows:
```c++
// msvc2015 64bit
IUnknown
		{
		public:
			BEGIN_INTERFACE
			virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
				/* [in] */ REFIID riid, // Identifies the interface requested by the client
				/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) = 0; // Address of the requested interface pointer

			virtual ULONG STDMETHODCALLTYPE AddRef( void) = 0; // Increment reference count

			virtual ULONG STDMETHODCALLTYPE Release( void) = 0; // Decrement reference count

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

- `QueryInterface` is used to determine whether the component supports a specific interface.

Example, using QueryInterface:
```c++
void foo(IUnknown* pI)
{
	IX* pIX = NULL;
    
	HRESULT hr = pI->QueryInterface(IID_IX, (void**)&pIX); // Query if pIX supports the interface identified by IID_IX
    
	if (SUCCEEDED(hr))
	{
		pIX->Fx();
	}
}
```

**Features**

- QueryInterface always returns the same IUnknown pointer;
- If a client has previously obtained an interface, it can always obtain this interface again;
- Clients can reacquire interfaces they already own;
- Clients can return to the initial interface;
- If a specific interface can be obtained from one interface, it can be obtained from any interface.

**Reference Counting**

`QueryInterface::AddRef` and `QueryInterface::Release` are used to manage reference counting. The rules for using reference counting are as follows:
- Call `AddRef` before returning;
- Call `Release` after using the interface;
- Call `AddRef` after assignment.

Example, using reference counting:
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

**Note: Maintain a separate reference count for each interface rather than for the entire component; reasons:**
1. This makes debugging easier;
2. Supports on-demand resource acquisition.

### CoCreateInstance

The CoCreateInstance function is used to create an instance of a component and return a specific interface of that instance.
```c++
// msvc2015 64bit
__inline _Check_return_ HRESULT CoCreateInstance(
	_In_     REFCLSID rclsid,
	_In_opt_ LPUNKNOWN pUnkOuter,
	_In_     DWORD dwClsContext,
	_In_     REFIID riid,
	_COM_Outptr_ _At_(*ppv, _Post_readable_size_(_Inexpressible_(varies))) LPVOID FAR* ppv)
```
- `rclsid` CLSID to create;
- `pUnkOuter` for aggregating components;
- `dwClsContext` specifies the execution context of the component to be created, can be:
  - CLSCTX_INPROC_SERVER: create a component running in the same process.
  - CLSCTX_INPROC_HANDLER: create an in-process handler.
  - CLSCTX_LOCAL_SERVER: create a component running in another process on the same machine.
  - CLSCTX_REMOTE_SERVER: create a component running on a remote machine.
- `riid` IID of the interface to use on the component;
- `ppv` pointer to return the interface.

Example, using CoCreateInstance:
```c++
IX* pIX = NULL;
HRESULT hr = ::CoCreateInstance(CLSID_Component1,     // Identifier
								NULL,                 // No aggregation
								CLSCTX_INPROC_SERVER, // Only load in-process server or DLL component
								(void**)&pIX);
if (SUCCEEDED(hr))
{
	pIX->Fx();
	pIX->Release();
}
```

### CoGetClassObject

The `CoGetClassObject` function takes a CLSID as a parameter and returns a pointer to an interface in the corresponding class factory (similar to CoCreateInstance); its declaration is as follows:
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
- `rclsid` CLSID of the component
- `dwclsContext` context
- `pvReserved` 
- `riid`
- `ppv` pointer to the interface in the class factory

The standard interface supported by the class factory for creating components is IClassFactory, declared as follows:
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

In most cases, `CoCreateInstance` should be preferred over `CoGetClassObject`, except in the following cases:
- You need to use a creation interface other than IClassFactory to create the component;
- You need to create multiple instances of the same component.



## Component Registration

`DllRegisterServer` and `DllUnregisterServer` are used to register/unregister components in the Windows registry.



## Component Usage

### Loading and Unloading Components
TODO

### Interprocess Communication

COM uses the following interprocess communication methods:

Local Procedure Call (LPC), for communication between different processes on the same machine.

Remote Procedure Call (RPC), for communication between processes on different machines.

### Component Reuse
TODO



## References

[1] Dale Rogerson. Inside COM. 1st Edition
