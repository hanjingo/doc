# 第五章 FFmpeg流媒体

## FFmpeg发布与录制RTMP流

### RTMP参数

| 参数           | 类型       | 说明                                                         |
| -------------- | ---------- | ------------------------------------------------------------ |
| rtmp_app       | 字符串     | RTMP流发布点，又称为APP                                      |
| rtmp_buffer    | 整数       | 客户端buffer大小（单位:ms），默认3秒                         |
| rtmp_conn      | 字符串     | 在RTMP的Connect命令中增加自定义AMF数据                       |
| rtmp_flashver  | 字符串     | 设置模拟的flashplugin的版本号                                |
| rtmp_live      | 整数       | 指定RTMP流媒体播放类型，具体如下: any:直播或点播随意; live:直播; recorded:点播; |
| rtmp_gateurl   | 字符串     | RTMP在Connect命令中设置的PageURL字段，其为播放时所在的Web页面URL |
| rtmp_playpath  | 字符串     | RTMP流播放的Stream地址，或者称为秘钥，或者称为发布流         |
| rtmp_subscribe | 字符串     | 直播流名称，默认设置为rtmp_playpath的值                      |
| rtmp_swfhash   | 二进制数据 | 解压swf文件后的SHA256的hash值                                |
| rtmp_swfsize   | 整数       | swf文件解压后的大小，用于swf认证                             |
| rtmp_swfurl    | 字符串     | RTMP的Connect命令中设置的swfURL播放器的URL                   |
| rtmp_swfverify | 字符串     | 设置swf认证时swf文件的URL地址                                |
| rtmp_tcurl     | 字符串     | RTMP的Connect命令中设置的tcURL目标发布点地址，一般形如rtmp://xxx.xxx.xxx/app |
| rtmp_listen    | 整数       | 开启RTMP服务时所监听的端口                                   |
| listen         | 整数       | 与rtmp_listen相同                                            |
| timeout        | 整数       | 监听rtmp端口时设置的超时时间，以秒为单位                     |

### RMP参数举例

1. rtmp_app参数

   使用rtmp_app参数可以设置RTMP得推流发布点:

   ```sh
   ffmpeg -rtmp_app live -i rtmp://publish.chinaffmpeg.com -c copy -f flv output.flv
   ```

2. rtmp_playpath参数

   通过使用rtmp_playpath来解决identify stream failed错误

   ```sh
   ffmpeg -re -i input.mp4 -c copy -f flv -rtmp_app live -rtmp_playpath class rtmp://publish.chinaffmpeg.com
   ```

   省略rtmp_app与rtmp_playpath参数

   ```sh
   ./ffmpeg -i input.mp4 -c copy -f flv rtmp://publish.chinaffmpeg.com/lib/class
   ```

   拉流录制

   ```sh
   ./ffmpeg -i rtmp://publish.chinaffmpeg.com/live/class -c copy -f flv output.flv
   ```

3. rtmp_pageurl, rtmp_swfurl, rtmp_tcurl参数

   设置pageUrl

   ```sh
   ./ffmpeg -rtmp_pageurl "http://www.chinaffmpeg.com" -i rtmp://publish.chinaffmpeg.com/live/class
   ```

## FFmpeg录制RTSP流

### FFmpeg操作RTSP的参数

| 参数                | 类型   | 说明                                                         |
| ------------------- | ------ | ------------------------------------------------------------ |
| initial_pause       | 布尔   | 建立连接后暂停播放                                           |
| rtsp_transport      | 标记   | 设置RTSP传输协议，具体如下: udp: UDP; tcp: TCP; udp_multicast: UDP多播协议; http: HTTP隧道; |
| rtsp_flags          | 标记   | RTSP使用标记，具体如下: filter_src: 只接受指定IP的流; listen: 设置为被动接受模式; prefer_tcp: TCP亲和模式，如果TCP可用则首选TCP传输 |
| allowed_media_types | 标记   | 设置允许接受的数据模式(默认为全部开启): video: 只接收视频; audio: 只接收音频; data: 只接收数据; sbutitle: 只接收字幕; |
| min_port            | 整数   | 设置最小本地UDP端口，默认5000                                |
| max_port            | 整数   | 设置最大本地UDP端口，默认65000                               |
| timeout             | 整数   | 设置监听端口超时时间                                         |
| reorder_queue_size  | 整数   | 设置录制数据buffer的大小                                     |
| buffer_size         | 整数   | 设置底层传输包buffer的大小                                   |
| user-agent          | 字符串 | 用户客户端标识                                               |

### RTSP参数使用举例

1. TCP方式录制RTSP直播流

   ```sh
   ./ffmpeg -rtsp_transport tcp -i rtsp://47.90.47.25/test.ts -c copy -f mp4 output.mp4
   ```

2. User-Agent设置参数

   ```sh
   ./ffmpeg -user-agent "ChinaFFmpeg-Player" -i rtsp://input:554/live/1/stream.sdp -c copy mp4 -y output.mp4
   ```

## FFmpeg录制HTTP流

### FFmpeg操作HTTP的参数

| 参数              | 类型       | 说明                             |
| ----------------- | ---------- | -------------------------------- |
| seekable          | 布尔       | 设置HTTP链接为可以seek操作       |
| chunked_post      | 布尔       | 使用Chunked模式post数据          |
| http_proxy        | 字符串     | 设置HTTP代理传输数据             |
| headers           | 字符串     | 自定义HTTP Header数据            |
| content_type      | 字符串     | 设置POST的内容类型               |
| user_agent        | 字符串     | 设置HTTP的请求客户端信息         |
| multiple_requests | 布尔       | HTTP长连接开启                   |
| post_data         | 二进制数据 | 设置将要POST的数据               |
| cookies           | 字符串     | 设置HTTP请求时写代码的Cookies    |
| icy               | 布尔       | 请求ICY元数据：默认打开          |
| auth_type         | 整数       | HTTP验证类型设置                 |
| offset            | 整数       | 初始化HTTP请求时的偏移位置       |
| method            | 字符串     | 发起HTTP请求时使用的HTTP的方法   |
| reconnect         | 布尔       | 在EOF之前断开发起重连            |
| reconnect_at_eof  | 布尔       | 在得到EOF时发起重连              |
| reply_code        | 整数       | 作为HTTP服务时向客户端反馈状态码 |

### HTTP参数使用举例

1. seekable参数举例

   在使用FFmpeg打开直播或者点播文件时，可以通过seek操作进行播放进度移动，定位等操作:
   
   ```sh
   ./ffmpeg -ss 300 -seekable 0 -i http://bbs.chinaffmpeg.com/test/ts -c copy output.mp4
   ```
   
2. headers参数举例

   在HTTP传输时在header中增加referer字段:

   ```sh
   ./ffmpeg -headers "referer: http://bbs.chinaffmpeg.com/index.html" -i http://play.chinaffmpeg.com/live/class.flv -c copy -f flv -y output.flv
   ```

3. user_agent参数设置

   将User-Agent被设置为LiuQi's Player:

   ```sh
   ./ffmpeg -user_agent "LiuQi's Player" -i http://bbs.chinaffmpeg.com/1.flv
   ```

## HTTP拉流录制

### 拉取HTTP中的流录制FLV

1. 拉取FLV直播流录制为FLV:

   ```sh
   ./ffmpeg -i http://bbs.chinaffmpeg.com/live.flv -c copy -f flv output.flv
   ```

2. 拉取TS直播流录制为FLV：

   ```sh
   ./ffmpeg -i http://bbs.chinaffmpeg.com/live.ts -c copy -f flv output.flv
   ```

3. 拉取HLS直播流录制为FLV：

   ```sh
   ./ffmpeg -i http://bbs.chinaffmpeg.com/live.m3u8 -c copy -f flv output.flv
   ```

### TCP参数使用举例

1. TCP监听接收流

   ```sh
   ./fffmpeg -listen 1 -f flv -i tcp://127.0.0.1:1234/live/stream -c copy -f flv output.flv
   ```

2. TCP请求发布流

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f flv tcp://127.0.0.1:1234/live/stream
   ```

3. 监听端口超时listen_timeout

   超时时间为5秒，5秒内未收到任何请求则自动退出监听

   ```sh
   time ./ffmpeg -listen_timeout 5000 -listen 1 -f flv -i tcp://127.0.0.1:1234/live/stream -c copy -f flv output.flv
   ```

4. TCP拉流超时参数timeout

   设置超时时间为20秒，连接TCP拉取端口1935的数据，如果超过20秒没有收到数据则自动退出

   ```sh
   time ./ffmpeg -timeout 20000000 -i tcp://192.168.100.179:1935/live/stream -c copy -f flv output.flv
   ```

5. TCP传输buffer大小设置send_buffer_size/recv_buffer_size

   设置TCP传输时buffer的大小，buffer设置的越小，传输就会越频繁，网络开销就会越大:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -send_buffer_size 265 -f flv tcp://192.168.100.179:1234/live/stream
   ```

6. 绑定本地UDP端口localport

   设置监听本地端口:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -localport 23456 -f flv udp://192.168.100.179:1234/live/stream
   ```

## FFmpeg推多路流

### 管道方式输出多路流

使用系统管道的方式进行一次转码多次输出RTMP流

```sh
./ffmpeg -i input -acodec aac -vcodec libx264 -f flv - | ffmpeg -f mpegts -i - -c copy output1 -c copy output2 -c copy output3
```

另一种方法:

```sh
./ffmpeg -i input.mp4 -vcodec libx264 -acodec aac -f flv - | ffmpeg -f flv -i - -c copy -f flv rtmp://publish.chinaffmpeg.com/live/stream1 -c copy -f flv rtmp://publish.chinaffmpeg.com/live/stream2
```

### tee封装格式输出多路流

编码一次，输出tee封装格式，格式中包含2个FLV格式的RTMP流，一路为stream1，另一路为stream2:

```sh
./ffmpeg -re -i input.mp4 -vcodec libx264 -acodec aac -map 0 -f tee "[f=flv]rtmp://publish.chinaffmpeg.com/live/stream1 | [f=flv]rtmp://publish.chinaffmpeg.com/live/stream2"
```

### tee协议输出多路流

FFmpeg在3.1.3版本之后支持tee协议输出多路流

```sh
./ffmpeg -re -i input.mp4 -vcodec libx264 -acodec aac -f flv "tee:rtmp://publish.chinaffmpeg.com/live/stream1|rtmp://publish.chinaffmpeg.com/live/stream2"
```

## FFmpeg生成HDS流

### HDS参数说明

| 参数              | 类型 | 说明                                |
| ----------------- | ---- | ----------------------------------- |
| window_size       | 整数 | 设置HDS文件列表的最大文件数         |
| extra_window_size | 整数 | 设置HDS文件列表之外的文件保留数     |
| min_frag_duration | 整数 | 设置切片文件时长（单位：微秒）      |
| remove_at_exit    | 布尔 | 生成HDS文件退出时删除所有列表及文件 |

### HDS使用举例

1. window_size参数控制文件列表大小

   生成output目录，目录下面包含三种文件:

   - index.f4m: 索引文件，主要为F4M参考标准中mainfest相关，Metadata信息等
   - stream0.abst: 文件流相关描述信息
   - stream0Seg1-Frag: 相似规则文件切片，文件切片中均为mdat信息

   ```sh
   ./ffmpeg -i input -c copy -f hds -window_size 4 output
   ```

2. extra_window_size参数控制文件个数

   使用extra_window_size可以控制残留文件个数

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f hds -window_size 4 -extra_window_size 1 output
   ```

## FFmpeg生成DASH流

FFmpeg生成DASH的参数:

| 参数              | 类型   | 说明                         |
| ----------------- | ------ | ---------------------------- |
| window_size       | 整数   | 索引文件中文件的条目数       |
| extra_window_size | 整数   | 索引文件之外的切片文件保留数 |
| min_seg_duration  | 整数   | 最小切片时长（微秒）         |
| remove_at_exit    | 布尔   | 当FFmpeg退出时删除所有切片   |
| use_template      | 布尔   | 按照模板切片                 |
| use_timeline      | 布尔   | 设置切片模板为时间模板       |
| single_file       | 布尔   | 设置切片为单文件模式         |
| single_file_name  | 字符串 | 设置切片文件命名模板         |
| init_seg_name     | 字符串 | 设置切片出事命名模板         |
| media_seg_name    | 字符串 | 设置切片文件名模板           |

### DASH参数使用举例

1. window_size与extra_window_size参数举例

   生成文件索引列表index.mpd，文件列表长度为4个切片长度，切片之外会保留5个切片

   ```sh
   ./ffmpeg -re -i input.mp4 -c:v copy -acodec copy -f dash -window_size 4 -extra_window_size 5 index.mpd
   ```

2. single_file参数举例

   生成3个文件:1个索引文件，1个音频文件，1个视频文件

   ```sh
   ./ffmpeg -re -i input.mp4 -c:v copy -acodec copy -f dash -window_size 4 -extra_window_size 5 -single_file 1 index.mpd
   ```

   