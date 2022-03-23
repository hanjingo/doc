# 第三章 创建型模式

[TOC]



## 3.1 ABSTRACT FACTORY（抽象工厂）-对象创建型模式

1. 意图

   提供一个创建一系列相关或相互依赖对象的接口，而无需指定他们具体的类。

2. 别名

   Kit

3. 动机

4. 适用性

   在以下情况下可以使用Abstract Factory模式：

   - 一个系统要独立于它的产品的创建，组合和表示时。
   - 一个系统要由多个产品系列中的一个来配置时。
   - 当你要强调一系列相关的产品对象的设计以便进行联合使用时。
   - 当你提供一个产品类库，而只想显示它们的接口而不是实现时。

5. 结构

   ![3_1](res/3_1.png)

6. 参与者

   - AbstractFactory(WidgetFactory)
   
     声明一个创建抽象产品对象的操作接口。
   
   - ConcreteFactory(MotifWidgetFactory, PMWidgetFactory)
   
     实现创建具体产品对象的操作。
   
   - AbstractProduct(Windows, ScrollBar)
   
     为一类产品对象声明一个接口。
   
   - ConcreteProduct(MotifWindow, MotifScrollBar)
   
     定义一个将被相应的具体工厂创建的产品对象。
   
     实现AbstractProduct接口。
   
   - Client
   
     仅使用由AbstractFactory和AbstractProduct类声明的接口。
   
7. 协作
   
   - 通常在运行时刻创建一个ConcreteFactory类的实例。这一具体的工厂创建具有特定实现的产品对象。为创建不同的产品对象，客户应使用不同的具体工厂。
   - AbstractFactory将产品对象的创建延迟到它的ConcreateFactory子类。
   
8. 效果
   
   AbstractFactory模式有以下优缺点：
   
   - 它分离了具体的类
   - 它使得易于交换产品系列
   - 它有利于产品的一致性
   - 难以支持新种类的产品
   
9. 实现
   
   1. 将工厂作为单件。
   2. 创建产品。
   3. 定义可扩展的工厂。
   
10. 代码示例

    ```c++
    class MazeFactory {
    public:
        MazeFactory();
        
        virtual Maze* MakeMaze() const { return new Maze; }
        virtual Wall* MakeWall() const { return new Wall; }
        virtual Room* MakeRoom(int n) const { return Room(n); }
        virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }
    };
    
    Maze* MazeGame::CreateMaze(MazeFactory& factory) {
        Maze* aMaze = factory.MakeMaze();
        Room* r1 = factory.MakeRoom(1);
        Room* r2 = factory.MakeRoom(2);
        Door* aDoor = factory.MakeDoor(r1, r2);
        
        aMaze->AddRoom(r1);
        aMaze->AddRoom(r2);
        
        r1->SetSide(North, factory.MakeWall());
        r1->SetSide(East, aDoor);
        r1->SetSide(South, factory.MakeWall());
        r1->SetSide(West, factory.MakeWall());
        r1->SetSide(North, factory.MakeWall());
        r1->SetSide(East, factory.MakeWall());
        r1->SetSide(South, factory.MakeWall());
        r1->SetSide(West, factory.MakeWall());
    
        return aMaze;
    }
    
    class EnchantedMazeFactory : public MazeFactory {
    public:
        EnchantedMazeFactory();
        
        virtual Room* MakeRoom(int n) const { return new EnchantedRoom(n, CastSpell()); }
        virtual Door* MakeDoor(Room* r1, Room* r2) const { return new DoorNeedingSpell(r1, r2); }
    
    protected:
        Spell* CastSpell() const;
    };
    
    Wall* BombedMazeFactory::MakeWall() const { return new BombedWall; }
    
    Room* BombedMazeFactory::MakeRoom(int n) const { return new RoomWithABomb(n); }
    ```

11. 已知应用

12. 相关模式

    - Factory Method
    - Singleton



## 3.2 BUILDER（生成器） - 对象创建型模式

1. 意图

   将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。

2. 动机

3. 适用性

   在以下情况使用Builder模式：

   - 当创建复杂对象的算法应该独立于该对象的组成部分以及他们的装配方式时。
   - 当构造过程必须允许被构造的对象有不同的表示时。

4. 结构

   ![3_2](res/3_2.png)

5. 参与者

   - Builder(TextConverter)

     为创建一个Product对象的各个部件指定抽象接口。

   - ConcreteBuilder(ASCIIConverter, TeXConverter, TextWidgetConverter)

     实现Builder的接口以构造和装配该产品的各个部件。

     定义并明确它所创建的表示。

     提供一个检索产品的接口。

   - Director(RTFReader)

     构造一个使用Builder接口的对象。

   - Product(ASCIIText, TeXText, TextWidget)

     表示被构造的复杂对象。ConcreteBuilder创建该产品的内部表示并定义它的装配过程。

     包含定义组成部件的类，包括将这些部件装配成最终产品的接口。

6. 协作

   - 客户创建Director对象，并用它所想要的Builder进行配置。
   - 一旦产品部件被生成，导向器就会通知生成器。
   - 生成器处理导向器的请求，并将部件添加到该产品中。
   - 客户从生成器中检索产品。

   ![3_2_2](res/3_2_2.png)

7. 效果

   Builder模式的主要效果：

   - 它使你可以改变一个产品的内部表示。
   - 它将构造代码和表示代码分开。
   - 它使你可对构造过程进行更精细的控制。

8. 实现

   需要考虑的实现问题：

   - 装配和构造接口。
   - 为什么产品没有抽象类。
   - 在Builder中缺省的方法为空。

9. 代码示例

   ```c++
   class MazeBuilder {
   public:
       virtual void BuildMaze() { }
       virtual void BuildRoom(int room) { }
       virtual void BuildDoor(int roomFrom, int roomTo) { }
       
       virtual Maze* GetMaze() { return 0; }
   protected:
       MazeBuilder();
   };
   
   Maze* MazeGame::CreateMaze(MazeBuilder& builder) {
       builder.BuildMaze();
   
       builder.BuildRoom(1);
       builder.BuildRoom(2);
       builder.BuildDoor(1, 2);
       
       return builder.GetMaze();
   }
   
   Maze* MazeGame::CreateComplexMaze(MazeBuilder& builder) {
       builder.BuildRoom(1);
       builder.BuildRoom(1001);
       return builder.GetMaze();
   }
   
   class StandardMazeBuilder : public MazeBuilder {
   public:
       StandardMazeBuilder();
       
       virtual void BuildMaze();
       virtual void BuildRoom(int);
       virtual void BuildDoor(int, int);
       virtual Maze* GetMaze();
   private:
       Direction CommonWall(Room*, Room*);
       Maze* _currentMaze;
   };
   
   StandardMazeBuilder::StandardMazeBuilder() {
       _currentMaze = 0;
   }
   
   void StandardMazeBuilder::BuildMaze() {
       _currentMaze = new Maze;
   }
   
   Maze* StandardMazeBuilder::GetMaze() {
       return _currentMaze;
   }
   
   void StandardMazeBuilder::BuildRoom(int n) {
       if (!_currentMaze->RoomNo(n)) {
           Room* room = new Room(n);
           _currentMaze->AddRoom(room);
           
           room->SetSide(North, new Wall);
           room->SetSide(South, new Wall);
           room->SetSide(East, new Wall);
           room->SetSide(West, new Wall);
       }
   }
   
   void StandardMazeBuilder::BuildDoor(int n1, int n2) {
       Room* r1 = _currentMaze->RoomNo(n1);
       Room* r2 = _currentMaze->RoomNo(n2);
       Door* d = new Door(r1, r2);
       
       r1->SetSide(CommonWall(r1, r2), d);
       r2->SetSide(CommonWall(r2, r1), d);
   }
   
   class CountingMazeBuilder : public MazeBuilder {
   public:
       CountingMazeBuilder();
       
       virtual void BuildMaze();
       virtual void BuildRoom(int);
       virtual void BuildDoor(int, int);
       virtual void AddWall(int, Direction);
       
       void GetCounts(int&, int&) const;
   private:
       int _doors;
       int _rooms;
   };
   
   CountingMazeBuilder::CountingMazeBuilder() {
       _rooms = _doors = 0;
   }
   
   void CountingMazeBuilder::BuildRoom(int) {
       _doors++;
   }
   
   void CountingMazeBuilder::GetCounts(int& rooms, int& doors) {
       rooms = _rooms;
       doors = _doors;
   }
   ```
   
10. 已知应用

11. 相关模式

    - Abstract Factory
    - Composite



## 3.3 FACTORY METHOD(工厂方法) - 对象创建型模式

1. 意图

   定义一个用于创建对象的接口，TODO

​    

   