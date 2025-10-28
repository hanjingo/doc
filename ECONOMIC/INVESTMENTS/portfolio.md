# Portfolio

This note consolidates capital-allocation principles and optimal-portfolio ideas into a single, practical reference. It explains how investors allocate capital across asset classes, construct efficient portfolios, and manage risk through rebalancing and position sizing. The note emphasizes actionable methods (mean-variance optimization, risk budgeting, practical constraints) and highlights common pitfalls and mitigations.

## Why allocation and optimal portfolios matter
Allocation determines exposures to return drivers and risk factors. Portfolio construction formalizes the trade-off between expected return and risk and provides tools to design portfolios aligned with objectives, horizon, and constraints.

## Strategic vs tactical allocation
- Strategic Asset Allocation (SAA): a long-term target mix across major asset classes determined by objectives, liabilities, and risk tolerance. SAA changes infrequently.
- Tactical Asset Allocation (TAA): short- to medium-term deviations from SAA to capture temporary opportunities or to manage risk. TAA should be disciplined and constrained.

Define SAA first; then layer TAA, active bets, and hedges on top with clear rules and budgets.

## Mean-variance optimization and the efficient frontier

Mean-variance optimization (MVO) constructs portfolios that trade off expected return and variance. For expected returns vector \mu and covariance matrix \Sigma, portfolio expected return and variance are:

$$
E[R_p] = w^T \mu,
$$

$$
\mathrm{Var}(R_p) = w^T \Sigma w.
$$

The efficient frontier is the set of portfolios minimizing variance for a given expected return. Common targets:

- Global minimum-variance (GMV): minimize w^T \Sigma w subject to 1^T w = 1 and (optionally) w >= 0.
- Mean-variance with target return: minimize w^T \Sigma w subject to w^T \mu = R_target and 1^T w = 1.

Numerical quadratic programming solves constrained problems; Black-Litterman and regularization improve stability when inputs are noisy.

## Risk budgeting and risk parity

Risk budgeting allocates the portfolio's risk budget across assets. The volatility contribution (risk contribution) of asset i is:

$$
RC_i = w_i (\Sigma w)_i,
$$

and risk parity sets RC_i approximately equal across assets. Risk parity is useful when expected-return estimates are unreliable but covariance structure is informative.

## Kelly, leverage, and sizing active bets

The Kelly criterion maximizes expected long-run growth (log-utility). In multiple-asset form, Kelly-optimal weights are proportional to \Sigma^{-1}\mu (excess returns). Because Kelly can imply leverage and large drawdowns, fractional Kelly is commonly used in practice.

Be aware: Kelly is highly sensitive to estimation error in \mu and assumes stationary returns.

## Constraints, frictions, and realistic implementation

- Practical constraints include no-short rules, leverage caps, liquidity limits, and minimum lot sizes.
- Include transaction costs, taxes, and market impact in optimization or as explicit penalties.
- Use robust techniques (shrinkage, Black-Litterman, regularization) to avoid extreme or unstable allocations.

## Estimation improvements and robustness

1. Ledoit-Wolf and other shrinkage estimators improve covariance estimates.
2. Factor models reduce dimensionality and stabilize out-of-sample behavior.
3. Black-Litterman blends market equilibrium with investor views to produce stable expected-return inputs.
4. Regularization (L1/L2) and turnover penalties produce more robust weights.

## Rebalancing and monitoring

Common rebalancing policies:

- Calendar-based: periodic rebalancing (monthly/quarterly/yearly).
- Threshold-based: rebalance when weights drift beyond a defined band.
- Cost-aware: rebalance only when expected benefits exceed transaction costs.

Monitor risk factors, concentration, turnover, tracking error, and attribution; maintain governance for TAA and active positions.

## Worked example (two-asset mean-variance)

Assets A and B with expected returns \mu_A, \mu_B, volatilities \sigma_A, \sigma_B and correlation \rho. Portfolio variance with weight w in A is:

$$
\mathrm{Var}(R_p) = w^2\sigma_A^2 + (1-w)^2\sigma_B^2 + 2w(1-w)\rho\sigma_A\sigma_B.
$$

Solve first-order conditions or use numeric solvers to obtain efficient weights; extend to multi-asset problems with quadratic programming.

## Implementation checklist and practical tips

1. Set objectives: return targets, acceptable drawdown, liquidity and regulatory constraints.
2. Define SAA and rebalancing rules.
3. Select optimization framework and apply regularization or Black-Litterman when using MVO.
4. Use robust covariance estimators or factor models for \Sigma.
5. Incorporate transaction costs and penalties for turnover.
6. Backtest, stress-test, and examine out-of-sample sensitivity to inputs.
7. Document assumptions and maintain change governance.

## Common metrics (quick reference)

- Expected return: $E[R_p] = w^T\mu$.
- Volatility: $\sigma_p = \sqrt{w^T\Sigma w}$.
- Beta: exposure to a benchmark, $\beta = \mathrm{Cov}(R_p,R_b)/\mathrm{Var}(R_b)$.
- Sharpe ratio: $(E[R_p]-R_f)/\sigma_p$.

## Final notes

Combining capital allocation and optimal-portfolio methods gives a structured approach to portfolio construction. Prefer simple, robust allocations and explicit constraints over fragile, unconstrained optimizations. Validate out-of-sample, use risk budgeting and rebalancing to manage realized risk, and document assumptions clearly.

---

References: Markowitz (portfolio selection), Black & Litterman (1992), Ledoit & Wolf on covariance shrinkage, Grinold & Kahn on active portfolio management.
# Portfolio construction and capital allocation — Overview

This note consolidates capital-allocation principles and optimal-portfolio ideas into a single, practical reference. It explains how investors allocate capital across asset classes, construct efficient portfolios, and manage risk through rebalancing and position sizing. The note emphasizes actionable methods (mean-variance optimization, risk budgeting, practical constraints) and highlights common pitfalls and mitigations.

## Why allocation and optimal portfolios matter
Allocation determines exposures to return drivers and risk factors. Portfolio construction formalizes the trade-off between expected return and risk and provides tools to design portfolios aligned with objectives, horizon, and constraints.

## Strategic vs tactical allocation
- Strategic Asset Allocation (SAA): a long-term target mix across major asset classes determined by objectives, liabilities, and risk tolerance. SAA changes infrequently.
- Tactical Asset Allocation (TAA): short- to medium-term deviations from SAA to capture temporary opportunities or to manage risk. TAA should be disciplined and constrained.

Define SAA first; then layer TAA, active bets, and hedges on top with clear rules and budgets.

## Mean-variance optimization and the efficient frontier

Mean-variance optimization (MVO) constructs portfolios that trade off expected return and variance. For expected returns vector \mu and covariance matrix \Sigma, portfolio expected return and variance are:

$$
E[R_p] = w^T \mu,
$$

$$
\mathrm{Var}(R_p) = w^T \Sigma w.
$$

The efficient frontier is the set of portfolios minimizing variance for a given expected return. Common targets:

- Global minimum-variance (GMV): minimize w^T \Sigma w subject to 1^T w = 1 and (optionally) w >= 0.
- Mean-variance with target return: minimize w^T \Sigma w subject to w^T \mu = R_target and 1^T w = 1.

Numerical quadratic programming solves constrained problems; Black-Litterman and regularization improve stability when inputs are noisy.

## Risk budgeting and risk parity

Risk budgeting allocates the portfolio's risk budget across assets. The volatility contribution (risk contribution) of asset i is:

$$
RC_i = w_i (\Sigma w)_i,
$$

and risk parity sets RC_i approximately equal across assets. Risk parity is useful when expected-return estimates are unreliable but covariance structure is informative.

## Kelly, leverage, and sizing active bets

The Kelly criterion maximizes expected long-run growth (log-utility). In multiple-asset form, Kelly-optimal weights are proportional to \Sigma^{-1}\mu (excess returns). Because Kelly can imply leverage and large drawdowns, fractional Kelly is commonly used in practice.

Be aware: Kelly is highly sensitive to estimation error in \mu and assumes stationary returns.

## Constraints, frictions, and realistic implementation

- Practical constraints include no-short rules, leverage caps, liquidity limits, and minimum lot sizes.
- Include transaction costs, taxes, and market impact in optimization or as explicit penalties.
- Use robust techniques (shrinkage, Black-Litterman, regularization) to avoid extreme or unstable allocations.

## Estimation improvements and robustness

1. Ledoit-Wolf and other shrinkage estimators improve covariance estimates.
2. Factor models reduce dimensionality and stabilize out-of-sample behavior.
3. Black-Litterman blends market equilibrium with investor views to produce stable expected-return inputs.
4. Regularization (L1/L2) and turnover penalties produce more robust weights.

## Rebalancing and monitoring

Common rebalancing policies:

- Calendar-based: periodic rebalancing (monthly/quarterly/yearly).
- Threshold-based: rebalance when weights drift beyond a defined band.
- Cost-aware: rebalance only when expected benefits exceed transaction costs.

Monitor risk factors, concentration, turnover, tracking error, and attribution; maintain governance for TAA and active positions.

## Worked example (two-asset mean-variance)

Assets A and B with expected returns \mu_A, \mu_B, volatilities \sigma_A, \sigma_B and correlation \rho. Portfolio variance with weight w in A is:

$$
\mathrm{Var}(R_p) = w^2\sigma_A^2 + (1-w)^2\sigma_B^2 + 2w(1-w)\rho\sigma_A\sigma_B.
$$

Solve first-order conditions or use numeric solvers to obtain efficient weights; extend to multi-asset problems with quadratic programming.

## Implementation checklist and practical tips

1. Set objectives: return targets, acceptable drawdown, liquidity and regulatory constraints.
2. Define SAA and rebalancing rules.
3. Select optimization framework and apply regularization or Black-Litterman when using MVO.
4. Use robust covariance estimators or factor models for \Sigma.
5. Incorporate transaction costs and penalties for turnover.
6. Backtest, stress-test, and examine out-of-sample sensitivity to inputs.
7. Document assumptions and maintain change governance.

## Common metrics (quick reference)

- Expected return: $E[R_p] = w^T\mu$.
- Volatility: $\sigma_p = \sqrt{w^T\Sigma w}$.
- Beta: exposure to a benchmark, $\beta = \mathrm{Cov}(R_p,R_b)/\mathrm{Var}(R_b)$.
- Sharpe ratio: $(E[R_p]-R_f)/\sigma_p$.

## Final notes

Combining capital allocation and optimal-portfolio methods gives a structured approach to portfolio construction. Prefer simple, robust allocations and explicit constraints over fragile, unconstrained optimizations. Validate out-of-sample, use risk budgeting and rebalancing to manage realized risk, and document assumptions clearly.

---

References: Markowitz (portfolio selection), Black & Litterman (1992), Ledoit & Wolf on covariance shrinkage, Grinold & Kahn on active portfolio management.

# Portfolio construction and capital allocation — Overview

This note combines capital-allocation principles with optimal portfolio ideas. It summarizes how investors allocate capital across asset classes and construct portfolios that balance expected return and risk. The note covers strategic and tactical allocation, mean-variance optimization and the efficient frontier, risk budgeting (risk parity), practical constraints, rebalancing, and concrete implementation tips.

## Why allocation and optimal portfolios matter
Allocation determines exposures to return drivers and risk factors. Optimal portfolio theory formalizes the trade-off between expected return and risk and provides tools to construct portfolios that suit an investor's objectives, horizon, and constraints.

## Strategic vs tactical allocation
- Strategic Asset Allocation (SAA): long-term target mix across major asset classes chosen to meet long-term objectives and liability profiles.
- Tactical Asset Allocation (TAA): temporary deviations from SAA to capture short- to medium-term opportunities or to manage risk.

Define SAA first, then layer rules for TAA and for active/hedging positions.

## Mean-variance optimization and the efficient frontier

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

## Risk budgeting and risk parity

Risk parity allocates portfolio risk (volatility contributions) across assets rather than capital. If each asset's volatility contribution equals

$$
RC_i = w_i (\Sigma w)_i
$$

then risk parity sets RC_i equal across assets. This often increases allocations to low-volatility assets (bonds) compared to equal-capital portfolios and can produce lower leverage for a given volatility target when combined with risk-free borrowing/lending.

Risk budgeting is attractive when expected-return estimates are unreliable but covariance structure is trusted.

## Kelly, leverage, and sizing active bets

The Kelly criterion maximizes expected log growth and yields an aggressive sizing rule. In vector form the Kelly-optimal weights (for excess returns \mu over the risk-free rate) are proportional to \Sigma^{-1}\mu. Because Kelly often implies leverage and large drawdowns, practitioners commonly use fractional Kelly (e.g., 0.5×Kelly) to reduce risk.

Kelly is highly sensitive to \mu estimation error and assumes stationarity — use with caution.

## Incorporating constraints and realistic frictions

- No-short constraints, leverage limits, liquidity constraints, and minimum/maximum lot sizes are common.
- Transaction costs and taxes should be modeled or penalized in optimization.
- Robust optimization and Black-Litterman help stabilize allocations by shrinking extreme weights.

## Estimation improvements and robustness

1. Shrinkage estimators for \Sigma (Ledoit-Wolf) reduce estimation error.
2. Factor models (e.g., using a small number of common factors) reduce dimensionality and improve out-of-sample stability.
3. Black-Litterman blends market-implied (equilibrium) returns with investor views to create more stable \mu inputs.
4. Regularization (L2, L1) penalizes extreme weights and turnover.

## Rebalancing and monitoring

Rebalancing policies preserve SAA or risk budgets. Typical approaches:

- Calendar-based: periodic (monthly/quarterly/yearly).
- Threshold-based: rebalance when weights drift beyond a band.
- Cost-aware: only rebalance when expected benefit exceeds estimated transaction costs.

Maintain monitoring: risk exposures, concentration (top holdings), turnover, realized tracking error, and performance attribution.

## Worked example (two-asset mean-variance)

Assets A and B with expected returns \mu_A, \mu_B, volatilities \sigma_A, \sigma_B and correlation \rho. Portfolio variance for weight w in A is

$$
\mathrm{Var}(R_p) = w^2\sigma_A^2 + (1-w)^2\sigma_B^2 + 2w(1-w)\rho\sigma_A\sigma_B.
$$

The efficient weight for minimizing variance (GMV with two assets, unconstrained) can be computed from first-order conditions; in larger problems numerical solvers are used.

## Implementation checklist and practical tips

1. Start with clear objectives: return targets, acceptable drawdown, liquidity, and regulatory constraints.
2. Choose a baseline SAA and a rebalancing policy.
3. Select an optimization framework and apply regularization or Black-Litterman if using MVO.
4. Use robust covariance estimators or factor models for \Sigma.
5. Incorporate transaction costs and implement turnover penalties.
6. Backtest and stress test; examine out-of-sample performance and sensitivity to inputs.
7. Document assumptions and maintain a governance process for making changes.

## Common metrics (quick reference)

- Expected return: $E[R_p] = w^T\mu$.
- Volatility: $\sigma_p = \sqrt{w^T\Sigma w}$.
- Beta: exposure to a benchmark, $\beta = \mathrm{Cov}(R_p,R_b)/\mathrm{Var}(R_b)$.
- Sharpe ratio: $(E[R_p]-R_f)/\sigma_p$.

## Final notes

Combining capital allocation and optimal-portfolio methods gives a structured approach to portfolio construction. In practice, prefer simple, robust allocations and explicit constraints over fragile, unconstrained optimizations. Always validate out-of-sample and use position sizing (risk budgeting) and rebalancing to control realized risk.

---

Further reading: Markowitz (portfolio selection), Black & Litterman (1992), Ledoit & Wolf on covariance shrinkage, and Grinold & Kahn on active portfolio management.
# Capital Allocation — Overview

This note summarizes practical principles for capital allocation: how investors decide where to put capital across asset classes, strategies to allocate risk and capital, and pragmatic techniques for portfolio construction and rebalancing. It highlights both strategic (long-term) and tactical (short-term) allocation, risk budgeting, simple rules (e.g., Kelly), and common constraints that affect real-world decisions.

# Why capital allocation matters
Capital allocation determines an investor's exposures to different sources of return and risk. The allocation decision drives expected return, volatility, drawdown behavior, liquidity profile, and tax/transaction outcomes. Good allocation matches objectives (return target, risk tolerance), horizon, and constraints.

# Portfolio construction and capital allocation — Overview

This concise note explains how investors allocate capital across asset classes and construct portfolios that balance expected return and risk. It covers strategic and tactical allocation, mean-variance optimization, risk budgeting (risk parity), practical implementation, rebalancing, and robust estimation techniques.

## Why allocation and optimal portfolios matter
Allocation determines exposures to return drivers and risk factors. Portfolio construction formalizes trade-offs between expected return and risk and helps align portfolios with investor objectives, horizon, and constraints.

## Strategic vs tactical allocation
- Strategic Asset Allocation (SAA): long-term target mix across major asset classes based on objectives and liabilities.
- Tactical Asset Allocation (TAA): short- to medium-term deviations from SAA to capture opportunities or manage risk. Keep TAA disciplined and budgeted.

## Mean-variance optimization & efficient frontier
For expected return vector \mu and covariance matrix \Sigma, portfolio return and variance are:

$$
E[R_p]=w^T\mu,
$$

$$
\mathrm{Var}(R_p)=w^T\Sigma w.
$$

The efficient frontier contains portfolios minimizing variance for each target return. Common targets: global minimum-variance (GMV) and mean-variance portfolios with a target return. Use Black-Litterman and regularization to reduce sensitivity to noisy inputs.

## Risk budgeting and risk parity
Risk contributions:

$$
RC_i = w_i (\Sigma w)_i
$$

Risk parity equalizes these contributions across assets and is useful when returns are hard to estimate but covariances are informative.

## Kelly, leverage, and sizing active bets
The Kelly criterion maximizes expected log growth; multi-asset Kelly weights are proportional to \Sigma^{-1}\mu. Kelly can be aggressive; practitioners often use fractional Kelly to control drawdowns.

## Constraints, frictions, and robustness
- Model common constraints (no-shorting, leverage caps, liquidity limits). 
- Include transaction costs and tax considerations in decisions.
- Use shrinkage (Ledoit-Wolf), factor models, Black-Litterman, and regularization to improve out-of-sample stability.

## Rebalancing and monitoring
- Calendar-based, threshold-based, or cost-aware rebalancing rules.
- Monitor concentration, turnover, tracking error, and risk exposures; maintain governance for changes.

## Worked example (two-asset)
For two assets A and B, weight w in A gives portfolio variance:

$$
\mathrm{Var}(R_p)=w^2\sigma_A^2+(1-w)^2\sigma_B^2+2w(1-w)\rho\sigma_A\sigma_B.
$$

Solve analytically for small problems or use quadratic programming for larger universes.

## Implementation checklist
1. Define objectives and constraints.
2. Set SAA and rebalancing rules.
3. Choose optimization framework and regularization.
4. Use robust covariance estimation or factor models.
5. Account for transaction costs and turnover.
6. Backtest and stress-test; validate out-of-sample.
7. Document assumptions and governance.

## Quick metrics
- Expected return: $E[R_p]=w^T\mu$.
- Volatility: $\sigma_p=\sqrt{w^T\Sigma w}$.
- Sharpe: $(E[R_p]-R_f)/\sigma_p$.

## Final note
Prefer simple, robust allocations with explicit constraints. Validate models out-of-sample, use risk budgeting and rebalancing to manage realized risk, and keep assumptions transparent.

---

References: Markowitz (1952), Black & Litterman (1992), Ledoit & Wolf (2003), Grinold & Kahn.