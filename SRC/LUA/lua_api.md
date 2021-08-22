# LUA API

[TOC]

## 基础库

### assert

`assert(v[, message])`

- `v` 需要断言的语句
- `message` 输出yu ju

断言

### collectgrabage

`collectgarbage([opt [, arg]])`

- `opt`
  - `collect`
  - `stop`

启动垃圾收集

## 协程库

TODO



## 包管理库

TODO



## 字符串控制

TODO



## 基础UTF-8支持

TODO



## 表控制

TODO



## 数学函数

TODO



## 输入输出

TODO



## 操作系统库

TODO



## 调试库

TODO





lua_checkstack

lua_xmove

lua_atpanic

lua_version

lua_absindex

lua_gettop

lua_settop

reverse

lua_rotate

lua_copy

lua_pushvalue

lua_type

lua_typename

lua_iscfunction

lua_isinteger

lua_isnumber

lua_isstring

lua_isuserdata

lua_rawequal

lua_arith

lua_compare

lua_stringtonumber

lua_tonumberx

lua_tointegerx

lua_toboolean

lua_tostring

lua_rawlen

lua_tocfunction

lua_touserdata

lua_tothread

lua_topointer

lua_pushnil

lua_pushnumber

lua_pushinteger

lua_pushlstring

lua_pushstring

lua_pushstring

lua_pushvfstring

lua_pushfstring

lua_pushcclosure

lua_pushboolean

lua_pushlightuserdata

lua_pushthread

autgetstr

lua_getglobal

lua_gettable

lua_getfield

lua_geti

lua_rawget

lua_rawgeti

lua_rawgetp

lua_createtable

lua_getmetatable

lua_getuservalue

auxsetstr

lua_setglobal

lua_settable

lua_setfield

lua_seti

lua_rawset

lua_rawseti

lua_rawsetp

lua_setmetatable

lua_setuservalue

lua_callk

f_call

lua_pcallk

lua_load

lua_dump

lua_status

lua_gc

lua_next

lua_concat

lua_len

lua_getallocf

lua_setallocf

lua_newuserdata

aux_upvalue

lua_getupvalue

lua_setupvalue

getupvalref

lua_upvalueid

lua_upvaluejoin





