# 第14章 TCP超时与重传

[TOC]



## 简单的超时与重传举例

二进制指数退避（binary exponential backoff）：每次重传间隔时间加倍；

### 经典方法

最初的TCP规范[RFC0793]采用如下公式计算得到`平滑的RTT估计值（俗称SRTT）`：

$SRTT \leftarrow a(SRTT) + (1 - a)RTT_s$

- $a$ 平滑因子（常量，推荐0.8~0.9）

这种估算方法称为`指数加权移动平均(Exponentially Weighted Moving Average, EWMA)`或`低通过滤器(low-pass filter)`；

考虑到SRTT估计器得到的估计值会随RTT而变化，[RFC0793]推荐根据如下公式设置RTO：

$RTO=min(ubound, max(lbound, (SRTT)\beta))$

- $\beta$ 时延离散因子（推荐1.3~2.0）
- $ubound$ RTO的上边界（可设定建议值，1min）
- $lbound$ RTO的下边界（可设定建议值，1sec）

### 标准方法

经典方法的缺陷：

- 按照经典方法设置计时器无法适应RTT的大规模变动，当实际的RTT远大于估计值时，会导致不必要的重传；
- 增大的RTT样本值表明网络已出现过载，此时不必要的重传会进一步加重网络负担；

标准方法在采用经典方法的同时，考虑RTT变化值以及均值来设置RTO，比仅使用均值的常数倍来计算RTO更能适应RTT变化幅度较大的情况；

对每个RTT测量值$M$(即前面的$RTT_s$)采用以下方法估算：

$srtt \leftarrow (1-g)(srtt)+(g)M$

$rttvar \leftarrow (1-h)(rttvar) + (h)(|M-srtt|)$

$RTO = srtt + 4(rttvar)$

或另一种对计算机实现来说操作较为方便的估算方法：

$Err = M - srtt$

$srtt \leftarrow srtt + g(Err)$

$rttvar \leftarrow rttvar + h(|Err| - rttvar)$

