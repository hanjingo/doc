# 第五章 行为模式
本章包括2个模式:
- Template Method 
- Interpreter

## CHAIN OF RESPONSIBILITY(职责链)-对象行为型模式
### 目的
使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。
将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。
### 适用性
- 有多个的对象可以处理一个请求，哪个对象处理该请求运行时刻自动确定。
- 你想在不明确指定接收者的情况下，想多个对象中的一个提交一个请求。
- 可处理一个请求的对象集合应被动态指定。
### Responsibility链有下列优点和缺点(liabilities):
1. 降低耦合度
2. 增强了给对象指派职责(Responsibility)的灵活性		
3. 不保证被接受
### 示例
```c++
typedef int Topic;
const Topic NO_HELP_TOPIC = -1;

class HelpHandler {
		public:
				HelpHandler(HelpHandler* = 0, Topic = NO_HELP_TOPIC);
				virtual bool HasHelp();
				virtual void SetHandler(HelpHandler*, Topic);
				virtual void HandleHelp();
		private:
				HelpHandler* _successor;
				Topic _topic;
};

HelpHandler::HelpHandler {
	HelpHandler* h, Topic t
} : _successor(h), _topic(t) { }

bool HelpHandler::HasHelp () {
	return _topic != NO_HELP_TOPIC;
}
void HelpHandler::HandleHelp () {
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

Widget::Widget (Widget* w, Topic t) : HelpHandler(w, t) {
	_parent = w;
}

class Button : public Widget {
public:
		Button(Widget* d, Topic t = NO_HELP_TOPIC);

		virtual void HandleHelp();
};

Button::Button (Widget* h, Topic t) : Widget(h, t) {}

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

Dialog::Dialog (HelpHandler* h, Topic t) : Widget(0) {
	SetHandler(h, t);
}

void Dialog::HandleHelp () {
	if (HasHelp()) {
		// offer help on the dialog
	} else {
		HelpHandler::HandleHelp();
	}
}

class Application : public HelpHandler {
public:
		Application(Topic t) : HelpHandler(0, t) { }

		virtual void HandleHelp();
};

void Application::HandleHelp() {
	if (HasHelp()) {
		// offer help on the dialog
	} else {
		HelpHandler::HandleHelp();
	}
}

class Application : public HelpHandler {
public:
		Application(Topic t) : HelpHandler(0, t) { }

		virtual void HandleHelp();
		// appllication-specific operations...
};

const Topic PRINT_TOPIC = 1;
const Topic PAPER_ORIENTATION_TOPIC = 2;
const Topic APPLICATION_TOPIC = 3;

Application* application = new Application(APPLICATION_TOPIC);
Dialog* dialog = new Dialog(application, PRINT_TOPIC);
Button* button = new Button(dialog, PAPER_ORIENTATION_TOPIC);
```

## COMMAND(命令)-对象行为型模式
### 目的
将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数话；对请求排队或记录请求日志，以及支持可撤销的操作
### 实现
```c++
class Command {
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
};

OpenCommand::OpenCommand (Application* a) {
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
	PasteCommand(Document*);

	virtual void Execute();
private:
	Document* _document;	
};

PasteCommand::PasteCommand (Document* doc) {
	_document = doc;
}

void PasterCommand::Execute() {
	_document->Paste();
}

template <class Receiver>
class SimpleCommand : public Command {
		public:
				typedef void (Receiver::* Action)();

				SimpleCommand(Receiver* r, Action a):
						_receiver(r), _action(a) {}

				virtual void Execute();
		private:
				Action _action;
				Receiver* _receiver;
};

template <class Receiver>
void SimpleCommand<Receiver>::Execute(){
	(_receiver->*_action)();
}

MyClass* receiver = new MyClass;
// ...
Command* aCommand = new SimpleCommand<MyClass>(receiver, &MyClass::Action);
// ...
aCommand->Execute();

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

void MacroCommand::Execute () {
	ListIterator<Command*> i(_cmds);

	for (i.First(); !I.IsDone(); i.Next()) {
		Command* c = i.CurrentItem();
		c->Execute();
	}
}

void MacroCommand::Add (Command* c) {
	_cmds->Append(c);
}

void MacroCommand::Remove (Command* c) {
	_cmds->Remove(c);
}
```

## INTERPRETER(解释器)-类行为型模式
### 目的
给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子

### 实现
```c++
class BooleanExp {
public:
		BooleanExp();
		virtual ~BooleanExp();

		virtual bool Evaluate(Context&) = 0;
		virtual BooleanExp* Replace(const char*, BooleanExp&);
		virtual BooleanExp* Copy() const;

private:
		char* _name;
};
VariableExp::VariableExp (const char* name) {
	_name = strdup(name);
}

bool VariableExp::Evaluate (Context& aContext) {
	return aContext.Lookup(_name);
}

BooleanExp* VariableExp::Copy() const {
	return new  VariableExp(_name);
}

BooleanExp* VariableExp::Replace {
	const char* name, BooleanExp& exp
} {
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
		virtual BooleanExp* Replace(consst char*, BooleanExp&);
		virtual BooleanExp* Copy() const;


private:
		BooleanExp* _operand1;
		BooleanExp* _operand2;
};

AndExp::AndExp (BooleanExp* op1, BooleanExp* op2) {
	_operand1 = op1;
	_operand2 = op2;
}

bool AndExp::Evaluate (Context& aContext) {
	return
			_operand1->Evaluate(aContext) && 
			_operand2->Evaluate(aContext);
}

```
