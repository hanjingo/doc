English | [中文版](cmake_zh.md)

# CMake

[TOC]



## Basics

### Code of Conduct

1. Do not use functions with global scope, such as `link_directories`, `include_libraries`, etc.
2. Do not add unnecessary PUBLIC requirements.
3. Do not add GLOB files in the file function.
4. Link libraries directly to the targets that need to be built; if possible, always explicitly link libraries to targets.
5. When linking libraries, do not omit the PUBLIC or PRIVATE keyword; omitting them will cause all subsequent links to default.
6. Commands are case-insensitive, but parameters and variables are case-sensitive. **It is recommended to use uppercase for variables, lowercase for functions and macros.**

### Basic Principles

1. Variables are accessed using `${}` syntax, but in IF control statements, use the variable name directly.
2. System variables are accessed using `ENV{varname}`.
3. Command format: `command(param1 param2 ...)`.
4. make does not support make distclean.
5. In CMake, C++ is the default programming language; to compile other languages, use the `LANGUAGES` option explicitly.
6. When using the cmake command, set options with `-D`, and use `-G` to set the generator.
7. Use `EQUAL` for string comparison.

### Conditional Control

#### IF...ELSE...ENDIF

```cmake
if(<condition>)
	<commands>
elseif(<condition>) 
	<commands>
else()
	<commands>
endif()
```

Conditions include:

- Basic expressions

	| condition                                                    | Description |
	| ------------------------------------------------------------ | ---------- |
	| 1<br>ON<br>YES<br>true<br>Y<br>nonzero value                 | true       |
	| 0<br>OFF<br>NO<br>false<br>N<br>IGNORE<br>NOTFOUND<br>empty string<br>xxx-NOTFOUND | false      |

- Logical expressions

	| condition | Description |
	| --------- | ----------- |
	| NOT       | NOT        |
	| AND       | AND        |
	| OR        | OR         |

- Extended checks

	| condition     | Description |
	| ------------- | ------------------------------------------------------------ |
	| COMMAND       | True if the given name is a callable command, macro, or function |
	| POLICY        | True if the given name is an existing policy (format CMP<NNNN>) |
	| TARGET        | True if the given name is a logical target created by add_executable(), add_library(), or add_custom_target() in any directory |
	| TEST          | True if the given name is a test created by add_test() (since 3.3) |
	| DEFINED<name> | True if a variable with the given `<name>` exists |
	| CACHE{<name>} | True if a cache variable with the given `<name>` exists |
	| ENV{<name>}   | True if an environment variable with the given `<name>` exists |
	| IN_LIST       | True if the given element is in the named list variable (since 3.3) |

- File operations

	| condition     | Description |
	| ------------- | ------------------------------------------------------------ |
	| EXISTS        | True if the specified file or directory exists |
	| IS_NEWER_THAN | True if file1 is newer than file2 or if either file does not exist |
	| IS_DIRECTORY  | True if the given name is a directory |

Use IF for conditional control.

Example:

```cmake
set(ok 0)
set(ok OFF)
set(ok NO)
set(ok false)
set(ok N)
set(ok IGNORE)
set(ok NOTFOUND)
set(ok "")
set(ok xxx-NOTFOUND)

if (ok)
		message("do ok")
else()
		message("do fail")
endif()
```

#### WHILE

```cmake
while(<condition>)
	<commands>
endwhile()
```

Loop executes commands while the condition is true.

#### FOREACH

Iterate over lists, with 4 usage patterns:

- Use `foreach(loop_var arg1 arg2 ...)` to provide a loop variable and explicit item list (if the item list is in a variable, it must be expanded, i.e., `${sources_with_lower_optimization}` must be passed as a parameter).
- Specify a range to loop over integers
	// ...existing code...
- Loop over list value variables
	// ...existing code...
- Loop over variables
	// ...existing code...

Example:

```cmake
list(
		APPEND hello_src
)

foreach(f IN LISTS hello_src)
		...
endforeach()
```

### Project Structure

- `Makefile`: make will run commands to build the project
- `CMakefile`: directory containing temporary files, CMake uses it to detect OS, compiler, etc.
- `cmake_install.cmake`: CMake script handling install rules, used during project installation
- `CMakeCache.txt`: CMake cache, used when re-running configuration

---


## Functions

### CMake Functions

**ADD_COMPILE_DEFINITIONS**

TODO

**ADD_COMPILE_OPTIONS**

TODO

**ADD_CUSTOM_COMMAND**

```cmake
add_custom_command(OUTPUT output1 [output2 ...]
									 COMMAND command1 [ARGS] [args1...]
									 // ...existing code...
									 [COMMAND_EXPAND_LISTS])
```

Execute a command.

Example:

```cmake
add_custom_command(
		Setup ALL hello.exe /V1 hello.nsi
		// ...existing code...
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
```

**ADD_CUSTOM_TARGET**

TODO

**ADD_DEFINITIONS**

```cmake
add_definitions(-DFOO -DBAR ...)
```

Add compiler command line definitions (flags defined by `-D`).

```cmake
add_definitions(-DABC -DHELLO)
```

```c++
#ifdef ABC
		...
#endif

#ifdef HELLO
		...
#endif
```

**ADD_DEPENDENCIES**

```cmake
add_dependencies(<target> [<target-dependency>]...)
```

- `target`: top-level target
- `target-dependency`: dependency

Add a dependency between top-level targets.

```cmake
add_subdirectory(lib1)

add_dependencies(hello lib1)
```

**ADD_EXECUTABLE**

```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
							 [EXCLUDE_FROM_ALL]
							 [source1] [source2 ...]) 
```

Generate an executable.

```cmake
add_executable(<name> IMPORTED [GLOBAL])
```

Import an executable.

```cmake
add_executable(<name> ALIAS <target>)
```

Alias an executable.

Example:

```cmake
add_executable(hello 
		main.c
)
```

**ADD_LIBRARY**

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
						[EXCLUDE_FROM_ALL]
						[<source>...])
```

- STATIC: static library
- SHARED: shared library
- OBJECT: object file
- MODULE: DSO group (for dynamic loading, runtime plugins; not linked to any project target)
- IMPORTED: immutable library (for building existing dependencies)
- INTERFACE: interface library (for use by targets outside the project)
- ALIAS: alias (for defining an alias for an existing library target)

Create a library (dynamic/static/object/...).

```cmake
add_library(<name> OBJECT [<source>...])
```

Create an object file dependency library.

```cmake
add_library(<name> OBJECT [<source>...])
```

Create an interface dependency.

```cmake
add_library(<name> <type> IMPORTED [GLOBAL])
```

Import a dependency.

Example:

```cmake
# Create hello.lib
add_library(hello
		STATIC
)
```

**ADD_LINK_LIBRARY**

```cmake
link_libraries([item1 [item2 [...]]]
							 [[debug|optimized|general] <item>] ...)
```

Link dependency files (libs) to executables at link time.

```cmake
target_link_libraries(hello
		PRIVATE
)
```

**ADD_LINK_OPTIONS**

```cmake
add_link_options(<option> ...)
```

Add options to executables, shared libraries, or module library targets in the current and subdirectories during the link step.

**ADD_SUBDIRECTORY**

`ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])` 

- `source_dir`: subdirectory of source files
- `binary_dir`: build output (intermediate build results) path
- `EXCLUDE_FROM_ALL`: exclude this directory from the build process

Add a subdirectory containing source files to the current project, optionally specifying where to store intermediate and target binaries.

```cmake
ADD_SUBDIRECTORY(sub_dir)
```

**ADD_TEST**

```cmake
add_test(NAME <name> COMMAND <command> [<arg>...]
				 [CONFIGURATIONS <config>...]
				 // ...existing code...
				 [COMMAND_EXPAND_LISTS])
```

- `COMMAND`: command line
- `CONFIGURATIONS`: configuration
- `WORKING_DIRECTORY`: working directory
- `COMMAND_EXPAND_LISTS`: expand COMMAND parameter (added in 3.16)

Add a test (see [CTest](#CTest)).

**AUX_SOURCE_DIRECTORY**

```cmake
aux_source_directory(<dir> <variable>)
```

Collect all source file names in the specified path and store the output list in the specified variable.

```cmake
aux_source_directory(. HELLO_SRC) # Find all source files in the current directory and save to HELLO_SRC
```

**CMAKE_DEPENDENT_OPTION**

```cmake
cmake_dependent_option(<option> "<help_text>" <value> <depends> <force>)
```

Define an option that depends on other options.

```cmake
cmake_dependent_option(
		MAKE_STATIC_LIBRARY "compile static library" OFF # OFF depends on USE_LIBRARY=ON
		"USE_LIBRARY" ON
)
```

```sh
cmake -DUSE_LIBRARY=ON .. # MAKE_STATIC_LIBRARY=OFF
```


**CMAKE_MINIMUM_REQUIRE**

```cmake
cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])
```

Minimum CMake version requirement.

```cmake
cmake_minimum_required()

cmake_minimum_required(VERSION 3.24.1)
```

**CONFIGURE_FILE**

Configure file with source version check.

```cmake
configure_file(hello.h.in hello.h)
```

**ENABLE_TESTING**

```cmake
configure_file(<input> <output>
							 [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
								// ...existing code...
							 [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

Enable testing for the current and subdirectories.

**EXEC_PROGRAM**

```cmake
exec_program(Executable [directory in which to run]
						 [ARGS <arguments to executable>]
						 // ...existing code...
						 [RETURN_VALUE <var>])
```

Whether to build the test target, involving all project directories.

**EXECUTE_PROCESS**

Execute a command and get its result.

```cmake
find_package(GIT QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
										// ...existing code...
		endif()
endif()
```

**FILE**

```cmake
Reading
	file(READ <filename> <out-var> [...])
	// ...existing code...
	file(GET_RUNTIME_DEPENDENCIES [...])

Writing
	file({WRITE | APPEND} <filename> <content>...)
	// ...existing code...
	file(CONFIGURE OUTPUT <output-file> CONTENT <content> [...])

Filesystem
	file({GLOB | GLOB_RECURSE} <out-var> [...] [<globbing-expr>...])
	// ...existing code...
	file(CHMOD_RECURSE <files>... <directories>... PERMISSIONS <permissions>... [...])

Path Conversion
	file(REAL_PATH <path> <out-var> [BASE_DIRECTORY <dir>] [EXPAND_TILDE])
	// ...existing code...
	file({TO_CMAKE_PATH | TO_NATIVE_PATH} <path> <out-var>)

Transfer
	file(DOWNLOAD <url> [<file>] [...])
	file(UPLOAD <file> <url> [...])

Locking
	file(LOCK <path> [...])

Archiving
	file(ARCHIVE_CREATE OUTPUT <archive> PATHS <paths>... [...])
	file(ARCHIVE_EXTRACT INPUT <archive> [...])
```

File operation commands.

**FIND_PACKAGE**

- TODO: library name
- TODO: minimum library version
- REQUIRED: module is required (fail if not found)
- COMPONENTS: list of libraries to find

Search for CMAKE modules in the folders listed in `CMAKE_MODULE_PATH` with the format `Findxxx.cmake`.

```cmake
find_package(Boost 1.80.0 REQUIRED COMPONENTS filesystem system)
```

**FIND_PATH**

```cmake
find_path (
					<VAR>
					// ...existing code...
				 )
```

- `NAMES`: specify one or more possible names for files in the directory
- `HINTS, PATHS`: directories to search
- `PATH_SUFFIXES`: specify extra subdirectories to check under each directory, otherwise invalid
- `DOC`: documentation string for the `<VAR>` cache entry
- `NO_CACHE`: store the result in a normal variable, not a cache entry (since 3.21)
- `REQUIRED`: stop processing and error if nothing is found, otherwise will try again on next call (since 3.18)
- `CMAKE_FIND_ROOT_PATH_BOTH`: search as above
- `NO_CMAKE_FIND_ROOT_PATH`: do not use `CMAKE_FIND_ROOT_PATH`
- `ONLY_CMAKE_FIND_ROOT_PATH`: only search re-rooted directories and under `CMAKE_STAGING_PREFIX`

Find the directory containing the named file.

**FIND_LIBRARY**

```cmake
find_library (
					<VAR>
					// ...existing code...
				 )
```

This command is used to find libraries.

**INCLUDE**

```cmake
include(<file|module> [OPTIONAL] [RESULT_VARIABLE <var>]
											[NO_POLICY_SCOPE])
```

Load and run CMake code from a file or module.

**INSTALL**

`INSTALL(TARGETS targets ... [[ARCHIVE|LIBRARY|RUNTIME]] [DESTINATION <dir>] [PERMISSIONS permissions ...] [CONFIGURATIONS [Debug|Release|...]] [COMPONENT <component>] [OPTIONAL]])` 

- `PERMISSIONS`
- `OWNER_EXECUTE`
- `OWNER_WRITE`
- `OWNER_READ`
- `GROUP_EXECUTE`
- `GROUP_READ`
- `CMAKE_INSTALL_PREFIX`: install location
- TODO

Define install rules.

```cmake
INSTALL(TARGETS myrun mylib mystaticlib 
				RUNTIME DESTINATION bin       # Executable myrun installed to ${CMAKE_INSTALL_PREFIX}/bin
				// ...existing code...
				ARCHIVE DESTINATION libstatic # Static library libmystaticlib installed to ${CMAKE_INSTALL_PREFIX}/libstatic
)
```

**LIST**

Compose file lists.

```cmake
list(
		APPEND hello_src
)
```

**MACRO**

```cmake
macro(<name> [<arg1> ...])
	<commands>
endmacro()
```

Start recording a macro for later invocation as a command (invocation is case-insensitive).

Example:

```cmake
macro(hello)
		...
endmacro()

Hello()
```

**MESSAGE**

`MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)` 

- `SEND_ERROR`: error, skip generation
- `STATUS`: output with prefix
- `FATAL_ERROR`: immediately terminate all cmake processes

Output information to the terminal.

**OPTION**

`OPTION(<NAME> "MESSAGE" [VALUE])`

- `NAME`: variable name
- `MESSAGE`: description
- `VALUE`: default value (ON/OFF)

Used to accept parameters from the command line.

```cmake
option(hello "hello world" ON)
```

**PROJECT**

`PROJECT(target_name LANGUAGES language)`

- `LANGUAGES`: programming language (default C++).

Declare project name.

```cmake
project(HELLO)
```

Specify project name.

**SET**

`SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])`

Set [variable value](#variables).

```cmake
SET(SRC_LIST main.c t1.c t2.c)
```

**SET_TARGET_PROPERTIES**

```cmake
set_target_properties(target1 target2 ...
											PROPERTIES prop1 value1
											prop2 value2 ...)
```

Set properties for generated targets.

```cmake
set_target_properties(hello
		PROPERTIES
)
```

**SET_TESTS_PROPERTES**

```cmake
set_tests_properties(test1 [test2...] PROPERTIES prop1 value1 prop2 value2)
```

- `prop*`: key
	+ TIMEOUT 

Set test parameters.

```cmake
set_tests_properties(helo PROPERTIES TIMEOUT 10) # Set test timeout
```

**SUBDIRS**

`SUBDIRS(dir1 dir2 ...)` 

Add multiple subdirectories at once (not recommended).

**TARGET_COMPILE_DEFINITIONS**

Pass target compile flags to other targets according to scope.

```cmake
target_compile_definitions(hello_flags
		PRIVATE EX3
)
```

**TARGET_COMPILE_FEATURES**

Set C++ standard.

```c++
target_compile_features(hello PUBLIC cxx_auto_type)
```

**TARGET_COMPILE_OPTIONS**

Set compile options.

```c++
target_compile_options(hello PRIVATE ${hello_flags})
```

**TARGET_LINK_LIBRARIES**

`TARGET_LINK_LIBRARIES[TARGETS SOURCE]` 

- `TARGETS`: executable targets to link to
- `SOURCE`: target library

Link target library to executable target.

```cmake
target_link_libraries(hello hello_lib)
```

**TARGET_INCLUDE_DIRECTORIES**

- `PRIVATE`: add directory to this target's include directories
- `INTERFACE`: add directory to any target linking to this library (not itself)
- `PUBLIC`: included in this library and any target linking to it

Add header file directories to the compiler, used in:

1. When compiling the library
2. When compiling any other target linking to the library

```cmake
target_include_directories(hello
		PRIVATE
)
```

**TARGETS**

Generated target names.


### Custom Functions

#### function

CMake provides `function` for custom functions.

```cmake
function(<name> [arg1 [arg2 [arg3 ...]]])
	COMMAND1(ARGS ...)
	// ...existing code...
	...
endfunction(<name>)
```

- `<name>`: function name
- `arg1, arg2...`: function parameters

Example:

```cmake
set(x "ABC")
set(y "DEF")

function(F1 arg)
	message(arg "abc" PARENT_SCOPE)
endfunction()

function(F2 arg)
	message(${arg} "def" PARENT_SCOPE) 
endfunction()

Foo(${x}) # pass by value
Foo(y)    # pass by reference
```

#### Implicit Parameters

CMake defines some implicit parameters for `function`:

| Implicit Param | Description |
| -------------- | ------------------------------------------------------------ |
| ARGC           | Number of actual arguments |
| ARGV           | List of all actual arguments |
| ARGN           | All extra arguments, i.e., ARGV minus explicitly declared ones |
| ARGV0          | First argument |
| ARGV1          | Second argument |
| ARGV2          | Third argument |
| ...            | ... |

Example:

```cmake
function(print_list arg)
		message("======= args count : ${ARGC} ======= ")    # Number of actual arguments
// ...existing code...
		endforeach()
endfunction()

set(arg hello world) 

message("------------ calling with quotes -----------")     # Call with quotes
print_list("${arg}")

message("------------ calling without quotes -----------")  # Call without quotes
print_list(${arg})
```

---


## Variables

### System Variables

- `CMAKE_MAJOR_VERSION`: major version
- `CMAKE_MINOR_VERSION`: minor version
- `CMAKE_PATCH_VERSION`: patch level
- `CMAKE_SYSTEM`: system name
	+ `APPLE`: macOS
	// ...existing code...
	+ `MINGW`: mingw environment
- `CMAKE_SYSTEM_NAME`: system name without version
- `CMAKE_SYSTEM_VERSION`: system version
- `CMAKE_SYSTEM_PROCESSOR`: processor name
- `HOME`

### Compile Variables

- `MSVC`

### Environment Variables

- `CMAKE_BINARY_DIR`: directory for generated binaries
- `CMAKE_RUNTIME_OUTPUT_DIRECTORY`: path for executables
- `CMAKE_CURRENT_BINARY_DIR`: current build directory
- `CMAKE_CURRENT_LIST_FILE`: full path of the current list file being processed
- `CMAKE_CURRENT_LIST_LINE`: line number in the current file being processed
- `CMAKE_CURRENT_SOURCE_DIR`: current source directory
- `CMAKE_INCLUDE_CURRENT_DIR`: whether to add current source and build directories to include path
- `CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE`: force project include dirs to be prepended
- `CMAKE_INCLUDE_PATH`
- `CMAKE_LIBRARY_PATH`
- `CMAKE_MODULE_PATH`
- `CMAKE_PROJECT_NAME`: name of the first (top-level) project set by `project()`
- `CMAKE_SOURCE_DIR`: root source directory
- `EXECUTABLE_OUTPUT_PATH`: path for generated executables
- `LIBRARY_OUTPUT_PATH`: path for shared libraries (only effective if default path not set)
- `CMAKE_ARCHIVE_OUTPUT_DIRECTORY`: default path for static libraries
- `CMAKE_LIBRARY_OUTPUT_DIRECTORY`: default path for dynamic libraries
- `PROJECT_BINARY_DIR`: current project's build directory
- `PROJECT_NAME`: project name
- `PROJECT_SOURCE_DIR`: current cmake project's source directory
- `xxx_SOURCE_DIR`: source directory for project xxx
- `xxx_BINARY_DIR`: binary directory for project xxx

### External Flags

- `BUILD_SHARED_LIBS`: controls default library build type (default is static)
- `CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS`: controls if/else statement syntax
- `CMAKE_BUILD_TYPE`: [build type](#build-type)
- `CMAKE_C_FLAGS`: C compiler flags
- `CMAKE_CXX_COMPILER`: which C++ compiler to use
	+ `clang++`: use clang
- `CMAKE_CXX_FLAGS`: C++ compiler flags
	+ `-std`: compiler version
- `CMAKE_CXX_STANDARD`: C++ standard flag (since v3.1)
- `CMAKE_LINKER_FLAGS`: linker flags

### Compiler Options

TODO

### Cache Variables

TODO

### Passing Parameters from Command Line

Define an option in CMakeLists.txt to accept parameters from the command line, then pass it to C++ files.

```cmake
# Define option
option(LOG_TABLE "select to use log table" OFF)

# Pass to C++ file
if(LOG_TABLE)
	 add_definitions(-DLOG_TABLE=on)
endif(LOG_TABLE)
```

Command line:

```cmake
cmake -DLOG_TABLE=ON ..
```

### Example

```cmake
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # Use C++11

set(CMAKE_CXX_STANDARD 11) # Use C++11 standard
```

```sh
cmake -DCMAKE_CXX_COMPILER=clang++ .. # Use clang
```

---


## Dependency Management

### Compiled Library Import

TODO

### FetchContent

CMake 3.11+ provides the `FetchContent` module for dependency management.

`FetchContent_Declare()` is used to fetch data or packages from URLs, Git repositories, etc.

`FetchContent_GetProperties()` is used to get package info.

`xxx_POPULATED` is used to check if a variable is exported (content populated).

`ExternalProject_Add()` is used to download during build; the main and external projects are only called the first time CMake runs.

`ExternalProject_Add` provides options for configuring and building external projects:

- Directory: tune source structure and build directory for external project
- Download: code may need to be downloaded from online repositories or resources
- Update and Patch: define how to update or patch external project source
- Configure: if the external project is a CMake project, `ExternalProject_Add` will call CMake and pass options
- Build: adjust actual build of external project
- Install: configure how to install external project
- Test: run tests for source-based builds
- URL: HTTP address for archive
- GIT_REPOSITORY: Git repo for dependency source
- GIT_TAG: branch to checkout
- SVN_REPOSITORY: SVN repo for dependency source
- HG_REPOSITORY: Mercurial repo for dependency source
- TEST_AFTER_INSTALL: run tests after install
- TEST_BEFORE_INSTALL: run tests before install
- TEST_EXCLUDE_FROM_MAIN: remove dependency on main target from test suite

```cmake
include(FetchContent) # Include FetchContent module

FetchContent_Declare( # Declare external content
		hello
		// ...existing code...
		GIT_TAG main
)

FetchContent_Populate( # Declare external content
	firmware
	// ...existing code...
	SOURCE_DIR firmware
)

# CMake 3.14+
FetchContent_MakeAvailable(hello)

# CMake 3.14-
FetchContent_GetProperties(hello) # Check if content is populated
if(NOT hello_POPULATED)           # Not populated
		FetchContent_Populate(hello)  # Populate content
// ...existing code...
		)
endif()
```

### CPM

TODO

### git submodule

TODO

---


## Unit Testing

### CTest

CMake 3.5+ provides CTest for unit testing.

CTest convention: return zero means success, nonzero means failure; any script returning zero/nonzero can be a test case.

Use these options for more detailed CTest output:

- `--output-on-failure`: print any output from test program to screen if test fails
- `-v`: enable verbose output
- `-vv`: enable more verbose output
- `--rerun-failed`: rerun previously failed tests

Example:

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(hello_test LANGUAGES CXX)

find_package(PythonInterp REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

add_executable(hello_test test.cpp)
```

```python
enable_testing() # Test this directory and all subfolders

# Set test environment variables
set_tests_properties(python_test
		PROTERTIES
)

# Define a new test
add_test(
		NAME hello_test # Set test name
		COMMAND $<TARGET_FILE:hello_test> # Run command with generator expression
)

# Set test duration
set_tests_properties(hello PROPERTIES TIMEOUT 10)
```

```sh
ctest
```

### Others

CMake also supports these other unit test tools:

- [boost test](#Integrate-Boost)

---


## Build & Compilation


### Build Process

- Internal build

	1. TODO

- External build

	// ...existing code...
	4. Run `make` to build the project.

### Build Types

`CMAKE_BUILD_TYPE` build types:

+ Debug: build with debug symbols, no optimization
+ Release: optimized build, no debug symbols
+ RelWithDebInfo: less optimized build with debug symbols
+ MinSizeRel: optimized for minimum code size

```cmake
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type" FORCE)
```

### Build Rules

`cmake --build . --target <target-name>`

- `target`
	// ...existing code...
	- `package`

Build the project.

```cmake
TODO
```

### Cross Compilation

TODO

### Packaging

CPack is used to generate packages. CPack commands are listed in CMakeCPack.cmake, which generates `CPackConfig.cmake`. When running CMake with the `package` or `package_source` target, CPack is called automatically.

#### Variables

- CPACK_PACKAGE_NAME: name
- CPACK_PACKAGE_VENDOR: vendor
- CPACK_PACKAGE_DESCRIPTION_FILE: description file
- CPACK_PACKAGE_DESCRIPTION_SUMMARY: package description
- CPACK_RESOURCE_FILE_LICENSE: license file
- CPACK_PACKAGING_INSTALL_PREFIX: install path
- CPACK_PACKAGE_VERSION_MAJOR: major version
- CPACK_PACKAGE_VERSION_MINOR: minor version
- CPACK_PACKAGE_VERSION_PATCH: patch version
- CPACK_SOURCE_IGNORE_FILES: files/directories to ignore
- CPACK_SOURCE_GENERATOR: archive format
- CPACK_GENERATOR: packaging tool
- CPACK_DEBIAN_PACKAGE_MAINTAINER
- CPACK_DEBIAN_PACKAGE_SECTION
- CPACK_NSIS_CONTACT
- CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL: uninstall before install
- CPACK_BUNDLE_NAME: bundle name
- CPACK_BUNDLE_PLIST: `*.plist` file
- CPACK_BUNDLE_ICON: icon

#### Tools

- linux
	TODO
- macos
	// ...existing code...
	1. Bundle
- windows
	// ...existing code...
	1. NSIS

#### Example

```cmake
# Declare package name
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")

# Declare package vendor
set(CPACK_PACKAGE_VENDOR "hello")

# Package description file
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/INSTALL.md")

# Add package description
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "hello")

# Add license file
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

# Set install path to /usr/local/hello
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local/${PROJECT_NAME}")

# Set major, minor, and patch version
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Set files/directories to ignore during packaging
set(CPACK_SOURCE_IGNORE_FILES "${PROJECT_BINARY_DIR};/.git/;.gitignore")

# Set archive format
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")

# Set binary archive generator
set(CPACK_GENERATOR "ZIP;TGZ")

# Declare native binary installer for linux
if(UNIX)
		if(CMAKE_SYSTEM_NAME MATCHES Linux) 
				// ...existing code...
		endif()
endif()

# Declare native binary installer for windows
if(WIN32 OR MINGW)
	 list(APPEND CPACK_GENERATOR "NSIS") # nsis installer
	 // ...existing code...
	 set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
endif()

# Declare native binary installer for macos
if(APPLE)
		list(APPEND CPACK_GENERATOR "Bundle") # bundle
		// ...existing code...
		set(CPACK_BUNDLE_ICON ${PROJECT_SOURCE_DIR}/cmake/coffee.icns)
endif()

# Print info
message(STATUS "CPack generators: ${CPACK_GENERATOR}")

include(CPack)
```

---


## Portability

---


## Integrate Protobuf

### Variables

- `PROTOBUF_FOUND`: whether protobuf is installed
- `PROTOBUF_INCLUDE_DIRS`: protobuf header directory
- `PROTOBUF_LIBRARIES`: protobuf library directory

### Generate Source Code

`PROTOBUF_GENERATE_CPP(SRCS HDRS *.proto)`

- `SRCS`: stores `.pb.cc` file names
- `HDRS`: stores `.pb.h` file names
- `*.proto`: proto files

```cmake
if(PROTOBUF_FOUND) # protobuf installed?
		...    
endif()

PROTOBUF_GENERATE_CPP(hello hello  hello.proto)
```

---


## Integrate Boost

### Variables

(For details, see `\share\cmake-xxx\Modules\FindBoost.cmake` in the cmake install dir, or the official docs: https://cmake.org/cmake/help/v3.6/module/FindBoost.html)

Boost info variables:

- Boost_FOUND: whether required libraries found
- Boost_INCLUDE_DIRS: boost header search path
- Boost_LIBRARY_DIRS: boost library link path
- Boost_LIBRARIES: boost library names for linking
- Boost_VERSION: version from boost/version.hpp
- Boost_LIB_VERSION: version of a sublibrary

Boost options:

- Boost_USE_STATIC_LIBS
- Boost_USE_MULTITHREADED
- Boost_USE_STATIC_RUNTIME

Set these environment variables to help find boost:

- BOOST_ROOT: preferred boost install path
- BOOST_INCLUDEDIR: preferred header search path
- BOOST_LIBRARYDIR: preferred library search path

### Boost Unit Testing

To use Boost unit testing:

1. Add boost component `unit_test_framework`
2. Add link dependency `Boost::unit_test_framework`
3. Define compile option `BOOST_TEST_DYN_LINK`
4. Define unit test

```cmake
find_package(Boost 1.80 REQUIRED COMPONENTS unit_test_framework)

target_link_libraries(hello
		PRIVATE
)

target_compile_definitions(hello
		PRIVATE
)

enable_testing()
add_test(
		NAME boost_test
		COMMAND $<TARGET_FILE:hello>
)
```

```c++
#define BOOST_TEST_MODULE xxx
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(xxx)
BOOST_AUTO_TEST_CASE(xx)
{
		BOOST_CHECK(...)
}
BOOST_AUTO_TEST_SUITE_END()
```

---


## Integrate git

TODO

---


## Integrate Visual Studio

Microsoft supports CMake in VS2017+. To enable Visual Studio CMake support, install the "C++ CMake tools for Windows" component.

### Build VS Project

To build different VS project versions, specify the VS generator and architecture:

```sh
cmake -G "<platform>" -A <architecture>
```

- `platform`: VS generator
	+ "Visual Studio 6"
	// ...existing code...
	+ ...
- `architecture`: architecture
	+ Win32
	// ...existing code...
	+ ...

Example:

```sh
cmake -G "Visual Studio 17 2022" -A x64
```

---


## Integrate Qt

### Variables

General variables:

- CMAKE_AUTOMOC: process .moc files?
- CMAKE_AUTORCC: process .qrc files (resources)?
- CMAKE_AUTOUIC: process .ui files (UI)?
- CMAKE_INCLUDE_CURRENT_DIR: moc search dir

Module variables:

- Qt5Widgets_COMPILE_DEFINITIONS: compile options
- Qt5Widgets_DEFINITIONS: dependency options
- Qt5Widgets_EXECUTABLE_COMPILE_FLAGS: executable options
- Qt5Widgets_FOUND: found Widgets module?
- Qt5Widgets_INCLUDE_DIRS: Qt widgets dir (QtCore and QtGui depend on this)
- Qt5Widgets_LIBRARIES: Qt widgets dependency dir
- QtWidgets_PRIVATE_INCLUDE_DIRS: Qt Widgets private dir
- QtWidgets_VERSION_STRING: module version
- Qt5Declarative_INCLUDE_DIRS: Qt Declarative dir
- Qt5Declarative_LIBRARIES: Qt Declarative dependency dir

Install variables:

- QT_DEFAULT_MAJOR_VERSIO: default major version (Qt5/Qt6)
- QT_LIBINFIX: dependency infix
- QT_NO_CREATE_VERSIONLESS_FUNCTIONS: fix function version compatibility (Qt5.15+, qt functions are versionless, e.g. `qt5_` becomes `qt_`)
- QT_NO_CREATE_VERSIONLESS_TARGETS: fix module version compatibility (Qt5.15+, qt modules are versionless, e.g. `Qt5::` becomes `Qt::`)
- QT_VISIBILITY_AVAILABLE: export symbols?

### Functions

Qt5::Core:

- qt5/qt_add_big_resources: add big resource files
- qt5/qt_add_binary_resources: create RCC files from qt resource files
- qt5/qt_add_resources: add binary resource files
- qt5/qt_generate_moc: call input .moc files
- qt5/qt_import_plugins: add qt static plugins
- qt5/qt_wrap_cpp: create .moc files from source

Qt5::DBus

- qt_add_dbus_adaptor
- qt_add_dbus_interface
- qt_add_dbus_interfaces
- qt_generate_dbus_interface

Qt5::LinguistTools

- qt5_add_translation: compile Linguist.ts to .qm
- qt5_create_translation: set up lightweight translation tool

Qt5::RemoteObjects

- qt5_generate_repc: create C++ classes from qt remote object .rep files

Qt5::Widgets

- qt5/qt_wrap_ui: create source from .ui files

### Commands

- `-debug`
	// ...existing code...
- `-release`
	// ...existing code...
- `-debug-and-release`

### Example

```cmake
cmake_minimum_required(2.8.8)
project(hello)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
		set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_definitions(${Qt5Widgets_DEFINITIONS}) # -DQT_WIDGETS_LIB

# cmake2.8.8+ supports, equivalent to .pro:
#   TARGET = hello
#   QT += widgets declarative
qt5_use_modules(hello Widgets Declarative)

add_executable(${PROJECT_NAME} 
		hello.h 
		// ...existing code...
		hello.ui
)

target_link_libraries(hello Qt5::Widgets)
```

---


## Integrate Zeromq

zeromq is an open-source third-party network library; cmake provides ways to integrate zeromq.

### Variables

- `ZMQ_BUILD_TESTS`: build test examples
- `BUILD_SHARED`: build shared library
- `BUILD_STATIC`: build static library

Example:

```sh
cmake .. -DZMQ_BUILD_TESTS=OFF -DBUILD_STATIC=ON -DBUILD_SHARED=ON
```

### zmqpp

zmqpp is an excellent C++ wrapper for zeromq. Use CMake to integrate zmqpp. Common variables:

- `ZMQ_BUILD_TESTS`: enable test?
- `ZMQPP_BUILD_STATIC`: build static library (default ON)
- `ZMQPP_BUILD_SHARED`: build shared library (default ON)
- `ZMQPP_LIBZMQ_NAME_STATIC`: zeromq static lib
- `ZMQPP_LIBZMQ_NAME_SHARED`: zeromq shared lib
- `ZEROMQ_LIB_DIR`: zeromq lib search path
- `ZEROMQ_INCLUDE_DIR`: zeromq header dir

Example:

```cmake
cmake .. -G "Visual Studio 14 2015 Win64" -DZMQ_BUILD_TESTS=OFF
```

---


## Integrate Valgrind

Valgrind is a general tool for detecting memory defects and leaks. CMake supports integrating Valgrind.

Example:

```c++
// main.cpp
#include <iostream>

int main() {
		auto m = new double[1000]; // not freed
}
```

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_test main.cpp)

# Find valgrind and set absolute path MEMORYCHECK_COMMAND
find_program(MEMORYCHECK_COMMAND NAMES valgrind)

# Set valgrind options (create log file for memory defect info)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")

include(CTest)
enable_testing()

add_test(
		NAME hello_test
		COMMAND $<TARGET_FILE:hello_test>
)
```

```sh
ctest -T memcheck
```

---


## References

[1] [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[2] Eric Noulard, Roberto Di Remigio.CMake-Cookbook

[3] [Modern CMake Simplified Chinese](https://github.com/Modern-CMake-CN/Modern-CMake-zh_CN)

[4] [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/)

[5] [CMake Basic Tutorial](https://www.cnblogs.com/juzaizai/category/1993745.html)

[6] [Find Boost Library with CMake on Linux](https://www.jianshu.com/p/1827cd86d576)

[7] [Using CMake with Qt 5](https://www.kdab.com/using-cmake-with-qt-5/)

[8] [Build with CMake](https://doc.qt.io/qt-5/cmake-manual.html)

[9] [CMake 3.21 [Chinese]](https://runebook.dev/zh-CN/docs/cmake/-index-#Commands)

[10] [CMake Projects in Visual Studio](https://learn.microsoft.com/zh-cn/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)

[11] [Visual Studio 17 2022](https://cmake.org/cmake/help/latest/generator/Visual%20Studio%2017%202022.html)

[12] [CMake Syntax—Cache Variable](https://www.cnblogs.com/Braveliu/p/15614013.html)

[13] [CMake C++ Project Template](https://zhuanlan.zhihu.com/p/606155750?utm_campaign=shareopn&utm_medium=social&utm_oi=974639756117843968&utm_psn=1609273999753658368&utm_source=wechat_session)

[14] [CMake Generate Beautiful VS Project Files](https://zhuanlan.zhihu.com/p/441155027?utm_campaign=shareopn&utm_medium=social&utm_oi=974639756117843968&utm_psn=1609391864909348864&utm_source=wechat_session)
