# 第四章 本金利息分离技术



## 4.1 摊还法

### 4.1.1 未结贷款余额的计算

未结贷款余额指在贷款业务中，每次分期还款后，借款人未偿还的债务在当时的价值。计算这个量的常用方法：

- 预期法：用所有未支付的分期付款现值之和表示每个时刻的贷款余额；
- 追溯法：用原始贷款额的累积值扣除所有已付款项的累积值表示每个时刻的贷款余额。

考虑一些特殊还款情况下的未结贷款余额的计算：

1. 每次还贷金额已知的情形

   设贷款利率为$i$，分$n$次还清，每次还款1个货币单位，则对任意的时刻$t(t = 0, 1, 2, ..., n)$，有：
   $$
   B_t^p = a_{\left.{\overline{\,n - t\,}}\!\right|i} \qquad (4.1.1)
   $$
   又因为这时的原始贷款额$L = a_{\left.{\overline{\,n\,}}\!\right|i}$，所以有：
   $$
   B_t^r = a_{\left.{\overline{\,n\,}}\!\right|i}(1 + i)^t - s_{\left.{\overline{\,t\,}}\!\right|i} \qquad (4.1.2)
   $$

2. 贷款金额已知的情形

   设原始贷款金额为$L$，贷款利率为$i$，分$n$次还清。若每次的还款额为$R$，则有：
   $$
   R a_{\left.{\overline{\,n\,}}\!\right|i} = L, 即 R = \frac{L}{a_{\left.{\overline{\,n\,}}\!\right|i}}
   $$
   于是，对任意时刻$t(t = 0, 1, 2, ..., n)$，有：
   $$
   B_t^p = R a_{\left.{\overline{\,n - t\,}}\!\right|i} = \left(\frac{L}{a_{\left.{\overline{\,n\,}}\!\right|i}}\right) = L \frac{a_{\left.{\overline{\,n - t\,}}\!\right|i}}{a_{\left.{\overline{\,n\,}}\!\right|i}} \qquad (4.1.3) \\
   
   B_t^r = L \left[(1 + i)^t - \frac{s_{\left.{\overline{\,t\,}}\!\right|i}}{a_{\left.{\overline{\,n\,}}\!\right|i}} \right] \qquad (4.1.4)
   $$

**结论4.1** 若贷款分$n$次偿还，每次还款1个货币单位，且利率为$i$，则：

- 采用预期法和追溯法计算得到的未结贷款余额是相同的，即：
  $$
  B_t^p = B_t^r,\ t = 0, 1, 2, ..., n
  $$

- 未结贷款余额有如下递推关系：
  $$
  B_t = (1 + i)B_{t - 1} - 1,\ t = 1, 2, ..., n 
  $$

### 4.1.2 摊还表





