# CHAPTER 10 Automated Market Making--Naive Inventory Models

[TOC]

Most high-frequency trading (HFT) systems are deployed to provide automated market-making services.

Automated market making provides several advantages to the market-making institution as well as other market participants:

- First, automated market makers stay on script. As a result, automated market makers reduce the incidence of market crashes and negative surprises for market maker's bottom line.
- Second, execution of automated market making is cost-efficient: once the human-intensive programming and testing stages are completed, automated market makers require little compensation.

The two broad functions of a market maker are therefore:

- Manage inventory to ensure sufficient profitability.
- Keep track and respond to information in order to avoid being "run over" or "picked over" by the markets.



## Naive Market-Making Strategies

### Fixed Offset

The smaller the offset of a limit order from the market price in a naive strategy, reallocation of the market maker's capital.

### Volatility-Dependent Offset

In high-volatility conditions, limit orders farther away from the market are likely to be hit, generating higher premium for market makers. In low-volatility conditions, however, limit orders may need to be placed closer to the market to be executed. A sample determination of volatility-dependent offset is shown in the equation:
$$
\text{offset}_{t} = \text{round}(\frac{1}{T} \sum_{\tau = t - 1}^{t - T}(p_{\tau} - p_{\tau - 1})^{2})
$$

### Offset Is a Function of Order-Arrival Rate

Under the assumptions of exponentially distributed inter-arrival times, for example, the market orders arrive to "hit the bid" and to "lift the ask" with a certain average rate, $\mu$. The limit orders can be assumed to repopulate the top of the limit order book at an average rate $\lambda$. Probability of a top-of-the-book limit order being matched can then be expressed as a function of $\lambda = 1 / \lambda$, $\mu = 1 / \mu$ and a given interval of time, $\Delta t$:
$$
P(hit, \Delta t) = 1 - P(\text{not hit}, \Delta t) = 1 - exp(- \frac{\lambda}{\mu} \Delta t)
$$
, Parameters $\lambda$ and $\mu$ can be calibrated on recent tick data. Level I data can be used to calibrate parameters for minimal time intervals, $\Delta t = 1$. When the best bid moves up or the size at the best bid increases, a new limit buy order is assumed to have arrived. When the best ask moves up or the size at the best ask decreases, a market buy order is recorded.

Another analytical model for determining the optimal offset of limit orders is due to Foucault, Kadan, and Kandel (2005). This model explicitly suggests whether a trader should place a passive or an aggressive limit order, and how many ticks away from the market price the trader should place his limit order. The model makes the following key assumptions:

- All other execution parameters have been selected.
- All traders in the market are free to switch from passive to aggressive execution, and vice versa.

, The determining factor in whether or not a trader decides to place a passive or an aggressive order, is the so-called "reservation spread," defined as follows:
$$
j^{R} = ceiling[\frac{\delta}{\mu \Delta}]
$$

- $\delta$ is the market-maker's expected dollar-cost of execution that may incorporate expectations about market impact.
- $\Delta$ is the minimal tick size, say $\$0.01$ for equities.
- $\mu$ is the arrival rate of matching market orders per unit of time; with $1/\mu$ representing the average time between two sequential order arrivals. If the model is used to determine levels of aggressiveness of limit buy orders, $\mu$ is the rate of arrival of market sell orders, computed as a number of market sell orders recorded per unit of time. In Foucault et al. (2005), all orders, both market and limit, are assumed to be of the same size.

In a market with $[1 ... q]$ heterogeneous traders, $j_{1}^{R} < j_{2}^{R} < ... < j_{q}^{R}$, similar dynamics hold: whenever the market spread $s$ is smaller than the $i$th trader reservation spread $j_{i}^{R}$, all traders $[i, ..., q]$ place market orders. All traders with reservation spread smaller than the market spread $s$, on the other hand, place limit orders at their reservation spread.

The differences in transaction costs of traders may be due to the following factors:

- Fees: Large institutional traders are likely to face lower fees than smaller traders.
- Market impace: Large child orders are expected to bear higher market impact than smaller order slices.
- Taxes: Individual investors may be subject to high marginal tax rates on their trading gains.
- Other quantifiable transaction costs.

Key implications from Foucault et al. (2005) model, $j^{R} = ceiling[\frac{\delta}{\mu \Delta}]$, include the following observations:

- Higher market order arrival rates lead to lower reservation spreads, and as a result, lower market spreads. As a result, competing market orders are good for the markets, lowering the costs of overall trading.
- Lower trading costs also lead to lower spreads, suggesting that rebates help facilitate cheaper execution, not to make trading more expensive.
- High execution costs and low market order arrival rates, however, result in wide reservation spreads, and may destroy markets by creating no-trade voids.



## Market Making as a Service

Many measures of liquidity have been developed over the years. Among the most popular metrics are:

- The tightness of the bid-ask spread.
- Market depth at best bid and best ask.
- Shape of the order book.
- Price sensitivity to block transactions.
- Price sensitivity to order-flow imbalance.
- Price change per unit volume.
- Technical support and resistance levels.
- Market resilience.



## Shape of the Order Book

When available, Level 2 data can be used to calculate the exact amount of aggregate supply and demand available on a given venue. Using Level 2 data, supply and demand can be determined as the cumulative sizes of limit orders posted on the sell and buy sides of the limit order book, respectively.

### Price Sensitivity to Block Transactions

When the Level 2 data are not available, the shape of the order book can still be estimated using techniques that hail from technical analysis, like support and resistance levels and moving averages.

Mathematically, support and resistance levels are determined as linear projections of recent price minima in case of support, and maxima in case of resistance. To determine the support level one minute ahead, the algorithm would compute minimum prices within the past minute and the prior minute, and then project the minima trend one minute ahead:
$$
SL_{t + 1} = min(P_{t}) + (min(P_{t}) - min(P_{t - 1}))
$$
, Similarly, resistance level can be computed as:
$$
RL_{t + 1} = max(P_{t}) + (max(P_{t}) - max(P_{t - 1}))
$$
, In addition to support and resistance levels, indicators based on moving averages help identify the skewness of the order book. When a short-run moving average rises above a long-run moving average, the buy-side liquidity pool in the limit order book moves closer to the market price.

### Price Change per Unit Volume

A modified Kyle's lambda proposed by Aldridge (2012d) works as follows:
$$
\Delta P_{t} = \alpha + \lambda(S_{t}^{b} - S_{t}^{a}) + \varepsilon_{t}
$$
, where $\Delta P_{t}$ is a change in prices on executed trades observed during predefined time period $t$, $S_{t}^{b}$ is the aggregate volume of trades executed at the best bid that was in force at the time each trade was processed during period $t$, and $S_{t}^{a}$ is the volume of trades matched at the best ask prevailing at trade time. The difference between $S_{t}^{b} - S_{t}^{a}$ can be interpreted as the net order flow imbalance observed during time period $t$: the volume executed at bid is likely to be generated by market sell orders, while the trades processed at ask are often a result of market buy orders.

### Technical Support and Resistance Levels

Absolute price change per unit volume traded is yet another measure of liquidity:
$$
\gamma_{t} = \frac{1}{D_{t}} \sum_{d=1}^{D_{t}} \frac{|r_{d,t}|}{v_{d,t}}
$$
, This metric is due to Amihud (2002) and is known as the illiquidity ratio.
