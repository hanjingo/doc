# CHAPTER 15 The Term Structure of Interest Rates

Practitioners commonly summarize the relationship between yield and maturity graphically in a `yield curve`, which is a plot of yield to maturity as a function of time to maturity.

Both `bond stripping` and `bond reconstitution` offer opportunities for arbitrage--the exploitation of mispricing among two or more securities to clear a riskless economic profit. Any violation of the Law of One Price, that identical cash flow bundles must sell for identical prices, gives rise to arbitrage opportunities.

To distinguish between yields on long-term bonds versus short-term rates that will be available in the future, practitioners use the following terminology. They call the yield to maturity on zero-coupon bonds the `spot rate`, meaning the rate that prevails `today` for a time period corresponding to the zero's maturity. In contrast, the `short rate` for a given time interval (e.g., 1 year) refers to the interest rate for that interval available at different points in time.

The following equation generalizes our approach to inferring a future short rate from the yield curve of zero-coupon bonds. It equates the total return on two $n$-year investment strategies: buying and holding an $n$-year zero-coupon bond versus buying an $(n - 1)$-year zero and rolling over the proceeds into a 1-year bond:
$$
(1 + y_{n})^{n} = (1 + y_{n - 1})^{n - 1} \times (1 + r_{n})
$$
, where $n$ denotes the period in question, and $y_{n}$ is the yield to maturity of a zero-coupon bond with an $n$-period maturity. Given the observed yield curve, we can solve above equation for the short rate in the last period:
$$
(1 + r_{n}) = \frac{(1 + y_{n})^n}{(1 + y_{n - 1})^{n - 1}}
$$
, the numerator on the right-hand side is the total growth factor of an investment in an $n$-year zero held until maturity. Similarly, the denominator is the growth factor of an investment in an $(n - 1)$-year zero. Because the former investment lasts for one more year than the latter, the difference in these growth factors must be the rate of return available in year $n$ when the $(n-1)$-year zero can be rolled over into a 1-year investment.

If the forward rate for period $n$ is denoted $f_{n}$, we then define $f_{n}$ by the equation:
$$
(1 + f_{n}) = \frac{(1 + y_{n})^{n}}{(1 + y_{n - 1})^{n - 1}}
$$
, equivalently, we may rewrite above equation as:
$$
(1 + y_{n})^{n} = (1 + y_{n - 1})^{n - 1}(1 + f_{n})
$$
, in this formulation, the forward rate is `defined` as the "break-even" interest rate that equates the return on an $n$-period zero-coupon bond to that of an $(n - 1)$-period zero-coupon bond rolled over into a 1-year bond in year $n$. The actual total returns on the two $n$-year strategies will be equal if the short interest rate in year $n$ turns out to equal $f_{n}$.

In a certain world, different investment strategies with common terminal dates must provide equal rates of return. Therefore, under certainty:
$$
(1 + r_{1})(1 + r_{2}) = (1 + y_{2})^{2}
$$
We have seen that under certainty, 1 plus the yield to maturity on a zero-coupon bond is simply the geometric average of 1 plus the future short rates taht will prevail over the life of teh bond. We give in general form here:
$$
1 + y_{n} = [(1 + r_{1})(1 + r_{2})...(1 + r_{n})]^{1/n}
$$
, when future rates are uncertain, we using short rates with forward rates:
$$
1 + y_{n} = [(1 + r_{1})(1 + f_{2})(1 + f_{3})...(1 + f_{n})]^{1/n}
$$
, thus there is a direct relationship between yields on various maturity bonds and forward interest rates.

Recall that the forward rate can be related to the expected future short rate according to this equation:
$$
f_{n} = E(r_{n}) + \text{Liquidity premium}
$$
, where the liquidity premium might be necessary to induce investors to hold bonds of maturities that do not correspond to their preferred investment horizons.

The nominal interest rate is composed of the real rate plus a factor to compensate for the effect of inflation:
$$
1 + \text{Nominal rate} = (1 + \text{Real rate})(1 + \text{Inflation rate})
$$
, or, approximately:
$$
\text{Nominal rate} \approx \text{Real rate} + \text{Inflation rate}
$$
