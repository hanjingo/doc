# 第三章 FFmpeg转封装

## 音视频文件转MP4格式

### MP4格式标准介绍

MP4的格式信息:

- MP4文件由许多Box与FullBox组成
- 每个Box由Header和Data两部分组成
- FullBox是Box的扩展，其在Box结构的基础上，在Header中增加8位version标志和24位的flags标志
- Header包含了整个Box的长度的大小(size)和类型(type),当size等于0时，代表这个Box是文件的最后一个Box。当size等于1时，说明Box长度需要更多的位来描述，在后面会定义一个64位的largesize用来描述Box的长度。当Type为uuid时，说明这个Box中的数据是用户自定义扩展类型
- Data为Box的实际数据，可以是纯数据，也可以是更多的子Box
- 当一个Box中Data是一系列的子Box时，这个Box又可以称为Container(容器)Box

MP4常用参考标准排列方式

容器名: 一级，二级，三级，四级，五级，六级

| 一级 | 二级 | 三级 | 四级 | 五级 | 六级 | 必选 | 描述                                 |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ------------------------------------ |
| ftyp |      |      |      |      |      | *    | 文件类型                             |
| pdin |      |      |      |      |      |      | 下载进度信息                         |
| moov |      |      |      |      |      | *    | 音视频数据的metadata信息             |
|      | mvhd |      |      |      |      | *    | 电影文件头                           |
|      | trak |      |      |      |      | *    | 流的track                            |
|      |      | tkhd |      |      |      | *    | 流信息的track头                      |
|      |      | tref |      |      |      |      | track参考容器                        |
|      |      | edts |      |      |      |      | edit list容器                        |
|      |      |      | elst |      |      |      | edit list元素信息                    |
|      |      | mdia |      |      |      | *    | track里面的media信息                 |
|      |      |      | mdhd |      |      | *    | media信息头                          |
|      |      |      | hdr  |      |      | *    | media信息的句柄                      |
|      |      |      | minf |      |      | *    | media信息的容器                      |
|      |      |      |      | vmhd |      |      | 视频media头（只存在于视频的track）   |
|      |      |      |      | smhd |      |      | 音频media头（只存在于音频的track）   |
|      |      |      |      | hmdh |      |      | 提示meida头（只存在于提示的track）   |
|      |      |      |      | nmhd |      |      | 空media头（其他的track）             |
|      |      |      |      | dinf |      | *    | 数据信息容器                         |
|      |      |      |      |      | dref | *    | 数据参考容器，track中media的参考信息 |
|      |      |      |      | stb1 |      | * | 采样表容器，容器做时间与数据所在位置的描述 |
|      |      |      |      |      | stsd | * | 采样描述（codec类型与初始化信息） |
|      |      |      |      |      | stts | * | (decoding)采样时间 |
|      |      |      |      |      | ctts |      | (composition)采样时间 |
|      |      |      |      |      | stsc | * | chunk采样，数据片段信息 |
|      |      |      |      |      | stsz |      | 采样大小 |
|      |      |      |      |      | stz2 |      | 采样大小详细描述 |
|      |      |      |      |      | stco | * | Chunk偏移信息，数据偏移信息 |
|      |      |      |      |      | co64 |      | 64为Chunk偏移信息 |
|      |      |      |      |      | stss |      | 同步采样表 |
|      |      |      |      |      | stsh |      | 采样同步表 |
|      |      |      |      |      | padb |      | 采样padding |
|      |      |      |      |      | stdp |      | 采样退化优先描述 |
|      |      |      |      |      | sdtp |      | 独立于可支配采样描述 |
|      |      |      |      |      | sbgp |      | 采样组 |
|      |      |      |      |      | sgpd |      | 采样组描述 |
|      |      |      |      |      | subs |      | 子采样信息 |
|      | mvex |      |      |      |      |      | 视频扩展容器 |
|      |      | mehd |      |      |      |      | 视频扩展容器头 |
|      |      | trex |      |      |      | * | track扩展信息 |
|      | impc |      |      |      |      |      | IPMP控制容器 |
| moof |      |      |      |      |      |      | 视频分片 |
|      | mfhd |      |      |      |      | * | 视频分片头 |
|      | traf |      |      |      |      |      | track分片 |
|      |      | tfhd |      |      |      | * | track分片头 |
|      |      | trun |      |      |      |      | track分片run信息 |
|      |      | sdtp |      |      |      |      | 独立和可支配的采样 |
|      |      | sdgp |      |      |      |      | 采样组 |
|      |      | subs |      |      |      |      | 子采样信息 |
| mfra |      |      |      |      |      |      | 视频分片访问控制信息 |
|      | tfra |      |      |      |      |      | track分片访问控制信息 |
|      | mfro |      |      |      |      | * | 拼分片访问控制偏移量 |
| mdat |      |      |      |      |      |      | media数据容器 |
| free |      |      |      |      |      |      | 空闲区域 |
| skip |      |      |      |      |      |      | 空闲区域 |
|      | udta |      |      |      |      |      | 用户数据 |
|      |      | cprt |      |      |      |      | copyright信息 |
| meta |      |      |      |      |      |      | 元数据 |
|      | hdlr |      |      |      |      | * | 定义元数据的句柄 |
|      | dinf |      |      |      |      |      | 数据信息容器 |
|      |      | dref |      |      |      |      | 元数据的源参考信息 |
|      | ipmc |      |      |      |      |      | IPMP控制容器 |
|      | iloc |      |      |      |      |      | 所在位置信息容器 |
|      | ipro |      |      |      |      |      | 样本保护容器 |
|      |      | sinf |      |      |      |      | 计划信息保护容器 |
|      |      |      | frma |      |      |      | 原格式容器 |
|      |      |      | imif |      |      |      | ipmp信息容器 |
|      |      |      | schm |      |      |      | 计划类型容器                               |
|      |      |      | schi |      |      |      | 计划信息容器 |
|      | iinf |      |      |      |      |      | 容器所在项目信息 |
|      | xml |      |      |      |      |      | XML容器 |
|      | bxml |      |      |      |      |      | binary XML容器 |
|      | pitm |      |      |      |      |      | 主要参考容器 |
|      | fiin |      |      |      |      |      | 文件发送信息 |
|      |      | paen |      |      |      |      | partition人口 |
|      |      |      | fpar |      |      |      | 文件片段容器 |
|      |      |      | fecr |      |      |      | FEC reservoir |
|      |      | segr |      |      |      |      | 文件发送session组信息 |
|      |      | gitn |      |      |      |      | 组id转名称信息 |
|      |      | tsel |      |      |      |      | track选择信息 |
| meco |      |      |      |      |      |      | 追加的metadata信息 |
|      | mere |      |      |      |      |      | metabox关系 |

解析MP4多媒体文件需要的一些关键信息:

- 1.moov容器

> moov容器定义了一个MP4文件中的数据信息，类型是moov,是一个容器Atom，其至少必须包含以下三种Atom中的一种:
>
> >- mvhd标签，Movie Header Atom,存放未压缩过的影片信息的头部容器
> >- cmov标签，Compressed Movie Atom,压缩过得电影信息容器，此容器不常用
> >- rmra标签，Reference Movie Atom,参考电影信息容器，此容器不常用

moov类型

| 字段 | 长度/字节 | 描述                          |
| ---- | --------- | ----------------------------- |
| 尺寸 | 4         | 这个movie header atom的字节数 |
| 类型 | 4         | moov                          |

- 2.解析mvhd子容器

  mvhd参数

  | 字段               | 长度/字节 | 描述                                                  |
  | ------------------ | --------- | ----------------------------------------------------- |
  | 尺寸               | 4         | movie header atom的字节数                             |
  | 类型               | 4         | mvhd                                                  |
  | 版本               | 1         | movie header atom的版本                               |
  | 标志               | 3         | 扩展的movie header标志，这里为0                       |
  | 生成时间           | 4         | Movie atom的起始时间。基准时间是1904-1-1 0:00 AM      |
  | 修订时间           | 4         | Movie atom的修订时间。基准时间是1904-1-1 0:00 AM      |
  | Time scale         | 4         | 时间计算单位，就像是系统时间单位换位成60秒一样        |
  | Duration           | 4         | 通过这个值可以得到影片的播放长度时间值                |
  | 播放速度           | 4         | 播放此movie的速度。1.0为正常播放速度(16.16的浮点表示) |
| 播放音量           | 2         | 播放此movie的音量。1.0为最大音量(8.8的浮点表示)       |
| 保留               | 10        | 这里为0                                               |
| 矩阵结构           | 36        | 该矩阵定义了此movie中两个坐标空间的映射关系           |
| 预览时间           | 4         | 开始预览此movie的时间                                 |
| 预览duration       | 4         | 以movie的time scale为单位，预览的duration             |
| Poster time        | 4         | Poster的时间值                                        |
| Selection time     | 4         | 当前选择时间的开始时间值                              |
| Selection duration | 4         | 当前选择时间的计算后的时间值                          |
| 当前时间           | 4         | 当前时间                                              |
| 下一个track ID     | 4         | 下一个待添加track的ID值。0不是一个有效的ID值          |

- 3. 解析trak子容器

     trak容器中定义了媒体文件中的一个track的信息，一个媒体文件中可以包含多个trak，每个trak都是独立的，具有自己的时间和空间占用的信息，每个trak容器都有与它关联的media容器描述信息。trak容器的主要使用目的具体如下:

     - 包含媒体数据的引用和描述(media track)
     - 包含modifier track信息
     - 流媒体协议的打包信息（hint track）,hint track可以引用或者复制对应的媒体采样数据

     hint track和modifier track必须保证完整性，同时要与至少一个media track一起存在。一个trak容器中要求必须要有一个Track Header Atom(tkhd)，一个Media Atom（mdia）,其他的Atom都是可选的，例:atom选项

     - Track剪辑容器：Track Clipping Atom(clip)
     - Track画板容器：Track Matte Atom(matt)
     - Edit容器：Edit Atom(edts)
     - Track参考容器：Track Reference Atom(tref)
     - Track配置加载容器：Track Load Settings Atom(load)
     - Track输出映射容器：Track Input Map Atom(imap)
     - 用户数据容器：User Data Atom(udta)

     Track 数据通用参数表

     | 字段 | 长度/字节 | 描述                     |
     | ---- | --------- | ------------------------ |
     | 尺寸 | 4         | 这个Atom的大小           |
     | 类型 | 4         | tkhd, mdia, clip, matt等 |

- 4. 解析tkhd容器

     tkhd参数

     | 字段            | 长度/字节 | 描述                                                         |
     | --------------- | --------- | ------------------------------------------------------------ |
     | 尺寸            | 4         | 这个Atom的字节数                                             |
     | 类型            | 4         | tkhd                                                         |
     | 版本            | 1         | 这个Atom的版本                                               |
     | 标志            | 3         | 有效的标志分别如下: 0x0001:track生效; 0x0002:track被用在Movie中; 0x0004:track被用在Movie预览中; 0x0008:track被用在Movie的Poster中； |
     | 生成时间        | 4         | Movie Atom的起始时间。基准时间是1904-1-1 0:00 AM             |
     | 修订时间        | 4         | Movie Atom的修订时间。基准时间是1904-1-1 0:00 AM             |
     | Track ID        | 4         | 唯一标志该track的一个非零值                                  |
     | 保留            | 4         | 这里为0                                                      |
     | Layer           | 2         | 视频层，默认为0，值小的再上层                                |
     | Alternate group | 2         | track分组信息，默认为0，表示该track未与其他track有群组关系   |
     | 音量            | 2         | 播放此track的音量。1.0为正常音量                             |
     | 保留            | 2         | 这里为0                                                      |
     | 矩阵结构        | 36        | 该矩阵定义了此track中2个坐标空间的映射关系                   |
     | 宽度            | 4         | 如果该track是video track,那么此值为图像的宽度(16.16浮点表示) |
     | 高度            | 4         | 如果该track是video track,那么此值为图像的高度(16.16浮点表示) |

- 5. 解析mdia容器

     Media Atom的类型是mdia,其必须包含如下容器:

     - 一个媒体头: Media Header Atom(mdhd)
     - 一个句柄参考: Handler Reference(hdlr)
     - 一个媒体信息: Media Information(minf)和用户数据 User Data(udta)
     
     mdia容器参数
     
     | 字段 | 长度/字节 | 描述           |
     | ---- | --------- | -------------- |
     | 尺寸 | 4         | 这个Atom的大小 |
     | 类型 | 4         | mdia           |

- 6. 解析mdhd容器

  mdhd容器被包含在各个track中，描述Media的Header，其包含的信息如下表:

  | 字段       | 长度/字节 | 描述                                             |
  | ---------- | --------- | ------------------------------------------------ |
  | 尺寸       | 4         | 这个Atom的字节数                                 |
  | 类型       | 4         | mdhd                                             |
  | 版本       | 1         | 这个Atom的版本                                   |
  | 标志       | 3         | 这里为0                                          |
  | 生成时间   | 4         | Movie atom的起始时间。基准时间是1904-1-1 0:00 AM |
  | 修订时间   | 4         | Movie atom的修订时间。基准时间是1904-1-1 0:00 AM |
  | Time scale | 4         | 时间计算单位                                     |
  | Duration   | 4         | 这个媒体Track的duration时长                      |
  | 语言       | 2         | 媒体的语言码                                     |
  | 质量       | 2         | 媒体的回放质量                                   |
  

注意:音频时长可以根据Duration/TimeScale的方式来计算

- 7. 解析hdlr容器

  hdlr容器中描述了媒体流的播放过程，该容器中包含的内容如下:

  | 字段           | 长度/字节 | 描述                                                         |
  | -------------- | --------- | ------------------------------------------------------------ |
  | 尺寸           | 4         | 这个Atom的字节数                                             |
  | 类型           | 4         | hdlr                                                         |
  | 版本           | 1         | 这个Atom的版本                                               |
  | 标志           | 3         | 这里为0                                                      |
  | Handle的类型   | 4         | handler的类型。当前只有2种类型:mhlr: media handlers; dhlr: data handlers; |
  | Handle的子类型 | 4         | media handler or data handler的类型。如果component type是mhlr,那么这个字段定义的就是数据的类型，例如:'vide'是video数据，'soun'是sound数据；如果component type是dhlr，那么这个字段定义的就是数据引用的类型，例如'alis'是文件的别名 |
  | 保留           | 12        | 保留字段，默认为0                                            |
  | Component name | 可变      | 这个component的名字,也就是生成此media的media handler。该字段的长度可以为0 |
  
- 8. 解析minf容器

     minf容器中包含了很多重要的子容器，例如音视频采样等信息相关的容器，minf容器中的信息将作为音视频数据的映射存在，其内容信息具体如下:

     - 视频信息头: Video Media Information Header(vmhd子容器)
     - 音频信息头: Sound Media Information Header(smhd子容器)
     - 数据信息: Data Information(dinf子容器)
     - 采样表: Sample Table(stbl子容器)

- 9. 解析vmhd容器

     | 字段     | 长度/字节 | 描述                           |
     | -------- | --------- | ------------------------------ |
     | 尺寸     | 4         | 这个Atom的字节数               |
     | 类型     | 4         | vmhd                           |
     | 版本     | 1         | 这个Atom的版本                 |
     | 标志     | 3         | 固定为0x000001                 |
     | 图形模式 | 2         | 传输模式，传输模式指定的布尔值 |
     | Opcolor  | 6         | 颜色值，RGB颜色值              |

- 10. 解析smhd容器

      | 字段 | 长度/字节 | 描述                                                         |
      | ---- | --------- | ------------------------------------------------------------ |
      | 尺寸 | 4         | 这个Atom的字节数                                             |
      | 类型 | 4         | smhd                                                         |
      | 版本 | 1         | 这个Atom的版本                                               |
      | 标志 | 3         | 固定为0                                                      |
      | 均衡 | 2         | 音频的均衡是用来控制计算机的2个扬声器的声音混合效果，一般是0 |
      | 保留 | 2         | 保留字段，默认为0                                            |

- 11. 解析dinf容器

      dinf容器是一个用于描述数据信息的容器，其定义的是音视频数据的信息，这是一个容器，它饱汉子容器dref。

      | 字段     | 长度/字节 | 描述                                                   |
      | -------- | --------- | ------------------------------------------------------ |
      | 尺寸     | 4         | 这个Atom的字节数                                       |
      | 类型     | 4         | dref                                                   |
      | 版本     | 1         | 这个Atom的版本                                         |
      | 标志     | 3         | 固定为0                                                |
      | 条目数目 | 4         | data references的数目                                  |
      | 数据参考 |           | 每个data reference都像容器的格式一样，包含以下数据成员 |
      | 尺寸     | 4         | 这个Atom的字节数                                       |
      | 类型     | 4         | url/alis/rsrc                                          |
      | 版本     | 1         | 这个                                                   |
      | 标志     | 3         | 目前只有一个标志:0x0001                                |
      | 数据     | 可变      | data reference信息                                     |

- 12. 解析stbl容器

  stbl容器又称为采样参数列表的容器(Sample Table Atom)，该容器包含转化媒体时间到实际的sample的信息，也说明了解释sample的信息，例如，视频数据是否需要解压缩，解压缩算法是什么等信息。其所包含的子容器具体如下：

  - 采样描述容器: Sample Description Atom (stsd)
  - 采样时间容器: Time To Sample Atom (stts)
  - 采样同步容器: Sync Sample Atom(stss)
  - Chunk采样容器: Sample To Chunk Atom(stsc)
  - 采样大小容器: Sample Size Atom (stsz)
  - Chunk偏移容器: Chunk Offset Atom (stco)
  - Shadow同步容器: Shadow Sync Atom (stsh)

- 13. 解析edts容器

      edts容器定义了创建Movie媒体文件中一个track的一部分媒体，所有的edts数据流都在一个表里，包括每一部分的时间偏移量和长度，如果没有该表，那么这个track就会立即开始播放，一个空的edts数据用来定位到track的起始时间偏移位置，如表所示:

      | 字段 | 长度/字节 | 描述             |
      | ---- | --------- | ---------------- |
      | 尺寸 | 4         | 这个Atom的字节数 |
      | 类型 | 4         | edts             |

### MP4分析工具

1. Elecard StreamEye
2. mp4box
3. mp4info

### MP4在FFmpeg中的Demuxer

查看MP4文件的Demuxer信息：

```sh
ffmpeg -h demuxer=mp4
```

ffmpeg解封装MP4常用参数

| 参数                      | 类型 | 说明                                                         |
| ------------------------- | ---- | ------------------------------------------------------------ |
| use_absolute_path         | 布尔 | 可以通过绝对路径加载外部的track, 可能会有安全因素的影响，默认不开启 |
| seek_streams_individually | 布尔 | 根据单独流进行seek,默认开启                                  |
| ignore_editlist           | 布尔 | 忽略EditList Atom信息，默认不开启                            |
| ignore_chapters           | 布尔 | 忽略Chapers信息，默认不开启                                  |
| enable_drefs              | 布尔 | 外部track支持，默认不开启                                    |

### MP4在FFmpeg中的Muxer

FFmpeg封装MP4常用参数

| 参数                  | 值                | 说明                                                   |
| --------------------- | ----------------- | ------------------------------------------------------ |
| movflags              | -                 | MP4 Muxer标记                                          |
| movflags              | rtphint           | 增加RTP的hint track                                    |
| movflags              | empty_moov        | 初始化空的moov box                                     |
| movflags              | frag_keyframe     | 在视频关键帧处切片                                     |
| movflags              | separate_moof     | 每一个Track写独立的moof/mdat box                       |
| movflags              | frag_custom       | 每一个caller请求时Flush一个片段                        |
| movflags              | isml              | 创建实时流媒体（创建一个直播流发布点）                 |
| movflags              | faststart         | 将moov box移动到文件的头部                             |
| movflags              | omit_tfhd_offset  | 忽略tfhd容器中的基础数据偏移                           |
| movflags              | disable_chpl      | 关闭Nero Chapter容器                                   |
| movflags              | default_base_moof | 在tfhd容器中设置default-base-is-moof标记               |
| movflags              | dash              | 兼容DASH格式的mp4分片                                  |
| movflags              | frag_discont      | 分片不连续式设置discontinuous信号                      |
| movflags              | delay_moov        | 延迟写入moov信息，直到第一个分片出来，或者第一片被刷掉 |
| movflags              | global_sidx       | 在文件的开头设置公共的sidx索引                         |
| movflags              | write_colr        | 写入colr容器                                           |
| movflags              | write_gama        | 写被弃用的gama容器                                     |
| moov_size             | 正整数            | 设置moov容器大小的最大值                               |
| rtpflags              |                   | 设置rtp传输相关的标记                                  |
| rtpflags              | latm              | 使用MP4A-LATM方式传输AAC音频                           |
| rtpflags              | rfc2190           | 使用RFC2190传输H.264 H.263                             |
| rtpflags              | skip_rtcp         | 忽略使用RTCP                                           |
| rtpflags              | h264_mode0        | 使用RTP传输mode0的H264                                 |
| rtpflags              | send_bye          | 当传输结束时发送RTCP的BYE包                            |
| skip_iods             | 布尔型            | 不写入iods容器                                         |
| iods_audio_profile    | 0~255             | 设置iods的音频profile容器                              |
| iods_video_profile    | 0~255             | 设置iods的视频profile容器                              |
| frag_duration         | 正整数            | 切片最大的duration                                     |
| min_frag_duration     | 正整数            | 切片最小的duration                                     |
| frag_size             | 正整数            | 切片最大的大小                                         |
| ism_lookahead         | 正整数            | 预读取ISM文件的数量                                    |
| video_track_timescale | 正整数            | 设置所有视频的时间计算方式                             |
| brand                 | 字符串            | 写major brand                                          |
| use_editlist          | 布尔型            | 使用edit list                                          |
| fragment_index        | 正整数            | 下一个分片编号                                         |
| mov_gamma             | 0~10              | Gama容器的gama值                                       |
| frag_interleave       | 正整数            | 交错分片样本                                           |
| encryption_scheme     | 字符串            | 配置加密的方案                                         |
| encryption_key        | 二进制            | 秘钥                                                   |
| encryption_kid        | 二进制            | 秘钥标识符                                             |

1. faststart参数使用案例

- 通过参数faststart将moov容器移动至mdat的前面:

  ```sh
  ./ffmpeg -i input.flv -c copy -f mp4 output.mp4
  ```

- 将moov移动到mdat前面:

  ```sh
  ./ffmpeg -i input.flv -c copy -f mp4 -movflags faststart output.mp4
  ```

2. dash参数使用案例

- 使用mp4info查看容器的格式信息:

  ```sh
  ./ffmpeg -i input.flv -c copy -f mp4 -movflags dash output.mp4
  ```

3. isml参数使用案例

- 发布ISML直播流，将ISMV推流至IIS服务器:

  ```sh
  ./ffmpeg -re -i input.mp4 -c copy -movflags isml+frag_keyframe -f ismv Stream
  ```

## 视频文件转FLV

### FLV格式标准介绍

FLV文件格式分为两部分：一部分为FLV文件头，另一部分为FLV文件内容

1. FLV文件头

   | 字段                            | 占用位数 | 说明                          |
   | ------------------------------- | -------- | ----------------------------- |
   | 签名字段(Signature)             | 8        | 字符"F"(0x46)                 |
   | 签名字段(Signature)             | 8        | 字符"L"(0x4C)                 |
   | 签名字段(Signature)             | 8        | 字符"V"(0x56)                 |
   | 版本(Version)                   | 8        | 文件版本（例如0x01为FLV版本） |
   | 保留标记类型(TypeFlagsReserved) | 5        | 固定为0                       |
   | 音频标记类型(TypeFlagsAudio)    | 1        | 1为显示音频标签               |
   | 保留标记类型(TypeFlagsReserved) | 1        | 固定为0                       |
   | 视频标记类型(TypeFlagsVideo)    | 1        | 1为显示视频标签               |
   | 数据偏移(DataOffset)            | 32       | 这个头的字节                  |

2. FLV文件内容格式解析

   | 字段                           | 类型大小                     | 说明                                                         |
   | ------------------------------ | ---------------------------- | ------------------------------------------------------------ |
   | 上一个TAG的大小(PreTagSize0)   | 4字节(32位)                  | 一直是0                                                      |
   | TAG1                           | FLVTAG(FLVTAG是一个类型)     | 第一个TAG                                                    |
   | 上一个TAG的大小(PreTagSize1)   | 4字节(32位)                  | 上一个TAG字节的大小，包括TAG的Header+Body,TAG的Header大小为11字节，所以这个字段大小为11字节+TAG的Body的大小 |
   | TAG2                           | 上一个TAG的大小(PreTagSize0) | 第二个TAG                                                    |
   | ...                            | ...                          | ...                                                          |
   | 上一个TAG的大小(PreTagSizeN-1) | 4字节(32位)                  | -                                                            |

3. FLVTAG格式解析

   | 字段                          | 类型大小                   | 说明                                                         |
   | ----------------------------- | -------------------------- | ------------------------------------------------------------ |
   | 保留(Reserved)                | 2位                        | 为FMS保留，应该是0                                           |
   | 滤镜(Filter)                  | 1位                        | 主要用来做文件内容加密处理: <br>0: 不预处理; <br>1: 预处理;  |
   | TAG类型(TagType)              | 5位                        | 8(0x08): 音频TAG; <br>9(0x09): 视频TAG; <br>18(0x12): 脚本数据(Script Data, 例如Metadata) |
   | 数据的大小(DataSize)          | 24位                       | TAG的DATA部分的大小                                          |
   | 时间戳(Timestamp)             | 24位                       | 以毫秒为单位的展示时间0x000000                               |
   | 扩展时间戳(TimestampExtended) | 8位                        | 针对时间戳增加的补充时间戳                                   |
   | 流ID(StreamID)                | 24位                       | 一直是0                                                      |
   | TAG的Data(Data)               | 音频数据/视频数据/脚本数据 | 音视频媒体数据，包含startcode                                |

4. VideoTag数据解析

   | 字段                         | 数据类型                                 | 说明                                                         |
   | ---------------------------- | ---------------------------------------- | ------------------------------------------------------------ |
   | 帧类型(FrameType)            | 4位                                      | 视频帧的类型，下面的值为主要定义:<br>1. 为关键帧(H.264使用，可以seek的帧); <br>2. 为P或B帧(H.264使用，不可以seek的帧); <br>3. 仅应用于H.263; <br>4. 生成关键帧（服务器端使用）; <br>5. 视频信息/命令帧; |
   | 编码标识(CodecID)            | 4位                                      | Codec类型定义，下面是对应的编码值与对应的编码: <br>2. Sorenson H.263(用的少); <br>3. Screen Video(用的少); <br>4. On2 VP6(偶尔用); <br>5. 带Alpha通道的On2 VP6(偶尔用); <br>6. Screen Video 2(用得少); <br>7. H.264(使用非常频繁); |
   | H.264的包类型(AVCPacketType) | 当Codec为H.264编码时则占用这个8位(1字节) | 当H.264编码封装在FLV中时，需要三类H.264的数据: <br>0. H.264的Sequence Header; <br>1. NALU(H.264做字节流时需要用的); <br>2. H.264的Sequence的end |
   | CTS(CompositionTime)         | 当Codec为H.264编码时占用这个24位(3字节)  | 当编码使用B帧时，DTS和PTS不相等，CTS用于表示PTS和DTS之间的差值 |
   | 视频数据                     | 视频数据                                 | 压缩过的视频的数据                                           |

5. AudioTag数据格式解析

   | 字段                      | 数据类型                              | 说明                                                         |
   | ------------------------- | ------------------------------------- | ------------------------------------------------------------ |
   | 声音格式(SoundFormat)     | 4位                                   | 不同的值代表着不同的格式，具体如下: <br>0: 限行PCM，大小端取决于平台；<br>1：ADPCM音频格式；<br>2：MP3；<br>3：线性PCM，小端；<br>4：Nellymoser 16kHz Mono; <br>5: Nellymoser 8kHz Mono;<br> 6: Nellymoser; <br>7: G.711 A-law; <br>8: G.711 mu-law;<br> 9: 保留; <br>10: AAC; <br>11: Speex; <br>14: MP3 8kHz; <br>15: 设备支持的声音; 格式7，8，14，15均为保留；使用频率非常高的为AAC，MP3，Speex |
   | 音频采样率(SoundRate)     | 2位                                   | 下面各值代表不同的采样率，具体如下: <br>0: 5.5kHz; <br>1: 11kHz; <br>2: 22kHz; <br>3: 44kHz; <br>有些音频为48kHz的AAC也可以被包含进来，不过也是采用44kHz的方式存储，因为音频采样率在标准中只用2位来表示不同的采样率，所以一般为4种 |
   | 采样大小(SoundSize)       | 1位                                   | 下面的值分别表示不同的采样大小，具体如下: <br>0: 8位采样; <br>1: 16位采样; |
   | 音频类型(SoundType)       | 1位                                   | 0: Mono sound; <br>1: Stereo sound;                          |
   | 音视包类型(AACPacketType) | 当音频为AAC时占用这个字节，8位(1字节) | 0: AAC Sequence Header; <br>1: AAC raw数据                   |
   | 音频数据                  | 音频数据                              | 具体编码的音频数据                                           |

6. ScriptData格式解析

   | 字段                  | 数据类型    | 说明                                                         |
   | --------------------- | ----------- | ------------------------------------------------------------ |
   | 类型(Type)            | 8位(一字节) | 不同的值代表着AMF格式的不同类型，具体如下：<br>0: Number; <br>1: Boolean; <br>2: String; <br>3: Object; <br>5: Null; <br>6: Undefined;<br>7: Reference; <br>8: ECMA Array;<br>9: Object end marker; <br>10: Strict Array; <br>11: Date; <br>12: Long String; |
   | 数据(ScriptDataValue) | -           | 按照Type的类型进行对应的AMF解析                              |

### FFmpeg转FLV参数

| 参数     | 类型                  | 说明                                          |
| -------- | --------------------- | --------------------------------------------- |
| flvflags | flag                  | 设置生成FLV时使用的flag                       |
| flvflags | aac_seq_header_detect | 添加AAC音频的Sequence Header                  |
| flvflags | no_sequence_end       | 生成FLV结束时不写入Sequence End               |
| flvflags | no_metadata           | 生成FLV时不写入metadata                       |
| flvflags | no_duration_filesize  | 用于直播时不在metadata中写入duration与filezie |
| flvflags | add_keyframe_index    | 生成FLV时自动写入关键帧索引信息到metadata头   |

### FFmpeg文件转FLV举例

FLV封装中可以支持的视频编码主要包含如下内容:

- Sorenson H.263
- Screen Video
- On2 VP6
- 带Alpha通道的On2 VP6
- Screen Video 2
- H.264(AVC)

而FLV封装中支持的音频主要包含如下内容:

- 限行PCM，大小端取决于平台
- ADPCM音频格式
- MP3
- 线性PCM，小端
- Nellymoser 16kHz Mono
- Nellymoser 8kHz Mono
- Nellymoser
- G.711 A-law
- G.711 mu-law
- 保留
- AAC
- Spex
- MP3 8kHz

将音频从AC3转换为AAC或者MP3这类FLV标准支持的音频:

```sh
./ffmpeg -i input_ac3.mp4 -vcodec copy -acode aac -f flv output.flv
```

### FFmpeg生成带关键索引的FLV

将FLV文件中的关键帧建立一个索引，并将索引写入Metadata头中:

```sh
ffmpeg -i input.mp4 -c copy -f flv -flvflags add_keyframe_index output.flv
```

### FLV文件格式分析工具

- flvparse
- FlvAnalyzer

## 视频文件转M3U8

### M3U8格式标准介绍

- EXTM3U

  > m3u8文件必须包含的标签，并且必须在文件的第一行，所有的M3U8文件中必须包含这个标准

- EXT-X-VERSION

  > M3U8文件的版本，常见的是3，其实版本已经发展了很多了

- EXT-XTARGETDURATION

  > 最大的那个分片的浮点数四舍五入后的整数值

- EXT-X-MEDIA-SEQUENCE

  > M3U8直播时的直播切片序列，当播放打开M3U8时，以这个标签的值为参考，播放对饮的序列号的切片
  >
  > 分片必须是动态改变的，序列不能相同，并且序列必须是增序的

- EXTINF

  > EXTINF为M3U8列表中每一个分片的duration

- EXT-ENDLIST

  > 表明该M3U8文件不会再产生更多的切片，可以理解为该M3U8已停止更新，并且播放分片到这个标签后结束。

- EXT-X-STREAM-INF

  > EXT-X-STREAM-INF标签出现在M3U8中时，主要是出现在多级M3U8文件中时；该标签后需要跟一些属性：
  >
  > - BANDWIDTH: BANDWIDTH的值为最高码率值,当播放EXT-X-STREAM-INF下对应的M3U8时占用的最大码率，这个参数是EXT-X-STREAM-INF标签中比需要包含的属性
  > - AVERANGE-BANDWIDTH: AVERAGE-BANDWIDTH的值为平均码率值，当播放EXT-X-STREAM-INF下对应的M3U8时占用的平均码率，这个参数是一个可选参数。
  > - CODECS: CODECS的值用于声明EXT-X-STREAM-INF下面对应M3U8里面的音频编码，视频编码的信息，这个属性应该出现在EXT-X-STREAM-INF标签里，但是并不是所有的M3U8中都可以看到，仅供参考。
  > - RESOLUTION: M3U8中视频的宽高信息描述，这个属性是一个可选属性。
  > - FRAME-RATE: 子M3U8中的视频帧率，这个属性已然是一个可选属性。

### FFmpeg转HLS参数

| 参数                 | 类型         | 说明                                                         |
| -------------------- | ------------ | ------------------------------------------------------------ |
| start_number         | 整数         | 设置M3U8列表中的第一片的序列数                               |
| hls_time             | 浮点数       | 设置每一片时长                                               |
| hls_list_size        | 整数         | 设置M3U8中分片的个数                                         |
| hls_wrap             | 整数         | 设置切片索引回滚的边界值                                     |
| hls_allow_cache      | 整数         | 设置M3U8中EXT-X-ALLOW-CACHE的标签                            |
| hls_base_url         | 字符串       | 设置M3U8中每一片的前置路径                                   |
| hls_segment_filename | 字符串       | 设置切片名模板                                               |
| hls_key_info_file    | 字符串       | 设置M3U8加密的key文件路径                                    |
| hls_subtitle_path    | 字符串       | 设置M3U8字幕路径                                             |
| hls_flags            | 标签（整数） | 设置M3U8文件列表的操作，具体如下: <br>single_file: 生成一个媒体文件索引与字节范围;<br> delete_segments: 删除M3U8文件中不包含的过期的TS切片文件;<br> round_durations: 生成的M3U8切片信息的duration为整数; <br>discont_start: 生成M3U8的时候在列表前边加上discontinuity标签; <br>omit_endlist: 在M3U8末尾不追加endlist标签 |
| use_localtime        | 布尔         | 设置M3U8文件序号为本地时间戳                                 |
| use_localtime_mkdir  | 布尔         | 根据本地时间戳生成目录                                       |
| hls_playlist_type    | 整数         | 设置M3U8列表为事件或者点播列表                               |
| method               | 字符串       | 设置HTTP属性                                                 |

### FFmpeg转HLS举例

从文件转换HLS直播:

```sh
./ffmpeg -re -i input.mp4 -c copy -f hls -bsf:v h264_mp4toannexb output.m3u8
```

1. start_number参数

   start_number参数用于设置M3U8列表中的第一片的序列数;

   例:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f hls -bsf:v h264_mp4toannexb -start_number 300 output.m3u8
   ```

2. hls_time参数

   hls_time参数用预设值M3U8列表中切片的duration;

   例:控制转码切片长度为10秒钟左右一片，该切片规则采用的方式是从关键帧处开始切片，所以时间并不是很均匀，如果先转码再进行切片，则会比较规律:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f hls -bsf:v h264_mp4toannexb -hls_time 10 output.m3u8
   ```

3. hls_list_size参数

   hls_list_size参数用于设置M3U8列表中TS切片的个数，通过hls_list_size可以控制M3U8列表中TS分片的个数;

   例:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f hls -bsf:v h264_mp4toannexb -hls_list_size 3 output.m3u8
   ```

4. hls_wrap参数

   hls_wrap参数用于为M3U8列表中TS设置刷新回滚参数，当TS分片序号等于hls_wrap参数设置的数值时回滚；

   例:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f hls -bsf:v h264_mp4toannexb -hls_wrap 3 output.m3u8
   ```

   ***注意:FFmpeg中的这个hls_wrap配置参数对CDN缓存节点的支持并不友好，并且会引起很多不兼容相关的问题，在新版本的FFmpeg中该参数将被弃用***

5. hls_base_url参数

   hls_base_url参数用于为M3U8列表中的文件路径设置前置基本路径参数，因为在FFmpeg中生成M3U8时写入的TS切片路径默认为与M3U8生成的路径相同，但是实际上TS所在存储的路径既可以为本地绝对路径，也可以为当前相对路径，还可以为网络路径，因此使用hls_base_url参数可以达到该效果;

   例:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f hls -hls_base_url http://192.168.0.1/live/ -bsf:v h264_mp4toannexb output.m3u8
   ```

6. hls_segment_filename参数

   hls_segment_filename参数用于为M3U8列表设置切片文件名的规则模板参数，如果不设置hls_segment_filename参数，那么生成的TS切片文件名模板将与M3U8的文件名模板相同；

   例:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f hls -hls_segment_filename test_output-%d.ts -bsf:v h264_mp4toannexb output.m3u8
   ```

7. hls_flags参数

   hls_flags参数包含了一些子参数，子参数包含了正常文件索引，删除过期切片，整数显示duration,列表开始插入discontinuity标签，M3U8结束不追加endlist标签

   - delete_segments子参数

     > 使用delete_segments参数用于删除已经不在M3U8列表中的旧文件，这里需要注意的是，FFmpeg删除切片时会将hls_list_size大小的2倍作为删除的依据；
     >
     > 例:
     >
     > ```sh
     > ./ffmpeg -re -i input.mp4 -c copy -f hls -hls_flags delete_segments -hls_list_size 4 -bsf:v h264_mp4toannexb output.m3u8
     > ```

   - found_durations子参数

     > 使用round_durations子参数实现切片信息的duration为整型；
     >
     > 例:
     >
     > ```sh
     > ./ffmpeg -re -i input.mp4 -c copy -f hls -hls_flags round_durations -bsf:vh264_mp4toannexb output.m3u8
     > ```

   - discont_start子参数

     > discont_start子参数在生成M3U8的时候在切片信息的前边插入discontinuity标签；
     >
     > 例:
     >
     > ```sh
     > ./ffmpeg -re -i input.mp4 -c copy -f hls -hls_flags discont_start -bsf:v h264_mp4toannexb output.m3u8
     > ```

   - omit_endlist子参数

     > omit_endlist子参数在生成M3U8结束的时候若不在文件末尾则不追加endlist标签，因为在常规的生成M3U8文件结束时，FFmpeg会默认写入endlist标签，使用这个参数可以控制在M3U8结束时不写入endlist标签；
     >
     > 例:
     >
     > ```sh
     > ./ffmpeg -re -i input.mp4 -c copy -f hls -hls_flags omit_endlist -bsf:v h264_mp4toannexb output.m3u8
     > ```

   - split_by_time子参数

     > split_by_time子参数生成M3U8时根据hls_time参数设定的数值作为秒数参考对TS进行切片的，并不一定要遇到关键帧；
     >
     > 例:
     >
     > ```sh
     > ./ffmpeg -re -i input.ts -c copy -f hls -hls_time 2 -hls_flags split_by_time output.m3u8
     > ```
     >
     > ***注意：split_by_time参数必须与hls_time配合使用，并且使用split_by_time参数时有可能会影响首画面体验，例如花屏或者首画面显示慢的问题，因为视频的第一帧不一定是关键帧***

8. use_localtime参数

   使用use_localtime参数可以以本地系统时间为切片文件名；

   例:

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f hls -use_localtime 1 -bsf:v h264_mp4toannexb output.m3u8
   ```

9. method参数

   method参数用于设置HLS将M3U8及TS文件上传至HTTP服务器；

   例:

   ```sh
   ./ffmpeg -i input.mp4 -c copy -f hls -hls_time 3 -hls_list_size 0 -method PUT -t 30 http://127.0.0.1/test/output_test.m3u8
   ```

## 视频文件切片

### FFmpeg切片segment参数

| 参数                            | 类型   | 说明                                                       |
| ------------------------------- | ------ | ---------------------------------------------------------- |
| reference_stream                | 字符串 | 切片参考用的stream                                         |
| segment_format                  | 字符串 | 切片文件格式                                               |
| segment_format_options          | 字符串 | 切片格式的私有操作参数                                     |
| segment_list                    | 字符串 | 切片列表主文件名                                           |
| segment_list_flags              | -      | (标签)m3u8切片的存在形式; liv; cache                       |
| segment_list_size               | 整数   | 列表文件长度                                               |
| segment_list_type               | -      | 列表类型; flat; csv; ext; ffconcat; m3u8; hls;             |
| segment_atclocktime             | 布尔   | 时钟频率生效参数，启动定时切片间隔用                       |
| segment_clocktime_offset        | 时间值 | 切片时钟偏移                                               |
| segment_clocktime_wrap_duration | 时间值 | 切片时钟回滚duration                                       |
| segment_time                    | 字符串 | 切片的duration                                             |
| segment_time_delta              | 时间值 | 用于设置切片的时间点                                       |
| segment_times                   | 字符串 | 设置切片的时间点                                           |
| segment_frames                  | 字符串 | 设置切片的帧位置                                           |
| segment_wrap                    | 整数   | 列表回滚阀值                                               |
| segment_list_entry_prefix       | 字符串 | 写文件列表时写入每个切片路径的前置路径                     |
| segment_start_number            | 整数   | 列表中切片的起始基数                                       |
| strftime                        | 布尔   | 设置切片名为生成切片的时间点                               |
| break_non_keyframes             | 布尔   | 忽略关键帧按照时间切片                                     |
| individual_header_trailer       | 布尔   | 默认在每个切片中都写入文件头和文件结束容器                 |
| write_header_trailer            | 布尔   | 只在第一个文件写入文件头以及在最后一个文件写入文件结束容器 |
| reset_timestamps                | 布尔   | 每个切片都重新初始化时间戳                                 |
| initial_offset                  | 时间值 | 设置初始化时间戳偏移                                       |

### FFmpeg切片segment举例

1. segment_format指定切片文件的格式

   > 将一个MP4文件切割为MP4切片，切出来的切片文件的时间戳与上一个MP4的结束时间戳是连续的;
   >
   > 例:
   >
   > ```sh
   > ./ffmpeg -re -i input.mp4 -c copy -f segment -segment_format mp4 test_output-%d.mp4
   > ```
   >
   > 查看第一片分片MP4的最后的时间戳;
   >
   > 例
   >
   > ```sh
   > ffprobe -v quiet -show_packets -select_streams v test_output-0.mp4 2> x|grep pts_time | tail -n 3
   > ```
   >
   > 查看第二分片MP4的最开始的时间戳
   >
   > 例
   >
   > ```sh
   > ffprobe -v quiet -show_packets -select_streams v test_output-1.mp4 2> x|grep pts_time | head -n 3
   > ```

2. segment_list与segment_list_type指定切片索引列表

   > - 生成ffconcat格式索引文件
   >
   >   ```sh
   >   ./ffmpeg -re -i input.mp4 -c copy -f segment -segment_format mp4 -segment_list_type ffconcat -segment_list output.1st test_output-%d.mp4
   >   ```
   >
   > - 生成FLAT格式索引文件
   >
   >   ```sh
   >   ./ffmpeg -re -i inputmp4 -c copy -f segment -segment_format mp4 -segment_list_type flat -segment_list filelist.txt test_output-%d.mp4
   >   ```
   >
   > - 生成CSV格式索引文件
   >
   >   ```sh
   >   ./ffmpeg -re -i inputmp4 -c copy -f segment -segment_format mp4 -segment_list_type csv -segment_list filelist.csv test_output-%d.mp4
   >   ```
   >
   > - 生成M3U8格式索引文件
   >
   >   ```sh
   >   ./ffmpeg -re -i input.mp4 -c copy -f segment -segment_format mp4 -segment_list_type m3u8 -segment_list output.m3u8 test_output-%d.mp4
   >   ```

3. reset_timestamps使切片时间戳归0

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f segment -segment_format mp4 -reset_timestamps 1 test_output-%d.mp4
   ```

4. segment_times按照时间点剪切

   ```sh
   ./ffmpeg -re -i input.mp4 -c copy -f segment -segment_format mp4 -segment_times 3,9,12 test_output-%d.mp4
   ```

### FFmpeg使用ss与t参数进行切片

1. 使用ss指定剪切开头部分

   ```sh
   ./ffmpeg -ss 10 -i input.mp4 -c copy output.ts
   ```

2. 使用t指定视频总长度

   ```sh
   ./ffmpeg -i input.mp4 -c copy -t 10 -copyts output.mp4
   ```

3. 使用output_ts_offset指定输出start_time

   ```sh
   ./ffmpeg -i input.mp4 -c copy -t 10 -output_ts_offset 120 output.mp4
   ```

## 音视频文件音视频流抽取

### FFmpeg抽取音视频文件中的AAC音频流

```sh
./ffmpeg -i input.mp4 -vn -acodec copy output.aac
```

### FFmpeg抽取音视频文件中的H.264视频流

```sh
./ffmpeg -i input.mp4 -vcodec copy -an output.h264
```

### FFmpeg抽取音视频文件中的H.265数据

```sh
./ffmpeg -i input.mp4 -vcodec copy -an -bsf hevc_mp4toannexb -f hevc output.hevc
```

## 系统资源使用情况

```sh
./ffmpeg -re -i input.mp4 -c copy -f mpegts output.ts
```

