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
