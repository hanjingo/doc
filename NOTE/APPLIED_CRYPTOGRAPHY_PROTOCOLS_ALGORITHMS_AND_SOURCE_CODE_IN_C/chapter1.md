# 第一章 基础知识
## 摘要
密码学专业术语介绍

## 详情
### 定义:
1. 明文(plaintext)：消息
2. 密文(ciphertext)：被加密后的消息
3. 加密(encryption):用某种方法伪装消息以隐藏他的内容
4. 解密(decryption):把密文转变成明文的过程
5. 无条件保密(unconditionally secure):不论密码分析者有多少密文，都没有足够的信息恢复出明文
6. 蛮力攻击(brute_force attack):只要简单地一个接一个地去尝试每种可能的秘钥，并且检查所的明文是否有意义
7. 隐写术(steganography):将秘密消息隐藏在其他消息中，这样真正存在的秘密被隐藏

### 对称算法(symmetric algo-rithm):
有时又叫做传统密码算法，就是加密秘钥能从解密秘钥中推算出来，反过来也成立；  
对称算法分类:  
* 序列算法(stream algorithm)或序列密码(stream cipher)

  一次只对明文中的单个位（有时对字节）运算的算法；

* 分组算法(block algorithm)或分组密码(biock cipher)

  对明文的一组位进行运算；

### 非对称算法/公开秘钥算法(public-key algorithm)：
用作加密的秘钥不同于用作解密的秘钥，而且解密秘钥不能根据加密秘钥计算出来；加密秘钥叫做公开密钥(public-key, 简称公钥)，解密秘钥叫做私人秘钥(private key, 简称私钥)

### 密码分析:
1. 唯密文攻击(ciphertext-only attack):密码分析者有一些消息的密文，这些消息都用相同加密算法加密。
2. 已知明文攻击(known-plaintext attack):密码分析者不仅可得到一些消息的密文，而且也知道这些消息的明文。
3. 选择明文攻击(chosen-plaintext acctack):分析者不仅可得到一些消息的密文和相应的明文，而且他们也可以选择被加密的明文。
4. 自适应选择明文攻击(adaptive-chosen-plaintext attack):这是选择明文攻击的特殊情况。分析者不仅能选择被加密的明文，而且也能基于以前加密的结果修正这个选择。
5. 选择密文攻击(chosen-ciphertext attack):密码分析者能选择不同的被加密的密文，并可得到对应的解密的明文。
6. 选择秘钥攻击(chosen-key attack):这种攻击并不表示密码分析者能够选择秘钥，它只表示密码分析者具有不同秘钥之间关系的有关知识。
7. 软磨硬泡攻击(rubber-hose cryptanalysis):密码分析者威胁，勒索，或者折磨某人，直到他给出秘钥为止。

### 破译等级:
* 全部破译(total break)
* 全盘推导(global deduction)
* 实例(或局部)推导(instance (or local) deduction)
* 信息推导(information deduction)

### 攻击方法复杂性:
* 数据复杂性(data complexity):用于攻击输入所需要的数据量
* 处理复杂性(processing complexity):完成攻击所需要的时间，也经常称做工作因素(work factor)
* 存储需求(storage requirement):进行攻击所需要的存储量

### 代替密码:
明文中每一个字符被替换成密文中的另一个字符，接收者对密文进行逆替换就可以恢复明文。  
* 简单代替密码(simple substitution cipher)/单字母密码(monoalphabetic cipher):明文的一个字符用相应的一个密字符代替
* 多名码代替密码(homophonic substitution cipher):与简单代替密码系统相似，唯一的不同是单个字符明文可以映射成密文的多个字符之一
* 多字母代替密码(polygram substitution cipher):字符块被组成加密
* 多表代替密码(polyalphabetic substitution cipher):由多个简单的代替密码构成

### 破译方法:
1. 重合码计数法(counting coincidence):用密文异或相对其本身的各种字节的位移，统计那些相等的字节数。
2. 按此长度移动密文，并且与自身进行异或。这样就消除了秘钥，留下明文和移动了秘钥长度的明文的异或。

### 计算机算法:
1. DES(Data Encryption Standard) 数据加密标准:对称算法，加密和解密的密钥是相同的。
2. RSA:公开密钥算法，用作加密和数字签名。
3. DSA(Digital Signature Algorithm) 数字签名算法:用做数字签名标准的一部分，是另一种公开密钥算法，他不能用做加密，只用做数字签名