# CHAPTER 10 Arbitrage Pricing Theory and Multifactor Models of Risk and Return



Formally, the `single-factor model` of excess return is described by equation:
$$
R_i = E(R_i) + \beta_i F + e_i
$$
, where $E(R_i)$ is the expected excess return on stock $i$.

We can write a two-factor model describing the excess return on stock $i$ in some time period as follows:
$$
E_i = E(R_i) + \beta_{iGDP}GDP + \beta_{iIR}IR + e_i
$$
Stephen Ross developed the `arbitrage pricing theory` (APT) in 1976. Like the CAPM, the APT predicts a security market line linking expected returns to risk, but the path it takes to the SML is quite different. Ross's APT relies on three key propositions:

1. security returns can be described by a factor model;
2. there are sufficient securities to diversify away idiosyncratic risk;
3. well-functioning security markets do not allow for the persistence of arbitrage opportunities.

An `arbitrage` opportunity arises when an investor can earn riskless profits without making a net investment.

The `Law of One Price` states that if two assets are equivalent in all economically relevant respects, then they should have the same market price.

Arbitrageur often refers to a professional searching for mispriced securities in specific areas such as merger-target stocks, rather than to one who seeks (risk-free) arbitrage opportunities. Such activity is sometimes calles `risk arbitrage` to distinguish it from pure arbitrage.

The excess return on an $n$-stock portfolio with weights $w_i, \sum_{w_i} = 1$, is:
$$
R_P = E(R_P) + \beta_{P}F + e_P
$$
, where:
$$
\beta_{P} = \sum w_i \beta_i; \quad E(R_P) = \sum w_i E(R_i)
$$
, are the weighted averages of the $\beta_i$ and risk premiums of the $n$ securities. The portfolio nonsystematic component (which is uncorrelated with $F$) is $e_P = \sum w_i e_i$, which similarly is a weighted average of the $e_i$ of the $n$ securities.

The excess return on any security is given by $R_i = \alpha_i + \beta_i R_M + e_i$, and that of a well-diversified (therefore zero residual) portfolio, $P$, is:
$$
R_P = \alpha_P + \beta_P R_M \\
E(R_P) = \alpha_P + \beta_P E(R_M)
$$
We can eliminate the risk of $P$ altogether: Construct a zero-beta portfolio, called $Z$, from $P$ and $M$ by appropriately selecting weights $w_P$ and $w_M = 1 - w_P$ on each portfolio:
$$
\beta_Z = w_P \beta_P + (1 - w_P)\beta_M = 0 \\
\beta_M = 1 \\
w_P = \frac{1}{1 - \beta_P}; w_M = 1 - w_P = \frac{-\beta_P}{1 - \beta_P}
$$
, therefore, portfolio $Z$ is riskless, and its alpha is:
$$
\alpha_Z = w_P \alpha_P + (1 - w_P)\alpha_M = w_P \alpha_P
$$
, The risk premium on $Z$ must be zero because the risk of $Z$ is zero. If its risk premium were not zero, you could earn arbitrage profits. Here is how:

, Since the beta of $Z$ is zero, Equation $E(R_P) = \alpha_P + \beta_P E(R_M)$ implies that its risk premium is just its alpha. Using Equation $\alpha_Z = w_P \alpha_P + (1 - w_P)\alpha_M = w_P \alpha_P$, its alpha is $w_P \alpha_P$, so
$$
E(R_Z) = w_P \alpha_P = \frac{1}{1 - \beta_P} \alpha_P
$$
, You now form a zero-net-investment arbitrage portfolio: If $\beta_P < 1$ and the risk premium of $Z$ is positive (implying that $Z$ returns more than the risk-free rate), borrow and invest the proceeds in $Z$. For every borrowed dollar invested in $Z$, you get a net return (i.e., net of paying the interest on your loan) of $\frac{1}{1 - \beta_{P}} \alpha_P$. This is a money machine, which you would work as hard as you can. Similarly if $\beta_P > 1$, Equation $E(R_Z) = w_P \alpha_P = \frac{1}{1 - \beta_P} \alpha_P$ tells us that the risk premium is negative; therefore, sell $Z$ short and invest the proceeds at the risk-free rate. Once again, a money machine has been created.

Setting the expression in Equation $E(R_Z) = w_P \alpha_P = \frac{1}{1 - \beta_P} \alpha_P$ to zero implies that the alpha of `any` well-diversified portfolio must also be zero. From Equation $E(R_P) = \alpha_P + \beta_P E(R_M)$, this means that for any well-diversified $P$,
$$
E(R_P) = \beta_P E(R_M)
$$
, In other words, the risk premium (expected excess return) on portfolio $P$ is the product of its beta and the market-index risk premium.

`factor portfolio`, which is a well-diversified portfolio constructed to have a beta of 1 on one of the factors and a beta of zero on any other factor.
