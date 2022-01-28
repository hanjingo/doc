# BitTorrent协议

**摘要**    BitTorrent(简称BT)[<sup>[1]</sup>](#refer-1)是用在对等网络中文件分享的协议。它以p2p(peer-to-peer)的形式来分享文件，下载同一文件的人越多，下载该文件的速度越快。BitTorrent协议是架构于TCP/IP协议之上的一个P2P文件传输通信协议，处于TCP/IP结构的应用层。根据BitTorrent协议，文件发布者会根据要发布的文件生成提供一个.torrent文件，即种子文件，也简称为“种子”。种子文件本质上是文本文件，包含Tracker信息和文件信息两部分。

关键词    **种子** **p2p**

---

[TOC]



## 角色

Tracker：收集下载者信息的服务器，并将此信息提供给其他下载者，使下载者们相互连接起来，传输数据。

种子：指一个下载任务中所有文件都被某下载者完整的下载，此时下载者成为一个种子。发布者本身发布的文件就是原始种子。

做种：发布者提供下载任务的全部内容的行为；下载者下载完成后继续提供给他人下载的行为。



## 实现

TODO



---

## 参考

### 文献
<div id="refer-1">[1]: [维基百科BitTorrent协议](https://zh.wikipedia.org/wiki/BitTorrent_(%E5%8D%8F%E8%AE%AE)</div>

### 外部链接

 * [Torrent.Express](https://torrent.express/)
 * [Confluence](https://github.com/anacrolix/confluence)
 * [Trickl](https://github.com/arranlomas/Trickl)
 * [Elementum(up to version 0.0.71)](http://elementum.surge.sh/) 
 * [goTorrent](https://github.com/deranjer/goTorrent)
 * [Go Peerflix](https://github.com/Sioro-Neoku/go-peerflix)
 * [Simple Torrent](https://github.com/boypt/simple-torrent) 
 * [Android Torrent Client](https://gitlab.com/axet/android-torrent-client)
 * [libtorrent](https://gitlab.com/axet/libtorrent)
 * [Remote-Torrent](https://github.com/BruceWangNo1/remote-torrent)
 * [ANT-Downloader](https://github.com/anatasluo/ant)
 * [Go-PeersToHTTP](https://github.com/WinPooh32/peerstohttp)
 * [CortexFoundation/torrentfs](https://github.com/CortexFoundation/torrentfs)
 * [BitTorrent协议](https://github.com/xipfs/IPFS-Internals/blob/master/ebook/03.5.md)

