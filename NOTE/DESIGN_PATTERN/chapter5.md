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

   ![5_8_1](res/5_8_1.png)
   
6. 参与者

   - `Context` 环境
   - `State` 状态
   - `ConcreteState subclasses` 具体状态子类

7. 协作

   - Context 将与状态相关的请求委托给当前的ConcreteState对象处理。
   - Context可将自身作为一个参数传递给处理该请求的状态对象；这使得状态对象在必要时可访问Context。
   - Context是客户使用的主要接口。客户可用状态对象来配置一个Context，一旦一个Context配置完毕，它的客户不再需要直接与状态对象打交道。
   - Context或ConcreteState子类都可以决定哪个状态是另外哪一个的后继者，以及是在何种条件下进行状态转换。
   
8. 效果

   State模式有以下效果：

   1. 它将与特定状态相关的行为局部化，并且将不同状态的行为分割开来。

      State模式将所有与一个特定的状态的状态相关的行为都放入一个对象中，决定状态转移的逻辑**不在**单块的if或switch语句中，而是分布在State子类之间。将每个状态转换和动作封装到一个类中，就把着眼点从执行状态提高到整个对象的状态，这将使代码结构化并使其意图更加清晰。

   2. 它使得状态转换显式化。

   3. State对象可被共享。

9. 实现

   实现State模式要考虑以下方面：

   1. 谁定义状态转换。

   2. 基于表的另一种方法；

      使用表将输入映射到状态转换，对于每一个状态，一张表将每一个可能的输入映射到一个后继状态。

   3. 创建和销毁State对象。

   4. 使用动态继承。

10. 代码示例

   ```cpp
   class TCPOctetStream;
   class TCPState;
   
   class TCPConnection {
   public:
       TCPConnection();
       
       void ActiveOpen();
       void PassiveOpen();
       void Close();
       void Send();
       void Acknowledge();
       void Synchronize();
       
       void ProcessOctet(TCPOctetStream*);
   private:
       friend class TCPState;
       void ChangeState(TCPState*);
   private:
       TCPState* _state;
   };
   
   TCPConnection::TCPConnection() {
       _state = TCPClosed::Instance();
   }
   void TCPConnection::ChangeState(TCPState* s) {
       _state = s;
   }
   void TCPConnection::ActiveOpen() {
       _state->ActiveOpen(this);
   }
   void TCPConnection::PassiveOpen() {
       _state->PassiveOPen(this);
   }
   void TCPConnection::Close() {
       _state->Close(this);
   }
   void TCPConnection::Acknowledge() {
       _state->ActiveOpen(this);
   }
   void TCPConnection::Synchronize() {
       _state->Synchronize(this);
   }
   
   class TCPState {
   public:
       virtual void Transmit(TCPConnection*, TCPOctetStream*);
       virtual void ActiveOpen(TCPConnection*);
       virtual void PassiveOpen(TCPConnection*);
       virtual void Close(TCPConnection*);
       virtual void Synchronize(TCPConnection*);
       virtual void Acknowledge(TCPConnection*);
       virtual void Send(TCPConnection*);
   protected:
       void ChangeState(TCPConnection*, TCPState*);
   };
   
   class TCPEstablished : public TCPState {
   public:
       static TCPState* Instance();
       virtual void Transmit(TCPConnection*, TCPOctetStream*);
       virtual void Close(TCPConnection*);
   };
   
   class TCPListen : public TCPState {
   public:
       static TCPState* Instance();
       virtual void Send(TCPConnection*);
       // ...
   };
   
   class TCPClosed : public TCPState {
   public:
       static TCPState* Instance();
       
       virtual void ActiveOpen(TCPConnection*);
       virtual void PassiveOpen(TCPConnection*);
       // ...
   };
   
   void TCPClosed::ActiveOpen(TCPConnection* t) {
       ChangeState(t, TCPEstablished::Instance());
   }
   
   void TCPClosed::PassiveOpen(TCPConnection* t) {
       ChangeState(t, TCPListten::Instance());
   }
   
   void TCPEstablished::Close(TCPConnection* t) {
       ChangeState(t, TCPListen::Instance());
   }
   
   void TCPEstablished::Transmit(TCPConnection* t, TCPOctetStream* o) {
       t->ProcessOctet(o);
   }
   
   void TCPListen::Send(TCPConnection* t) {
       ChangeState(t, TCPEstablished::Instance());
   }
   ```

11. 已知应用

12. 相关模式

    Singleton。