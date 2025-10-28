# Investment Instruments

[TOC]

This note summarizes common financial instruments, their characteristics, risks, and typical uses. It condenses material from the INVESTMENTS notes into a practical reference for students and practitioners.

## Quick orientation

Investment instruments can be grouped by purpose and market:

- Money-market instruments: short-term, highly liquid debt (Treasury bills, commercial paper).
- Fixed-income (bonds): government, municipal, corporate bonds, characterized by maturity, coupon, credit risk.
- Equities: common and preferred stocks — ownership claims with variable returns and higher risk.
- Collective investment vehicles: mutual funds, ETFs, index funds.
- Derivatives: forwards, futures, options, swaps — contracts deriving value from underlying assets.
- Real assets and alternatives: real estate (REITs), commodities, private equity, hedge funds.
- Foreign exchange (FX) instruments and structured products.

Each instrument differs in liquidity, return profile, risk type (market, credit, liquidity), and tax treatment.

---

## Money-market instruments

Characteristics:

- Short maturities (overnight to 1 year), high liquidity, low default risk for government-issued instruments.
- Common instruments: Treasury bills (T-bills), commercial paper, certificates of deposit (CDs), repurchase agreements (repos).

Use cases: cash management, short-term parking of funds, liquidity buffers.

---

## Bonds and fixed-income securities

Key concepts and definitions

- Face value (par): the principal repaid at maturity, typically 100 or 1,000 units of currency.
- Coupon rate: the periodic interest paid by the bond expressed as a percentage of par.
- Maturity: the date when the principal is repaid.
- Yield to maturity (YTM): the single discount rate that equates the present value of future cash flows (coupons + principal) to the current price; an internal rate of return for buy-and-hold investors.
- Current yield: annual coupon divided by current price (simple, ignores time and principal repayment).
- Clean vs dirty price: clean price excludes accrued interest; dirty price = clean price + accrued interest (what the buyer actually pays between coupon dates).

Why bonds matter

Fixed-income instruments are central to capital markets because they provide predictable cash flows, play a key role in portfolio allocation, and form the foundation of the interest-rate term structure used for valuing other assets (derivatives, corporate projects). Bond markets also transmit monetary policy through yields.

Types of bonds (overview)

- Government bonds: issued by sovereigns (e.g., Treasuries). Generally lowest credit risk for that currency, used as risk-free benchmarks.
- Agency and supranational bonds: issued by government agencies or international organizations; credit quality typically high but varies.
- Corporate bonds: issued by companies; credit spreads reflect default risk and liquidity.
- Municipal bonds: issued by local governments; may have tax advantages.
- Inflation-linked bonds: coupons/principal adjusted for inflation (e.g., TIPS), protect real purchasing power.
- Structured and hybrid bonds: convertible bonds, callable/puttable bonds, zero-coupon bonds.

Bond cash flows and pricing

A plain-vanilla fixed-rate bond pays periodic coupons and returns principal at maturity. Its price P is the present value of future coupons C_t and principal F:

P = sum_{t=1}^{N} C_t / (1+y)^t + F / (1+y)^N

where y is the discount rate per period consistent with coupon frequency. For semiannual coupons, convert annual rates to semiannual periods.

Yield measures and conventions

- Yield to maturity (YTM): solves the PV equation above. For non-flat yield curves, YTM is a useful summary but does not reflect reinvestment or term-structure shape.
- Spot rates and forward rates: valuation using the term structure (zero-coupon yields) gives exact theoretical prices under no-arbitrage.
- Par yield: coupon rate that makes a bond trade at par given the current term structure.
- Zero-coupon yields: yields on zero-coupon instruments for each maturity (used for discounting cash flows precisely).

Accrued interest and day-count conventions

Bond markets use day-count conventions (e.g., ACT/360, ACT/365, 30/360) to compute accrued interest between coupon dates. Always confirm the market convention when calculating clean/dirty prices and yields.

Clean vs dirty price

- Clean price: quoted market price excluding accrued interest.
- Dirty price (invoice price): clean price + accrued interest — the amount transferred on settlement.

Duration and convexity (interest-rate risk)

- Macaulay duration: the weighted average time to receive bond cash flows (weights are PVs of cash flows). Measured in years.
- Modified duration: Macaulay duration divided by (1+y) — approximates percentage price change for small parallel shifts in yield: ΔP/P ≈ -ModifiedDuration * Δy.
- Convexity: second-order sensitivity measuring curvature. Using both duration and convexity improves price-change estimates for larger yield moves.

Credit risk, spreads, and liquidity

- Credit risk: probability issuer will default on coupon or principal. Credit ratings (S&P, Moody's, Fitch) provide a convenient signal but are not perfect.
- Credit spread: the yield difference between a corporate bond and a comparable-risk-free benchmark (usually government yield of similar maturity). Spread compensates investors for default risk, liquidity, tax differences, and other risks.
- Liquidity: less-liquid bonds (e.g., some corporates, municipals) require a liquidity premium and may trade at wider bid-ask spreads.

Special features

- Zero-coupon bonds: no periodic coupons, sold at deep discount; duration equals maturity.
- Callable bonds: issuer can repay early; call feature benefits issuer and adds reinvestment/call risk for holders (tends to raise yield vs non-callable).
- Puttable bonds: investor has the right to sell back to issuer; reduces investor risk and thus typically lowers yield.
- Convertible bonds: bond can be converted into equity under specified terms — hybrid characteristics.

Term structure and yield curve

The yield curve (plot of yields vs maturity) summarizes market expectations and risk premia. Common shapes: normal (upward-sloping), inverted (downward-sloping), flat, humped. Term-structure models (bootstrapping, Nelson–Siegel/ Svensson, Vasicek/Hull-White for dynamics) help with pricing and risk management.

Valuation with the term structure

When the term structure is not flat, discount each cash flow using the corresponding zero-coupon spot rate s_t:

P = sum_{t=1}^{N} C_t / (1+s_t)^t + F / (1+s_N)^N

This no-arbitrage approach avoids distortions from using a single YTM.

Worked example (simple)

Example: Price a 5-year annual coupon bond, face F=1,000, coupon 3% (annual), if the appropriate discount rate is 4% (flat yield curve).

- Annual coupon C = 0.03 * 1000 = 30.
- Price P = 30/1.04 + 30/1.04^2 + 30/1.04^3 + 30/1.04^4 + (30+1000)/1.04^5 ≈ 956.39.

Duration estimate (approximate)

Using the cash flows above, compute Macaulay duration (weighted average time) and modified duration to estimate sensitivity: for small Δy, ΔP/P ≈ -ModifiedDuration * Δy.

Practical notes for practitioners

- Always check coupon frequency and day-count convention.
- Use spot-rate discounting for precise valuation, especially for irregular cash flows or when hedging.
- Consider liquidity and transaction costs when trading corporate bonds; market impact can be material for large orders.
- For callable bonds, price using option-adjusted spread (OAS) models to isolate call option value.

Further reading

- Fabozzi, "Fixed Income Analysis" for a practical and comprehensive treatment.
- Hull, "Options, Futures, and Other Derivatives" for OAS and interest-rate option interactions.


---

## Equities (stocks)

Equities represent ownership in a firm. Returns come from dividends and capital gains. Equities typically offer higher expected returns but greater volatility than bonds.

Classes:

- Common stock: voting rights, residual claim on earnings.
- Preferred stock: fixed dividends, priority over common stock in claims, hybrid between equity and debt.

Valuation approaches: discounted cash flows (DCF), dividend discount models (DDM), relative valuation (P/E, EV/EBITDA).

Risks: market risk, business risk, liquidity risk, event risk.

---

## Collective investment vehicles

Mutual funds and ETFs pool investor capital to buy diversified portfolios.

- Mutual funds: actively or passively managed, traded at NAV once per day, may have sales loads and management fees.
- Exchange-traded funds (ETFs): trade on exchanges intraday like stocks, often track indices with lower expense ratios.

Benefits: diversification, professional management, easy access to many asset classes.

Costs: management fees (expense ratio), tracking error for index funds, potential tax inefficiencies in some fund structures.

---

## Derivatives: forwards, futures, options, and swaps

Derivatives derive value from an underlying asset (commodity, security, index, interest rate, currency).

- Forwards and futures: contractual agreements to buy/sell an asset at a future date for a price agreed today. Futures are standardized and exchange-traded; forwards are OTC.
- Options: contracts that give the holder the right, but not the obligation, to buy (call) or sell (put) the underlying at a strike price before or at expiry.
- Swaps: OTC agreements to exchange cash flows (e.g., interest rate swap exchanging fixed for floating payments).

Uses: hedging risk (price, interest rate, currency), speculation, arbitrage, and synthetic position creation.

Risks: counterparty risk (OTC), margin and leverage risk, model risk.

---

## Real assets & alternatives

- Real estate: direct property investment or via REITs (Real Estate Investment Trusts).
- Commodities: physical goods (oil, metals, agricultural products) traded via futures and spot markets.
- Private equity and venture capital: illiquid, long-horizon investments in private companies.
- Hedge funds: often use leverage and alternative strategies (long/short, relative value, event-driven).

Alternatives often offer diversification but come with liquidity, fee, and due-diligence concerns.

---

## Foreign exchange (FX) instruments

FX instruments include spot FX, forwards, futures, and currency options. FX markets are large and liquid; exchange-rate risk affects international investments.

Hedging currency exposure is common for international portfolios.

---

## Structured products and hybrids

Structured products combine debt and derivatives to provide tailored payoff profiles (capital-protected notes, autocallables). They are typically issued by banks and have issuer credit risk.

Advice: understand payoff diagrams, fees, and embedded risks before investing in structured products.

---

## Risk and return considerations

- Expected return: compensation for time value and risk.
- Diversification reduces idiosyncratic (firm-specific) risk but not systematic market risk.
- Liquidity matters: less-liquid instruments typically command a liquidity premium.
- Tax and regulatory treatments alter after-tax returns and suitability for different investors.

Key metrics and concepts:

- Yield to maturity (YTM), current yield
- Duration and convexity (interest-rate sensitivity)
- Volatility and beta (equity risk)
- Credit spreads and default probability
- Sharpe ratio, tracking error for funds

---

## Practical guidance

- Match instrument selection to investment horizon and liquidity needs.
- Use diversification (across assets, sectors, geographies) to manage risk.
- Understand fees, tax implications, and counterparty exposures.
- When using derivatives, manage leverage and margin requirements carefully.

## Further reading and resources

- See the `INVESTMENTS` notes in `c:\work\doc\NOTE\INVESTMENTS` for chapter-level depth on valuation, portfolio theory, and financial markets.
- Standard textbooks: Bodie, Kane, and Marcus; John C. Hull (derivatives); Fabozzi (fixed income).

---

If you want, I can expand any section into a full chapter (e.g., bond valuation and duration, options basics and payoff diagrams, ETF vs mutual fund comparison) or add short worked examples and simple code snippets for basic valuation formulas.

