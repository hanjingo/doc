# golang常见错误
## waitgroup的坑
先上代码
```go
func main() {
    wg := new(sync.WaitGroup)
    for i := 0; i < 5; i++ {
        go func(wg sync.WaitGroup, i int) {
            wg.Add(1)
            log.Printf("i:%d", i)
            wg.Done()
        }(wg, i)
    }
    wg.Wait()
    log.Println("exit")
}
结果是有时候什么也不输出.
因为 WaitGroup 同步的是 goroutine, 而上面的代码却在 goroutine 中进行 Add(1) 操作.
因此，可能在这些 goroutine 还没来得及 Add(1) 已经执行 Wait 操作了.
可以改成这样:
func main() {
    wg := new(sync.WaitGroup)
    for i := 0; i < 5; i++ {
        wg.Add(1)
        go func(wg sync.WaitGroup, i int) {
            log.Printf("i:%d", i)
            wg.Done()
        }(wg, i)
    }
    wg.Wait()
    log.Println("exit")
}
```