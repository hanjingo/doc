English | [中文版](bittorrent_zh.md)

# BitTorrent Protocol

[TOC]


**Abstract**    BitTorrent (BT) [<sup>[1]</sup>](#refer-1) is a protocol for file sharing in peer-to-peer networks. It shares files in a p2p (peer-to-peer) manner: the more people downloading the same file, the faster the download speed. The BitTorrent protocol is a P2P file transfer communication protocol built on top of TCP/IP, operating at the application layer of the TCP/IP stack. According to the BitTorrent protocol, the publisher generates and provides a .torrent file (the torrent file or simply "torrent") for the file to be shared. The torrent file is essentially a text file containing two parts: tracker information and file information.

Keywords    **torrent** **p2p**

---

[TOC]


## Roles

Tracker: A server that collects information about downloaders and provides this information to other downloaders, enabling them to connect to each other and transfer data.

Seeder: In a download task, when a downloader has downloaded all files completely, the downloader becomes a seeder. The publisher's original file is the original seed.

Seeding: The act of providing the entire content of a download task by the publisher; or, after a downloader finishes downloading, continuing to provide the file for others to download.


## Implementation

TODO


---

## References

### Literature
[1] [Wikipedia BitTorrent Protocol](https://en.wikipedia.org/wiki/BitTorrent_(protocol))

### External Links

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
 * [BitTorrent Protocol](https://github.com/xipfs/IPFS-Internals/blob/master/ebook/03.5.md)
