# 第7章 设计与实现



## 7.1 利用UML进行面向对象设计

开发系统设计，由概念设计转变为详细的面向对象的设计，需要完成如下几点：

1. 了解并定义上下文和系统的外部交互。
2. 设计系统体系结构。
3. 识别出系统中的主要对象。
4. 开发设计模型。
5. 定义对象接口。

### 7.1.1 系统上下文与交互

系统上下文模型和交互模型可以互为补充，呈现出系统和环境之间的关系：

1. 系统上下文模型是一个结构模型，描述开发中的系统所处环境中的其它系统。
2. 交互模型是一个动态模型，表明系统在运行中是如何与环境交互的。

### 7.1.2 体系结构的设计

### 7.1.3 对象类识别

### 7.1.4 设计模型

用UML进行设计通常需要如下两类设计模型：

1. 结构模型，通过系统对象类及其之间的关系来描述系统的静态结构。
2. 动态模型，描述系统的动态结构和系统对象之间的交互。

在设计过程的早期阶段，有3个模型特别有助于为用例和体系结构模型增加细节：

1. 子系统模型，给出对象的逻辑分组即子系统，子系统之间存在着有机联系。这些模型用类图的形式来表示，每个子系统作为一个包，里面封装了一些对象。子系统模型是静态（结构）模型。
2. 时序模型说明对象交互的序列。使用UML时序图或协作图来表示。时序模型是动态模型。
3. 状态机模型说明单个对象如何响应事件来改变它们的状态。它们使用UML的状态图来表示。状态机模型是动态模型。

### 7.1.5 接口描述



## 7.2 设计模式



## 7.3 实现问题

### 7.3.1 复用

软件复用可以运用在不同层次上：

1. 抽象层
2. 对象层
3. 组件层
4. 系统层

软件复用也有相应的花费：

1. 寻找可复用的软件并评估其是否复合需求的时间花费。
2. 找到合适的可复用软件后，还要有购买此软件的花费。
3. 调整和配置可复用软件组件或系统使其满足待开发系统需求的花费。
4. 集成各个可复用软件（如果使用的是不同来源的软件）及新代码的花费。

### 7.3.2 配置管理

配置管理包含如下3个基本活动：

1. 版本管理
2. 系统集成
3. 问题追踪

### 7.3.3 宿主机-目标机开发

对于分布式系统来说，我们需要决定组件部署到何种特定平台上。做决定时需要考虑到的问题有：

1. 组件的软硬件需求
2. 系统可用性需求
3. 组件通信



## 7.4 开源开发

多数开源许可都衍生自下述3种通用模型：

1. GNU通用公共许可（GPL）：如果我们用GPL许可证的开源软件，那么我们必须也将自己的软件开源。
2. GNU宽松的通用公共许可（LGPL）：这是GPL许可的变体，我们可以编写链接到开源代码的组件，而无需公布自己的组件源码。但是如果我们更改了这些许可下的组件，那么就需要开源。
3. Berkley标准分布（BSD）许可：这是一个非互惠许可，我们不会被强制要求公开对开源代码的任何改动。我们可以在用于商业用途的系统中使用这些代码。如果我们使用的是开源组件，那么我们必须知道代码的原作者。



## 总结

TODO

