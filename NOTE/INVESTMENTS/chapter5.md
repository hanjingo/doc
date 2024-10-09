# CHAPTER 5 Risk, Return, and the Historical Record



Forecasting interest rates is one of the most notoriously difficult partsw of applied macro-economics. Nonetheless, we do have a good understanding of the fundamental factors that determine the level of interest rates:

1. The supply of funds from savers, primarily households.
2. The demand for funds from businesses to be used to finance investments in plant, equipment, and inventories (real assets or capital formation).
3. The government's net demand for funds as modified by the actions of the Federal Reserve Bank.

`nominal interest rate`: the growth rate of your money.

`real interest rate`: the growth rate of your purchasing power. 

If we call $rn$ the nominal rate, $rr$ the real rate, and $i$ the inflation rate, then we conclude:
$$
rr \approx rn - i
$$
In fact, the exact relationship between the real and nominal interest rate is given by:
$$
1 + rr = \frac{1+rn}{1+i}
$$
, this is because the growth factor of your purchasing power, $1 + rr$, equals the growth factor of your money, $1 + rn$, divided by the growth factor of prices, $1 + i$. The exact relationship can be rearranged to:
$$
rr = \frac{rn - i}{1 + i}
$$
, which shows that the approximation rule $rr \approx rn - i$ overstates the real rate by the factor $1 + i$​.

Irving Fisher (1930) argued that the nominal rate ought to increase one-for-one with expected inflation, $E(i)$. The so-called Fisher equation is:
$$
rn = rr + E(i)
$$
, the equation implies that when real rates are reasonably stable, changes in nominal rates ought to predict changes in inflation rates.

Index-linked tax brackets do not provide relief from the effect of inflation on the taxation of savings, however. Given a tax rate $(t)$ and a nominal interest rate, $rn$, the after-tax interest rate is $rn(1 - t)$. The real after-tax rate is approximately the after-tax nominal rate minus the inflation rate:
$$
rn(1 - t) - i = (rr + i)(1 - t) - i = rr(1 - t) - it
$$
, thus the after-tax real rate falls as inflation rises.

Given the price $P(T)$ of a Treasury bond with \$100 par value and maturity of $T$ years, we calculate the total risk-free return available for a horizon of $T$ years as the percentage increase in the value of the investment:
$$
r_f(T) = \frac{100}{P(T)} - 1
$$
, for $T = 1$​, this equation provides the risk-free for an investment horizon of 1 year.

We typically express all investment returns as an `effective annual rate (EAR)`, defined as the percentage increase in funds invested over a 1-year horizon.

Annualized rates on short-term investments (by convention, $T < 1$​ year) often are reported using simple rather than compound interest. These are called `annual percentage rates` or `APRs`.

Note that for short-term investments of length $T$, there are $n = 1 / T$ compounding periods in a year. Therefore, the relationship among the compounding period, the $EAR$, and the $APR$ is:
$$
1 + EAR = [1 + r_f(T)]^n = [1 + r_f(T)]^{1/T} = [1 + T \times APR]^{1/T}
$$
, equivalently:
$$
APR = \frac{(1 + EAR)^T - 1}{T}
$$
As $T$ approaches zero, we effectively approach `continuous compounding (CC)`, and the relation of $EAR$ to the annual percentage rate, denoted by $r_{cc}$ for the continuously compounded case, is given by the exponential function:
$$
1 + EAR = exp(r_{cc}) = e^{r_{cc}}
$$
, where $e$ is approximately 2.71828. To find $r_{cc}$ from the effective annual rate, we solve this equation for $r_{cc}$ as follows:
$$
ln(1 + EAR) = r_{cc}
$$
, where $ln(*)$ is the natural logarithm function, the inverse of $exp(*)$. Both the exponential and logarithmic functions are available in Excel, and are called $EXP(*)$ and $LN(*)$, respectively.

The realized return, called the `holding-period return`, HPR is defined as:
$$
HPR = \frac{{Ending\ price\ of\ a\ share} - {Beginning\ price} + {Cash\ dividend}}{Beginning\ price}
$$
The expected rate of return is a probability-weighted average of the rates of return in each scenario. Calling $p(s)$ the probability of each scenario and $r(s)$ the HPR in each scenario, where scenarios are labeled or "indexed" by $s$, we write the expected return as:
$$
E(r) = \sum_{s}{p(s)}{r(s)}
$$
Variance and standard deviation provide one measure of the uncertainty of outcomes. Symbolically:
$$
\sigma^2 = \sum_{s}{p(s)[r(s) - E(r)]^2}
$$
We measure the reward as the difference between the `expected` HPR on the index stock fund and the `risk-free rate`, that is, the rate you can earn by leaving money in risk-free assets such as T-bills, money market funds, or the bank. We call this difference the `risk premium` on common stocks.

The degree to which investors are willing to commit funds to stocks depends on `risk aversion`.

If there are $n$ observations, we substitute equal probabilities of $1/n$ for each $p(s)$. The expected return, $E(r)$, is then estimated by the arithmetic average of the sample rates of return:
$$
\begin{equation}\begin{split}
E(r) &= \sum_{s=1}^{n}p(s)r(s) = \frac{1}{n}\sum_{s=1}^{n}r(s) \\
&={Arithmetic\ average\ of\ rates\ of\ return}
\end{split}\end{equation}
$$
The larger the swing in rates of return, the greater the discrepancy between the arithmetic and geometric averages, that is, between the compound rate earned over the sample period and the average of the annual returns. If returns come from a normal distribution, the expected difference is exactly half the variance of the distribution, that is:
$$
E[Geometric\ average] = E[Arithmetic\ average] - 1/2\sigma^2
$$
In practice, we usually cannot directly observe expectations, so we estimate the variance by averaging squared deviations from our `estimate` of the expected return, the arithmetic average, $\overline{x}$. Adapting Equation $\sigma^2 = \sum_{s}{p(s)[r(s) - E(r)]^2}$ for historic data, we again use equal probabilities for each observation, and use the sample average in place of the unobservable $E(r)$:
$$
\begin{equation}\begin{split}
Variance &= Expected\ value\ of\ squared\ deviations \\
\sigma^2 &= \sum{p(s)[r(s) - E(r)]^2} 
\end{split}\end{equation}
$$
, using historical data with $n$ observations, we could `estimate` variance as:
$$
\hat{\sigma}^2 = \frac{1}{n} \sum_{s=1}^{n}[r(s) - \overline{r}]^2
$$
, where $\hat{\sigma}$ replaces $\sigma$ to denote that it is an estimate.

The variance estimate from $\hat{\sigma}^2 = \frac{1}{n} \sum_{s=1}^{n}[r(s) - \overline{r}]^2$ is biased downward, however. The reason is that we have taken deviations from the sample arithmetic average, $\overline{r}$, instead of the unknown, true expected value, $E(r)$, and so have introduced an estimation error. Its effect on the estimated variance is sometimes called a `degrees of freedom` bias. We can eliminate the bias by multiplying the arithmetic average of squared deviations by the factor $n/(n - 1)$. The variance and standard deviation then become:
$$
\begin{equation}\begin{split}
\hat{\sigma}^2 &= (\frac{n}{n - 1}) \times \frac{1}{n}\sum_{s=1}^{n}[r(s) - \overline{r}]^2 = \frac{1}{n - 1}\sum_{s=1}^{n}[r(s) - \overline{r}]^2 \\
\hat{\sigma} &= \sqrt{\frac{1}{n - 1} \sum_{s=1}^{n}[r(s) - \overline{r}]^2}
\end{split}\end{equation}
$$
The importance of the trade-off between reward (the risk premium) and risk (as measured by standard deviation or SD) suggests that we measure the attraction of a portfolio by the ratio of risk premium to SD of excess returns:
$$
Sharpe\ ratio = \frac{Risk\ premium}{SD\ of\ excess\ return}
$$
, this reward-to-volatility measure is widely used to evaluate the performance of investment managers.

The bell-shaped `normal distribution` appears naturally in many applications.

A measure of asymmetry called `skew` uses the ratio of the average `cubed` deviations from the average, called the third moment, to the cubed standard deviation to measure asymmetry or "skewness" of a distribution:
$$
Skew = Average \left[\frac{(R-\overline{R})}{\hat{\sigma}^3}\right]
$$
, cubing deviations maintains their sign (the cube of a negative number is negative).

`Kurtosis` measures the degree of fat tails. We use deviations from the average raised to the `fourth` power, scaled by the fourth power of the SD:
$$
Kurtosis = Average \left[\frac{(R-\overline{R})^4}{\hat{\sigma}^4}\right] - 3
$$
, we subtract 3 in this equation, because the ratio for a normal distribution is 3.

A risk measure that addresses these issues is the `lower partial standard deviation (LPSD)` of excess returns, which is computed like the usual standard deviation, but using only "bad" returns.

$m$, the expected continuously compounded expected rate of return, is larger than $g$. The rule for the expected $CC$ annual rate becomes:
$$
E(r_{CC}) = m = g + 1/2\sigma^2
$$
With a normally distributed $CC$ rate, we expect that some initial wealth of $\$W_0$ will compound over one year to $W_0e^{g+1/2\sigma^2} = We^m$, and hence the expected effective rate of return is:
$$
E(r) = e^{g+1/2\sigma^2} - 1 = e^m - 1
$$
If an annual $CC$ rate applies to an investment over any period $T$, either longer or shorter than one year, the investment will grow by the proportion $r(T) = e^{r_{CC}T} - 1$. The expected cumulative return, $r_{CC}T$, is proportional to $T$, that is, $E(r_{CC}T) = mT = gT + 1/2 \sigma^2 T$ and expected final wealth is:
$$
E(W_T) = W_0 e^{mT} = W_0 e^{(g+1/2\sigma^2)T}
$$
, the variance of the cumulative return is also proportional to the time horizon: $Var(r_{CC}T) = TVar(r_{CC})$, but standard deviation rises only in proportion to the square root of time: $\sigma(r_{CC}T) = \sqrt{TVar(r_{CC})} = \sigma \sqrt{T}$.



## Vocabulary

scenario
