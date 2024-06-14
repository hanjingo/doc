# 软件开发流程

<!-- vim-markdown-toc GFM -->

* [需求分析](#需求分析)
* [立项](#立项)
* [开发](#开发)
    - [测试](#测试)
    - [CodeReview](#codereview)
    - [CI/CD](#cicd)
    - [版本管理](#版本管理)
* [打包](#打包)
    - [静态编译](#静态编译)
    - [动态编译](#动态编译)
    - [依赖分析](#依赖分析)
        + [Dependency Walker工具](#dependency-walker工具)
    - [依赖处理](#依赖处理)
        + [Qt工具](#qt工具)
    - [打包封装](#打包封装)
        + [NSIS工具](#nsis工具)
* [发布](#发布)
* [反馈](#反馈)
* [升级](#升级)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 需求分析

TODO

---



## 立项

TODO

---



## 开发

### 测试

具体见：[软件测试](software_test.md)。

### CodeReview

TODO

### CI/CD

TODO

### 版本管理

TODO

### 崩溃捕捉

breakpad/crashpad

TODO

---



## 打包

### 静态编译

TODO

### 动态编译

TODO

### 编译加速

IncrediBuild

TODO

### 依赖分析

#### Dependency Walker工具

TODO

### 依赖处理

#### Qt工具

Qt推荐使用`windeployqt`工具来打包依赖。

例：

- 打包QWidgets

  ```sh
  windeployqt xx.exe  # xx 可执行程序名
  ```

- 打包QML

  ```sh
  windeployqt xx.exe --qmldir xxx  # xx 可执行程序名，xxx qml安装目录
  ```

**注意1：QT运行时需要用到一些系统依赖库（使用windeployqt工具生成在\platforms目录下），如果放置在其它位置，需要设置系统环境变量：QT_PLUGIN_PATH=platforms的上层目录。**

### 打包封装

#### NSIS工具

NSIS是由开发WinAMP的公司制作的打包工具，使用NSIS的打包流程如下：

1. 安装`NSIS`和脚本编辑器`HM NIS Edit`；

   NSIS：`https://nsis.sourceforge.io/Download`

   NSISEDIT：`http://hmne.sourceforge.net/`

2. 打开`HM NIS Edit`，点击`新建脚本:向导`；

3. 在"NSIS脚本向导"界面填入相应信息，保存打包脚本（*.nsi, *.nsh, ...）；

4. 编辑nsi脚本；

   | 常量       | 说明                 |
   | ---------- | -------------------- |
   | InstallDir | 程序的默认安装路径。 |
   | OutFile    | 生成的打包程序名。   |

5. 选择"编译脚本"，完成编译；

6. 完成。

注意：

1. 打包后如果程序安装在系统目录，可能会遇到权限问题；可通过使用插件：AccessControl来修改文件权限，参考：https://blog.csdn.net/wyw0000/article/details/130940479

---



## 发布

TODO

---



## 反馈

TODO

---



## 升级

TODO

---



## 参考

- [使用NSIS打包程序](https://zhuanlan.zhihu.com/p/144079072)
- [nsis制作windows安装包-修改安装目录读写权限](https://blog.csdn.net/wyw0000/article/details/130940479)
- [Qt应用打包发布，部署真正的Qt程序Linux&Windows](https://www.jianshu.com/p/3822addbf096?u_atoken=3ea4540e-7e56-4434-bdda-ffee6a13bbde&u_asession=01lfkJPHmquz4yWlkrJd9RnR-xPkMeq3-6wI7EMOK_uq-FTwafr4pFbNDg5sB2mGNeX0KNBwm7Lovlpxjd_P_q4JsKWYrT3W_NKPr8w6oU7K_BD-OyU7upKs7s6-2fKDBqK1h9zIJGqUc2hCV04v6XLWBkFo3NEHBv0PZUm6pbxQU&u_asig=05QQGENPHj3y0qRSj9RI0Xfq1nJH53GHjAkSXx36L4i7-BoQ3D9UPwSEMRh9ZcrIMc4ruywSmutjBQCF-LRWlJeKogHYT_JOCqt9Ta9vk-PylooRqt7VSOrtNH7qyFrp3T_VEGbYZ2rlDw4P411cQEfZnrQk8hQVX_5xsVJeWXpjH9JS7q8ZD7Xtz2Ly-b0kmuyAKRFSVJkkdwVUnyHAIJzfllwJ0JjoKeTFJQi4ILT2hm_Kqn1m0z57U51OSiJyvxn3URtWYq5VQe2s5Xl6Zn2u3h9VXwMyh6PgyDIVSG1W86WMJNItsIFfq0VbYDx1m-GVjuvW8Mbnw36tryIj0GRs1up2ljDTFMirZ8nF_FO7KA0a_HbABeZOL0rfsv7BP8mWspDxyAEEo4kbsryBKb9Q&u_aref=bshiuf1dzl%2BMf%2Bb7xX10dMDL2zA%3D)
