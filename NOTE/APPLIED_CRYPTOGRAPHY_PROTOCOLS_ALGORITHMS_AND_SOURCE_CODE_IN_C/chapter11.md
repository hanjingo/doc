# 第十一章 数学背景
[TOC]



## 信息论

### 熵和不确定性

`信息量(amount of information)` 假设信息是等可能的，对消息中所有可能的值进行编码所需要的最少位数。

### 语言信息率

`语言信息率(rate of language)` 的计算公式：

 $r=H(M)/N$

- $r$ 语言信息率
- $N$ 消息的长度，在N相当大时，标准英语的语言信息率($r$值)在1.0位/字母与1.5位/字母之间

`绝对信息率(absolute rate)` 假定每一个字符串是等可能的，对每一个字母而言可被编码的最大位数。如果在一种语言中有L个字母，其绝对信息率是：

$R=log_2L$ 

`冗余度(redundancy)` 语言的冗余度，称为$D$，定义为：

$D = R - r$

### 密码系统的安全性

语言冗余度越大，它就越容易被攻击。密码系统的熵可由秘钥空间大小$K$来衡量:$H(K)=log_2K$

### 唯一解距离

`唯一解距离(unidty distance)` 使得对应明文的实际信息（熵）与加密秘钥的熵之和等于所用的密文位数的渐进密文量。

1. 对于大多数对称秘钥系统而言，唯一减距离定义为秘钥系统的熵除以语言的冗余度：$U=H(K)/D$
2. 唯一解距离与冗余度成反比。唯一解距离无穷大的密码系统定义为具有`理想保密(ideal secrecy)`
3. 对于长度为n的消息而言，将一个密文消息解密为同一语言中某个有意义的明文，不同秘钥的数目由下式给出:$2^{H(k)-nD}-1$

可变密钥长度的ASCII码文本加密算法的唯一解距离：

| 密钥长度（位） | 唯一解距离（字符） | 密钥长度（位） | 唯一解距离（字符） |
| -------------- | ------------------ | -------------- | ------------------ |
| 40             | 5.9                | 80             | 11.8               |
| 56             | 8.2                | 128            | 18.8               |
| 64             | 9.4                | 156            | 37.6               |

### 混乱和扩散
`混乱(confusion)` 用于掩盖明文和密文之间的关系。

`扩散(diffusion)` 通过将明文冗余度分散到密文中使之分散开来；密码分析者寻求这些冗余度将会更难；产生扩散最简单的方法是通过换位（也称为置换）。



## 复杂性理论

### 算法的复杂性

算法的计算复杂性常常用两个变量来度量：`T(时间复杂性 time complexity) `和 `S(空间复杂性 space complexity)` 

复杂性分类:  

* `常数(constant)` 一个算法的复杂性不依赖于n，即为$O(1)$；
* `线性(linear)` 时间复杂性是$O(n)$；
* `二次方(quadratic)` 三次方(cubic)：...；
* `指数(exponential)` 时间复杂性为:$O(t^{f(n)})$
* `超多项式(superpdynomial)` 复杂性为:$O(c^{f(n)})$
  - $c$ 常数
  - $f(n)$ 是大于常数而小于线性的函数

### 问题的复杂性
NP问题与密码学的关系如下:许多对称算法和所有公开密钥算法能够用非确定性的多项式时间（算法）进行攻击



## 数论

### 模运算

如果$a = b + kn$对某些整数$k$成立，那么$a \equiv b (mod \, n) $。如果$a$为正，$b$为`0~n`，那么可以将$b$看作$a$被$n$整除后的余数。有时$b$叫做$a$模$n$的**余数(residue)**。有时$a$叫做与$b$模$n$**同余(congruent)**

从`0~n-1`的整数组成的集合构成了模$n$的**完全剩余集(complete set of residue)**。这意味着，对于每一个整数$a$，它的模$n$的余项是从`0~n-1`的某个数。

$a$模$n$的运算给出了$a$的余数，余数是从`0~n-1`的某个整数，这种运算称为**模变换(modular reduction)**。

### 素数

**素数** 比1大，其因子只有1和它本身，没有其它数可以整除它。

### 最大公因子

**互素(relatively prime)** 它们除了1外没有共同的因子；即，如果$a$和$n$的**最大公因子(greatest common divisor)**等于1，那么可写作：$gcd(a, n) = 1$；

**欧几里得算法(Euclid's algorithm)** 用于计算两个数的最大公因子的方法，其C语言描述如下：

返回单个最大公因子：

```c
/* returns gcd of x and y */
int gcd(int x, int y)
{
	int g;
  if (x < 0)
    x = -x;
  if (y < 0)
    y = -y;
  if (x + y == 0)
    ERROR;
  g = y;
  while(x > 0) {
  	g = x;
    x = y % x;
    y = g;
  }
  return g;
}
```

返回最大公因子数组：

```c
/* returns the gcd of x1, x2, ... xm */
int multiple_gcd(int m, int *x)
{
	size_t i;
  int g;
  if (m < 1)
    return 0;
  g = x[0];
  for (i = 1; i < m; ++i) {
  	g = gcd(g, x[i]);
    if (g == 1)
      return 1;
  }
  return g;
}
```

### 求模逆元

`求模逆元(inverse)` 寻找一个$x$，使得：

$1 = (a \times x) mod \, n$

也可写作：

$a^{-1} \equiv x(mod \, n)$

如果$a$和$n$互素，那么$a^{-1} \equiv x (mod \, n)$有唯一解。

如果$a$和$n$不是互素的，那么$a^{-1} \equiv (mod \, n)$没有解。

如果$n$是素数，那么从`1~n-1`的每一个数与$n$都是互素的，且在这个范围内恰好有一个逆元。

**扩展欧几里得算法(extended Euclidean algorithm)** 的C++语言描述：

```c++
#define isEven(x)  ((x & 0x01) == 0)
#define isOdd(x)   (x & 0x01)
#define swap(x, y) (x ^= y, y ^= x, x ^= y)
void ExtBinEuclid(int *u, int *v, int u1, int *u2, int *u3)
{
	int k, t1, t2, t3;
  if (*u < *v) swap(*u, *v);
  for (k = 0; isEven(*u) && isEven(*v); ++k) {
  	*u >>= 1; *v >>= 1;
  }
  *u1 = 1; *u2 = 0; *u3 = *u; t1 = *v; t2 = *u-1; t3 = *v;
  do {
    do {
			if (isEven(*u3)) {
    		if (isOdd(*u1) || isOdd(*u2)) {
      		*u1 += *v; *u2 += *u;
      	}
      	*u1 >>= 1; *u2 >>= 1; *u3 >>= 1;
    	}
    	if (isEven(t3) || *u3 < t3) {
    		swap(*u1, t1); swap(*u2, t2); swap(*ue, t3);
    	}
  	} while(isEven(*u3));
  	while(*u1 < t1 || *u2 < t2) {
  		*u1 += *v; *u2 += *u;
  	}
  	*u1 -= t1; *u2 -= t2; *u3 -= t3;
	}while(t3 > 0);
  while (*u1 >= *v && *u2 >= *u) {
  	*u1 -= *v; *u2 -= *u;
  }
  *u1 <<= k; *u2 <<= k; *u3 <<= k;
}

main(int argc, char *argv) {
	int a, b, gcd;
  
  if (argc < 3) {
  	cerr << "Usage: xeuclid u v" << endl;
    return -1;
  }
  int u = atoi(argv[1]);
  int v = atoi(argv[2]);
  if (u <= 0 || v <= 0) {
  	cerr << "Arguments must be positive!" << endl;
    return -2;
  }
  ExtBinEuclid(&u, &v, &a, &b, &gcd);
  cout << a << "*" << u << " + (-"
    << b << ") * " << v << " = " << gcd << endl;
  if (gcd == 1)
    	cout << "the inverse of " << v << " mod " << u << " is: "
    		<< u - b << endl;
  return 0;
}
```

### 求系数

欧几里得算法用于解决下面的一类问题：给出一个包含$m$个变量$x_1, x_2, ..., x_m$的数组，求一个包含$m$个系数$u_1, u_2, ..., u_m$的数组，使得：

$u_1 \times x_1 + ... + u_m \times x_m = 1$

### 费尔马小定理

如果$m$是一个素数，且$a$不是$m$的倍数，那么，根据**费尔马小定理(Fermat's little theorem)**，有：

$a^{m-1} \equiv 1(mod \, m)$ 

### 欧拉函数

`欧拉函数(Euler totient)` 也称作欧拉$\varphi$函数，写作$\phi(n)$，它表示与$n$互素的小于$n$的正整数的数目$(n>1)$。

如果$n$是素数，那么$\phi(n) = n - 1$；

如果$n = pq$，且$p$和$q$互素，那么$\phi(n) = (p - 1)(q - 1)$；

根据费尔马小定理的欧拉推广，如果$gcd(a, n) = 1$，那么$a^{\phi(n)} mod \, n = 1$；现在计算$a$模$n$很容易：$x = a^{\phi(n) - 1} mod \, n$；

计算逆元的两种方法都可推广到在一般性的问题中求解$x$（如果$gcd(a, n) = 1$）：

$(a \times x) mod \, n = b$

用欧拉推广公式，解：$x = (b \times a ^ {\phi(n) - 1} mod \, n)$

用欧几里得算法，解：$x = (b \times (a ^ {-1} mod \, n) mod \, n)$

例，求5模7的逆元是多少？

既然7是素数，$\phi(7) = 7 - 1 = 6$；因此，5模7的逆元是

$5^{6-1} mod \, 7 = 5^{5} mod \, 7 = 3$

**通常，欧几里得算法在计算逆元方面比欧拉推广更快，特别是对于500位范围内的数。如果$gcd(a, n) \neq 1$，并非一切都没用了。这种一般情况而言，$(a \times x) mod \, n = b$，可能有多个解或无解。**

### 中国剩余定理

`中国剩余定理(Chinese remainder theorem)` 一般而言，如果$n$的素因子可分解为$n = P_1 \times P_2 \times ... \times P_t$，那么方程组：$(x mod \, p_i) = a_i \quad i = 1, 2, ..., t$有唯一解，这里$x < n$（注意，有些素数可能不止一次地出现。例如，$P_1$可能等于$P_2$）。

例，取素数$3$和$5$，取一个数$14$，那么$14 mod \, 3 = 2, 14 mod \, 5 = 4$。则小于$3 \times 5 = 15$且具有上述余数的数只有14，即由这两个余数唯一确定了数$14$。

**总结：一个数(小于一些素数之积)被他的余数模这些素数唯一确定；**

**推论:**

如果$p$和$q$都是素数，且$p < q$，那么存在一个唯一的$x < p \times q$，使得

$a \equiv x(mod \, p)且b \equiv x(mod \, q)$

如果$a \geqslant b mod\, p$，那么

$x = (((a - (b mod \, p)) \times u) mod \, p) \times q + b$

如果$a < b mod \, p$，那么

$x = (((a + p - (b mod \, p)) \times u) mod \, p) \times q + b$

用C语言描述中国剩余定理：

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

### 二次剩余
如果$p$是素数，且$a < p$,如果:$x^2 \equiv a(mod \quad p)$对某些$x$成立，那么称a是对模p的**二次剩余(quadratic residue)**。

容易证明，当$p$为奇数时，对模$p$的二次剩余数目恰好是$(p-1)/2$，且与其二次非剩余的数目相同。而且，如果$x^2$等于二次剩余模$p$，那么$x^2$恰好有两个平方根：其中一个在$1~(p-1)/2$之间；另一个在$(p+1)/2~(p-1)$之间。这两个平方根中的一个也是模$p$的二次剩余，称为**主平方根(pricipal square root)**。

如果$n$是两个素数$p$和$q$之积，那么模$n$恰好有$(p-1)(q-1)/4$个二次剩余。模$n$的一个二次剩余是模$n$的一个完全平方。这是因为要成为模$n$的平方，其余数必须有模$p$的平方和模$q$的平方。例：模35有11个二次剩余：1, 4, 9, 11, 14, 15, 16, 21, 25, 29, 30。每个二次剩余恰好有4个平方根。

### 勒让德符号

`勒让德符号(Legendre symbol)`，写作$L(a, p)$，当$a$为任意整数且$p$是一个大于2的素数时，它等于0, 1或-1。

$L(a, p) = 0$，如果a被p整除 

$L(a, p) = 1$，如果a是二次剩余 

$L(a, p) = -1$，如果a是非二次剩余 

一种计算$L(a, p)$的方法是:$L(a, p)=a^{(p-1)/2} mod \, p$

或者用下面的算法计算：

1. 如果$a = 1$，那么$L(a, p) = 1$。
2. 如果$a$是偶数，那么$L(a, p) = L(a/2, p) \times (-1)^{(p^2 - 1)/8}$。
3. 如果$a$是奇数（且$a \neq 1$），那么$L(a, p) = L(p mod \, a, a) \times (-1)^{(a-1)\times(p-1)/4}$。

### 雅克比符号
`雅可比符号(Jacobi symbol)`，写作$J(a, n)$，是勒让德符号的合数模的一般化表示，它定义在任意整数$a$和奇整数$n$上。

雅可比符号是基于$n$的除数的余数化简集上的函数，可按多种方法进行计算，下面列举一种方法：

定义1：$J(a, n)$只定义在$n$为奇数的情况下。

定义2：$J(0, n) = 0$。

定义3：如果$n$是素数，且$n$能整除以$a$，那么$J(a, n) = 0$。

定义4：如果$n$是素数，且$a$是模$n$的一个二次剩余，那么$J(a, n) = 1$。

定义5：如果$n$是素数，且$a$是模$n$的一个非二次剩余，那么$J(a, n) = -1$。

定义6：如果$n$是合数，那么$J(a, n) = J(a, P_1) \times ... \times J(a, P_m)$，其中$P_1 ... P_m$是$n$的素因子。

计算雅可比符号的递归算法如下：

规则1：$J(1, n) = 1$。

规则2：$J(a \times b, n) = J(a, n) \times J(b, n)$。

规则3：如果$(n^2 - 1) / 8$是偶数，则$J(2, n) = 1$；否则，为$-1$。

规则4：$J(a, n) = J((a mod \, n), n)$。

规则5：$J(a, b_1 \times b_2) = J(a, b_1) \times J(a, b_2)$。

规则6：如果$a$和$b$都是奇数，且它们的最大公因子是$1$，那么

规则6a：如果$(a-1)(b-1)/4$是偶数，那么$J(a, b) = J(b, a)$。

规则6b：如果$(a - 1)(b - 1)/4$是奇数，那么$J(a, b) = -J(b, a)$。

C语言描述如下：

```c
int jacobi(int a, int b)
{
	int g;
  assert(odd(b));
  if (a >= b) a %= b;
  if (a == 0) return 0;
  if (a == 1) return 1;
  if (a < 0)
  if ((b - 1) / 2 % 2 == 0)
  	return +jacobi(a / 2, b);    
  else
    return -jacobi(-a, b);
  g = gcd(a, b);
  assert(odd(a));
  if (g == a)
    return 0;
  else if (g != 1)
    return jacobi(g, b) * jacobi(a/g, b);
  else if (((a-1)*(b-1)/4) % 2 == 0)
    return +jacobi(b, a);
  else
    return -jacobi(b, a);
}
```

### Blum整数

如果$p$和$q$是两个素数，且都是与$3$模$4$同余的，那么$n = p \times q$叫做**Blum整数(Blum integer)**。如果$n$是一个Blum整数，那么它的每一个二次剩余恰好有4个平方根，其中一个也是平方，这就是主平方根。

### 生成元
如果$p$是一个素数，且$g$小于$p$，对于从`0~p-1`的每一个$b$，都存在某个$a$，使得$g^a \equiv b(mod \quad p)$，那么$g$是模$p$的**生成元(generator)**，也称为$g$是$p$的**本原元(primitive)**。

例，如果$p = 11$，2是模11的一个生成元：

$2^{10} = 1024 \equiv 1(mod \, 11)$

$2^1 = 2 \equiv 2(mod \, 11)$

$2^8 = 256 \equiv 3(mod \, 11)$

$2^2 = 4 \equiv 4(mod \, 11)$

$2^4 = 16 \equiv 5(mod \, 11)$

$2^9 = 512 \equiv 6(mod \, 11)$

$2^7 = 128 \equiv 7(mod \, 11)$

$2^3 = 8 \equiv 8(mod \, 11)$

$2^6 = 64 \equiv 9(mod \, 11)$

$2^5 = 32 \equiv 10(mod \, 11)$

对于$p = 11$，生成元是$2, 6, 7, 8$，其它数不是生成元。例如，3不是生成元，因为下列方程无解。

$3^a \equiv 2(mod \, 11)$



## 因子分解

目前最好的因子分解算法：

- `数域筛选法(Number Field Sieve, NFS)`
- `二次筛选法(Quadratic Sieve, QS)`
- `椭圆曲线法(Elliptic Curve Method, ECM)`
- `Pollard的蒙特卡罗算法(Pollard's Monte Carlo algorithm)`
- `连分式算法(continued fraction algorithm)`
- `试除法(trial division)`



## 素数的产生

### Solovag-Strassen

Robert Solovag和Volker Strassen开发了一种概率的基本测试算法。这个算法使用了雅可比函数来测试$p$是否为素数：

1. 选择一个小于$p$的随机数$a$。
2. 如果$gcd(a, p) \neq 1$，那么$p$不能通过测试，它是合数。
3. 计算$j = a^{(p-1)/2} mod \, p$。
4. 计算雅可比符号$J(a, p)$。
5. 如果$j \neq J(a, p)$，那么$p$肯定不是素数。
6. 如果$j = J(a, p)$，那么$p$不是素数的可能性至多是50%。

数$a$称为一个`证据(wimess)`，如果$a$不能确定$p$，$p$肯定不是素数。如果$p$是合数，随机数$a$是证据的概率不小于50%。对$a$选择$t$个不同的随机值，重复$t$次这种测试。$p$通过所有$t$次测试后，它是合数的可能性不超过$1/2^t$。

### Lehmann

另一种更简单的测试是由Lehmann独自研究出的；下面是他的测试算法：

TODO

### Rabin-Miller

首先选择一个待测的随机数$p$，计算$b$，$b$是$2$整除$p - 1$的次数（即，$2^b$是能整除$p - 1$的2的最大幂数）。然后计算$m$，使得$n = 1 + 2^bm$。

1. 选择一个小于$p$随机数$a$。
2. 设$j = 0$且$z = a^m mod \, p$。
3. 如果$z = 1$或$z = p - 1$，那么$p$通过测试，$p$可能是素数。
4. 如果$j > 0 $且$z = 1$，那么$p$不是素数。
5. 设$j = j + 1$。如果$j < 6$且$z \neq p - 1$，设$z = z^2 mod \, p$，然后回到第4步。如果$z = p - 1$，那么$p$通过测试，$p$可能是素数。
6. 如果$j = b$且$z \neq p - 1$，那么$p$不是素数。

### 强素数
如果n是两个素数$p$和$q$之积，那么$p$和$q$采用**强素数(strong prime)**将更可取。强素数是慢速某些特性的素数，使得用某些特殊因子分解方式对他们的乘积$n$进行分解很困难。给出了以下特性：

- $p - 1$和$q - 1$的最大公因子应该较小。
- $p - 1$和$q - 1$都应有大的素因子，分别记为$p'$和$q'$。
- $p' - 1$和$q' - 1$都应有大的素因子。
- $p + 1$和$q + 1$都应有大的素因子。
- $(p - 1)/2$和$(q - 1)/2$都应该是素数。



## 有限域上的离散对数

模指数运算是频繁地用于密码学中的另一种单向函数。计算下面的表达式很容易：

$a^x mod \, n$

模指数运算的逆问题是找出一个数的离散对数，这是一个难题：

$求解x, 使是a^x \equiv b(mod \, n)$

例：

$如果 3^x \equiv 15 mod \, 17，那么 x = 6$

### 计算有限群中的离散对数

密码设计者对下面三个主要群的离散对数很感兴趣:
* 素数域的乘法群: $GF(p)$
* 特征为2的有限域上的乘法群: $GF(2^n)$
* 有限域F上的椭圆曲线群: $EC(F)$