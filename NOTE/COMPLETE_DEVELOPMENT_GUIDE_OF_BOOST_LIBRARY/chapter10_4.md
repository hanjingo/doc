# 10.4 program_options
## 选项值
value_semantic是选项描述器的核心类，他定义了选项值的语义信息，但我们通常不直接使用它，而是使用它的一个子类typed_value, typed_value的类摘要如下:
```c++
template<typename T>
class typed_value
{
public:
    typed_value(T *);

    typed_value * default_value(const T &);
    typed_value * implicit_value(const T &);
    typed_value * multitoken();
    typed_value * zero_tokens();
    typed_value * composing();
    typed_value * required();
}
```

## 选项描述器
- option_description 用于描述单个选项，它提供了选项的名称，语法和详细的描述信息，并使用value_semantic(值语义)类来分析处理选项值。
- options_description 是option_description的一个聚集，它使用vector<shared_ptr<option_description>>来存储多个选项，提供一个方便定义多个选项值的接口。

option_description的类摘要如下:
```c++
class option_description
{
public:
    option_description();
    option_description(const char *, const value_semantic *);
    option_description(const char *, const value_semantic *, const char *);
}
```

示例:
```c++
option_description("help,h", 0, "help message\n"
                            "\ta bit of long text");
```

## 选项描述器的用法
```c++
# define BOOST_PROGRAM_OPTIONS_NO_LIB
#include <boost/program_options.hpp>
using namespace boost::program_options;
void print_vm(options_description &opts, variables_map &vm)
{
    if (vm.size() == 0)         // 无参数处理
    {
        cout << opts << endl;
        return;
    }

    if (vm.count("help"))       // 处理帮助选项
    {
        cout << opts << end;
    }

    // 输出查找文件名，因为它有缺省值，故总存在
    cout << "find opt:" << vm["filename"].as<string>() << endl;

    if (vm.count("dir")) // 处理搜索路径
    {
        cout << "dir opt:";
        BOOST_FOREACH(string str,
            vm["dir"].as<vector<string> >())
        { cout << str << ","; }
        cout << endl;
    }
    if (vm.count("depth"))
    { cout << "depth opt:" << vm["depth"].as<int>() << endl; }
}

int main(int argc, char* argv[])
{
    options_description opst("demo options");

    string filename;    // 外部的选项值存储
    opts.add_options()  // 产生辅助对象，调用operator()

        // 帮助选项，使用空格缩进格式
        ("help,h", "help message\n  a bit of long text")

        // 文件名选项，值可存储到外部，缺省值是test
        ("filename,f", value<string>(&filename)->default_value("test"), "to find a file")

        // 搜索路径选项，可以多次出现，可以接受多个记号
        ("dir,D", value<vector<string> >()-?multitoken(), "search dir")

        // 搜索深度选项，隐含值是5，短名与搜索路径不同
        ("depth,d", value<int>()->implicit_value(5), "search depth")
        ;

    variables_map vm;                                // 选项存储map容器
    store(parse_command_line(argc, argv, opts), vm); // 解析
    notify(vm);                                      // 解析结果存储外部变量

    // 解析完成，调用函数实现选项处理逻辑
    print_vm(opts, vm);
}
```

## 分析器
1. program_options库的分析器负责解析命令行参数，行为好像字符串处理的分词动作，将命令行拆分成选项名和选项值，存储在basic_parsed_options类中。
最简单的分析器是parse_command_line()函数，它可以解析标准的main()函数入口的命令行参数，我们之前一直在使用它，它的声明如下:
```c++
parse_command_line(int argc, charT * argv, const options_description &);
```

2. parse_config_file()函数可以解析配置文件,输入可以是文件名或IO流(istream),配置文件的基本格式是name=value,类似于ini格式,选项名必须使用长名，等号两边允许有空格。函数声明如下:
```c++
parse_config_file(src, const options_description& desc, bool allow_unregistered = false);
```

3. 其他:
- command_line_paeser 类，它被parse_command_line()函数在内部调用，可以提供一些扩展功能;
- parse_environment() 函数，用于分析环境变量;

## 使用位置选项值
program_options库将没有选项名的选项称为位置选项，它的描述要使用positional_options_description类来辅助,positional_options_description类摘要如下:
```c++
class positional_options_description
{
public:
    positional_options_description();
    positional_options_description & add(const char *name, int count);
};
```

位置选项的解析较为复杂，我们不能再使用parse_command_line()函数，而要使用command_line_parser类。它的用法与parse_command_line()函数类似，接受命令行参数，然后调用options()传入options_description对象，最后用run()进行解析.command_line_parser类摘要如下:
```c++
class command_line_parser
{
public:
    command_line_parser(const vector< string > &);
    command_line_parser(int, char *);

    basic_parsed_options< charT > run();

    command_line_parser & options(const options_description &);
    command_line_parser & positional(const positional_options_description &);
    command_line_parser & style(int);
    command_line_parser & extra_parser(ext_parser);
    command_line_parser & allow_unregistered();
    command_line_parser & extra_style_parser(style_parser);
}
```

示例:
```c++
positional_options_description pod;     // 位置选项
pod.add("filename", 1);                 // 查找文件名仅出现一个
BOOST_AUTO(pr,                          // 使用BOOST_AUTO保存解析结果
    command_line_parser(argc, argv).    // 构造一个解析对象
    options(opts).                      // 传入选项描述
    positional(pod).                    // 传入位置描述
    run());                             // 设置完成，开始解析
store(pr, vm);                          // 保存解析结果到vm中
```

## 分析环境变量
分析器组件中的parse_environment()函数可以从环境变量中提取信息，其声明如下:
```c++
parsed_options parse_environment(const options_description &, name_mapper);
```