## Portfolio construction and capital allocation — Overview

This note combines capital-allocation principles with optimal portfolio ideas. It summarizes how investors allocate capital across asset classes and construct portfolios that balance expected return and risk. The note covers strategic and tactical allocation, mean-variance optimization and the efficient frontier, risk budgeting (risk parity), practical constraints, rebalancing, and concrete implementation tips.

### Why allocation and optimal portfolios matter
Allocation determines exposures to return drivers and risk factors. Optimal portfolio theory formalizes the trade-off between expected return and risk and provides tools to construct portfolios that suit an investor's objectives, horizon, and constraints.

### Strategic vs tactical allocation
- Strategic Asset Allocation (SAA): long-term target mix across major asset classes chosen to meet long-term objectives and liability profiles.
- Tactical Asset Allocation (TAA): temporary deviations from SAA to capture short- to medium-term opportunities or to manage risk.

Define SAA first, then layer rules for TAA and for active/hedging positions.

### Mean-variance optimization and the efficient frontier

Mean-variance optimization (MVO) is the canonical framework for constructing efficient portfolios. For asset returns with expected vector \mu and covariance matrix \Sigma, the portfolio expected return and variance for weights w (sum(w)=1) are:

$$
E[R_p] = w^T \mu
$$

$$
\mathrm{Var}(R_p) = w^T \Sigma w
$$

The efficient frontier is the set of portfolios that minimize variance for a given expected return (or equivalently maximize expected return for a given variance).

Two commonly used optimizations:

- Global minimum-variance (GMV): minimize w^T \Sigma w subject to sum(w)=1.
- Mean-variance with target return: minimize w^T \Sigma w subject to w^T \mu = R_target and sum(w)=1.

In practice, solutions use numerical quadratic programming; analytic forms exist when constraints are simple.

Practical caveats: MVO is sensitive to estimation error in \mu and \Sigma. Small changes in expected-return inputs can produce large changes in weights.

### Risk budgeting and risk parity

Risk parity allocates portfolio risk (volatility contributions) across assets rather than capital. If each asset's volatility contribution equals

$$
RC_i = w_i (\Sigma w)_i
$$

then risk parity sets RC_i equal across assets. This often increases allocations to low-volatility assets (bonds) compared to equal-capital portfolios and can produce lower leverage for a given volatility target when combined with risk-free borrowing/lending.

Risk budgeting is attractive when expected-return estimates are unreliable but covariance structure is trusted.

### Kelly, leverage, and sizing active bets

The Kelly criterion maximizes expected log growth and yields an aggressive sizing rule. In vector form the Kelly-optimal weights (for excess returns \mu over the risk-free rate) are proportional to \Sigma^{-1}\mu. Because Kelly often implies leverage and large drawdowns, practitioners commonly use fractional Kelly (e.g., 0.5×Kelly) to reduce risk.

Kelly is highly sensitive to \mu estimation error and assumes stationarity — use with caution.

### Incorporating constraints and realistic frictions

- No-short constraints, leverage limits, liquidity constraints, and minimum/maximum lot sizes are common.
- Transaction costs and taxes should be modeled or penalized in optimization.
- Robust optimization and Black-Litterman help stabilize allocations by shrinking extreme weights.

### Estimation improvements and robustness

1. Shrinkage estimators for \Sigma (Ledoit-Wolf) reduce estimation error.
2. Factor models (e.g., using a small number of common factors) reduce dimensionality and improve out-of-sample stability.
3. Black-Litterman blends market-implied (equilibrium) returns with investor views to create more stable \mu inputs.
4. Regularization (L2, L1) penalizes extreme weights and turnover.

### Rebalancing and monitoring

Rebalancing policies preserve SAA or risk budgets. Typical approaches:

- Calendar-based: periodic (monthly/quarterly/yearly).
- Threshold-based: rebalance when weights drift beyond a band.
- Cost-aware: only rebalance when expected benefit exceeds estimated transaction costs.

Maintain monitoring: risk exposures, concentration (top holdings), turnover, realized tracking error, and performance attribution.

### Worked example (two-asset mean-variance)

Assets A and B with expected returns \mu_A, \mu_B, volatilities \sigma_A, \sigma_B and correlation \rho. Portfolio variance for weight w in A is

$$
\mathrm{Var}(R_p) = w^2\sigma_A^2 + (1-w)^2\sigma_B^2 + 2w(1-w)\rho\sigma_A\sigma_B.
$$

The efficient weight for minimizing variance (GMV with two assets, unconstrained) can be computed from first-order conditions; in larger problems numerical solvers are used.

### Implementation checklist and practical tips

1. Start with clear objectives: return targets, acceptable drawdown, liquidity, and regulatory constraints.
2. Choose a baseline SAA and a rebalancing policy.
3. Select an optimization framework and apply regularization or Black-Litterman if using MVO.
4. Use robust covariance estimators or factor models for \Sigma.
5. Incorporate transaction costs and implement turnover penalties.
6. Backtest and stress test; examine out-of-sample performance and sensitivity to inputs.
7. Document assumptions and maintain a governance process for making changes.

### Common metrics (quick reference)

- Expected return: $E[R_p] = w^T\mu$.
- Volatility: $\sigma_p = \sqrt{w^T\Sigma w}$.
- Beta: exposure to a benchmark, $\beta = \mathrm{Cov}(R_p,R_b)/\mathrm{Var}(R_b)$.
- Sharpe ratio: $(E[R_p]-R_f)/\sigma_p$.

### Final notes

Combining capital allocation and optimal-portfolio methods gives a structured approach to portfolio construction. In practice, prefer simple, robust allocations and explicit constraints over fragile, unconstrained optimizations. Always validate out-of-sample and use position sizing (risk budgeting) and rebalancing to control realized risk.

---

Further reading: Markowitz (portfolio selection), Black & Litterman (1992), Ledoit & Wolf on covariance shrinkage, and Grinold & Kahn on active portfolio management.
## Portfolio construction and capital allocation — Overview

This note combines capital-allocation principles with optimal portfolio ideas. It summarizes how investors allocate capital across asset classes and construct portfolios that balance expected return and risk. The note covers strategic and tactical allocation, mean-variance optimization and the efficient frontier, risk budgeting (risk parity), practical constraints, rebalancing, and concrete implementation tips.

### Why allocation and optimal portfolios matter
Allocation determines exposures to return drivers and risk factors. Optimal portfolio theory formalizes the trade-off between expected return and risk and provides tools to construct portfolios that suit an investor's objectives, horizon, and constraints.

### Strategic vs tactical allocation
- Strategic Asset Allocation (SAA): long-term target mix across major asset classes chosen to meet long-term objectives and liability profiles.
- Tactical Asset Allocation (TAA): temporary deviations from SAA to capture short- to medium-term opportunities or to manage risk.

Define SAA first, then layer rules for TAA and for active/hedging positions.

### Mean-variance optimization and the efficient frontier

Mean-variance optimization (MVO) is the canonical framework for constructing efficient portfolios. For asset returns with expected vector \mu and covariance matrix \Sigma, the portfolio expected return and variance for weights w (sum(w)=1) are:

$$
E[R_p] = w^T \mu
$$

$$
\mathrm{Var}(R_p) = w^T \Sigma w
$$

The efficient frontier is the set of portfolios that minimize variance for a given expected return (or equivalently maximize expected return for a given variance).

Two commonly used optimizations:

- Global minimum-variance (GMV): minimize w^T \Sigma w subject to sum(w)=1.
- Mean-variance with target return: minimize w^T \Sigma w subject to w^T \mu = R_target and sum(w)=1.

In practice, solutions use numerical quadratic programming; analytic forms exist when constraints are simple.

Practical caveats: MVO is sensitive to estimation error in \mu and \Sigma. Small changes in expected-return inputs can produce large changes in weights.

### Risk budgeting and risk parity

Risk parity allocates portfolio risk (volatility contributions) across assets rather than capital. If each asset's volatility contribution equals

$$
RC_i = w_i (\Sigma w)_i
$$

then risk parity sets RC_i equal across assets. This often increases allocations to low-volatility assets (bonds) compared to equal-capital portfolios and can produce lower leverage for a given volatility target when combined with risk-free borrowing/lending.

Risk budgeting is attractive when expected-return estimates are unreliable but covariance structure is trusted.

### Kelly, leverage, and sizing active bets

The Kelly criterion maximizes expected log growth and yields an aggressive sizing rule. In vector form the Kelly-optimal weights (for excess returns \mu over the risk-free rate) are proportional to \Sigma^{-1}\mu. Because Kelly often implies leverage and large drawdowns, practitioners commonly use fractional Kelly (e.g., 0.5×Kelly) to reduce risk.

Kelly is highly sensitive to \mu estimation error and assumes stationarity — use with caution.

### Incorporating constraints and realistic frictions

- No-short constraints, leverage limits, liquidity constraints, and minimum/maximum lot sizes are common.
- Transaction costs and taxes should be modeled or penalized in optimization.
- Robust optimization and Black-Litterman help stabilize allocations by shrinking extreme weights.

### Estimation improvements and robustness

1. Shrinkage estimators for \Sigma (Ledoit-Wolf) reduce estimation error.
2. Factor models (e.g., using a small number of common factors) reduce dimensionality and improve out-of-sample stability.
3. Black-Litterman blends market-implied (equilibrium) returns with investor views to create more stable \mu inputs.
4. Regularization (L2, L1) penalizes extreme weights and turnover.

### Rebalancing and monitoring

Rebalancing policies preserve SAA or risk budgets. Typical approaches:

- Calendar-based: periodic (monthly/quarterly/yearly).
- Threshold-based: rebalance when weights drift beyond a band.
- Cost-aware: only rebalance when expected benefit exceeds estimated transaction costs.

Maintain monitoring: risk exposures, concentration (top holdings), turnover, realized tracking error, and performance attribution.

### Worked example (two-asset mean-variance)

Assets A and B with expected returns \mu_A, \mu_B, volatilities \sigma_A, \sigma_B and correlation \rho. Portfolio variance for weight w in A is

$$
\mathrm{Var}(R_p) = w^2\sigma_A^2 + (1-w)^2\sigma_B^2 + 2w(1-w)\rho\sigma_A\sigma_B.
$$

The efficient weight for minimizing variance (GMV with two assets, unconstrained) can be computed from first-order conditions; in larger problems numerical solvers are used.

### Implementation checklist and practical tips

1. Start with clear objectives: return targets, acceptable drawdown, liquidity, and regulatory constraints.
2. Choose a baseline SAA and a rebalancing policy.
3. Select an optimization framework and apply regularization or Black-Litterman if using MVO.
4. Use robust covariance estimators or factor models for \Sigma.
5. Incorporate transaction costs and implement turnover penalties.
6. Backtest and stress test; examine out-of-sample performance and sensitivity to inputs.
7. Document assumptions and maintain a governance process for making changes.

### Common metrics (quick reference)

- Expected return: $E[R_p] = w^T\mu$.
- Volatility: $\sigma_p = \sqrt{w^T\Sigma w}$.
- Beta: exposure to a benchmark, $\beta = \mathrm{Cov}(R_p,R_b)/\mathrm{Var}(R_b)$.
- Sharpe ratio: $(E[R_p]-R_f)/\sigma_p$.

### Final notes

Combining capital allocation and optimal-portfolio methods gives a structured approach to portfolio construction. In practice, prefer simple, robust allocations and explicit constraints over fragile, unconstrained optimizations. Always validate out-of-sample and use position sizing (risk budgeting) and rebalancing to control realized risk.

---

Further reading: Markowitz (portfolio selection), Black & Litterman (1992), Ledoit & Wolf on covariance shrinkage, and Grinold & Kahn on active portfolio management.
# Capital Allocation — Overview

This note summarizes practical principles for capital allocation: how investors decide where to put capital across asset classes, strategies to allocate risk and capital, and pragmatic techniques for portfolio construction and rebalancing. It highlights both strategic (long-term) and tactical (short-term) allocation, risk budgeting, simple rules (e.g., Kelly), and common constraints that affect real-world decisions.

## Why capital allocation matters
Capital allocation determines an investor's exposures to different sources of return and risk. The allocation decision drives expected return, volatility, drawdown behavior, liquidity profile, and tax/transaction outcomes. Good allocation matches objectives (return target, risk tolerance), horizon, and constraints.

## Strategic vs. tactical allocation
- Strategic Asset Allocation (SAA): a long-term target mix across major asset classes (e.g., equities, bonds, cash, real assets) based on investor objectives, liability profile, and return/risk expectations. SAA forms the backbone of a portfolio and changes infrequently.
- Tactical Asset Allocation (TAA): short- to medium-term deviations from the strategic weights to exploit expected temporary mispricings or to manage risk (for example, overweight equities when valuations are attractive). TAA should be used sparingly and with a clear edge.

Design tip: Define SAA first (objectives, constraints, glide paths), then layer TAA rules and risk management on top.

## Risk budgeting and allocation approaches

1. Risk-parity (risk budgeting): allocate risk (volatility contribution) rather than capital. In a simple risk-parity portfolio, each asset contributes equally to portfolio volatility. This often leads to higher weight in lower-volatility assets (e.g., bonds) compared to equal-capital weighting.

2. Mean-variance / utility-based allocation: choose weights w to maximize expected utility (or Sharpe ratio) given estimates of expected returns and covariances. This leads to the classical mean-variance solution where optimal weights are proportional to Σ^{-1}(E[R] - R_f 1).

3. Black-Litterman: blends investor views with equilibrium (market) implied returns to produce more stable expected-return inputs for mean-variance optimization.

4. Heuristics and rule-of-thumb allocations: target-date funds, 60/40 portfolios, age-based rules (e.g., equity allocation ~ 100 - age) — simple, easy to communicate, and often robust for retail investors.

## Kelly criterion and sizing aggressive bets

The Kelly rule (maximize long-run growth rate) gives a fraction to wager when odds and payoffs are known. For a simple single-bet model with edge g and odds b, Kelly fraction f* = g / b. In continuous returns and multiple assets, the Kelly-optimal portfolio maximizes expected log-utility and leads to weights proportional to Σ^{-1}µ (µ = vector of expected excess returns). Practical notes:

- Kelly can produce aggressive leverage and high turnover; many practitioners use fractional Kelly (e.g., half-Kelly) to reduce drawdown and estimation risk.
- Kelly assumes stationary return distributions and accurate inputs — both are strong assumptions in markets.

## Implementation: constraints, estimation, and robustness

- Constraints: regulatory limits, no-short rules, leverage caps, minimum holding sizes, and liquidity needs must be part of the allocation optimization.
- Estimation error: small errors in expected returns lead to large swings in mean-variance optimal weights. Use techniques to improve robustness: shrinkage, Black-Litterman, robust optimization (minimax regret), or simply rely more on covariance structure than on precise expected returns.
- Turnover and transaction costs: penalize turnover or include transaction cost models in the optimization objective.

## Rebalancing and drift management

Rebalancing maintains the portfolio near its strategic or target allocation. Common rules:

- Calendar rebalancing: monthly, quarterly, or yearly.
- Threshold rebalancing: rebalance when an asset's weight deviates by X% from target.
- Hybrid rules: check at intervals and rebalance only when drift exceeds thresholds.

Practical choice depends on transaction costs, tax considerations, and the expected benefit from rebalancing (selling winners and buying underperformers to capture mean reversion or maintain risk exposures).

## A simple capital-allocation example

Target SAA: 60% equities, 35% bonds, 5% cash. Suppose equities are volatile and have outperformed — equity weight drifts to 68%. If a threshold rebalancing rule is +/-5%, the portfolio would be rebalanced once equity weight exceeds 65%. Rebalancing restores target risk exposures and can lock in gains while controlling concentration risk.

## Combining allocation with risk management

- Use stress testing and scenario analysis to see portfolio behavior under extreme moves (e.g., market crash, rate shock).
- Consider tail-risk hedging strategies (put protection, tail risk funds) when drawdown protection is a high priority; note hedging costs reduce long-term returns if held continuously.
- Size active bets with a risk budget: decide how much volatility or tracking error you will allocate to active strategies versus baseline exposures.

## Practical checklist for allocating capital

1. Clarify objectives: target returns, acceptable drawdown, liquidity and regulatory constraints.
2. Define SAA and the rebalancing policy.
3. Choose estimation and optimization framework (heuristic, mean-variance with regularization, Black-Litterman, risk-parity).
4. Add practical constraints and transaction-cost models.
5. Backtest and stress test the allocation; examine turnover and tax impacts.
6. Document assumptions and triggers for tactical changes.

## Final notes

Capital allocation is a mix of art and science. Use simple, robust frameworks first. Be explicit about assumptions, and favor approaches that are stable out-of-sample. When in doubt, simpler allocations with disciplined rebalancing often outperform complex, over‑fitted strategies in practice.