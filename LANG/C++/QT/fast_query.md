# qt速查手册



[TOC]



## `Q_CLASSINFO`

类信息，姓名表格化



## `Q_PROPERTY`

用来说明属性继承自QObject

```c++
	Q_PROPERTY(type name
             (READ getFunction [WRITE setFunction] |
              MEMBER memberName [(READ getFunction | WRITE setFunction)])
```



## `T qobject_cast(QObject *object)`

- 如果object是T类型，则返回T类型，否则返回0；
- T类必须直接或间接继承自QObject,并使用Q_Object宏声明
```c++
	QObject *obj = new QTimer;
	// QTimer inherits QObject
	QTimer *timer = qobject_cast<QTimer *>(obj);
	// timer == (QObject *)obj
	QAbstractButton *button = qobject_cast<QAbstractButton *>(obj);
	// button == 0
```
qobject_cast()类似于c++的dynamic_cast();它的好处是不要求RTTI支持，并超越了标准动态库限制；它也能用于连接接口；

注意：使用此函数之前必须使用Q_OBJECT宏



## `QT_BEGIN_NAMESPACE`
class QVBoxLayout;



## `QT_END_NAMESPACE`
在编译时转换为：
```c++
    namespace QT_BEGIN_NAMESPACE{
        class QVBoxLayout;
    }
```
注意：仅当在编译Qt时，加上-qtnamespace选项时，这两个宏才会有作用，这时，Qt作为第三方库，要使用用户自定义的命名空间来访问Qt中的类，如QListView *view = new QT_NAMESPACE::QListView



## `setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy)`
设置水平滑动条
```c++
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);//在需要时启用水平滑动条
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滚动条  
```



## `QMainWindow::setCentralWidget(QWidget *widget)`

将widget设置为当前窗口的中心部件

注意：widget的所有权归当前窗口，且当前窗口会在合适的时间释放widget



## `void QWidget::setAttribute(Qt::WidgetAttribute attribute, bool on = true)`

当on为true时用来设置类属性，否则清除属性
```c++
	setAttribute(Qt::WA_DeleteOnClose);     //子窗口关闭时销毁mychild类对象
```



## `setWindowModified(bool)`

当窗口名称中包含`"[*]"`时，如果bool为true，则将窗口名称标记为已修改`（在后面加*）`



## `QFileInfo(const QString &file)`

通过给予的路径构造QFileInfo对象



## `QString QFileInfo::fileName() const`

返回不带路径的文件名
```c++
    QFileInfo fi("/tmp/archive.tar.gz");
    QString name = fi.fileName();// name = "archive.tar.gz"
```
注意：如果fi为以斜杠结束的路径名，则返回空



## `Void Qaction::setCheckable(bool)`

设置可以被选中



## `foreach(variable, container)`

被用来实现历遍容器
```c++
	QLinkedList<QString> list;
	QString str;
  	foreach (str, list)
     	qDebug() << str;
	注意：如果担心污染命名空间，可以使用“CONFIG += no_Keywords”防止
	注意：qt将不再支持这个函数，建议使用c++17的for函数
	c++17: 
		QString s = "abc";
  		for (QChar ch : s)
			cout<<ch;
```



## `QSignalMapper`

用来捆绑来自可辨认的信号发射者；简单的理解，可以把SignalMapper这个类看成是信号的翻译和转发器， 它可以把一个无参	数的信号翻译成带int参数、QString参数、QObject*参数或者QWidget*参数的信号， 并将之转发。 这么一说大家有没有联想到	该类的适用范围呢？ 呵呵， 是不是一下就想到了如果我有一堆的button， 可以把clicked事件放在一个函数里处理， 只要给	button编个号或者给button起个名就行了， 这样就不用给每个button写一个slot了，岂不是很方便？ 

下面这段代码就实现了该功能： 
```c++
	class MainWin : public QWidget 

	{
	Q_OBJECT 
	public: 
    		MainWin(QWidget *parent = 0); 
	private slots: 
     	void doClicked(const QString & btnname);//处理最终信号的槽 
	private:
     	QSignalMapper *signalMapper; 
	};
	MainWin::MainWin(QStringList texts, QWidget *parent) : QWidget(parent) 
	{ 
		QString buttontext = "btn1,btn2,btn3,btn4,btn5,btn6,btn7,btn8,btn9,btn10";//10个button 
		QStringList texts = buttontext.split(","); 
		signalMapper = new QSignalMapper(this); 
		QGridLayout *gridLayout = new QGridLayout; 
		for (int i = 0; i < texts.size(); ++i) 
		{ 
		QPushButton *button = new QPushButton(texts[i]); 
		connect(button, SIGNAL(clicked()), signalMapper, SLOT(map ()));//原始信号传递给signalmapper 
		signalMapper->setMapping (button, texts[i]);
		//设置signalmapper的转发规则, 转发为参数为QString类型的信号， 并把texts[i]的内容作为实参传递。 
		gridLayout->addWidget(button, i / 3, i % 3); 
	} 
	connect(signalMapper, SIGNAL(mapped (const QString &)), this, SLOT(doClicked(const QString &)));//将转发的信号连接到最终的槽函		数 
	setLayout(gridLayout);
	} 
	void MainWin::doClicked(const QString& btnname) 
	{ 
		QMessageBox::information(this, "Clicked", btnname + " is clicked!");//显示被按下的btn名称。
	}
```
从这个例子来看QSignalMapper的用法是非常简单的,也很容易理解。
- 首先把原始不带参数的信号连接到signalmapper的map槽函数， 这样signalmapper能在第一时间接收到原始信号； 
- 其次调用setMapper方法告诉signalmapper怎样去处理原始信号。 在这个例子中是把原始信号转化为一个带QString参数的信	号 
- 最后接收转化后的带参数信号， 这里所把转化后的信号与槽函数连接， 在槽函数中获得需要的数据。 

QSignalMapper类的功能核心是要建立一个从发出原始信号的object到需要的数据的映射（setMapper函数）， 如果你的程序恰巧	需要这样的功能，那么当然QSignalMapper就是当仁不让的最佳选择。 除了上述最常见的用法， 我们也来开动脑筋想想还有什	么别的场合适合使用这个类呢？ 

在Qt的examples里仅有一个例子用到了QSignalMapper这个类， 在examples/mainwindow/mdi/mainwindow.cpp里。 它的用法	是将QWidget指针作为参数， 然后菜单选中的信号映射到子Window的指针， 最终由QMainWindow来处理， 用于实现子窗口	的切换。 这个用法很有些意思， 可以说是QSignalMapper的最佳用例， 建议大家学习一下。 这里截取其中最核心的代码， 有	注释应该很好看懂吧， 如果还是有问题就留言： 



## `QByteArray`

用来存储新的bytes（包括‘\0’）和老的8位的’\0‘终端字符，当总是需要确保数据后面跟随‘\0’时，使用QByteArray比const char *更方便。主要是用来做深度的数据操作（连带'\0'一起复制，剪切等等...）

实例：
```c++
QByteArray ba("Hello");		//虽然它只有5个字母，但它还是包含了一个隐藏的'\0'
```



## `[static] QTextCodec *QTextCodec::codecForHtml(const QByteArray &ba)`

通过检查BOM (Byte Order Mark)和元素头包含的类型来查明HTML片段的编码，查不到就返回-1



## `canonicalFilePath()`

返回此抽象路径名的规范路径名字符串。
	
规范路径名是绝对路径名，并且是惟一的。规范路径名的准确定义与系统有关。如有必要，此方法首先将路径名转换为绝对路径名，这与调用 getAbsolutePath() 方法的效果一样，然后用与系统相关的方式将它映射到其惟一路径名。这通常涉及到从路径名中移除多余的名称（比如 "." 和 ".."）、解析符号连接（对于 UNIX 平台），以及将驱动器号转换为标准大小写形式（对于 Microsoft 	Windows 平台）。

每个表示现存文件或目录的路径名都有一个惟一的规范形式。每个表示不存在文件或目录的路径名也有一个惟一的规范形式。不存在文件或目录路径名的规范形式可能不同于创建文件或目录之后同一路径名的规范形式。同样，现存文件或目录路径名的规范	形式可能不同于删除文件或目录之后同一路径名的规范形式。



## `Qt中QFileDialog::getOpenFileName的用法（附如何支持带中文路径的读取）`

QFileDialog::getOpenFileName 函数含有六个参数:
```c++
QString QFileDialog::getOpenFileName (QWidget * parent = 0,
​	                                   const QString & caption = QString(),
    ​	                               const QString & dir = QString(), 
	                                  const QString & filter = QString(),
                        ​              QString * selectedFilter = 0,
                                    ​  Options options = 0 )
```
- 第一个参数parent，用于指定父组件。注意，很多Qt组件的构造函数都会有这么一个parent参数，并提供一个默认值0；在一般成员函数中写作this，但是要记住如果是在main函数中一定要写NULL。	
- 第二个参数caption，是对话框的标题。
​- 第三个参数dir，是对话框显示时默认打开的目录。"." 代表程序运行目录，"/" 代表当前盘符的根目录。如果不明确选择，只需要返回绝对路径也可以这样写QDir dir;     dir.absolutePath()。这个参数是最不好理解的。
​- 第四个参数filter，是对话框的后缀名过滤器。如果显示该目录下的全部文件可以“*.*”需要什么自己修改后面的*。
- 第五个参数selectedFilter，是默认选择的过滤器。
- 第六个参数options，是对话框的一些参数设定，比如只显示文件夹等等，它的取值是enum QFileDialog::Option，每个选项可以使用 | 运算组合起来。

第五、六个参数没有要求的话可以不写。
```c++
​QString filter;
filter = "Image file (*.*)";
QDir dir;
​r_fixedfilename = QFileDialog::getOpenFileName( NULL, QString("Load Image file supported by ITK Image Reader"), dir.absolutePath(), filter );
```
如何支持带中文路径的读取：
```c++
QByteArray file_mid = r_fixedfilename.toLocal8Bit(); 
fixedfilename = file_mid.data(); //r_fixedfilename接前面的例子
```



## `void QStatusBar::showMessage(const QString &message, int timeout = 0)`

用来隐藏正常的状态栏指示，显示给定的特定信息并持续timeout毫秒；如果timeout为默认值（0），则一直显示；



## `bool QString::endsWith(const QString &s, Qt::CaseSensitivity cs = Qt::CaseSensitive) const`

当它以QString类型的s结束时，返回true；
```c++
Qt::CaseSensitivity		//大小写敏感
```



## `[static] QColor QColorDialog::getColor(const QColor &initial = Qt::white, QWidget *parent = Q_NULLPTR, const QString &title = QString(), ColorDialogOptions options = ColorDialogOptions())`

出现一个颜色选择框，如果选择cancel则返回一个无效的颜色；



## `QSqlQueryModel `

是执行查询语句和横贯查询结果的高级接口，他是建立在低级的QsqlQuery 之上的，它可以直接给显示类提供数据如：QTableView
```c++
		QSqlQueryModel *model = new QSqlQueryModel;  
     	model->setQuery("SELECT name, salary FROM employee");  
     	model->setHeaderData(0, Qt::Horizontal, tr("Name"));//显示时的表头  
     	model->setHeaderData(1, Qt::Horizontal, tr("Salary"));  
	     QTableView *view = new QTableView;  
     	view->setModel(model);  
     	view->show();
```
当然QSqlQueryModel也能单独取回数据，不显示。
```c++
QSqlQueryModel model;  
model.setQuery("SELECT * FROM employee");  
int salary = model.record(4).value("salary").toInt();
```
有上面可得，得到的salary 是第4行第二列，故还以写成
```c++
int salary = model.data(model.index(4, 2)).toInt();  
```
QSqlQueryModel默认情况下只能读，如果想读写必须子类化它，并重新实先setData（）和flags()这两个函数或者用QSqlTableModel类，它提供读写模式，但它是基于单一表的。
	
QT qtcreator 自身提供了读写模式的范例Query Model Example，在example 中可以看到，用户可以自定义自己想要的数据显	示模式。
	
查询执行语句：
```c++
void QSqlQueryModel::setQuery ( const QString & query, const QSqlDatabase & db = QSqlDatabase() )
```
例
```c++
QSqlQueryModel model;  
model.setQuery("select * from MyTable");  
if (model.lastError().isValid())  
	qDebug() << model.lastError();
```
