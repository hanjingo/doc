# 3 Creational Patterns



## ABSTRACT FACTORY

1. Intent

   Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

2. Also Known As

   Kit

3. Motivation

4. Applicability

   Use the Abstract Factory pattern when:

   - a system should be independent of how its products are created, composed, and represented.
   - a system should be configured with one of multiple families of products.
   - a family of related product objects is designed to be used together, and you need to enforce this constraints.
   - you want to provide a class library of products, and you want to reveal just their interfaces, not their implementations.

5. Structure

   ![3_1](res/3_1.png)

6. Participants

   - AbstractFactory

     declares an interface for operations that create abstract product objects.

   - ConcreteFactory

     implements the operations to create concrete product objects.

   - AbstractProduct

     declares an interface for a type of product objects.

   - ConcreteProduct

     defines a product object to be created by the corresponding concrete factory.

     implements the AbstractProduct interface.

   - Client

     uses only interfaces declared by AbstractFactory and AbstractProduct classes.

7. Collaborations

   - Normally a single instance of a ConcreteFactory class is created at run-time. This concrete factory creates product objects having a particular implementation. To create differnt product objects, clients should use a different concrete factory.
   - AbstractFactory defers creation of product objects to its ConcreteFactory subclass.

8. Consequences

   The Abstract Factory pattern has the following benefits and liabilities:

   - It isolates concrete classes.
   - It makes exchanging product families easy.
   - It promotes consistency among products.
   - Supporting new kinds of products is difficult.

9. Implementation

   Here are some useful techniques for implementing the Abstract Factory pattern:

   1. Factories as singletons.
   2. Creating the products.
   3. Defining extensible factories.

10. Sample Code

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

11. Known Uses

12. Related Patterns

    - Factory Method
    - Singleton

---



## BUILDER

1. Intent

   Separate the construction of a complex object from its representation so that the same construction process can create different representations.

2. Motivation

3. Applicability

   Use the Builder pattern when:

   - the algorithm for creating a complex object should be independent of the parts that make up the object and how they're assembled.
   - the construction process must allow different representations for the object that's constructed.

4. Structure

   ![3_2](res/3_2.png)

5. Participants

   - Builder

     specifies an abstract interface for creating parts of a Product object.

   - ConcreteBuilder

     constructs and assembles parts of the product by implementing the Builder interface.

     define and keeps track of the representation it creates.

     provides an interface for retrieving the product.

   - Director

     constructs an object using the Builder interface.

     defines and keeps track of the representation it creates.

     provides an interface for retrieving the product.

   - Director

     constructs an object using the Builder interface.

   - Product

     represents the complex object under construction. ConcreteBuilder builds the product's internal representation and defines the process by which it's assembled.

     includes classes that define the constituent parts, including interfaces for assembling the parts into the final result.

6. Collaborations

   - The client creates the Director object and configures it with the desired Builder object.
   - Director notifies the builder whenever a part of the product should be built.
   - Builder handles requests from the director and adds parts to the product.
   - The client retrieves the product from the builder.

   The following interaction diagram illustrates how Builder and Director cooperate with a client:

   ![3_2_2](res/3_2_2.png)

7. Consequences

   Here are key consequences of the Builder pattern:

   1. It lets you vary a product's internal representation.
   2. It isolates code for construction and representation.
   3. It gives you finer control over the construction process.

8. Implementation

   Here are other implementation issues to consider:

   - Assembly and construction interface.
   - Why no abstract class for products.
   - Empty methods as default in Builder.

9. Sample Code

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

10. Known Uses

11. Related Patterns

    - Abstract Factory
    - Composite

---



## FACTORY METHOD

1. Intent

   Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

2. Also Known As

   Virtual Constructor

3. Motivation

4. Applicability

   Use the Factory Method pattern when:

   - a class can't anticipate the class of objects it must create.
   - a class wants its subclasses to specify the objects it creates.
   - classes delegate responsibility to one of several helper subclasses, and you want to localize the knowledge of which helper subclass is the delegate.

5. Structure

   ![3_3](res/3_3.png)

6. Participants

   - Product

     defines the interface of objects the factory method creates.

   - ConcreteProduct

     implements the Product interface.

   - Creator

     declares the factory method, which returns an object of type Product. Creator may also define a default implementation of the factory method that returns a default ConcreteProduct object.

     may call the factory method to create a Product object.

   - ConcreteCreator

     overrides the factory method to return an instance of a ConcreteProduct.

7. Collaborations

   Creator relies on its subclasses to define the factory method so that it returns an instance of the appropriate ConcreteProduct.

8. Consequences

   Here are two additional consequences of the Factory Method pattern:

   1. Provides hooks for subclasses.
   2. Connects parallel class hierarchies.

9. Implementation

   Consider the following issues when applying the Factory Method pattern:

   1. Two major varieties.
   2. Parameterized factory methods.
   3. Language-specific variants and issues.
   4. Using templates to avoid subclassing.
   5. Naming conventions.

10. Sample Code

    ```c++
    class MazeGame {
    public:
      Maze* CreateMaze();
      
      virtual Maze* MakeMaze() const { return new Maze; }
      virtual Room* MakeRoom(int n) const { return new Room(n); }
      virtual Wall* MakeWall() const { return new Wall; }
      virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2); }
    };
    
    Maze* MazeGame::CreateMaze() {
      Maze* aMaze = MakeMaze();
      
      Room* r1 = MakeRoom(1);
      Room* r2 = MakeRoom(2);
      
      Door* theDoor = MakeDoor(r1, r2);
      
      aMaze->AddRoom(r1);
      aMaze->AddRoom(r2);
      
      r1->SetSide(North, MakeWall());
      r1->SetSide(East, theDoor);
      r1->SetSide(South, MakeWall());
      r1->SetSide(West, MakeWall());
      
      r1->SetSide(North, MakeWall());
      r1->SetSide(East, MakeWall());
      r1->SetSide(South, MakeWall());
      r1->SetSide(West, theDoor);
      return aMaze;
    }
    
    class BombedMazeGame : public MazeGame {
    public:
      BombedMazeGame();
      
      virtual Wall* MakeWall() const { return new BombedWall; }
      
      virtual Room* MakeRoom(int n) const { return new RoomWithABomb(n); }
    };
    
    class EnchantedMazeGame : public MazeGame {
    public:
      EnchantedMazeGame();
      
      virtual Room* MakeRoom(int n) const { return new EnchantedRoom(n, CastSpell()); }
      
      virtual Door* MakeDoor(Room* r1, Room* r2) const { return new DoorNeedingSpell(r1, r2); }
    protected:
      Spell* CastSpell() const;
    }
    ```

11. Known Uses

12. Related Patterns

    Abstract Factory

    Template Methods

    Prototypes

---



## PROTOTYPE

1. Intent

   Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

2. Motivation

3. Applicability

   Use the Prototype pattern when a system should be independent of how its products are created, composed, and represented; and 

   - when the classes to instantiate are specified at run-time, for example, by dynamic loading; or
   - to avoid building a class hierarchy of factories that parallels the class hierarchy of products; or
   - when instances of a class can have one of only a few different combinations of state. It may be more convenient to install a corresponding number of prototype and clone them rather than instantiating the class manually, each time with the appropriate state.

4. Structure

   ![3_4](res/3_4.png)

5. Participants

   - Prototype

     declares an interface for cloning itself.

   - ConcretePrototype

     implements an operation for cloning itself.

   - Client

     creates a new object by asking a prototype to clone itself.

6. Collaborations

   A client asks a prototype to clone itself.

7. Consequences

   Additional benefits of the Prototype pattern are listed below:

   1. Adding and removing products at run-time.
   2. Spedifying new objects by varying values.
   3. Specifying new objects by varying structure.
   4. Reduced subclassing.
   5. Configuring an application with classes dynamically.

8. Implementation

   Consider the following issues when implementing prototypes:

   1. Using a prototype manager.
   2. Implementing the Clone operation.
   3. Initializing clones.

9. Sample Code

   ```c++
   class MazePrototypeFactory : public MazeFactory {
   public:
     MazePrototypeFactory(Maze*, Wall*, Room*, Door*);
     
     virtual Maze* MakeMaze() const;
     virtual Room* MakeRoom(int) const;
     virtual Wall* MakeWall() const;
     virtual Door* MakeDoor(Room*, Room*) const;
     
   private:
     Maze* _prototypeMaze;
     Room* _prototypeRoom;
     Wall* _prototypeWall;
     Door* _prototypeDoor;
   };
   
   MazePrototypeFactory::MazePrototypeFactory(
     Maze* m, Wall* w, Room* r, Door* d) {
     _prototypeMaze = m;
     _prototypeWall = w;
     _prototypeRoom = r;
     _prototypeDoor = d;
   }
   
   Wall* MazePrototypeFactory::MakeWall() const {
     return _prototypeWall->Clone();
   }
   
   Door* MazePrototypeFactory::MakeDoor(Room* r1, Room* r2) const {
     Door* door = _prototypeDoor->Clone();
     door->Initialize(r1, r2);
     return door;
   }
   
   MazeGame game;
   MazePrototypeFactory simpleMazeFactory(new Maze, new Wall, new Room, new Door);
   Maze* maze = game.CreateMaze(simpleMazeFactory);
   
   MazePrototypeFactory bombedMazeFactory(
     new Maze, new BombedWall, new RoomWithABomb, new Door);
   
   class Door : public MapSite {
   public:
     Door();
     Door(const Door&);
     
     virtual void Initialize(Room*, Room*);
     virtual Door* Clone() const;
     virtual void Enter();
     Room* OtherSideFrom(Room*);
   private:
     Room* _room1;
     Room* _room2;
   };
   
   Door::Door(const Door& other) {
     _room1 = other._room1;
     _room2 = other._room2;
   }
   
   void Door::Initialize(Room* r1, Room* r2) {
     _room1 = r1;
     _room2 = r2;
   }
   
   Door* Door::Clone() const {
     return new Door(*this);
   }
   
   class BombedWall : public Wall {
   public:
     BombedWall();
     BombedWall(const BombedWall&);
     
     virtual Wall* Clone() const;
     bool HasBomb();
   private:
     bool _bomb;
   };
   
   BombeWall::BombedWall(const BombedWall& other) : Wall(other) {
     _bomb = other._bomb;
   }
   
   Wall* BombedWall::Clone() const {
     return new BombedWall(*this);
   }
   ```

10. Known Uses

11. Related Patterns

    Abstract Factory

    Composite

    Decorator

---



## SINGLETON

1. Intent

   Ensure a class only has one instance, and provide a global point of access to it.

2. Motivation

3. Applicability

   Use the Singleton pattern when:

   - there must be exactly one instance of a class, and it must be accessible to clients from a well-known access point.
   - when the sole instance should be extensible by subclassing, and clients should be able to use an extended instance without modifying their code.

4. Structure

   ![3_5](res/3_5.png)

5. Participants

   - Singleton

     defines an Instance operation that lets clients access its unique instance. Instance is a class operation.

     may be responsible for creating its own unique instance.

6. Collaborations

   Clients access a Singleton instance solely through Singleton's Instance operation.

7. Consequences

   The Singleton pattern has several benefits:

   1. Controlled access to solo instance.
   2. Reduced name space.
   3. Permits refinement of operations and representation.
   4. Permits a variable number of instance.
   5. More flexible than class operations.

8. Implementation

   Here are implementation issue to consider when using the Singleton pattern:

   1. Ensuring a unique instance.
   2. Subclassing the Singleton class.

9. Sample Code

   ```c++
   class MazeFactory {
   public:
       static MazeFactory* Instance();
       
   protected:
       MazeFactory();
       
   private:
       static MazeFactory* _instance;
   };
   
   MazeFactory* MazeFactory::_instance = 0;
   
   MazeFactory* MazeFactory::Instance() {
       if (_instance == 0) {
           const char* mazeStyle = getenv("MAZESTYLE");
           
           if (strcmp(mazeStyle, "bombed") == 0) {
               _instance = new EnchantedMazeFactory;
               
               // ...
           } else {
           	_instance = new MazeFactory;
           }
       }
       return _instance;
   }
   ```

10. Known Uses

11. Related Patterns

    Abstract Factory

    Builder

    Prototype

---



## Discussion of Creational Patterns

