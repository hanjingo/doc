# 第八章 生成随机数
# 摘要
随机数的生成
# 详情
## 总结
* 随机数引擎可以生成随机比特序列。有如下3个定义了随机数引擎的类模板:
> + mersenne_twister_engine：能够生成最高质量的随机序列，但它是这2个类模板中最慢的.
> + linear_congruential_engine：最简单且最快，但序列的质量比其他两个引擎差.
> + subtract_with_carry_engine：可以比linear_congruential_engine生成更好质量的序列，但他的状态会占用太多的内存，而且还有一点慢
* 自定义引擎模板的随机数生成器实现了一个可以生成一个非负整数的均匀随机分布的特定算法。除了default_random_engine是由定义实现的之外，还有9个定义了不同生成器的类:
> + mt19937和mt19937_64是从mersenne_twister_engine模板得到的.
> + minstd_rand0,minstd_rand,knuth_b是从linear_congruential_engine模板得到的.
> + ranlux24_base,ranlux48_base,ranlux24,ranlux48是从subtract_with_carry_engine模板得到的.
* 使用随机数生成器生成的序列的分布函数对象会用给定的概率分布生成整数或浮点值的序列，有21个定义了分布的模板，但只有一个是类模板
> + 均匀分布：uniform_int_distribution, uniform_real_distribution和generate_canonical函数模板.
> + 正态分布：normal_distribution, lognormal_distribution, chi_squared_distribution, cauchy_distribution, fisher_f_distribution和student_t_distribution.
> + 抽样分布：discrete_distribution, piecewise_constant_distribution, piecewise_linear_distribution.
> + 伯努利分布：bernoulli_distribution, geometric_distribution, binomial_distribution, negative_binomial_distribution.
> + 泊松分布：poisson_distribution, gamma_distribution, weibull_distribution, extreme_value_distribution和exponential_distribution.
  
一些类型的随机数生成器会用随机数引擎适配器来修改从引擎得到的序列。引擎适配器有3个类模板：
* 用来定义knuth_b的shuffle_order_engine.
* 用来定义ranlux24和ranlux48的discard_block_engine.
* 未在STL中应用的independent_bits_engine.
随机数生成器需要一个或多个种子值来初始化他的状态。random_device类定义了可以返回非负整数的均匀分布序列的函数对象，非法整数的均匀分布的大多数实现都是非确定性的。为了能够确定是否得到高质量的序列，不能直接使用随机数引擎，应该总是使用随机数生成器。