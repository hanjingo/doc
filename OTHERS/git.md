# git指南

[TOC]



## git命令

| 命令            | 参数                                                         | 例子                                                         |
| --------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `add`           |                                                              | `git add file1`添加文件file1                                 |
| `branch`        | `-a`列出所有分支<br>`-d`删除分支<br>`-D`删除分支（强制）<br>`-m`重命名分支<br>`-M`重命名分支（强制）<br>--set-upstream-to 本地关联远程分支<br> | `git branch`列出所有**本地**分支<br>`git branch -a`列出所有分支<br>`git branch -d branchName`删除本地分支branchName，如果分支没有被合并会删除失败<br>`git branch -D branchName`删除分支branchName，即使分支没有被合并也删除<br>`git branch -m oldName newName`重命名本地分支oldName为newName，如果newName已存在，跳过<br>`git branch --set-upstream-to=origin/dev dev` 将本地分支dev与远程分支dev关联 |
| `checkout`      | `-b` 创建新分支                                              | `git checkout master`切换到master分支<br>`git checkout -b mybranch`创建一个名叫mybranch<br>`git checkout -b branchName tagName`基于标签"tagName"创建一个名叫"branchName"的分支<br>`git checkout -- file`撤销**未提交的**文件file1的修改 |
| `clone`         |                                                              | `git clone xxx.git`克隆`xxx`项目<br>`git clone xxx.git ~/src` 克隆`xxx`项目到`~/src` |
| `commit`        | `-m` 提交注释<br>`-amend`修改提交信息                        | `git commit` 提交详细注释<br>`git commit -m "memo"`提交简略注释memo<br>`git commit -C head -a --amend`增补提交，不会产生新的提交记录<br>`git commit -amend`启动编辑器（默认vim），修改提交信息 |
| `config`        | `-t` <br>`-C`<br>`--global`                                  | `git config --global user.name "name"`设置git的用户名为"name"<br>`git config --global user.email "xxx@xxx"`设置git邮箱为"xxx@xxx" |
| `count-objects` | `-v`<br>`-H`                                                 | `git count-objects -vH`统计当前仓库占用的空间大小            |
| `diff`          | `--cached`<br>`--staged`                                     | `git diff` 查看当前工作树与暂存区的差别<br>`git diff HEAD` 查看与最新提交的差别 |
| `fetch`         |                                                              |                                                              |
| `init`          |                                                              | `git init` 初始化当前仓库                                    |
| `log`           | `-m`<br>`-n` 显示前n条<br>`-p` 显示提交差异<br>`--stat` 显示简要统计信息<br/>`--author` 指定作者<br/>`--committer` 指定提交者<br/>`--name-only` 仅在提交信息后显示已修改的文件清单<br/>`--grep` 指定关键字<br/>`--since` 指定时间之后的日志<br/>`--after` 指定时间之前的日志<br/>`--graph` 以ASCII图形显示日志<br/>`--pretty=` 格式如下：<br/>   `%H` 提交的完整哈希值<br/>   `%h` 提交的简写哈希值<br/>   `%T 树的完整哈希值`<br/>   `%t` 树的简写哈希值<br/>   `%P` 父提交的完整哈希值<br/>   `%p` 父提交的简写哈希值<br/>   `%an` 作者名字<br/>   `%ae` 作者的电子邮件地址<br/>   `%ad` 作者修订日期<br/>   `%ar` 作者修订日期，按多久以前的方式显示<br/>   `%cn` 提交者的名字<br/>   `%ce` 提交者的电子邮件地址<br/>   `%cd` 提交日期<br/>   `%cr` 提交日期（距今多长时间）<br/>   `%s` 提交说明 | `git xx.md` 查看文件xx.md的日志<br>`git log -10`显示前10条日志<br>`git log -p xx.md` 显示文件xx.md提交前后的差别<br>`git log -p -2`显示最近2次的提交差异<br>`git log --pretty="%an--%s"`显示日志的作者信息和提交说明 |
| `merge`         | `--no-ff`记录下本次分支合并                                  | `git merge branchName`合并分支branchName到当前分支<br>`git checkout xxx && git merge master` 将master更新合并到分支xxx |
| `push`          | `-u ` 推送的同时，将远程分支设为当前分支的upstream           | `git push origin xxx`把分支xxx推送到远程分支<br>`git push --delete origin xxx`删除远程仓库的xxx分支 |
| `pull`          |                                                              |                                                              |
| `rebase`        | `-i` 压缩历史记录                                            | `git rebase -i HEAD-2`选定包含HEAD在内的2个最新历史记录      |
| `remote`        | `-v` 查看远程仓库信息<br>`add` 添加别名                      | `git remote add name xxx.git`为远程版本库xxx.git添加别名name<br>`git remote rm name`删除别名name<br>`git remote -v` 查看远程仓库信息 |
| `reflog`        | `--date`                                                     | `git reflog --date=local | grep branchName`查看分支branchName是从哪里切过来的 |
| `reset`         | `--hard` 强制重置                                            | `git reset HEAD file1`取消文件file1的暂存<br>`git reset --hard HEAD`同时取消工作区与暂存区的修改（**慎用**） |
| `revert`        |                                                              |                                                              |
| `rm`            | `-r`                                                         | `git rm fileName`删除文件fileName<br>`git rm -r dir`递归删除目录dir下的所有文件 |
| `status`        |                                                              | `git status`查看当前版本状态                                 |
| `submodule`     |                                                              | `git submodule init`初始化子模块<br>`git submodule update`更新子模块<br>`git submodule foreach git pull`拉取所有子模块<br>`git submodule update --init --recursive`拉取和更新所有子模块 |
| `tag`           | `-a` 添加标签<br>`-d` 删除tag<br>`-m`                        | `git tag`查看tag信息<br>`git tag tagName`给当前分支的最近一次提交创建标签<br>`git tag -a tagName commitId`给commitId的提交添加标签tagName<br>`git tag -d tagName`删除tag名为tagName的标签 |

---



## 环境配置

### 配置信息

```sh
ssh-keygen -t rsa -C "xxx@xxx"
git config --global user.name "name" # 设置git的用户名为"name"
git config --global user.email "xxx@xxx" # 设置git邮箱为"xxx@xxx"
```

### 初始化git

```sh
git init
```

### 设置代理与取消

```shell
# 设置http/https代理
git config --global http.proxy 'x.x.x.x:x' # x.x.x.x:x 这里填提供代理的 IP:port
git config --global https.proxy 'x.x.x.x:x' # x.x.x.x:x 这里填提供代理的 IP:port

# 取消http/https代理
git config --global --unset http.proxy
git config --global --unset https.proxy

# 设置ssh代理（需要安装nc工具）
echo -e 'Host github.com\n    User git\n    ProxyCommand nc -v -x 127.0.0.1:7890 %h %p\n' >> ~/.ssh/config # 127.0.0.1:7890这里修改为提供代理服务的IP:port
```

---



## commit规范

### angular规范

```git
<type>(<scope>): <subject>
// 空一行
<body>
// 空一行
<footer>
```

**Header**

包括3个字段：type(必需), scope(可选)， subject(必需)

1. type

   用于说明commit类别,只允许使用下面7个标识

   - **feat**         添加新特性
   - **fix**            修复bug
   - **docs**        文档
   - **style**       格式
   - **refactor** 重构
   - **test**         增加测试
   - **chore**      构建过程或辅助工具的变动

   如果type为feat和fix，则该commit将肯定出现在Change log之中；其他情况(docs, chore, style, refactor, test)由用户决定。

2. scope

   用于说明commit影响的范围，比如：数据层，控制层，视图层等等

3. subject

   简短描述，不超过50个字符，规则如下：

   - 以动词开头，使用第一人称现在时，比如change，而不是changed或changes
   - 第一个字母小写
   - 结尾不加句号（。）

**Body**

对本次commit的详细描述，可以分成多行。

 注意：

1. 使用第一人称现在时，比如使用change而不是changed或changes。
2. 应该说明代码变动的动机，以及与以前行为的对比。

**Footer**

Footer只用于2种情况：

1. 不兼容变动

   如果当前代码与上一个版本不兼容，则Footer部分以BREAKING CHANGE开头，后面是对变动的描述，以及变动理由和迁移方法。

2. 关闭Issue

   如果当前commit针对某个issue，那么可以在Footer部分关闭这个issue。也可以一次关闭多个issue。

---



## 如何给开源项目提交代码

2. 切换到远程库的分支（这里使用master）

   ```sh
   git checkout master
   ```

3. 基于远程分支新建自己的分支

   ```sh
   git checkout -b 我们的分支名
   ```

4. 在github上`fork`下这个项目（按`fork按钮`）

5. 提交我们的更改到我们`fork`的项目地址

   ```sh
   git remote add upstream 我们fork到的地址
   ```

6. 推送

   ```sh
   git fetch origin
   git merge 我们的分支名
   git push upstream 我们的分支名
   ```

7. 在github上点击`create pull request`

---



## 常用命令

### 子模块

#### 添加子模块

```shell
git submodule add -b 分支 --name 子模块名(不填默认) ssh地址 模块路径
```

#### 拉取子模块更新
1. 方法一:
```shell
git submodule init
git submodule update
```

2. 方法二:
```shell
git submodule update --init --recursive
```

#### 删除子模块
~~1. rm -rf 子模块目录 删除子模块目录及源码~~
~~2. vi .gitmodules 删除项目目录下.gitmodules文件中子模块相关条目~~
~~3. vi .git/config 删除配置项中子模块相关条目~~
~~4. rm .git/module/* 删除模块下的子模块目录，每个子模块对应一个目录，注意只删除对应的子模块目录即可~~

```shell
git submodule deinit 子模块名
git rm --cached 子模块名
```

---

### 分支

#### 从官方项目切换为自己的分支

```sh
git clone --recursive 官方项目地址
cd 项目
git remote rename origin github
git remote add origin 自己项目地址
git fetch --all
git checkout -b 我们想要切换到的分支名字 github/官方项目commit id
git pull
git branch --set-upstream-to=github/master master
git push --set-upstream origin 我们的版本
```

#### 把master的内容更新到分支xxx

1. 切换到分支

   ```sh
   git checkout xxx
   ```

2. 把master的内容合并过来

   ```sh
   git merge master
   ```

#### 重命名分支

- 本地分支

  ```sh
  git branch -m oldName newName
  ```

- 远程分支

  ```sh
  # 基于本地分支切一个新的分支
  git branch -m oldName newName
  # 删除远程分支
  git push --delete origin oldbranch
  # 推送本地新的分支
  git push origin newbranch
  ```

---

### 线上回退到某个版本

```sh
# 本地回退
git reset --hard 版本hash
git rev-parse HEAD
# 强制提交
git push -f
```

### 统计git项目

- 指定语言

```sh
find . "(" -name "*.java" ")" -print | xargs wc -l # java语言
```

- 总行数

```sh
git log  --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }' -
```

---



## 版本管理

### 工具分类

- 集中型

  以`Subversion`为代表，将所有数据存放在服务器仓库中，用户通过访问服务器来进行协作；

  ```sequence
  Title:集中型示意图
  开发者A->Subversion: commit
  Subversion-->开发者A: checkout
  开发者B->Subversion: commit
  Subversion-->开发者B: checkout
  ```

  

- 分散型

  以`Git`为代表，每个用户都拥有一个或多个独立的仓库，不一定需要通过服务器来进行协作；

  ```sequence
  Title:分散型
  开发者A->git1: push
  git1-->开发者A: pull
  git1->git2: Fork
  git2-->git1: Pull Request
  开发者B->git2: commit
  git2-->开发者B: checkout
  ```

  对比：

  |        | 优点                             | 缺点                                 |
  | ------ | -------------------------------- | ------------------------------------ |
  | 集中型 | + 可管理性强<br>+ 使用方便       | - 容易单点故障<br>- 数据丢失无法恢复 |
  | 分散型 | + 可靠性好<br>+ 数据丢失可以找回 | - 使用便利性较差，需要花时间掌握     |

### 常用工具

- JenKins

### 开发流程

TODO

---



## 常见bug

### `fatal: refusing to merge unrelated histories`
因为远程仓库已经存在代码记录了，并且那部分代码没有和本地仓库进行关联，我们可以使用如下操作允许pull未关联的远程仓库旧代码

```sh
git pull origin master --allow-unrelated-histories
```

---



## 参考

### 文献

[1] (日)大塚弘记.GitHub入门与实战.2015
