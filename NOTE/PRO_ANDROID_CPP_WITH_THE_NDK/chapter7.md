# 第七章 原生线程

摘要:



## 创建线程示例项目

### 创建Android项目

### 添加原生支持

### 声明字符串资源

### 创建简单的用户界面

### 实现Main Activity

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
    // todo
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
}
```

### 生成C/C++头文件

```c++
// com_apress_threads_MainActivity.h

#include <jni.h>

JNIEXPORT void JNICALL Java_com_apress_threads_MainActivity_nativeInit(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_apress_threads_MainActivity_nativeFree(JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_apress_threads_MainActivity_nativeWorker(JNIEnv *, jobject, jint, jint);
```

### 实现原生函数

```c++
// com_appress_threads_MainActivity.cpp

#include <stdio.h>
#include <unistd.h>

#include "com_apress_threads_MainActivity.h"

// 方法ID能被缓存
static jmethodID gOnNativeMessage = NULL;

void Java_com_apres_threads_MainActivity_nativeInit (
	JNIEnv* env,
  jobject obj)
{
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
}

void Java_com_appress_threads_MainActivity_nativeFree (
	JNIEnv* env,
	jobject obj)
{}

void Java_com_apress_threads_MainActivity_nativeWorker (
	JNIEnv* env,
	jobject obj,
	jint id,
	jint iterations)
{
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
}
```

