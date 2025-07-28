# CHAPTER 14 Risk Management of HFT

[TOC]



## Measuring HFT Risk

### Regulatory and Legal Risk

Regulatory and legal risk comprises the demands of new legislations that may affect the operation of HFT systems.

### Credit and Counterparty Risk

`Credit risk` specifies potential issues in a high-frequency trader's ability to secure leverage. Leverage refers to the trader's ability to borrow capital for his trading needs.

### Market Risk

The bulk of high-frequency market risk management focuses on the following four key aspects:

1. First order: Stop losses.

   Stop losses denote hard loss limits for each position and can be fixed or variable, absolute or trailing.

2. Second order: Volatility cutouts.

   The optimal stop-loss parameter should satisfy the following three requirements:

   - The stop loss should limit losing trades without affecting the winning trades.
   - A stop loss should not be triggered due to natural market volatility alone.
   - Stop losses should be executed immediately.

   The preceding requirements translate into the following mathematical conditions for stop losses:
   $$
   E[Profit] > 0
   $$
   , where $E[Profit]$:
   $$
   \begin{equation}\begin{split} 
   &=E(Gain) * Pr(Gain) + E(Loss|Loss > StopLoss) \\
   &*Pr(Loss|Loss > StopLoss) \\
   &+E(Loss|Loss \leq StopLoss) \\
   &*Pr(StopLoss|Loss \leq StopLoss) \\
   \end{split}\end{equation}
   $$
   Probability of gain, $Pr(Gain)$, as well as the cumulative probability of loss, $Pr(Loss|Loss > StopLoss) + Pr(StopLoss|Loss \leq StopLoss)$, can be estimated from the simulation, as can be the average gain, $E(Gain)$, and average losses above and below the stop loss values, $E(Loss|Loss > StopLoss)$ and $E(Loss|Loss \leq StopLoss)$​.

   `Volatility cutouts` refer to rules surrounding market conditions during which the HFT systems are halted.

   To determine the volatility conditions optimal for strategy execution, one may use the following technique:

   1. In the in-sample back-test, estimate the volatility parameter over a rolling window. Within each time window, the volatility parameter can be estimated as a simple standard deviation, or (better) weighted toward later observations using a triangular or exponential weighting function. The duration of the window can match the average position holding time of the strategy.

   2. Regress strategy gains on the obtained volatility estimates using the following equation:
      $$
      R_{t} = \alpha + \beta \hat{\sigma_{t}} + \varepsilon_{t}
      $$
      , where $R_{t}$ represents the gain of the last completed round-trip trade realized at time $t$, and $\hat{\sigma_{t}}$ is the moving volatility estimate obtained in the previous step. Instead of realized strategy returns, the $R_{t}$ on the left-hand side of the regression can be mark-to-market strategy gain sampled at regular time intervals.

   3. If the estimate of $\beta$​ is positive (negative) and statistically significant, the strategy performs better in high (low) volatility conditions. A median of volatility estimates obtained in step 1 above can be used as a turn-on/turn-off volatility switch for the strategy.

   Volatility has been shown to "cluster" in time: volatility "builds up" into peaks and reverses into valleys gradually, resulting in clusters of high-volatility observations. As a result, volatility is straightforward to predict: high-volatility observations are usually followed by more or less high observations, while low-volatility cases are surrounded by similarly low volatility figures.

   When the key research question is whether the volatility is high or low, another technique, known as `Markov state dependency`, developed by Aldridge (2011), may work best. The Markov technique divides historical observations into high and low volatility states, and then assesses probabilities of transition from high to low probability and vice versa. Specifically, the technique can be used as follows:

   1. Run a linear regression of price changes on past price changes.
   2. Examine the distribution of error terms; separate them into two groups: low and high errors, based on the arbitrary yet appropriate cutoff point.
   3. Estimate historical "transition probabilities" based on the sequential changes from low to high states and vice versa:
      - For each sequential error observation, determine whether the error was a change from low to high, a change from high to low, a stay in the low state, or a stay in the high-volatility state.
      - Count the totals and express them in a percentage probability form.
   4. During run-time, assess whether the current volatility level is high or low. Given the probabilities of transition determined in step 3, assess the likelihood of a volatility change in the next period. Adjust the trading accordingly.

3. Third and fourth order: Short-term value-at-risk (VaR).

   Value-at-risk(VaR) is a probabilistic metric of potential loss that takes into consideration the distributional properties of returns of the HFT.

   To compute VaR, the trader or risk manager may use the following steps：

   1. Compute daily net (after transaction costs) historical returns of the strategy either live or simulated (back-tested) returns.
   2. Determine the cut-off corresponding to the worst 5 percent of strategy returns.
   3. Set the shutdown threshold equivalent to the lowest 5 percentile of strategy returns, place the strategy "on probation" in paper trading until the cause of the low return is ascertained and the strategy is adjusted.

   The parameterization of the tails is performed using the extreme value theory (EVT). `EVT` is an umbrella term spanning a range of tail modeling functions. Dacorogna et al. (2001) note that all fat-tailed distributions belong to the family of Pareto distributions. A Pareto distribution family is described as follows:
   $$
   G(x)
   \begin{cases}
   0 &x \leq 0 \\
   exp(-x^{-\alpha}) &x > 0, \alpha > 0
   \end{cases}
   $$
   , where the tail index $\alpha$​ is the parameter that needs to be estimated from the return data. For raw security returns, the tail index varies from financial security to financial security. Even for raw returns of the same financial security, the tail index can bary from one quoting institution to another, especially for really high-frequency estimations.
   
   Suleiman et al. (2005) define tracking error as a contemporaneous difference between the manager's return and the return on the manager's benchmark index:
   $$
   TE_{t} = In(R_{i,t}) - In(R_{X,t})
   $$
   , where $R_{i,t}$ is the manager's return at time $t$ and $R_{x,t}$ is return on the manager's benchmark, also at time $t$. The Var parameters are then estimated on the tracking error observations.
   
4. Higher order: Hedging with other instruments.

   The objective of hedging is to create a portfolio tht maximizes returns while minimizing risk--downside risk in particular. Hedging can also be thought of as a successful payoff matching: the negative payoffs of one security "neutralized" by positive payoffs of another.

   Hedging can be further broken down into the following categories:

   - Delta hedging

     In delta hedging, for every unit of the HF-traded instrument, the system purchases a specific quantity of the hedging instrument. This hedging quantity is determined by the average relative changes in the prices of the HF-traded instrument and the hedging instrument:
     $$
     Q_{hedging, t} = \frac{\Delta P_{HFT,t}}{\Delta P_{hedging,t}}
     $$
     , where $\Delta P_{HFT,t}$ is the average return on the HF-traded instrument computed per chosen unit of time, and $\Delta_{hedging,t}$ represents the return on the selected hedging instrument computed over the same unit of time.

   - Portfolio hedging

     A classic portfolio hedging strategy, developed by Mrkowis (1952), solves the following optimization problem:
     $$
     max\ x\ E[R] - Ax^{'} Vx \\
     s.t.\sum x_{i} = 1
     $$
     , where $x_{i}$ is the portfolio weight of security $i, i \in [1, ..., I], E[R]$ is a vector of expected returns of $I$ securities, $V$ is an $I \times I$ variance-covariance matrix of returns, and $A$ is the coefficient reflecting the risk aversion of the trading operation. $A$ is commonly assumed to be 0.5 to simplify the solution. A dynamic state-dependent hedging would repeat the process outlined in above equation, but only for returns pertaining to a specific market state.
     
     Several classes of algorithms have been proposed to simplify and speed up setting the optimal portfolio weights:
     
     1. Simultaneous equations
     
     2. Nonlinear programming
     
     3. Critical-line optimizing algorithms
     
     4. Discrete pairwise (DPW) optimizations
     
     5. Genetic algorithms
     
        The traditional Bayesian approach, applied to mean-variance optimization by Jorion (1986), works as follows: both mean and variance estimates of a portfolio computed on a contemporary data sample are adjusted by lessons gleaned from historical (prior) observations.
     
        The dispersion of the distributions of the true mean and variance of the distributions shrinks as more observations are collected and analyzed with time. If $R_{p,t}$ is the portfolio return following the mean-variance optimization of follow equation from time $t - 1$ to time $t$, and $\hat{E}[R_{i,t}]$ is the average return estimate for security $i$, $\hat{E}[R_{i,t}] = \frac{1}{t} \sum_{\tau = 1}^{t}R_{i,\tau}$, the "Bayes-Stein shinkage estimators" for expected return and variance of an individual security $i$ to be used in the mean-variance optimization for the next period $t + 1$, are computed as follows:
        $$
        E[R_{i,t+1}]_{BS} = (1 - \phi_{i,BS})\hat{E}[R_{i,t}] + \phi_{i,BS}R_{p,t} \\
        V[R_{i,t+1}]_{BS} = V[R_{i,t}][1 + \frac{1}{t + v}] + \frac{v}{t(t + 1 + v)}V[R_{i,t}]
        $$
        , where $v$ is the precision of the mean estimates: $v = \frac{(N - 2)}{t} \frac{V[R_{i,t}]}{(R_{p,t} - \hat{E}[R_{i,t}])^{2}}$, $N$ is the number of observations in the sample at time $t$, and $\phi_{BS}$ is the shrinkage factor for the mean: $\phi_{BS} = \frac{v}{t + v}$. The case of zero precision ($v = 0$) corresponds to completely diffuse estimates.

### Liquidity Risk

Bervas (2006) proposes the following measure of liquidity risk:
$$
VaR^{L} = VaR + \text{Liquidity Adjustment} = VaR - (\mu^{S} + z_{\alpha}\sigma^{S})
$$
, where VaR is the market risk value-at-risk discussed previously in this chapter, $\mu^{S}$ is the mean expected bid-ask spread, $\sigma^{S}$ is the standard deviation of the bid-ask spread, and $z_{\alpha}$ is the confidence coefficient corresponding to the desired $\alpha$-percent of the VaR estimation. Both $\mu^{S}$ and $\sigma^{S}$ can be estimated either from raw spread data or from the Roll (1984) model.

Using Kyle's $\lambda$ measure, the VaR liquidity adjustment can be similarly computed through estimation of the mean and standard deviation of the trade volume:
$$
VaR^{L} = VaR + \text{Liquidity Adjustment} = VaR - (\hat{\alpha} + \hat{\lambda}(\mu^{NVOL} + z_{\alpha}\sigma^{NVOL}))
$$
where $\hat{\alpha}$ and $\hat{\lambda}$ are estimated using OLS regression following Kyle(1985):
$$
\Delta P_{t} = \alpha + \lambda NVOL_{t} + \varepsilon_{t}
$$
$\Delta P_{t}$ is the change in market price due to the market impact of orders, and $NVOL_{t}$ is the difference between the buy and sell market depths in period $t$.

Hasbrouck (2005) finds that the Amihud (2002) illiquidity measure best indicates the impact of volume on prices. Similar to Kyle's $\lambda$ adjustment to VaR, the Amihud(2002) adjustment can be applied as follows:
$$
VaR^{L} = VaR + \text{Liquidity Adjustment} = VaR - (\mu^{\gamma} + z_{\alpha}\sigma^{\gamma})
$$
, where $\mu^{\gamma}$ and $\sigma^{\gamma}$ are the mean and standard deviation of the Amihud(2002) illiquidity measure $\gamma$, $\gamma_{t} = \frac{1}{D} \sum_{d = 1}^{D_{t}} \frac{|r_{d,t}|}{v_{d,t}}$, $D_{t}$ is the number of trades executed during time period $t$, $r_{d,t}$ is the relative price change following trade $d$ during trade period $t$, and $r_{d,t}$ is the trade quantity executed within trade $d$.
