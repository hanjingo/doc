# skynet日志模块
## 摘要
日志操作,结构比较简单,不多赘述

## 详情
- skynet_log.h
- skynet_log.c

### 日志操作
```c++
//打开日志
FILE * skynet_log_open(struct skynet_context * ctx, uint32_t handle);
//关闭日志
void skynet_log_close(struct skynet_context * ctx, FILE *f, uint32_t handle);
//输出日志
void skynet_log_output(FILE *f, uint32_t source, int type, int session, void * buffer, size_t sz);
```

### 一些辅助函数
```c++
//按字节刷入
static void
log_blob(FILE *f, void * buffer, size_t sz) {
    size_t i;
    uint8_t * buf = buffer;
    for (i=0;i!=sz;i++) {
        fprintf(f, "%02x", buf[i]);
    }
}
 
//打印socket信息
static void
log_socket(FILE * f, struct skynet_socket_message * message, size_t sz) {
    fprintf(f, "[socket] %d %d %d ", message->type, message->id, message->ud);
    if (message->buffer == NULL) {
        const char *buffer = (const char *)(message + 1);
        sz -= sizeof(*message);
        const char * eol = memchr(buffer, '\0', sz);//查找结尾符
	if (eol) {
            sz = eol - buffer;//如果有结尾符,只取到结尾符，其他还回去
        }
	fprintf(f, "[%*s]", (int)sz, (const char *)buffer);
    } else {
        sz = message->ud;
        log_blob(f, message->buffer, sz);
    }
    fprintf(f, "\n");
    fflush(f);
}
```