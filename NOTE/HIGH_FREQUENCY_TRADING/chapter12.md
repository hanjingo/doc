# CHAPTER 12 Additional HFT Strategies, Market Manipulation, and Market Crashes

[TOC]

As this chapter shows, strategies thought to be malicious and often associated with HFT fall into one of the following categories:

- Legitimate strategies serving price discovery.
- Strategies not feasible in "lit" markets-regulated exchanges; the same strategies can be feasible in dark pools.
- Strategies that are a direct consequence of pump-and-dump activity, a market manipulation technique that is banned in most financial markets.

The CFTC subcommittee on HFT tasked with identifying undesirable HFT strategies identified the following instances:

- Latency arbitrage
- Spread scalping
- Rebate capture
- Quote matching
- Layering
- Ignition
- Pinging/Sniping/Sniffing
- Quote stuffing
- Spoofing
- Pump-and-dump manipulation
- Machine learning

### Latency Arbitrage

Latency arbitrage is an example of a trading strategy that is based on taking advantage of high speeds.

### Spread Scalping

High-frequency `spread scalping` often refers to an automated market-making activity that some market participants think is simple: a continuous two-sided provision of liquidity that generates or "scalps" the spread value for the account of the HFT.

### Rebate Capture

Under this strategy, high-frequency traders are presumed to generate profit simply by arbitrage the costs and benefits of limit and market orders on various exchanges.

### Quote Matching

The strategy assumes that the high-frequency trader is capable of identifying which limit orders always move the markets in a certain direction in the short term, allowing the high-frequency trader to quickly take advantage of the move, reversing positions, and capturing the profit.

### Layering

In `layering`, a high-frequency trader enters limit orders at different price levels away from the market price, often to cancel the orders in the near future, and then to resubmit the orders again. The objectives of layering often confound casual observers, who in turn suspect wrongdoing.

### Ignitiong

In an `ignition` strategy, a high-frequency trader is thought to detect the location of long-term investors' stop-loss orders and match against them, or "ignite" them. Next, the strategy assumes that large stop-loss positions will have a substantial impact on the market, allowing the high-frequency trader to ride the market impact wave, swiftly closing out his positions, all the while capturing small gains at the expense of long-term investors' losses.

### Pinging/Sniping/Sniffing/Phishing

`Pinging, sniping, sniffing,` and `phishing` monikers typically refer to the same general type of strategy. The pinging strategy, much like the ignition strategy, identifies hidden pools of limit orders and matches against those orders, creating and riding temporary market impact for small gains.

### Quote Stuffing

quote-stuffing traders are thought to send in rapid orders and cancellations with the expressed purpose of slowing down other traders, and thus manipulating markets. Quote-stuffing traders are further thought to do so to delay other traders, ensure quote stuffers' priority access to the matching engine and the quote stream, and then effectively front-run other traders.

### Spoofing

In spoofing, the trader intentionally distorts the order book without execution; in the process, the trader changes other traders' inferences about available supply and demand, and resulting prices.

### Pump-and-Dump

In the high-frequency pump-and-dump, computer-assisted traders are thought to momentarily drive up or down the prices of securities, only to promptly reverse their positions and capitalize on false momentum at the expense of other traders.

Aldridge (2012e) formally describes pump-and-dump strategies using a measure of permanent market impact $f(V_{t})$ of a trade of size $V_{t}$ processed at time $t$, where $V_{t} > 0$ indicates a buyer-initiated trade and $V_{t} < 0$ describes a seller-initiated trade. If $f(V) > -f(-V)$, a trader could artificially pump and then dump by first buying and then selling at the same trade size $V$. Conversely, if $f(V) < -f(-V)$, the trader could manipulate the markets by first selling and then buying the securities back.

Denoting market impact function $f$, we obtain the following specification:
$$
f_{t + 1} = ln[P_{t + 1}] - ln[P_{t - 1}] \\
\vdots \\
f_{t + \tau} = ln[P_{t + \tau}] - ln[P_{t - 1}]
$$
To evaluate the feasibility of the pump and dump, we use a linear specification for the market impact as a function of trading volume, $V$, consistent with Breen, Hodrick, and Korajczyk (2002); Kissell and Glantz (2002); and Lillo, Farmer, and Mantegna (2003), following Huberman and Stanzl (2004) and Gatheral (2010):
$$
f_{t + \tau}(V_{t}) = \alpha_{\tau} + \beta_{\tau}V_{t} + \varepsilon_{t + \tau}
$$
, where $V_{t}$ is the size of trade executed at time $t$, $\beta_{\tau}$ is the trade size-dependent market impact, and $\alpha_{\tau}$ is the trade size-independent impact of each trade recorded at time $t$. If the high-frequency pump-and-dump is feasible, $\beta_{\tau}$ for buyer-initiated trades will be different from $-\beta_{\tau}$ estimated for seller-initiated trades. The null hypothesis, that pump-and-dump exists in trading activity of a financial instrument, can then be specified as follows:
$$
H_{0}:\beta_{\tau}|_{\text{buyer-initiated trades}} \neq -\beta_{\tau}|_{\text{seller-initiated trades}}
$$
, And the alternative hypothesis ruling out pump and dump can be specified as:
$$
H - A.:,,\beta - \tau.|\text{-buyer-initiated trades} = -,,\beta - \tau.|\text{-seller-initiated trades}
$$

### Machine Learning

Machine learning can be broken down into two major categories:

- supervised learning.

  Supervised learning is the iterative estimation of data relationships, whereby each subsequent iteration seeks to minimize the deviations from the previous analysis.

- unsupervised learning

  Unsupervised learning seeks to identify patterns in so-called unstructured data, devoid of any relationships. Techniques used to distill information under an unsupervised learning umbrella include identification of important signals by observing clustering of data points.

A supervised boosting algorithm works as follows: a dependent variable $Y$, for instance, a time series of returns on a particular financial instrument, is fitted with a function $G$, expressing dependence of $Y$ on returns of another financial instrument, $X$, and parameters $\theta$:
$$
Y_{t} = G(X_{t}, \theta) + \varepsilon_{t}
$$
, Next, the boosting error term is computed as follows:
$$
E = \sum W_{t} I_{st<>0}
$$
, where $I_{st <> 0}$ is the indicator function taking on value of 0 when $G(X_{t}, \theta)$ matches $Y_{t}$ precisely, and 1 when $\varepsilon_{t}$ is not equal to 0. The time series $w_{t}$ represents boosting weights assigned to each observation time, with all weights in the first iteration set to 1, and weights in later iterations recomputed according to the following calculation:
$$
w_{t}^{'} = w_{t} exp(\alpha_{t} I_{st <> 0})
$$
, where:
$$
\alpha = log[\frac{1 - s_t}{s_t}]
$$
This machine learning methodology ultimately produces a function $G(X_{t}, \theta)$ that closely fits $Y_{t}$.