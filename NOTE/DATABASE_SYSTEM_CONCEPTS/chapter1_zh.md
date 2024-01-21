# 第1章 引言

[TOC]



系统开发人员通过如下层次上的抽象来对用户屏蔽复杂性，以简化用户与系统的交互：

- 物理层
- 逻辑层
- 视图层

特定时刻存储在数据库中的信息的集合称作数据库的一个实例（instance）。而数据库的总体设计称为数据库模式（schema）。

数据库系统可以分为几种不同的模式：

- 物理模式
- 逻辑模式
- 子模式

应用程序如果不依赖于五一模式，他们就称为是具有物理数据独立性（physical data independence），因此即使物理模式改变了他们也无须重写。

数据模型是一个描述数据，数据联系，数据语义以及一致性约束的概念工具的集合，可以划分为以下几类：

- 关系模型（relational model）
- 实体-联系模型（entity-relationship model）
- 基于对象的数据模型（object-based data model）
- 半结构化数据模型（semistructured data model）

数据操纵语言（Data-Manipulation Language, DML）使得用户可以访问或操纵那些按照某种适合的数据模型组织起来的数据；有以下访问类型：

- 对存储在数据库中的信息进行检索
- 向数据库中插入新的信息
- 从数据库中删除信息
- 修改数据库存储的信息

通常有两类基本的数据操纵语言：

- 过程化DML（procedural DML）：要求用户指定需要什么数据以及如何获得这些数据。
- 声明式DML（declarative DML）：（也称为非过程化DML）只要求用户指定需要什么数据，而不指明如何获得这些数据。

查询（query）是要求对信息进行检索的语句。DML中涉及信息检索的部分称作查询语言（query language）。

存储在数据库中的数据值必须满足某些一致性约束（consistency constraint）。数据库系统实现可以以最小代价测试的完整性约束：

- 域约束（domain constraint）
- 参照完整性（referential integrity）
- 断言（assertion）
- 授权（authorization）

数据库中实体通过属性（attribute）集合来描述。

联系（relationship）是几个实体之间的关联。

存储管理器是数据库系统中负责在数据库中存储的底层数据与应用程序以及向系统提交的查询之间提供接口的部件。存储管理器负责数据库中数据的存储，检索和更新。存储管理部件包括：

- 权限及完整性管理器（authorization and integrity manager）
- 事务管理器（transaction manager）
- 文件管理器（file manager）
- 缓冲区管理器（buffer manager）

存储管理器实现了几种数据结构，作为系统物理实现的一部分：

- 数据文件（data files）
- 数据字典（data dictionary）
- 索引（index）

查询处理器组件包括：

- DDL解释器（DDL interpreter）
- DML编译器（DML compiler）
- 查询执行引擎（query evaluation engine）

事务（transaction）是数据库应用中完成单一逻辑功能的操作集合。具有以下特性：

- 原子性（atomicity）
- 一致性（consistency）
- 持久性（durability）

数据挖掘（data mining）这个术语指半自动地分析大型数据库并从中找出有用的模式的过程。

对系统进行集中控制的人称作数据库管理员（DataBase Administratr, DBA）。DBA的作用包括：

- 模式定义（schema definiation）
- 存储结构及存取方法定义（storage structure and access-method definition）
- 模式及物理组织的修改（schema and physical-organization modification）
- 数据访问授权（granting of authorization for data access）
- 日常维护（routine maintenance）



