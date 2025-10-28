# Market Making

This note summarizes practical concepts for market making: the role of market makers, components of the bid-ask spread, inventory and adverse-selection risk, quoting strategies, simple modeling approaches, execution considerations (latency, fees, slippage), monitoring metrics, and a short toy simulation example. The goal is a concise practitioner reference that complements the broader INVESTMENTS notes.

## What is market making?
Market makers (MMs) provide liquidity by continuously posting both bid and ask quotes for one or more instruments. They earn the spread (ask minus bid) for providing immediacy to other market participants, while managing inventory risk and the risk of trading with better-informed counterparties.

Key responsibilities:
- Supply two‑sided liquidity.
- Manage inventory to limit directional exposure.
- Price quotes to balance expected profit per trade against fill probability and risk.

## Components of the bid-ask spread
- Order processing / explicit costs: fees, clearing, exchange fees.
- Inventory risk premium: compensation for bearing temporary imbalances in inventory.
- Adverse selection (information risk): compensation for trading with counterparties who may possess superior information.

Total spread ≈ processing cost + inventory component + adverse-selection premium (model dependent).

## Quoting strategies (practical patterns)

- Symmetric quoting: post bid = mid − s/2 and ask = mid + s/2 with a fixed spread s. Simple but ignores inventory.
- Inventory-skewed quoting: skew quotes to encourage trades that reduce inventory (e.g., if long, raise the ask and/or lower the bid to discourage additional buys and encourage sells).
- Time-varying spread: widen spread during low liquidity or high volatility; tighten when liquidity returns.

Rules of thumb for inventory skew:
- Compute inventory I_t; set quote skew proportional to I_t (and optionally to instantaneous volatility σ_t and risk-aversion γ).
- Use position limits and time-based rebalancing to avoid large persistent exposures.

## Simple modeling ideas

- Fill model: model arrival of market orders against your quotes as Poisson processes with rates that decline with the quote distance from mid.
- P&L decomposition: realized P&L = collected spreads − inventory P&L (mark-to-market losses/gains) − transaction costs − fees.

Basic notation (informal):
- mid_t: mid-price (reference price).
- q_bid, q_ask: quoted bid and ask prices.
- s_t = q_ask − q_bid: quoted spread.
- I_t: current inventory (signed quantity).

Risk-aware quote adjustment: shift quotes by a skew Δ such that

  q_bid = mid_t - s/2 - Δ(I_t)

  q_ask = mid_t + s/2 - Δ(I_t)

where Δ(I_t) is chosen so that expected change in inventory tends toward zero and compensates for risk aversion.

### Avellaneda–Stoikov (intuition)
The Avellaneda–Stoikov framework treats market-making as a stochastic control problem: choose bid/ask offsets to maximize expected utility of terminal wealth (often exponential utility) given Poisson arrival intensities for fills. Key qualitative insights:
- The reservation price (reference around which you quote) is shifted away from the mid by an inventory-dependent term; larger inventory causes you to shift prices to encourage rebalancing.
- Optimal half-spread increases with risk aversion and expected volatility, decreases with higher arrival intensity.

I avoid detailed derivations here, but the Avellaneda–Stoikov model is a practical starting point for systematic quoting algorithms; see references below for closed-form approximations under simplifying assumptions.

## Execution, latency and microstructure considerations

- Latency: in electronic markets, small timing advantages matter. Fast cancellations and amendments reduce adverse fills but increase message traffic and costs.
- Order types: use limit orders for providing liquidity; consider hidden or iceberg orders to manage information leakage.
- Fee schedule: maker rebates vs taker fees change incentives; incorporate them into spread setting and expected P&L.
- Market depth and queue position: early queue priority often matters as much as price; consider queue position models when optimizing fills.

## Risk management and governance

- Position limits (per-symbol and portfolio), intraday rebalancing rules, and stop-loss thresholds.
- Stress testing: run scenarios with sudden volatility spikes, liquidity droughts, and correlation breakdowns.
- Real-time monitoring: inventory, realized and unrealized P&L, fill rates, order-to-trade ratios, message rates, and execution latency.

## Metrics to monitor
- Average quoted spread and realized spread (collected after costs).
- Fill probability vs distance from mid.
- Inventory turnover and time-in-inventory.
- Trade-to-quote ratio, cancelation rate, and execution latency.
- P&L attribution: spread capture vs inventory P&L vs fees and costs.

## Worked toy example (conceptual)

- Suppose mid = 100, quoted spread s = 0.2 (bid 99.9, ask 100.1). If arrival rate λ per side yields an expected number of fills per hour, expected gross spread income per hour ≈ λ · s. Inventory P&L depends on mid moves while positions are held.

Practical lesson: a small spread with high fill rate can outperform a wide spread with rare fills after accounting for inventory risk and costs.

## Small simulation snippet (toy)

This is a minimal illustrative example (not production-ready). It simulates symmetric quoting with simple fill probabilities that decline with spread distance.

```python
import numpy as np
import pandas as pd

T = 1000
mid = 100.0
spread = 0.2
inventory = 0
pnl = 0.0
lambda0 = 0.01  # baseline fill prob per step

for t in range(T):
    bid = mid - spread/2
    ask = mid + spread/2
    # fill probabilities decline with half-spread
    p_fill = lambda0 * np.exp(-spread)
    if np.random.rand() < p_fill:
        # randomly pick side
        if np.random.rand() < 0.5:
            # buy at bid
            inventory += 1
            pnl -= bid  # cash outflow; mark-to-market later
        else:
            # sell at ask
            inventory -= 1
            pnl += ask
    # simple mid-price random walk
    mid += np.random.normal(scale=0.05)

# mark inventory to market
pnl += inventory * mid
print('Inventory', inventory, 'P&L', pnl)
```

Extend this snippet with inventory-skewing, fee models, and more realistic fill processes (queue dynamics, order book simulation) for better insights.

## Common pitfalls

- Ignoring queue priority and assuming constant fill probabilities.
- Overfitting quoting parameters on a quiet historic period that does not represent stressed markets.
- Underestimating message/cancellation costs and exchange limits.

## References and further reading

- Avellaneda, Marco & Stoikov (2008) — High-frequency market-making
- Cartea, Jaimungal & Penalva — Algorithmic and High-Frequency Trading (market microstructure chapters)
- Papers and blog posts on queue dynamics, limit order book simulation, and empirical studies of spread and liquidity.

---

If you want, I can: (1) add a small Avellaneda–Stoikov worked derivation with formulae, (2) expand the simulation into a Jupyter notebook with parameterized experiments and fee models, or (3) insert practical production notes on order router design and exchange connectivity. Tell me which next step you prefer and I will follow the same todo → edit → verify workflow.
