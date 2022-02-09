# ipfs的swarm.key

## 启用私有网络

启用私有网络有2步：

1. 清除默认的公有节点
```sh
ipfs bootstrap rm --all
```
2. 设置环境变量`export LIBP2P_FORCE_PNET=1`来强行启用私有网络

    看一下源代码，这个环境变量是如何生效的：

    ```go
    // go-libp2p-core/pnet/env.go
    const EnvKey = "LIBP2P_FORCE_PNET"

    var ForcePrivateNetwork = false

    func init() {
	    ForcePrivateNetwork = os.Getenv(EnvKey) == "1"
    }
    ```

## swarm.key的生成

swarm.key本质就是一个32字节的随机数，用来给不同的swarm(群)做加解密通讯；其生成算法如下：

```go
// github.com/Kubuxu/go-ipfs-swarm-key-gen/main.go
package main

import "crypto/rand"
import "encoding/hex"
import "fmt"
import "log"

func main() {
	key := make([]byte, 32)
	_, err := rand.Read(key)
	if err != nil {
		log.Fatalln("While trying to read random source:", err)
	}

	fmt.Println("/key/swarm/psk/1.0.0/")
	fmt.Println("/base16/")
	fmt.Print(hex.EncodeToString(key))
}
```



## swarm.key的加载

ipfs启动时会去查找`swarm.key`，找到之后，反序列化`swarm.key`得到`psk`，代码如下：

```go
// github.com/ipfs/go-ipfs/core/node/libp2p/pnet.go
func PNet(repo repo.Repo) (opts Libp2pOpts, fp PNetFingerprint, err error) {
	swarmkey, err := repo.SwarmKey()
	if err != nil || swarmkey == nil {
		return opts, nil, err
	}

	psk, err := pnet.DecodeV1PSK(bytes.NewReader(swarmkey))
	if err != nil {
		return opts, nil, fmt.Errorf("failed to configure private network: %s", err)
	}

	opts.Opts = append(opts.Opts, libp2p.PrivateNetwork(psk))

	return opts, pnetFingerprint(psk), nil
}
```

上面解压出psk后，会赋值给`Config`的PSK，代码如下：

```go
// github.com/libp2p/go-libp2p/options.go
func PrivateNetwork(psk pnet.PSK) Option {
	return func(cfg *Config) error {
		if cfg.PSK != nil {
			return fmt.Errorf("cannot specify multiple private network options")
		}

		cfg.PSK = psk
		return nil
	}
}
```

这个PSK在函数`makeSwarm`创建Swarm时用到，如果`LIBP2P_FORCE_PNET`被设置同时swarm.key为空时，会导致创建swarm失败，继而导致daemon启动失败，代码如下：

```go
// github.com/libp2p/go-libp2p/config/config.go
func (cfg *Config) makeSwarm(ctx context.Context) (*swarm.Swarm, error) {
	if cfg.Peerstore == nil {
		return nil, fmt.Errorf("no peerstore specified")
	}

	// Check this early. Prevents us from even *starting* without verifying this.
	if pnet.ForcePrivateNetwork && len(cfg.PSK) == 0 {
		log.Error("tried to create a libp2p node with no Private" +
			" Network Protector but usage of Private Networks" +
			" is forced by the enviroment")
		// Note: This is *also* checked the upgrader itself so it'll be
		// enforced even *if* you don't use the libp2p constructor.
		return nil, pnet.ErrNotInPrivateNetwork
	}

    ... // 余下代码不再赘述
}
```



## swarm.key的生效

在使用swarm之前，会先解码PSK，代码如下：

```go
// github.com/ipfs/go-ipfs/core/node/libp2p/pnet.go
func PNet(repo repo.Repo) (opts Libp2pOpts, fp PNetFingerprint, err error) {
	swarmkey, err := repo.SwarmKey()
	if err != nil || swarmkey == nil {
		return opts, nil, err
	}

	psk, err := pnet.DecodeV1PSK(bytes.NewReader(swarmkey)) // 解码PSK
	if err != nil {
		return opts, nil, fmt.Errorf("failed to configure private network: %s", err)
	}

	opts.Opts = append(opts.Opts, libp2p.PrivateNetwork(psk))

	return opts, pnetFingerprint(psk), nil
}
```

在监听器(listener)监听请求时会通过`upgrader`创建连接，代码如下：

```go
// github.com/libp2p/go-libp2p-transport-upgrader/listener.go
func (l *listener) handleIncoming() {
    // 前面太长略过...
    conn, err := l.upgrader.UpgradeInbound(ctx, l.transport, maconn)
    // 后面略过...
}
```

当PSK不为空时，`upgrader`创建的是`ProtectedConn(私有连接)`，代码如下：

```go
// github.com/libp2p/go-libp2p-transport-upgrader/upgrader.go
func (u *Upgrader) UpgradeInbound(ctx context.Context, t transport.Transport, maconn manet.Conn) (transport.CapableConn, error) {
	return u.upgrade(ctx, t, maconn, "", network.DirInbound)
}

func (u *Upgrader) upgrade(ctx context.Context, t transport.Transport, maconn manet.Conn, p peer.ID, dir network.Direction) (transport.CapableConn, error) {
    var stat network.Stat
	if cs, ok := maconn.(network.ConnStat); ok {
		stat = cs.Stat()
	}

	var conn net.Conn = maconn
	if u.PSK != nil { // 如果psk不为空，创建私密连接
		pconn, err := pnet.NewProtectedConn(u.PSK, conn)
		if err != nil {
			conn.Close()
			return nil, fmt.Errorf("failed to setup private network protector: %s", err)
		}
		conn = pconn
	} else if ipnet.ForcePrivateNetwork { // 如果设置了环境变量LIBP2P_FORCE_PNET，同时PSK为空，报错;
		log.Error("tried to dial with no Private Network Protector but usage" +
			" of Private Networks is forced by the enviroment")
		return nil, ipnet.ErrNotInPrivateNetwork
	}
    // 后面略...
}    
```

创建`pskConn(受保护的连接)`时，赋予PSK的解码值给它，代码如下：

```go
// github.com/libp2p/go-libp2p-pnet/protector.go
func NewProtectedConn(psk ipnet.PSK, conn net.Conn) (net.Conn, error) {
	if len(psk) != 32 {
		return nil, errors.New("expected 32 byte PSK")
	}
	var p [32]byte
	copy(p[:], psk)
	return newPSKConn(&p, conn)
}
```

`pskConn`对`net.Conn`的Read和write函数进行了封装，每次建立连接前，都会交换一个24byte的空包，代码如下：

```go
// github.com/libp2p/go-libp2p-pnet/psk_conn.go
type pskConn struct {
	net.Conn
	psk *[32]byte

	writeS20 cipher.Stream
	readS20  cipher.Stream
}

func (c *pskConn) Read(out []byte) (int, error) {
	if c.readS20 == nil { // readS20默认为空，说明这是第一个数据包(一个24byte的空包)
		nonce := make([]byte, 24)
		_, err := io.ReadFull(c.Conn, nonce)
		if err != nil {
			return 0, errShortNonce
		}
		c.readS20 = salsa20.New(c.psk, nonce)
	}

	n, err := c.Conn.Read(out) // read to in
	if n > 0 {
		c.readS20.XORKeyStream(out[:n], out[:n]) // 解密，异或操作 
	}
	return n, err
}

func (c *pskConn) Write(in []byte) (int, error) {
	if c.writeS20 == nil { // 一开始发一个24byte的空包
		nonce := make([]byte, 24)
		_, err := rand.Read(nonce)
		if err != nil {
			return 0, err
		}
		_, err = c.Conn.Write(nonce)
		if err != nil {
			return 0, err
		}

		c.writeS20 = salsa20.New(c.psk, nonce)
	}
	out := pool.Get(len(in))
	defer pool.Put(out)

	c.writeS20.XORKeyStream(out, in) // 加密，异或操作

	return c.Conn.Write(out) // send
}

```
