# vim快捷键

<!-- vim-markdown-toc GFM -->

* [跳转操作](#跳转操作)
* [查找替换操作](#查找替换操作)
* [编辑操作](#编辑操作)
    - [一键删除指定元素及其后面的内容](#一键删除指定元素及其后面的内容)
* [窗口切换](#窗口切换)
* [辅助操作](#辅助操作)
* [文件操作](#文件操作)
* [第三方插件](#第三方插件)
    - [NerdTree](#nerdtree)
    - [YouCompleteMe](#youcompleteme)
    - [tagbar](#tagbar)
    - [fzf](#fzf)
    - [markdown-preview](#markdown-preview)

<!-- vim-markdown-toc -->



## 跳转操作

| 命令       | 说明                                | 命令       | 说明                   |
| ---------- | ----------------------------------- | ---------- | ---------------------- |
| `h`        | 向上                                | `j`        | 向下                   |
| `k`        | 向左                                | `l`        | 向右                   |
| `ctrl + e` | 移动页面                            |            |                        |
| `ctrl + f` | 上翻一页                            | `ctrl +b`  | 下翻一页               |
| `ctrl + u` | 上翻半页                            | `ctrl + d` | 下翻半页               |
| `$`        | 跳到行尾                            | `gg`       | 跳到第一行             |
| `G`        | 跳到最后一行                        | `5G`       | 跳到第五行             |
| `0`        | 跳到行首的第0个字符，不管有没有缩进 | `^`        | 跳到行首的第1个字符    |
| `w`        | 下一个单词第一个字符                | `W`        | 下一个长单词第一个字符 |
| `e`        | 下一个单词最后字符                  | `E`        | 下一个长单词最后字符   |
| `b`        | 跳到上一个字                        | `B`        | 跳到上一个字，长跳     |
| `ctrl + ]` | 跳到定义                            | `ctrl + o` | 跳回来                 |



## 查找替换操作 

| 命令                            | 说明                               | 命令                                        | 说明                                                     |
| ------------------------------- | ---------------------------------- | ------------------------------------------- | -------------------------------------------------------- |
| **`:vim /内容/ % | copen`**     | 只搜索当前文件                     | **`:vim /内容/ ** | copen`**                | 只搜索当前目录                                           |
| **`:vim /内容/ ../** | copen`** | 递归搜索上级目录                   | **`:vim /内容/ 路径1/** 路径2/** | copen`** | 搜索多个路径                                             |
| `;`                             | 重复上一个f命令                    |                                             |                                                          |
| `:%s/old/new/g`                 | 搜索整个文件，将所有的old替换为new | `:%s/old/new/gc`                            | 搜索整个文件，将所有的old替换为new，每次都要确认是否替换 |
| `/pattern`                      | 向后搜索字符串pattern              | `?pattern`                                  | 向前搜索字符串pattern                                    |
| `fa`                            | 在当前行中找a，找到就跳转至a的位置 | `:s/old/new/`                               | 当前行出现的第一个匹配                                   |
| `:s/old/new/`                   | 当前行所有匹配                     | `:%s/old/new/gc`                            | 搜索整个文件，将所有的old替换为new，每次都要确认是否替换 |



## 编辑操作 

| 命令  | 说明                               | 命令       | 说明                                 |
| ----- | ---------------------------------- | ---------- | ------------------------------------ |
| `yy`  | 复制一行                           | `d`        | 剪切                                 |
| `P`   | 粘贴到光标前                       | `p`        | 粘贴到光标后                         |
| `u`   | 撤销改动                           | `ctrl + r` | 重做                                 |
| `.`   | 重复上一个命令                     |            |                                      |
| `x`   | 删除当前光标下的字符               | `X`        | 删除当前光标左边的字符               |
| `diw` | 删除光标所在的单词，不包括空白字符 | `daw`      | 删除当前光标所在的单词，包括空白字符 |
| `dw`  | 删除一个字                         | `D`        | 删除到行尾的内容                     |
| `dd`  | 删除一行                           | `s`        | 修改一个字符                         |
| `i`   | 在光标之前插入                     | `a`        | 在光标之后插入                       |

### 一键删除指定元素及其后面的内容

一键删除`【`后面的内容，例：

```sh
%s/【.*//
```



## 窗口切换

| 命令            | 说明                                                         | 命令             | 说明                                                    |
| --------------- | ------------------------------------------------------------ | ---------------- | ------------------------------------------------------- |
| `ctrl+w h`      | 跳到左边的窗口                                               | `ctrl+w k`       | 跳到上边的窗口                                          |
| `ctrl+w l`      | 跳到右边的窗口                                               | `ctrl+w j`       | 跳到下边的窗口                                          |
| `:split 文件名` | 把当前窗口水平分割                                           | `:args`          | 显示当前编辑的文件                                      |
| `:next`         | 切换到下一个文件                                             | `:next!`         | 不保存当前文件就切换到下一个文件                        |
| `:wnetx`        | 保存当前文件并切换到下一个文件                               |                  |                                                         |
| `:prev`         | 切换到上一个文件                                             | `:prev!`         | 不保存当前文件就切换到上一个文件                        |
| `:wprev`        | 保存当前文件并切换到上一个文件                               |                  |                                                         |
| `:first`        | 定位首文件                                                   | `:last`          | 定位尾文件                                              |
| `:close`        | 关闭当前窗口                                                 | `:only`          | 只显示当前窗口，关闭所有其他的窗口                      |
| `:all`          | 打开所有的窗口                                               | `:qall`          | 退出所有窗口                                            |
| `:wall`         | 保存所有窗口                                                 |                  |                                                         |
| `:qall!`        | 退出所有窗口不保存                                           | `:wqall`         | 保存并退出所有窗口                                      |
| `:split 文件名` | 把当前窗口水平分割                                           | `:vsplit 文件名` | 把当前窗口垂直分割                                      |
| `ctrl+^`        | 快速在最近打开的两个文件间切换                               | `ctrl+w`         | 跳到最顶上的窗口                                        |
| `ctrl+w b`      | 跳到最底下的窗口                                             | `ctrl+w r`       | 向右或向下方交换窗口，`而Ctrl + w + R则和它方向相反.  ` |
| `ctrl+w x`      | 交换同列或同行的窗口的位置。vim默认交换当前窗口的与它下一个窗口的位置，如果下方没有 |                  |                                                         |



## 辅助操作 

| 命令   | 说明      | 命令    | 说明                      |
| ------ | --------- | ------- | ------------------------- |
| `:sh`  | 进入shell | `:term` | 进入shell(vim8及以上支持) |
| `gg=G` | 自动排版  |         |                           |



## 文件操作

| 命令          | 说明         | 命令         | 说明                      |
| ------------- | ------------ | ------------ | ------------------------- |
| `:pwd`        | 打印当前目录 | `:edit 文件` | 编辑文件,如果不存在就创建 |
| `:find文件名` | 查找文件     |              |                           |



## 第三方插件

### NerdTree

| 命令    | 说明                                | 命令    | 说明                                        |
| ------- | ----------------------------------- | ------- | ------------------------------------------- |
| `?`     | 帮助文档                            |         |                                             |
| `o`     | 打开目录                            | `go`    | 打开文件,光标留在NERDTree,创建的是buffer    |
| `t`     | 打开文件,创建的是tab                | `T`     | 打开文件,光标留在`NERDTree`,创建的是buffer  |
| `i`     | 水平分割创建文件的窗口              | `gi`    | 水平分割创建文件窗口,光标留在NERDTree       |
| `s`     | 垂直分割创建文件窗口,创建的是buffer | `gs`    | 垂直分割创建文件窗口,光标留在NERDTree       |
| `x`     | 收起当前打开的目录                  | `X`     | 收起所有打开的目录                          |
| `e`     | 以文集爱你管理的方式打开选中的目录  | `D`     | 删除书签                                    |
| `P`     | 跳转到当前根目录                    | `p`     | 跳转到上一级目录                            |
| `K`     | 跳转到第一个子路径                  | `J`     | 跳转到最后一个子路径                        |
| `<C-j>` | 在同级目录中向下                    | `<C-k>` | 在同级目录中向上                            |
| `C`     | 将根目录设置为光标所在的目录        |         |                                             |
| `u`     | 设置上级目录为根目录                | `U`     | 设置上级目录位根目录,维持原来目录的打开状态 |
| `r`     | 刷新光标所在的目录                  | `R`     | 刷新当前根路径                              |
| `l`     | 显示或不显示隐藏的文件              | `f`     | 打开或关闭文集爱你过滤器                    |
| `q`     | 关闭NERDTree                        | `A`     | 全屏幕显示NERDTree,或者关闭全屏             |

### YouCompleteMe

| 命令    | 说明     | 命令    | 说明     |
| ------- | -------- | ------- | -------- |
| `<C-j>` | 选下一个 | `<C-k>` | 选上一个 |
|         |          |         |          |
|         |          |         |          |

### tagbar

| 命令 | 说明 | 命令 | 说明 |
| ---- | ---- | ---- | ---- |
|      |      |      |      |

### fzf

| 命令 | 说明 | 命令 | 说明 |
| ---- | ---- | ---- | ---- |
|      |      |      |      |

### markdown-preview

| 命令 | 说明 | 命令 | 说明 |
| ---- | ---- | ---- | ---- |
|      |      |      |      |
