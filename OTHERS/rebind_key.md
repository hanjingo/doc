# 键的重新绑定

## 重新绑定 escape键和capslock键

### window

新建 *.reg 文件并执行
```reg
Windows Registry Editor Version 5.00
[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Keyboard Layout]
"Scancode Map"=hex:00,00,00,00,00,00,00,00,03,00,00,00,3a,00,01,00,01,00,3a,00,00,00,00,00
```

### ubuntu

```sh
# 查看键位映射
xmodmap -pke > /tmp/map && cat /tmp/map
# 找到对应的键并修改
xmodmap -e "keycode 66 = Escape"
# 保存到 ~/.Xmodmap
xmodmap -pke >> ~/.Xmodmap
# 激活
xmapmap ~/.Xmodmap
```



