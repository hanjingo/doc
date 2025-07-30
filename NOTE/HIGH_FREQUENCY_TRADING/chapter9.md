# CHAPTER 9 Directional Trading Around Events

[TOC]



## Developing Directional Event-Based Strategies

`Directional event-based strategies` refer to a group of trading strategies that place trades on the basis of the markets' reaction to events. The events may be economic, industry, or even instrument-specific occurrences that consistently affect the instrument(s) of interest time and time again.

Most event arbitrage strategies follow a three-stage development process:

1. For each event type, identify dates and times of past events in historical data.
2. Compute historical price changes at desired frequencies pertaining to securities of interest and surrounding the events identified in step 1.
3. Estimate expected price responses based on historical price behavior surrounding past events.



## Forecasting Methodologies

Development of forecasts involves event studies on very specific trading data surrounding event announcements of interest. Event studies measure the quantitative impact of announcements on the returns surrounding the news event and are usually conducted as follows:

1. The announcement dates, times, and "surprise" changes are identified and recorded.

   The surprise component can be measured in two ways:

   - As the difference between the realized value and the prediction based on autoregressive analysis.
   - As the difference between the realized value and the analyst forecast consensus.

2. The returns corresponding to the times of interest surrounding the announcements are calculated for the securities under consideration.

3. The impact of the announcements is then estimated in a simple linear regression:
   $$
   R_{t} = \alpha + \beta \Delta X_{t} + \varepsilon_{t}
   $$

   - $R_{t}$ is the vector of returns surrounding the announcement for the security of interest arranged in the order of announcements.
   - $\Delta X_{t}$ is the vector of "surprise" changes in the announcements arranged in the order of announcements.
   - $\varepsilon_{t}$ is the idiosyncratic error pertaining to news announcements.
   - $\alpha$ is the estimated intercept of the regression that captures changes in returns due to factors other than announcement surprises.
   - $\beta$ measures the average impact of the announcement on the security under consideration.

Changes in equity prices are adjusted by changes in the overall market prices to account for the impact of broader market influences on equity values. The adjustment is often performed using the market model of Sharpe(1964):
$$
R_{t}^{a} = R_{t} - \hat{R_{t}}
$$
, where the "hat" notation expresses the average estimate and $\hat{R_{t}}$ is the expected equity return estimated over historical data using the market model:
$$
R_{t} = \alpha + \beta R_{m,t} \varepsilon_{t}
$$

### Corporate News

Corporate activity, such as earnings announcements, both quarterly and annual, significantly impacts equity prices of the firms releasing the announcements. Unexpectedly positive earnings typically lift equity prices, and unexpectedly negative earnings often depress corporate stock valuation.

Theoretically, equities are priced as present values of future cash flows of the company, discounted at the appropriate interest rate determined by the capital asset pricing model (CAPM), the arbitrage pricing theory of Ross(1977), or the investor-specific opportunity cost:
$$
\text{Equity price} = \sum_{t = 1}^{\infty} \frac{E[Earnings_{t}]}{(1 + R_{t})^{t}}
$$

- $E[Earnings_{t}]$ are the expected cash flows of the company at a future time $t$
- $R_{t}$ is the discount rate found appropriate for discounting time $t$ dividends to present.

### Industry News

Industry news consists mostly of legal and regulatory decisions along with announcements of new products. These announcements reverberate throughout the entire sector and tend to move all securities in that market in the same direction. Unlike macroeconomic news that is collected and disseminated in a systematic fashion, industry news usually emerges in an erratic fashion.

### Macroeconomic News

Macroeconomic decisions and some observations are made by government agencies on a predetermined schedule.

### Foreign Exchange Markets

Andersen et al. (2003) use the consensus forecasts compiled by the International Money Market Services (MMS) as the expected value for estimation of surprise component of news announcements. The authors then model the five-minute changes in spot foreign exchange rate $R_{t}$ as follows:
$$
R_{t} = \beta_{0} + \sum_{i=1}^{I}\beta_{i}R_{t-i} + \sum_{k=1}^{K} \sum_{j=0}^{J} \beta_{kj} S_{k, t - j} + \varepsilon_{t}, t = 1, ..., T
$$

- $R_{t - i}$ is $i$-period lagged value of the five-minute spot rate.
- $S_{k,t -j}$ is the surprise component of the $k^{th}$ fundamental variable lagged $j$ periods.
- $\varepsilon_{t}$ is the time-varying volatility that incorporates intraday seasonalities.

### Equity Markets

According to classical financial theory, changes in equity prices are due to two factors: changes in expected earnings fo publicly traded firms, and changes in the discount rates associated with those firms.

Ample empirical evidence shows that equity prices respond strongly to interest rate announcements and, in a less pronounced manner, to other macroeconomic news.