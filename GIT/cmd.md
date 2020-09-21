### 添加子模块
1. 方法一:

```
git submodule init
git submodule update
```

2. 方法二:

```
git submodule update --init --recursive
```

### 删除子模块
1. rm -rf 子模块目录 删除子模块目录及源码
2. vi .gitmodules 删除项目目录下.gitmodules文件中子模块相关条目
3. vi .git/config 删除配置项中子模块相关条目
4. rm .git/module/* 删除模块下的子模块目录，每个子模块对应一个目录，注意只删除对应的子模块目录即可
