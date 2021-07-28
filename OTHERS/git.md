# git指南

[TOC]

## API

| 命令            | 参数                                                         | 例子                                                         |
| --------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `add`           |                                                              | `git add file1`添加文件`file1`                               |
| `branch`        | `-a`所有分支<br>`-d`删除分支<br>`-D`删除分支（强制）<br>`-m`重命名分支<br>`-M`重命名分支（强制） | `git branch`列出所有**本地**分支<br>`git branch -a`列出所有分支<br>`git branch -d branchName`删除分支`branchName`，如果分支没有被合并会删除失败<br>`git branch -D branchName`删除分支`branchName`，即使分支没有被合并也删除<br>`git branch -m oldName newName`重命名分支`oldName`为`newName`，如果`newName`已存在，跳过 |
| `checkout`      | `-b` 创建新分支                                              | `git checkout master`切换到master分支<br>`git checkout -b mybranch`创建一个名叫`mybranch`<br>`git checkout -b branchName tagName`基于标签`"tagName"`创建一个名叫`"branchName"的分支`<br>`git checkout -- file`撤销**未提交的**文件`file1`的修改 |
| `clone`         |                                                              | `git clone xxx.git`克隆`xxx`项目                             |
| `commit`        | `-m` 提交注释                                                | `git commit -m "memo"`提交注释`memo`<br>`git commit -C head -a --amend`增补提交，不会产生新的提交记录 |
| `config`        | `-t` <br>`-C`<br>`--global`                                  | `git config --global user.name "name"`设置git的用户名为"name"<br>`git config --global user.email "xxx@xxx"`设置git邮箱为`"xxx@xxx"`<br> |
| `count-objects` | `-v`<br>`-H`                                                 | `git count-objects -vH`统计当前仓库占用的空间大小            |
| `diff`          | `--cached`<br>`--staged`                                     | `git diff`                                                   |
| `fetch`         |                                                              |                                                              |
| `log`           | `-m`<br>`-n` 显示前n条<br>`-p` 显示提交差异<br>`--stat` 显示简要统计信息<br/>`--author` 指定作者<br/>`--committer` 指定提交者<br/>`--name-only` 仅在提交信息后显示已修改的文件清单<br/>`--grep` 指定关键字<br/>`--since` 指定时间之后的日志<br/>`--after` 指定时间之前的日志<br/>`--graph` 以ASCII图形显示<br/>`--pretty=` 指定格式<br/>格式说明如下：<br/>   `%H` 提交的完整哈希值<br/>   `%h` 提交的简写哈希值<br/>   `%T 树的完整哈希值`<br/>   `%t` 树的简写哈希值<br/>   `%P` 父提交的完整哈希值<br/>   `%p` 父提交的简写哈希值<br/>   `%an` 作者名字<br/>   `%ae` 作者的电子邮件地址<br/>   `%ad` 作者修订日期<br/>   `%ar` 作者修订日期，按多久以前的方式显示<br/>   `%cn` 提交者的名字<br/>   `%ce` 提交者的电子邮件地址<br/>   `%cd` 提交日期<br/>   `%cr` 提交日期（距今多长时间）<br/>   `%s` 提交说明 | `git log -10`显示前10条日志<br>`git log -p -2`显示最近2次的提交差异<br>`git log --pretty="%an--%s"`显示日志的作者信息和提交说明 |
| `merge`         |                                                              | `git merge branchName`合并分支`branchName`到当前分支         |
| `push`          |                                                              | `git push origin branchName`推送到远程的分支`branchName`<br>`git push origin :refs/tags/xxx`删除远程仓库的`xxx`分支 |
| `pull`          |                                                              |                                                              |
| `remote`        |                                                              | `git remote add name xxx.git`为远程版本库`xxx.git`添加别名`name`<br>`git remote rm name`删除别名`name` |
| `reflog`        | `--date`                                                     | `git reflog --date=local | grep branchName`查看分支`branchName`是从哪里切过来的 |
| `reset`         |                                                              | `git reset HEAD file1`取消文件`file1`的暂存<br>`git reset --hard HEAD`同时取消工作区与暂存区的修改（慎用） |
| `revert`        |                                                              |                                                              |
| `rm`            | `-r`                                                         | `git rm fileName`删除文件`fileName`<br>`git rm -r dir`递归删除目录`dir`下的所有文件 |
| `status`        |                                                              | `git status`查看当前版本状态                                 |
| `submodule`     |                                                              | `git submodule init`初始化子模块<br>`git submodule update`更新子模块<br>`git submodule foreach git pull`拉取所有子模块<br>`git submodule update --init --recursive`拉取和更新所有子模块 |
| `tag`           | `-a` 添加标签<br>`-d` 删除tag<br>`-m`                        | `git tag`查看tag信息<br>`git tag tagName`给当前分支的最近一次提交创建标签<br>`git tag -a tagName commitId`给`commitId`的提交添加标签`tagName`<br>`git tag -d tagName`删除tag名为`tagName`的标签 |

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

1. type：用于说明commit类别,只允许使用下面7个标识

- 添加新特性(feat)
- 修复bug(fix)
- 文档(docs)
- 格式(style)
- 重构(refactor)
- 增加测试(test)
- 构建过程或辅助工具的变动(chore)

如果type为feat和fix，则该commit将肯定出现在Change log之中。其他情况(docs, chore, style, refactor, test)由用户决定

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

#### 把master的内容更新到分支

1. 切换到分支
2. `git merge master`

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

#### 删除分支

- 本地分支

```sh
git branch -d 分支名
```

- 远程分支

```sh
git push origin --delete 分支名
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

### 统计git项目代码行数

- 指定语言

```sh
find . "(" -name "*.java" ")" -print | xargs wc -l # java语言
```

- 总行数

```sh
git log  --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }' -
```

---



## 常见bug

### `fatal: refusing to merge unrelated histories`
因为远程仓库已经存在代码记录了，并且那部分代码没有和本地仓库进行关联，我们可以使用如下操作允许pull未关联的远程仓库旧代码

```sh
git pull origin master --allow-unrelated-histories
```

---
