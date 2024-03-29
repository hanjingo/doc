# 5 Behavioral Patterns

[TOC]



## CHAIN OF RESPONSIBILITY

1. Intent

   Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the chain until an object handles it.

2. Motivation

3. Applicability

   Use Chain of Responsibility when:

   - more than one object may handle a request, and the handler isn't known a priori. The handler should be ascertainedautomatically.
   - you want to issue a request to one ofseveral objectswithout specifyingthe receiver explicitly.
   - the set of objects that can handle a request should be specified dynamically.

4. Structure

   ![5_1](res/5_1.png)

5. Participants

   - Handler

     defines an interface for handling requests.

     (optional)implements the successor link.

   - ConcreteHandler

     handles requests it isresponsible for.

     can access its successor.

     if the ConcreteHandler can handle the request, it does so; otherwise it forwards the request to its successor.

   - Client

     initiates the request to a ConcreteHandler object on the chain.

6. Collaborations

   When a client issues a request, the request propagates along the chain until a ConcreteHandler object takes responsibility for handling it.

7. Consequences

   Chain of Responsibility has the following benefits and liabilities:

   - Reduced coupling.
   - Added flexibility in assigning responsibilities to objects.
   - Receipt isn't guaranteed.

8. Implementation

9. Sample Code

   ```c++
   typedef int Topic;
   const Topic NO_HELP_TOPIC = -1;
   
   class HelpHandler {
   public:
       HelpHandler(HelpHandler* = 0, Topic = NO_HELP_TOPIC);
       virtual bool HashHelp();
       virtual void SetHandler(HelpHandler*, Topic);
       virtual void HandleHelp();
       
   private:
       HelpHandler* _successor;
       Topic _topic;
   };
   
   HelpHandler::HelpHandler(HelpHandler* h, Topic t) : _successor(h), _topic(t) {}
   
   bool HelpHandler::HasHelp() {
       return _topic != NO_HELP_TOPIC;
   }
   void HelpHandler::HandleHelp() {
       if (_successor != 0) {
           _successor->HandleHelp();
       }
   }
   
   class Widget : public HelpHandler {
   protected:
       Widget(Widget* parent, Topic t = NO_HELP_TOPIC);
       
   private:
       Widget* _parent;
   };
   
   Widget::Widget(Widget* w, Topic t) : HelpHandler(w, t) {
       _parent = w;
   }
   
   class Button : public Widget {
   public:
       Button(Widget* d, Topic t = NO_HELP_TOPIC);
       
       virtual void HandleHelp();
       // Widget operations that Button overrides...
   };
   Button::Button(Widget* h, Topic t) : Widget(h, t) {}
   void Button::HandleHelp() {
       if (HasHelp()) {
           // offer help on the button
       } else {
           HelpHandler::HandleHelp();
       }
   }
   
   class Dialog : public Widget {
   public:
       Dialog(HelpHandler* h, Topic t = NO_HELP_TOPIC);
       virtual void HandleHelp();
       
       // Widget operations that Dialog overrides...
       // ...
   };
   
   Dialog::Dialog(HelpHandler* h, Topic t) : Widget(0) {
       SetHandler(h, t);
   }
   
   void Dialog::HandleHelp() {
       if (HasHelp()) {
           // offer help on the button
       } else {
           HelpHandler::HandleHelp();
       }
   }
   
   class Dialog : public Widget {
   public:
       Dialog(HelpHandler* h, Topic t = NO_HELP_TOPIC);
       virtual void HandleHelp();
       
       // Widget operations that Dialog overrides...
       // ...
   };
   
   Dialog::Dialog(HelpHandler* h, Topic t) : Widget(0) {
       SetHandler(h, t);
   }
   
   void Dialog::HandleHelp() {
       if (HasHelp()) {
           // offer help on the dialog
       } else {
           HelpHandler::HandleHelp();
       }
   }
   
   class Application : public HelpHandler {
   public:
       Application(Topic t) : HelpHandler(0, t) {}
       
       virtual void HandleHelp();
       // application-specific operations...
   };
   
   void Application::HandleHelp() {
       // show a list of help topics
   }
   
   const Topic PRINT_TOPIC = 1;
   const Topic PAPER_ORIENTATION_TOPIC = 2;
   const Topic APPLICATION_TOPIC = 3;
   
   Application* application = new Application(APPLICATION_TOPIC);
   Dialog* dialog = new Dialog(application, PRINT_TOPIC);
   Button* button = new Button(dialog, PAPER_ORIENTATION_TOPIC);
   button->HandleHelp();
   ```

10. Known Uses

11. Related Patterns

    Chain of Responsibility is often applied in conjunction with Composite. There, a component's parent can act as its successor.

---



## COMMAND

1. Intent

   Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations.

2. Also Known As

   Action, Transaction

3. Motivation

4. Applicability

   - parameterize objects by an actiontoperform, asMenultem objects did above.
   - specify, queue, and execute requests at different times.
   - support undo.
   - support logging changes so that they can be reapplied in case of a system crash.
   - structure a system around high-level operations built on primitives operations.

5. Structure

   ![5_2](res/5_2.png)

6. Participants

   - Command

     declares an interface for executing an operation

   - ConcreteCommand

     defines a binding between a Receiver object and an action.

     implements Execute by invoking the corresponding operation(s) on Receiver.

   - Client

     creates a ConcreteCommand object and sets its receiver

   - Invoker

     asks the command to carry out the request.

   - Receiver

     knows how to perform the operations associated with carrying out a request. Any class may serve as a Receiver.

7. Collaborations

   - The client creates a ConcreteCommand object and specifies itsreceiver.
   - An Invoker object stores the ConcreteCommand object.
   - The invoker issues a request by calling Execute on the command. When commands are undoable, ConcreteCommand stores state for undoing the command prior to invoking Execute.
   - The ConcreteCommand object invokes operations on its receiver to carry out the request.

8. Consequences

   The Command pattern has the following consequences:

   - Command decouples the object that invokesthe operation from the one that knows how to perform it.
   - Commands are first-class objects. They can be manipulated and extended like any other object.
   - Youcan assemble commands into a composite command. An example is the MacroCommand class described earlier. In general, composite commands are an instance of the Composite pattern.
   - It's easy to add new Commands, because you don't have to change existing classes.

9. Implementation

10. Sample Code

    ```c++
    class Comkmand {
    public:
        virtual ~Command();
        virtual void Execute() = 0;
        
    protected:
        Command();
    };
    
    class OpenCommand : public Command {
    public:
        OpenCommand(Application*);
        virtual void Execute();
        
    protected:
        virtual const char* AskUser();
        
    private:
        Application* _application;
        char* _response;
    }
    
    OpenCommand::OpenCommand(Application* a) {
        _application = a;
    }
    void OpenCommand::Execute() {
        const char* name = AskUser();
        
        if (name != 0) {
            Document* document = new Document(name);
            _application->Add(document);
            document->Open();
        }
    }
    
    class PasteCommand : public Command {
    public:
        PasteComkmand(Document*);
        virtual void Execute();
        
    private:
        Document* _document;
    };
    PasteCommand::PasteCommand(Document* doc) {
        _document = doc;
    }
    void PasteCommand::Execute() {
        _document->Paste();
    }
    
    template <class Receiver>
    class SimpleCommand : public Command {
    public:
        typedef void (Receiver::* Action)();
        SimpleCommand(Receiver* r, Action a) : _receiver(r), _action(a) {}
        virtual void Execute();
        
    private:
        Action _action;
        Receiver* _receiver;
    };
    template <class Receiver>
    void SimpleCommand<Receiver>::Execute() {
        (_receiver->*_action)();
    }
    
    class MacroCommand : public Command {
    public:
        MacroCommand();
        virtual ~MacroCommand();
        virtual void Add(Command*);
        virtual void Remove(Command*);
        virtual void Execute();
        
    private:
        List<Command*>* _cmds;
    };
    void MacroCommand::Execute() {
        ListIterator<Command*> i(_cmds);
        
        for (i.First(); !i.IsDone(); i.Next()) {
            Command* c = i.CurrentItem();
            c->Execute();
        }
    }
    void MacroCommand::Add(Command* c) {
        _cmds->Append(c);
    }
    void MacroCommand::Remove(Command* c) {
        _cmds->Remove(c);
    }
    
    MyClass* receiver = new MyClass;
    // ...
    Command* pCommand = new SimpleCommand<MyClass>(receiver, &MyClass::Action);
    // ...
    aCommand->Execute();
    ```

11. Known Uses

12. Related Patterns

    A Composite can be used to implement MacroCommands. 

    A Memento can keep state the command requires to undo its effect. 

    A command that must be copied before being placed on the history list acts as a Prototype.

---



## INTERPRETER

1. Intent

   Given a language, define a represention forits grammar along with an interpreter that uses the representation to interpret sentences in the language.

2. Motivation

   If a particular kind of problem occurs often enough, then it might be worthwhile to express instances of the problem as sentences in a simple language. Then you can build an interpreter that solves the problem by interpreting these sentences.

3. Applicability

   - the grammar is simple.
   - efficiency is not a critical concern.

4. Structure

   ![5_3](res/5_3.png)

5. Participants

   - AbstractExpression

     declares an abstractInterpret operation that is common to allnodes in the abstract syntax tree

   - TerminalExpression

     implements anInterpret operation associated with terminal symbolsin the grammar.

     an instance isrequired for every terminal symbol in a sentence.

   - NoterminalExpression 

     one such classisrequired for every rule $R ::= R_1 R_2 ... R_n$ in the grammar.

     maintains instance variables of type AbstractExpression for each of the symbols $R_1$ through $R_n$.

     implements an Interpret operation for nonterminal symbols in the grammar.Interpret typically callsitself recursively on the variables representing $R_1$ through $R_n$.

   - Context

     containsinformation that's global totheinterpreter.

   - Client

     builds (oris given) an abstract syntax tree representing a particular sentence in the language that the grammar defines. The abstract syntax tree is assembled from instances of the NonterminalExpression and TerminalExpression classes.

     invokes the Interpret operation.

6. Collaborations

   - The client builds (oris given) the sentence as an abstract syntax tree ofNonterminalExpression and TerminalExpression instances. Then the client initializes the context and invokes the Interpret operation.
   - Each NonterminalExpression node defines Interpret in terms of Interpret on each subexpression. The Interpret operation of each TerminalExpression defines the base case in the recursion.
   - The Interpret operations at each node use the context to store and access the state of the interpreter.

7. Consequences

   The Interpreter pattern has the following benefits and liabilities:

   - It's easy to change and extend the grammar.
   - Implementing the grammar is easy, too.
   - Complex grammars arehard to maintain.
   - Adding new ways to interpret expressions.

8. Implementation

9. Sample Code

   ```c++
   class BooleanExp {
   public:
       BooleanExp();
       virtual ~BooleanExp();
       virtual bool Evaluate(Context&) = 0;
       virtual BooleanExp* Replace(const char*, BooleanExp&) = 0;
       virtual BooleanExp* Copy() const = 0;
   };
   
   class Context {
   public:
       bool Lookup(const char*) const;
       void Assign(VariableExp*, bool);
   };
   
   class VariableExp : public BooleanExp {
   public:
       VariableExp(const char*);
       virtual ~VariableExp();
       virtual bool Evaluate(Context&);
       virtual BooleanExp* Replace(const char*, BooleanExp&);
       virtual BooleanExp* Copy() const;
       
   private:
       char* _name;
   };
   VariableExp::VariableExp(const char* name) {
       _name = strdup(name);
   }
   bool VariableExp::Evaluate(Context& aContext) {
       return aContext.Lookup(_name);
   }
   BooleanExp* VariableExp::Copy() const {
       return new VariableExp(_name);
   }
   BooleanExp* VariableExp::Replace(const char* name, BooleanExp& exp) {
       if (strcmp(name, _name) == 0) {
           return exp.Copy();
       } else {
           return new VariableExp(_name);
       }
   }
   
   class AndExp : public BooleanExp {
   public:
       AndExp(BooleanExp*, BooleanExp*);
       virtual ~AndExp();
       virtual bool Evaluate(Context&);
       virtual BooleanExp* Replace(const char*, BooleanExp&);
       virtual BooleanExp* Copy() const;
       
   private:
       BooleanExp* _operand1;
       BooleanExp* _operand2;
   };
   AndExp::AndExp(BooleanExp* op1, BooleanExp* op2) {
       _operand1 = op1;
       _operand2 = op2;
   }
   bool AndExp::Evaluate(Context& aContext) {
       return _operand1->Evaluate(aContext) &&
                _operand2->Evaluate(aContext);
   }
   BooleanExp* AndExp::Copy() const {
       return new AndExp(_operand1->Copy(), _operand2->Copy());
   }
   BooleanExp* AndExp::Replace(const char* name, BooleanExp& exp) {
       return new AndExp(_operand1->Replace(name, exp), 
                         _operand2->Replace(name, exp));
   }
   
   BooleanExp* expression;
   Context context;
   
   VariableExp* x = new VariableExp("X");
   VariableExp* y = new VariableExp("Y");
   
   expression = new OrExp(
   	new AndExp(new Constant(true), x),
       new AndExp(y, new NotExp(x))
   );
   
   context.Assign(x, false);
   context.Assign(y, true);
   
   bool result = expression->Evaluate(context);
   
   VariableExp* z = new VariableExp("Z");
   NotExp not_z(z);
   
   BooleanExp* replacement = expression->Replace("Y", not_z);
   
   context.Assign(z, true);
   
   result = replacement->Evaluate(context);
   ```

10. Known Uses

11. Related Patterns

    Composite: The abstract syntax tree is an instance of the Composite pattern. 

    Flyweight: shows how to share terminal symbols within the abstractsyntax tree. 

    Iterator: The interpreter can use an Iterator to traverse the structure. 

    Visitor: can be used to maintain the behavior in each node in the abstract syntax tree in one class.

---



## ITERATOR

1. Intent

   Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

2. Motivation

3. Applicability

   Use the Iterator pattern:

   - to access an aggregate object's contents without exposing its internal representation.
   - to support multiple traversals of aggregateobjects.
   - to provide a uniform interface for traversing different aggregate structures (that is, to support polymorphic iteration).

4. Structure

   ![5_4](res/5_4.png)

5. Participants

   - Iterator

     defines an interface for accessing and traversing elements.

   - ConcreteIterator

     1. implements theIterator interface.
     2. keeps track ofthe current position in the traversal ofthe aggregate.

   - Aggregate

     defines an interface for creating an Iterator object.

   - ConcreteAggregate

     implements the Iterator creation interface to return an instance of the proper Concretelterator.

6. Collaborations

   A Concretelterator keeps track of the current object in the aggregate and can compute the succeeding object in the traversal.

7. Consequences

   The Iterator pattern has three important consequences:

   - It supports variations in the traversal of an aggregate.
   - Iterators simplify the Aggregate interface.
   - More than one traversal can be pending on an aggregate.

8. Implementation

9. Sample Code

   ```c++
   template <class Item>
   class List {
   public:
       List(long size = DEFAULT_LIST_CAPACITY);
       long Count() const;
       Item& Get(long index) const;
       // ...
   };
   
   template <class Item>
   class Iterator {
   public:
       virtual void First() = 0;
       virtual void Next() = 0;
       virtual bool IsDone() const = 0;
       virtual Item CurrentItem() const = 0;
       
   protected:
       Iterator();
   };
   
   template<class Item>
   class ListIterator : public Iterator<Item> {
   public:
       ListIterator(const List<Item>* aList);
       virtual void First();
       virtual void Next();
       virtual bool IsDone() const;
       virtual Item CurrentItem() const;
       
   private:
       const List<Item>* _list;
       long _current;
   };
   
   template<class Item>
   ListIterator<Item>::ListIterator(const List<Item>* aList) : 
       _list(aList), _current(0) {}
   
   template<class Item>
   void ListIterator<Item>::First() {
       _current = 0;
   }
   
   template <class Item>
   void ListIterator<Item>::Next() {
       _current++;
   }
   
   template <class Item>
   bool ListIterator<Item>::IsDone() const {
       return _current >= _list->Count();
   }
   
   template <class Item>
   Item ListIterator<Item>::CurrentItem() const {
       if (IsDone()) {
           throw IteratorOutOfBounds;
       }
       return _list->Get(_current);
   }
   
   void PrintEmployee(Iterator<Employee*>& i) {
       for (i.First(); !i.IsDone(); i.Next()) {
           i.CurrentItem()->Print();
       }
   }
   
   List<Employee*>* employees;
   // ...
   ListIterator<Employee*> forward(employees);
   ReverseListIterator<Employee*> backward(employees);
   PrintEmployees(forward);
   PrintEmployees(backward);
   
   SkipList<Employee*>* employees;
   // ...
   
   SkipListIterator<Employee*> iterator(employees);
   PrintEmployees(iterator);
   
   template<class Item>
   class AbstractList {
   public:
       virtual Iterator<Item>* CreateIterator() const = 0;
       // ...
   };
   
   template <class Item>
   Iterator<Item>* List<Item>::CreateIterator() const {
       return new ListIterator<Item>(this);
   }
   
   // we know only that we have an AbstractList
   AbstractList<Employee*>* employees;
   // ...
   
   Iterator<Employee*>* iterator = employees->CreateIterator();
   PrintEmployees(*iterator);
   delete iterator;
   
   template<class Item>
   class IteratorPtr {
   public:
       IteratorPtr(Iterator<Item>* i) : _i(i) {}
       ~IteratorPtr() { delte _i; }
       
       Iterator<Item>* operator->() { return _i; }
       Iterator<Item>& operator*() { return *_i; }
       
   private:
       // disallow copy and assignment to avoid
       // multiple deletions of _i:
       
       IteratorPtr(const IteratorPtr&);
       IteratorPtr& operator=(const IteratorPtr&);
       
   private:
       Iterator<Item>* _i;
   };
   
   AbstractList<Employee*>* employees;
   // ...
   
   IteratorPtr<Employee*> iterator(employees->CreateIterator());
   PrintEmployees(*iterator);
   
   template <class Item>
   class ListTraverser {
   public:
       ListTraverser(List<Item>* aList);
       bool Traverse();
       
   protected:
       virtual bool ProcessItem(const Item&) = 0;
       
   private:
       ListIterator<Item> _iterator;
   };
   
   template <class Item>
   ListTraverser<Item>::ListTraverser(List<Item>* aList) : 
       _iterator(aList) {}
   
   template <class Item>
   bool ListTraverser<Item>::Traverse() {
       bool result = false;
       
       for (_iterator.First(); !_iterator.IsDone(); _iterator.Next()) {
           result = ProcessItem(_iterator.CurrentItem());
           
           if (result == false) {
               break;
           }
       }
       return result;
   }
   
   class PrintNEmployees : public ListTraverser<Employee*> {
   public:
       PrintNEmployees(List<Employee*>* aList, int n) :
           ListTraverser<Employee*>(aList), _total(n), _count(0) {}
       
   protected:
       bool ProcessItem(Employee* const&);
       
   private:
       int _total;
       int _count;
   };
   
   bool PrintNEmployees::ProcessItem(Employee* const& e) {
       _count++;
       e->Print();
       return _count < _total;
   }
   
   List<Employee*>* employees;
   // ...
   
   PrintNEmployees pa(employees, 10);
   pa.Traverse();
   
   ListIterator<Employee*> i(employees);
   int count = 0;
   for (i.First(); !i.IsDone(); i.Next()) {
       count++;
       i.CurrentItem()->Print();
       if (count >= 10) {
           break;
       }
   }
   
   template <class Item>
   class FilteringListTraverser {
   public:
       FilteringListTraverser(List<Item>* aList);
       bool Traverse();
       
   protected:
       virtual bool ProcessItem(const Item&) = 0;
       virtual bool TestItem(const Item&) = 0;
       
   private:
       ListIterator<Item> _iterator;
   };
   
   template <class Item>
   void FilteringListTraverser<Item>::Traverse() {
       bool result = false;
       for (_iterator.First(); !_iterator.IsDone(); _iterator.Next()) {
           if (TestItem(_iterator.CurrentItem())) {
               result = ProcessItem(_iterator.CurrentItem());
               if (result == false) {
                   break;
               }
           }
       }
       return result;
   }
   ```

10. Known Uses

11. Related Patterns

    Composite (163):Iterators are often applied to recursive structures such as Composites.

    Factory Method (107):Polymorphic iterators rely on factory methods to instantiate the appropriate Iterator subclass. 

    Memento (283) is often used in conjunction with the Iterator pattern. An iterator can use a memento to capture the state of an iteration. The iterator stores the memento internally.

---



## MEDIATOR

1. Intent

   Define an object that encapsulateshow a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.

2. Motivation

3. Applicability

   Use the Mediator pattern when:

   - a set of objects communicatein well-defined but complexways.The resulting interdependencies are unstructured and difficult to understand.
   - reusing an object is difficult because itrefers to and communicateswithmany other objects.
   - a behavior that's distributed between several classes should be customizable without a lot of subclassing.

4. Structure

   ![5_5](res/5_5.png)

5. Participants

   - Mediator

     defines an interface for communicating with Colleague objects

   - ConcreteMediator

     implements cooperative behavior bycoordinating Colleague objects.

      knows andmaintains itscolleagues.

   - Colleague class

     each Colleague class knows itsMediator object.

     each colleague communicates with its mediator whenever it would have otherwise communicated with another colleague.

6. Collaborations

   Colleagues send and receive requests from a Mediator object. The mediator implements the cooperative behavior by routing requests between the appropriate colleague(s).

7. Consequences

   The Mediator pattern has the followingbenefits and drawbacks:

   1. It limits subclassing.
   2. It decouples colleagues.
   3. It simplifies object protocols.
   4. It abstracts how objects cooperate.
   5. It centralizes control.

8. Implementation

9. Sample Code

   ```c++
   class DialogDirector {
   public:
       virtual ~DialogDirector();
       virtual void ShowDialog();
       virtual void WidgetChanged(Widget*) = 0;
       
   protected:
       DialogDirector();
       virtual void CreateWidgets() = 0;
   };
   
   class Widget {
   public:
       Widget(DialogDirector*);
       virtual void Changed();
       virtual void HandleMouse(MouseEvent& event);
       // ...
       
   private:
       DialogDirector* _director;
   };
   
   void Widget::Changed() {
       _director->WidgetChanged(this);
   }
   
   class ListBox : public Widget {
   public:
       ListBox(DialogDirector*);
       virtual const char* GetSelection();
       virtual void SetL:ist(List<char*>* listItems);
       virtual void HandleMouse(MouseEvent& event);
       // ...
   };
   
   class EntryField : public Widget {
   public:
       EntryField(DialogDirector*);
       virtual void SetText(const char* text);
       virtual const char* GetText();
       virtual void HandleMouse(MouseEvent& event);
       // ...
   };
   
   class Button : public Widget {
   public:
       Button(DialogDirector*);
       virtual void SetText(const char* text);
       virtual void HandleMouse(MouseEvent& event);
       // ...
   };
   void Button::HandleMouse(MouseEvent& event) {
       // ...
       Changed();
   }
   
   class FontDialogDirector : public DialogDirector {
   public:
       FontDialogDirector();
       virtual ~FontDialogDirector();
       virtual void WidgetChanged(Widget*);
       
   protected:
       virtual void CreateWidgets();
       
   private:
       Button* _ok;
       Button* _cancel;
       ListBox* _fontList;
       EntryField* _fontName;
   };
   void FontDialogDirector::CreateWidgets() {
       _ok = new Button(this);
       _cancel = new Button(this);
       _fontList = new ListBox(this);
       _fontName = new EntryField(this);
       // fill the listBox with the available font names
       // assemble the widgets in the dialog
   }
   void FontDialogDirector::WidgetChanged(Widget* theChangedWidget) {
       if (theChangedWidget == _fontList) {
           _fontName->SetText(_fontList->GetSelection());
       } else if (theChangedWidget == _ok) {
           // apply font change and dismiss dialog
           // ...
       } else if (theChangedWidget == _cancel) {
           // dismiss dialog
       }
   }
   ```

10. Known Uses

11. Related Patterns

    Facade (185) differs from Mediator in that it abstracts a subsystem of objects to provide a more convenient interface. Its protocol is unidirectional; that is, Facade objects make requests of the subsystem classes but not vice versa. In contrast, Mediator enables cooperative behavior that colleague objects don't or can't provide, and the protocol is multidirectional.

    Colleagues can communicate with the mediator using the Observer (293) pattern.

---



## MEMENTO

1. Intent

   Without violating encapsulation, capture and externalize an object's internal state so that the object can be restored to this state later.

2. Motivation

3. Applicability

   Use the Memento pattern when:

   - a snapshot of (some portion of) an object's state must be saved so that it can be restored to that state later, and
   - a direct interface to obtaining the state would expose implementation details and break the object's encapsulation.

4. Structure

   ![5_6](res/5_6.png)

5. Participants

   - Memento

     stores internal state of the Originator object. The memento may store as much or as little of the originator's internal state as necessary at its originator's discretion.

     protects against access by objects other than the originator. Mementos have effectively two interfaces. Caretaker sees a narrow interface to the Memento—it can only pass the memento to other objects. Originator, in contrast, sees a wide interface, one that letsit access all the data necessary to restore itself to its previous state. Ideally, only the originator that produced the memento would be permitted to access the memento's internal state.

   - Originator

     creates a memento containing a snapshot of its current internal state.

     uses the memento to restore its internal state.

   - Caretaker

     is responsible for the memento's safekeeping.

     never operates on or examines the contents of a memento.

6. Collaborations

   - A caretaker requests a memento from an originator, holds it for a time, and passes it back to the originator, as the following interaction diagram illustrates:

     ![5_6b](res/5_6b.png)

   - Mementos are passive. Only the originator that created a mementowill assign or retrieve its state.

7. Consequences

   The Memento pattern has several consequences:

   - Preserving encapsulation boundaries.
   - It simplifies Originator.
   - Using mementos might beexpensive.
   - Defining narrow and wide interfaces.
   - Hidden costs in caring for mementos.

8. Implementation

9. Sample Code

   ```c++
   class State;
   
   class Originator {
   public:
       Memento* CreateMemento();
       void SetMemento(const Memento*);
       // ...
   private:
       State* _state; // internal data structures
       // ...
   };
   
   class Memento {
   public:
       // narrow public interface
       virtual ~Memento();
   private:
       // private members accessible only to Originator
       friend class Originator;
       Memento();
       void SetState(State*);
       State* GetState();
       // ...
   private:
       State* _state;
       // ...
   };
   
   class Graphic;
   // base class for graphical objects in the graphical editor
   
   class MoveCommand {
   public:
       MoveCommand(Graphic* target, const Point& delta);
       void Execute();
       void Unexecute();
   private:
       ConstraintSolverMemento* _state;
       Point _delta;
       Graphic* _target;
   };
   void MoveCommand::Unexecute() {
       ConstraintSolver* solver = ConstraintSolver::Instance();
       _target->Move(-_delta);
       solver->SetMemento(_state); // restore solver state
       solver->Solve();
   }
   
   class ConstraintSolver {
   public:
       static ConstraintSolver* Instance();
       
       void Solve();
       void AddConstraint(Graphic* startConnection, Graphic* endConnection);
       void RemoveConstraint(Graphic* startConnection, Graphic* endConnection);
       ConstraintSolverMemento* CreateMemeto();
       void SetMemento(ConstraintSolverMemento*);
   private:
       // nontrivial state and operations for enforcing
       // connectivity semantics
   };
   
   class ConstraintSolverMemento {
   public:
       virtual ~ConstraintSolverMemento();
   private:
       friend class ConstraintSolver;
       ConstraintSolverMemento();
       
       // private constraint solver state
   };
   ```

10. Known Uses

11. Related Patterns

    Command (233): Commands can use mementos to maintain state for undoable operations. 

    Iterator (257): Mementos can be used for iteration as described earlier.

---



## OBSERVER

1. Intent

   Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

2. Motivation

   The Observer pattern describes how to establish these relationships. The key objects in this pattern are subject and observer. A subject may have any number of dependent observers.Allobservers are notified whenever the subject undergoes a change in state.In response, each observer will query the subjectto synchronize its state with the subject's state. 

   This kind of interaction is also known as publish-subscribe. The subject is the publisher of notifications. It sends out these notifications without having to know who its observers are. Any number of observers can subscribe to receive notifications.

3. Applicability

   Use the Observer pattern in any of the following situations: 

   - When an abstraction has two aspects, one dependent on the other. Encapsulating these aspects in separate objects lets you vary and reuse them independently. 
   - When a change to one object requires changing others, and you don't know how many objects need to be changed. 
   - When an object should be able to notify other objects without making assumptions about who these objects are.In other words, you don't want these objects tightly coupled.

4. Structure

   ![5_7](res/5_7.png)

5. Participants

   - Subject

     nows its observers. Any number of Observer objects may observe a subject.

     provides an interface for attachingand detaching Observer objects.

   - Observer

     defines an updating interface for objects that should be notified ofchanges in a subject.

   - ConcreteSubject

     stores state ofinterest toConcreteObserver objects.

     sends a notification to its observers when itsstate changes.

   - ConcreteObserver

     maintains a reference to a ConcreteSubject object.

     stores state that should stay consistent with the subject's.

     implements the Observer updating interface to keep its state consistent with the subject's.

6. Collaborations

   - ConcreteSubject notifies its observers whenever a change occurs that could make its observers' state inconsistent with its own.

   - After being informed of a change in the concrete subject, a ConcreteObserver object may query the subject for information.ConcreteObserver uses this information to reconcile its state with that of the subject.

     The following interaction diagram illustrates the collaborations between a subject and two observers:

     ![5_7b](res/5_7b.png)

7. Consequences

   Further benefits and liabilities of the Observer pattern include the following:

   - Abstract coupling between Subject and Observer.
   - Support for broadcast communication.
   - Unexpected updates.

8. Implementation

9. Sample Code

   ```c++
   class Subject;
   
   class Observer {
   public:
       virtual ~Observer();
       virtual void Update(Subject* theChangedSubject) = 0;
   protected:
       Observer();
   };
   
   class Subject {
   public:
       virtual ~Subject();
       
       virtual void Attach(Observer*);
       virtual void Detach(Observer*);
       virtual void Notify();
   protected:
       Subject();
   private:
       List<Observer*> *_observers;
   };
   void Subject::Attach(Observer* o) {
       _observers->Append(0);
   }
   void Subject::Detach(Observer* o) {
       _observers->Remove(0);
   }
   void Subject::Notify() {
       ListIterator<Observer*> i(_observers);
       for (i.First(); !i.IsDone(); i.Next()) {
           i.CurrentItem()->Update(this);
       }
   }
   
   class ClockTimer : public Subject {
   public:
       ClockTimer();
       
       virtual int GetHour();
       virtual int GetMinute();
       virtual int GetSecond();
       
       void Tick();
   };
   void ClockTimer::Tick() {
       // update internal time-keeping state
       // ...
       Notify();
   }
   
   class DigitalClock : public Widget, public Observer {
   public:
       DigitalClock(ClockTimer*);
       virtual ~DigitalClock();
       virtual void Update(Subject*);
       // overrides Observer operation
       
       virtual void Draw();
       // overrides Widget operation;
       // defines how to draw the digital clock
   private:
       ClockTimer* _subject;
   };
   DigitalClock::DigitalClock(ClockTimer* s) {
       _subject = s;
       _subject->Attach(this);
   }
   DigitalClock::~DigitalClock() {
       _subject->Detach(this);
   }
   void DigitalClock::Update(Subject* theChangedSubject) {
       if (theChangedSubject == _subject) {
           Draw();
       }
   }
   void DigitalClock::Draw() {
       // get the new values from the subject
       
       int hour = _subject->GetHour();
       int minute = _subject->GetMinute();
       // etc.
       
       // draw the digital clock
   }
   
   class AnalogClock : public Widget, public Observer {
   public:
       AnalogClock(ClockTimer*);
       virtual void Update(Subject*);
       virtual void Draw();
       // ...
   };
   
   ClockTimer* timer = new ClockTimer;
   AnalogClock* analogClock = new AnalogClock(timer);
   DigitalClock* digitalClock = new DigitalClock(timer);
   ```

10. Known Uses

11. Related Patterns

    Mediator (273):Byencapsulating complex update semantics, theChangeManager acts as mediator between subjects and observers.

    Singleton (127): The ChangeManager may use the Singleton pattern to make it unique and globally accessible.

---



## STATE

1. Intent

   Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.

2. Motivation

3. Applicability

   Use the State pattern in either of the following cases:

   - An object's behavior depends on its state, and it must change its behavior at run-time depending on that state.
   - Operations have large, multipart conditional statements that depend on the object's state. This state is usually represented by one or more enumerated constants.

4. Structure

   ![5_8_1](res/5_8_1.png)

5. Participants

   - Context

     defines the interface ofinterest to clients.

     maintains an instance of a ConcreteState subclass that defines the current state.

   - State

     defines an interface for encapsulating the behavior associated with a particular state of the Context.

   - ConcreteState subclasses

     each subclassimplements a behavior associated with a state of the Context.

6. Collaborations

   - Context delegates state-specific requests to the current ConcreteState object.
   - A context may pass itself as an argument to the State object handling the request. This lets the State object access the context if necessary. 
   - Context isthe primary interface for clients.Clients canconfigure a context with State objects. Once a context is configured, its clients don't have to deal with the State objects directly. 
   - EitherContextortheConcreteState subclasses candecide which state succeeds another and under what circumstances.

7. Consequences

   The State pattern has the following consequences:

   - It localizes state-specific behavior and partitions behavior for different states.
   - It makes state transitions explicit.
   - State objects can beshared.

8. Implementation

9. Sample Code

   ```c++
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

10. Known Uses

11. Related Patterns

    The Flyweight (195) pattern explains when and how State objects can be shared. 

    State objects are often Singletons (127).

---



## STRATEGY

1. Intent

   Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

2. Motivation

   Many algorithms existfor breaking a streamoftextintolines. Hard-wiring allsuch algorithms into the classes that require them isn't desirable for several reasons:

   - Clients that need linebreaking get more complex if they include the linebreaking code. That makes clients bigger and harder to maintain, especially if they support multiple linebreaking algorithms.
   - Different algorithms will be appropriate at different times. Wedon't want to support multiple linebreaking algorithms if we don't use them all.
   - It's difficult toadd newalgorithms and vary existing ones when linebreaking is an integral part of a client.

3. Applicability

   Use the Strategy pattern when:

   - many related classes differ only in their behavior. Strategies provide a way to configure a class with one of many behaviors.
   - you need different variants of an algorithm. For example, you might define algorithms reflecting different space/time trade-offs. Strategies can be used when these variants are implemented as a class hierarchy of algorithms.
   - an algorithm uses data that clients shouldn't know about. Use the Strategy pattern to avoid exposing complex, algorithm-specific data structures.
   - a class defines many behaviors, and these appear as multiple conditional statements in its operations. Instead of many conditionals, move related conditional branches into their own Strategy class.

4. Structure

   ![5_9](res/5_9.png)

5. Participants

   - Strategy

     declares an interface common to all supported algorithms. Context uses this interface to call the algorithm defined by a ConcreteStrategy

   - ConcreteStrategy

     implements the algorithm using the Strategy interface.

   - Context（上下文）

     is configured with a ConcreteStrategy object.

     maintains a reference to a Strategy object.

     may define an interface that lets Strategy access its data.

6. Collaborations

   - Strategy and Context interact to implement the chosen algorithm. A context may pass all data required by the algorithm to the strategy when the algorithm is called. Alternatively, the context can pass itself as an argument to Strategy operations. That lets the strategy call back on the context as required.
   - A context forwards requests from its clients to its strategy. Clients usually create and pass a ConcreteStrategy object to the context; thereafter, clients interact with the contextexclusively.There is often a family ofConcreteStrategy classes for a client to choose from.

7. Consequences

   The Strategy pattern has the following benefits and drawbacks:

   - Families of related algorithms.
   - An alternative to subclassing.
   - Strategies eliminate conditional statements. 
   - A choice of implementations.
   - Clients must be aware of different Strategies.
   - Communication overhead between Strategy and Context.
   - Increased number of objects.

8. Implementation

9. Sample Code

   ```c++
   class Composition {
   public:
       Composition(Compositor*);
       void Repair();
   private:
       Compositor* _compositor;
       Component* _components;
       int _componentCount;
       int _lineWidth;
       int* _lineBreaks;
       int _lineCount;
   };
   
   class Compositor {
   public:
       virtual int Compose(Coord natural[], Coord stretch[], Coord shrink[], 
                           int componentCount, int lineWidth, int breaks[]) = 0;
   protected:
       Compositor();
   };
   void Composition::Repair() {
       Coord* natural;
       Coord* stretchability;
       Coord* shrinkability;
       int componentCount;
       int* breaks;
       
       // prepare the arrays with the desired component sizes
       // ...
       
       // determine where the breaks are:
       int breakCount;
       breakCount = _compositor->Compose(
       	natural, stretchability, shrinkability,
           componentCount, _lineWidth, breaks);
       
       // lay out components according to breaks
       // ...
   }
   
   class SimpleCompositor : public Compositor {
   public:
       SimpleCompositor();
       virtual int Compose(Coord natural[], Coord stretch[], Coord shrink[],
                           int componentCount, int lineWidth, int breaks[]);
       // ...
   };
   
   class TeXCompositor : public Compositor {
   public:
       TeXCompositor();
       virtual int COmpose(Coord natural[], Coord stretch[], Coord shrink[], 
                           int componentCount, int lineWidth, int breaks[]);
       // ...
   };
   
   class ArrayCompositor : public Compositor {
   public:
       ArrayCompositor(int interval);
       virtual int Compose(Coord natural[], Coord stretch[], Coord shrink[],
                           int componentCount, int lineWidth, int breaks[]);
       // ...
   };
   
   Composition* quick = new Composition(new SimpleCompositor);
   Composition* slick = new Composition(new TeXCompositor);
   Composition* iconic = new Composition(new ArrayCompositor(100));
   ```

10. Known Uses

11. Related Patterns

    Flyweight (195): Strategy objects often make good flyweights.

---



## TEMPLATE METHOD

1. Intent

   Define the skeleton of an algorithm in an operation, deferring some steps to subclasses.Template Method letssubclassesredefine certain steps of an algorithm without changing the algorithm's structure.

2. Motivation

   By defining some of the steps of an algorithm using abstract operations, the template method fixes their ordering, but it lets Application and Document subclasses vary those steps to suit their needs.

3. Applicability

   By defining some of the steps of an algorithm using abstract operations, the template method fixes their ordering, but it lets Application and Document subclasses vary those steps to suit their needs:

   - to implement the invariant parts of an algorithm once and leave it up to subclasses to implement the behavior that can vary.
   - when common behavior among subclasses should be factored and localized in a common class to avoid code duplication.
   - to control subclasses extensions.

4. Structure

5. Participants

   - AbstractClass

     defines abstract primitive operations that concrete subclasses define to implement steps of an algorithm.

     implements a template method defining the skeleton of an algorithm. The template method calls primitive operations as well as operations defined in AbstractClass or those of other objects.

   - ConcreteClass

     implements the primitive operations to carry outsubclass-specific stepsof the algorithm.

6. Collaborations

   ConcreteClass relies on AbstractClass to implement the invariant steps ofthe algorithm.

7. Consequences

   Template methods call the following kinds of operations:

   - concrete operations (either on the ConcreteClass or on client classes);
   - concrete AbstractClass operations (i.e., operations that are generally useful to subclasses);
   - primitive operations (i.e., abstract operations);
   - factory methods (see Factory Method (107)); and
   - hook operations, which provide default behavior that subclasses can extend if necessary. A hook operation often does nothing by default.

8. Implementation

9. Sample Code

   ```c++
   void View::Display() {
       SetFocus();
       DoDisplay();
       ResetFocus();
   }
   
   void View::DoDisplay(){}
   
   void MyView::DoDisplay() {
       // render the view's contents
   }
   ```

10. Known Uses

11. Related Patterns

    Factory Methods (107) are often called by template methods. In the Motivation example, the factory method DoCreateDocument is called by the template method OpenDocument.

    Strategy (315): Template methods use inheritance to vary part of an algorithm. Strategies use delegation to vary the entire algorithm.

---



## VISITOR

1. Intent

   Represent an operation to be performed on the elements of an object structure.Visitor lets you define a new operation without changing the classes of the elements on which it operates.

2. Motivation

3. Applicability

   Use the Visitorpattern when:

   - an object structure contains many classes of objectswith differing interfaces, and you want to perform operations on these objects that depend on their concrete classes.
   - manydistinct and unrelated operations need tobe performed on objectsinan object structure, and you want to avoid "polluting" their classes with these operations. Visitorlets you keep related operations together by definingthem in one class. When the object structure is shared by many applications, use Visitor to put operations in just those applications that need them.
   - the classes defining the object structure rarely change, but you often want to define new operations over the structure. Changing the object structure classes requires redefining the interface to all visitors, which is potentially costly. Ifthe object structure classes change often, then it's probably better to define the operations in those classes.

4. Structure

   ![5_11](res/5_11.png)

5. Participants

   - Visitor

     declares a Visit operation for each class of ConcreteElement in the object structure. Theoperation's name and signature identifiesthe class that sends the Visit request to the visitor. That lets the visitor determine the concrete class of the element being visited. Then the visitor can access the element directly through its particularinterface.

   - ConcreteVisitor

     mplements each operation declared byVisitor.Eachoperation implements a fragment of the algorithm defined for the corresponding class of object in the structure. ConcreteVisitor provides the context for the algorithm and stores its local state. This state often accumulates results during the traversal of the structure.

   - Element

     defines an Accept operation that takes a visitor as an argument.

   - ConcreteElement

     implements an Accept operation that takes a visitor as an argument.

   - ObjectStructure（对象结构）

     can enumerate itselements.

     mayprovide a high-level interface to allow the visitor to visit its elements.

     may either be a composite (see Composite (163)) or a collection such as a list or a set.

6. Collaborations

   - A client that uses the Visitor pattern must create a ConcreteVisitor object and then traverse the object structure, visiting each element with the visitor.

   - When an element is visited, it calls the Visitor operation that corresponds to its class. The element supplies itself as an argument to this operation to let the visitor access its state, if necessary.

     ![5_11b](res/5_11b.png)

7. Consequences

   Some of the benefits and liabilities of the Visitor pattern are asfollows:

   - Visitor makes adding newoperations easy.
   - A visitor gathers related operations and separates unrelated ones.
   - Adding new ConcreteElement classes is hard.
   - Visiting across class hierarchies.
   - Accumulating state.
   - Breaking encapsulation.

8. Implementation

9. Sample Code

   ```c++
   class Equipment {
   public:
       virtual ~Equipment();
       const char* Name() { return _name; }
       virtual Watt Power();
       virtual Currency NetPrice();
       virtual Currency DiscountPrice();
       virtual void Accept(EquipmentVisitor&);
   protected:
       Equipment(const char*);
   private:
       const char* _name;
   };
   
   class EquipmentVisitor {
   public:
       virtual ~EquipmentVisitor();
       virtual void VisitFloppyDisk(FloppyDisk*);
       virtual void VisitCard(Card*);
       virtual void VisitChassis(Chassis*);
       virtual void VIsitBus(Bus*);
       
       // and so on for other concrete subclasses of Equipment
   protected:
       EquipmentVisitor();
   };
   
   class PricingVisitor : public EquipmentVisitor {
   public:
       PricingVisitor();
       Currency& GetTotalPrice();
       virtual void VisitFloppyDisk(FloppyDisk*);
       virtual void VisitCard(Card*);
       virtual void VisitChassis(Chassis*);
       virtual void VisitBus(Bus*);
       // ...
   private:
       Currency _total;
   };
   void PricingVisitor::VisitFloppyDisk(FloppyDisk* e) {
       _total += e->NetPrice();
   }
   void PricingVisitor::VisitChassis(Chassis* e) {
       _total += e->DiscountPrice();
   }
   
   class InventoryVisitor : public EquipmentVisitor {
   public:
       InventoryVisitor();
       Inventory& GetInventory();
       virtual void VisitFloppyDisk(FloppyDisk*);
       virtual void VisitCard(Card*);
       virtual void VisitChassis(Chassis*);
       virtual void VisitBus(Bus*);
       // ...
   private:
       Inventory _inventory;
   };
   
   void InventoryVisitor::VisitFloppyDisk(FloppyDisk* e) {
       _inventory.Accumulate(e);
   }
   
   void InventoryVisitor::VisitChassis(Chassis* e) {
       _inventory.Accumulate(e);
   }
   
   Equipment* component;
   InventoryVisitor visitor;
   component->Accept(visitor);
   cout << "Inventory " << component->Name() << visitor.GetInventory();
   ```

10. Known Uses

11. Related Patterns

    Composite (163):Visitorscan be used to apply an operation over an object structure defined by the Composite pattern. 

    Interpreter (243): Visitor may be applied to do the interpretation.

---



## Discussion of Behavioral Pattern

### Encapsulating Variation

Encapsulating variation is a theme of many behavioral patterns. When an aspect of a program changes frequently, these patterns define an object that encapsulates that aspect. Then other parts of the program can collaboratewith the object whenever they depend on that aspect. The patterns usually define an abstract class that describes the encapsulating object, and the pattern derives its name from that object.

### Objects as Arguments

Several patterns introduce an object that's always used as an argument.

Other patterns define objects that act as magic tokens to be passed around and invoked at a later time.

### Should Communication be Encapsulated or Distributed?

Mediator (273) and Observer (293) are competing patterns. The difference between them isthat Observer distributes communication by introducing Observer and Subject objects, whereas a Mediator object encapsulates the communication between other objects.

### Decoupling Senders and Receivers

The Command pattern supports decoupling by using a Command object to define the binding between a sender and receiver:

![5_12a](res/5_12a.png)

The Observer pattern decouples senders (subjects) from receivers (observers)by defining an interface for signaling changes in subjects. Observer defines a looser senderreceiver binding than Command, since a subject may have multiple observers, and their number can vary at run-time:

![5_12b](res/5_12b.png)

The Mediator pattern decouples objects by having them refer to each other indirectly through a Mediator object.

![5_12c](res/5_12c.png)

Finally, the Chain of Responsibility pattern decouples the sender from the receiver by passing the request along a chain of potential receivers:

![5_12d](res/5_12d.png)



## Summary

With few exceptions, behavioral design patterns complement and reinforce each other.

Well-designed object-oriented systems are just like this—they have multiple patterns embedded in them—but not because their designers necessarily thought in these terms.