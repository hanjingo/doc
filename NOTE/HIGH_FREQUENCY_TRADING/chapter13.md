# CHAPTER 13 Regulation

[TOC]



## Currently Deployed Measures for System Stability

### Interval Price Limits

`Interval price limits`(IPLs) are circuit breakers that are triggered by extreme short-term moves. The IPL-based halts work as follows. For each traded financial instrument, the exchange computes a moving average price level and a "normal" variation determined on the highs and lows evidenced in the moving data window used in computation.

### No-Cancel Range

`No-cancel range` refers to the depth of quotes in the limit order book, where the limit orders cannot be cancelled for a predetermined period of time. When the no-cancel range comprises only the best bid and the best ask, the measure is also known as the minimum quote life(MQL).

### Protection Points

`Protection points` stipulate the maximum number of price levels or ticks a large incoming market order can sweep through in the limit order book. When a market buy order sweeps through the maximum number of price levels and is still not filled in its entirety, the unfilled remainder of the order is automatically converted into a limit buy order.

### Cancel Orders on System Disconnect

Exchanges and broker-dealers alike continuously monitor "heartbeat" message from their clients. When a client fails to check in with the regular heartbeat, and then misses further scheduled "pings", the client connection is assumed to have been terminated. Exchanges such as CME take cancel limit orders of disconnected clients as a protective measure.

### Message Throttle Limits

The `message throttle limits`, also known as `minimum fill ratios`, dictate the maximum ratio of order cancellations to order executions.

### Maximum Quantity Limits

`Maximum quantity limits` help prevent human and algorithmic "fat finger" errors by enforcing the maximum order sizes and trading positions.

### Real-Time Position Validation

The secret to stable futures markets is the continuous, real-time check of position market values vis-à-vis the creditworthiness of the trading account. When the market value in a given account exceeds the critical margin limit, the client's trading algorithm is prohibited from entering into new positions. In extreme situations, some of the account holdings may be liquidated to satisfy margin requirements.

### Price Reasonability

Under `price reasonability`, exchanges allow orders only at price levels within a predetermined range away from the market price.

### Near-Term Surveillance Measures

- Kill Switches

  Kill switches are designed to automatically block and unblock order entry at the following levels:

  1. Execution firm
  2. Account
  3. Asset class
  4. Side of market
  5. Product
  6. Exchange

- Legal Entity Identifiers

  An LEI is a unique identifier assigned to all market participants:

  1. Financial intermediaries
  2. Banks
  3. Finance companies
  4. All listed companies
  5. Hedge funds
  6. Proprietary trading organizations
  7. Pension funds
  8. Mutual funds
  9. Private equity funds
  10. Other entities

### Investor Protection

The SEC and most other regulators seek to safeguard traders and investors by minimizing the following activities in the markets:

- Market manipulation

  1. The activity should be recurrent.
  2. The activity was performed with the intent of manipulating markets.

- Front-running

  Naturally, unscrupulous brokers possessing order-flow data may choose to front-run their own clients whenever they detect a large impending price move. The regulation has tried to deal with this problem.

- Market crashes

  Two main streams of crash predictability have emerged:

  1. Based on asymmetry of liquidity in the limit order books.

     To estimate the incidence of a crash, the authors develop a volume-based probability of informed trading, or VPN metric:
     $$
     VPIN \approx \frac{\sum_{\tau = 1}^{n}|V_{\tau}^{S} - V_{\tau}^{B}|}{nV}
     $$
     where $V_{\tau}^{S}$ and $V_{\tau}^{B}$ are volumes initiated by sell and buy market orders, respectively, computed within each volume-based clock unit. Easley, Lopez de Prado, and O'Hara (2011) consider volume clocks where each "time" unit corresponds to 5- E-mini contracts: within each volume-clock unit $\tau$, then, $V_{\tau}^{S} - V_{\tau}^{B} = 50$ contracts.

  2. Based on abnormal trading patterns.

     Normal market movements are calibrated to fit the Mandelbrot-like growth parameter, known as the `Hurst exponent`.