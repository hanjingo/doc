# 第十章 FFmpeg接口libavfilter的使用
libavfilter是FFmpeg中一个很重要的模块，其提供了很多音视频的滤镜，通过合理使用这些滤镜，可以达到事半功倍的效果;

## filtergraph和filter简述
todo

## FFmpeg中预留的滤镜
todo

## avfilter流程图
todo

## 使用滤镜加LOGO操作
```c++
// 注册FFmpeg的滤镜操作接口
int main(int argc, char *argv[])
{
	avfilter_register_all();
	return 0;
}

// 获得滤镜处理的源
AVFilter *buffersrc = avfilter_get_by_name("buffer");
AVFilter *buffersink = avfilter_get_by_name("buffersink");
AVFilterInOut *outputs = avfilter_inout_alloc();
AVFilterInOut *inputs = avfilter_inout_alloc();

// 处理AVfilterGraph
AVFilterGraph *filter_graph;
filter_graph = avfilter_graph_alloc();
if (!outputs || !inputs || !filter_graph) {
	ret = AVERROR(ENOMEM);
}

// 创建AVFilterContext
AVFilterContext *buffersink_ctx;
AVFilterContext *buffersrc_ctx;
snprintf(args, sizeof(args), "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
				dec_ctx->width, dec_ctx->height, dec_ctx->pix_fmt, time_base.num, time_base.den,
				dec_ctx->sample_aspect_ratio.num, dec_ctx->sample_aspect_ratio.den);
ret = avfilter_graph_create_filter(&buffersrc_ctx, buffersrc, "in", args, NULL, filter_graph);
if (ret < 0) {
	av_log(NULL, AV_LOG_ERROR, "cannot create buffer source\n");
}
/* buffer video sink: to terminate the filter chain. */
ret = avfilter_graph_create_filter(&buffersink_ctx, buffersink, "out", NULL, NULL, filter_graph);
if (ret < 0) {
	av_log(NULL, AV_LOG_ERROR, "cannot create buffer sink\n");
}

// 设置其他参数
ret = av_opt_set_int_list(buffersink_ctx, "pix_fmts", AV_PIX_FMT_YUV420P, AV_PIX_FMT_NONE, AV_OPT_SEARCH_CHILDREN);
if (ret < 0) {
	av_log(NULL, AV_LOG_ERROR, "cannot set output pixel format\n");
}

// 建立滤镜解析器
const char * filters_descr = "movie=logo.jpg[logo];[logo]colorkey=white:0.2:0.5[alphawm];[in][alphawn]overlay=20:20[out]";

outputs->name = av_strdup("in");
outputs->filter_ctx = buffersrc_ctx;
outputs->pad_idx = 0;
outputs->next = NULL;

inputs->name = av_strdup("out");
inputs->filter_ctx = buffersink_ctx;
inputs->pad_idx = 0;
inputs->next = NULL;

avfilter_graph_parse_ptr(filter_graph, filters_descr, &inputs, &outputs, NULL);
avfilter_graph_config(filter_graph, NULL);

// 数据解码
if (av_buffersrc_add_frame_flags(buffersrc_ctx, frame, AV_BUFFERSRC_FLAG_KEEP_REF) < 0) {
	av_log(NULL, AV_LOG_ERROR, "error while feeding the filtergrpah\n");
}

// 获取数据
while(1) {
	ret = av_buffersink_get_frame(buffersink_ctx, filt_frame);
	if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
		break;
	if (ret < 0)
		goto end;
	av_image_copy(video_dst_data, video_dst_linesize,
					(const uint8_t **)(frame->data), frame->linesize, AV_PIX_FMT_YUV420P,
					frame->width, frame->height);
	fwrite(video_dst_data[0], 1, video_dst_bufsize, video_dst_file);
	av_frame_unref(filt_frame);
} 
av_frame_unref(frame);
```
