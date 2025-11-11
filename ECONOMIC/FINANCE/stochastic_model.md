# Stochastic Models in Finance

## Introduction

Stochastic models are fundamental tools in modern financial mathematics, enabling the modeling and analysis of uncertainty in interest rates, asset prices, and investment returns. By treating key financial variables as random processes, these models provide a rigorous framework for pricing, risk management, and strategic decision-making in uncertain environments. This document summarizes the main stochastic models used in finance, including random interest rate models, the Capital Asset Pricing Model (CAPM), and option pricing models.

## 1. Random Interest Rate Models

### 1.1 Basic Approaches

Interest rates in the real world are not constant—they fluctuate due to economic, political, and market factors. Stochastic interest rate models treat the interest rate as a random variable or process. Common approaches include:

1. **Single Random Variable:** All spot rates for different maturities are represented by a single random annual rate $i$.
2. **Independent Random Rates:** The annual rate at each period $i_t$ is modeled as an independent random variable.
3. **Time Series Models:** Interest rates at different times are dependent, modeled using time series (e.g., AR(1), AR(2)).
4. **Continuous-Time Models:** The force of interest $\delta_t$ is modeled as a stochastic process.

### 1.2 No Term Structure (Single Random Rate)

If $i$ is a random annual effective rate, the equivalent deterministic rate $r$ satisfies:
$$
E\left(\frac{1}{1+i}\right) = \frac{1}{1+r}
$$
By Jensen's inequality:
$$
r \leq E(i)
$$

### 1.3 Independent Random Rates

Suppose $\{i_t\}$ are independent and identically distributed (i.i.d.) with $E(i_t) = i$.

- **Zero-Coupon Bond Future Value:**
  $$
  a(n) = \prod_{t=1}^n (1 + i_t)
  $$
  $$
  E[a(n)] = (1 + i)^n
  $$
  $$
  D[a(n)] = (1 + j)^n - (1 + i)^{2n},\quad j = 2i + i^2 + s^2,\ s^2 = D(i_t)
  $$

- **Zero-Coupon Bond Present Value:**
  $$
  a^{-1}(n) = \left[\prod_{t=1}^n (1 + i_t)\right]^{-1}
  $$
  $$
  E[a^{-1}(n)] = (1 + r)^{-n}
  $$
  $$
  D[a^{-1}(n)] = (1 + k)^{-n} - (1 + r)^{-2n},\quad (1 + k)^{-1} = E[(1 + i_t)^{-2}]
  $$

- **Annuity Present Value:**
  $$
  E(a_{\overline{n}|}) = a_{\overline{n}|i}
  $$
  $$
  D(a_{\overline{n}|}) = \frac{m_2^a + m_1^a}{m_2^a - m_1^a} a_{\overline{n}|j} - \frac{2m_2^a}{m_2^a - m_1^a} a_{\overline{n}|i} - (a_{\overline{n}|i})^2
  $$
  where $m_1^a = E[(1 + i_t)^{-1}]$, $m_2^a = E[(1 + i_t)^{-2}]$.

### 1.4 Dependent Rates: Time Series Models

- **First-Order Difference Model:**
  $$
  i_t - i = k(i_{t-1} - i)
  $$
- **AR(1) Model for Force of Interest:**
  $$
  \delta_t - \delta = k(\delta_{t-1} - \delta) + e(t)
  $$
  where $e(t) \sim N(0, \sigma^2)$, $|k| < 1$.
- **AR(2) Model:**
  $$
  \delta_t - \delta = k_1(\delta_{t-1} - \delta) + k_2(\delta_{t-2} - \delta) + e(t)
  $$

### 1.5 Discrete-Time Single-Factor Models

The binomial tree model assumes the short rate can move up or down each period with certain probabilities. The Ho-Lee model is a classic example:
$$
r_{t+1}^u = r_t(1+\gamma),\quad r_{t+1}^d = r_t(1+\gamma)^{-1}
$$
where $\gamma$ is the proportional change in rate.

### 1.6 Continuous-Time Single-Factor Models

A general continuous-time model for the short rate $r(t)$:
$$
dr(t) = k(\theta - r(t))dt + \sigma \sqrt{r(t)} dZ_1(t)
$$
where $Z_1(t)$ is a Wiener process (Brownian motion).

The Heath-Jarrow-Morton (HJM) model generalizes this to the entire forward rate curve:
$$
df(t, T) = \alpha(t, T)dt + \sigma(t, T)dZ_d(t)
$$

## 2. Capital Asset Pricing Model (CAPM)

The CAPM describes the relationship between expected return and risk for financial assets:
$$
E(r_k) = r_f + \beta_k [E(r_p) - r_f]
$$
where:
- $E(r_k)$: expected return of asset $k$
- $r_f$: risk-free rate
- $E(r_p)$: expected return of the market portfolio
- $\beta_k = \frac{Cov(r_k, r_p)}{Var(r_p)}$: beta coefficient (systematic risk)

The CAPM is used to estimate required returns, price risky assets, and assess risk.

## 3. Option Pricing Models

Options are financial derivatives that give the holder the right, but not the obligation, to buy or sell an asset at a specified price. Their value depends on the stochastic behavior of the underlying asset.

### 3.1 Binomial Model

The binomial model assumes the asset price can move up or down in each period. The price of a European call option is:
$$
C = \frac{1}{(1 + i)^T} \sum_{t=0}^m {m \choose t} p^{m-t} (1-p)^t \max\{0, S(1+k)^{m-t} - E\}
$$
where $S$ is the current asset price, $E$ is the exercise price, $T$ is the time to maturity, $k$ is the up/down factor, and $p$ is the probability of an up move.

### 3.2 Black-Scholes Model

The Black-Scholes model assumes the asset price follows a geometric Brownian motion. The price of a European call option is:
$$
C = S N(d_1) - e^{-\delta T} E N(d_2)
$$
where:
$$
d_1 = \frac{\ln(S/E) + (\delta + \frac{1}{2}\sigma^2)T}{\sigma \sqrt{T}}\\
d_2 = d_1 - \sigma \sqrt{T}
$$
$N(\cdot)$ is the standard normal cumulative distribution function, $\delta$ is the risk-free rate, and $\sigma$ is the volatility.

The price of a European put option is:
$$
P = e^{-\delta T} E N(-d_2) - S N(-d_1)
$$

## Conclusion

Stochastic models are essential for understanding and managing financial uncertainty. They provide the mathematical foundation for pricing, risk management, and investment analysis in modern finance. Mastery of these models enables financial professionals to make informed decisions in the face of uncertainty and market volatility.
