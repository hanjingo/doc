# 第五章 行为模式

[TOC]



## 5.8 STATE（状态） - 对象行为型模式

1.  意图

   允许一个对象在其内部状态改变时改变它的行为。对象看起来似乎修改了它的类。

2. 别名

   状态对象（Objects for States）

3. 动机

4. 适用性

   下面两种情况可使用State模式：

   - 一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为；
   - 一个操作中含有庞大的多分支的条件语句，且这些分支依赖于该对象的状态；这个状态通常用一个或多个枚举常量表示。

5. 结构

   ```mermaid
   classDiagram
   	class Context{
   		Request()
   	}
   	class State{
   		Handle()
   	}
   
   	State <|--o Context
   ```
   
6. 参与者

   - `Context`
   - `State`
   - `ConcreteState subclasses`

7. 协作

   - Context 将与状态相关的请求委托给当前的ConcreteState对象处理；
   - Context可将自身作为一个参数传递给处理该请求的状态对象；这使得状态对象在必要时可访问Context；
   - 