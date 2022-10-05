#  HLS(HTTP Live Streaming)协议

<!-- vim-markdown-toc GFM -->

* [参考](#参考)
* [组成](#组成)
* [编码要求](#编码要求)
* [播放](#播放)
    - [苹果: 使用Safari 浏览器直接就能打开 m3u8 地址，如:](#苹果-使用safari-浏览器直接就能打开-m3u8-地址如)
    - [安卓: 需要使用 html5 的 video 标签，然后在浏览器中打开这个页面](#安卓-需要使用-html5-的-video-标签然后在浏览器中打开这个页面)
* [m3u8](#m3u8)
    - [m3u8多码率支持](#m3u8多码率支持)

<!-- vim-markdown-toc -->



## 参考
* [HLS协议解析](https://www.cnblogs.com/jimodetiantang/p/9133564.html)
* [ HTTP Live Streaming draft-pantos-http-live-streaming-18](https://tools.ietf.org/html/draft-pantos-http-live-streaming-18)
* [hls之m3u8、ts流格式详解](https://my.oschina.net/u/727148/blog/666824)

## 组成
* 传输协议: HTTP
* 索引文件: M3U8
* 音视频数据容器: TS

## 编码要求
* 视频: H264
* 音频: AAC, MP3, AC-3
* 音视频数据容器: ts
* 索引文件: m3u8

## 播放
### 苹果: 使用Safari 浏览器直接就能打开 m3u8 地址，如:
```
http://demo.srs.com/live/livestream.m3u8
```

### 安卓: 需要使用 html5 的 video 标签，然后在浏览器中打开这个页面
```
<!-- livestream.html -->
<video width="640" height="360"
        autoplay controls autobuffer 
        src="http://demo.srs.com/live/livestream.m3u8"
        type="application/vnd.apple.mpegurl">
</video>
```

## m3u8
以 utf-8 编码的 m3u 文件，这个文件本身不能播放，只是存放了播放信息的文本文件,结构如下
1. #EXTM3U	
	
	> 每个 m3u8 文件第一行必须是这个 tag
	
2. #EXTINF 
	> 指定每个媒体段（ts）的时长(受gop影响)，这个仅对其后面的 URI 有效，每两个媒体段 URI 间被这个 tag 分隔开其格式为：
	```
	#EXTINF:<duration>,<title>
	
	duration：表示持续的时间（秒）
	```
	
3. #EXT-X-BYTERANGE
	> 表示媒体段是一个媒体 URI 资源中的一段，只对其后的 media URI 有效，格式为：
	```
	#EXT-X-BYTERANGE:<n>[@o]
	
	n：表示这个区间的大小
	o：表示在 URI 中的 offset
	```

4. #EXT-X-TARGETDURATION：
	> 指定当前视频流中的单个切片（即 ts）文件的最大时长（秒）。所以 #EXTINF 中指定的时间长度必须小于或是等于这个最大值。这个 tag 在整个 Playlist 文件中只能出现一次（在嵌套的情况下，一般有真正
	ts url 的 m3u8 才会出现该 tag）。格式为：
	```
	#EXT-X-TARGETDURATION:<s>
	
	s：表示最大的秒数
	```

5. #EXT-X-MEDIA-SEQUENCE：
	> 每一个 media URI 在 Playlist 中只有唯一的序号，相邻之间序号 +1。格式为：
	```
	#EXT-X-MEDIA-SEQUENCE:<number>
	
	一个 media URI 并不是必须要包含的，如果没有，默认为 0.
	```

6. #EXT-X-KEY：
	> 表示怎么对 media segments 进行解码。其作用范围是下次该 tag 出现前的所有 media URI。格式为：
	```
	#EXT-X-KEY:<attribute-list>
	
	如果为:NONE，则 URI 以及 IV 属性必须不存在，如果是 AES-128(Advanced Encryption Standard)，则 URI 必须存在，IV 可以不存在。
	
	对于 AES-128 的情况，keytag 和 URI 属性共同表示了一个 key 文件，通过 URI 可以获得这个 key，如果没有 IV（Initialization Vector），则使用序列号作为 IV 进行编解码，将序列号的高位赋到 16 个字节的 buffer 中，左边补 0；如果有 IV，则将该值当成 16 个字节的 16 进制数。
	```

7. #EXT-X-PROGRAM-DATE-TIME:
	> 将一个绝对时间或是日期和一个媒体段中的第一个 sample 相关联，只对下一个 media URI 有效，格式如下：
	```
	#EXT-X-PROGRAM-DATE-TIME:<YYYY-MM-DDThh:mm:ssZ>
	
	例：#EXT-X-PROGRAM-DATE-TIME:2010-02-19T14:54:23.031+08:00
	```

8. #EXT-X-ALLOW-CACHE：
	> 是否允许做 cache，这个可以在 Playlist 文件中任意地方出现，并且最多只出现一次，作用效果是所有的媒体段。格式如下：
	```
	#EXT-X-ALLOW-CACHE:<YES|NO>
	```

9. #EXT-X-PLAYLIST-TYPE：
	> 提供关于 Playlist 的可变性的信息，这个对整个 Playlist 文件有效，是可选的，格式如下：
	```
	#EXT-X-PLAYLIST-TYPE:<EVENT|VOD>
	
	VOD，即为点播视频，服务器不能改变 Playlist 文件，换句话说就是该视频全部的 ts 文件已经被生成好了
	
	EVENT，就是实时生成 m3u8 和 ts 文件。服务器不能改变或是删除 Playlist 文件中的任何部分，但是可以向该文件中增加新的一行内容。它的索引文件一直处于动态变化中，播放的时候需要不断下载二级 index 文件
	```

10. #EXT-X-ENDLIST：
	
	> 表示 m3u8 文件的结束，live m3u8 没有该 tag。它可以在 Playlist 中任意位置出现，但是只能出现一个
	
11. #EXT-X-MEDIA:
	> 被用来在 Playlist 中表示相同内容的不同语种/译文的版本，比如可以通过使用 3 个这种 tag 表示 3 种不同语音的音频，或者用 2 个这个 tag 表示不同角度的 video。在 Playlist 中，这个标签是独立存在的，其格式如下:
	```
	#EXT-X-MEDIA:<attribute-list>
	
	该属性列表中包含：URI、TYPE、GROUP-ID、LANGUAGE、NAME、DEFAULT、AUTOSELECT。
	
	URI：如果没有，则表示这个 tag 描述的可选择版本在主 PlayList 的 EXT-X-STREAM-INF 中存在
	
	TYPE：AUDIO and VIDEO
	
	GROUP-ID：具有相同 ID 的 MEDIAtag，组成一组样式
	
	LANGUAGE：identifies the primary language used in the rendition
	
	NAME：The value is a quoted-string containing a human-readable description of the rendition. If the LANGUAGE attribute is present then this description SHOULD be in that language
	
	DEFAULT：YES 或是 NO，默认是 No，如果是 YES，则客户端会以这种选项来播放，除非用户自己进行选择
	
	AUTOSELECT：YES 或是 NO，默认是 No，如果是 YES，则客户端会根据当前播放环境来进行选择（用户没有根据自己偏好进行选择的前提下）
	
	The EXT-X-MEDIA tag appeared in version 4 of the protocol。
	```

12. #EXT-X-STREAM-INF：
	> 指定一个包含多媒体信息的 media URI 作为 Playlist，一般做 m3u8 的嵌套使用，它只对紧跟后面的 URI 有效，格式如下：
	```
	#EXT-X-STREAM-INF:<attribute-list> 常用的属性如下：
	
	BANDWIDTH：带宽，必须有
	
	PROGRAM-ID：该值是一个十进制整数，唯一地标识一个在 Playlist 文件范围内的特定的描述。一个 Playlist 文件中可能包含多个有相同 ID 的此 tag
	
	CODECS：指定流的编码类型，不是必须的
	
	RESOLUTION：分辨率
	
	AUDIO：这个值必须和 AUDIO 类别的 "EXT-X-MEDIA" 标签中 "GROUP-ID" 属性值相匹配
	
	VIDEO：同上
	```

13. #EXT-X-DISCONTINUITY：
	> 当遇到该 tag 的时候说明以下属性发生了变化：
	```
	file format
	number and type of tracks
	encoding parameters
	encoding sequence
	timestamp sequence
	```

14. #ZEN-TOTAL-DURATION：
	
	> 表示这个 m3u8 所含 ts 的总时间长度

### m3u8多码率支持
```
二级m3u8文件:
#EXTM3U
#EXT-X-VERSION:3
#EXT-X-ALLOW-CACHE:YES
#EXT-X-MEDIA-SEQUENCE:2
#EXT-X-TARGETDURATION:16
#EXTINF:14.357, no desc
livestream-2.ts
#EXTINF:15.617, no desc
livestream-3.ts
#EXTINF:14.358, no desc
livestream-4.ts
#EXTINF:15.618, no desc
livestream-5.ts
#EXTINF:11.130, no desc
livestream-6.ts

顶级m3u8文件:
#EXTM3U
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=1280000
http://example.com/low.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=2560000
http://example.com/mid.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=7680000
http://example.com/hi.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=65000,CODECS="mp4a.40.5"
http://example.com/audio-only.m3u8
```
