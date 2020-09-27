# 第一章 认识ipfs
## 摘要
ipfs:整合已有的BitTorrent，DHT，Git和SFS等技术创造出的一种点对点超媒体协议；  
filecoin:运行在ipfs上的一个激励层；  

## 详情
### 优点:
* 下载速度快
* 优化全球存储
* 更加安全
* 数据的可持续保存

### 对区块链的帮助：
1. 高速分布式存储机制，解决区块链存储效率低，成本高的缺点
2. IPLD组建存储不同链的数据，解决跨链问题

### 相对http的优势：
IPFS协议栈：
* 身份层(Identity)：S/Kademlia算法增加创建新身份的成本，对等节点身份信息生成，验证
* 网络层(Network)：支持任意传输层协议,Overlay网络WebRTC & ICE NET & NAT穿透
* 路由层(Routing)：分布式哈希表(DHT),定位ie对等点和存储对象需要的信息
* 交换层(Exchange)：BitTorrent & BitSwap，保证节点网络稳定，激励交换数据行为
* 对象层(Object)：Merkle-DAG & IPLD，内容可寻址的不可篡改，去冗余的对象链接
* 文件层(File)：类似Git，版本控制的文件系统：blob, list, tree, commit
* 命名层(Naming)：具有SFS（Self-Certified Filesystem)& IPNS NDS TXT解析，Proquint可发音域名绑定