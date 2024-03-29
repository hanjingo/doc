# bancor算法


<!-- vim-markdown-toc GFM -->

* [摘要](#摘要)
* [知识点](#知识点)
* [token买入](#token买入)
    - [token卖出](#token卖出)
    - [特点](#特点)

<!-- vim-markdown-toc -->



## 摘要

bancor算法(bancor_protocol)



## 知识点
* Supply

  $$token供应量$$

* Price

  $$token价格 = Balance(储备金余额) \div (  Supply(token供应量) \times CW(储备金固定比率) )$$

* TotalValue

  $$token总市值 = Price(token价格) \times Supply(token供应量)$$

* Balance

  储备金余额

* CW
  
  $$储备金固定比率 = Balance(储备金余额) \div TotalValue(token总市值)$$



## token买入

$$token = Token供应量 \times (  (1 + EOS支付金额 \div 储备金余额)^{储备金固定比率} - 1 ) $$
例子:  

```md
Token供应量:1000
储备金余额:250
储备金固定比率:0.5
使用750个EOS可以购买到:1000 * ( (1 + 750 / 250)^0.5 -1 ) = 1000个token
```
### token卖出
$$EOS= 储备金余额 \times (1 - (1 - 出售的Token \div Token供应量) ^ {\frac{1}{div 储备金固定比率} )}$$
例子:  

```
Token供应量:1000+1000 = 2000
储备金余额:250 + 750 = 1000
储备金固定比率:0.5
卖出1000个token可以得到:1000 * (1 - (1 - 1000 / 2000) ^ (1 / 0.5) ) = 750
```
### 特点
储备金固定比率=100%时,EOS和token锚定；比率不变  
储备金固定比率=50%时,EOS和token的比率随着供应量的变化而变化  
