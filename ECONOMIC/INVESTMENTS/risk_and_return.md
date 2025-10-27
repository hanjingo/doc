# Risk and Return — Overview

This note summarizes the core concepts linking risk and return in investments, explains common measures, and outlines how these ideas apply when building and evaluating portfolios. It is written for readers who know basic statistics (mean, variance, covariance) and want a concise, practical reference.

## Intro: why risk matters
Return is the compensation an investor receives for committing capital. Risk captures the uncertainty of that return. Rational investors expect higher expected returns for taking on additional risk, but not all risk is equally priced. Understanding how to measure, combine, and manage risk is central to investment decisions.

## Key distinctions
- Systematic (market) risk: risk factors that affect many assets simultaneously (e.g., economic cycles, interest-rate changes). Not easily eliminated by diversification. Typically priced in market equilibrium models.
- Idiosyncratic (specific) risk: firm- or asset-specific uncertainty (e.g., management decisions, litigation). Can be reduced via diversification and therefore is generally not priced.

## Basic measures

- Return: for a single period, return R = (P1 + D - P0) / P0, where P0 is initial price, P1 is ending price, and D is distributions (dividends, coupons).
- Expected return: the mean of returns. For discrete outcomes, E[R] = Σ p_i R_i.
- Variance and standard deviation: measures of dispersion around the mean. Variance Var(R) = E[(R - E[R])^2]; standard deviation σ = sqrt(Var(R)).

These are statistical measures — higher σ means greater uncertainty in realized returns.

## Portfolio-level formulas

For a portfolio of n assets with weights w = (w1, ..., wn) (sum of wi = 1), expected return and variance are:

$$
E[R_p] = \sum_{i=1}^n w_i E[R_i]
$$

$$
\mathrm{Var}(R_p) = w^T \Sigma w = \sum_{i=1}^n\sum_{j=1}^n w_i w_j \mathrm{Cov}(R_i, R_j)
$$

where Σ is the covariance matrix of asset returns. Note that portfolio variance depends on covariances: diversification reduces variance when assets are not perfectly positively correlated.

## A simple two-asset example

For assets A and B with weights w and (1-w), expected return:

$$
E[R_p] = w E[R_A] + (1-w) E[R_B]
$$

Variance:

$$
\mathrm{Var}(R_p) = w^2 \sigma_A^2 + (1-w)^2 \sigma_B^2 + 2w(1-w)\mathrm{Cov}(R_A,R_B).
$$

If Cov is low or negative, the portfolio variance can be much lower than a weighted average of individual variances.

## Risk-Adjusted Performance: Sharpe Ratio and others

- Sharpe Ratio: measures return per unit of total risk (standard deviation). For portfolio p and risk-free rate R_f:

$$
S_p = \frac{E[R_p] - R_f}{\sigma_p}
$$

Higher Sharpe indicates better risk-adjusted performance, but it depends on the chosen time horizon and on whether returns are normally distributed.

- Sortino Ratio: like Sharpe but uses downside deviation (focuses on harmful volatility).
- Information Ratio: measures excess return over a benchmark divided by tracking error (stdev of active returns).

## Capital Asset Pricing Model (CAPM) — expected return from market risk

CAPM decomposes total risk into market exposure (beta) and idiosyncratic risk. Under CAPM, the expected return of asset i is:

$$
E[R_i] = R_f + \beta_i (E[R_m] - R_f)
$$

where

$$\beta_i = \frac{\mathrm{Cov}(R_i, R_m)}{\mathrm{Var}(R_m)}$$

β measures sensitivity to the market portfolio R_m. CAPM implies only systematic risk (β) is priced; diversified investors are not compensated for idiosyncratic risk.

Limitations: CAPM relies on strong assumptions (single-period horizon, frictionless markets, homogeneous expectations). Empirically, other factors (size, value, momentum) explain returns better than CAPM alone.

## Efficient Diversification and the Efficient Frontier

Modern Portfolio Theory (MPT) shows that for a given level of risk (σ_p) an investor can choose a portfolio that maximizes expected return. The set of such optimal portfolios traces the efficient frontier. The global minimum-variance portfolio gives the smallest achievable variance; portfolios above it trade increased expected return for increased risk.

Computationally, efficient portfolios come from solving a quadratic optimization (minimize w^T Σ w subject to expected return constraint and sum(w)=1).

## Practical estimation: inputs and pitfalls

1. Estimating expected returns is noisy: sample means have high estimation error, and small errors can change optimal weights drastically.
2. Covariance estimation requires sufficient data; shrinkage estimators or factor models reduce estimation error.
3. Transaction costs, taxes, and constraints (e.g., no shorting) change the optimal solution and should be incorporated.
4. Out-of-sample testing is essential: in-sample optimization often overfits historical noise.

Practical tips:
- Use robust expected return estimates (e.g., blending historical mean with analyst views or implied returns).
- Regularize covariance estimates (shrinkage toward a structured target or use a factor model like a few principal components).
- Apply weight constraints or penalize turnover to avoid extreme allocations.

## Risk decomposition and diversification rules of thumb

- Diversify across uncorrelated risk drivers (sectors, geographies, asset classes).
- A well-diversified equity portfolio typically reduces idiosyncratic risk substantially once it contains dozens of broadly diversified holdings; the remaining risk is mainly systematic.
- Correlations increase in crises: so “diversified” portfolios can still suffer in market stress — consider stress tests and scenario analysis.

## Example: compute portfolio return and risk

Suppose two assets with E[R_A]=6%, E[R_B]=10%, σ_A=8%, σ_B=15%, correlation ρ=0.2. For w=0.6 in asset A:

- E[R_p] = 0.6×6% + 0.4×10% = 7.6%
- Covariance = ρ σ_A σ_B = 0.2×0.08×0.15 = 0.0024 (in decimals)
- Var(R_p) = (0.6)^2(0.08^2) + (0.4)^2(0.15^2) + 2×0.6×0.4×0.0024
- Compute σ_p = sqrt(Var(R_p)) — this gives the portfolio risk used in Sharpe and other ratios.

## From theory to practice: decision checklist

1. Define investment horizon and liquidity needs.
2. Estimate expected returns and covariances; document assumptions.
3. Build candidate portfolios using regularization and constraints.
4. Evaluate using out-of-sample backtests, scenario analysis, and stress tests.
5. Monitor and rebalance with attention to transaction costs and tax consequences.

## Common metrics and quick references

- Expected return: mean of returns.
- Volatility (σ): standard deviation of returns.
- Beta (β): systematic sensitivity to a chosen benchmark.
- Sharpe Ratio: (E[R] - R_f) / σ.
- Tracking error: stdev(R_p - R_b) for a benchmark b.

## Final notes

Risk and return are linked but not interchangeable. The goal of portfolio construction is to achieve desired exposures to priced risks while managing costs and estimation error. Keep models simple, validate out-of-sample, and complement quantitative tools with economic judgment.

---

References and further reading: classic sources include Markowitz (1952) on portfolio selection, Sharpe (1964) on the Sharpe ratio, and Fama & French on multifactor models.
