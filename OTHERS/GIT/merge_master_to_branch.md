# git如何把master的内容更新到分支
1. 切换到分支
2. git merge master

# 如何去解决fatal: refusing to merge unrelated histories
因为远程仓库已经存在代码记录了，并且那部分代码没有和本地仓库进行关联，我们可以使用如下操作允许pull未关联的远程仓库旧代码

```sh
git pull origin master --allow-unrelated-histories
```