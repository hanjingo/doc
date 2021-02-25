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
|x264-params|字符串|与x264操作相同|

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
|-|Baseline|Extented|Main|High|High10|High 4:2:2|High 4:4:4 (Predictive)|
|:--|:--|:--|:--|:--|:--|:--|:--|

todo

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