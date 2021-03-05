# 标题
```
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题
```

# 段落
```
段落换行:2个空格+回车
重新开始段落:使用一个空行
```

# 字体
``` 
斜体:*字体*或_字体_
粗体:**字体*或__字体__
粗斜体:___字体___
```

# 分割线
```
***
* * *
******
- - -
----------
```

# 删除线
``` 
~~删除线~~ 
```

# 下划线
``` 
<u>下划线<u>
```

# 脚注
``` 
[^文字] -- 注释
```

# 列表
```
无序列表：*第一项 *第二项 *第三项 （*, +， - 都可以）
有序列表：1.第一项 2.第二项 3.第三项
列表嵌套：1.第一项：-嵌套 2.第二项：-嵌套
```

# 区块
```
普通区块：>区块1 >区块2
嵌套区块：>第一层 >>第二层
```

# 代码
```
方法一：用4个空格或一个制表符
方法二：用```编程语言
```

# 链接
```
方法1：[链接名称](链接地址)
方法2：<链接地址>
高级用法：
	这个链接用 1 作为网址变量 [Google][1]
	这个链接用 runoob 作为网址变量 [Runoob][runoob]
	然后在文档的结尾为变量赋值（网址）
  		[1]: http://www.google.com/
    	[runoob]: http://www.runoob.com/
```

# 图片
```
![图片标题](图片地址)
```

# 表格
```
无对齐方式
|  表头  |  表头  |
|--------|--------|
| 单元格 | 单元格 |
| 单元格 | 单元格 |

对齐方式
-: 右对齐, :- 左对齐, :-: 居中
|  表头  |  表头  |
|:-------|-------:|
| 单元格 | 单元格 |
| 单元格 | 单元格 |

```

# 公式
```
$$公式内容$$
```
一些常用的数学公式：  
|类型|写法|
|:--|:--|
|无穷, Delta, Gamma, Theta, Lambda, Sigma, Upsilon, Phi, Omega|$\infty$, $\Delta$, $\Gamma$, $\Theta$, $\Lambda$, $\Sigma$, $\Upsilon$, $\Phi$, $\omega$|
|对于所有, 存在, 因为, 所以|$\forall$, $\exists$, $\because$, $\therefore$|
|属于, 不属于, 子集, 非子集, 真子集, 非真子集|$x \in y$, $x \notin y$, $x \subset y$, $x \not\subset y$, $x \subseteq y$, $x \subsetneq y$|
|并,交,差集|$x \cup y$, $x \cap y$, $x \setminus y$|
|实数集, 自然数集, 空集|$\mathbb{R}$, $\mathbb{Z}$, $\emptyset$|
|加减, 减加, 乘法, 点乘, 星乘, 除法, 斜法, 空格, $\oint$|$x \pm y=z$, $x \mp y=z$, $x \times y=z$, $x \cdot y=z$, $x \ast y=z$, $x \div y=z$, $x/y=z$, $x \quad y$, $\oint$|
|大于等于, 小于等于, 不等于, 约等于, 恒等于|$x+y \geq z$, $x+y \leq z$, $x+y \neq z$, $x+y \approx z$, $x+y \equiv z$|
|分数，平方|$\frac{7x+5}{1+y^2}$|
|上标, 下标, 省略号, 开根号|$a^b$, $z=z_l$, $\cdots$, $\sqrt{2}+\sqrt[n]{3}$|
|矢量|$\vec{a} \cdot \vec{b}=0$|
|极限|$\lim^{x \to \infty}_{y \to 0} {\frac{x}{y}}$|
|累加|$\sum \frac{1}{i^2}$|
|累乘|$\prod \frac{1}{i^2}$|
|积分|$\int^{\infty}_{0}{xdx}$|
|微分|$\frac{\partial x}{\partial y}$|
|组合公式1|${n+1 \choose k}={n \choose k}+{n \choose k-1}$|
|组合公式2|$\sum_{k_0,k_1,\ldots>0 \atop k_0+k_1+\cdots=n}A_{k_0}A_{k_1}\cdots$|

矩阵的表示1:$$ \begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9
\end{bmatrix} $$



矩阵的表示2:$$ \begin{Bmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9
\end{Bmatrix} $$


# 绘制流程图，时序图，甘特图
## 流程图
### 样式流程图
基本语法:
- graph 指定流程图方向：
> - graph LR 从左到右(left right)
> - graph TD 从上到下(top bottom)
> - graph RL 从右到左(right left)
> - graph BT 从下到上(bottom top)
- 元素的形状定义：
> - id【描述】 以直角矩形绘制
> - id(描述) 以圆角矩形绘制
> - id{描述} 以菱形绘制
> - id>描述] 以不对称矩形绘制
> - id((描述)) 以圆形绘制
- 线条定义：
> - A-->B 带箭头指向
> - A---B 不带箭头连接
> - A-.-B 虚线连接
> - A-.->B 虚线指向
> - A==>B 加粗箭头指向
> - A--描述---B 不带箭头指向并在线段中间添加描述
> - A--描述-->B 带描述的箭头指向
> - A-.描述.->B 带描述的虚线连指向
> - A==描述==>B 带描述的加粗箭头指向
- 子流程图定义:
```sh
subgraph title
    graph direction
end
```

例:
```sh
​```mermaid
graph LR
    A(开始) -->B(起床)
    B --天气不好--- C>干活]
    C ==> D{休息时间到了}
    D -.yes.-> E((休息))
    D -.no.-> C
    E --> F(吃饭)
	subgraph one
	F(吃饭)-->G(吃菜)-->H(夹菜)
	end
```

### 标准流程图
基本语法：
- 定义模块 id=>关键字: 描述 （“描述”的前面必须有空格，“=>” 两端不能有空格）
- 关键字：
> - start 流程开始，以圆角矩形绘制
> - opearation 操作，以直角矩形绘制
> - condition 判断，以菱形绘制
> - subroutine 子流程，以左右带空白框的矩形绘制
> - inputoutput 输入输出，以平行四边形绘制
> - end 流程结束，以圆角矩形绘制
- 定义模块间的流向：
> - 模块1 id->模块2 id ：一般的箭头指向
> - 条件模块id (描述)->模块id(direction) ：条件模块跳转到对应的执行模块，并指定对应分支的布局方向

例子:
```sh
​```mermaid
st=>start: 开始框
op=>operation: 处理框
cond=>condition: 判断框（是或否?）
sub1=>subroutine: 子流程
io=>inputoutput: 输入输出框
e=>end: 结束框

st->op->cond
cond(yes)->io->e
cond(no)->sub1(right)->op
```