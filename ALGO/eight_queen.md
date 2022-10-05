# 八皇后问题

<!-- vim-markdown-toc GFM -->

* [更新1：如何用递归表示 n 层 for 循环](#更新1如何用递归表示-n-层-for-循环)
* [更新2：原答案的「解压」版本：](#更新2原答案的解压版本)
* [更新3： C++03 版本，采用 std::next_permutation](#更新3-c03-版本采用-stdnext_permutation)

<!-- vim-markdown-toc -->


问题：1-9 数字组成3个数 abc, cde, fgh 且 abc:def:ghi=1:2:3。

167个字符的答案：
```c++
g(x,y,z){x*2==y&x*3==z&&printf("%d,%d,%d\n",x,y,z);}
f(i,j,m,r){i?1<<j&m||f(i-1,1,m|1<<j,r*10+j),j<10&&f(i,j+1,m,r):g(r/1000000,r/1000%1000,r%1000);}
main(){
    f(9,1,0,0);
}
```
编译及输出：
```sh
gcc -w a.c && ./a.out
192,384,576
219,438,657
273,546,819
327,654,981
```
明明就有九层循环。

## 更新1：如何用递归表示 n 层 for 循环
在《Milo Yip：两个for循环能处理哪些问题？》里，我提到:

两个嵌套 for 循环可把两个集合 A, B 生成 笛卡儿积（Cartesian product） A \times B;那么，要对集合 A = \{ 1, 2, 3, ..., 9 \} 做九个嵌套 for，可表示为 \underbrace{ A \times A \times \cdots \times A}_9 = A^9 。

假设我们直接写成 9 个 for 循环：
```c++
#include <stdio.h>

void output(const int* a) {
    for (int i = 0; i < 9; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[9];

    for (a[8] = 1; a[8] < 10; a[8]++)
     for (a[7] = 1; a[7] < 10; a[7]++)
      for (a[6] = 1; a[6] < 10; a[6]++)
       for (a[5] = 1; a[5] < 10; a[5]++)
        for (a[4] = 1; a[4] < 10; a[4]++)
         for (a[3] = 1; a[3] < 10; a[3]++)
          for (a[2] = 1; a[2] < 10; a[2]++)
           for (a[1] = 1; a[1] < 10; a[1]++)
            for (a[0] = 1; a[0] < 10; a[0]++)
                output(a);
}
```
输出：
```sh
1 1 1 1 1 1 1 1 1 
2 1 1 1 1 1 1 1 1 
3 1 1 1 1 1 1 1 1 
...
1 2 1 1 1 1 1 1 1
2 2 1 1 1 1 1 1 1
3 2 1 1 1 1 1 1 1
...
9 9 9 9 9 9 9 9 9
```
但我们可以考虑到：A^n = A \times A^{n - 1}

我们可用这种递归形式，定义一个函数，里面只做一个 for 循环去表示上式里的一个笛卡儿积：
```c++
#include <stdio.h>

void output(const int* a) {
    for (int i = 0; i < 9; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void f(int* a, int n) {
    for (a[n] = 1; a[n] < 10; a[n]++)
        if (n == 0)
            output(a);
        else
            f(a, n - 1);
}

int main() {
    int a[9];
    f(a, 8);
}
```
这是一个通用的方式，把 n 个 for 循环写成递归形式。如果 n 不是常数，用递归是简单的解决方法。谈回到原问题，其实它只需要 A 的排列（permutation），即 9!=362880 次测试。原答案用了组合（combination），并用位集（bit set）的方式去避免加入重复的数字，但理想的做法是直接生成所有排列[1]。

## 更新2：原答案的「解压」版本：
```c++
#include <stdio.h>

void outputIfValid(int abc, int def, int ghi) {
    if (abc * 2 == def && abc * 3 == ghi)
        printf("%d,%d,%d\n", abc, def, ghi);
}

// 第 i 层 for 循环, m 以 bit set 表示已使用的数字, r 为当前排列 abcdefghi
void f(int i, int m, int r) {
    if (i == 0)
        outputIfValid(r / 1000000, r / 1000 % 1000, r % 1000); // abcdefghi -> abc, def, ghi
    else
        for (int j = 1; j < 10; j++)
            if (((1 << j) & m) == 0)                 // 若 j 没有被使用
                f(i - 1, m | (1 << j), r * 10 + j);  // m 和 r 都加入 j，进入 i - 1 的循环
}

int main() {
    f(9, 1, 0);
}
```

## 更新3： C++03 版本，采用 std::next_permutation
```c++
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

int main() {
    int a[9];
    iota(a, a + 9, 1);
    do {
        int abc = a[0] * 100 + a[1] * 10 + a[2];
        int def = a[3] * 100 + a[4] * 10 + a[5];
        int ghi = a[6] * 100 + a[7] * 10 + a[8];
        if (abc * 2 == def && abc * 3 == ghi)
            cout << abc << "," << def << "," << ghi << endl;
    } while(next_permutation(a, a + 9));
}
```
