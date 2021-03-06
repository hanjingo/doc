# git指南

## 环境配置

### 生成ssh key

```sh
ssh-keygen -t rsa -C "xxx@xxx"
```

### 设置git用户名

```sh
git config --global user.name "xxx"
```

### 设置邮箱

```sh
git config --global user.email "xxx@xxx"
```



---

## 常用命令
### 添加子模块
```shell
git submodule add -b 分支 --name 子模块名(不填默认) ssh地址 模块路径
```

### 拉取子模块更新
1. 方法一:
```shell
git submodule init
git submodule update
```

2. 方法二:
```shell
git submodule update --init --recursive
```

### 删除子模块
~~1. rm -rf 子模块目录 删除子模块目录及源码~~
~~2. vi .gitmodules 删除项目目录下.gitmodules文件中子模块相关条目~~
~~3. vi .git/config 删除配置项中子模块相关条目~~
~~4. rm .git/module/* 删除模块下的子模块目录，每个子模块对应一个目录，注意只删除对应的子模块目录即可~~
```shell
git submodule deinit 子模块名
git rm --cached 子模块名
```

### 线上回退到某个版本
```shell
# 本地回退
git reset --hard 版本hash
git rev-parse HEAD
# 强制提交
git push -f
```

---
## 如何从官方项目切换为自己的分支
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

---
## 如何把master的代码更新到分支
### git如何把master的内容更新到分支
1. 切换到分支
2. git merge master

### 如何去解决fatal: refusing to merge unrelated histories
因为远程仓库已经存在代码记录了，并且那部分代码没有和本地仓库进行关联，我们可以使用如下操作允许pull未关联的远程仓库旧代码

```sh
git pull origin master --allow-unrelated-histories
```