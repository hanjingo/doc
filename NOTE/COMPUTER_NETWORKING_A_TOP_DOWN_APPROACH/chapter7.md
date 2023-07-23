# Chapter7 Multimedia Networking



The most salient characteristic of video is its `high bit rate`. Another important characteristic of video is that it can be compressed, thereby trading off video quality with bit rate。

Streaming stored video has three key distinguishing features：

- `Streaming`.
- `Interactivity`.
- `Continuous playout`.

Streaming video systems can be classified into three categories:

- `UDP streaming`.
- `HTTP streaming`.
- `adaptive HTTP streaming`.

![7_1](res/7_1.png)

Before passing the video chunks to UDP, the server will encapsulate the video chunks within transport packets specially designed for transporting audio and video, using the Real-Time Transport Protocol (RTP) [RFC 3550] or a similar (possibly proprietary) scheme. 

Another distinguishing property of UDP streaming is that in addition to the serverto-client video stream, the client and server also maintain, in parallel, a separate control connection over which the client sends commands regarding session state changes (such as pause, resume, reposition, and so on). The Real-Time Streaming Protocol (RTSP) [RFC 2326], explained in some detail in the companion Web site for this textbook, is a popular open protocol for such a control connection.

In HTTP streaming, the video is simply stored in an HTTP server as an ordinary file with a specific URL. When a user wants to see the video, the client establishes a TCP connection with the server and issues an HTTP GET request for that URL. The server then sends the video file, within an HTTP response message, as quickly as possible, that is, as quickly as TCP congestion control and flow control will allow. On the client side, the bytes are collected in a client application buffer. Once the number of bytes in this buffer exceeds a predetermined threshold, the client application begins playback—specifically, it periodically grabs video frames from  the client application buffer, decompresses the frames, and displays them on the user’s screen.

![7_2](res/7_2.png)

Thus, when the available rate in the network is less than the video rate, playout will alternate between periods of continuous playout and periods of freezing.

![7_3](res/7_3.png)

**Note that when the available rate in the network is more than the video rate, after the initial buffering delay, the user will enjoy continuous playout until the video ends. **

`End-to-end delay` is the accumulation of transmission, processing, and queuing delays in routers; propagation delays in links; and end-system processing delays.

`Jitter` can often be removed by using sequence numbers, timestamps, and a playout delay, as discussed below.

TODO