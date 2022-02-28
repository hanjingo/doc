# linux错误

[TOC]



### ubuntu的dash问题

**问题**

在执行sh文件时报`Syntax error: "(" unexpected`错误

**原因**

`Ubuntu/Debian`为了加快开机速度，用dash代替了传统的bash，是dash在捣鬼，解决方法就是取消dash

**解决**

```sh
sudo dpkg-reconfigure dash
# 选no
```



### wsl环境下git clone报错

**问题**

在wsl环境下的windows文件夹中执行`git clone xx`报错：

```sh
xx/.git/config.lock failed: Operation not permitted
```

**原因**

windows的一些文件系统（如NTFS等）不兼容wsl导致报无权限的问题

**解决**

```sh
echo "[automount]\
enabled = true\
options = \"metadata,umask=22,fmask=11\"\
mountFsTab = false" >> /etc/wsl.conf
```

