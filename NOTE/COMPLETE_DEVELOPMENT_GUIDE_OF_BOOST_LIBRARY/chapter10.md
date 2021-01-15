## 10.4 filesystem
```c++
class path // 路径表示类
{
		public:
				typedef char_or_wchar_t value_type; // 路径的字符类型
				typedef std::basic_string<value_type> string_type; // 路径使用的字符串类型
				constexpr value_type preferred_separator; // 路径分隔符

				path(); // 各种构造函数
				path(const path& p);
				path(Source const& source);
				path(InputIterator begin, InputIterator end);

				path& operator=(const path& p); // 赋值操作
				path& operator=(Source const& source);
				path& assign(Source const& source);
				path& assign(InputIterator begin, InputIterator end);

				path& operator/=(const path& p);
				path& operator/=(Source const& source);
				path& append(Source const& source);
				path& append(InputIterator begin, InputIterator end);

				path& operator+=(const path& x);
				path& operator+=(const string_type& x); // 连接路径
				path& operator+=(Source const& x);
				path& concat(InputIterator begin, InputIterator end);

				void clear(); // 清空路径表示
				path& remove_filename(); // 删除文件名
				path& replace_extension(); // 更改扩展名
				void swap(path& rhs); // 交换操作

				const string_type& native() const; // 本地路径表示
				const value_type* c_str() const; // 转换为c字符串
				const string string() const; // 转换为字符串
				const wstring wstring() const; // 转换为宽字符串

				int compare(const path& p) const; // 比较路径
				int compare(const std::string& s) const;
				int compare(const value_type* s) const;

				path root_name() const; // 根名称
				path root_directory() const; // 根目录
				path root_path() const; // 根路径
				path relative_path() cosnt; // 相对路径
				path parent_path() const; // 父路径
				path filename() const; // 文件名
				path stem() const; // 全路径名
				path extension() const; // 扩展名

				bool empty() const; // 是否为空路径
				bool has_root_name() const; // 是否有根名称
				bool has_root_directory() const; // 是否有根目录
				bool has_root_path() const; // 是否有根路径
				bool has_relative_path() const; // 是否有相对路径
				bool has_parent_path() const; // 是否有父路径
				bool has_filename() const; // 是否有文件名
				bool has_stem() const; // 是否有全路径名
				bool has_extension() const; // 是否有扩展名
				bool is_absolute() const; // 是否是绝对路径
				bool is_relative() const; // 是否是相对路径
				
				iterator begin() const; // 迭代路径
				iterator end() const;
};
ostream& operator<<( ostream& os, const path& p ); // 流输出操作
path operator/ (const path& lhs, const path& rhs); // 连接两个路径
bool operator==(const path& lhs, const path& rsh); // 比较操作符
```
### 10.4.3 可移植的文件名
自由函数portable_posix_name()和windows_name()分别检测文件名字符串是否符合POSIX规范和Windows规范。

函数native()判断文件名是否符合本地文件系统的命名规则，在Windows操作系统下它等同于windows_name(),而在其他操作系统下则只是简单地判断文件名不是空格且不包含斜杠。

### 10.4.5 异常处理
filesystems库使用异常filesystem_error来处理文件操作时发生的错误，它是system库中system_error的子类，filesystem_error的类摘要如下:
```c++
class filesystem_error : public system_errror
{
public:
		filesystem_error(); 
		filesystem_error(const filesystem_error&);
		filesystem_error(const std::string& what_arg, system::error_code ec);

		filesystem_error(const std::string& what_arg, const path& p1, system::error_code ec);
		filesystem_error(const std::string& what_arg, const path& p1, const path& p2, system::error_code ec);

		const path& path1() const; // 获取路径对象
		const path& path2() const;

		const char* waht() const; // 错误信息
}						 

```

### 10.4.6 文件状态
fielsystem库提供一个文件状态类file_status以及一组相关函数，用于检查文件的属性。file_status的类摘要如下:
```c++
class file_status
{
		public:
				file_status(); 
				explicit file_status(file_type ft, perms prms = perms_not_known);

				file_type type() const; // 文件类型
				vodi type( file_type v ); // 设置文件类型

				perms permissions() const; // 访问权限
				void permissions(perms prms); // 设置访问权限
};
```
文件的类型file_type取值如下:
* status_error 获取文件类型出错
* file_not_found 文件不存在
* status_unknown 文件存在但状态未知
* regular_file 该文件是一个普通文件
* directory_file 该文件是一个目录
* symlink_file 该文件是一个链接文件
* block_file 该文件是一个块设备文件
* character_file 该文件是一个字符设备文件
* fifo_file 该文件是一个管道设备文件
* socket_file 该文件是一个socket设备文件
* type_unknown 文件的类型未知

通常我们不会直接使用file_status类,而是用相关函数file_status对象:
* status()/symlink_status()测试路径p的状态，如果路径不能被解析，那么会抛出异常filesystem_error
* status_known()检查文件状态s，返回s.type != status_error.

### 10.4.7 文件属性
* initial_path()返回程序启动时(进入main函数)的路径
* current_path()返回当前路径。它和initial_path()返回的都是一个完整路径(绝对路径)
* file_size()以字节为单位返回文件的大小
* last_write_time()返回文件的最后修改时间，是一个std::time_t
这些函数都要求操作的文件必须存在，否则会抛出异常，file_size()还要求文件必须是个普通文件(is_regular_file(name) == true)

含糊space()可以返回一个space_info结构，它表明了该路径下的磁盘空间的分配情况，space_info结构的定义如下:
```c++
struct space_info
{
	uintmax_t capacity;
	uintmax_t free;
	uintmax_t available;
}
```

### 10.4.8 文件操作
文件操作用法示例:
```c++
namespace fs = boost::filesystem;

path ptest = "./test";
if(exists(ptest)) // 检查路径是否存在
{
	if(fs::is_empty(ptest)) // 注意名字空间限定
	{
		remove(ptest); // remove只能删除空目录或文件
	}
	else
	{
		remove_all(ptest); // remove_all可以递归删除
	}
}

assert(!exists(ptest)); // 该目录已经被删除
create_directory(ptest); // 创建一个目录

copy_file("C://1.hpp", ptest / "a.txt");
assert(exists(ptest / "a.txt"));

rename(ptest / "a.txt", ptest / "b.txt");
assert(exists(ptest / "b.txt"));

// 使用create_directories 可以一次创建多级穆鲁
create_directories(ptest / "sub_dir1" / "sub_dir1");
```

### 10.4.9 迭代目录
filesystem使用directory_iterator提供了迭代一个目录下的所有文件的功能，它基于boost.iterator库的iterator_facade,x其类摘要如下:
```c++
class directory_iterator : public boost::iterator_facade<
						   directory_iterator,
						   directory_entry,
						   boost::single_pass_traversal_tag >
{
		public:
				directory_iterator(){}

}
```
```
