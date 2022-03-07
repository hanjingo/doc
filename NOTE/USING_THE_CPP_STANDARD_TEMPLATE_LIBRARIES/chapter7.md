# 第七章 更多的算法

[TOC]



## 7.1 检查元素的属性

检查元素属性的三种算法：

- `all_of()` 算法会返回true，前提是序列中的所有元素都可以使谓词返回true。

- `any_of()` 算法会返回true，前提是序列中的任意一个元素都可以使谓词返回true。

- `none_of()` 算法会返回true，前提是序列中没有元素可以使谓词返回true。

  ```c++
  std::vector<int> ages{22, 19, 46, 75, 54, 19, 27, 66, 61, 33, 22, 19};
  int min_age{18};
  std::cout << "There are " << (std::none_of(std::begin(ages), std::end(ages), 
                                             [min_age](int age){ return age < min_age; }) ? "no" : "some")
            << " people unser " << min_age << std::endl;
  ```

  