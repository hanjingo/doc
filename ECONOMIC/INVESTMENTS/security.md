# Securities — Overview

[TOC]

This note summarizes financial securities: what they are, common types, how they trade and are valued, the risks they carry, and key market infrastructure. It condenses material from the `INVESTMENTS` notes into a practical reference for students and practitioners.

## What is a security?

A security is a tradable financial instrument that represents some form of financial value. Securities fall into three broad economic categories:

- Debt securities (bonds, notes): promises to pay principal and interest.
- Equity securities (common and preferred stock): ownership claims on a firm.
- Derivative securities (options, futures, swaps): contracts whose value derives from underlying assets.

Securities can be issued in primary markets (new issues sold to investors) and subsequently traded in secondary markets (exchanges, OTC).

---

## Major classes of securities

### Debt securities (fixed income)

- Characteristics: issuer, face (par) value, coupon, maturity, credit rating, yield.
- Valuation: present value of future coupon and principal cash flows discounted at a market discount rate (yield to maturity).
- Common examples: Treasury bonds and notes, municipal bonds, corporate bonds, mortgage-backed securities (MBS), asset-backed securities (ABS).
- Special forms: zero-coupon bonds, floating-rate notes, convertible bonds (hybrid equity features).

Risks: interest-rate risk (duration/convexity), credit/default risk, liquidity risk, prepayment risk (for mortgages), inflation risk.

### Equity securities

- Common stock: ownership, voting rights, dividends (not guaranteed), residual claim on assets.
- Preferred stock: fixed or adjustable dividends, priority over common stock for dividend and liquidation, often non-voting; behaves as a hybrid between debt and equity.

Valuation: dividend discount models, DCF for free cash flows to equity, relative valuation (P/E, P/B, EV/EBITDA).

Risks: market volatility, business risk, dilution from issuance, dividend policy changes.

### Derivatives (securities derived from underlying assets)

- Options (calls and puts), futures and forwards, swaps.
- Uses: hedging, leverage, arbitrage, price discovery.
- Pricing: Black–Scholes and binomial models for options; cost-of-carry relationships for futures; discounting of expected cash flows for swaps.

Risks: leverage amplifies losses, counterparty risk for OTC derivatives, model risk and margin/margin calls for exchange-traded derivatives.

---

## Market types and participants

- Primary market: issuance, underwriting, IPOs, bond syndication.
- Secondary market: exchanges (NYSE, NASDAQ) and over-the-counter (OTC) markets.
- Participants: issuers, retail and institutional investors, brokers, dealers/market-makers, exchanges, clearing houses, custodians, regulators.

Market infrastructure:

- Exchanges: match buy and sell orders, provide price transparency and liquidity.
- Clearing houses and central counterparties (CCPs): reduce counterparty risk by interposing themselves between buyers and sellers and handling settlement.
- Settlement systems: ensure final transfer of securities and cash (common standards: T+2 or T+3 settlement cycles; some markets move to T+1 or real-time settlement).

---

## Trading mechanics and market microstructure (brief)

- Order types: market orders, limit orders, stop orders.
- Liquidity providers and market makers post bid/ask quotes — the spread compensates for immediacy and inventory risk.
- Matching algorithms, price-time priority, and electronic order books determine execution.

Understanding microstructure helps explain short-term price movements, transaction costs, and execution quality.

---

## Valuation basics

- Present value: value of a security equals discounted expected future cash flows (coupons/dividends/principal) using appropriate discount rates.
- Bond price formula: price = sum_{t=1..T} (coupon_t)/(1+y)^t + par/(1+y)^T.
- Yield measures: current yield, yield to maturity (YTM), yield to call.
- Duration and convexity measure interest-rate sensitivity; duration approximates percentage price change for a small yield change.

For equities, valuation often combines expected growth rates, discount rates (cost of equity), and comparables.

---

## Key risks and metrics

- Market risk (systematic): cannot be diversified away — often measured by volatility or beta.
- Idiosyncratic risk: firm-specific, diversifiable through portfolio construction.
- Credit risk: likelihood of issuer default; measured by credit ratings and credit spreads.
- Liquidity risk: difficulty of selling without moving the market.
- Operational and settlement risk: errors, fraud, settlement failures.

Common metrics and tools:

- Volatility (standard deviation), beta (CAPM), Sharpe ratio for risk-adjusted returns.
- Credit spreads, probability of default (PD), loss given default (LGD), expected loss (EL).
- Duration, convexity for bond portfolios; tracking error and information ratio for funds.

---

## Corporate actions and ownership events

- Dividends, share buybacks, stock splits, rights issues, mergers and acquisitions — these events affect security values and shareholder rights.
- For debt: covenants, ratings changes, restructuring or default.

Investors should understand corporate action mechanics and record dates, ex-dividend dates, and settlement implications.

---

## Securitization and structured securities

- Securitization pools illiquid assets (mortgages, loans) and issues tranches of securities backed by those cash flows (MBS, ABS, CDOs).
- Structured products include notes with embedded options, capital-protected structures, and autocallables.

Benefits: access to diversified cash flows, potential yield enhancement.
Risks: complexity, model risk, correlation of underlying assets, tranching concentrates credit risk in lower tranches (observe 2007–2009 MBS/CDO failures as cautionary example).

---

## Regulation and investor protection

- Securities are regulated to ensure market integrity, protect investors, and reduce systemic risk (examples: SEC in the U.S., FCA in the U.K.).
- Key regulations cover disclosure (prospectuses), market conduct, insider trading, capital requirements for intermediaries, and the operation of exchanges and CCPs.

Retail investor protections: suitability rules, best-execution obligations, segregation of client assets.

---

## Practical guidance for investors

- Know the instrument: read the prospectus, terms, covenants, and payoff diagrams for structured products.
- Match securities to objectives: liquidity needs, time horizon, risk tolerance, tax status.
- Diversify across asset classes and issuers to reduce idiosyncratic risk.
- Incorporate transaction costs, fees, and tax effects into expected returns.
- For derivatives, clearly understand margin, collateral, and contingency plans for margin calls.
