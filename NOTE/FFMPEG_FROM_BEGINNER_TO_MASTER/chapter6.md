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
./ffmpeg -re -i input1.mp4 -re -i input2.mp4 -re -i input3.m2t -re -i input4.mp4 -filter_complex "nullsrc=size=640x480 [base]; [0:v] setpts=PTS-STARTPTS,scale=320x240 [upperleft]; [1:v] setpts=PTS-STARTPTS, scale=320x240 [upperright]; [2:v] setpts=PTS-STARTPTS, scale=320x240 [lowerleft]; [3:v] setpts=PTS-STARTPTS, scale=320x240 [lowerright]; [base][upperleft] overlay=shortest=1[tmp1]; [tmp1][upperright] overlay=shortest=1:x=320 [tmp2]; [tmp2][lowerleft]overlay=shortest=1:y=240 [tmp3][lowerright] overlay=shortest=1:x=320:y=240" -c:v libx264 output.flv
```

## FFmpeg音频流滤镜操作

### 双声道合并单声道

例：input.aac的音频原为双声道，现被转为单声道

```sh
./ffmpeg -i input.aac -ac 1 output.aac
```

### 双声道提取

例：将音频为stereo的布局提取为两个mono流，左声道一个流，右声道一个流

```sh
./ffmpeg -i input.aac -map_channel 0.0.0 left.aac -map_channel 0.0.1 right.aac
```

例：将布局格式为stereo的input.aac转换为两个mono布局的left.aac与right.aac

```sh
./ffmpeg -i input.aac -filter_complex "[0:0]pan=1c|c0=c0[left];[0:0]pan=1c|c0=c1[right]" -map "[left]" left.aac -map "[right]" right.aac
```

### 双声道转双音频流

例：通过channelsplit滤镜将stereo布局方式的音频切分开，分成两个音频流

```sh
./ffmpeg -i input.aac -filter_complex channelsplit=channel_layout=stereo output.mka
```

### 单声道转双声道

例：从left.aac中，将布局为mono的音频转换为stereo布局的音频文件output.m4a

```sh
./ffmpeg -i left.aac -ac 2 output.m4a
```

或

```sh
./ffmpeg -i left.aac -filter_complex "[0:a][0:a]amerge=inputs=2[aout]" -map "[aout]" output.m4a
```

### 两个音频源合并双声道

例：将left.aac与right.aac两个音频为mono布局的AAC合并为一个布局为stereo的音频流，输出至output.mka文件

```sh
./ffmpeg -i left.aac -i right.aac -filter_complex "[0:a][1:a] amerge=inputs=2[aout]" -map "[aout]" output.mka
```

### 多个音频合并为多声道

例：将6个mono布局的音频流合并为一个多声道（5.1声道）的音频流

```sh
./ffmpeg -i front_left.wav -i front_right.wav -i front_center.wav -i 1fe.wav -i back_left.wav -i back_right.wav -filter_complex "[0:a][1:a][2:a][3:a][4:a][5:a] amerge=inputs=6[aout]" -map "[aout]" output.wav
```

## FFmpeg音频音量探测

### 音频音量获得

例：获得音频的音量分贝，以及与音频相关的一些信息

```sh
./ffmpeg -i output.wav -filter_complex volumedetect -c:v copy -f null /dev/null
```

### 绘制音频波形

例：生成一个宽高为640x120大小的output.png图片，图片内容为音频波形

```sh
./ffmpeg -i output.wav -filter_complex "showwavespic=s=640x120" -frames:v 1 output.png
```

例：显示每个声道的音频的波形图

```sh
./ffmpeg -i output.wav -filter_complex "showwavespic=s=640x210:split_channels=1" -frames:v 1 output.png
```

## FFmpeg为视频加字幕

### ASS字幕流写入视频流

例：将字幕写入视频流中

```sh
./ffmpeg -i input.mp4 -vf ass=t1.ass -f mp4 output.mp4
```

### ASS字幕流写入封装容器

例：将ASS字幕流写入MKV封装容器中，并以字幕流的形式存在：

```sh
./ffmpeg -i input.mp4 -i t1.ass -acodec copy -vcodec copy -scodec copy output.mkv
```

例：将第一个输入文件的第一个流和第二个流与第二个输入文件的第一个流写入output.mkv中

```sh
./ffmpeg -i input.mp4 -i t1.ass -map 0:0 -map 0:1 -map 1:0 -acodec copy -vcodec copy -scodec copy output.mkv
```

## FFmpeg视频抠图合并

FFmpeg滤镜chromakey参数

| 参数       | 类型 | 说明                            |
| ---------- | ---- | ------------------------------- |
| color      | 颜色 | 设置chromakey颜色值，默认为黑色 |
| similarity | 浮点 | 设置chromakey相似值             |
| blend      | 浮点 | 设置chromakey融合值             |
| yuv        | 布尔 | yuv替代rgb，默认为false         |

例：使用chromakey滤镜将绿色背景中的任务抠出来，然后贴到以input.mp4为背景的视频中

```sh
./ffmpeg -i input.mp4 -i input_green.mp4 -filter_complex "[1:v]chromakey=Green:0.1:0.2[ckout];[0:v][ckout]overlay[out]" -map "[out]" output.mp4
```

**注意：FFmpeg中除了有chromakey滤镜之外，还有一个colorkey参数，chromakey滤镜主要处理YUV数据，所以一般来说做绿幕处理更有优势；而colorkey处理纯色均可以，因为colorkey处理主要以RGB数据为主。**

## FFmpeg 3D 视频处理

### stereo3d处理3D视频

FFmpeg滤镜stereo3d参数

| 参数 | 类型 | 说明                                                         |
| ---- | ---- | ------------------------------------------------------------ |
| in   | 整数 | sbsl: 并排平行（左眼左，右眼右）；<br>sbsr: 并排对穿（右眼左，左眼右）；<br>sbs2l：并排半宽度分辨率（左眼左，右眼右）；<br>sbs2r：并排对穿半宽度分辨率（右眼左，左眼右）；<br>abl：上下（左眼上，右眼下）；<br>abr：上下（右眼上，左眼下）；<br>ab2l：上下半高度分辨率（左眼上，右眼下）；<br>ab2r：上下半高度分辨率（右眼上，左眼下）；<br>al：交替帧显示（左眼先显示，右眼后显示）；<br>ar：交替帧显示（右眼先显示，左眼后显示）；<br>irl：交错行（左眼上面一行，右眼开始下一行）；<br>irr：交错行（右眼上面一行，左眼开始下一行）；<br>icl：交叉行（左眼先显示）；<br>icr：交叉列（右眼先显示）；<br>默认是为sbsl |
| out  | 整数 | sbsl: 并排平行（左眼左，右眼右）；<br>sbsr: 并排对穿（右眼左，左眼右）；<br>sbs2l：并排半宽度分辨率（左眼左，右眼右）；<br>sbs2r：并排对穿半宽度分辨率（右眼左，左眼右）；<br>abl：上下（左眼上，右眼下）；<br>abr：上下（右眼上，左眼下）；<br>ab2l：上下半高度分辨率（左眼上，右眼下）；<br>ab2r：上下半高度分辨率（右眼上，左眼下）；<br>al：交替帧显示（左眼先显示，右眼后显示）；<br>ar：交替帧显示（右眼先显示，左眼后显示）；<br>irl：交错行（左眼上面一行，右眼开始下一行）；<br>irr：交错行（右眼上面一行，左眼开始下一行）；<br>arbg：浮雕红/蓝灰色（红色左眼，右眼蓝色）；<br>argg：浮雕红/绿灰色（红色左眼，右眼绿色）；<br>arcg：浮雕红/青灰色（红色左眼，右眼青色）；<br>arch：浮雕红/青半彩色（红色左眼，右眼青色）；<br>arcc：浮雕红/青颜色（红色左眼，右眼青色）；<br>arcd：浮雕红/青颜色优化的最小二乘预测（红色左眼，右眼青色）；<br>agmg：浮雕绿色/红色灰色（红色绿色，右眼红色）；<br>agmh：浮雕绿色/红色一半颜色（红色绿色，右眼红色）；<br>agmc：浮雕绿色/红色灰色（红色绿色，右眼红色）；<br>agmd：浮雕绿色/红色颜色（红色绿色，右眼红色）；<br>agmc：浮雕绿色/红色颜色（绿色左眼，红色右眼）；<br>agmd：浮雕绿色/红色颜色优化的最小二乘预测（绿色左眼，红色右眼）；<br>aybg：浮雕黄/蓝灰色（黄色左眼，蓝色右眼）；<br>aybc：浮雕黄色/蓝色颜色（黄色左眼，蓝色右眼）；<br>aybd：浮雕黄色/蓝色优化的最小二乘预测（黄色左眼，蓝色右眼）；<br>ml：mono输出（只显示左眼）；<br>mr：mono输出（只显示右眼）；<br>irl：交错行（左眼上面一行，右眼开始下一行）；<br>irr：交错行（右眼上面一行，左眼开始下一行）；<br>默认值是arcd |

例：将原片的左右排列效果合并为黄蓝合并排列效果

```sh
ffplay -vf "stereo3d=arbg" input.mp4
```

## FFmpeg定时视频截图

### vframe参数截取一张图片

例：定位到input.flv的第七秒位置，获得对应的视频帧，然后将图像解码出来编码成RGB24的图像并封装成PNG图像

```sh
./ffmpeg -i input.flv -ss 00:00:7.435 -vframes 1 out.png
```

### fps滤镜定时获得图片

例：每个1秒钟生成一张PNG图片

```sh
./ffmpeg -i input.flv -vf fps=1 out%d.png
```

例：每隔1分钟生成一张JPEG图片

```sh
./ffmpeg -i input.flv -vf fps=1/60 img%03d.jpg
```

例：每隔10分钟生成一张BMP图片

```sh
./ffmpeg -i input.flv -vf fps=1/600 thumb%04d.bmp
```

例：判断图像类型是否为I帧，如果是I帧则会生成一张PNG图像

```sh
./ffmpeg -i input.flv -vf "select='eq(pict_type,PICT_TYPE_I)'" -vsync vfr thumb%04d.png
```

## FFmpeg生成测试元数据

### FFmpeg生成音频测试流

例：根据lavfi设备输入的abuffer中定义的采样率，格式，以及声道布局，通过AAC编码，然后生成AAC音频文件

```sh
./ffmpeg -re -f lavfi -i abuffer=sample_rate=44100:sample_fmt=s16p:channel_layout=stereo -acodec aac -y output.aac
```

例：音频为使用aevalsrc生成的双通道音频，输出为output.aac

```sh
./ffmpeg -re -f lavfi "aevalsrc=sin(420*2*PI*t)|cos(430*2*PI*t):c=FC|BC" -acodec aac output.aac
```

### FFmpeg生成视频测试流

可以通过FFmpeg虚拟设备虚拟出来一个输入视频流，可以通过FFmpeg模拟多种视频源：allrgb, allyuv, color, haldclutsrc, nullsrc, rgbtestsrc, smptebgars, smptehdbars, testsrc, testsrc2, yuntestsrc;

例：根据testsrc生成长度为5.3秒，图像大小为QCIF分辨率，帧率为25fps的视频图像数据，并编码称为H.264，然后输出output.mp4视频文件

```sh
./ffmpeg -re -f lavfi -i testsrc=duration=5.3:size=acif:rate=25 -vcodec libx264 -r:v 25 output.mp4
```

例：根据testsrc2生成一个视频图像内容，其他参数与testsrc相同

```sh
./ffmpeg -re -f lavfi -i testsrc2=duration=5.3:size=qcif:rate=25 -vcodec libx264 -r:v 25 output.mp4
```

例：使用color作为视频源，图像内容为纯红色，编码为H.264

```sh
./ffmpeg -re -f lavfi -i color=c=red@0.2:s=qcif:r=25 -vcodec libx264 -r:v 25 output.mp4
```

例：使用nullsrc作为视频源，宽高为256x256，数据位随机雪花样

```sh
./ffmpeg -re -f lavfi -i "nullsrc=s=256x256, gep=random(1)*256:128:128" -vcodec libx264 -r:v 25 output.mp4
```

## FFmpeg对音视频倍速处理

## atempo音频倍速处理

1. 半速处理

   ```sh
   ./ffmpeg -i input.wav -filter_complex "atempo=tempo=0.5" -acodec aac output.aac
   ```

2. 2倍速处理

   ```sh
   ./ffmpeg -i input.wav -filter_complex "atempo-tempo=2.0" -acodec aac output.aac
   ```

### setpts视频倍速处理

FFmpeg滤镜setpts参数

| 值         | 说明                                |
| ---------- | ----------------------------------- |
| FRAME_RATE | 根据帧率设置帧率值，只用于固定帧率  |
| PTS        | 输入的pts时间戳                     |
| RTCTIME    | 使用RTC的时间作为时间戳（即将弃用） |
| TB         | 输入的时间戳的时间基                |

1. 半速处理

   ```sh
   ./ffmpeg -re -i input.mp4 -filter_complex "setpts=PTS*2" output.mp4
   ```

2. 2倍速处理

   ```sh
   ./ffmpeg -i input.mp4 -filter_complex "setpts=PTS/2" output.mp4
   ```

   