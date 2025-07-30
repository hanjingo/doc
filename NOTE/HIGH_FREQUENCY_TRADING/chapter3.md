# CHAPTER 3 Market Microstructure, Orders, and Limit Order Books

[TOC]

In many risk management applications, order books are also assumed to follow normal bell-curve distributions. Neither of the assumptions tends to hold: order books are seldom normal and are often asymmetric.

FIFO, known as the continuous auction, has been shown to enhance transparency of trading via the following measures:

- Reducing information asymmetry--all traders have access to the limit order book information.
- Enhancing liquidity--a CLOB structure incentivizes traders to add limit orders, thereby increasing market liquidity.
- CLOB's organization supports efficient price determination by providing a fast and objective order-matching mechanism.
- Uniform rules for all market participants ensure operational fairness and equal access.

The main advantage of the pro-rata matching from the exchange point of view is the built-in incentives for traders to place large limit orders, and, therefore, to bring liquidity to the exchange.

Orders can be described as passive or aggressive. A limit order far away from the market price (a low-priced limit buy order, or a high-priced limit sell order) is considered passive. The closer the limit order is to the market price, the more aggressive the order is. A market order is the most aggressive order, "crossing the spread" to be matched with the best-priced limit order on the opposite side of the limit order book. Limit orders crossing the spread are treated like market orders in the execution queue and are also considered aggressive.

In today's markets, price uncertainty can be the costliest component associated with the market order execution. From the time the market order is placed to the time the execution is recorded, the market price may "slip", resulting in worse execution than the prevailing price at the time the market order was placed. The slippage may be due to several factors:

- Several market orders may arrive at the exchange and be executed between the time a given market order is placed and the time it is executed. Each of the arriving market orders may deplete the matching liquidity in the order book, adversely moving the market price.
- A market order that is large relative to the available depth of the order book may sweep through the book, executing fractional pieces of the order against limit orders at different price levels.
- Additional market conditions, such as market disruptions, may also result in significant slippage.

The NBBO execution rule was put forth by the Securities and Exchange Commission (SEC) in 2005 under the regulation NMS, with the explicit purpose of leveling the playing field: under the NBBO rule, every limit order, whether placed by a large institution or an individual investor, has to be displayed to all market participants.

NBBO limit orders can be achieved using two distinct approaches:

1. The exchange can compete to attract the top-of-the-book liquidity--limit orders priced at NBBO or better.
2. The exchange can compete to attract market orders, while simultaneously serving as a proprietary market maker posting NBBO limit orders.

The exchange may pay liquidity providers for posting limit orders, or pay takers of liquidity for bringing in market orders. Such payments, amounting to negative transaction costs, are known as `rebates`.