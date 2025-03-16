# DOT语言

[TOC]



## DOT语法

DOT语言是一种文本图形描述语言它提供了一种简单的描述图形的方法，并且可以为人类和计算机程序所理解。DOT语言文件通常是具有`.gv`或是`.dot`的文件扩展名。很多程序都可以处理DOT文件。



## Graphviz

`graphviz(Graph Visualization Software)` 是一个由AT&T实验室启动的开源工具包，用于绘制DOT语言脚本描述的图形。

### 语法

Graphviz语法主要由以下部分组成：

- `代码块` 位于`{}`中的语句即为代码块；
- `语句` 以`;`结尾，主要分为代码块，节点，连线，属性四种语句类型；
- `实体对象标识符` 除了特殊字符外的所有字符都可以用于标识符，如数字，中英文字符串等；
- `注释` `//`表示单行注释，`/*...*/`表示多行注释。

### 节点

| 属性名    | 默认值      | 说明                                                         |
| --------- | ----------- | ------------------------------------------------------------ |
| label     | name name   | 节点显示内容                                                 |
| color     | black       | node边框颜色                                                 |
| fontcolor | black       | 字体颜色                                                     |
| fillcolor |             | 背景色                                                       |
| fontname  | Times-Roman | 字体                                                         |
| fontsize  | 14          | 字体大小                                                     |
| shape     | ellipse     | 形状：<br>- box<br>- box3d<br>- cds<br>- circle<br>- component<br>- diamond<br>- doublecircle<br>- doubleoctagon<br>- egg<br>- ellipse<br>- folder<br>- hexagon<br>- house<br>- invhouse<br>- invtrapezium<br>- invtriangle<br>- Mcircle<br>- Mdiamond<br>- Msquare<br>- none<br>- note<br>- octagon<br>- oval<br>- parallelogram<br>- pentagon<br>- plain<br>- plaintext<br>- point<br>- polygon<br>- promoter<br>- rect<br>- rectangle<br>- septagon<br>- square<br>- star<br>- tab<br>- trapezium<br>- triangle<br>- tripleoctagon<br>- underline |
| style     |             | 图形样式：<br>- eg.bold<br>- dashed<br>- dotted<br>- filled  |
| height    | .5          | 最低高度尺寸                                                 |
| width     | .75         | 最低宽度尺寸                                                 |
| URL       |             | 点击跳转地址                                                 |
| target    |             | 点击跳转打开方式                                             |
| image     |             | 背景图片地址                                                 |

例：

```markdown
![](https://g.gravizo.com/svg?
	digraph demo {
		rankdir=LR
    	bgcolor="floralwhite"
    	"box"[shape=box]
    	"box3d"[shape=box3d]
    	"cds"[shape=cds]
    	"circle"[shape=circle]
    	"component"[shape=component]
    	"diamond"[shape=diamond]
    	"doublecircle"[shape=doublecircle]
    	"doubleoctagon"[shape=doubleoctagon]
    	"egg"[shape=egg]
    	"ellipse"[shape=ellipse]
    	"foler"[shape=folder]
    	"hexagon"[shape=hexagon]
    	"house"[shape=house]
    	"invhouse"[shape=invhouse]
    	"invtrapezium"[shape=invtrapezium]
    	"invtriangle"[shape=invtriangle]
    	"Mcircle"[shape=Mcircle]
    	"Mdiamond"[shape=Mdiamond]
    	"Msquare"[shape=Msquare]
    	"none"[shape=none]
    	"note"[shape=note]
    	"octagon"[shape=octagon]
    	"oval"[shape=oval]
    	"parallelogram"[shape=parallelogram]
    	"pentagon"[shape=pentagon]
    	"plain"[shape=plain]
    	"plaintext"[shape=plaintext]
    	"point"[shape=point]
    	"polygon"[shape=polygon]
    	"promoter"[shape=promoter]
    	"rect"[shape=rect]
    	"rectangle"[shape=rectangle]
    	"septagon"[shape=septagon]
    	"square"[shape=square]
    	"star"[shape=star]
    	"tab"[shape=tab]
    	"trapezium"[shape=trapezium]
    	"triangle"[shape=triangle]
    	"tripleoctagon"[shape=tripleoctagon]
    	"underline"[shape=underline]
	}
)
```

![](https://g.gravizo.com/svg?
	digraph demo {
		rankdir=LR
    	bgcolor="floralwhite"
    	"box"[shape=box]
    	"box3d"[shape=box3d]
    	"cds"[shape=cds]
    	"circle"[shape=circle]
    	"component"[shape=component]
    	"diamond"[shape=diamond]
    	"doublecircle"[shape=doublecircle]
    	"doubleoctagon"[shape=doubleoctagon]
    	"egg"[shape=egg]
    	"ellipse"[shape=ellipse]
    	"foler"[shape=folder]
    	"hexagon"[shape=hexagon]
    	"house"[shape=house]
    	"invhouse"[shape=invhouse]
    	"invtrapezium"[shape=invtrapezium]
    	"invtriangle"[shape=invtriangle]
    	"Mcircle"[shape=Mcircle]
    	"Mdiamond"[shape=Mdiamond]
    	"Msquare"[shape=Msquare]
    	"none"[shape=none]
    	"note"[shape=note]
    	"octagon"[shape=octagon]
    	"oval"[shape=oval]
    	"parallelogram"[shape=parallelogram]
    	"pentagon"[shape=pentagon]
    	"plain"[shape=plain]
    	"plaintext"[shape=plaintext]
    	"point"[shape=point]
    	"polygon"[shape=polygon]
    	"promoter"[shape=promoter]
    	"rect"[shape=rect]
    	"rectangle"[shape=rectangle]
    	"septagon"[shape=septagon]
    	"square"[shape=square]
    	"star"[shape=star]
    	"tab"[shape=tab]
    	"trapezium"[shape=trapezium]
    	"triangle"[shape=triangle]
    	"tripleoctagon"[shape=tripleoctagon]
    	"underline"[shape=underline]
	}
)

### 边

| 属性名    | 默认值  | 说明                                                         |
| --------- | ------- | ------------------------------------------------------------ |
| label     |         | 描述关系                                                     |
| color     | black   | 箭头颜色                                                     |
| fontcolor | black   | 关系文件颜色                                                 |
| dir       | forward | 设置方向：<br>- forward<br>- back<br>- both<br>- none        |
| arrowhead | normal  | 箭头头部形状：<br>- box<br>- crow<br>- diamond<br>- dot<br>- none<br>- normal<br>- vee |
| arrowtail |         | 箭头尾部形状                                                 |
| arrowsize | 1.0     | 箭头大小                                                     |
| style     |         | 图形样式：<br>- eg.bold<br>- dashed<br>- dotted<br>- filled  |
| lhead     |         | 当 compound 为true时，lhead用于指定边指向的cluster           |
| ltail     |         | 与ltail类似                                                  |

```markdown
![](https://g.gravizo.com/svg?
	digraph demo {
    	bgcolor="floralwhite"
    	rankdir=LR
    	"box"->"crow"[arrowhead=box]
    	"crow"->"curve"[arrowhead=crow]
    	"curve"->"diamond"[arrowhead=curve]
    	"diamond"->"dot"[arrowhead=diamond]
    	"dot"->"inv"[arrowhead=dot]
    	"inv"->"none"[arrowhead=inv]
    	"none"->"normal"[arrowhead=none]
    	"normal"->"tee"[arrowhead=normal]
    	"tee"->"vee"[arrowhead=tee]
    	"vee"->"box"[arrowhead=vee]
    	a->b[arrowhead=lcrowortee]
    	"solid"->"dashed"[style=solid]
    	"dashed"->"dotted"[style=dashed]
    	"dotted"->"bold"[style=dotted]
    	"solid"->"invis"[style=bold]
    	"invis"->"solid"[style=invis]
    }
)
```

![](https://g.gravizo.com/svg?
	digraph demo {
    	bgcolor="floralwhite"
    	rankdir=LR
    	"box"->"crow"[arrowhead=box]
    	"crow"->"curve"[arrowhead=crow]
    	"curve"->"diamond"[arrowhead=curve]
    	"diamond"->"dot"[arrowhead=diamond]
    	"dot"->"inv"[arrowhead=dot]
    	"inv"->"none"[arrowhead=inv]
    	"none"->"normal"[arrowhead=none]
    	"normal"->"tee"[arrowhead=normal]
    	"tee"->"vee"[arrowhead=tee]
    	"vee"->"box"[arrowhead=vee]
    	a->b[arrowhead=lcrowortee]
    	"solid"->"dashed"[style=solid]
    	"dashed"->"dotted"[style=dashed]
    	"dotted"->"bold"[style=dotted]
    	"solid"->"invis"[style=bold]
    	"invis"->"solid"[style=invis]
    }
)

### 起点，方向，尺寸，间距

起点：

```markdown
![](https://g.gravizo.com/svg?
	digraph G{
        node [shape=box];
        c1:n -> d1[label=n];
        c2:ne -> d1[label=ne];
        c3:e -> d1[label=e];
        c4:se -> d1[label=se];
        c5:s -> d1[label=s];
        c6:sw -> d1[label=sw];
        c7:w -> d1[label=w];
        c8:rw -> d1[label=rw];
    }
)
```

![](https://g.gravizo.com/svg?
	digraph G{
        node [shape=box];
        c1:n -> d1 [label=n];
        c2:ne -> d2:ne [label=ne];
        c3:e -> d3:ne [label=e];
        c4:se -> d4:n [label=se];
        c5:s -> d5:n [label=s];
        c6:sw -> d6:n [label=sw];
        c7:w -> d7:nw [label=w];
        c8:rw -> d8:nw [label=rw];
    }
)

方向：

```markdown
![](https://g.gravizo.com/svg?
	digraph G{
        node [shape=box];
        A1 -> B1 [dir = both] [label=both];
        A2 -> B2 [dir = none] [label=none];
        A3 -> B3 [dir = back] [label=back];
        A4 -> B4 [dir = forward] [label=forward];
    }
)
```

![](https://g.gravizo.com/svg?
	digraph G{
        node [shape=box];
        A1 -> B1 [dir = both] [label=both];
        A2 -> B2 [dir = none] [label=none];
        A3 -> B3 [dir = back] [label=back];
        A4 -> B4 [dir = forward] [label=forward];
    }
)

尺寸：

- `ranksep`  相邻 rank 之间的距离；

间距：

- `nodesep`  同一个 rank 中的相邻节点的最小距离，单位为英寸（=2.54 cm)。直线的不同端点属于不同的 rank；

![](https://g.gravizo.com/svg?
	digraph G{
        nodesep=2;
        ranksep=1;
        rankdir=LR;
    	a -> b;
    	c;
    	b -> d;
    }
)

### 图

- `graph` 图
  - `digraph {...}` 有向图；
  - `graph {...}`无向图；
- `subgraph` 子图；

| 属性名    | 默认值      | 说明                                                         |
| --------- | ----------- | ------------------------------------------------------------ |
| bgcolor   |             | 背景颜色                                                     |
| compound  | false       | 配合lhead和ltail使用                                         |
| fontcolor | black       | 字体颜色                                                     |
| fontname  | Times-Roman | 字体                                                         |
| fontsize  | 14          | 字体大小                                                     |
| label     |             | 图片标签                                                     |
| layout    |             | 布局引擎                                                     |
| rank      |             | 子图等级限制：<br>- same<br>- min<br>- max<br>- source<br>- sink |
| rankdir   | TB          | 排序方向：<br>- LR<br>- TB                                   |
| ratio     |             | 垂直夸大率浮点数：<br>- fill<br>- compress<br>- auto         |
| size      |             | 最大大小（英寸）                                             |

例：

```markdown
![graphviz](https://g.gravizo.com/svg?
	digraph graph_name{
        bgcolor="transparent";
        subgraph cluster_subgraph_name{
        	node[shape=box];
        	cluster_A -> cluster_B;
        }
        subgraph subgraph_name{
            node[shape=none];
            sub_A -> sub_B [dir = both];
    	}
    	{
            node[shape=octagon];
            nest_A -> nest_B [dir = none];
        }
    	global_A -> global_B [dir = back];
    	cluster_B -> global_B [dir = forward];
    	sub_B -> global_B;
    	nest_B -> global_B;
    }
)
```

![graphviz](https://g.gravizo.com/svg?
	digraph graph_name{
        bgcolor="transparent";
        subgraph cluster_subgraph_name{
        	node[shape=box];
        	cluster_A -> cluster_B;
        }
        subgraph subgraph_name{
            node[shape=none];
            sub_A -> sub_B [dir = both];
    	}
    	{
            node[shape=octagon];
            nest_A -> nest_B [dir = none];
        }
    	global_A -> global_B [dir = back];
    	cluster_B -> global_B [dir = forward];
    	sub_B -> global_B;
    	nest_B -> global_B;
    }
)

### 二叉树

- `|` 分隔符
- `<>` 锚点
- `{}` 竖型排列

```markdown
![graphviz](https://g.gravizo.com/svg?
	digraph demo {
    	bgcolor="beige"
    	node [shape="record", height=.1]
    	node0[label="<f0> | <f1> G | <f2>"]
    	node1[label="<f0> | <f1> E | <f2>"]
    	node2[label="<f0> | <f1> B | <f2>"]
    	node0:f0 -> node1:f1
    	node0:f2 -> node2:f1
    	a [label="{a | b | c}"]
    }
)
```

![graphviz](https://g.gravizo.com/svg?
	digraph demo {
    	bgcolor="beige"
    	node [shape="record", height=.1]
    	node0[label="<f0> | <f1> G | <f2>"]
    	node1[label="<f0> | <f1> E | <f2>"]
    	node2[label="<f0> | <f1> B | <f2>"]
    	node0:f0 -> node1:f1
    	node0:f2 -> node2:f1
    	a [label="{a | b | c}"]
    }
)



## 参考

### 外部链接

- [Graphviz官网](http://www.graphviz.org/)
- [十分钟学会graphviz画图](https://www.jianshu.com/p/6d9bbbbf38b1)
- [markdown 绘图利器之graphviz](https://zhuanlan.zhihu.com/p/194274635)
- [Graphviz绘图 - DOT语言](https://itopic.org/graphviz.html)
- [Graphviz Tutorial 1.0 文档](https://graphviztutorial.readthedocs.io/zh_CN/latest/index.html#)
- [用Graphviz自动布局各种图](https://www.chungkwong.cc/dot.html)
