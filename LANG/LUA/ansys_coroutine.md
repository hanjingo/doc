# Lua源码分析-协程

[TOC]



## 创建

coroutine.create

TODO



## 执行

coroutine.resume

TODO



## 暂停

coroutine.yield

TODO



## 终止

- 主函数返回
- 未捕获错误



## 例

```lua
function foo(a)
  print("foo", a)
  return coroutine.yield(2*a)
end

co = coroutine.create(function(a, b)
  print("co-body", a, b)
  local r = foo(a+1)
  print("co-body", r)
  local r, s = coroutine.yield(a+b, a-b)
  print("co-body", r, s)
  return b, "end"
end)

print("main", coroutine.resume(co, 1, 10))
print("main", coroutine.resume(co, "r"))
print("main", coroutine.resume(co, "x", "y"))
print("main", coroutine.resume(co, "x", "y"))
```

