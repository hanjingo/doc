# 第八章 POSIX Socket API 面向连接的通信



## Echo_Socket示例应用

### 抽象echo_activity

```java
package com.apress.echo;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;

// 抽象echo activity对象
public abstract class AbstractEchoActivity extends Activity implements OnClickListener {
  // 端口号
  protected EditText portEdit;
  // 服务按钮
  protected Button startButton;
  // 日志滚动
  protected ScrollView logScroll;
  // 日志视图
  protected TextView logView;
  // 布局ID
  private final int layoutID;
  // 构造函数
  public AbstractEchoActivity(int layoutID) {
    this.layoutID = layoutID;
  }
  
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(layoutID);
    
    portEdit = (EditText) findViewById(R.id.port_edit);
    startButton = (Button) findViewById(R.id.start_button);
    logScroll = (ScrollView) findViewById(R.id.log_scroll);
    logView = (TextView) findViewById(R.id.log_view);
    
    startButton.setOnClickListener(this);
  }
  
  public void onClick(View view) {
    if (view == startButton) {
      onStartButtonClicked();
    }
  }
  
  // 在开始按钮上单击
  protected abstract void onStartButtonClicked();
  
  // 以整型获取端口号
  protected Integer getPort() {
    Integer port;
    
    try {
      port = Integer.valueOf(portEdit.getText().toString());
    } catch (NumberFormatException e) {
      port = null;
    }
    
    return port;
  }
  
  // 记录给定的消息
  protected void logMessage(final String message) {
    runOnUiThread(new Runnable() {
      public void run() {
        logMessageDirect(message);
      }
    });
  }
  
  // 直接记录给定的消息
  protected void logMessageDirect(final String message) {
    logView.append(message);
    logView.append("\n");
    logScroll.fullScroll(View.FOCUS_DOWN);
  }
  
  // 抽象异步echo任务
  protected abstract class AbstractEchoTask extends Threads {
    // Handler对象
    private final Handler handler;
    // 构造函数
    public AbstractEchoTask() {
      handler = new Handler();
    }
    // 在调用线程中先执行回调
    protected void onPreExecute() {
      startButton.setEnabled(false);
      logView.setText("");
    }
    
    public synchronized void start() {
      onPreExecute();
      super.start();
    }
    
    public void run() {
      onBackground();
      handler.post(new Runnable() {
        public void run() {
          onPostExecute();
        }
      });
    }
    
    // 新线程中的背景回调
    protected abstract void onBackground();
    
    // 在调用线程中后执行回调
    protected void onPostExecute() {
      startButton.setEnabled(true);
    }
  }
  
  static {
    System.loadLibrary("Echo");
  }
}
```

