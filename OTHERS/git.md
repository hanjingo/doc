# git指南

### 环境配置

#### 生成ssh key

```sh
ssh-keygen -t rsa -C "xxx@xxx"
```

#### 设置git用户名

```sh
git config --global user.name "xxx"
```

#### 设置邮箱

```sh
git config --global user.email "xxx@xxx"
```



---

### commit规范

#### angular 规范

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

### 常用命令

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

#### 线上回退到某个版本
```shell
# 本地回退
git reset --hard 版本hash
git rev-parse HEAD
# 强制提交
git push -f
```

#### 如何从官方项目切换为自己的分支
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

#### git如何把master的内容更新到分支
1. 切换到分支
2. git merge master


#### 如何去解决fatal: refusing to merge unrelated histories
因为远程仓库已经存在代码记录了，并且那部分代码没有和本地仓库进行关联，我们可以使用如下操作允许pull未关联的远程仓库旧代码

```sh
git pull origin master --allow-unrelated-histories
```

#### 如何查看git仓库大小

```sh
git count-objects -vH
```

#### 如何统计git项目代码行数

- 指定语言

```sh
find . "(" -name "*.java" ")" -print | xargs wc -l
```

- 总行数

```sh
git log  --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }' -
```

#### 查看tag信息

```
git tag
```

#### 给commit打标签

```sh
git tag -a 标签名 commitID
```

#### 删除本地tag

```sh
git tag -d 标签名
```

#### 删除远程标签

```sh
git push origin :refs/tags/标签名
```

#### 基于某个tag创建分支

```sh
git checkout -b 分支名 tag名
```



---

