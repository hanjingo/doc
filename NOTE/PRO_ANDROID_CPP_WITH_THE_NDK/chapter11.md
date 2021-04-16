# 第十一章 支持c++

支持c++的运行库比较

|c++运行库|C++异常支持|c++RTTI支持|C++标准库|
|---|---|---|---|
|系统库|N|N|N|
|GAbi++|N|Y|N|
|STLport|N|Y|Y|
|GNU STL|Y|Y|Y|

## 指定c++运行库

APP_STL可被用于指定c++运行库,APP_STL可以