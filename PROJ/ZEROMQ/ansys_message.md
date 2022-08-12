# ZMQ源码分析 - Message

[TOC]



## msg_t

```c++
// zmq消息
class msg_t
{
    
}
```

### 分类

zmq将消息分为以下两类：

- `cmsg（constant message，常量消息）`
- `delimiter（分隔符消息）`
- `vsm（very small，短消息）` 
- `lmsg（long message，长消息）`
- `zclmsg（zero copy long message, 零拷贝长消息）`
- `join（加入TODO消息）`
- `leave（离开TODO消息）`

### 消息处理

zmq对于不同的消息类型有不同的处理方式：

- 短消息：zmq处理vsm消息时，将内容直接存储在消息的结构体内，复制等操作采用直接赋值的方式。
- 长消息： zmq处理lmsg时，在lmsg初始化时，先在外部开辟一块内存；当销毁该消息时，需要判定当前消息没有被引用或复制时，才可以销毁；复制该消息时，只需要将指针指向该内存，并将引用计数+1，从而实现零拷贝。

### 创建

init -> init_size -> init_external_storage -> init_data

```c++
// 初始化消息长度
int zmq::msg_t::init_size (size_t size_)
{
    if (size_ <= max_vsm_size) { // 小消息
        _u.vsm.metadata = NULL;
        _u.vsm.type = type_vsm;
        _u.vsm.flags = 0;
        _u.vsm.size = static_cast<unsigned char> (size_);
        _u.vsm.group.sgroup.group[0] = '\0';
        _u.vsm.group.type = group_type_short;
        _u.vsm.routing_id = 0;
    } else { // 长消息
        _u.lmsg.metadata = NULL;
        _u.lmsg.type = type_lmsg;
        _u.lmsg.flags = 0;
        _u.lmsg.group.sgroup.group[0] = '\0';
        _u.lmsg.group.type = group_type_short;
        _u.lmsg.routing_id = 0;
        _u.lmsg.content = NULL;
        if (sizeof (content_t) + size_ > size_)
            _u.lmsg.content =
              static_cast<content_t *> (malloc (sizeof (content_t) + size_)); // 开辟新内存
        if (unlikely (!_u.lmsg.content)) {
            errno = ENOMEM;
            return -1;
        }

        _u.lmsg.content->data = _u.lmsg.content + 1;
        _u.lmsg.content->size = size_;
        _u.lmsg.content->ffn = NULL;
        _u.lmsg.content->hint = NULL;
        new (&_u.lmsg.content->refcnt) zmq::atomic_counter_t ();
    }
    return 0;
}

// 初始化消息内容
int zmq::msg_t::init_data (void *data_,
                           size_t size_,
                           msg_free_fn *ffn_,
                           void *hint_)
{
    zmq_assert (data_ != NULL || size_ == 0);

    if (ffn_ == NULL) { // 销毁函数为空，该消息为常量消息
        _u.cmsg.metadata = NULL;
        _u.cmsg.type = type_cmsg;
        _u.cmsg.flags = 0;
        _u.cmsg.data = data_;
        _u.cmsg.size = size_;
        _u.cmsg.group.sgroup.group[0] = '\0';
        _u.cmsg.group.type = group_type_short;
        _u.cmsg.routing_id = 0;
    } else {
        _u.lmsg.metadata = NULL;
        _u.lmsg.type = type_lmsg;
        _u.lmsg.flags = 0;
        _u.lmsg.group.sgroup.group[0] = '\0';
        _u.lmsg.group.type = group_type_short;
        _u.lmsg.routing_id = 0;
        _u.lmsg.content =
          static_cast<content_t *> (malloc (sizeof (content_t)));
        if (!_u.lmsg.content) {
            errno = ENOMEM;
            return -1;
        }

        _u.lmsg.content->data = data_;
        _u.lmsg.content->size = size_;
        _u.lmsg.content->ffn = ffn_;
        _u.lmsg.content->hint = hint_;
        new (&_u.lmsg.content->refcnt) zmq::atomic_counter_t (); // placement new用法
    }
    return 0;
}
```



### 销毁

```c++
// 销毁消息
int zmq::msg_t::close ()
{
    if (unlikely (!check ())) {
        errno = EFAULT;
        return -1;
    }

    if (_u.base.type == type_lmsg) {
        if (!(_u.lmsg.flags & msg_t::shared) // 非共享或引用次数为0的消息，直接释放
            || !_u.lmsg.content->refcnt.sub (1)) {
            _u.lmsg.content->refcnt.~atomic_counter_t ();     // 析构计数器
            if (_u.lmsg.content->ffn)
                _u.lmsg.content->ffn (_u.lmsg.content->data,
                                      _u.lmsg.content->hint); // 调用销毁函数
            free (_u.lmsg.content); // 释放content
        }
    }

    if (is_zcmsg ()) {
        zmq_assert (_u.zclmsg.content->ffn);
        if (!(_u.zclmsg.flags & msg_t::shared)
            || !_u.zclmsg.content->refcnt.sub (1)) {
            _u.zclmsg.content->refcnt.~atomic_counter_t ();
            _u.zclmsg.content->ffn (_u.zclmsg.content->data,
                                    _u.zclmsg.content->hint);
        }
    }

    if (_u.base.metadata != NULL) {
        if (_u.base.metadata->drop_ref ()) {
            LIBZMQ_DELETE (_u.base.metadata);
        }
        _u.base.metadata = NULL;
    }

    if (_u.base.group.type == group_type_long) {
        if (!_u.base.group.lgroup.content->refcnt.sub (1)) {
            _u.base.group.lgroup.content->refcnt.~atomic_counter_t ();

            free (_u.base.group.lgroup.content);
        }
    }

    _u.base.type = 0; // 类型置0，消息失效

    return 0;
}
```



## 帧

网络上的帧数据在网络上是以很小的称为帧（Frame）的单位传输的，每一帧都是一个`msg_t`结构。

### 多帧

特性：

- 在发送多帧消息时，只有当最后一帧提交发送了，整个消息才会发送；
- 多帧消息是整体传输的，不会只收到一部分；
- 多帧消息的每一帧都是一个`zmq_msg`结构；
- 无论是否检查套接字的ZMQ_RCVMORE选项，都会收到所有的消息；
- 发送时，ZMQ会将开始的消息帧缓存在内存中，直到收到最后一帧才会发送；
- 无法在发送了一部分消息后取消发送，只能关闭该套接字。



## 参考

- [ZeroMQ源码阅读阶段性总结](https://www.icode9.com/content-1-120408.html#mailbox_tmutex_t_75)
- [Linux架构师源码分析---ZeroMQ源码](https://zhuanlan.zhihu.com/p/357533714)
