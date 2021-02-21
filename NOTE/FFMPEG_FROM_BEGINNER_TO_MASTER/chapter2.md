# 第二章 FFmpeg工具使用基础
## ffmpeg常用命令
ffmpeg在做音视频编解码时非常方便，所以在很多场景下转码使用的是ffmpeg,通过ffmpeg --help可以看到ffmpeg常见的命令大概分为6个部分，具体如下:
- ffmpeg信息查询部分
- 公共操作参数部分
- 文件主要操作参数部分
- 视频操作参数部分
- 音频操作参数部分
- 字母操作参数部分
通过ffmpeg --help查看到的help信息是ffmpeg命令的基础信息，如果想获得高级参数部分，那么可以通过使用ffmpeg --help long参数来查看，如果希望获得全部的帮助信息，那么可以通过使用ffmpeg --help full参数来获得。
### 常用的命令
- ffmpeg -formats: 查看当前使用的ffmpeg是否支持对应的视频文件格式
- ffmpeg -codecs: 查看全部信息
- ffmpeg -encoders: 查看是否支持H.264编码器
- ffmpeg -decoders: 查看是否支持H.264解码器

### ffmpeg的封装转换
ffmpeg的封装转换（转封装）功能包含在AVFormat模块中，通过libavformat库进行Mux和Demux操作；

**ffmpeg AVFormatContext主要参数帮助**
|参数|类型|说明|
|:--|:--|:--|
|avioflags|标记|format的缓冲设置，默认为0，就是有缓冲|
|avioflags|direct|无缓冲状态|
|probesize|整数|在进行媒体数据处理前获得文件内容的大小，可以用在预读取文件头时提高速度，也可以设置足够大的值来读取到足够多的音视频数据信息|
|fflags|标记|-|
|fflags|flush_packets|立即将packets数据刷新写入文件中|
|fflags|genpts|输出时按照正常规则产生pts|
|fflags|nofillin|不填写可以精确计算缺失的值|
|fflags|igndts|忽略dts|
|fflags|discardcorrupt|丢弃损坏的帧|
|fflags|sortdts|尝试以dts的顺序为准输出|
|fflags|keepside|不合并数据|
|fflags|fastseek|快速seek(定位)操作，但是不够精确|
|fflags|latm|设置RTP MP4_LATM生效|
|fflags|nobuffer|直接读取或写出，不存入buffer,用于在直播采集时降低延迟|
|fflags|bitexact|不写入随机或者不稳定的数据|
|seek2any|整数|支持随意位置seek,这个seek不以keyframe为参考|
|analyzeduration|整数|指定解析媒体所需要花销的时间，这里设置的值越高，解析越准确，如果在直播中为了降低延迟，这个值可以设置得低一些|
|codec_whitelist|列表|设置可以解析的codec的白名单|
|format_whitelist|列表|设置可以解析的format的白名单|
|output_ts_offset|整数|设置输出文件的起始时间|

### ffmpeg的转码参数
ffmpeg AVCodecContext主要参数帮助
|参数|类型|说明|
|:--|:--|:--|
|b|整数|设置音频和视频码率，可以认为是音视频加起来的码率，默认为200kbit/s使用这个参数可以根据b:v设置视频码率,b:a设置音频码率|
|ab|整数|设置音频的码率，默认是128kbit/s|
|g|整数|设置视频GOP(可以理解为关键帧间隔)大小，默认是12帧一个GOP|
|ar|整数|设置音频采样率，默认为0|
|ac|整数|设置音频通道数，默认为0|
|bf|整数|设置连续编码为B帧的个数，默认为0|
|maxrate|整数|最大码率设置，与bufsize一同使用即可，默认为0|
|minrate|整数|最小码率设置，配合maxrate与bufsize可以设置为CBR模式，平时很少使用，默认为0|
|bufsize|整数|设置控制码率的buffer的大小，默认为0|
|keyint_min|整数|设置关键帧最小间隔，默认为25|
|sc_threshold|整数|设置场景切换支持，默认为0|
|me_threshold|整数|设置运动估计阀值，默认为0|
|mb_threshold|整数|设置宏块阀值，默认为0|
|profile|整数|设置音视频的profile，默认为-99|
|level|整数|设置音视频的level，默认为-99|
|timecode_frame_start|整数|设置GOP帧的开始时间，需要在non-drop-frame默认情况下使用|
|channel_layout|整数|设置音频通道的布局格式|
|threads|整数|设置编解码工作的线程数|

### ffmpeg的基本转码原理
例:
```sh
./ffmpeg -i ~/Movies/input1.rmvb -vcodec mpeg4 -b:v 200k -r 15 -an output.mp4
```
功能解释:
- 转封装格式从RMVB格式转换为MP4格式
- 视频编码从RV40转换为MPEG4格式
- 视频码率从原来的377kbit/s转换为200kbit/s
- 视频帧率从原来的23.98fps转换为15fps
- 转码后的文件中不包括音频(-an参数)

## ffprobe常用命令
ffprobe主要用来查看多媒体文件的信息，常用参数比较多
- ffprobe --help: 查看详细的帮助信息
- ffprobe -show_packets input.flv: 查看多媒体数据包信息

packet字段说明:
|字段|说明|
|:--|:--|
|codec_type|多媒体类型，如视频包，音频包等|
|stream_index|多媒体的stream索引|
|pts|多媒体的显示时间值|
|pts_time|根据不同格式计算过后的多媒体的显示时间|
|dts|多媒体解码时间值|
|dts_time|根据不同格式计算过后的多媒体解码时间|
|duration|多媒体包占用的时间值|
|duration_time|根据不同格式计算过后的多媒体包所占用的时间值|
|size|多媒体包的大小|
|pos|多媒体包所在的文件偏移位置|
|flags|多媒体包标记，如关键包与非关键包的标记|
- ffprobe -show_data -show_packets input.flv: 查看包中的具体数据
- ffprobe -show_format output.mp4: 查看多媒体的封装格式

format字段说明:
|字段|说明|
|:--|:--|
|filename|文件名|
|nb_streams|媒体中包含的流的个数|
|nb_programs|节目数|
|format_name|使用的封装模块的名称|
|format_long_name|封装的完整名称|
|start_time|媒体文件的起始时间|
|duration|媒体文件的总时间长度|
|size|媒体文件的大小|
|bit_rate|媒体文件的码率|
- ffprobe -show_frame input.flv: 查看视频文件中的帧信息

frame字段说明:
|属性|说明|值|
|:--|:--|:--|
|media_type|帧的类型(视频，音频，字幕等)|video|
|stream_index|帧所在的索引区域|0|
|key_frame|是否为关键帧|1|
|pkt_pts|Frame包的pts|0|
|pkt_pts_time|Frame包的pts的时间显示|0.080000|
|pkt_dts|Frame包的dts|80|
|pkt_dts_time|Frame包的dts的时间显示|0.080000|
|pkt_duration|Frame包的时长|N/A|
|pkt_duration_time|Frame包的时长时间显示|N/A|
|pkt_pos|Frame包所在文件的偏移位置|344|
|width|帧显示的宽度|1280|
|height|帧显示的高度|714|
|pix_fmt|帧的图像色彩格式|yuv420p|
|pict_type|帧类型|I|
- ffprobe -show_stream: 查看多媒体文件中的流信息

stream字段说明:
|属性|说明|值|
|:--|:--|:--|
|index|流所在的索引区域|0|
|codec_name|编码名|h264|
|codec_long_name|编码全名|MPEG-4 part 10|
|profile|编码的profile|High|
|level|编码的level|31|
|has_b_frames|包含B帧信息|2|
|codec_type|编码类型|video|
|codec_time_base|编码的时间戳计算基础单位|1/50|
|pix_fmt|图像显示的色彩格式|yuv420p|
|coded_width|图像的宽度|1280|
|coded_height|图像的高度|714|
|codec_tag_string|编码的标签数据|\[0\]\[0\]\[0\]\[0\]|

stream字段其他说明
|属性|说明|值|
|:--|:--|:--|
|r_frame_rate|实际帧率|25/1|
|avg_frame_rate|平均帧率|25/1|
|time_base|时间基数（用来进行timestamp计算）|1/1000|
|bit_rate|码率|200000|
|max_bit_rate|最大码率|N/A|
|nb_frames|帧数|N/A|

- ffprobe -print_format 或者 ffprobe -of: 进行格式化的显示
- ffprobe -of ini -show_streams input.flv: 得到的INI格式的输出
- ffprobe -of flat -show_streams input.flv: 输出FLAT格式
- ffprobe -of json -show_packets input.flv: 输出JSON格式
- ffprobe -of csv -show_packets input.flv: 输出CSV格式
- ffprobe -show_frame -select_streams v -of xml input.mp4: 查看视频的frame信息

## ffplay常用命令
### ffplay常用参数
ffplay不仅仅是播放器，同时也是测试ffmpeg的codec引擎，format引擎，以及filter引擎的工具，并且还可以进行可视化的媒体参数分析，其看可以通过ffplay --help进行查看:

ffplay基础帮助信息
|参数|说明|
|:--|:--|
|x|强制设置视频显示窗口的宽度|
|y|强制设置视频显示框口的高度|
|s|设置视频现实的宽高|
|fs|强制全屏显示|
|an|屏蔽音频|
|vn|屏蔽视频|
|sn|屏蔽字幕|
|ss|根据设置的秒进行定位拖动|
|t|设置播放视频/音频的长度|
|bytes|设置定位拖动的策略，0为不可拖动，1为可拖动，-1为自动|
|nodisp|关闭图形化显示窗口|
|f|强制使用设置的格式进行解析|
|window_title|设置显示窗口的标题|
|af|设置音频的滤镜|
|codec|强制使用设置的codec进行解码|
|autorotate|自动旋转视频|

例:
- 如果希望从视频的第30秒开始播放，播放10秒钟的文件，则可以使用如下命令:
```sh
ffplay -ss 30 -t 10 input.mp4
```
- 如果希望视频播放时播放器的窗口显示标题为自定义标题，则可以使用如下命令:
```sh
ffplay -windows_title "Hello World, This is a sample" output.mp4
```
- 如果希望使用ffplay打开网络直播流,则可以使用如下命令:
```sh
ffplay -window_title "播放测试" rtmp://up.v.test.com/live/stream
```

### ffplay高级参数
通过使用ffplay --help参数可以看到比较多的帮助信息，期中包含了高级参数介绍，具体如下:
|参数|说明|
|:--|:--|
|ast|设置将要播放的音频流|
|vst|设置将要播放的视频流|
|sst|设置将要播放的字幕流|
