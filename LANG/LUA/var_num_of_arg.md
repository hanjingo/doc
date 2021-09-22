[TOC]

# Lua可变长参数

lua中用`...`表示函数的可变参数，例：

```lua
function f(...)
	-- TODO    
end
```



## select

`select (index, ...)`

- `index` 起始位置（可负，负数表示从后向前索引，正数表示从前向后索引；当`index='#'`时，select返回参数的个数）

返回可变长参数的区间`[index, #...]`中的参数



## 遍历

### 直接遍历

利用`in ipairs`直接遍历

```lua
function f(...)
    for _, a in ipairs(...) do
        -- DO SOMETHING WITH arg
    end
end
```

**注意：使用`in ipairs`时会自动跳过nil值**

### 打包成一个数组

利用函数`table.pack`，将可变长参数打包成数组；例：

```lua
function f(...)
   local args = table.pack(...)
   for i = 1, args.n do
        local arg = args[i]
        -- DO SOMETHING WITH arg
   end
end
```

**注意：由于它是通过`table.pack`创建了一个新的表args，当参数过多时，效率不佳**

### 使用select

```lua
function f(...)
	for i = 1, select('#', ...) do -- '#'表示拿到可变长参数的长度
        local arg = select(i, ...)
        -- DO SOMETHING WITH arg
    end
end    
```



## 修改

### 将可变参数集合转化为table

```lua
local t = {...}
```

### 将集合拆分为可变参数

```lua
table.unpack(t)
```



## 参考

- [Lua-几种可变长参数的遍历方式](https://blog.csdn.net/u014078887/article/details/116568626)

