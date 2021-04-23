# GOLANG

## io.WriteAt(p []byte, off int64) (n int, err error)

WriteAt 从 p 中将 len(p) 个字节写入到偏移量 off 处的基本数据流中。它返回从 p 中被写入的字节数
n（0 <= n <= len(p)）以及任何遇到的引起写入提前停止的错误。若 WriteAt 返回的 n < len(p)，
它就必须返回一个非nil的错误。若 WriteAt 按查找偏移量写入到目标中，WriteAt 应当既不影响基本查找偏移量
也不被它所影响。若区域没有重叠，WriteAt 的客户端可对相同的目标并行执行 WriteAt 调用

