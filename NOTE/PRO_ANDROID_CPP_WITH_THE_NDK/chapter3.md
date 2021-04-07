# 第三章 用JNI实现与原生代码通信

## 什么是JNI



## 以一个示例开始

### 原生方法的声明

使用native关键字声明原生方法。

### 加载共享库

提供2种方法加载共享库:

- load
- loadLibrary

### 实现原生方法

函数的显式命名可以让虚拟机在加载的共享库中自动查找原生函数。

1. c/c++头文件生成器: javah

   将java类解析成c++类文件，命令格式`javah -classpath java文件路径 java类名`例：

   ```sh
   javah -classpath bin/classes com.example.hellojni.HelloJni
   ```

2. 方法声明

   原生函数的声明格式`JNIEXPORT 返回值 JNICALL 函数名(JNIEnv*, jobject)`;

   - JNIEnv: 指向可用JNI函数表的接口指针，是线程-局部数据指针，无法缓存以及被其它线程使用。
   - jobject: 当前类实例的java对象引用



## 数据类型

### 基本数据类型

| Java类型 | JNI类型  | c/c++类型      | 大小       |
| -------- | -------- | -------------- | ---------- |
| Boolean  | Jblloean | unsigned char  | 无符号8位  |
| Byte     | Jbyte    | char           | 有符号8位  |
| Char     | Jchar    | unsigned short | 无符号16位 |
| Short    | Jshort   | short          | 有符号16位 |
| Int      | Jint     | int            | 有符号32位 |
| Long     | Jlong    | long long      | 有符号64位 |
| Float    | Jfloat   | float          | 32位       |
| Double   | Jdouble  | double         | 64位       |

### 引用类型

| java类型            | 原生类型      |
| ------------------- | ------------- |
| java.lang.Class     | jclass        |
| java.lang.Throwable | jthrowable    |
| Java.lang.String    | jstring       |
| Other objects       | jobjects      |
| java.lang.Object[]  | jobjectArray  |
| boolean[]           | jbooleanArray |
| byte[]              | jbyteArray    |
| char[]              | jcharArray    |
| short[]             | jshortArray   |
| int[]               | jintArray     |
| long[]              | jlongArray    |
| float[]             | jfloatArray   |
| double[]            | jdoubleArray  |
| other arrays        | Jarray        |



## 对引用数据类型的操作

引用类型以不透明的引用方式传递给原生代码，而不是以原生数据类型的形式，引用类型不能直接使用和修改。

### 字符串操作

JNI不提供任何修改字符串的函数，支持Unicode和UTF-8两种编码。例:

```c++
jstring javaString;
javaString = (*env)->NewStringUTF(env, "Hello World!");
```

java字符串转c++字符串函数

- Unicode: GetStringChars
- UTF-8: GetStringUTFChars

例:

```c++
const jbyte* str;
jboolean isCopy;
str = (*env)->GetStringUTFChars(env, javaString, &isCopy);
```

c++字符串使用完后要记得释放，否则会引起内存泄漏。

释放c++字符串

- Unicode: ReleaseStringChars
- UTF-8: ReleaseStringUTFChars

例:

```c++
(*env)->ReleaseStringUTFChars(env, javaString, str);
```

### 数组操作

使用`New+数组类型`的方法创建数组实例,例:

```c++
jintArray javaArray;
javaArray = (*env)->NewIntArray(env, 10);
```

2种访问java数组元素的方法:

- 将java数组复制成c++格式的数组
- JNI提供直接指向数组元素的指针

使用格式`Get+数组类型+Region`的方法复制java数组(数据量大时不推荐用)，例:

```c++
jint nativeArray[10];
(*env)->GetIntArrayRegion(env, javaArray, 0, 10, nativeArray);
```

使用格式`Get+数组类型+Elements`的方法获取指向数组元素的直接指针，例:

```c++
jint* nativeDirectArray;
jboolean isCopy;
nativeDirectArray = (*env)->GetIntArrayElements(env, javaArray, &isCopy);
```

使用格式`Release+数组类型+Elements`的方法来释放数组指针，不释放会出现内存溢出，例:

```c++
(*env)->ReleaseIntArrayElements(env, javaArray, nativeDirectArray, 0);
```

上面第四个参数指的是释放模式，释放模式列表如下:

| 释放模式   | 动作                                                         |
| ---------- | ------------------------------------------------------------ |
| 0          | 将内容复制回来并释放原生数组                                 |
| JNI_COMMIT | 将内容复制回来但不释放原生数组，一般用于周期性更行一个java数组 |
| JNI_ABORT  | 释放原生数组但不用将内容复制回来                             |

### NIO操作

创建字节缓冲区,例:

```c++
unsigned char* buffer = (unsigned char*) malloc(1024);
jobject directBuffer;
directBuffer = (*env)->NewDirectByteBuffer(env, buffer, 1024);
```

获取java的缓冲区,例:

```c++
unsigned char* buffer;
buffer = (unsigned char*) (*env)->GetDirectBufferAddress(env, directBuffer);
```

### 访问域

用对象引用获得类,例:

```c++
jclass clazz;
clazz = (*env)->GetObjectClass(env, instance);
```

- 实例域

```c++
jfieldID instanceFieldId;
instanceFieldId = (*env)->GetFieldID(env, clazz, "instanceField", "Ljava/lang/String;");
```

- 静态域

```c++
jfieldID staticFieldId;

```





