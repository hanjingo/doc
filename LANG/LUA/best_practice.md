# LUA最佳实践

1. 使用LUA过程中，尽量遵守3R原则：Reducing(减量化)，Reusing(再利用)，RecyCling(再循环)。

2. 在Lua中，应该尽量少地使用字符串连接操作符（建议使用table.concat），因为每一次连接都会生成一个新的字符串。

   例：

   ```lua
   local max = 10000
   local str_concat = function()
       local str1 = "abc"
       local str2 = "def"
       local start = os.clock()
       for i = 0, max do
           str1 = str1 .. str2
       end
       local finish = os.clock()
       local dur = finish - start
       print("str concat ", max, " times, cost:", dur * 1000, " ms")
   end
   local tbl_concat = function()
       local str1 = "abc"
       local str2 = "def"
       local start = os.clock()
       local tbl = {str1}
       for i = 2, max + 2 do
           tbl[i] = str2
       end
       str1 = table.concat(tbl)
       local finish = os.clock()
       local dur = finish - start
       print("tbl concat ", max, " times, cost:", dur * 1000, " ms")
   end
   str_concat()
   tbl_concat()
   ```

   | max     | 字符串连接耗时(ms) | table.concat耗时(ms) |
   | ------- | ------------------ | -------------------- |
   | 10000   | 19.902             | 0.675                |
   | 100000  | 570.305            | 3.512                |
   | 1000000 | 48999.008          | 35.809               |

3. 创建表时可以采用“预分配技术”，防止表散列操作长度小的表时造成的性能不佳。

4. 尽量不要将一个表混用数组和散列桶，即一个表最好只存放一类数据(array/map)。

5. 命名要规范，并且尽量使用local；不规范的非local变量可能会污染程序命名。

6. 当表的层级较深时，优先使用局部变量来缓存而不是直接使用表索引。

   例：

   ```lua
   tbl = {a = {b = {c = 1} } }
   local max = 10000000
   local test_tbl = function()
       local start = os.clock()
       for i = 0, max do 
           tbl.a.b.c = tbl.a.b.c + 1
           tbl.a.b.c = tbl.a.b.c - 1
   
           tbl.a.b.c = tbl.a.b.c * 2
           tbl.a.b.c = tbl.a.b.c / 2
       end
       local finish = os.clock()
       local dur = finish - start
       print("test_tbl calc: ", max, " time, cost:", dur * 1000, " ms")
   end
   local test_local = function()
       local start = os.clock()
       local tmp -- 使用临时对象
       for i = 0, max do
           tmp = tbl.a.b.c
           tmp = tmp + 1
           tmp = tmp - 1
           
           tmp = tmp * 2
           tmp = tmp / 2
   
           tbl.a.b.c = tmp
       end
       local finish = os.clock()
       local dur = finish - start
       print("test_local calc: ", max, " time, cost:", dur * 1000, " ms")
   end
   test_tbl()
   test_local()
   ```

   在同一台电脑的运行结果如下：

   | max       | 表索引方式耗时(ms) | 临时对象耗时(ms) |
   | --------- | ------------------ | ---------------- |
   | 1000000   | 179.204            | 49.951           |
   | 10000000  | 1761.347           | 514.481          |
   | 100000000 | 17572.626          | 5236.509         |

7. 不要在for循环中创建表和闭包。

8. 尽量避免使用loadstring函数。

   

