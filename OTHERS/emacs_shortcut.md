[进入Emacs]
- C-z 挂起Emacs
- C-x C-c 永久离开Emacs

[用方向键]
上一行 C-p 向左移 C-b  向右移 C-f  下一行 C-n

[文件]
- C-x C-f 读取文件
- C-x r 只读打开文件
- C-x C-q 清除一个窗口的只读属性
- C-x C-s 保存文件到磁盘
- C-x s 保存所有文件
- C-x i 插入其它文件的内容到当前缓冲
- C-x C-v 用将要读取的文件替换当前文件
- C-x C-w 将当前缓冲写入指定的文件

[错误恢复]
- C-g 取消当前要执行的命令
- M-x recover-file 恢复系统崩溃后丢失的文件
- C-x u或C-_ 撤销更新
- M-x revert-buffer 使缓冲回复到初始内容

[增量查找]
- C-s 向前查找
- C-r 向后查找
- C-M-s 规则表达式查找
- C-M-r 反向规则表达式查找
- M-p 选择前一个查找字符串
- M-n 选择下一个查找字符串
- RET 退出增量查找
- DEL(Backspace) 取消上一个字符的作用
- C-g 退出当前查找模式
可重复使用C-s和C-r来改变查找方向

[替换]
- M-% 交互式地替换一个文本串
- M-x replace-regexp 交互式地替换一个规则表达式
- SPE 替换当前的并移动到下一处
- , 替换当前的但不移动到下一处
- L(Backspace) 不替换当前的并移动到下一处
- ! 替换所有剩下的符合条件的文本
- RET 退出替换模式
- C-r 进入递归的编辑模式
- C-M-c 退出递归的编辑模式

[光标移动]
- C-f 向前一个字符
- C-b 向后一个字符
- M-f 向前一个字
- M-b 向后一个字
- C-p 向上一行
- C-n 向下一行
- C-a 到行首
- C-e 到行尾
- M-a 到句首
- M-e 到句尾
- M-{ 到段首
- M-} 到段尾
- C-x [ 到页首
- C-x ] 到页尾
- C-M-f 到表达式首部
- C-M-b 到表达式尾部
- M-< 到缓冲首部
- M-> 到缓冲尾部
- C-v 滚动到下一屏
- M-v 滚动到上一屏
- C-x < 滚动到右边一屏（内容向左移动）
- C-x > 滚动到左边一屏（内容向右移动）
- C-u C-l 滚动当前行到屏幕中央
- C-M-n 移到结尾的)、}或]
- C-M-p 移到开始的)、}或]
- C-M-u 向上移到父结构开始
- C-M-d 向下移到父结构开始

[复制、粘贴、剪切、删除]
- C-d 向前delete字符
- DEL(Backspace) 向后delete字符
- M-d 向前delete到字首
- M-DEL(Backspace) 向后delete到字尾
- M-0 C-k 向前delete到行首
- C-k 向后delete到行尾
- C-x DEL(Backspace) 向前delete到句首
- M-k 向后delete到句尾
- M-- C-M-k 向前delete到表达式首部
- C-M-k 向后delete到表达式尾部
- C-w Kill区域
- M-w 拷贝区域到Kill Ring
- M-z Kill到下一个给定字符出现的位置
- C-y 拉回（yank）上次kill的内容
- M-y 用更早kill的内容取代拉回的上次kill的内容

[标记Marking]
- C-SPC或C-@ 标记当前位置
- C-x C-x 以字符为单位使用移动命令动态标记区域
- M-@ 以字为单位使用移动命令动态标记区域
- M-h 标记一段
- C-x C-p 标记一页
- C-M-@ 标记一个表达式
- C-M-h 标记一个函数
- C-x h 标记整个缓冲区

[寄存器]
- C-x r s 存储区域到寄存器
- C-x r i 插入矩形内容到缓冲
- C-x r SPC 存储光标位置到寄存器
- C-x r j 跳跃到寄存器中存储的光标位置

[矩形]
- C-x r r 拷贝一个矩形到寄存器
- C-x r k Kill矩形
- C-x r y 拉回矩形
- C-x r o 打开一个矩形, 将文本移动至右边
- C-x r c 清空矩形
- C-x r t 为矩形中每一行加上一个字符串前缀
- C-x r i r 从r缓冲区内插入一个矩形

[标记Tags]
- M-. 查找标记
- C-u M-. 查找标记下一次出现的位置
- M-x visit-tags-table 指定一个新的标记文件
- M-x tags-search Regexp search on all files in tabs table
- M-x tags-query-replace 在所有文件中执行查询-替换
- M-, 继续进行上一次标记查找或查询-替换

[窗口与缓冲]
- C-x 1 删除所有其它窗口
- C-x 5 2
- C-x 2 上下分割当前窗口
- C-x 3 左右分割当前窗口
- C-x 5 0
- C-x 0 删除当前窗口
- C-M-v 滚动其它窗口
- C-x o 切换光标到另一个窗口
- C-x 4 b C-x 5 b 选择另一个窗口中的缓冲
- C-x 5 C-o
- C-x 4 C-o 显示另一个窗口中的缓冲
- C-x 5 f
- C-x 4 f 在另一窗口中查找并打开文件
- C-x 5 r
- C-x 4 r 在另一窗口中以只读方式打开文件
- C-x 5 d
- C-x 4 d 在另一窗口中运行dired命令
- C-x 5 .
- C-x 4 . 在另一窗口中查找tag
- C-x ^ 增加窗口高度
- C-x { 减小窗口宽度
- C-x } 增加窗口宽度
- C-x b 选择另一个缓冲
- C-x C-b 列出所有的缓冲
- C-x k Kill一个缓冲

[分栏编辑]
- C-x 6 2C-command
- C-x 6 s 2C-split
- C-x 6 b 2 C-associate-buffer
- C-x 6 2 2 C-two-columns

[格式]
- TAB 缩进当前行（与模式相关）
- C-M-\ 缩进区域（与模式相关）
- C-M-q 缩进表达式（与模式相关）
- C-x TAB Indent region rigidly arg. Columns
- C-o 在光标后插入一个新的行
- C-M-o 静态地将一行下移
- C-x C-o 删除光标附近的空行（留下一行）
- M-^ 与上一行合并成一行
- M- 删除光标附近的所有空格
- M-SPC 删除光标附近的空格（留下一格）
- M-q Fill paragraph
- C-x f Set fill column
- C-x . 设置每一行开始的前缀
- M-g 设置字体   
