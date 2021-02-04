# ipfs使用总结

## ipfs add命令默认pin
ipfs add 文件时默认pin

ipfs get 文件时不pin

## ipfs gc时无法添加文件
ipfs默认达到最大磁盘容量的90%(可配置)时启动gc; ipfs gc时，无法add文件，整个ipfs文件系统锁死; 尽量不要触发ipfs的gc;

代码如下:

```go
func GC(ctx context.Context, bs bstore.GCBlockstore, dstor dstore.Datastore, pn pin.Pinner, bestEffortRoots []cid.Cid) <-chan Result {
	ctx, cancel := context.WithCancel(ctx)

	unlocker := bs.GCLock() //在这里锁死了 bstore

	bsrv := bserv.New(bs, offline.Exchange(bs))
	ds := dag.NewDAGService(bsrv)

	output := make(chan Result, 128)

	go func() {
		defer cancel()
		defer close(output)
		defer unlocker.Unlock()

		gcs, err := ColoredSet(ctx, pn, ds, bestEffortRoots, output)
		if err != nil {
			select {
			case output <- Result{Error: err}:
			case <-ctx.Done():
			}
			return
		}
		keychan, err := bs.AllKeysChan(ctx)
		if err != nil {
			select {
			case output <- Result{Error: err}:
			case <-ctx.Done():
			}
			return
		}

		errors := false
		var removed uint64

	loop:
		for ctx.Err() == nil { // select may not notice that we're "done".
			select {
			case k, ok := <-keychan:
				if !ok {
					break loop
				}
				if !gcs.Has(k) {
					err := bs.DeleteBlock(k)
					removed++
					if err != nil {
						errors = true
						select {
						case output <- Result{Error: &CannotDeleteBlockError{k, err}}:
						case <-ctx.Done():
							break loop
						}
						// continue as error is non-fatal
						continue loop
					}
					select {
					case output <- Result{KeyRemoved: k}:
					case <-ctx.Done():
						break loop
					}
				}
			case <-ctx.Done():
				break loop
			}
		}
		if errors {
			select {
			case output <- Result{Error: ErrCannotDeleteSomeBlocks}:
			case <-ctx.Done():
				return
			}
		}

		gds, ok := dstor.(dstore.GCDatastore)
		if !ok {
			return
		}

		err = gds.CollectGarbage()
		if err != nil {
			select {
			case output <- Result{Error: err}:
			case <-ctx.Done():
			}
			return
		}
	}()

	return output
}
```

## ipfs pin过程
ipfs pin文件时,会像节点表中的所有节点广播hash信息;

如果其他节点没有拉取当前hash的文件，而本节点又解除了pin，并gc掉了缓存的话，其他节点将无法根据hash拿到文件;

## ipfs 添加文件/文件夹
ipfs 可以添加文件也可以添加文件夹; 

添加文件时用:ipfs add 文件名, 返回一个hash

添加文件夹时用:ipfs add -r 文件夹名, 返回一个文件夹hash和文件夹下的所有文件的所有fhash

示例:
```bash
# 添加文件夹
<15:39:20>[root@192.168.2.10] ~
$ ipfs add -r test
added QmYsrwNj3dZsmJ3BMoSkose94wvKoFGjwWnTLuLyVDL6wf test/hello.txt
added QmVQUH9m81CvNLfyVpk3HDt6xX8RsgKtrJTZbmx4TcFsBR test
 6 B / 6 B [================================================================================================] 100.00%<15:39:35>[root@192.168.2.10] ~

 # 查看文件夹下指定文件名
$ ipfs cat QmVQUH9m81CvNLfyVpk3HDt6xX8RsgKtrJTZbmx4TcFsBR/hello.txt
hango
```

可以利用ipfs添加文件夹的特性来实现文件更新;比如

```bash
# 添加文件夹
<15:39:20>[root@192.168.2.10] ~
$ ipfs add -r test
added QmYsrwNj3dZsmJ3BMoSkose94wvKoFGjwWnTLuLyVDL6wf test/hello.txt
added QmVQUH9m81CvNLfyVpk3HDt6xX8RsgKtrJTZbmx4TcFsBR test
 6 B / 6 B [================================================================================================] 100.00%<15:39:35>[root@192.168.2.10] ~

 # 查看文件夹下指定文件名
$ ipfs cat QmVQUH9m81CvNLfyVpk3HDt6xX8RsgKtrJTZbmx4TcFsBR/hello.txt
hango

# 修改hello.txt并再次添加
$ ipfs add -r test
added QmeueCk6d2e33wQqaKbrrHSG1gHT1LiajoqARmBqHJYznX test/hello.txt
added QmRN9JxBsf3j7bKU5oMwuD1JbpfVP7QbYZY23cVR7STHp2 test
 8 B / 8 B [================================================================================================] 100.00%<15:59:00>[root@192.168.2.10] ~

 # 查看
$ ipfs cat QmRN9JxBsf3j7bKU5oMwuD1JbpfVP7QbYZY23cVR7STHp2/hello.txt
pzkj123
```