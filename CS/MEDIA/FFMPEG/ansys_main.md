# FFmpeg源码分析-main函数

[TOC]



## main函数

- `fftools/ffmpeg.h`
- `fftools/ffmpeg.c`
```mermaid
graph LR
A[main]-->B[init_dynload]-->B1[SetDllDirectory]
A[main]-->C[register_exit]
A[main]-->D[setvbuf]
A[main]-->E[av_log_set_flags]
A[main]-->F[parse_loglevel]
subgraph parse_loglevel
	F[parse_loglevel]-->F1[locate_option]
	F[parse_loglevel]-->F2[check_options]
	F[parse_loglevel]-->F3[opt_loglevel]
	F[parse_loglevel]-->F4[init_report]
	F[parse_loglevel]-->F5[dump_argument]
	F[parse_loglevel]-->F6[fflush]
end
A[main]-->G[avdevice_register_all]-->G1[avpriv_register_devices]-->G1.1[av_format_init_next]
A[main]-->H[avformat_network_init]
A[main]-->I[show_banner]
A[main]-->J[ffmpeg_parse_options]
A[main]-->K[exit_program]
```

- init_dynload: 初始化动态链接库加载地址

- resister_exit: 注册程序退出时的回调函数

- setvbuf: win32用到

- av_log_set_flags: 

- parse_loglevel: 

- av_format_init_next: 用链表存储注册的组件(编解码器...)

- avformat_network_init: 初始化网络

- show_banner: 打印ffmpeg的版本信息

- ffmpeg_parse_options: 解析输入选项

- exit_program: 调用前面resister_exit注册的程序退出时的回调函数

  

