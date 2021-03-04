# 第四章 FFmpeg转码
## FFmpeg软编码H.264与H.265
查看x264所支持的编码:
```sh
ffmpeg -h encoder=libx264
```
### x264编码参数简介
|参数|类型|说明|
|:--|:--|:--|
|preset|字符串|编码器预设参数|
|tune|字符串|调优编码参数|
|profile|字符串|编码profile档级设置|
|level|字符串|编码level层级设置|
|wpredp|字符串|P帧预测设置|
|x264opts|字符串|设置x264专有参数|
|crf|浮点数|选择质量恒定质量模式|
|crf_max|浮点数|选择质量恒定质量模式最大值|
|qp|整数|恒定量化参数控制|
|psy|浮点数|只用pschovisual优化|
|rc-lookahead|整数|设置预读帧设置|
|weightb|浮点数|B帧预测设置|
|weightp|整数|设置预测分析方法:none,simple,smart三种模式|
|ssim|布尔|计算打印SSIM状态|
|intra-refresh|布尔|定时刷I帧以替代IDR帧|
|bluray-compat|布尔|蓝光兼容参数|
|b-bias|整数|B帧使用频率设置|
|mixed-refs|布尔|每个partition一个参考，而不是每个宏块一个参考|
|8x8dct|布尔|8x8矩阵变缓，用在high profile|
|aud|布尔|带AUD分隔标识|
|mbtree|布尔|宏块树评率控制|
|deblock|字符串|环路滤波参数|
|cplxblur|浮点数|减少拨动QP参数|
|partitions|字符串|逗号分割的partition列表，可以包含的值有p8x8,p4x4,b8x8,i8x8,i4x4,none,all|
|direct-pred|整数|运动向量预测模式|
|slice-max-size|整数|Slice的最大值|
|nal-hrd|整数|HRD信号信息设置:None,VBR,CBR设置|
|motion-est|整数|运动估计方法|
|forced-idr|布尔|强行设置关键帧为IDR帧|
|coder|整数|编码器类型包括default,cavlc,cabac,vlc,ac|
|b_strategy|整数|I/P/B帧选择策略|
|chromaoffset|整数|QP色度和亮度之间的差异参数|
|sc_threshold|整数|场景切换阀值参数|
|noise_reduction|整数|降噪处理参数|
|x264-params|字符串|与x264opts操作相同|

### H.264编码举例
1. 编码器预设参数设置preset:
- ultrafast:最快的编码方式
- superfast:超级快速的编码方式
- veryfast:非常快速的编码方式
- faster:稍微快速的编码方式
- fast:快速的编码方式
- medium:这种的编码方式
- slow:慢的编码方式
- slower:更慢的编码方式
- veryslow:非常慢的编码方式
- placebo:最慢的编码方式
例:设置ultrafast与设置medium预设参数
```sh
./ffmpeg -i input.mp4 -vcodec libx264 -preset ultrafast -b:v 2000k output.mp4
```

2. H.264编码优化参数tune
- film
- animation
- grain
- stillimage
- psnr
- ssim
- fastdecode
- zerolatency

3. H.264的profile与level设置
    x264编码profile参数

| -                      | Baseline | Extented | Main | High | High10 | High 4:2:2 | High 4:4:4 (Predictive)|
| ---------------------- | -------- | -------- | ---- | ---- | ------ | ------ | ------ |
| I与P分片               | √        | √        | √    | √    | √      |√|√|
| B分片                  | x | √ | √ | √ | √ |√|√|
| SI和SP分片             | x | √ | x | x | x |x|x|
| 多参考帧               | √ | √ | √ | √ | √ |√|√|
| 环路去块滤波           | √ | √ | √ | √ | √ |√|√|
| CAVLC熵编码            | √ | √ | √ | √ | √ |√|√|
| CABAC熵编码            | x | x | √ | √ | √ |√|√|
| FMO                    | x | √ | x | x | x |x|x|
| ASO                    | x | √ | x | x | x |x|x|
| RS                     | x | √ | x | x | x |x|x|
| 数据分区               | √ | √ | x | x | x |x|x|
| 场编码PAFF/MBAFF       | x | √ | √ | √ | √ |√|√|
| 4:2:0 色度格式         | √ | √ | √ | √ | √ |√|√|
| 4:0:0 色度格式         | x | x | x | √ | √ |√|√|
| 4:2:2 色度格式         | x | x | x | x | x |√|√|
| 4:4:4 色度格式         | x | x | x | x | x |x|√|
| 8位采样深度            | √ | √ | √ | √ | √ |√|√|
| 9和10位采样深度        | x | x | x | x | √ |√|√|
| 11至14位采样深度       | x | x | x | x | x |x|√|
| 8x8与4x4转换适配       | x | x | x | √ | √ |√|√|
| 量化计算矩阵           | x | x | x | √ | √ |√|√|
| 分离Cb和Cr量化参数控制 | x | x | x | √ | √ |√|√|
| 分离色彩平面编码       | x | x | x | x | x |x|√|
| 分离无损编码           | x | x | x | x | x |x|√|

例:使用FFmpeg编码生成baseline与high2种profile的视频
```sh
ffmpeg -i input.mp4 -vcodec libx264 -profile:v baseline -level 3.1 -s 352x288 -an -y -t 10 output_baseline.ts
ffmpeg -i input.mp4 -vcodec libx264 -profile:v high -level 3.1 -s 352x288 -an -y -t 10 output_high.ts
```
例:使用ffprobe查看上面2个文件包含的B帧的情况
```sh
ffprobe -v quiet -show_frames -select_streams v output_baseline.ts |grep "pict_type=B"|wc -l
ffprobe -v quiet -show_frames -select_streams v output_high.ts grep "pict_type=B"|wc -l
```

4. 控制场景切换关键帧插入参数sc_threshold
使GOP的插入更加均匀，使用参数sc_threshold:
```sh
./ffmpeg -i input.mp4 -c:v libx264 -g 50 -sc_threshold 0 -t 60 -y output.mp4
```

5. 设置x264每部参数x264opts
FFmpeg开放了x264opts,可以通过这个参数设置x264内部私有参数
```sh
./ffmpeg -i input.mp4 -c:v libx264 -x264opts "bframes=0" -g 50 -sc_threshold 0 output.mp4
```

例:每2个P帧之间存放3个B帧:
```sh
./ffmpeg -i input.mp4 -c:v libx264 -x264opts "bframes=3:b-adapt=0" -g 50 -sc_threshold 0 output.mp4
```

6. CBR恒定码率设置参数nal-hrd

   例：设置1M bit/s码率的视频，bufsize设置为50KB，可以很好地控制码率波动:

   ```sh
   ./ffmpeg -i input.mp4 -c:v libx264 -x264opts "bframes=10:b-adapt=0" -b:v 1000k -maxrate 1000k -minrate 1000k -bufsize 50k -nal-hrd cbr -g 50 -sc_threshold 0 output.ts
   ```
   
   ***说明:在FFmpeg中进行H.265编码时，可以采用x265进行编码，H.265编码参数与x264的编码参数相差不多，基本可以通用。***

## FFmpeg硬编解码

### Nvidia GPU 硬编解码

1. Nvidia硬编解码参数

   | 参数         | 类型 | 说明                                                         |
   | ------------ | ---- | ------------------------------------------------------------ |
   | preset       | 整数 | 预设置模板，设置的模板不同，转码时的书读也会不同，模板如下（默认为medium模板）:default, slow, medium, fast, hp, hq, bd, ll, llhq, llhp, lossless, losslesshp |
   | profile      | 整数 | 视频编码profile参数:baseline, main, high, high444p           |
   | level        | 整数 | 视频编码Level参数:auto, 1, 1.0, 1b, 1.0b, 1.1, 1.2, 1.3, 2, 2.0, 2.1, 2.2, 3, 3.0, 3.1, 3.2, 4, 4.0, 4.1, 4.2, 5, 5.0, 5.1 |
   | rc           | 整数 | 预设置码率控制模板:constqp, vbr, cbr, vbr_minqp, ll_2pass_quality, ll_2pass_size, vbr_2pass |
   | rc-lookahead | 整数 | 控制码率预读取帧                                             |
   | gpu          | 整数 | GPU使用: any: 默认使用第一个GPU; list: 列取可用GPU列表;      |
   | no-scenecut  | 布尔 | 场景切换是否插入I帧                                          |
   | forced-idr   | 布尔 | 强制将帧转换为IDR帧                                          |
   | b_adapt      | 布尔 | 开启预读取帧时设置B帧适配                                    |
   | zerolatency  | 布尔 | 低延时编码设置                                               |
   | nonreg_p     | 布尔 | 设置P帧为非参考帧                                            |
   | cq           | 整数 | VBR模式时设置量化参数                                        |
   | aud          | 布尔 | 设置AUD分隔符                                                |

2. Nvidia硬编解码参数使用举例

   查看FFmpeg中Nvidia做H.264编码时的参数支持

   ```sh
   ffmpeg -h encoder=h264_nvenc
   ```

   查看FFmpeg中Nvidia做H.264解码时的参数支持

   ```sh
   ffmpeg -h decoder=h264_cuvid
   ```

   将input.mp4的视频像素改变为1920x1080,将码率改变为2000kbit/s,输出为output.mp4

   ```sh
   ./ffmpeg -hwaccel cuvid -vcodec h264_cuvid -i input.mp4 -vf scale_npp=1920:1080 -vcodec h264_nvenc -acodec copy -f mp4 -y output.mp4
   ```

### Intel QSV硬编码

编译FFmpeg时开启QSV支持:

```sh
./ffmpeg -hide_banner -codecs|grep h264
```

1. Intel QSV H.264参数

   | 参数                    | 类型 | 说明                                                         |
   | ----------------------- | ---- | ------------------------------------------------------------ |
   | async_depth             | 整数 | 编码最大并行处理深度                                         |
   | avbr_accuracy           | 整数 | 精确的AVBR控制                                               |
   | avbr_convergence        | 整数 | 收敛的AVBR控制                                               |
   | preset                  | 整数 | 预设值模板:包括veryfast, faster, fast, medium, slow, slower, veryslow共7中预置参数模板 |
   | vcm                     | 整数 | 使用视频会议模式码率控制                                     |
   | rdo                     | 整数 | 失真优化                                                     |
   | max_frame_size          | 整数 | 帧最大size设置                                               |
   | max_slice_size          | 整数 | Slice最大size设置                                            |
   | bitrate_limit           | 整数 | 码率极限值设置                                               |
   | mbbrc                   | 整数 | 宏块级别码率设置                                             |
   | exbrc                   | 整数 | 扩展级别码率设置                                             |
   | adaptive_i              | 整数 | I帧自适应位置设置                                            |
   | adaptive_b              | 整数 | B帧自适应位置设置                                            |
   | b_strategy              | 整数 | I/P/B帧编码策略                                              |
   | idr_interval            | 整数 | IDR帧频率(GOP Size)                                          |
   | single_sei_nal_unit     | 整数 | NALU合并设置                                                 |
   | max_dec_frame_buffering | 整数 | DPB最大数量的帧缓冲设置                                      |
   | look_ahead              | 整数 | 在进行VBR算法时使用lookahead模式                             |
   | look_ahead_depth        | 整数 | 设置lookahead预读取的帧数                                    |
   | look_ahead_downsampling | 整数 | 设置lookahead预读取采样帧时                                  |
   | int_ref_type            | 整数 | 帧内参考刷新类型                                             |
   | int_ref_cycle_size      | 整数 | 帧内参考刷新类别刷新帧的数量设置                             |
   | int_ref_qp_delta        | 整数 | 刷新宏块时设置的量化差值                                     |
   | profile                 | 整数 | 编码参考profile: 支持baseline, main, high共2种profile        |

2. Intel QSV H.264 使用举例

   使用h264_qsv进行解码与编码:

   ```sh
   ./ffmpeg -i 10M1080P.mp4 -pix_fmt nv12 -cvodec h264_qsv -an -y output.mp4
   ```

3. Intel QSV H.265(HEVC)参数

   | 参数         | 类型   | 说明                                                         |
   | ------------ | ------ | ------------------------------------------------------------ |
   | load_plugin  | 整数   | 加载编码插件的情况如下: none: 不加载任何插件; hevc_sw: H.265软编码插件; hevc_hw: H.265硬编码插件; |
   | load_plugins | 字符串 | 加载硬件编码插件的时候使用十六进制串                         |

4. Intel QSV H.265使用举例

   在使用Intel进行高清编码时，使用AVC编码之后观察码率会比较高，但是使用H.265(HEVC)则能更好的地降低同样清晰度的码率；

   例:

   ```sh
   ./ffmpeg -hide_banner -y -hwaccel qsv -i 10M1080P.mp4 -an -c:v hevc_qsv -load_plugin hevc_hw -b:v 5M -maxrate 5M out.mp4
   ```

### 树莓派硬编码

1. 树莓派H.264编码参数

   | 参数          | 类型   | 说明           |
   | ------------- | ------ | -------------- |
   | omx_libname   | 字符串 | OpenMAX库名    |
   | omx_libprefix | 字符串 | OpenMAX库路径  |
   | zerocopy      | 整数   | 避免复制输入帧 |

2. h264_omx使用举例

   解码input.mp4,通过使用h264_omx编码器进行编码，最后输出output.mp4；

   例:

   ```sh
   ./ffmpeg -i input.mp4 -vcodec h264_omx -b:v 500k -acodec copy -y output.mp4
   ```

### OSX系统硬编解码

1. OSX硬编解码参数

   videotoolbox编码参数:

   | 参数     | 类型 | 说明                                                         |
   | -------- | ---- | ------------------------------------------------------------ |
   | profile  | 整数 | 视频编码profile设置:baseline, main, high                     |
   | level    | 整数 | 视频编码level设置:1.3, 3.0, 3.1, 3.2, 4.0, 4.1, 4.2, 5.0, 5.1, 5.2 |
   | allow_sw | 布尔 | 使用软编码模式，默认关闭                                     |
   | coder    | 整数 | 熵编码模式:CAVLC, VLC, CABAC, AC                             |
   | realtime | 布尔 | 如果编码不够快则会开启实时编码模式，默认关闭                 |

2. OSX硬编解码使用示例

   使用h264_vda对input.mp4的视频解码，然后使用h264_videotoolbox进行编码，输出视频码率为2Mbit/s的文件output.mp4；

   例：

   ```sh
   ./ffmpeg -vcodec h264_vda -i input.mp4 -vcodec h264_videotoolbox -b:v 2000k output.mp4
   ```

## FFmpeg输出MP3

### MP3编码参数介绍

MP3编码参数

| 参数              | 类型 | 说明                                                         |
| ----------------- | ---- | ------------------------------------------------------------ |
| b                 | 布尔 | 设置MP3编码的码率                                            |
| joint_stereo      | 布尔 | 设置环绕立体声模式                                           |
| abr               | 布尔 | 设置编码为ABR状态，自动调整码率                              |
| compression_level | 整数 | 设置压缩算法质量，参数设置为0~9区间的值即可，数值越大质量越差，但是编码速度越快 |
| q                 | 整型 | 设置恒质量的VBR。调用lame接口的话，设置global_quality变量具有同样的效果 |



### MP3的编码质量设置

在FFmpeg中进行MP3编码采用的是第三方库libmp3lame，所以进行MP3编码时，需要设置编码参数acodec为libmp3lame，命令行如下:

```sh
./ffmpeg -i INPUT -acodec libmp3lame OUTPUT.mp3
```

MP3基本信息与q参数的对应参数

| lame操作参数 | 平均码率/kbit/s | 码率区间/kbit/s | ffmpeg操作参数 |
| ------------ | --------------- | --------------- | -------------- |
| -b 320       | 320             | 320(CBR)        | -b:a 320k      |
| -v 0         | 245             | 220~260         | -q:a 0         |
| -v 1         | 225             | 190~250         | -q:a 1         |
| -v 2         | 190             | 170~210         | -q:a 2         |
| -v 3         | 175             | 150~195         | -q:a 3         |
| -v 4         | 165             | 140~185         | -q:a 4         |
| -v 5         | 130             | 120~150         | -q:a 5         |
| -v 6         | 115             | 100~130         | -q:a 6         |
| -v 7         | 100             | 80~120          | -q:a 7         |
| -v 8         | 85              | 70~105          | -q:a 8         |
| -v 9         | 65              | 45~85           | -q:a 9         |

将生成的output.mp3的码率区间设置在70kbit/s至105kbit/s之间:

```sh
./ffmpeg -i input.mp3 -acodec libmp3lame -q:a 8 output.mp3
```

生成编码为MP3的音频

```sh
./ffmpeg -i input.mp3 -acodec libmp3lame -b:a 64k output.mp3
```



### 平均码率编码参数ABR

控制MP3编码为ABR编码方式；

例：

```sh
./ffmpeg -i input.mp3 -acodec libmp3lame -b:a 64k -abr 1 output.mp3
```



## FFmpeg输出AAC

与MP3相比，AAC是一种编码效率更高，编码音质更好的音频编码格式，常见的使用AAC编码后的文件存储格式为m4a，如在iPhone或者iPad中即为m4a。FFmpeg可以支持AAC的三种编码器具体如下:

- aac: FFmpeg本身的AAC编码实现
- libfaac: 第三方的AAC编码器
- libfdk_aac: 第三方的AAC编码器

### FFmpeg中的AAC编码器使用

将编码为AAC音频，码率为160kbit/s，编码生成的输出文件为output.aac文件；例：

```sh
./ffmpeg -i input.mp4 -c:a aac -b:a 160k output.aac
```

### FDK AAC第三方的AAC编解码Codec库

FDK-AAC库是FFmpeg支持的第三方编码库中质量最高的AAC编码库

1. 恒定码率(CBR)模式

   > 如果使用libfdk_aac设定一个恒定的码率，改变编码后的大小，并且可以兼容HE-AAC Profile，则可以根据音频设置的经验设置码率；
   >
   > 
   >
   > 例：使用libfdk_aac将input.wav转为恒定码率为128kbit/s，编码为AAC的output.m4a音频文件:
   >
   > ```sh
   > ./ffmpeg -i input.wav -c:a libfdk_aac -b:a 128k output.m4a
   > ```
   >
   > 例：将input.mp4的视频文件按照原有的编码方式进行输出封装，将音频以libfdk_aac进行编码，音频通道为环绕立体声，码率为384kbit/s，封装格式为output.mp4

2. 动态码率(VBR)模式

   使用VBR可以有更好的音频质量，使用libfdk_aac进行VBR模式的AAC编码时，可以设置5个级别:
   AAC编码信息:

   - LC: Low Complexity AAC, 这种编码相对来说体积比较大，质量稍差
- HE: High-Efficiency AAC, 这种编码相对来说体积稍小，质量较好
   - HEv2: High-Efficiency AAC version 2, 这种编码相对来说体积小，质量优

   AAC编码级别参数:
   
   | VBR  | 每声道码率/(kbit/s) | 编码信息     |
   | ---- | ------------------- | ------------ |
   | 1    | 20~32               | LC, HE, HEv2 |
   | 2    | 32~40               | LC, HE, HEv2 |
   | 3    | 48~56               | LC, HE, HEv2 |
   | 4    | 64~72               | LC           |
   | 5    | 96~112              | LC           |
   
   
   例:将input.wav的音频转为音频编码为libfdk_aac的output.m4a音频文件:
   
   ```sh
   ./ffmpeg -i input.wav -c:a libfdk_aac -vbr 3 output.m4a
   ```

### 高质量AAC设置

1. HE-AAC音频编码设置

   ```sh
   ./ffmpeg -i input.wav -c:a libfdk_aac -profile:a aac_he -b:a 64k output.m4a
   ```

2. HEv2-AAC音频编码设置

   ```sh
   ./ffmpeg -i input.wav -c:a libfdk_aac -profile:a aac_he_v2 -b:a 32k output.m4a
   ```

### AAC音频质量对比

AAC-LC的音频编码可以采用libfaac, libfdk_aac, FFmpeg内置AAC三种，其质量顺序排列如下:

- libfdk_aac 音频编码质量最优
- FFmpeg内置AAC编码次于libfdk_aac但优于libfaac
- libfaac在FFmpeg内置AAC编码为实验品时是除了libfdk_aac之外的唯一选择

**注意:在新版本的FFmpeg中，libfaac已经被删除**

