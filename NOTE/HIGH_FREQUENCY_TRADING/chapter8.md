# CHAPTER 8 Statistical Arbitrage Strategies

[TOC]

Like human trading, high-frequency trading (HFT) strategies can be broken down into three major categories (per Harris, 1998):

1. Statistical arbitrage or stat-arb, also known as value-motivated strategies.
2. Directional strategies, also known as informed trading.
3. Market-making, also known as liquidity trading.



## Practical Applications of Statistical Arbitrage

Summary of Fundamental Arbitrage Strategies by Asset Class Presented in This Section:

| Asset Class      | Fundamental Arbitrage Strategy              |
| ---------------- | ------------------------------------------- |
| Equities         | Pairs trading                               |
| Equities         | Different equity classes of the same issuer |
| Equities         | Risk arbitrage                              |
| Equities         | Liquidity rbitragea                         |
| Foreign exchange | Triangular arbitrage                        |
| Foreign exchange | Uncovered interest parity (UIP) arbitrage   |
| Indices and ETFs | Index composition arbitrage                 |
| Options          | Volatility curve arbitrage                  |
| Cross-asset      | Futures basis trading                       |
| Cross-asset      | Futures/ETF arbitrage                       |

### Pairs Trading

A relationship based on price levels $S_{i,t}$ and $S_{j,t}$ for any two instruments $i$ and $j$ can be arrived at through the following procedure:

1. Identify the universe of liquid financial instruments: instruments that trade at least once within the desired trading frequency unit.

2. Measure the difference between prices of every two securities, $i$ and $j$, identified in step (1) across time $t$:
   $$
   \Delta S_{ij,t} = S_{i,t} - S_{j,t}, t \in [1, T]
   $$
   , where $T$ is a sufficiently large number of daily observations.

3. For each pair of securities, select the ones with the most stable relationship security pairs that move together. To do this, Gatev, Goetzmann and Rouwenhorst (1999) perform a simple minimization of the historical differences in returns between every two liquid securities:
   $$
   min_{i,j} \sum_{t = 1}^{T} (\Delta S_{ij,t})^{2}
   $$

4. Estimate basic distributional properties of the difference as follows. Mean or average of the difference:
   $$
   E[\Delta S_{t}] = \frac{1}{T} \sum_{t = 1}^{T} \Delta S_{t}
   $$
   , Standard deviation:
   $$
   \sigma [\Delta S_{t}] = \frac{1}{T - 1} \sum_{t = 1}^{T}(\Delta S_{t} - E[\Delta S_{t}])^{2}
   $$

5. Monitor and act upon differences in security prices:

   At a particular time $\tau$, if:
   $$
   \Delta S_{\tau} = S_{i,\tau} - S_{j,\tau} > E[\Delta S_{\tau}] + 2\sigma[\Delta S_{\tau}]
   $$
   sell security $i$ and buy security $j$. However, if:
   $$
   \Delta S_{\tau} = S_{i,\tau} - S_{j,\tau} < E[\Delta S_{\tau}] - 2\sigma[\Delta S_{\tau}]
   $$
   buy security $i$ and sell security $j$.

6. Once the gap in security prices reverses to achieve a desirable gain, close out the positions. If the prices move against the predicted direction, activate stop loss.

### Arbitraging Different Equity Classes of the Same Issuer

It is reasonable to expect stocks corresponding to two common equity classes issued by the same company to be trading within a relatively constant price range from each other.

A typical trade may work as follows: if the price range widens to more than two standard deviations of the average daily range without a sufficiently good reason, it may be a fair bet that the range will narrow within the following few hours.

The dual-class share strategy suffers from two main shortcomings and may not work for funds with substantial assets under management (AUM):

1. The number of public companies that have dual share classes trading in the open markets in severely limited, restricting the applicability of the strategy.
2. The daily volume for the less liquid share class is often small, further restricting the capacity of the strategy.

### Risk Arbitrage

The CAPM is based on the idea that returns on all securities are influenced by the broad market returns. The degree of the co-movement that a particular security may experience with the market is different for each individual security and can vary through time.

The CAPM equation is specified as follows:
$$
r_{i,t} - r_{f,t} = \alpha_{i} + \beta_{i}(r_{M,t} - r_{f,t}) + \varepsilon_{t}
$$

- $r_{i,t}$ is the return on security $i$ at time $t$.
- $r_{M,t}$ is the return on a broad market index achieved in time period $t$.
- $r_{f,t}$ is the risk-free interest rate, such as Fed Funds rate, valid in time period $t$.

, The equation can be estimated using ordinary least squares (OLS) regression. The resulting parameter estimates, $\hat{\alpha}$ and $\hat{\beta}$, measure the abnormal return that is intrinsic to the security $(\hat{\alpha})$ and the security's comovement with the market ($\hat{\beta}$).

Once the point estimates for alphas and betas of the two securities are produced, along with standard deviations of those point estimates, the statistical significance of difference in alphas and betas is then determined using the difference in the means test, described here for betas only:
$$
\Delta \hat{\beta} = \hat{\beta_{i}} - \hat{\beta_{j}} \\
\hat{\sigma_{\Delta \beta}} = \sqrt{\frac{\sigma_{\beta_{i}}^{2}}{n_{i}} + \frac{\sigma_{\beta_{j}}^{2}}{n_{j}}}
$$
, where $n_{i}$ and $n_{j}$ are the numbers of observations used in the estimation of above equation for security $i$ and security $j$, respectively.

The standard $t$-ratio statistic is then determined as follows:
$$
\text{Student} t_{\beta} = \frac{\Delta \hat{\beta}}{\hat{\sigma}_{\Delta \beta}}
$$
, the difference test for alphas follows the same procedure as the one outlined for betas in above equations.

As with other $t$-test estimations, betas can be deemed to be statistically similar if the $t$ statistic falls within one standard deviation interval:
$$
t_{\beta} \in [\Delta \hat{\beta} - \hat{\sigma}_{\Delta \beta}, \Delta \hat{\beta} + \hat{\sigma}_{\Delta \beta}]
$$
At the same time, the difference in alphas has to be both economically and statistically significant. The difference in alphas has to exceed trading costs, $TC$, and the $t$-ratio has to indicate a solid statistical significance, with 95 percent typically considered the minimum:
$$
\Delta \hat{\alpha} > TC \\
|t_{\alpha}| > [\Delta \hat{\alpha} + 2\hat{\sigma}_{\Delta \alpha}]
$$
Once a pair of securities satisfying above equations is identified, the traer goes long in the security with the higher alpha and shorts the security with the lower alpha. The position is held for the predetermined horizon used in the forecast.

### Liquidity Arbitrage

In classical asset pricing literature, a financial security that offers some inconvenience to the prospective investors should offer higher returns to compensate investors for the inconvenience. Limited liquidity is one such inconvenience; lower liquidity levels make it more difficult for individual investors to unwind their positions, potentially leading to costly outcomes. On the flip side, if liquidity is indeed priced in asset returns, then periods of limited liquidity may offer nimble investors highly profitable trading opportunities.

Pastor and Stambaugh (2003) find that in equities, stocks whose returns have higher exposure to variability in the market-wide liquidity indeed deliver higher returns than stocks that are insulated from the market-wide liquidity. To measure sensitivity of stock $i$ to market liquidity, Pastor and Stambaugh (2003) devise a metric $\gamma$ that is estimated in the following OLS specification:
$$
r_{i, t+1}^{e} = \theta + \beta_{r_{i,t}} + \gamma sign(r_{i,t}^{e}).v_{i,t} + \tau_{t + 1}
$$

- $r_{i,t}$ is the return on stock $i$ at time $t$.
- $v_{i,t}$ is the dollar volume for stock $i$ at time $t$.
- $r_{i.t}^{e}$ is the return on stock $i$ at time $t$ in excess of the market return at time $t$: $r_{i,t}^{e} = r_{i,t} - r_{m,t}$.

, The sign of the excess return $r_{i,t}^{e}$ proxies for the direction of the order flow at time $t$; when stock returns are positive, it is reasonable to assume that the number of buy orders in the market outweighs the number of sell orders, and vice versa. The prior time-period return $r_{i,t}$ is included to capture the first-order auto-correlation effects shown to be persistent in the return time series of most financial securities.

### Large-to-Small Information Spillovers

Small stocks are known to react to news significantly more slowly than large stocks. Lo and MacKinlay (1990), for example, found that returns on smaller stocks follow returns on large stocks.

The market features of small stocks make the stocks illiquid and highly inefficient, enabling profitable trading.

### Foreign Exhange

Triangular arbitrage exploits temporary deviations from fair prices in three foreign exchange crosses.

### Uncovered Interest Parity Arbitrage

Chaboud and Wright (2005) find that the UIP best predicts changes in foreign exchange rates at high frequencies and daily rates when thecomputation is run between 4:00 p.m.ET and 9:00 p.m.ET. The UIP is specified as follows:
$$
1 + i_{t} = (1 + i_{t}^{*})\frac{E_{t}[S_{t + 1}]}{S_{t}}
$$

- $i_{t}$ is the one-period interest rate on the domestic currency deposits.
- $i_{t}^{*}$ is the one-period interest rate on deposits denominated in a foreign currency.
- $S_{t}$ is the spot foreign exchange price of one unit of foreign currency in units of domestic currency.

### Indices and ETFs

Alexander (1999) shows that cointegration-based index arbitrage strategies deliver consistent positive returns and sets forth a cointegration-based portfolio management technique step by step:

1. A portfolio manager selects or is assigned a benchmark.

2. The manager next determinies which countries lead EAFE by running the error-correcting model (ECM) with log(EAFE) as a dependent variable and log prices of constituent indices in local currencies as independent (explanatory) variables:
   $$
   EAFE_{t} = \alpha + \beta_{1 x_{1,t}} + ... + \beta_{n X_{n,t}} + \varepsilon_{t}
   $$
   , where the statistically significant $\beta_{1} ... \beta{n}$ coefficients indicate optimal allocations pertaining to their respective country indices $X_1 ... X_n$, and $\alpha$ represents the expected outperformance of the EAFE benchmark if the residual from the cointegrating regression is stationary. $\beta_{1} ... \beta_{n}$ can be constrained in estimation, depending on ivestor preferences.

### Basis Trading

Futures are financial instruments of choice in many cross-market stat-arb models. Futures prices are liner functions of the underlying asset and are easy to model:
$$
F_{t} = S_{t} exp[r_{t}(T - t)]
$$

- $F_t$ is the price of a futures contract at time $t$.
- $S_t$ is the price of the underlying asset also at time $t$.
- $T$ is the time the futures contract expires.
- $r_t$ is the interest rate at time $t$. For foreign exchange futures, $r_t$ is the differential between domestic and foreign interest rates.

### Futures/ETF Arbitrage

In response to macroeconomic news announcements, futures markets have been shown to adjust more quickly than spot markets.

### Cointegration of Various Financial Instruments/Asset Classes

Stat-arb models can also be built on two or more financial instruments, potentially from drastically different asset classes. Often, such multi-instrument multiasset models are developed using cointegration. `Cointegration` refers to a condition whereby prices of two or more financial instruments move in tandem according to a simple specification, parameterized on historical data. A two-instrument cointegration model can be specified as follows:
$$
P_{1,t} = \alpha + \beta P_{2,t} + \varepsilon_{t}
$$

- $P_{1,t}$ is the price of the first financial instrument.
- $P_{2,t}$ is the price of the second financial instrument under consideration.
- $\alpha$ and $\beta$ are coefficients in a simple OLS regression.

To further fine-tune statistical dependencies between any two securities, a stat-arb researcher may include lagged realizations of price changes in a vector-autoregressive framework to detect stat-arb relationships several time periods ahead of trading time:
$$
P_{1,t} = \alpha + \beta_{0}p_{2,t} + \beta_{1}(p_{2,t} - p_{2,t - 1}) + \beta_{2}(p_{2,t - 1} - p_{2, t - 2}) + ... + \beta_{k}(p_{2, t - k + 1} - p_{2, t - k}) + \varepsilon_{t} \\
p_{2,t} = \gamma + \delta_{0}p_{1,t} + \delta_{1}(p_{1,t} - p_{1,t - 1}) + \delta_{2}(p_{1,t - 1} - p_{1,t - 2}) + ... + \delta_{k}(p_{1,t - k + 1} - p_{1, t - k}) + w_{t}
$$
Another common way to enhance performance of stat-arb models is to extend the regression of above equation with additional financial instruments:
$$
p_{1,t} = \alpha + \beta p_{2,t} + \gamma p_{3,t} + ... + \delta p_{n,t} + \varepsilon_{t}
$$
