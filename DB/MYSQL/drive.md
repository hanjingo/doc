# 驱动Mysql

[TOC]



## C++

```c++
#include <iostream>
#include <string>
#include <mysql/mysql.h>

int main()
{
    // 初始化mysql变量
    MYSQL mysql;
    mysql_init(&mysql);

    // 连接mysql服务器
    if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "123", "test", 3306, 0, 0))
    {
        std::cout << "mysql_real_connect fail!" << std::endl;
        return 0;
    }

    // 查询mysql数据库中的表
    std::string sql{"select * from test limit 1"};
    if (mysql_real_query(&mysql, sql.c_str(), sql.length()))
    {
        std::cout << "mysql_real_query failure!" << std::endl;
        return 0;
    }

    // 存储结果集
    MYSQL_RES *res = mysql_store_result(&mysql);
    if (!res)
    {
        std::cout << "mysql_store_result failure!" << std::endl;
        return 0;
    }

    // 重复读取行，并输出第一个字段的值，直到row为NULL
    MYSQL_ROW row;
    while (row = mysql_fetch_row(res))
    {
        std::cout << row[0] << std::endl;
    }

    // 释放结果集
    mysql_free_result(res);

    // 关闭连接
    mysql_close(&mysql);
    return 0;
}
```



## 参考

[1] [MySQL见闻录 - 入门之旅（六）（C++操作MySQL）](https://cloud.tencent.com/developer/article/1685883)