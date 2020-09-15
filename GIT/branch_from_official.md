# 如何从官方项目切换为自己的分支
```
git clone --recursive 官方项目地址
cd 项目
git remote rename origin isecsp
git remote add origin 自己项目地址
git fetch --all
git checkout -b 我们想要切换到的分支名字 isecsp/官方项目commit id
git pull
git branch --set-upstream-to=origin/master master
git push --set-upstream origin 我们的版本
```