[TOC]

# Lua面向对象



## Class类

```lua
local _class = {}

function Class(super)
    local class_type = {}
    class_type.ctor = false 		-- 构造函数
    class_type.super = super 		-- 父类
    class_type.new = function(...)
        local obj = {}
        do 
            local create
            create = function (c, ...)
                if c.super then
                    create(c.super, ...)
                end
                if c.ctor then
                    c.ctor(obj, ...)
                end
            end
            create(class_type, ...)
        end
        setmetatable(obj, {__index = _class[class_type]}) -- 递归
        return obj
    end

    local vtbl={}
    _class[class_type] = vtbl

    setmetatable(class_type, {__newindex = 
        function (t, k, v)
            vtbl[k] = v
        end
    })

    if super then
        setmetatable(vtbl, {__index=
            function (t, k)
                local ret = _class[super][k]
                vtbl[k] = ret
                return ret
            end
        })
    end

    return class_type
end
```



## 工厂模式

TODO



## 示例

### 1 lua实现继承

```lua
local child = Class(parent)
function child:ctor()
    self.xxx = xxx
end
```



## 参考

- [云风-在 Lua 中实现面向对象](https://blog.codingnow.com/2006/06/oo_lua.html)
- [Lua官网 Object-Oriented Programming](http://www.lua.org/pil/16.html)
- [Lua 面向对象](https://www.runoob.com/lua/lua-object-oriented.html)

