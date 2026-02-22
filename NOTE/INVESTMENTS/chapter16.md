# CHAPTER 16 Managing Bond Portfolios

the determinants of interest rate risk:

1. Bond prices and yields are inversely related: as yields increase, bond prices fall; as yields fall, bond prices rise.
2. An increase in a bond's yield to maturity results in a smaller price change than a decrease in yield of equal magnitude.
3. Prices of long-term bonds tend to be more sensitive to interest rate changes than prices of short-term bonds.
4. The sensitivity of bond prices to changes in yields increases at a decreasing rate as maturity increases. In other words, interest rate risk is less than proportional to bond maturity.
5. Interest rate risk is inversely related to the bond's coupon rate. Prices of low-coupon bonds are more sensitive to changes in interest rates than prices of high-coupon bonds.
6. The sensitivity of a bond's price to a change in its yield is inversely related to the yield to maturity at which the bond currently is selling.

`Macaulay's duration` equals the weighted average of the times to each coupon on principal payment. The weight associated with each payment time clearly should be related to the "importance" of that payment to the value of the bond. In fact, the weight applied to each payment time is the proportion of the total value of the bond accounted for by that payment, that is, the present value of the payment divided by the bond price. We define the weight, $w_{t}$, associated with the cash flow made at time $t$ (denoted $CF_{t}$) as:
$$
w_{t} = \frac{CF_{t}/(1 + y)^{t}}{\text{Bond price}}
$$
, where $y$ is the bond's yield to maturity. The numerator on the right-hand side of this equation is the present value of the cash flow occurring at time $t$ while the denominator is the value of all the bond's payments. These weights sum to 1.0 because the sum of the cash flows discounted at the yield to maturity equals the bond price. Using these values to calculate the weighted average of the times until the receipt of each of the bond's payments, we obtain Macaulay's duration formula:
$$
D = \sum_{t = 1}^{T}t \times w_{t}
$$
Specifically, it can be shown that when interest rates change, the proportional change in a bond's price can be related to the change in its yield to maturity, $y$, according to the rule:
$$
\frac{\Delta P}{P} = -D \times \left[\frac{\Delta(1 + y)}{1 + y}\right]
$$
, the proportional price change equals the proportional change in 1 plus the bond's yield times the bond's duration. Practitioners commonly use above equation in a slightly different form. They define `modified duration` as $D^{*} = D/(1 + y)$, note that $\Delta(1 + y) = \Delta y$, and rewrite above equation as:
$$
\frac{\Delta P}{P} = -D^{*} \Delta y
$$
, the percentage change in bond price is just the product of modified duration and the change in the bond's yield to maturity.

Where durations of bonds of various coupon rates, yields to maturity, and times to maturity are plotted:

- **Rule 1 for Duration** The duration of a zero-coupon bond equals it time to maturity.

- **Rule 2 for Duration** Holding maturity constant, a bond's duration is lower when the coupon rate is higher.

- **Rule 3 for Duration** Holding the coupon rate constant, a bond's duration generally increases with its time to maturity. Duration always increases with maturity for bonds selling at par or at a premium to par.

- **Rule 4 for Duration** Holding other factors constant, the duration of a coupon bond is higher when the bond's yield to maturity is lower.

- **Rule 5 for Duration** The duration of a level perpetuity is:
  $$
  \text{Duration of perpetuity} = \frac{1 + y}{y}
  $$

The percentage change in the value of a bond approximately equals the product of modified duration times the change in the bond's yield:
$$
\frac{\Delta P}{P} = -D^{*}\Delta y
$$
, this equation asserts that the percentage price change is directly proportional to the change in the bond's yield.

Convexity allows us to improve the duration approximation for bond price changes. Accounting for convexity, the equation:
$$
\frac{\Delta P}{P} = -D^{*} \Delta y + 1/2 \times Convexity \times (\Delta y)^{2}
$$
The convention on Wall Street is to compute the `effective duration` of bonds with embedded options. More complex bond valuation approaches that account for the embedded options are used, and effective duration is `defined` as the proportional change in the bond price per unit change in market interest rates:
$$
\text{Effective duration} = -\frac{\Delta P / P}{\Delta r}
$$
The net worth of the firm or the ability to meet future obligations fluctuates with interest rates. `Immunization` techniques refer to strategies used by such investors to shield their overall financial status from interest rate risk.

The importance of `rebalancing` immunized portfolios. As interest rates and asset durations change, a manager must rebalance the portfolio to realign its duration with the duration of the obligation. Moreover, even if interest rates do not change, asset durations will change solely because of the passage of time.

Homer and Liebowitz coined a popular taxonomy of active bond portfolio strategies. They characterize portfolio rebalancing activities as one of four types of `bond swaps`:

1. The `substitution swap` is an exhange of one bond for a nearly identical substitute. The substituted bonds should be of essentially equal coupon, maturity, quality, call features, sinking fund provisions, and so on. This swap would be motivated by a belief that the market has temporarily mispriced the two bonds, and that the discrepancy between the prices of the bonds represents a profit opportunity.
2. The `intermarket spread swap` is pursued when an investor believes that the yield spread between two sectors of the bond market is temporarily out of line.
3. The `rate anticipation swap` is pegged to interest rate forecasting. In this case if investors believe that rates will fall, they will swap into bonds of longer duration. Conversely, when rates are expected to rise, they will swap into shorter duration bonds.
4. The `pure yield pickup swap` is pursued not in response to perceived mispricing, but as a means of increasing return by holding higher-yield bonds. When the yield curve is upward-sloping, the yield pickup swap entails moving into longer-term bonds. This must be viewed as an attempt to earn an expected term premium in higher-yield bonds. The investor is willing to bear the interest rate risk that this strategy entails. The investor who swaps the shorter-term bond for the longer one will earn a higher rate of return as long as the yield curve does not shift up during the holding period. Of course if it does, the longer-duration bond will suffer a greater capital loss.
