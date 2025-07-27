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

The secret to stable futures markets is the continuous real-time check of position market values vis-a-vis credit worthiness of trading account. When the market value in a given account exceeds the critical margin limit, the client's trading algorithm is prohibited from entering into new positions. In extreme situations, some of the account holdings may be liquidated to satisfy margin requirements.

### Price Reasonability

TODO