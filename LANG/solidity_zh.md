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

### 类型

#### 基本类型

| 类型             | 支持的操作                                                   | 取值范围                           | 说明                             |
| ---------------- | ------------------------------------------------------------ | ---------------------------------- | -------------------------------- |
| bool             | `!, &&, ||, ==, ==, !=`                                      | [false, true]                      | 布尔值                           |
| uint<br>int      | `<=, <, ==, !=, >=, >`<br>`&, |, ^, ~`<br>`<<, >>`<br>`+, -, *, /, % **(幂)` | [uint8, uint256]<br>[int8, int256] | 无符号整数<br>有符号整数         |
| unfixed<br>fixed | `<=, <, ==, !=, >=, >`<br>`+, -, *, /, %(模)`                | []                                 | 无符号定点数<br>有符号定点数     |
| address          | `<=, <, ==, !=, >=, >`                                       | [0, 20]                            | 地址                             |
| address payable  | `<=, <, ==, !=, >=, >`                                       | [0, 20]                            | 带附加成员(transfer, send)的地址 |
| bytes            | `<=, <, ==, !=, >=, >`<br>`&, |, ^, ~`<br>`<<, >>`<br>`[i](索引访问)` | [1, n]                             | 字节数组                         |
| string           | `\<newline>`(转义换行符)<br>`\\`(反斜杠)<br>`\'`(单引号)<br>`\"`(双引号)<br>`\n`(新队)<br>`\r`(回车)<br>`\t`(标签)<br>`\xNN`(十六进制转义)<br>`\uNNNN`(unicode转义) |                                    | 字符串                           |
| hex""            |                                                              |                                    | 十六进制字面值                   |

例：

```solidity
address addr1 = address(this);
address payable addr2 = payable(0x123);

string memory str1 = unicode"hello 😊";

hex"001" hex"002" hex'003'
```

#### 数组

数组可以具有编译时固定大小`T[k]`，也可以具有动态大小`T[]`，新分配的数组的元素始终使用默认值初始化。

数组字面量是一个或多个表达式的逗号分割列表，用`[...]`标识。

例，使用数组字面量：

```solidity
contract c {
	 function fn1() public pure {
	 	fn2([uint(1), 2, 3]);
	 }
	 function fn2(uint[3] memory) public pure {
	 	...
	 }
}
```

#### 切片

切片没有任何成员，它们可以隐式转换为其基础类型的数组并支持索引访问；索引访问在底层数组中不是绝对的，而是相对于切片的起始位置。

切片没有类型名称，这意味着没有变量可以将切片作为类型，它们只存在于中间表达式中。

例：

```solidity
bytes4 arr1 = bytes4(s[:4]);
```

#### 映射

映射（Mapping）类似于其它语言的map或dictionary，Solidity语法不提供对映射进行迭代（可以通过自定义数据类型来避免这个问题）。

例，将地址映射到uint：

```solidity
mapping (address => uint) public balance;
```

例，通过自定义数据结构来迭代映射：

```solidity
struct pair{ uint keyIndex; uint value; }
struct s {
	mapping(uint => pair) data;
	uint[] keys; // 存储所有的key
}
type Iterator is uint;

function range(s storage self, uint n) internal view returns (Iterator) {
	while(n < self.keys.length && self.keys[n].deleted)
		n++;
	return Iterator.wrap(n);
}
```

#### 基本单位

以太单位：

- `1 wei == 1`
- `1 gwei == 1e9 wei`
- `1 ether == 1e18 wei`

时间单位：

- `1 seconds == 1`
- `1 minutes == 60 seconds`
- `1 hours == 60 minutes`
- `1 days = 24 hours`
- `1 weeks = 7 days`

#### 隐式转化

编译器会在赋值期间，将参数传递给函数以及应用运用运算符时自动应用隐式转化，转换规则如下：

| 源类型 | 目标类型     | 规则                               |
| ------ | ------------ | ---------------------------------- |
| 字符串 | 整型         | 先转化为足够大的整型，再将整型截断 |
| 字符串 | 固定字节数组 | 必须要长度一致                     |

例，隐式转化：

```solidity
uint8 x;
uint16 y;
uint32 z = x + y;

uint8  a = "12";
uint32 b = "1234";
uint16 c = "0x123456"; // c = 0x3456

byte2 b2 = hex"1234";
byte2 b2 = hex"12"; // 禁止转换
```

#### 显式转化

对于编译器不允许的隐式转换，可以通过显式转换来进行强制转换，转换规则如下：

| 源类型              | 目标类型           | 规则           |
| ------------------- | ------------------ | -------------- |
| 有符号型            | 无符号型           | 去掉符号       |
| 整型（长）          | 整型（短）         | 高阶位被截断   |
| 整型（短）          | 整型（长）         | 高阶位被填充   |
| 固定字节数组（长）  | 固定字节数组（短） | 切断右侧序列   |
| 固定字节数组（短）  | 固定字节数组（长） | 填充右侧序列   |
| 固定字节数组        | 整型               | 必须要长度相同 |
| 字节数组/切片（长） | 固定字节数组（短） | 截断右侧序列   |
| 字节数组/切片（短） | 固定字节数组（长） | 填充右侧序列   |

例，显式转化：

```solidity
int i1  = -3;
uint i2 = uint(i1); // i2 = 3

uint32 u1 = 0x12345678;
uint16 u2 = uint16(u1); // u2 = 0x5678
uint32 u3 = uint32(u2); // u3 = 0x00005678

bytes2 b2 = 0x1234;
bytes1 b1 = bytes1(b2); // b1 = 0x12
bytes4 b4 = bytes4(b2); // b4 = 0x12340000

bytes2 bi2 = 0x1234;
uint32 i1 = uint16(bi2);         // i1 = 0x00001234
uint32 i2 = uint32(bytes4(bi2)); // i2 = 0x12340000
uint8  i3 = uint8(uint16(bi2));  // i3 = 0x34
uint8  i4 = uint8(bytes1(bi2));  // i4 = 0x12

bytes b = "abcdefgh";
bytes calldata c = "abcdefgh";
bytes16 b16 = bytes16(b);    // b16 = "abcdefgh\0\0\0\0\0\0\0\0"
bytes3  b3  = bytes3(b);     // b3  = "abc"
bytes3  b4  = bytes3(c[:3]); // b4  = "abc\0"
```

#### 常量和不可变变量

变量被声明为以下两种类型之一时，在合约构建后不能被修改：

- `constant` 值必须在编译时固定；
- `immutable` 允许在构造时赋值。

例：

```solidity
contract C {
	string constant TEXT = "abc";
	uint immutable u;
	
	constructor(uint x) {
		u = x;
	}
}
```

### 操作符

#### 基本运算

| 运算                 | 说明   |
| -------------------- | ------ |
| `+, ++, +=`          | 加     |
| `-, --, -=`          | 减     |
| `*, **(平方), *=`    | 乘     |
| `/, /=`              | 除     |
| `%, |, &, ^, <<, >>` | 位运算 |

#### 三元运算

三元运算符表达式：`<expression> ? <trueExpression> : <falseExpression>`。

例：

```solidity
a == b ? 1 : 0;
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

### 函数

#### 分类

- 内部函数：在合约内部定义的函数；
- 外部函数：在合约外部定义的函数。

#### 定义

`function(<parameter types>){internal|external}[pure|view|payable][returns(<return types>)]`

- `parameter types` 参数

  函数参数的声明方式与变量相同，未使用的参数名称可以省略。

- `internal|external`内部/外部函数标识

- `pure|view|payable` 状态可变性

  | 状态可变性 | 可转换成的函数          | 说明                           |
  | ---------- | ----------------------- | ------------------------------ |
  | pure       | `view`<br>`non-payable` | 纯函数，承诺不读取或修改状态。 |
  | view       | `non-payable`           | 承诺不修改状态。               |
  | payable    | `non-payable`           | 接收以太功能（收币）。         |
  
  读取状态的定义：
  
  1. 从状态变量中读取；
  2. 访问`address(this).balance`或`<address>.balance`；
  3. TODO；
  4. 调用任何未标记`pure`的函数；
  5. 使用包含某些操作码的内联汇编。
  
  修改状态的定义：
  
  1. 写入状态变量；
  2. 发射事件；
  3. 创建其它合同；
  4. 使用`selfdestruct`；
  5. 通过调用发送以太币；
  6. 调用任何未标记`view`或`pure`的函数；
  7. 使用低级调用；
  8. 使用包含某些操作码的内联汇编。
  
- `return types` 返回值

  返回值的名称可以省略。

例，定义函数：

```solidity
contract c {
	function fn1() internal payable returns(bytes4) {...}
}
c c1;
c1.fn1();

function fn2(uint x) public pure returns(uint) {...}
```

#### 重载

一个合约可以有多个同名但参数类型不同的函数，这个过程称为“重载”。

例：

```solidity
// 内部函数重载
contract C {
	function f(uint value) public pure returns(uint out) { ... }
	function f(uint value, bool b) public pure returns(uint out) {...} 
}

// 外部函数重载
TODO
```

#### 调用

solidity支持递归调用，但是建议尽量避免使用递归调用，因为每个内部函数调用至少使用一个堆栈槽并且最多只有1024个可用槽。

solidity也支持外部调用，如果被调用合约本身抛出异常或者gas耗尽，函数调用也会导致异常。

例，递归调用函数：

```solidity
contract c {
	function fn() internal pure returns (uint ret) { return fn();}
}
```

#### 函数修饰符

函数修饰符可用于以声明方式更改函数的行为；修饰符是合约的可继承属性，可以被派生合约覆盖（仅限于被标记为virtual的修饰符）。

例：

```solidity
constract father {
	modifier fn1 {...}
}
constract son is father {
	function fn2() public fn1 {...}
}
```

#### 返回值

TODO

### 事件

Solidity 事件在 EVM 的日志记录功能之上提供了一个抽象；应用程序可以通过以太坊客户端的 RPC 接口订阅和监听这些事件。

例，使用事件：

```solidity
contract c {
	event fn1(...); // 定义事件
	function fn2() public payable {
		emit fn1(...); // 触发事件
	}
}
```

### 错误处理

错误允许为故障情况定义描述性名称和数据，可用于还原语句。

例，定义错误：

```solidity
error Fail(...); // 定义错误
```

#### 断言

`assert`（断言）用于检查条件不满足时抛出异常，只能用于测试内部错误，正常运行的代码不应该造成panic。

例：

```solidity

```

#### 要求

`require`（要求）用于确保在执行之前无法检测到的有效条件。

例，require结合try catch使用：

```solidity
uint n;
C c;
function fn(address addr) returns (uint balance) {
	require(n % 2 == 0, "even value required.");
	
	try c.get(addr) return (string back) { // try catch
		...
	} catch Error(string reason) {
		n++;
		...
	} catch Panic(uint errorcode) {
		n++;
		...
	} catch(bytes memory lowLevelData) {
		n++;
		...
	} catch {
		n++;
		...
	}
}
```

#### 还原

Solidity 使用状态恢复异常来处理错误。这样的异常会撤消对当前调用（及其所有子调用）中状态所做的所有更改，并向调用者标记错误。

#### 异常

TODO

### 删除

删除`delete`用于重置变量的初始值，对映射的键无效（因为映射的键是任意的，无法设置初始值，只能**删除**单个键及其对应的值）。

例：

```solidity
uint i = 1;
uint[] arr1  = [1, 2, 3];
uint[3] arr2 = [1, 2, 3];

delete i;      // i = 0
delete arr1[]; // arr1 = []
delete arr2[]; // arr2 = [0, 0, 0] 
```

---



## 面向对象

### 结构体

结构是自定义定义的类型，可以对多个变量进行分组。

例，定义结构体：

```solidity
struct info { // 定义结构体
	uint xx;
	function fn(uint n) public payable {
		...
	}
	...
}
```

### 合约

#### 变量可见性

| 变量可见性 | 说明                                                         |
| ---------- | ------------------------------------------------------------ |
| public     | 公共状态变量；编译器会位变量自动生成`getter`函数，从而允许其它合约读取该变量的值。但是不生成`setter`函数，从而禁止其它合约直接修改变量值。 |
| internal   | 内部状态变量（默认）；只能从当前合约或派生的合约中访问，无法被外部访问。 |
| private    | 私有状态变量；类似于`internal`，但是在派生合约中不可见。     |

#### 功能可见性

| 功能可见性 | 说明                                                         |
| ---------- | ------------------------------------------------------------ |
| external   | 外部函数；可以从其它合约和交易中调用。                       |
| public     | 公共函数；可以在内部调用，也可以通过消息调用。               |
| internal   | 内部函数；只能从当前合约或派生的合约中访问，不能被外部访问。 |
| private    | 私有函数；类似于`internal`，但是在派生合约中不可见。         |

#### 构造函数

构造函数用于在创建合约时执行一些初始化动作；构造函数是可选的，并且不支持重载；如果没有构造函数，合约将假定默认的构造函数`constructor(){}`。

可以在构造函数中使用内部参数（如：存储指针），在这种情况下，必须将合约标记为`abstract`；因为这些参数不能从外部分配有效值，只能通过派生合约的构造函数分配。

例：

```solidity
abstract contract father {
	uint public a;
	constractor(uint a_) { a = a_; }
}
contract son1 is father {
	constructor(uint a_) father(a_) {}
}
contract son2 is father(2) {
	constructor(){}
}
```

#### 创建

创建合约的几种方法：

- `通过new创建合约`
- `加盐合约创建`

例，创建合约：

```solidity
contract C {
	uint public id;
	constructor(uint a) payable { id = a; }
}

C c1 = new C(1); // 通过new创建合约
C C2 = new C{value: 100}(1); // 通过new创建合约，创建时指定ether的数量100

C c3 = new C{salt: "xx..."}(1); // 创建合约时加盐
```

### 继承

Solidity 支持多重继承，包括多态性。

注意事项：

1. 覆盖父类的函数时，使用`override`关键字显式说明（0.8.8版以后可以不用显式说明）；
2. 对于需要被覆盖的函数，使用`virtual`关键字显式说明；
3. 在多重基层的情况下，必须明确指定所有直接基础合约。

例，多继承：

```solidity
contract father {
	address payable addr;
	function fn1() virtual public {...}
	modifier fn2() virtual {_;}
}
contract son is fater {
	function fn1() virtual public override {...}
	modifier fn2() virtual {_;}
}
contract grandson is father, son {
	modifier fn2() override(father, son) {_;}
}
```

例，修改器覆盖：

```solidity
contract father {
	modifier fn() virtual{_;}
}
contract son is father {
	modifier fn() override {_;}
}
```

### 抽象

当合约有至少一个功能未实现时，需要将合约标记为抽象（类似于C++的虚类）；抽象合约使用`abstract`关键字声明。

注意：

1. 抽象合约不能直接实例化；
2. 如果合约继承自抽象合约，并且没有通过股改实现所有未实现的功能，则也需要将其标记为抽象。

例：

```solidity
abstract contract v { // 抽象合约
	function fn() public virtual returns(bytes32);
}
abstract contract subv is interf{ // 继承抽象合约
}
contract impl is v { // 继承抽象合约
	function fn() public pure override returns(bytes32){...}
}
```

### 接口

接口（类似于C++的纯虚类）与抽象类相似，使用`interface`关键字声明，并且有以下限制：

1. 不能从其它合约继承，但可以从其它接口继承；
2. 所有声明的函数在接口中必须是外部的，即使它们在合约中是公共的；
3. 不能声明构造函数；
4. 不能声明状态变量；
5. 不能声明修饰符；
6. 不能实现任何功能。

例：

```solidity
interface intf {
	enum e{One, Two}
	struct Coin{string obverse; string reverse; }
	function transfer(address recipient, uint amount) external;
}
```

### 内存布局

TODO

### 库

TODO

---



## 系统API

### 块和事务属性

- `blockhash(uint blockNumber) returns (bytes32)` 当blocknumber是256个最近的块之一时，返回给定块的哈希值；否则，返回0。
- `block.basefee(uint)` 当前区块的基本费用。
- `block.chainid(uint)` 当前链id。
- `block.coinbase()` 当前区块矿工地址。
- `block.difficulty(uint)` 当前区块难度。
- `block.gaslimit(uint)` 当前区块gas限制。
- `block.number(uint)` 当前区块号。
- `block.timestamp(uint)` 当前区块时间戳，自unix纪元以来的秒数。
- `gasleft() returns(uint256)` 剩余气体。
- `msg.data()` 完整的通话数据。
- `msg.sender(address)` 消息的发送者。
- `msg.sig(bytes4)` calldata的前4个字节。
- `msg.value(uint)` 随消息发送的`wei`数量。
- `tx.gasprice(uint)` 交易的gas价格。
- `tx.origin(address)` 交易的发送者。

### ABI编码和解码函数

- `abi.decode(bytes memory encodedData, (...)) returns (...)` ABI解码给定的数据，类型在括号中作为第二个参数给出。
- `abi.encode(...) returns (bytes memory)` ABI编码给定的参数。
- `abi.encodePacked(...) returns(byte memory)` 对给定参数执行打包编码。
- `abi.encodeWithSelector(bytes selector, ...) returns(bytes memory)` ABI从第二个开始对给定的参数进行编码，并将给定的四字节选择器放在前面。
- `abi.encodeWithSignature(string memory signature, ...) return(bytes memory)` 等价于`abi.encodeWithSelector(bytes4(keccak256(bytes(signature))), ...)`
- `abi.encodeCall(function functionPointer, (...)) returns(bytes memory)functionPointer` ABI使用元组中的参数对调用进行编码；执行完整的类型检查，确保类型与函数签名匹配。

### 字节成员

- `bytes.concat(...) returns(bytes memory)` 将可变数量的字节和byte1, ..., bytes32参数连接到一个字节数组。

### 字符串成员

- `string.concat(...) returns(string memory)` 将可变数量的字符串参数连接到一个字符串数组。

### 错误处理

- `assert(bool condition)` 如果条件不满足，则会导致Panic错误并因此状态更改恢复（用于内部错误）。
- `require(bool condition)` 如果条件不满足，则恢复（用于输入或外部组件中的错误）。
- `require(bool condition, string memory message)` 如果条件不满足，则恢复（用于输入或外部组件中的错误，并提供错误信息）。
- `revert()` 中止执行并恢复状态更改。
- `revert(string memory reason)` 终止执行并恢复状态更改，提供解释性字符串。

### 数学和密码函数

- `addmod(uint x, uint y, uint k) returns(uint)` TODO。
- `mulmod(uint x, uint y, uint k) returns(uint)` TODO。
- `keccak256(bytes memory) returns(bytes32)` TODO。
- `sha256(bytes memory) returns(bytes32)` 计算SHA-256哈希。
- `ripemd160(bytes memory) returns(bytes20)` 计算RIPEMD-160哈希。
- `ecrecover(bytes32 hash, uint8 v, bytes 32 r, bytes 32 s) returns(address)` 从椭圆曲线签名中恢复与公钥关联的地址或在错误时返回0
  - `r` 签名的前32个字节；
  - `s` 第二个32字节的签名；
  - `v` 签名的最后1个字节。

### 地址类型成员

- `<address>.balance(uint256)` 地址余额。
- `<address>.code() bytes memory` 地址的代码（可空）。
- `<address>.codehash` 地址的代码哈希。
- `<address payable>.transfer(uint256 amount)` 将给定数量的wei发送到address；失败时恢复，转发2300gas津贴，不可调整。
- `<address>.send(uint256 amount) returns(bool)` 发送给定数量的wei到地址；失败返回，转发2300gas津贴，不可调整。
- `<address>.call(bytes memory) returns(bool, bytes memory)` 使用给定的有效载荷发出低级`CALL`；返回成功条件和返回数据，转发所有可用的的gas，可调整。
- `<address>.delegatecall(bytes memory) returns(bool,, bytes memory)` 使用给定的有效载荷发出低级`DELEGATECALL`，返回成功条件和返回数据，转发所有可用的gas，可调整。
- `<address>.staticcall(bytes memory) returns(bool, bytes memory)` 使用给定的有效载荷发出低级`STATICCALL`，返回成功条件和返回数据，转发所有可用的gas，可调整。

### 合约相关

- `this` 当前合约（可显式转换为地址）。
- `selfdestruct(address payable recipient)` 销毁当前合约，将其资金发送到给定地址并执行。

### 类型信息

- `type(c).name` 合同名称。
- `type(c).creationCode` 合约创建字节码。
- `type(c).runtimeCode` 合约运行时字节码。
- `type(I).interfaceId` 接口的EIP-165接口标识符的值。
- `type(T).min` 最小值。
- `type(T).max` 最大值。

---



## 参考

[1] [Solidity](https://www.osgeo.cn/solidity/index.html)

[2] [Solidity 教程](https://www.w3cschool.cn/solidity/)

[3] [Gitbook Solidity](https://solidity-cn.readthedocs.io/zh/develop/)

[4] [solidity官网](https://docs.soliditylang.org/en/latest/contracts.html#interfaces)
