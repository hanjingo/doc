# makefile



make是一个自动化构建工具，通过读取“makefile”文件来构建项目。



## 分类

- GNU make
- BSD make
- Microsoft namke



## Makefile

### 语法

```makefile
宏名 = 文件1 文件2
target(要生成的文件) : prerequisites(被依赖的文件)
	命令1 # 注释
	命令n
	@# 回声
	
.PHONY: target
```

- `#` 表示注释

- `target...prerequisites` 目标

  用来指示make合适以及如何重新生成target或执行target下的命令；target通常是我们要生成的文件的名字，prerequisites是生成target所需的文件名列表；

- `.PHONY` 伪目标

  防止在Makefile中定义的只执行命令的目标和工作目录下的实际文件出现名字冲突。

- 宏

  "宏"指的是用一个字符串代替另一个字符串的功能；在makefile中可以使用“=”号来定义宏，使用“$(宏名)”来使用宏；还可以用“+=”追加宏的内容；习惯上，宏名使用大写；

- 回声

  正常情况下，make会打印每条命令，然后再执行，这就叫回声(echoing)。

  通过`@`可以关闭回声

- 通配符

  通配符（wildcard）用来指定一组符合条件的文件名。Makefile的通配符与Bash一致，主要有：`*`，`?`，`%`，`...`

- 变量

  - 内置变量（Implicit Variables）

    make命令提供一系列内置变量：

    - `$(CC)` 指向当前使用的编译器
    - `$(MAKE)` 指向当前使用的make工具
    - ...

  - 自动变量（Automatic Variables）

    make命令还提供一些自动变量，它们的值与当前规则有关，主要有：

    1. `$@` 指代当前目标

       例：

       ```makefile
       a.txt b.txt
       	touch $@
       ```

       等价于

       ```sh
       a.txt
       	touch a.txt
       b.txt
       	touch b.txt
       ```

    2. `$<` 指代第一个前置条件

       例：

       ```makefile
       a.txt: b.txt c.txt
       	cp $< $@
       ```

       等价于

       ```makefile
       a.txt: b.txt c.txt
       	cp b.txt a.txt
       ```

    3. `$?` 指代目标更新的所有前置条件，之间以空格分隔。

    4. `$^` 指代所有前置条件，之间以空格分隔。

    5. `$`

    6. `$(@D)和$(@F)` 分别指向`$@`的目录名和文件名。

    7. `$(<D)和$(<F)` 分别指向`$<`的目录名和文件名

- 函数

  makefile可以使用如下函数：

  - `shell` 用来执行shell命令

    例：

    ```makefile
    srcfiles := $(shell echo src/{00..99}.txt)
    ```

  - `wildcard` 用来在makefile中替换bash的通配符

    例：

    ```makefile
    srcfiles := $(wildcard src/*.txt)
    ```

  - `subst` 用来文本替换

    用法：`$(subst from,to,text)`

    例：

    ```makefile
    # 将字符串"feet on the street"替换成"fEEt on the strEEt"
    $(subst ee,EE,feet on the street) 
    ```

  - `patsubst` 用于模式匹配的替换

    例：

    ```makefile
    # 将文件名"x.c.c bar.c"，替换成"x.c.o bar.o"
    $(patsubst %.c,%.o,x.c.c bar.c)
    ```

例：

```makefile
OBJECTS = main.o text.o
editor: $(OBJECTS)
	gcc -o editor $(OBJECTS)

main.o: main.c def.h
	gcc -c main.c
text.o: text.c com.h
	gcc -c text.c
%.o: other.c

clean:
	rm editor main.o text.o *.o
	
install:editor
	mv editor $(INSTALL_PATH)
	
@# make结束
.PHONY: editor clean
```



## 参考

- [维基百科-make](https://zh.wikipedia.org/wiki/Make)
- [GNU make](https://www.gnu.org/software/make/manual/make.html)
- [如何系统地学习 Makefile 相关的知识（读/写）？](https://www.zhihu.com/question/23792247/answer/2902637809?utm_campaign=shareopn&utm_medium=social&utm_oi=974639756117843968&utm_psn=1612875781914554368&utm_source=wechat_session)

