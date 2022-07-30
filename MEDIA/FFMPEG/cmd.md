# FFmpeg速查手册

[TOC]



## 查询

| 效果                           | 命令                                         |
| ------------------------------ | -------------------------------------------- |
| 查看是否支持对应的视频文件格式 | `ffmpeg -formats`                            |
| 查看全部信息                   | `ffmpeg -codecs`                             |
| 查看是否支持H.264编码器        | `ffmpeg -encoders`                           |
| 查看是否支持H.264解码器        | `ffmpeg -decoders`                           |
| 查看详细的帮助信息             | `ffprobe --help`                             |
| 查看多媒体数据包信息           | `ffprobe -show_packets input.flv`            |
| 查看包中的具体数据             | `ffprobe -show_data -show_packets input.flv` |
| 查看多媒体的封装格式           | `ffprobe -show_format output.mp4`            |
| 查看视频文件中的帧信息         | `ffprobe -show_frame input.flv`              |
| 查看多媒体文件中的流信息       | `ffprobe -show_stream`                       |



## 播放

| 效果                                                         | 命名                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 从视频的第30秒开始播放，播放10秒钟                           | `ffplay -ss 30 -t 10 input.mp4`                              |
| 视频播放时播放器的窗口显示标题为自定义标题                   | `ffplay -windows_title "Hello World, This is a sample" output.mp4` |
| 打开网络直播流                                               | `ffplay -window_title "播放测试" rtmp://up.v.test.com/live/stream` |
| 从20秒播放一个视频，播放时长为10秒钟，播放完成后自动退出ffplay,播放器窗口标题为"Hello World" | `time ffplay -window_title "Hello World" -ss 20 -t 10 -autoexit output.mp4` |
| 加载SRT字幕                                                  | `ffplay -window_title "Test Movie" -vf "subtitles=input.srt" output.mp4` |
| 播放音频文件，播放的时候将解码后的音频数据以音频波形的形式显示出来 | `ffplay -showmode 1 output.mp3`                              |
| 通过ffplay查看B帧预测与P帧预测信息                           | `ffplay -flags2 +export_mvs -ss 40 output.mp4 -vf codecview=mv=pf+bf+bb` |



## 编解码

| 效果                                                      | 命令行                                                       |
| --------------------------------------------------------- | ------------------------------------------------------------ |
| 查看MP4文件的Demuxer信息                                  | `ffmpeg -h demuxer=mp4`                                      |
| 将音频从AC3转换为AAC或者MP3这类FLV标准支持的音频          | `ffmpeg -i input_ac3.mp4 -vcodec copy -acode aac -f flv output.flv` |
| 将FLV文件中的关键帧建立一个索引，并将索引写入Metadata头中 | `ffmpeg -i input.mp4 -c copy -f flv -flvflags add_keyframe_index output.flv` |
| 从文件转换HLS直播                                         | `ffmpeg -re -i input.mp4 -c copy -f hls -bsf:v h264_mp4toannexb output.m3u8` |
| 抽取音视频文件中的AAC音频流                               | `ffmpeg -i input.mp4 -vn -acodec copy output.aac`            |
| 抽取音视频文件中的H.264视频流                             | `ffmpeg -i input.mp4 -vcodec copy -an output.h264`           |
| 抽取音视频文件中的H.265数据                               | `ffmpeg -i input.mp4 -vcodec copy -an -bsf hevc_mp4toannexb -f hevc output.hevc` |




## 转码

将input.mp4的视频像素改变为1920x1080,将码率改变为2000kbit/s,输出为output.mp4：

```sh
ffmpeg -hwaccel cuvid -vcodec h264_cuvid -i input.mp4 -vf scale_npp=1920:1080 -vcodec h264_nvenc -acodec copy -f mp4 -y output.mp4
```



## 流媒体录制与输出

TCP方式录制RTSP直播流

```sh
ffmpeg -rtsp_transport tcp -i rtsp://47.90.47.25/test.ts -c copy -f mp4 output.mp4
```

拉取FLV直播流录制为FLV

```sh
ffmpeg -i http://bbs.chinaffmpeg.com/live.flv -c copy -f flv output.flv
```

拉取TS直播流录制为FLV

```sh
ffmpeg -i http://bbs.chinaffmpeg.com/live.ts -c copy -f flv output.flv
```

拉取HLS直播流录制为FLV

```sh
ffmpeg -i http://bbs.chinaffmpeg.com/live.m3u8 -c copy -f flv output.flv
```

一次转码多次输出RTMP流

```sh
ffmpeg -i input.mp4 -vcodec libx264 -acodec aac -f flv - | ffmpeg -f flv -i - -c copy -f flv rtmp://publish.chinaffmpeg.com/live/stream1 -c copy -f flv rtmp://publish.chinaffmpeg.com/live/stream2
```

