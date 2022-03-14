# FFmpeg源码分析-注册系列函数

[TOC]



## 注册所有组件(包括:复用器/解复用器...) av_register_all

- libavformat/allformats.c
- libavformat/avformat.h

实现:

```c++
// 注册组件到链表(复用器/解复用器...)
static void av_format_init_next(void)
{
    AVOutputFormat *prevout = NULL, *out;
    AVInputFormat *previn = NULL, *in;

    ff_mutex_lock(&avpriv_register_devices_mutex);

    for (int i = 0; (out = (AVOutputFormat*)muxer_list[i]); i++) {
        if (prevout)
            prevout->next = out;
        prevout = out;
    }

    if (outdev_list) {
        for (int i = 0; (out = (AVOutputFormat*)outdev_list[i]); i++) {
            if (prevout)
                prevout->next = out;
            prevout = out;
        }
    }

    for (int i = 0; (in = (AVInputFormat*)demuxer_list[i]); i++) {
        if (previn)
            previn->next = in;
        previn = in;
    }

    if (indev_list) {
        for (int i = 0; (in = (AVInputFormat*)indev_list[i]); i++) {
            if (previn)
                previn->next = in;
            previn = in;
        }
    }

    ff_mutex_unlock(&avpriv_register_devices_mutex);
}
```



## 注册编解码器 avcodec_register_all

- libavcodec/allcodecs.c
- libavcodec/

实现:

```c++
static void av_codec_init_static(void)
{
    for (int i = 0; codec_list[i]; i++) {
        if (codec_list[i]->init_static_data)
            codec_list[i]->init_static_data((AVCodec*)codec_list[i]);
    }
}

const AVCodec *av_codec_iterate(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVCodec *c = codec_list[i];

    ff_thread_once(&av_codec_static_init, av_codec_init_static);

    if (c)
        *opaque = (void*)(i + 1);

    return c;
}

#if FF_API_NEXT
FF_DISABLE_DEPRECATION_WARNINGS
static AVOnce av_codec_next_init = AV_ONCE_INIT;

static void av_codec_init_next(void)
{
    AVCodec *prev = NULL, *p;
    void *i = 0;
    while ((p = (AVCodec*)av_codec_iterate(&i))) {
        if (prev)
            prev->next = p;
        prev = p;
    }
}
```



