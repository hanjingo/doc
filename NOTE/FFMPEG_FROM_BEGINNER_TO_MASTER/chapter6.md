# 第六章 FFmpeg滤镜使用

## FFmpeg滤镜Filter描述格式

### FFmpeg滤镜Filter的参数排列方式

下面先用最简单的方式来描述Filter使用时的参数排列方式：

```sh
[输入流或标记名]滤镜参数[临时标记名];[输入流或标记名]滤镜参数[临时标记名]...
```

例：输入两个文件，一个视频input.mp4, 一个图片logo.png，将logo进行缩放，然后放在视频的左上角

```sh
./ffmpeg -i input.mp4 -i logo.png -filter_complex "[1:v]scale=176:144[logo];[0:v][logo]overlay=x=0:y=0" output.mp4
```

### FFmpeg滤镜Filter时间内置变量

| 变量 | 说明                                              |
| ---- | ------------------------------------------------- |
| t    | 时间戳以秒表示，如果输入的时间戳是未知的，则是NAN |
| n    | 输入帧的顺序编号，从0开始                         |
| pos  | 输入帧的位置，如果未知则是NAN                     |
| w    | 输入视频帧的宽度                                  |
| h    | 输入视频帧的高度                                  |

## FFmpeg为视频加水印

### 文字水印

FFmpeg文字滤镜参数:

| 参数      | 类型   | 说明                       |
| --------- | ------ | -------------------------- |
| fontfile  | 字符串 | 字体文件                   |
| text      | 字符串 | 文字                       |
| textfile  | 字符串 | 文字文件                   |
| fontcolor | 色彩   | 文字颜色                   |
| box       | 布尔   | 文字区域背景框             |
| boxcolor  | 色彩   | 展示字体的区域块的颜色     |
| fontsize  | 整数   | 显示字体的大小             |
| font      | 字符串 | 字体名称（默认为Sans字体） |
| x         | 整数   | 文字显示的x坐标            |
| y         | 整数   | 文字显示的y坐标            |

drawtext滤镜使用：

例：将文字的水印加在视频的左上角

```sh
./ffmpeg -i input.mp4 -vf "drawtext=fontsize=100:fontfile=FreeSerif.ttf:text='hello world':x=20:y=20" output.mp4
```

例：将字体的颜色设置为绿色

```sh
./ffmpeg -i input.mp4 -vf "drawtext=fontsize=100:fontfile=FreeSerif.ttf:text='hello world':fontcolor=green" output.mp4
```

例：文字水印增加一个框，然后给框加上背景颜色

```sh
./ffmpeg -i input.mp4 -vf "drawtext=fontsize=100:fontfile=FreeSerif.ttf:text='hello world':fontcolor=green:box=1:boxcolor=yellow" output.mp4
```

例：在text中显示本地当前时间，格式为年月日时分秒的方式

```sh
./ffmpeg -re -i input.mp4 -vf "drawtext=fontsize=60:fontfile=FreeSerif.ttf:text='%{localtime\:%Y\-%m\-%d %H-%M-%S}':fontcolor=green:box=1:boxcolor=yellow" output.mp4
```

例：每3秒钟显示一次文字水印

```sh
./ffmpeg -re -i input.mp4 -vf "drawtext=fontsize=60:fontfile=FreeSerif.ttf:text='test':fontcolor=green:box=1:boxcolor=yellow:enable=1t(mod(t\,3)\,1)" output.mp4
```

例：将中文水印加入到视频当中，并且中文字符的字体为行文楷体

```sh
./ffmpeg -re -i input.mp4 -vf "drawtext=fontsize=50:fontfile=/Library/Fonts/Songti.ttc:text='文字水印测试':fontcolor=green:box=1:boxcolor=yellow" output.mp4
```

### 图片水印

FFmpeg movie滤镜的参数：

| 参数             | 类型     | 说明                                 |
| ---------------- | -------- | ------------------------------------ |
| filename         | 字符串   | 输入的文件名，可以是文件，协议，设备 |
| format_name, f   | 字符串   | 输入的封装格式                       |
| stream_index, si | 整数     | 输入的流索引编号                     |
| seek_point, sp   | 浮点数   | Seek输入流的时间位置                 |
| stream, s        | 字符串   | 输入的多个流的流信息                 |
| loop             | 整数     | 循环次数                             |
| discontinuity    | 时间差值 | 支持跳动的时间戳差值                 |

例：logo.png水印将会打入到input.mp4视频中，显示在x坐标30，y坐标10的位置

```sh
./ffmpeg -i input.mp4 -vf "movie=logo.png[wm]; [in][wm] overlay=30:10[out]" output.mp4
```

例：根据colorkey设置的颜色值，相似度，混合度与原片混合为半透明水印

```sh
./ffmpeg -i input.mp4 -vf "movie=logo.png,colorkey=black:1.0:1.0 [wm]; [in] [wm] overlay=30:10[out]" output.mp4
```

## FFmpeg生成画中画

FFmpeg滤镜overlay基本参数:

| 参数       | 类型   | 说明                                                         |
| ---------- | ------ | ------------------------------------------------------------ |
| x          | 字符串 | x坐标                                                        |
| y          | 字符串 | y坐标                                                        |
| eof_action | 整数   | 遇到eof标志时的处理方式，默认为重复：repeat(值为0):重复前一帧;  endall(值为1):停止所有的流; pass(值为2):保留主图层; |
| shortest   | 布尔   | 终止最短的视频时全部终止（默认关闭）                         |
| format     | 整数   | 设置output的像素格式，默认为yuv420: yuv420(值为0); yuv422(值为1); yuv444(值为2); rgb(值为3) |

例：将sub.mp4视频文件缩放成宽480，高320的视频，然后显示在视频input.mp4的x坐标为0，y坐标为0的位置

```sh
./ffmpeg -re -i input.mp4 -vf "movie=sub.mp4,scale=480x320[test]; [in][test] overlay [out]" -vcodec libx264 output.flv
```

例：子视频将会定位在主画面的最右边减去子视频的宽度，最下边减去子视频的高度的位置

```sh
./ffmpeg -re -i input.mp4 -vf "movie=sub.mp4,scale=480x320[test]; [in][test] overlay=x=main_w-480:y=main_h-320 [out]" -vcodec libx264 output.flv
```

例：子视频从主视频的左侧开始渐入视频从左向右游动

```sh
./ffmpeg -re -i input.mp4 -vf "movie=sub.mp4,scale=480x320[test]; [in][test] overlay=x='if(gte(t,2), -w+(t-2)*20, NAN)':y=0 [out]" -vcodec libx264 output.flv
```

## FFmpeg视频多宫格处理

通过nullsrc创建一个overlay画布，画布的大小的宽640像素，高480像素，使用:

```sh
[0:v][1:v][2:v][3:v]
```

将输入的4个视频流去除，分别进行缩放处理，处理为宽320，高240的视频，然后基于nullsrc生成的画布进行视频平铺

```sh
./ffmpeg -re -i input1.mp4 -re -i input2.mp4 -re -i input3.m2t -re -i input4.mp4
```

