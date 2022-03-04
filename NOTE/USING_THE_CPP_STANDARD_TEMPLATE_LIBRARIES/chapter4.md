# 第四章 map容器

[TOC]

## 4.1map容器介绍

* `map<K, T>`容器保存的是`pair<const K, T>`类型的元素。
* `multimap<K, T>`容器和`map<K, T>`容器类似，允许使用重复的键。
* `unordered_map<K, T>`中`pair<const K, T>`元素的顺序并不是直接由键值确定的，而是由键值的哈希值决定的。
* `unordered_multimap<K, T>`也可以通过键值生成的哈希值来确定对象的位置，但它允许有重复的键。



## 4.2map容器的用法

![4_1](res/4_1.png)

*map<K, T>容器的概念展示图*

![4_2](res/4_2.png)

*map容器的内部组织图*

### 4.2.1创建map容器

```c++
// 使用初始化列表初始化map
std::map<std::string, size_t> people{{"Ann", 25}, {"Bill", 46}, {"Jack", 32}, {"Jill", 32}};

// 创建pair对象来初始化map
std::map<std::string, size_t> people{ 
    std::make_pair("Ann", 25),
    std::make_pair("Bill", 46),
    std::make_pair("Jack", 32),
    std::make_pair("Jill", 32)
};

// 通过复制构造初始化map
std::map<std::string, size_t> personnel{people};

// 使用一段区间初始化map
std::map<std::string, size_t> personnel{++std::begin(people), std::end(people)};
```

### 4.2.2map元素的插入

```c++
// 插入单个元素
std::map<std::string, size_t> people{
    std::make_pair("Ann", 25),
    std::make_pair("Bill", 46),
    std::make_pair("Jack", 32),
    std::make_pair("Jill", 32)
};
auto ret_pr = peopel.insert(std::make_pair("Fred", 22));
std::cout << ret_pr.first->first << " " << ret_pr.first->second
    << " " << std::boolalpha << ret_pr.second << " \n";

// 将一段元素插入map
std::map<std::string, size_t> crowd{{"May", 55}, {"Pat", 66}, {"Al", 22}, {"Ben", 44}};
auto iter = std::begin(people);
std::advance(iter, 4);
crowd.insert(++std::begin(people), iter);

// 创建初始化列表，作为参数传递给insert函数
std::initializer_list<std::pair<const std::string, size_t> > init{
    {"Bert", 44}, {"Ellen", 99}};
crowd.insert(init);
```

完整示例：

```c++
// Name.h
#ifndef NAME_H
#define NAME_H
#include <string>
#include <ostream>
#include <istream>

class Name
{
private:
    std::string first {};
    std::string second {};
public:
    Name(const std::string& name1, const std::string& name2) : first (name1),second (name2) {}
    Name() = default;

    bool operator<(const Name& name) const
    {
        return second < name.second || (second == name.second && first < name.first);
    }
    friend std::istream& operator>>(std::istream& in, Name& name);
    friend std::ostream& operator<<(std::ostream& out, const Name& box);
};

inline std::istream& operator>>(std::istream& in, Name& name)
{
    in >> name.first >> name.second;
    return in;
}

inline std::ostream& operator<<(std::ostream& out, const Name& name)
{
    out << name.first + " " + name.second;
    return out;
}

#endif
```

```c++
// Ex4_01.cpp
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <cctype>
#include "Name.h"

using std::string;
using Entry = std::pair<const Name, size_t>;
using std::make_pair;
using std::map;

Entry get_entry()
{
    std::cout << "Enter first and second names followed by the age: ";
    Name name {};
    size_t age {};
    std::cin >> name >> age;
    return make_pair(name, age);
}

void list_entries(const map<Name, size_t>& people)
{
    for(auto& entry : people)
    {
        std::cout << std::left << entry.first << std::right << entry.second << std::endl;
    }
}

int main()
{
    map<Name, size_t> people { {{"Ann", "Dante"}, 25}, {{"Bill", "Hook"}, 46},
                               {{"Jim", "Jams"}, 32}, {{"Mark", "Time"}, 32} };
    std::cout << "\nThe initial contents of the map is:\n";
    list_entries(people);

    char answer {'Y'};
    std::cout << "\nEnter a Name and age entry.\n";
    while(std::toupper(answer) == 'Y')
    {
        Entry entry {get_entry()};
        auto pr = people.insert(entry);
        if(!pr.second)
        {
            std::cout << "Key \"" << pr.first->first << "\" already present. Do you want to update the age (Y or N)?";
            std::cin >> answer;
            if(std::toupper(answer) == 'Y')
                pr.first->second = entry.second;
        }
        std::cout << "Do you want to enter another entry(Y or N)? ";
        std::cin >> answer;
    }

    std::cout << "\nThe map now contains the following entries:\n";
    list_entries(people);
}
```

### 4.2.3在map中构造元素

```c++
// 使用emplace构造新元素以避免复制和移动操作
std::map<Name, size_t> people;
auto pr = people.emplace(Name{"Dan", "Druff"}, 77);

// 使用emplace_hint在指定位置构造新元素以避免复制和移动操作
std::map<Name, size_t> people;
auto pr = people.emplace(Name{"Dan", "Druff"}, 77);
auto iter = people.emplace_hint(pr.first, Name{"Cal", "Cutta"}, 62);

// s
```





