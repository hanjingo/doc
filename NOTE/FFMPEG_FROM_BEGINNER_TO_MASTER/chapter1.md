# 第一章FFmpeg简介

## FFmpeg的基本组成
### AVFormat(封装模块)
AVFormat中实现了目前多媒体领域中的绝大多数媒体封装格式，包括封装和解封装，如MP4,FLV,KV,TS等文件封装格式，RTMP,RTSP,MMS,HLS等网络协议封装格式。

### AVCdoce(编解码模块)
AVCodec中实现了目前多媒体领域绝大多数常用的编解码格式，既支持编码，也支持解码。AVCodec除了支持MPEG4,AAC,MJPEG等自带的媒体编解码格式之外，还支持第三方的编解码器，如H.264(AVC)编码，需要使用x264编码器；H.265(HEVC)编码，需要使用x265编码；MP3(mp3lame)编码，需要使用libmp3lame编码器。

### AVFilter(滤镜模块)
AVFilter库提供了一个通用的音频，视频，字幕等滤镜处理框架。在AVFilter中，滤镜框架可以有多个输入和输出。例
```sh
./ffmpeg -i INPUT -vf "split [main][tmp]; [tmp] crop=iw:ih/2:0:0, vflip [flip]; [main][flip] overlay=0:H/2" OUTPUT
```
说明一下规则:
- 相同的Filter线性链之间用逗号分隔
- 不同的Filter线性链之间用分号分隔
在一上示例中，crop与vflip使用的是同一个滤镜处理的线性链,split滤镜和overlay滤镜使用的是另外一个线性链，一个线性链与另一个线性链汇合时是通过方括号"\[\]"括起来的标签进行标示的。在这个例子中，2个流处理后是通过\[main\]与\[flip\]进行关联汇合的。

split滤镜将分割后的视频流的第二部分打上标签\[tmp\]，通过crop滤镜对该部分流进行处理，然后进行纵坐标调换操作，打上标签\[flip\]，然后将\[main\]标签与\[flip\]标签进行合并，\[flip\]标签的视频流从视频的左边最中间的位置开始显示，这样就出现了镜像效果.

### swscale(视频图像转换计算模块)
swscale模块提供了高级别的图像转换API，例如它允许进行图像缩放和像素格式转换，常见于将图像从1080p转换成720p或者480p等的缩放，或者将图像数据从YUV420P转换成YUYV,或者YUV转RGB等图像格式转换。

### swreasmple(音频转换计算模块)
swresample模块提供了高级别的音频重采样API。例如它允许操作音频采样，音频通道布局转换与布局调整。

## 编解码工具ffmpeg
例:
```sh
./ffmpeg -i input.mp4 -f avi output.dat
```
"-f"参数的工作非常重要，它指定了输出文件的容器格式，所以可以看到输出的文件为output.dat,文件后缀名为.dat。

ffmpeg的主要工作流程相对比较简单，具体如下:
1. 解封装(Demuxing)
2. 解码(Decoding)
3. 编码(Encoding)
4. 封装(Muxing)
其详细分为6个步骤:
1. 读取输入源
2. 进行音视频的解封装
3. 解码每一帧音视频数据
4. 编码每一帧音视频数据
5. 进行音视频的重新封装
6. 输出到目标

## 播放器ffplay
FFmpeg不但可以提供转码，转封装等功能，同时还提供了播放器相关功能，使用FFmpeg的avformat与avcodec,可以播放各种媒体文件或者流。如果想要使用ffplay,那么系统首先需要有SDL来进行ffplay的基础支撑。

## 多媒体分析器ffprobe
ffprobe是一个非常强大的多媒体分析工具，可以从媒体文件或者媒体流中获得你想要了解的媒体信息，比如音频的参数，视频的参数，媒体容器的参数信息等。例:
```sh
./ffprobe -show_streams output.mp4
```

## FFmpeg编译
### windows平台
FFmpeg在windows平台中的编译需要使用MinGW-w64,编译步骤如下:
1. ./configure
2. configure成功后执行make
3. 执行make install
4. 使用./ffmpeg.ext -h 来验证结果
注意:以上编译方式编译出来的ffmpeg仅仅只是最简单的ffmpeg，并没有H.264, H.265, 加字幕等编码支持，如果需要支持更多的模块和参数，还需要进行更加详细的定制

### linux平台
默认编译FFmpeg的时候，需要用到yasm汇编器对FFmpeg中的汇编部分进行编译。如果不需要用到汇编部分的代码，则可以不安装yasm汇编器。如果没有安排yasm，则执行默认配置的时候，会提示错误。

可以使用 --disable-yasm来取消yasm编译配置：

通过以下步骤来安装yasm：
```sh
wget http://www.tortall.net/projects/yasm/releases/yasm-1.3.0.tar.gz
```
下载yasm汇编器后，先进性configure操作，然后通过make编译，再执行make install安装即可。

### OSX平台编译
在OSX平台上编译FFmpeg之前，首先需要安装所需要的编译环境，在OSX平台上使用的编译工具链为LLVM;另外还需要安装yasm汇编编译工具，否则在生成Makefile时会报错提示未安装yasm工具。

## FFmpeg编码支持与定制
通过FFmpeg源码的configure命令查看FFmpeg所支持的音视频编码格式，文件封装格式与流媒体传输协议，对于FFmpeg不支持的格式，可以通过configure --help查看所需要的第三方外部库，然后通过增加对应的编译参数选项进行支持。

例支持H.264视频与AAC音频编码:
```sh
./configure --enable-libx264 --enable-libfdk-aac --enable-gpl --enable-nonfree
```

例关闭不需要用到的编码，封装与协议等模块:
```sh
./comfigure --disable-encoders --disable-decoders --disable-hwaccels --disable-muxers --disable-demuxers --disable-parsers --disable-bsfs --disable-protocols --disable-indevs --disable-devices --disable-filters
```

例在关闭所有模块后，可以根据自己的需要定制模块；比如希望支持H.264视频编码,AAC音频编码,封装为MP4:
```sh
./configure --disable-filters --disable-encoders --disable-decoders --disable-hwaccels --disable-muxers --disable-demuxers --disable-parsers --disable-bsfs --disable-protocols --disable-indevs --disable-devices --enable-libx264 --enable-libfdk-aac --enable-gpl --enable-nonfree --enable-muxer=mp4
```

### FFmpeg的编码器支持
通过以下命令查看支持的编码器
```sh
./configure --list-encoders
```

### FFmpeg的解码器支持
通过以下命令查看支持的解码器
```sh
./configure --list-decoders
```

### FFmpeg的封装支持
通过以下命令查看支持输出的容器格式
```sh
./configure --list-muxers
```

### FFmpeg的解封装支持
通过以下命令查看支持输入的容器格式
```sh
./configure --list-demuxers
```

### FFmpeg的通信协议支持
通过以下命令查看支持的网络流媒体协议
```sh
./configure --list-protocols
```

## 总结
本章重点介绍了FFmpeg的获取，安装，容器封装与解封装的格式支持，音视频编码与解码的格式支持，以及流媒体传输协议的支持。综合来说，FFmpeg所支持的容器，编解码，协议相对来说比较全面，是一款功能强大的多媒体处理工具和开发套件。