# 摘要
eos的名字系统，包括名字和uint64_t的转换，名字合法性判断

# 详情
* [name.hpp](https://github.com/hanjingo/eosio.cdt/blob/master/libraries/eosiolib/core/eosio/name.hpp)

## 知识点:
1. constexpr:函数的返回值类型及所有形参的类型都是字面值类型；
2. decltype:选择并返回操作数的数据类型;与auto配合使用;

## 命名规则:
1. 长度必须大于0且小于14;
2. 每个字符从[.], [1~5], [a~z]中间选;
3. 如果长度等于13，则最后一个字符不能是".";

## 别名:
```c++
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-string-literal-operator-template"
template <typename T, T... Str>
inline constexpr eosio::name operator""_n() {
	constexpr auto x = eosio::name{std::string_view{eosio::detail::to_const_char_arr<Str...>::value, sizeof...(Str)}};
	return x;
}
#pragma clang diagnostic pop
用_n来代替name构造函数
```
