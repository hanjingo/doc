# CHAPTER 18 Equity Valuation Models

 The intrinsic value of the share is the present value of the dividend to be received at the end of the first year, $D_{1}$, and the expected sales price, $P_{1}$. We will henceforth use the simpler notation $P_{1}$ instead of $E(P_{1})$ to avoid clutter. Keep in mind, though, that future prices and dividends are unknown, and we are dealing with expected values, not certain values. We've already established:
$$
V_{0} = \frac{D_{1} + P_{1}}{1 + k}
$$
, Although this year's dividends are fairly predictable given a company's history, you might ask how we can estimate $P_{1}$, the year-end price. According to above equation, $V_{1}$(the eyar-end intrinsic value) will be:
$$
V_{1} = \frac{D_{2} + P_{2}}{1 + k}
$$
, If we assume the stock will be selling for its intrinsic value next year, then $V_{1} = P_{1}$, and we can substitute this value for $P_{1}$ into above equation to find:
$$
V_{0} = \frac{D_{1}}{1 + k} + \frac{D_{2} + P_{2}}{(1 + k)^{2}}
$$
, this equation may be interpreted as the present value of dividends plus sales price for a 2-year holding period. Of course, now we need to come up with a forecast of $P_{2}$. Continuing in the same way, we can replace $P_{2}$ by $(D_{3} + P_{3})/(1 + k)$, which relates $P_{0}$ to the value of dividends plus the expected sales price for a 3-year holding period. More generally, for a holding period of $H$ years, we can write the stock value as teh present value of dividends over the $H$ years, plus the ultimate sale price, $P_{H}$:
$$
V_{0} = \frac{D_{1}}{1 + k} + \frac{D_{2}}{(1 + k)^{2}} + ... + \frac{D_{H} + P_{H}}{(1 + k)^{H}}
$$
, each relates price to the present value of a stream of payments (coupons in the case of bonds, dividends in the case of stocks) and a final payment (the face value of teh bond, or the sales price of the stock). The key differences in the case of stocks are the uncertainty of dividends, the lack of a fixed maturity date, and the unknown sales price at the horizon date. Indeed, one can continue to substitute for price indefinitely, to conclude:
$$
V_{0} = \frac{D_{1}}{1 + k} + \frac{D_{2}}{(1 + k)^{2}} + \frac{D_{3}}{(1 + k)^{3}} + ...
$$
, this equation states that the stock price should equal the present value of all expected future dividends into perpetuity. This formula is called the `dividend discount model (DDM)` of stock prices. Using dividend forecasts in above equation, we solve for intrinsic value as:
$$
V_{0} = \frac{D_{0}(1 + g)}{1 + k} + \frac{D_{0}(1 + g)^{2}}{(1 + k)^{2}} + \frac{D_{0}(1 + g)^{3}}{(1 + k)^{3}} + ...
$$
, this equation can be simplified to:
$$
V_{0} = \frac{D_{0}(1 + g)}{k - g} = \frac{D_{1}}{k - g}
$$
, note in above equation that we divide $D_{1}$ (not $D_{0}$) by $k - g$ to calculate intrinsic value. This equation is called the `constant-growth DDM`, or the Gordon model, after Myron J. Gordon, who popularized teh model. It should remind you of the formula for the present value of a perpetuity. If dividends were expected not to grow, then the dividend stream would be a simple perpetuity, and the valuation formula would be $V_{0} = D_{1} / k$. Above equation is a generalization of the perpetuity formula to cover the case of a `growing` perpetuity. As $g$ increases (for a given value of $D_{1}$), the stock price also rises.

The constant-growth rate DDM implies that a stock's value will be greater:

1. The larger its expected dividend per share.
2. The lower the market capitalization rate, $k$.
3. The higher the expected growth rate of dividends.

For a stock whose market price equals its intrinsic value $(V_{0} = P_{0})$, the expected holding-period return will be:
$$
\begin{equation}\begin{split}
E(r) &= \text{Dividend yield} + \text{Capital gains yield} \\
&= \frac{D_1}{P_0} + \frac{P_1 - P_0}{P_0} = \frac{D_1}{P_0} + g
\end{split}\end{equation}
$$
, this formula offers a means to infer the market capitalization rate of a stock, for if the stock is selling at its intrinsic value, then $E(r) = k$, implying that $k = D_{1} / P_{0} + g$. By observing the dividend yield, $D_{1} / P_{0}$, and estimating the growth rate of dividends, we can compute $k$. This equation is also known as the `discounted cash flow (DCF) formula`.

We can see how growth opportunities are reflected in P/E ratios with equation:
$$
\frac{P_{0}}{E_{1}} = \frac{1}{k} \left(1 + \frac{PVGO}{E/k}\right)
$$
, when $PVGO = 0$, above equation shows that $P_{0} = E_{1} / k$. The stock is valued like a nongrowing perpetuity of $E_1$, and the $P/E$ ratio is just $1/k$. However, as PVGO becomes an increasingly dominant contributor to price, the P/E ratio can rise dramatically.

Look again at the constant-growth DDM formula, $P_{0} = D_{1} / (k - g)$. Now recall that dividends equal the earnings that are not reinvested in the firm: $D_{1} = E_{1}(1 - b)$. Recall also that $g = ROE \times b$. Hence, substituting for $D_{1}$ and $g$, we find that:
$$
P_{0} = \frac{E_{1}(1 - b)}{k - ROE \times b}
$$
, implying the P/E ratio is:
$$
\frac{P_{0}}{E_{1}} = \frac{1 - b}{k - ROE \times b}
$$
, it is easy to verify that the P/E ratio increases with ROE. This makes sense, because high ROE projects give the firm good opportunities for growth. We also can verify that the P/E ratio increases for higher plowback, $b$, as long as ROE exceeds $k$. This too makes sense. When a firm has good investment opportunities, the market will reward it with a higher P/E multiple if it exploits those opportunities more aggressively by plowing back more earnings into those opportunities.

`Earnings management` is the practice of using flexibility in accounting rules to improve the apparent profitability of the firm.

**Price-to-Book Ratio** This is the ratio of price per share divided by book value per share.

**Prcie-to-Cash-Flow Ratio** Earnings as reported on the income statement can be affected by the company's choice of accounting practices, and thuse are commonly viewed as subject to some imprecision and even manipulation.

**Price-to-Sales Ratio** Many start-up firms have no earnings. As a result, the price earnings ratio for these firms is meaningless.

**Be Creative** Sometimes a standard valuation ratio will simply not be available, and yo will have to devise your own.

One approach is to discount the `free cash flow for the firm (FCFF)` at the weighted average cost of capital to obtain the value of the firm, and subtract the then-existing value of debt to find the value of equity. Another is to focus from the start on the free cash flow to `equityholders`(FCFE), discounting those directly at the cost of equity to obtain the market value of equity. The free cash flow to the firm is the after-tax cash flow generated by the firm's operations, net of investments in capital, and net working capital. It includes cash flows available to both debt- and equityholders. It equals:
$$
\text{FCFF} = EDIT(1 - t_{c}) + \text{Depreciation} - \text{Capital expenditures} - \text{Increase in NWC}
$$
, where:
$$
EBIT = \text{earnings before interest and taxes} \\
t_{c} = \text{the corporate tax rate} \\
NWC = \text{net working capital}
$$
, alternatively, we can focus on cash flow available to equityholders. This will differ from free cash flow to the firm by after-tax interest expenditures as well as by cash flow associated with net issuance or repurchase of debt (i.e., principal repayments minus proceeds from issuance of new debt):
$$
\text{FCFE} = \text{FCFF} - \text{Interest expense} \times (1 - t_{c}) + \text{Increases in net debt}
$$
, a free cash flow to the firm valuation model discounts year-by-year cash flows plus some estimate of terminal value, $V_{T}$. In below equation, we use the constant-growth model to estimate terminal value and discount at the weighted-average cost of capital:
$$
\text{Firm value} = \sum_{t = 1}^{T}\frac{FCFF_{t}}{(1 + WACC)^{t}} + \frac{V_{T}}{(1 + WACC)^{T}}, \text{where } V_{T} = \frac{FCFF_{T + 1}}{WACC - g}
$$
, to find equity value, we subtract teh existing market value of debt from the derived value of the firm. Alternatively, we can discount free cash flow to `equity (FCFE)` at the cost of `equity`, $k_{E}$:
$$
\text{Intrinsic value of equity} = \sum_{t = 1}^{T} \frac{FCFE_{t}}{(1 + k_{E})^{t}}, \text{where } V_{T} = \frac{FCFE_{T + 1}}{k_{E} - g}
$$


## Summary

TODO