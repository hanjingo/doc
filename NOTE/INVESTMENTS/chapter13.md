# CHAPTER 13 Empirical Evidence on Security Returns



If the expected return-beta relationship holds with respect to an observable exante efficient index, $M$, the expected rate of return on any security $i$ is:
$$
E(r_i) = r_f + \beta_i[E(r_M) - r_f]
$$
, where $\beta_i$ is defined as $Cov(r_i, r_M)/\sigma^{2}_{M}$. This is the most commonly tested implication of the CAPM. Early simple tests followed three basic steps:

- **Setting Up the Sample Data** Determine a sample period of.

- **Estimating the SCL** For each stock, $i$, you estimate the beta coefficient as the slope of a `first-pass regression` equation. (The terminology `first-pass` regression is due to the fact that the estimated coefficients will be used as input into a `second-pass regression`.)
  $$
  r_{it} - r_{ft} = a_{i} + b_{i}(r_{Mt} - r_{ft}) + e_{it}
  $$

- **Estimating the SML** You can estimate $\gamma_{0}$ and $\gamma_1$ in the following second-pass regression equation with the estimates $b_i$ from the first pass as the independent variable:
  $$
  \overline{r_i - r_f} = \gamma_{0} + \gamma_{1}b_{i} \qquad i = 1, ..., 1000
  $$
  , Compare equation $E(r_i) = r_f + \beta_i[E(r_M) - r_f]$ and $\overline{r_i - r_f} = \gamma_{0} + \gamma_{1}b_{i} \qquad i = 1, ..., 1000$; you should conclude that if the CAPM is valid, then $\gamma_{0}$ and $\gamma_{1}$ should satisfy:
  $$
  \gamma_{0} = 0 \text{ and } \gamma_{1} = \overline{r_M - r_f}
  $$
  , In fact, however, you can go a step further and argue that the key property of the expected return-beta relationship described by the SML is that the expected excess return on securities is determined only by the systematic risk (as measured by beta) and should be independent of the nonsystematic risk, as measured by the variance of the residuals, $\sigma^{2}(e_i)$, which also were estimated from the first-pass regression. These estimates can be added as a variable in equation $\overline{r_i - r_f} = \gamma_{0} + \gamma_{1}b_{i} \qquad i = 1, ..., 1000$ of an expanded SML that now looks like this:
  $$
  \overline{r_i - r_f} = \gamma_{0} + \gamma_{1}b_{i} + \gamma_{2}\sigma^{2}(e_i)
  $$
  , This `second-pass` regression equation is estimated with the hypotheses:
  $$
  \gamma_{0} = 0; \gamma_{1} = \overline{r_{M} - r_{f}}; \gamma_{2} = 0
  $$
  , The hypothesis that $\gamma_{2} = 0$ is consistent with the notion that nonsystematic risk should not be "priced", that is, that there is no risk premium earned for bearing nonsystematic risk. More generally, according to the CAPM, the risk premium depends only on beta. Therefore, any additional right-hand-side variable in equation $\overline{r_i - r_f} = \gamma_{0} + \gamma_{1}b_{i} + \gamma_{2}\sigma^{2}(e_i)$ beyond beta should have a coefficient that is insignificantly different from zero in the second-pass regression.

**The Market Index** In what has come to be known as `Roll's critique`, Richard Roll pointed out that:

1. There is a single testable hypothesis associated with CAPM: The market portfolio is mean-variance efficient.
2. All the other implications of the model, the best-known being the linear relation between expected return and beta, follow from the market portfolio's efficiency and therefore are not independently testable. There is an "if and only if" relation between the expected return-beta relationship and the efficiency of the market portfolio.
3. In any sample of observations of individual returns there will be an infinite number of ex post (i.e., after the fact) mean-variance efficient portfolios using the sample period returns and covariances (as opposed to the ex ante `expected` returns and covariances). Sample betas of individual assets estimated against each such ex-post efficient portfolio will be exactly linearly related to the sample average returns of these assets. In other words, if betas are calculated against such portfolios, they will satisfy the SML relation exactly whether or not the true market portfolio is meanvariance efficient in an ex ante sense.
4. The CAPM is not testable unless we know the exact composition of the true market portfolio and use it in the tests. This implies that the theory is not testable unless all individual assets are included in the sample.
5. Using a proxy such as the S&P 500 for the market portfolio is subject to two difficulties. First, the proxy itself might be mean-variance efficient even when the true market portfolio is not. Conversely, the proxy may turn out to be inefficient, but obviously this alone implies nothing about the true market portfolio's efficiency. Furthermore, most reasonable market proxies will be very highly correlated with each other and with the true market portfolio whether or not they are mean-variance efficient. Such a high degree of correlation will make it seem that the exact composition of the market portfolio is unimportant, whereas the use of different proxies can lead to quite different conclusions. This problem is referred to as `benchmark error`, because it refers to the use of an incorrect benchmark (market proxy) portfolio in the tests of the theory.

Kandel and Stambaugh considered the properties of the usual two-pass test of the CAPM in an environment in which borrowing is restricted but the zero-beta version of the CAPM holds. In this case, you will recall that the expected return-beta relationship describes the expected returns on a stock, a portfolio $E$ on the efficient frontier, and that portfolio's zero-beta companion, $Z$:
$$
E(r_{i}) - E(r_{Z}) = \beta_{i}[E(r_{E} - E(r_{Z})]
$$
 , where $\beta_{i}$ denotes the beta of security $i$ on efficient portfolio $E$. We cannot construct or observe the efficient portfolio $E$ (because we do not know expected returns and covariances of all assets), and so we cannot estimate above equation directly. Kandel and Stambaugh asked what would happen if we followed the common procedure of using a market proxy portfolio $M$ in place of $E$, and used as well the more efficient generalized least squares regression procedure in estimating the second-pass regression for the zero-beta version of the CAPM, that is:
$$
r_{i} - r_{Z} = \gamma_{0} + \gamma_{1} \times (Estimated\ \beta_{i})
$$
, they shouwed that the estimated values of $\gamma_{0}$ and $\gamma_{1}$ will be biased by a term proportional to the relative efficiency of the market proxy.

For a sequence of many subperiods, they estimated for each subperiod the equation:
$$
r_{i} = \gamma_{0} + \gamma_{1}\beta_{i} + \gamma_{2}\beta_{i}^2 + \gamma_{3}\sigma(e_{i})
$$
, the term $\gamma_2$ measures potential nonlinearity of return, and $\gamma_{3}$ measures the explanatory power of nonsystematic risk, $\sigma(e_{i})$. According to the CAPM, both $\gamma_{2}$ and $\gamma_{3}$ should have coefficients of zero in the second-pass regression.

Jagannathan and Wang used the rate of change in aggregate labor income as a proxy for changes in the value of human capital. In addition to the standard security betas estimated using the value-weighted stock market index, which we denote $\beta^{vw}$, they also estimated the betas of assets with respect to labor income growth, which we denote $\beta^{labor}$. Finally, they considered the possibility that business cycles affect asset betas, an issue that has been examined in a number of other studies. These may be viewed as `conditional` betas, as their values are conditional on the state of the economy. Jagannathan and Wang used the spread between the yields on low- and high-grade corporate bonds as a proxy for the state of the business cycle and estimate asset betas relative to this business cycle variable; we denote this beta as $\beta^{prem}$. With the estimates of these three betas for several stock portfolios, Jagannathan and Wang estimated a second-pass regression which includes firm size (market value of equity, denoted ME):
$$
E(R_{i}) = c_{0} + c_{size}log(ME) + c_{vw}\beta^{vw} + c_{prem}\beta^{prem} + c_{labor}\beta^{labor}
$$
**Early Versions of the Multifactor CAPM and APT** The multifactor CAPM and APT are elegant theories of how exposure to systematic risk factors should influence expected returns, but they provide little guidance concerning which factors (sources of risk) ought to result in risk premiums. A test of this hypothesis would require three stages:

1. Specification fo risk factors.
2. Identification of portfolios that hedge these fundamental risk factors.
3. Test of the explanatory power and risk premiums of the hedge portfolios.

**A Macro Factor Model** Chen, Roll, and Ross identify several possible variables that might proxy for systematic factors:

IP = Growth rate in industrial production.

EI = Changes in expected inflation measured by changes in short-term (T-bill) interest rates.

UI = Unexpected inflation defined as the difference between actual and expected inflation.

CG = Unexpected changes in risk premiums measured by the difference between the returns on corporate Baa-rated bonds and long-term government bonds.

GB = Unexpected changes in the term premium measured by the difference between the returns on long- and short-term government bonds.

The returns on the Big and Small portfolio are:
$$
R_{S} = \frac{1}{3}(R_{S/L} + R_{S/M} + R_{S/H}); R_{B} = \frac{1}{3}(R_{B/L} + R_{B/M} + R_{B/H})
$$
, similarly, the returns on the high and low (Value and Growth) portfolios are:
$$
R_{H} = \frac{1}{2}(R_{SH} + R_{BH}); R_{L} = \frac{1}{2}(R_{SL} + R_{BL})
$$
, the returns of the zero-net-investment factors SMB (Small minus Big, i.e., Long Small and Short Big), and HTML (High minus Low, i.e., Long High B/M and Short Low B/M) are created from these portfolios:
$$
R_{SMB} = R_{S} - R_{B}; R_{HML} = R_{H} - R_{L}
$$
, we measure the sensitivity of individual stocks to the factors by estimating the factor betas from first-pass regressions of stock excess returns on the excess return of the market index as well as on $R_{SMB}$ and $R_{HML}$. These factor betas should, as a group, predict the total risk premium. Therefore, the Fama-French three-factor asset-pricing model is:
$$
E(r_{i}) - r_{f} = a_{i} + b_{i}[E(r_{M}) - r_{f}] + s_{i}E[SMB] + h_{i}E[HML]
$$
, the coefficients $b_i$, $s_i$, and $h_i$ are the betas (also called loadings in this context) of the stock on the three factors. If these are the only risk factors, excess returns on all assets should be fully explained by risk premiums due to these factor loadings. In other words, if these factors fully explain asset returns, the intercept of the equation should be zero.

Petkova and Zhang attempt to fit both beta and the market risk premium to a set of "state variables", that is, variables that summarize the state of the economy. There are:

DIV = Market dividend yield.

DEFLT = Default spread on corporate bonds (Baa-Aaa rates).

TERM = Term structure spread (10-year-1-year Treasury rates).

TB = 1-month T-bill rate.

, they estimate a first-pass regression, but first substitute these state variables for beta as follows:
$$
r_{HML} &= \alpha + \beta r_{Mt} + e_{i} \\
&= \alpha + [\underbrace{b_{0} + b_{1}DIV_{t} + b_{2}DEFLT_{t} + b_{3}TERM_{t} + b_{4}TB_{t}}_{\beta_{t} \leftarrow \text{a time-varying beta}}]r_{Mt} + e_{i}
$$
, the strategy is to estimate parameters $b_{0}$ through $b_4$ and then fit beta using the values of the four state variables at each data. In this way, they can estimate beta in each period.

Similarly, one can directly estimate the determinants of a time-varying market risk premium, using the same set of state variables:
$$
r_{Mkt, t} - r_{ft} = c_{0} + c_{1}DIV_{t} + c_{2}DEFLT_{t} + c_{3}TERM_{t} + c_{4}TB_{t} + e_{t}
$$
, the fitted value from this regression is the estimate of the market risk premium.

The effect of liqudity on an asset's expected return is composed of two factors:

1. Transaction costs that are dominated by the bid-ask spread that dealers set to compensate for losses incurred when trading with informed traders.
2. Liquidity `risk` resulting from covariance between `changes` in asset liquidity cost with both `changes` in market-index liquidity cost and with market-index rates of return.

Another measure of illiquidity, proposed by Amihud, also focuses on the association between large trades and price movements. His measure is:
$$
\text{ILLIQ} = \text{Monthly average of daily} \left[\frac{\text{Absolute value(Stock return)}}{\text{Dollar volume}} \right]
$$
, this measure of illiquidity is based on the price impact per dollar of transactions in the stock and can be used to estimate both liquidity cost and liquidity risk.

The risk premium of the market index to be related to that covariance as follows:
$$
E(r_{M}) - r_{f} = ACov(r_{M}, r_{C})
$$
, where $A$ depends on the average coefficient of risk aversion and $r_{C}$ is the rate of return on a consumption-tracking portfolio constructed to have the highest possible correlation with growth in aggregate consumption.

The expected total return on the firm's stock will be the sum of dividend yield (dividend/price) plus the expected dividend growth rate, $g$:
$$
E(r) = \frac{D_{1}}{P_{0}} + g
$$
, where $D_{1}$ is end-of-year dividends and $P_{0}$ is the current price of the stock.
