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
      |          |           |                                                        |
      |          |           |                                                        |
      |          |           |                                                        |