# Solidity语言

[TOC]



## 基础语法

### 编译指示

`pragma`关键字用于启用某些编译器功能或检查。

#### 版本控制

Solidity版本号格式为：`主版本号.副版本号.修复版本号`。

例，指定合约版本号范围：

```solidity
pragma solidity >=0.4.16 <0.9.0;
```

例，禁用`0.5.2`之前的版本：

```sh
pragma solidity ^0.5.2
```

#### ABI编码器

目前有`V1`和`V2`两款编/解码器，`V2`编码器能够编码和解码任意嵌套的数组和结构。

例，使用`V1`编码器：

```solidity
pragma abicoder v1;
```

例，使用`V2`编码器：

```solidity
pragma abicoder v2;
```

#### SMTChecker

在构建 Solidity 编译器时必须启用此组件，因此它并非在所有 Solidity 二进制文件中都可用。

例，启用SMTChecker：

```solidity
pragma experimental SMTChecker;
```

### 导入

编译器维护一个内部数据库（*虚拟文件系统*或简称*VFS*），其中为每个源单元分配一个唯一的*源单元名称*，该名称是一个不透明且非结构化的标识符。

导入方式：

- 全局导入；
- 重命名导入。

例，全局导入：

```solidity
import * as symbol from "filename";
import "filename" // 同上
import "filename" as symbol; // 同上
```

例，重命名导入：

```solidity
import {symbol1 as alias1, symbol2} from "filename";
```

### 基本类型

| 类型                                         | 支持的操作                                                   | 取值范围                           | 说明                             |
| -------------------------------------------- | ------------------------------------------------------------ | ---------------------------------- | -------------------------------- |
| bool                                         | `!, &&, ||, ==, ==, !=`                                      | [false, true]                      | 布尔值                           |
| uint<br>int                                  | `<=, <, ==, !=, >=, >`<br>`&, |, ^, ~`<br>`<<, >>`<br>`+, -, *, /, % **(幂)` | [uint8, uint256]<br>[int8, int256] | 无符号整数<br>有符号整数         |
| unfixed<br>fixed                             | `<=, <, ==, !=, >=, >`<br>`+, -, *, /, %(模)`                | []                                 | 无符号定点数<br>有符号定点数     |
| address                                      | `<=, <, ==, !=, >=, >`                                       | [0, 20]byte                        | 地址                             |
| address payable                              | `<=, <, ==, !=, >=, >`                                       | [0, 20]byte                        | 带附加成员(transfer, send)的地址 |
| bytes1<br>bytes2<br>bytes3<br>...<br>bytes32 | `<=, <, ==, !=, >=, >`<br>`&, |, ^, ~`<br>`<<, >>`<br>`[i](索引访问)` | [1, n]                             | 字节数组                         |
| string                                       | `\<newline>`(转义换行符)<br>`\\`(反斜杠)<br>`\'`(单引号)<br>`\"`(双引号)<br>`\n`(新队)<br>`\r`(回车)<br>`\t`(标签)<br>`\xNN`(十六进制转义)<br>`\uNNNN`(unicode转义) |                                    | 字符串                           |
| hex""                                        |                                                              |                                    | 十六进制字面值                   |

例：

```solidity
address addr1 = address(this);
address payable addr2 = payable(0x123);

string memory str1 = unicode"hello 😊";

hex"001" hex"002" hex'003'
```

### 枚举

枚举可用于创建具有一组有限“常量值”的自定义类型。

例，定义枚举：

```solidity
enum e { One, Two, Three } // 定义枚举
e e1 = e.One; // 使用枚举
```

### 用户重定义类型

用户定义的值类型允许在基本值类型上创建零成本抽象，类似于别名。

例：

```solidity
type mytype is uint128;
```

### 数据地址

每个引用类型数据位置修饰：

- `storage` 对本地存储变量的赋值只分配一个引用；
- `memory` 对一个内存变量的更改在引用相同数据的所有其他内存变量中也可见；
- `calldata` 独立的副本，始终复制。

例：

```solidity
function fn(uint[] memory arr1) public {
	uint[] storage arr2 = arr1;
	uint[] calldata arr3 = arr1;
}
```

### 数组

数组可以具有编译时固定大小`T[k]`，也可以具有动态大小`T[]`。

### 切片

TODO

### 函数

分类：

- 内部函数：只能在合约内部调用，无法在合约上下文之外执行；
- 外部函数：由地址和函数签名组成，可以通过外部函数调用传递和返回。

定义：

函数是代码的可执行单元，函数可以在合约内定义，也可以在合约外定义。

函数格式：`function(<parameter types>){internal|external}[pure|view|payable][returns(<resturn types>)]`

- `parameter types` 参数

- `internal|external`内部/外部函数标识

- `pure|view|payable` 状态可变性

  | 状态可变性 | 可转换成的函数          | 说明   |
  | ---------- | ----------------------- | ------ |
  | pure       | `view`<br>`non-payable` |        |
  | view       | `non-payable`           |        |
  | payable    | `non-payable`           | 可收币 |

例，定义函数：

```solidity
contract c {
	function fn1() internal payable returns(bytes4) {...}
}
c c1;
c1.fn1();

function fn2(uint x) public pure returns(uint) {...}
```

### 事件

事件是与 EVM 日志记录工具的便利接口。

例，使用事件：

```solidity
contract c {
	event fn1(...); // 定义事件
	function fn2() public payable {
		emit fn1(...); // 触发事件
	}
}
```

### 错误

错误允许为故障情况定义描述性名称和数据，可用于还原语句。

例，定义错误：

```solidity
error Fail(...); // 定义错误
```

### 映射

例，将地址映射到uint：

```solidity
mapping (address => uint) public balance;
```

### 结构体

结构是自定义定义的类型，可以对多个变量进行分组。

例，定义结构体：

```solidity
struct info { // 定义结构体
	uint id;
	...
}
```



## 面向对象

### 权限

| 权限   | 说明 |
| ------ | ---- |
| public |      |
|        |      |
|        |      |

### 构造函数

TODO

### 成员函数

TODO



## 参考

[1] [Solidity](https://www.osgeo.cn/solidity/index.html)

[2] [Solidity 教程](https://www.w3cschool.cn/solidity/)