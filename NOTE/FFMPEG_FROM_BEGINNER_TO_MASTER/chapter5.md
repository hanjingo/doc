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

   在使用FFmpeg打开直播或者点播文件时，可以通过seek