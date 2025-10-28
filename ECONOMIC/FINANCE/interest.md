# Interest — Practical Reference

[TOC]

This note summarizes the core concepts and practical formulas for interest and discounting used across finance: simple and compound interest, effective and nominal rates, continuous compounding, present and future value, discount factors, yield measures (spot, forward, and yield-to-maturity), and a short discussion of the term structure and bootstrapping. Examples and brief numerical calculations are included to illustrate the mechanics.

## Basic concepts

- Principal (P): the initial amount of money.
- Interest rate (r): the rate of return per period (expressed as a decimal, e.g., 5% = 0.05).
- Time (t): number of periods (years, months, etc.).

Two elementary conventions:
- Simple interest (rare in modern markets except for some short-term instruments):

  Future value: $FV = P(1 + r t)$

- Compound interest (standard): interest accrues on previously earned interest. For discrete compounding with $m$ compounding periods per year and nominal annual rate $r_{nom}$:

  Period rate: $r_p = r_{nom}/m$.

  After $n$ total periods (or $t$ years, $n = m t$):

  $FV = P(1 + r_p)^{n} = P\left(1 + \frac{r_{nom}}{m}\right)^{m t}$.

Effective annual rate (EAR): the actual annual growth rate with compounding:

  $EAR = \left(1 + \frac{r_{nom}}{m}\right)^{m} - 1$.

As $m\to\infty$ (continuous compounding) the limit is $e^{r} - 1$ when $r$ is the continuously compounded annual rate.

## Continuous compounding

With continuous compounding at rate $r$ (annual),

  $FV = P e^{r t}$,

and the present value is

  $PV = P e^{-r t}$.

Continuous compounding simplifies many analytical formulas and is commonly used in mathematical finance.

## Discounting and present value

Discounting converts future cash flows into present value using an appropriate discount rate. For discrete compounding,

  $PV = \dfrac{FV}{(1 + r_p)^{n}}$,

and for continuous compounding,

  $PV = FV\,e^{-r t}$.

Discount factors are often written as $DF(t) = e^{-r(t) t}$ (continuous) or $DF(t) = (1 + r_p)^{-n}$ (discrete). Many pricing models express cash flows multiplied by discount factors to compute present value.

## Yields and rates: spot, forward, and yield-to-maturity (YTM)

- Spot rate $r(0,t)$: the zero-coupon yield for maturity $t$ (annualized). The price of a zero-coupon bond paying 1 at time $t$ is $P(0,t)=DF(t)=e^{-r(0,t) t}$ (if continuous compounding).
- Forward rate $f(t_1,t_2)$: implied future short rate between $t_1$ and $t_2$ derived from spot rates. Under continuous compounding,

  $f(t_1,t_2) = \frac{r(0,t_2) t_2 - r(0,t_1) t_1}{t_2 - t_1}$.

- Yield-to-maturity (YTM): internal rate of return that sets the present value of cash flows equal to price; commonly used for coupon-bearing bonds. For a coupon bond with cash flows $C_i$ at times $t_i$ and price $P$ find $y$ solving

  $P = \sum_i C_i (1 + y)^{-t_i}$ (discrete) or using continuous compounding versions.

When markets quote yields they may use different conventions (ACT/360, ACT/365, semiannual compounding, etc.), so always confirm the convention when comparing rates.

## Term structure and bootstrapping

The term structure (yield curve) displays spot rates $r(0,t)$ across maturities. Bootstrapping constructs spot rates from observed market prices of coupon bonds by solving for zero rates that match prices sequentially from short to long maturities.

Key practical points:
- Short-term rates are often set by money market instruments (deposits, FRAs, T-bills).
- Longer-term zero rates can be bootstrapped from coupon-bearing bond prices or swap rates.

## Converting between conventions

- From continuously compounded rate $r_c$ to effective rate over period $t$: $1 + r_{eff} = e^{r_c t}$.
- From nominal rate $r_{nom}$ with $m$ compounding to continuous rate $r_c$: $r_c = m \ln\left(1 + \frac{r_{nom}}{m}\right)$.

Always be explicit about compounding frequency when reporting or using rates.

## Simple numerical examples

1) Discrete compounding:

   P = 1000, r_{nom} = 6\% annually, compounded monthly (m=12), t=2 years.

   $FV = 1000\left(1 + \frac{0.06}{12}\right)^{24} \approx 1000 \times 1.12749 = 1127.49$.

2) Continuous compounding:

   P = 1000, r = 6\% (continuous), t=2 → $FV = 1000 e^{0.06 \times 2} \approx 1000 \times 1.1275 = 1127.50$ (close to monthly compounding at this rate).

3) Present value of $1000$ payable in 3 years at continuous rate 4\%:

   $PV = 1000 e^{-0.04 \times 3} \approx 1000 \times 0.88692 = 886.92$.

## Applications and practical notes

- Bond pricing: discount each coupon and principal by appropriate zero rates and sum.
- Swap pricing: use par swap rates and bootstrapped zero curve to value fixed and floating legs.
- Risk management: small changes in rates (DV01, duration) measure sensitivity of PV to yield shifts.
- Rate conventions: money-market instruments may use ACT/360, bonds ACT/365 or ACT/365F, swaps often use ACT/360 for money market leg — confirm convention before computing.

## Common mistakes to avoid

- Mixing compounding conventions (comparing a nominal semiannual quote to a continuously compounded rate directly).
- Forgetting day-count conventions that affect accrual and interest amounts.
- Imprecise quoting: ensure whether quoted rates are nominal or effective and the compounding frequency.

## Further reading

- Basic textbooks: Hull — Options, Futures, and Other Derivatives (interest-rate basics); Baxter & Rennie — Financial Calculus; Introductory mathematical finance notes in `INTRODUCTION_TO_THE_MATHEMATICS_OF_FINANCE`.
- Practical references: fixed income textbooks and market convention guides from major exchanges.