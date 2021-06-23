# ipfs的swarm-key

## 启用私有网络

启用私有网络有2种方法：

1. 清除默认的公有节点

```sh
ipfs bootstrap rm --all
```

2. 设置环境变量`export LIBP2P_FORCE_PNET=1`来强行启用私有网络

