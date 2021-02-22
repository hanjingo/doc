# 第九章 FFmpeg接口libavcodec的使用

## FFmpeg新接口
### 使用FFmpeg新接口音频编码流程
```mermaid
graph TD
A[avcodec_register_all]-->B[avcodec_find_encoder]-->C[avcodec_alloc_context3]-->D[avcodec_open2]-->E[av_packet_alloc]-->F[av_frame_alloc]-->G[av_fame_get_buffer]
G[av_fame_get_buffer]-->H1.1[av_frame_free]-->I[av_packet_free]-->J[avcodec_free_context]
G[av_fame_get_buffer]-->H2.1[av_frame_make_writable]-->H2.2[avcodec_send_frame]-->H2.3[avcodec_receive_packet]-->H1.1[av_frame_free]
H2.3[avcodec_receive_packet]-->H2.3[avcodec_receive_packet]
H2.3[avcodec_receive_packet]-->H2.1[av_frame_make_writable]
```



```c++
// 查找和打开编码器
const AVCodec *codec;
AVCodecContext *c = NULL;
AVFrame *frame;
AVPacket pkt;
avcodec_register_all();
codec = avcodec_find_encoder(AV_CODEC_ID_MP2);
if (!codec) {
	fprintf(stderr, "codec not found\n");
	exit(1);
}
c = avcodec_alloc_context3(codec);
if (!c) {
	fprintf(stderr, "could not allocate audio codec context\n");
	exit(1);
}
if (avcodec_open2(c, codec, NULL) < 0) {
	fprintf(stderr, "could not open codec\n");
	exit(1);
}
frame = av_frame_alloc();
if (!frame) {
	fprintf(stderr, "could not allocate audio frame\n");
	exit(1);
}
frame->nb_samples = c->frame_size;
frame->format = c->sample_fmt;
frame->channel_layout = c->channel_layout;
/* allocate the data buffers */
ret = av_frame_get_buffer(frame, 0);
if (ret < 0) {
	fprintf(stderr, "could not allocate audio data buffers\n");
	exit(1);
}

// 填充数据
t = 0;
tincr = 2 * M_PI * 440.0 / c->sample_rate;
for (i = 0; i < 200; i++) {
	/* make sure the frame is writable -- makes a copy if the encoder
	   kept a reference internally */
	ret = av_frame_make_writeable(frame);
	if (ret < 0)
			exit(1);
	samples = (uint16_t*)frame->data[0];
	for (j = 0; j < c->frame_size; j++) {
		samples[2*j] = (int)(sin(t) * 10000);
		for (k = 1; k < c->channels; k++) {
			samples[2*j + k] = samples[2*j];
			t += tincr;
		}
		encode(c, frame, pkt, f);
	}
}

// 音频编码
static void encode(AVCodecContext *ctx, AVFrame *frame, AVPacket *pkt, FILE *output) {
	int ret;
	/* send the frame for encoding */
	ret = avcodec_send_frame(ctx, frame);
	if (ret < 0) {
		fprintf(stderr, "error sending the frame to the encoder\n");
		exit(1);
	}
	/ *read all the available output packets (in general there may be any number of them)* /
	while (ret >= 0) {
		ret = avcodec_receive_packet(ctx, pkt);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) 
			return;
		else if (ret < 0) {
			fprintf(stderr, "error encoding audio frame\n");
			exit(1);
		}
		fwrite(pkt->data, 1, pkt->size, output);
		av_packet_unref(pkt);
	}		
}
```

### FFmpeg新接口音频解码
#### 音频解码API调用流程 
```mermaid
graph TD
A[avcodec_register_all]-->B[av_packet_alloc]-->C[avcodec_find_decoder]
```



```c++
// 查找和打开解码器
const AVCodec *codec;
AVCodecContext *c = NULL;
AVCodecParserContext *parser = NULL;
AVPacket *pkt;
AVFrame *decoded_frame = NULL;
avcodec_register_all();
pkt = av_packet_alloc();
/* find the MPEG audio decoder */
codec = avcodec_find_decoder(AV_CODEC_ID_MP2);
if (!codec) {
	fprintf(stderr, "codec not found\n");
	exit(1);
}
parser = av_parser_init(codec->id);
if (!parser) {
	fprintf(stderr, "parser not found\n");
	exit(1);
}
c = avcodec_alloc_context3(codec);
if (!c) {
	fprintf(stderr, "could not allocate audio codec context\n");
	exit(1);
}
if (avcodec_open2(c, codec, NULL) < 0) {
	fprintf(stderr, "could not open codec\n");
	exit(1);
}

// 音频解码准备
while (data_size > 0) {
	if (!decoded_frame) {
		if (!(decoded_frame = av_frame_alloc())) {
			fprintf(stderr, "could not allocate audio frame\n");
			exit(1);
		}
	}
	ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size, data, data_size, 
					AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
	if (ret < 0) {
		fprintf(stderr, "error while parsing\n");
		exit(1);
	}
	ata += ret;
	ata_size -= ret;
	if (pkt->size)
			decode(c, pkt, decoded_frame, outfile);
	if (data_size < AUDIO_REFILL_THRESH) {
		memmove(inbuf, data, data_size);
		data = inbuf;
		len = fread(data + data_size, 1, AUDIO_INBUF_SIZE - data_size, f);
		if (len > 0)
				data_size += len;
	}
}

// 音频解码函数
static void decode(AVCodecContext *dec_ctx, AVPacket *pkt, AVFrame *frame, FILE *outfile) {
	int i, ch;
	int ret, data_size;
	/* send the packet with the compressed data to the deocder */
	ret = avcodec_send_packet(dec_ctx, pkt);
	if (ret < 0) {
		fprintf(stderr, "error submitting the packet to the decoder\n");
		exit(1);
	}
	/* read all the output frames (in general there may be any number of them) */
	while (ret >= 0) {
		ret = avcodec_receive_frame(dec_ctx, frame);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
			return;
		} else if (ret < 0) {
			fprintf(stderr, "error during decoding\n");
			exit(1);
		}
		data_size = av_get_bytes_per_sample(dec_ctx->sample_fmt);
		if (data_size < 0) {
			/* this should not occur, checking just for paranoia */
			fprintf(stderr, "failed to calculate data size\n");
			exit(1);
		}
		for (i = 0; i < frame->nb_samples; i++)
			for (ch = 0; ch < dec_ctx->channels; ch++)
					fwrite(frame->data[ch] + data_size*i, 1, data_size, outfile);
	}
}
```

### 视频编码API调用流程
todo

### 视频解码API调用流程
todo
