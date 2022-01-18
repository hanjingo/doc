# 第十一章 数学背景
## 摘要
密码学的数学背景

## 详情
### 知识点
1. 信息量(amount of information):假设信息是等可能的，对消息中所有可能的值进行编码所需要的最小位数
2. 语言信息率(rate of language): $r=H(M)/N$; N:是消息的长度；在N相当大时，标准英语的语言信息率(r值)在1.0位/字母与1.5位/字母之间
3. 绝对信息率(absolute rate):假定每一个字符串是等可能的，对每一个字母而言可被编码的最大位数。如果在一种语言中有L个字母，其绝对信息率是:$R=log_2L$ 
4. 语言冗余度越大，它就越容易被攻击。密码系统的熵可由秘钥空间大小K来衡量:$H(K)=log_2K$

### 唯一解距离(unidty distance)
使得对应明文的实际信息（熵）与加密秘钥的熵之和等于所用的密文位数的渐进密文量。
1. 对于大多数对称秘钥系统而言，唯一减距离定义为秘钥系统的熵除以语言的冗余度：$U=H(K)/D$
2. 唯一解距离与冗余度成反比。唯一解距离无穷大的密码系统定义为具有理想保密(ideal secrecy)
3. 对于长度为n的消息而言，将一个密文消息解密为同一语言中某个有意义的明文，不同秘钥的数目由下式给出:$2^{H(k)-nD}-1$

### 混乱和扩散
隐蔽明文消息中冗余度的基本技术
1. 混乱(confusion):用于掩盖明文和密文之间的关系。
2. 扩散(diffusion):通过将明文冗余度分散到密文中使之分散开来。密码分析者寻求这些冗余度将会更难。产生扩散最简单的方法是通过换位（也称为置换）。

### 复杂性理论
算法的计算复杂性常常用两个变量来度量：T(时间复杂性 time complexity) 和 S(空间复杂性 space complexity)  
复杂性分类:  
* 常数(constant):一个算法的复杂性不依赖于n，即为O(1)；
* 线性(linear):时间复杂性是O(n)；
* 二次方(quadratic)，三次方(cubic)：...；
* 指数(exponential):时间复杂性为:$O(t^{f(n)})$
* 超多项式(superpdynomial):复杂性为:$O(c^{f(n)})$；c是一个常数，f(n)是大于常数而小于线性的函数；

### 问题的复杂性
NP问题与密码学的关系如下:许多对称算法和所有公开密钥算法能够用非确定性的多项式时间（算法）进行攻击

### 费尔马小定理(Fermat's little theorem)
如果m是一个素数，且a不是m的倍数，那么，根据费尔马小定理有$a^{m-1} \equiv 1(mod \quad m)$ 

### 欧拉函数(Euler totient fuction)
表示模n的余数化简集中元素的数目。用$\oint(n)$ 表示与n互素的小于n的正整数的数目(n>1)。

### 中国剩余定理(Chinese remainder theorem)
一个数(小于一些素数之积)被他的余数模这些素数唯一确定；代码：  
```c++
int chinese_remainder (size_t r, int *m, int *u)
{
    size_t i;
    int modulus;
    int n;
    modulus = 1;
    for( i = 0; i < r; ++i)
        modules *= m[i];
    n = 0;
    for( i = 0; i < r; ++i) {
        n += u[i] * modexp(modulus / m[i], totient(m[i])), m[i]);
        n %= modulus;
    }
    return n;
}
```

### 二次剩余(quadratic residue)
如果p是素数，且a < p,如果:$x^2 \equiv a(mod \quad p)$对某些x成立，那么称a是对模p的二次剩余。

### 勒让德符号(Legendre symbol)
写作L(a, p), 当a为任意整数且p是一个大于2的素数时，它等于0， 1 或 -1。 
L(a, p) = 0,如果a被p整除 
L(a, p) = 1,如果a是二次剩余 
L(a, p) = -1,如果a是非二次剩余 
一种计算L(a, p)的方法是:$L(a, p)=a^{(p-1)/2} mod \quad p$

### 雅克比符号(Jacobi symbol)
写作J(a, n),是勒让德符号的合数模的一般化表示，它定义在任意整数a和奇整数n上。

### Blum整数(Blum integar)
如果p和q是两个素数，且都是与3模4同余的，那么n=p x q叫做Blum整数。

### 生成元(generator)
如果p是一个素数，且g小于p，对于从0~p-1的每一个b，都存在某个a，使得$g^a \equiv b(mod \quad p)$,那么g是模p的生成元,也称为g是p的本原元(primitive)。

### 因子分解
1. 数域筛选法(Number Field Sieve, NFS)
2. 二次筛选法(Quadratic Sieve, QS)
3. 椭圆曲线法(Elliptic Curve Method, ECM)
4. Pollard的蒙特卡罗算法(Pollard's Monte Carlo algorithm)
5. 连分式算法(continued fraction algorithm)
6. 试除法(trial division)

### 强素数(strong prime)
如果n是两个素数p和q之积，那么p和q采用强素数将更可取。强素数是慢速某些特性的素数，使得用某些特殊因子分解方式对他们的乘积n进行分解很困难。

### 计算有限群中的离散对数
密码设计者对下面三个主要群的离散对数很感兴趣:
* 素数域的乘法群:GF(p)
* 特征为2的有限域上的乘法群$GF(2^n)$
* 有限域F上的椭圆曲线群 EC(F)