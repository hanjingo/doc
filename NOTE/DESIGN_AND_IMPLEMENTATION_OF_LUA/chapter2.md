# 第二章 Lua中的数据类型



## Lua通用数据结构的实现

Lua中的数据类型：

| 宏                 | 类型            | 对应的数据结构       |
| ------------------ | --------------- | -------------------- |
| LUA_NONE           | 无类型          | 无                   |
| LUA_TNIL           | 空类型          | 无                   |
| LUA_TBOOLEAN       | 布尔类型        | 无                   |
| LUA_TLIGHTUSERDATA | 指针            | `void *`             |
| LUA_TNUMBER        | 数据            | `lua_Number`         |
| LUA_TSTRING        | 字符串          | `TString`            |
| LUA_TTABLE         | 表              | Table                |
| LUA_TFUNCTION      | 函数            | `CClosure, LClosure` |
| LUA_TUSERDATA      | 指针            | `void *`             |
| LUA_TTHREAD        | Lua虚拟机，协程 | `lua_State`          |

- `LUA_TLIGHTUSERDATA`由Lua外部的使用者来完成分配和释放
- `LUA_TUSERDATA` 由Lua内部来完成分配和释放

Lua通用数据结构的组织如下：

![datatype_common](res/datatype_common.png)

- `CommonHeader`

  ```c
  /**
   * @brief 宏定义需要GC的类型
   * @param next 指向下一个GC链表的成员 @param tt 数据的类型 @param marked GC相关的标记位
   */
  #define CommonHeader	GCObject *next; lu_byte tt; lu_byte marked
  ```

- `GCheader`(3.6.5已废弃)

- `GCObject`

  ```c
  /**
   * @brief 需要进行GC的数据类型 
   */
  struct GCObject {
    CommonHeader;
  };
  ```

- `Value`

  ```c
  /**
   * @brief 值
  */
  typedef union Value {
    GCObject *gc;    /* collectable objects */
    void *p;         /* light userdata */
    int b;           /* booleans */
    lua_CFunction f; /* light C functions */
    lua_Integer i;   /* integer numbers */
    lua_Number n;    /* float numbers */
  } Value;
  ```

- `TValuefields`

  ```c
  /** @brief 将值和类型结合在一起 @param value_ 值 @param tt_ 类型 */
  #define TValuefields	Value value_; int tt_
  ```

Lua表示任何类型的数据结构定义如下：

```c
/** @brief 万能的数据类型（可以用来标识任何数据和类型）*/
typedef struct lua_TValue {
  TValuefields;
} TValue;
```

