English | [中文版](makefile_zh.md)

# makefile

[TOC]

make is an automated build tool that builds projects by reading the "makefile" file.


## Categories

- GNU make
- BSD make
- Microsoft nmake


## Makefile

### Syntax

```makefile
MACRO = file1 file2
target (file to generate) : prerequisites (dependent files)
	command1 # comment
	commandn
	@# echo

.PHONY: target
```

- `#` indicates a comment

- `target...prerequisites` target

	Used to tell make when and how to regenerate the target or execute the commands under the target; target is usually the name of the file we want to generate, prerequisites are the list of files needed to generate the target.

- `.PHONY` phony target

	Prevents conflicts between command-only targets defined in the Makefile and actual files in the working directory with the same name.

- Macro

	A "macro" is a way to substitute one string for another; in makefile, use `=` to define a macro, use `$(MACRO)` to use it; you can also use `+=` to append to a macro; by convention, macro names are uppercase.

- Echo

	By default, make prints each command before executing it, called echoing.

	Use `@` to turn off echoing.

- Wildcards

	Wildcards are used to specify a set of matching filenames. Makefile wildcards are the same as Bash: `*`, `?`, `%`, `...`

- Variables

	- Implicit Variables

		make provides a series of built-in variables:

		- `$(CC)` points to the current compiler
		- `$(MAKE)` points to the current make tool
		- ...

	- Automatic Variables

		make also provides some automatic variables whose values depend on the current rule, mainly:

		1. `$@` refers to the current target

			 Example:

			 ```makefile
			 a.txt b.txt
			 	touch $@
			 ```

			 Equivalent to

			 ```sh
			 a.txt
			 	touch a.txt
			 b.txt
			 	touch b.txt
			 ```

		2. `$<` refers to the first prerequisite

			 Example:

			 ```makefile
			 a.txt: b.txt c.txt
			 	cp $< $@
			 ```

			 Equivalent to

			 ```makefile
			 a.txt: b.txt c.txt
			 	cp b.txt a.txt
			 ```

		3. `$?` refers to all prerequisites that are newer than the target, separated by spaces.

		4. `$^` refers to all prerequisites, separated by spaces.

		5. `$`

		6. `$(@D)` and `$(@F)` refer to the directory and filename of `$@` respectively.

		7. `$(<D)` and `$(<F)` refer to the directory and filename of `$<` respectively.

- Functions

	Makefile supports the following functions:

	- `shell` executes shell commands

		Example:

		```makefile
		srcfiles := $(shell echo src/{00..99}.txt)
		```

	- `wildcard` replaces bash wildcards in makefile

		Example:

		```makefile
		srcfiles := $(wildcard src/*.txt)
		```

	- `subst` for text replacement

		Usage: `$(subst from,to,text)`

		Example:

		```makefile
		# Replace "feet on the street" with "fEEt on the strEEt"
		$(subst ee,EE,feet on the street) 
		```

	- `patsubst` for pattern matching replacement

		Example:

		```makefile
		# Replace filenames "x.c.c bar.c" with "x.c.o bar.o"
		$(patsubst %.c,%.o,x.c.c bar.c)
		```

Example:

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

@# make end
.PHONY: editor clean
```


## References

- [Wikipedia - make](https://en.wikipedia.org/wiki/Make_(software))
- [GNU make](https://www.gnu.org/software/make/manual/make.html)
- [How to systematically learn Makefile knowledge (read/write)?](https://www.zhihu.com/question/23792247/answer/2902637809?utm_campaign=shareopn&utm_medium=social&utm_oi=974639756117843968&utm_psn=1612875781914554368&utm_source=wechat_session)
