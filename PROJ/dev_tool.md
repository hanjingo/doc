# Development Tools

[TOC]



## GCC

### GCC Options

| Option               | Description                                 |
| -------------------- | ------------------------------------------- |
| -fsanitize=address   | Enable AddressSanitizer for memory error detection |

### Using LeakSanitizer to Locate Memory Errors

1. Write a program with a memory leak:

	```c++
	#include <iostream>
   
	int main()
	{
		 int* data = new int[10];
		 return 0;
	}
	```

2. Compile

	```shell
	g++ -fsanitize=address -g main.cpp -o mem_leak
	```

3. Run and check error

	```sh
	./mem_leak
   
	================================================================
	==2275==ERROR: LeakSanitizer: detected memory leaks
   
	Direct leak of 40 byte(s) in 1 object(s) allocated from:
		 #0 0x7fb17b356357 in operator new[](unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:102
		 #1 0x7fb17bce825e in main /mnt/c/work/example/mem_leak/main.cpp:5
		 #2 0x7fb17ad59d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
   
	SUMMARY: AddressSanitizer: 40 byte(s) leaked in 1 allocation(s).
	```

---



## GDB

GDB stands for GNU Project Debugger and is a powerful debugging tool for C/C++. It helps you to poke around inside your C programs while they are executing and also allows you to see what exactly happens when your program crashes. GDB operates on executable files which binary files produced by the compilation process.

### GDB Commands

| Command                | Abbr | Description                                                  |
| ---------------------- | ---- | ------------------------------------------------------------ |
| `run`                  | r    | Restart and run the file                                     |
| `start`                | -    | Step execution, run program, stop at first statement         |
| `quit`                 | q    | Exit GDB                                                     |
| `list`                 | l    | View source code (l+n: from line n; l+function: view function) |
| `set`                  | -    | Set variable value                                           |
| `display`              | -    | Track variable value (display+var: track and show value at each stop) |
| `undisplay`            | -    | Stop tracking variable                                       |
| `watch`                | -    | Set watchpoint                                               |
| `i watch`              | -    | Show watchpoints                                             |
| `break`                | b    | Set breakpoint (b+n: at line n; b+function: at function start; break...if...: conditional) |
| `delete`               | d    | Delete breakpoint (d+n: delete nth breakpoint)               |
| `enable breakpoints`   | -    | Enable breakpoints                                           |
| `disable breakpoints`  | -    | Disable breakpoints                                          |
| `info breakpoints`     | -    | View all breakpoints                                         |
| `next`                 | n    | Step over (do not enter function)                            |
| `step`                 | s    | Step into function                                           |
| `continue`             | c    | Continue execution                                           |
| `finish`               | -    | Finish current function, return to caller                    |
| `backtrace`            | bt   | View call stack and hierarchy                                |
| `frame`                | f    | Switch stack frame                                           |
| `info`                 | i    | View local variable values                                   |
| `print`                | p    | Print value and address                                      |
| `x`                    | -    | View memory                                                  |

For more info, use GDB's `help` command.

### Debug File CMAKE Settings

```cmake
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$EN{CXXFLAGS} -O3 -Wall")
```

### Debugg Executable File

1. Write a program with a undefined behaviour bug:

   ```c++
   // gdb_test.cpp
   // g++ -g gdb_test.cpp -o gdb_test
   #include <stdio.h>
   
   int main()
   {
       int x;
       int a = x;
       int b = x;
       int c = a + b;
       printf("c=%d\n", c);
       return 0;
   }
   ```

2. Compile

   ```shell
   g++ -g gdb_test.cpp -o gdb_test
   ```

3. Run and check error

   ```sh
   hj@crypto:~/tmp/test$ g++ -g gdb_test.cpp -o gdb_test
   hj@crypto:~/tmp/test$ gdb gdb_test 
   GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
   Copyright (C) 2022 Free Software Foundation, Inc.
   License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
   Type "show copying" and "show warranty" for details.
   This GDB was configured as "x86_64-linux-gnu".
   Type "show configuration" for configuration details.
   For bug reporting instructions, please see:
   <https://www.gnu.org/software/gdb/bugs/>.
   Find the GDB manual and other documentation resources online at:
       <http://www.gnu.org/software/gdb/documentation/>.
   
   For help, type "help".
   Type "apropos word" to search for commands related to "word"...
   Reading symbols from gdb_test...
   (gdb) l
   1       // gdb_test.cpp
   2       // g++ -g gdb_test.cpp -o gdb_test
   3       #include <stdio.h>
   4
   5       int main()
   6       {
   7           int x;
   8           int a = x;
   9           int b = x;
   10          int c = a + b;
   (gdb) b 5
   Breakpoint 1 at 0x1155: file gdb_test.cpp, line 8.
   (gdb) info b
   Num     Type           Disp Enb Address            What
   1       breakpoint     keep y   0x0000000000001155 in main() at gdb_test.cpp:8
   (gdb) r
   Starting program: /home/hj/tmp/test/gdb_test 
   [Thread debugging using libthread_db enabled]
   Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
   
   Breakpoint 1, main () at gdb_test.cpp:8
   8           int a = x;
   (gdb) p x
   $1 = 0
   (gdb) n
   9           int b = x;
   (gdb) p b
   $2 = 0
   (gdb) p a
   $3 = 0
   (gdb) n
   10          int c = a + b;
   (gdb) n
   11          printf("c=%d\n", c);
   (gdb) n
   c=0
   12          return 0;
   (gdb) n
   13      }
   ```

### Debug Process

Use the following command to debug a running process:

```sh
gdb pfile PID # pfile is the process file, PID is the process ID
```

### Debug Core File

Use the following command to debug a core file:

```sh
gdb core # core: absolute path to core file
```

---



## Valgrind

Valgrind's memory check runs the test program in a special virtual machine, which monitors and records every operation, dynamically analyzes the program at runtime, captures and tracks memory operations, and provides warnings or reports as needed.

### Environment Setup

#### Command Installation

- Ubuntu/Debian

  ```sh
  sudo apt-get install valgrind
  ```

- CentOS/Fedora

  ```sh
  sudo yum install balgrind
  ```

- macos

  ```sh
  brew install valgrind
  ```

#### Compile and Install

```sh
./configure
make
make install
```

#### Test

1. Write a program with a memory leak:

	```c++
	#include <iostream>
   
	int main()
	{
		 int* data = new int[10];
		 return 0;
	}
	```

2. Compile

	```shell
	g++ -g main.cpp -o mem_leak
	```

3. Use valgrind to check

	```sh
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes ./mem_leak
	```

### Usage

valgrind command format: `valgrind [tool (optional)] [tool options (optional)] [program] [program options (optional)]`

**Note: The program to be tested by valgrind should be compiled with the "-g" flag to retain debug info.**

#### Command Options

| Tool     | Option                                                         |
| -------- | -------------------------------------------------------------- |
| General  | `-h` `--help` help<br>`--version` version<br>`-q` `--quiet` quiet mode<br>`-v` `--verbose` verbose<br>`--trace-children=no|yes` trace into children<br>`--trace-children-skip=patt1,patt2,...`<br>`--trace-children-skip-by-arg=patt1,patt2,...`<br>`--child-silent-after-fork=no`<br>`--vgdb=no`<br><br><br><br><br><br><br><br><br><br><br><br><br><br>`--track-fds=[default: no]` print open file descriptors on exit<br>`--time-stamp= [default: no]` enable timestamp<br>`--log-fd= [default: 2, stderr]` log output path<br>`--log-file=` log file name<br>`--log-file-exactly=` like `--log-file=` but no suffix<br>`--log-file-qualifier=` specify log file name via env var `$VAR`<br>`--log-socket=` output log to network address<br>`--xml= [default: no]`<br>`--tool= [default: memcheck]` specify tool<br/><br><br><br><br><br><br><br> |

Example:

```sh
TODO
```

#### memcheck tool

Fine-grained memory checker.

#### cachegrind

Cache simulator, shows instructions per line and cache misses.

#### callgrind

Adds call tracing to cachegrind, can generate call graphs.

#### helgrind

Detects race conditions.

#### massif

Heap profiler, measures heap memory usage.

#### Generate Visual Graphs

To generate visual graphs, download gprof2dot: https://pypi.org/project/gprof2dot/#files

---



## WireShark

TODO

---



## BreakPad

### Environment Setup

1. Download source code

	```sh
	# Qt environment (for Qt, use qBreakpad)
	git clone git@github.com:buzzySmile/qBreakpad.git
	cd qBreakpad/third_party
	git clone git@github.com:google/breakpad.git
	git clone git@github.com:ithaibo/linux-syscall-support.git lss
   
	# vs environment (TODO)
   
	# *nix (TODO)
	```

2. Compile

	```sh
	# Qt: open with Qt Creator, click build
   
	# *nix
	./configure
	make
	```

3. Test (qt+breakpad)

	1. Create a new Qt Console project named test

	2. Copy the following to test.pro

		```txt
		# qBreakPad required features
		QT += network
		CONFIG += thread exceptions rtti stl
      
		# qBreakPad header and lib paths
		win32:CONFIG(release, debug|release): {
		LIBS += -L$$PWD/qbreakpadlib/lib/release/ -lqBreakpad
		DEPENDPATH += $$PWD/qbreakpadlib/lib/release
		}
		else:win32:CONFIG(debug, debug|release): {
		LIBS += -L$$PWD/qbreakpadlib/lib/debug/ -lqBreakpad
		DEPENDPATH += $$PWD/qbreakpadlib/lib/debug
		}
      
		INCLUDEPATH += $$PWD/qbreakpadlib/include
      
		# Set release mode to generate debug info (MSVC:xx.pdb, *nix/mingw: exe with debug info)
		win32-msvc* {
			 QMAKE_LFLAGS_RELEASE += /MAP
			 QMAKE_CFLAGS_RELEASE += /Zi
			 QMAKE_LFLAGS_RELEASE += /debug /opt:ref
		}
      
		* {
			 QMAKE_CFLAGS_RELEASE += -g
			 QMAKE_CXXFLAGS_RELEASE += -g
			 QMAKE_CFLAGS_RELEASE -= -O2
			 QMAKE_CXXFLAGS_RELEASE -= -O2
			 QMAKE_LFLAGS_RELEASE = -mthreads -W
		}
      
		QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
		QMAKE_LFLAGS_RELEASE += $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
		```

	3. Copy the following as instructed:

		```sh
		# Adjust for platform, directory, and release/debug mode
		mkdir -r test/qbreakpadlib/lib
		cp qBreakpad_folder/handler/libqBreakpad.a test/qbreakpadlib/lib/release 
		cp qBreakpad_folder/handler/QBreakpadHandler.h test/qbreakpadlib/include
		cp qBreakpad_folder/handler/QBreakpadHandler.cpp test/qbreakpadlib/include
		cp qBreakpad_folder/handler/QBreakpadHttpUploader.h test/qbreakpadlib/include
		cp qBreakpad_folder/handler/QBreakpadHttpUploader.cpp test/qbreakpadlib/include
		cp -r qBreakpad_folder/handler/singletone test/qbreakpadlib/include
		```

	4. Edit main.cpp

		```cpp
		#include <QCoreApplication>
      
		#include "QBreakpadHandler.h"
      
		int main(int argc, char *argv[])
		{
			 QCoreApplication a(argc, argv);
      
			 QBreakpadInstance.setDumpPath("./");
      
			 int *i = nullptr;
			 *i = 1;
      
			 return a.exec();
		}
		```

	5. Click build and run

		**Note: Use the correct version of qBreakpad library for debug/release mode, do not mix!!!**

### Analyze Dump Files

#### Analyze dump files with Windbg

1. For executables built with mingw, use [cv2pdb](https://github.com/rainers/cv2pdb) to generate pdb files (skip if you already have pdb);
2. Select "File"->"Symbol File Path…", import symbol file (*.pdb);
3. Select "File"->"Source File Path…", import source code;
4. Select "File"->"Open Crash Dump…", import dump file;
5. Enter: !analyze -v to start analysis.

Note: If you get errors like `ntdll.wrong.symbols.dll`, enter the following command:

```cmd
TODO
```

#### Analyze dump files with VS

1. Place `*.exe`, `*.dmp`, `*.pdb` (if any) in the same directory, open dump file with VS and debug

2. For executables built with mingw, use [cv2pdb](https://github.com/rainers/cv2pdb) to generate pdb files, and set source code path:

	Click: View - Solution Explorer - Properties - Debug Source Files; import source file directory.

#### Analyze dump files with breakpad tools

1. Export dump file info

	```sh
	dump_syms test.exe test.pdb > test.sym
	head -n1 test.sym > head.txt # get first line for symbol info address
	mkdir -p ./symbols/test
	mv test.sym ./symbols/test
	minidump_stackwalk ./xx.dmp ./symbols > test.txt
	```

2. Use address2line or other tools to locate errors.

### Errors

1. In some environments, dump files cannot be generated

	Check:

	- Dump file generation path.
	- Insufficient permissions.
	- Exception caught by other programs (antivirus, input method, etc.).

### breakpad successor - crashpad

- [chromium/crashpad](https://github.com/chromium/crashpad)

---



## References

- [Valgrind Study Summary](https://blog.csdn.net/andylauren/article/details/93189740)
- [Practical Use of Valgrind and LeakSanitizer for Memory Leak Detection (C++)](https://blog.csdn.net/weixin_44046545/article/details/138417524)
- [Learn to Use valgrind for Memory Checking](https://xie.infoq.cn/article/4e903f97fda10366f714d8266)
- [Debugging Under Unix: `gdb` Tutorial](https://www.cs.cmu.edu/~gilpin/tutorial/)
- [CMake generate executable for gdb](https://blog.csdn.net/lemonaha/article/details/72837561)
- [Linux System Log Management](https://blog.csdn.net/j_1282937574/article/details/81258153)
- [core file generation and gdb debugging](https://blog.csdn.net/zhang_han666/article/details/80668002)
- [gdb debug coredump (principle)](https://blog.csdn.net/sunlin972913894/article/details/113001810)
- [Performance Testing Introduction - LoadRunner](https://www.admin5.com/article/20161114/695706.shtml)
- [google/breakpad](https://github.com/google/breakpad)
- [buzzySmile/qBreakpad](https://github.com/buzzySmile/qBreakpad)
- [Qt-mingw generate dump and debug with VS](https://blog.csdn.net/LiHong333/article/details/129798322)
- [Qt Windows QBreakpad Practice](https://blog.csdn.net/CLinuxF/article/details/122917770)
- [Cross-platform Qt dump file with Breakpad](https://blog.csdn.net/HeroGuo_JP/article/details/105387526)
- [Google Breakpad on Windows](https://blog.csdn.net/goforwardtostep/article/details/56304285)
- [window mingw qbreakpad generate dump](https://blog.csdn.net/woquNOKIA/article/details/127860799)
- [GDB: The GNU Project Debugger](https://sourceware.org/gdb/)
