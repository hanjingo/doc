# Statistical Arbitrage (StatArb)

[TOC]

This note summarizes practical concepts and implementation notes for statistical arbitrage (StatArb). It explains the core idea (exploiting short-term mispricings using statistical relationships), common strategies (pairs trading and mean-reversion spread trading), model building (cointegration, spread modeling, Kalman filters), signal construction, execution considerations, risk management, and backtesting caveats. The content is aimed at a practitioner who wants a compact, actionable reference.

## What is statistical arbitrage?
Statistical arbitrage refers to trading strategies that exploit temporary price deviations from a statistical relationship between assets. Unlike pure arbitrage (riskless, guaranteed profit), StatArb accepts model risk and execution risk: profits come from mean reversion of a modeled spread or from persistent statistical edges after accounting for costs.

Core components:
- A relationship between assets (pair or basket) that is expected to be stable or mean-reverting.
- A model to estimate the relationship and to compute a tradeable spread or signal.
- Entry/exit rules and position sizing.
- Execution and slippage control, and robust risk limits.

## Common strategies

- Pairs trading: find two assets whose spread (price difference or a linear combination) is stationary; go long the underpriced asset and short the overpriced asset when the spread is wide, and exit when it reverts.
- Portfolio/statistical baskets: generalize pairs to more than two assets using factor or cointegration-based baskets (e.g., via PCA, factor models, or Johansen cointegration).
- Mean-reversion on residuals: regress one asset on others and trade the residual if it is mean-reverting.

## Modeling the spread

1) Simple price ratio / log-price difference

For assets $P1_t$ and $P2_t$, common spread forms are:

- price difference: $s_t = P1_t - \beta P2_t$
- log-price spread: $s_t = \log(P1_t) - \beta \log(P2_t)$

where $\beta$ may be 1 (for ratio/difference) or estimated by regression.

2) Ordinary Least Squares (OLS)

- Regress P1 on P2 (or log-prices) to obtain β_hat and compute residuals: r_t = P1_t - β_hat P2_t. Test residuals for stationarity (ADF test). If residuals are stationary, r_t is a candidate tradeable spread.

3) Cointegration (Engle–Granger, Johansen)

- Engle–Granger two-step: regress and test residuals for unit root. Johansen handles multiple time series and finds cointegrating vectors for higher-dimensional baskets.

4) State-space / time-varying models (Kalman filter)

- When relationships drift, fit a time-varying β_t using a Kalman filter. This helps adapt to slow structural changes and reduces look‑ahead bias in rolling estimation.

5) Factor models and PCA

- Use factor decomposition or PCA to identify common drivers; trade spreads orthogonal to dominant factors or construct market-neutral exposures.

## Signal construction

- Standardize the spread into a z-score: z_t = (s_t - μ_s)/σ_s using a rolling mean and standard deviation or exponentially weighted estimates.
- Entry/exit rules (typical):
  - Enter long spread when z_t < -z_entry and short when z_t > z_entry (e.g., z_entry = 2).
  - Exit when z_t crosses zero or reaches a smaller exit threshold z_exit (e.g., 0.5).
  - Use time-based exits to avoid lingering positions if reversion fails.

## Position sizing and risk controls

- Size positions by volatility parity or dollar-neutral rules. For pairs, a common rule is to choose weights so that the position is beta-neutral or risk-balanced: w = (1/σ) normalized across legs.
- Apply stop-loss limits (absolute loss or drawdown on a trade), maximum holding time, and maximum portfolio-level exposure.
- Monitor correlation breakdowns: if the historical correlation or cointegration relationship weakens (p-value rises, residual variance jumps), reduce or stop trading the pair.

## Execution, costs, and market impact

- Include realistic transaction costs (commissions, bid-ask spread) and market impact in backtests. Small gross edges can disappear after costs.
- Use limit orders or smart execution to reduce slippage; but be mindful of fill probabilities and latency.
- Avoid overcrowded signals that rely on the same short-term microstructure inefficiency.

## Backtesting and evaluation

- Use walk-forward testing and strict out-of-sample evaluation. Avoid look-ahead bias and parameter overfitting.
- Account for overlapping trades and autocorrelation when computing performance statistics (use non-overlapping bootstrap or proper time-series-aware metrics).
- Evaluate key metrics: annualized return, volatility, Sharpe ratio (use robust estimators), maximum drawdown, hit rate, average trade length, and turnover.

## Worked numeric example (simple pairs trade)

Assume two stocks with log-prices x_t and y_t. Fit OLS for a static hedge ratio β_hat by regressing x on y over a lookback window. Compute spread s_t = x_t - β_hat y_t and z-score z_t using rolling mean and std (lookback L).

If z_t > 2 → short spread (short x, long β_hat×y)
If z_t < -2 → long spread (long x, short β_hat×y)

This toy example can be implemented in Python with numpy/pandas/statsmodels (snippet below).

```python
import numpy as np
import pandas as pd
import statsmodels.api as sm

# price series: pandas Series log-prices x, y
L = 250  # lookback
beta = None
signals = pd.Series(index=x.index, dtype=float)

for t in range(L, len(x)):
    X = sm.add_constant(y.iloc[t-L:t])
    res = sm.OLS(x.iloc[t-L:t], X).fit()
    beta = res.params[1]
    spread = x.iloc[t] - beta * y.iloc[t]
    win = slice(t-L, t)
    mu = (x[win] - beta * y[win]).mean()
    sigma = (x[win] - beta * y[win]).std()
    z = (spread - mu) / sigma
    if z > 2:
        signals.iloc[t] = -1  # short spread
    elif z < -2:
        signals.iloc[t] = 1   # long spread
    else:
        signals.iloc[t] = 0

# signals contains discrete trade signals; turn into positions and simulate P&L with costs
```

Notes: this is a minimal example; in production, use rolling/online estimation (Kalman), include transaction costs, slippage models, and robust stats tests before trading.

## Common pitfalls and mitigations

- Overfitting: use parsimonious models, cross-validation and out-of-sample testing.
- Regime shifts: prefer adaptive models (EWMA, Kalman) and stop trading when residual variance increases sharply.
- Survivorship bias: use raw historical datasets including delistings.
- Data snooping / multiple testing: adjust significance for multiple hypotheses or use penalty for transaction frequency.

## Implementation checklist

1. Data: obtain clean, survivorship-free price series; align timestamps and handle corporate actions.
2. Pair selection: screen for candidates by low residual variance, high mean-reversion speed, and economic sense.
3. Modeling: test stationarity (ADF), estimate hedge ratios, and prefer regularized/time-varying fits.
4. Signals: define z-score rules, thresholds, and time/stop exits.
5. Sizing: set position sizes by volatility/risk parity and apply portfolio limits.
6. Execution: model costs, choose execution tactics, and monitor slippage.
7. Backtest: walk-forward, out-of-sample, stress tests (market crashes), and sensitivity to parameters.
8. Monitoring: live-track residual variance, correlation, turnover, P&L attribution, and drawdowns.

## References and further reading

- Gatev, Goetzmann & Rouwenhorst (2006) — Pairs Trading: Performance of a Relative-Value Arbitrage Rule
- Engle & Granger (1987) — Cointegration and Error Correction: Representation, Estimation, and Testing
- Campbell, Lo & MacKinlay — The Econometrics of Financial Markets (chapters on cointegration and pairs)
- Papers on Kalman-filter pairs and time-varying hedge ratios

---

This note is intended as a concise practitioner reference; if you want, I can add a longer Python notebook with: (a) data ingestion and cleaning, (b) automated pair screening, (c) rolling estimation with Kalman filter, and (d) a complete backtest including realistic costs. Let me know whether to (1) keep this concise, (2) add a numeric worked notebook, or (3) include a short Kalman example inline.
