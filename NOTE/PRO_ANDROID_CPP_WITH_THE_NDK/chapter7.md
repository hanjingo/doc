# 第七章 原生线程

摘要:

- [创建线程示例项目](#创建线程示例项目)
  - [实现MainActivity](#实现MainActivity)
  - [生成C或C++头文件](#生成C或C++头文件)
  - [实现原生函数](#实现原生函数)
  - [更新Android。mk构建脚本](#更新Android_mk构建脚本)
- [Java线程](#Java线程)
  - [原生代码使用Java线程的优缺点](#原生代码使用Java线程的优缺点)
- [POSIX线程](#POSIX线程)
  - [在原生代码中使用POSIX线程](#在原生代码中使用POSIX线程)
  - [用pthread_create创建线程](#用pthread_create创建线程)
- [从POSIX线程返回结果](#从POSIX线程返回结果)
- [POSIX线程同步](#POSIX线程同步)
  - [用互斥锁同步POSIX线程](#用互斥锁同步POSIX线程)
  - [用信号量同步POSIX线程](#用信号量同步POSIX线程)
- [POSIX线程的优先级和调度策略](#POSIX线程的优先级和调度策略)
  - [POSIX的线程调度策略](#POSIX的线程调度策略)
  - [POSIX Thread优先级](#POSIXThread优先级)



## 创建线程示例项目

### 实现MainActivity

```java
// MainActivity.java

package com.apress.threads;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {
  private EditText threadsEdit;
  private EditText iterationEdit;
  private Button startButton;
  private TextView logView;
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
    
    // 初始化原生代码
    nativeInit();
    
    threadsEdit = (EditText) findViewById(R.id.threads_edit);
    iterationsEdit = (EditText) findViewById(R.id.iterations_edit);
    startButton = (Button) findViewById(R.id.start_button);
    logView = (TextView) findViewById(R.id.log_view);
    
    startButton.setOnClickListener(new OnClickListener() {
      public void onClick(View view) {
        int threads = getNumber(threadsEdit, 0);
        int iterations = getNumber(iterationsEdit, 0);
        if (threads > 0 && iterations > 0) {
          startThreads(threads, iterations);
        }
      }
    });
  }
  
  protected void onDestroy() {
    // 释放原生资源
    nativeFree();
    super.onDestroy();
  }
  
  // 原生消息回调
  private void onNativeMessage(final String message) {
    runOnUiThread(new Runnable() {
      public void run() {
        logView.append(message);
        logView.append("\n");
      }
    });
  }
  
  // 以integer格式获取编辑文本的值。如果值为empty或计数不能分析，则返回默认值
  private static int getNumber(EditText editText, int defaultValue) {
    int value;
    try {
      value = Integer.parseInt(editText.getText().toString());
    } catch (NumberFormatException e) {
      value = defaultValue;
    }
    return value;
  }
  
  // 启动给定个数的线程进行迭代
  private void startThreads(int threads, int iterations) {
    // javaThreads(threads, iterations);
    posixThreads(threads, iterations);
  }
  // 初始化原生代码
  private native void nativeInit();
  // 释放原生资源
  private native void nativeFree();
  // 原生worker
  private native void nativeWorker(int id, int iterations);
  
  static {
    System.loadLibrary("Threads");
  }
  
  // 使用基于Java的线程
  private void javaThreads(int threads, final int iterations) {
    // 为每一个worker创建一个基于Java的线程
    for (int i = 0; i < threads; i++) {
      final int id = i;
      Thread thread = new Thread() {
        public void run() {
          nativeWorker(id, iterations);
        }
      };
      thread.start();
    }
  }
  
  // 使用POSIX线程
  private native void posixThreads(int threads, int iterations);
}
```

### 生成C或C++头文件

```c++
// com_apress_threads_MainActivity.h

#include <jni.h>

JNIEXPORT void JNICALL Java_com_apress_threads_MainActivity_nativeInit(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_apress_threads_MainActivity_nativeFree(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_apress_threads_MainActivity_nativeWorker(JNIEnv *, jobject, jint, jint);

JNIEXPORT void JNICALL Java_com_apress_threads_MainActivity_posixThreads(JNIEnv *, jobject, jint, jint);
```

### 实现原生函数

```c++
// com_appress_threads_MainActivity.cpp

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "com_apress_threads_MainActivity.h"

// 原生worker线程参数
struct NativeWorkerArgs
{
  jint id;
  jint iterations;
};

// 方法ID能被缓存
static jmethodID gOnNativeMessage = NULL;

// Java虚拟机接口指针
static JavaVM* gVm = NULL;

// 对象的全局引用
static jobject gObj = NULL;

// 互斥实例
static pthread_mutex_t mutex;

// JNI OnLoad函数存储Java虚拟机接口指针
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
  // 缓存Java虚拟机接口指针
  gVm = vm;
  return JNI_VERSION_1_4;
}

void Java_com_apress_threads_MainActivity_nativeInit (
	JNIEnv* env,
  jobject obj)
{
  // 初始化互斥量
  if (0 != pthread_mutex_init(&mutex))
  {
    // 获取异常类
    jclass exceptionClazz = env->FindClass(
    	"java/lang/RuntimeException");
    
    // 抛出异常
    env->ThrowNew(exceptionClazz, "Unable to initialize mutex");
    goto exit;
  }
  
  // 如果对象的全局引用未设置
  if (NULL = gObj)
  {
    // 为对象创建一个新的全局引用
    gObj = env->NewGlobalRef(obj);
    
    if (NULL == gObj)
    {
      goto exit;
    }
  }
  
  // 如果方法ID没被缓存
  if (NULL == gOnNativeMessage)
  {
  	// 从对象中获取类
    jclass clazz = env->GetObjectClass(obj);
    // 为回调获取方法ID
    gOnNativeMessage = env->GetMethodID(clazz,
    	"onNativeMessage", "(Ljava/lang/String;)V");
    // 如果方法没有找到
    if (NULL == gOnNativeMessage)
    {
      // 获取异常类
      jclass exceptionClazz = env->FindClass(
      	"java/lang/RuntimeException");
      // 抛出异常
      env->ThrowNew(exceptionClazz, "Unable to find method");
    }
  }
  
exit:
  return;
}

void Java_com_appress_threads_MainActivity_nativeFree (
	JNIEnv* env,
	jobject obj)
{
  // 如果对象的全局引用未设置
  if (NULL != gObj)
  {
    // 删除全局引用
    env->DeleteGlobalRef(gObj);
    gObj = NULL;
  }
  
  // 销毁互斥量
  if (0 != pthread_mutex_destroy(&mutex))
  {
    // 获取异常类
    jclass exceptionClazz = env->FindClass(
    	"java/lang/RuntimeException");
    // 抛出异常
    env->ThrowNew(exceptionClazz, "Unable to destroy mutex");
  }
}

void Java_com_apress_threads_MainActivity_nativeWorker (
	JNIEnv* env,
	jobject obj,
	jint id,
	jint iterations)
{
  // 锁定
  if (0 != pthread_mutex_lock(&mutex))
  {
    // 获得异常类
    jclass exceptionClazz = env->FindClass(
    	"java/lang/RuntimeException");
    // 抛出异常
    env->ThrowNew(exceptionClazz, "Unable to lock mutex");
    goto exit;
  }
  
  // 循环给定的迭代数
  for (jint i = 0; i < iterations; i++)
  {
    // 准备消息
    char message[26];
    sprintf(message, "Worker %d: Iteration %d", id, i);
    
    // 来自c字符串的消息
    jstring messageString = env->NewStringUTF(message);
    
    // 调用原生消息方法
    env->CallVoidMethod(obj, gOnNativeMessage, messageString);
    
    // 检查是否产生异常
    if (NULL != env->ExceptionOccurred())
      break;
    
    // 睡眠一秒
    sleep(1);
  }
  
  // 解锁
  if (0 != pthread_mutex_unlock(&mutex))
  {
    // 获得异常类
    jclass exceptionClazz = env->FindClass(
    	"java/lang/RuntimeException");
    // 抛出异常
    env->ThrowNew(exceptionClazz, "Unable to unlock mutex");
  }
  
exit:
  return;
}

static void* nativeWorkerThread (void* args)
{
  JNIEnv* env = NULL;
  
  if (0 == gVm->AttachCurrentThread(&env, NULL))
  {
    // 获取原生worker线程参数
    NativeWorkerArgs* nativeWorkerArgs = (NativeWorkerArgs*) args;
    
    // 在线程上下文中运行原生worker
    Java_com_apress_threads_MainActvity_nativeWorker(env, gObj, 
    	nativeWorkerArgs->id, nativeWorkerArgs->iterations);
    
    // 释放原生worker线程参数
    delete nativeWorkerArgs;
    
    // 从Java虚拟机中分离当前线程
    gVm->DetachCurrentThread();
  }
  return (void*) 1;
}

void Java_com_apress_threads_MainActivity_posixThreads (
	JNIEnv* env, jobject obj, jint threads, jint iterations)
{
  // 线程句柄
  pthread_t* handles = new pthread_t[threads];
  
  // 为每一个worker创建一个POSIX线程
  for (jint i = 0; i < threads; i++)
  {
    // 原生worker线程参数
    NativeWorkerArgs* nativeWorkerArgs = new NativeWorkerArgs();
    nativeWorkerArgs->id = i;
    nativeWorkerArgs->iterations = iterations;
    
    // 创建一个新线程
    int result = pthread_create(&handles[i], NULL, nativeWorkerThread,
                                (void*) nativeWorkerArgs);
    
    if (0 != result)
    {
      // 获取异常类
      jclass exceptionClazz = env->FindClass("java/lang/RuntimeException");
      // 抛出异常
      env->ThrowNew(exceptionClazz, "Unable to create thread");
    }
  }
  
  // 等待线程终止
  for (jint i = 0; i < threads; i++)
  {
    void* result = NULL;
    
    // 连接每个线程句柄
    if (0 != pthread_join(handles[i], &result))
    {
      // 获取异常类
      jclass exceptionClazz = env->FindClass(
      	"java/lang/RuntimeException");
      // 抛出异常
      env->ThrowNew(exceptionClazz, "Unable to join thread");
    }
    else
    {
      // 准备message
      char message[26];
      sprintf(message, "Worker %d returned %d", i, result);
      
      // 来自c字符串的message
      jstring messageString = env->NewStringUTF(message);
      
      // 调用原生消息方法
      env->CallVoidMethod(obj, gOnNativeMessage, messageString);
      
      // 检查是否产生异常
      if (NULL != env->ExceptionOccurred())
      {
        goto exit;
      }
    }
  }
  
exit:
  return;
}
```

### 更新Android_mk构建脚本

```mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := Threads
LOCAL_SRC_FILES := com_apress_threads_MainActivity.cpp

include $(BUILD_SHARED_LIBRARY)
```



## Java线程

### 原生代码使用Java线程的优缺点

优点:

- 更容易建立
- 原生代码不要求做任何修改
- 因为Java线程已经是Java平台的一部分，所以不要求显式地附着到虚拟机上。原生代码可以用提供的线程专用JNIEnv接口指针与Java代码通信
- 通过java.lang.Thread类提供的方法可以用于与Java代码中的线程实例无缝交互

缺点:

- 因为原生空间中没有创建Java线程的API，所以假设为线程分配任务的逻辑是Java代码的一部分
- 因为基于Java的线程对原生代码是透明的，所以假定原生代码是线程安全的
- 原生代码不能获益于其它并发程序的概念或组件，例如信号量等，因为原生空间中没有可供java线程使用的相应API
- 在不同的线程中运行的原生代码不能通信或直接共享资源



## POSIX线程

### 在原生代码中使用POSIX线程

要使用POSIX线程库，需要导入头文件 `pthread.h`

### 用pthread_create创建线程

- `int pthread_create(pthread_t* thread, pthread_attr_t const* attr, void* (*start_routine)(void*), void* arg)` 创建POSIX线程
  - thread: 返回新线程的句柄
  - attr: 用来指定新线程的属性，如：栈基址，栈大小，守护大小，调度策略和调度优先级等。
  - start_routine: 线程函数的函数指针
  - arg: 参数



## 从POSIX线程返回结果

- `int pthread_join(pthread_t thread, vooid** ret_val)` 等待线程执行后返回
  - thread: 线程句柄
  - ret_val: 返回值，指向空指针



## POSIX线程同步

- Mutexes(互斥锁): 确保代码的互斥执行。
- Semaphores(信号量): 控制对特定树木可用资源的访问，如果没有可用资源，等待。

### 用互斥锁同步POSIX线程

- `int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr)` 初始化互斥锁
  - mutex: 指向互斥量的指针
  - attr: 互斥量属性

- `int pthread_mutex_lock(pthread_mutex_t* mutex)` 锁定已初始化的互斥量
  - mutex: 指向互斥量的指针

- `int pthread_mutex_unlock(pthread_mutex_t* mutex)` 解锁互斥量
  - mutex: 指向互斥量的指针

- `int pthread_mutex_destroy(pthread_mutex_t* mutex)` 销毁互斥量
  - mutex: 指向互斥量的指针

### 用信号量同步POSIX线程

- `extern int sem_init(sem_t* sem, int pshared, unsigned int value)` 初始化信号量

  - sem: 指向信号量的指针
  - pshared: 共享标志
  - value: 初始值

- `extern int sem_wait(sem_t* sem)` 锁定信号量

  - sem: 指向信号量的指针

  如果信号量的值大于0，上锁成功，信号量值-1。

  如果信号量的值等于0，线程被挂起。

- `extern int sem_post(sem_t* sem)` 解锁信号量

  - sem: 指向信号量的指针

  解锁成功: 信号量值+1

- `extern int sem_destroy(sem_t* sem)` 销毁信号量



## POSIX线程的优先级和调度策略

### POSIX的线程调度策略

常用的调度策略:

- SCHED_FIFO: 先进先出调度策略基于线程进入列表的时间对线程进行排序，也可以基于优先级在列表中移动线程。
- SCHED_RR: 循环轮转调度策略是线程执行时间加以限制的SCHED_FIFO，其目的是避免线程独占可用的CPU时间。

调度策略定义在sched.h中，有以下方法修改调度策略:

- 调用pthread_create创建线程时，用线程属性pthread_attr_t.sched_policy来定义调度策略
- `int pthread_setschedparam(pthread_t thid, int poilcy, struct sched_param const* param)` 定义调度策略
  - thid: 指向线程句柄的指针
  - poilcy: 调度策略
  - param: 调度策略所需要的参数

### POSIXThread优先级

POSIX Thread API提供基于调度策略调整线程优先级的方法:

- 调用pthread_create穿件线程时，用线程属性pthread_attr_t.sched_priority来定义调度策略
- `pthread_setschedparam` 在sched_param结构体中提供优先级

使用以下函数查看调度策略:

- `sched_get_priority_max`
- `sched_get_priority_min`

