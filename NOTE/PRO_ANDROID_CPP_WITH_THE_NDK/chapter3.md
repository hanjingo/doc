# 第三章 用JNI实现与原生代码通信

摘要

- [什么是JNI](#什么是JNI)
- [以一个示例开始](#以一个示例开始)
  - [原生方法的声明](#原生方法的声明)
  - [加载共享库](#加载共享库)
  - [实现原生方法](#实现原生方法)
- [数据类型](#数据类型)
  - [基本数据类型](#基本数据类型)
  - [引用类型](#引用类型)
- [对引用数据类型的操作](#对引用数据类型的操作)
  - [字符串操作](#字符串操作)
  - [数组操作](#数组操作)
  - [NIO操作](#NIO操作)
  - [访问域](#访问域)
  - [调用方法](#调用方法)
  - [域和方法描述符](#域和方法描述符)
- [异常处理](#异常处理)
  - [捕获异常](#捕获异常)
  - [抛出异常](#抛出异常)
- [局部和全局引用](#局部和全局引用)
  - [局部引用](#局部引用)
  - [全局引用](#全局引用)
  - [弱全局引用](#弱全局引用)
- [线程](#线程)
  - [原生线程](#原生线程)



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

获得域id

```c++
jfieldID instanceFieldId;
instanceFieldId = (*env)->GetFieldID(env, clazz, "instanceField", "Ljava/lang/String;");
```

获得实例域

```c++
jstring instanceField;
instanceField = (*env)->GetObjectField(env, instance, instanceFieldId);
```

- 静态域

获得域id

```c++
jfieldID staticFieldId;
staticFieldId = (*env)->GetStaticFieldID(env, clazz, "staticField", "Ljava/lang/String;");
```

获得实例域

```c++
jstring staticField;
staticField = (*env)->GetStaticObjectField(env, clazz, staticFieldId);
```

### 调用方法

- 实例方法

获取方法id

```c++
jmethodID instanceMethodId;
instanceMethodId = (*env)->GetMethodID(env, clazz, "instanceMethod", "()Ljava/lang/String;");
```

调用方法

```c++
jstring instanceMethodResult;
instanceMethodResult = (*env)->CallStringMethod(env, instane, instanceMethodId);
```

- 静态方法

获取方法id

```c++
jmethodID staticMethodId;
staticMethodId = (*env)->GetStaticMethodID(env, clazz, "staticMethod", "()Ljava/lang/String;");
```

调用方法

```c++
jstring staticMethodResult;
staticMethodResult = (*env)->CallStaticStringMethod(env, clazz, staticMethodId);
```

### 域和方法描述符

获得域ID和方法ID分别需要域描述符和方法描述符，可以通过下表的java类型签名映射获得。

| Java类型              | 签名                  |
| --------------------- | --------------------- |
| Boolean               | Z                     |
| Byte                  | B                     |
| Char                  | C                     |
| Short                 | S                     |
| Int                   | I                     |
| Long                  | J                     |
| Float                 | F                     |
| Double                | D                     |
| fully-qualified-class | Fully-qualified-class |
| type[]                | [type                 |
| method type           | (arg-type)ret-type    |

反汇编程序: javap

通过命令格式 `javap -classpath java文件路径 -p -s java类` 进行反汇编，例：

```sh
javap -classpath bin/classes -p -s com.example.hellojni.HelloJni
```



## 异常处理

### 捕获异常

原生代码的异常处理,例:

```c++
jthrowable ex;
(*env)->CallVoidMethod(env, instance, throwingMethodId);
ex = (*env)->ExceptionOccurred(env);
if (0 != ex) {
  (*env)->ExceptionClear(env);
}
```

### 抛出异常

原生代码抛出异常,例：

```c++
jclass clazz;
clazz = (*env)->FindClass(env, "java/lang/NullPointerException");
if (0 != clazz) {
  (*env)->ThrowNew(env, clazz, "Exception message.");
}
```



## 局部和全局引用

### 局部引用

局部引用不能再后续的调用中被缓存以及重用，因为他们的使用期限仅限于原生方法，一旦原生函数返回，局部引用即被释放。

例：删除一个局部引用

```c++
jclass clazz;
clazz = (*env)->FindClass(env, "java/lang/String");
(*env)->DeleteLocalRef(env, clazz);
```

### 全局引用

在原生方法的后续调用过程中依然有效，不允许对象被垃圾回收，除非他们被原生代码显式释放。

创建全局引用

```c++
jclass localClazz;
jclass globalClazz;
localClazz = (*env)->FindClass(env, "java/lang/String");
globalClazz = (*env)->NewGlobalRef(env, localClazz);
```

删除全局引用

```c++
(*env)->DeleteGlobalRef(env, globalClazz);
```

### 弱全局引用

在原生方法的后续调用过程中依然有效，但并不阻止潜在的对象被垃圾回收

创建弱全局引用

```c++
jclass weakGlobalClazz;
weakGlobalClazz = (*env)->NewWeakGlobalRef(env, localClazz);
```

检查弱全局引用的有效性

```c++
if (JNI_FALSE == (*env)->IsSameObject(env, weakGlobalClazz, NULL)) {
  ...
}
```

删除弱全局引用

```c++
(*env)->DeleteWeakGlobalRef(env, weakGlobalClazz);
```



## 线程

JNI约束:

- 只在原生方法执行期间及正在执行原生方法的线程环境下局部引用是有效的，局部引用不能再多线程间共享，只有全局引用可以被多个线程共享。

- 被传递给每个原生方法的JNIEnv接口指针在与方法调用相关的线程中也是有效的，他不能被其它线程缓存或使用。

### 原生线程

线程的附着和分离

```c++
JavaVM* cacheJvm;
JNIEnv* env;
// 将当前线程附着到虚拟机
(*cachedJvm)->AttachCurrentThread(cachedJvm, &env, NULL);
// 可以用JNIEnv接口实现线程与Java应用程序的通信
...
// 将当前线程与虚拟机分离
(*cachedJvm)->DetachCurrentThread(cachedJvm);
```

