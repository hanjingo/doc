# 第七章 FFmpeg采集设备

## FFmpeg中Linux设备操作

### Linux下查看设备列表

例：查看系统当前支持的设备

```sh
./ffmpeg -hide_banner -devices
```

### Linux采集设备fbdev参数说明

例：查询fbdev支持的参数

```sh
./ffmpeg -h demuxer=fbdev
```

fbdev设备参数

| 参数      | 类型 | 说明                                 |
| --------- | ---- | ------------------------------------ |
| framerate | 帧率 | 采集时视频图像的刷新频率，默认值为25 |

### Liux采集设备fbdev使用举例

例：获取终端中的图像，而不是图形界面的图像

```sh
./ffmpeg -framerate 30 -f fbdev -i /dev/fb0 output.mp4
```

### Linux采集设备v412参数说明

Linux下，常见的视频设备还有video4linux，现在是video4linux2，设备一般缩写为v4l2，尤其是用于摄像头设备

```sh
./ffmpeg -h demuxer=v412
```

v412参数说明

| 参数           | 类型     | 说明                                 |
| -------------- | -------- | ------------------------------------ |
| standard       | 字符串   | 设置TV标准，仅用于模拟器分析帧时使用 |
| channel        | 整数     | 设置TV通道，仅用于模拟器分析帧时使用 |
| video_size     | 图像大小 | 设置采集视频帧大小                   |
| pixel_format   | 字符串   | 设置采集视频的分辨率                 |
| input_format   | 字符串   | 设置采集视频的分辨率                 |
| framerate      | 字符串   | 设置采集视频帧率                     |
| list_formats   | 整数     | 列举输入视频信号的信息               |
| list_standards | 整数     | 列举标准信息（与standard配合使用）   |
| timestamps     | 整数     | 设置时间戳类型                       |
| ts             | 整数     | 设置模拟器分析帧时使用的时间戳       |
| use_libv4l2    | 布尔     | 使用第三方库libv412选项              |

### Linux采集设备v4l2使用举例

例：电脑的v4l2摄像头所支持的色彩格式及分辨率

```sh
./ffmpeg -hide_banner -f v4l2 -list_formats all -i /dev/video0
```

例：把摄像头采集为视频文件

```sh
./ffmpeg -hide_banner -s 1920x1080 -i /dev/video0 output.avi
```

### Linux采集设备x11grab参数说明

使用FFmpeg采集Linux下面的图形部分桌面图像时，通常采用x11grab设备采集图像

x11grab参数说明

| 参数          | 类型   | 说明                                                 |
| ------------- | ------ | ---------------------------------------------------- |
| draw_mouse    | 整数   | 支持绘制鼠标光标                                     |
| follow_mouse  | 整数   | 跟踪鼠标轨迹数据                                     |
| framerate     | 字符串 | 输入采集的视频帧率                                   |
| show_region   | 整数   | 获得输入桌面的指定区域                               |
| region_border | 整数   | 当show_region为1时，设置输入指定区域的边框的粗细程度 |
| video_size    | 字符串 | 输入采集视频的分辨率                                 |

### Linux采集设备x11grab使用举例

FFmpeg通过x11grab录制屏幕时，输入设备的设备名规则如下：

```sh
[主机名]:显示编号id.屏幕编号id[+起始x轴, 起始y轴]
```

例：桌面录制，输入帧率25，图像分辨率为1366x768，采集的设备为"0.0"，输出文件为out.mp4

```sh
./ffmpeg -f x11grab -framerate 25 -video_size 1366x768 -i :0.0 out.mp4
```

例：桌面录制指定起始位置，指定x坐标为300，y坐标为200

```sh
./ffmpeg -f x11grab -framerate 25 -video_size 352x288 -i :0.0+300,200 out.mp4
```

**注意：video_size需要按实际大小指定，最好保证次大小不要超过实际采集区域的大小**

例：桌面录制带鼠标记录的视频

```sh
./ffmpeg -f x11grab -video_size 1366x768 -follow_mouse 1 -i :0.0 out.mp4
```

## FFmpeg中OS X设备操作

在FFmpeg中采集OS X系统的输入输出设备，常规方式采用的是OS X的avfoundation设备进行采集，avfoundation参数说明:

| 参数                 | 类型     | 说明                                |
| -------------------- | -------- | ----------------------------------- |
| list_devices         | 布尔     | 列举当前可用设备信息                |
| video_device_index   | 整数     | 视频设备索引编号                    |
| audio_device_index   | 整数     | 音频设备索引编号                    |
| pixel_format         | 色彩格式 | 色彩格式，例如yuv420, nv12, rgb24等 |
| framerate            | 帧率     | 视频帧率，例如25                    |
| video_size           | 分辨率   | 图像分辨率，类似于1280x720          |
| capture_cursor       | 整数     | 获得屏幕上鼠标图像                  |
| capture_mouse_clicks | 整数     | 获得屏幕上鼠标点击的事件            |

### OS X下查看设备列表

例：知道当前系统都支持哪些设备

```sh
./ffmpeg -devices
```

### OS X下设备采集举例

例：枚举avfoundation支持的输入设备

```sh
./ffmpeg -f avfoundation -list_devices true -i ""
```

例：采集内置摄像头

```sh
./ffmpeg -f avfoundation -i " FaceTime HD Camera (Built-in)" out.mp4
```

例：采集OS X桌面

```sh
ffmpeg -f avfoundation -i "Capture screen 0" -r:v 30 out.mp4
```

例：采集OSX桌面，将鼠标一起录制下来

```sh
ffmpeg -f avfoundation -capture_cursor 1 -i "Capture screen 0" -r:v 30 out.mp4
```

例：采集麦克风

```sh
ffmpeg -f avfoundation -i "0:0" out.aac
```

## FFmpeg中Windows设备操作

### FFmpeg使用dshow采集音视频设备

1. 使用dshow枚举设备

   例：使用dshow来枚举当前系统上存在的音视频设备，这些设备主要是摄像头，麦克风

   ```sh
   ./ffmpeg.exe -f dshow -list_devices true -i dummy
   ```

2. 使用dshow展示摄像头

   例：打开设备，并使用ffplay来展示摄像头

   ```sh
   ffplay.exe -f dshow -video_size 1280x720 -i video="Integrated Camera"
   ```

3. 将摄像头数据保存为MP4文件

   ```sh
   ./ffmpeg.exe -f dshow -i video="Integrated Camera" -f dshow -i audio="virtual-audio-capturer" out.mp4
   ```

### FFmpeg使用gdigrab采集窗口

gdigrab主要参数:

| 参数        | 主要作用                                            |
| ----------- | --------------------------------------------------- |
| draw_mouse  | 是否绘制采集鼠标指针                                |
| show_region | 是否绘制采集的边界                                  |
| framerate   | 设置视频帧率，默认为25帧，两个标准值分别为pal, ntsc |
| video_size  | 设置视频分辨率                                      |
| offset_x    | 采集区域偏移x个像素                                 |
| offset_y    | 采集区域偏移y个像素                                 |

1. 使用gdigrab采集整个桌面

   ```sh
   ./ffmpeg.exe -f gdigrab -framerate 6 -i desktop out.mp4
   ```

2. 使用gdigrab采集某个窗口

   ```sh
   ./ffmpeg.exe -f gdigrab -framerate 6 -i title=ffmpeg out.mp4
   ```

3. 使用gdigrab录制带偏移量的视频

   ```sh
   ./ffmpeg.exe -f gdigrab -framerate 6 -offset_x 50 -offset_y 50 -video_size 400x400 -i title=ffmpeg out.mp4
   ```

   