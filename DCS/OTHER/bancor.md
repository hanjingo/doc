English | [中文版](bancor_zh.md)

# Bancor Algorithm

[TOC]


## Abstract

Bancor Algorithm (bancor_protocol)


## Key Concepts
* Supply

	$$Token Supply$$

* Price

	$$Token\ Price = Balance\ (Reserve\ Balance) \div ( Supply\ (Token\ Supply) \times CW\ (Constant\ Reserve\ Ratio) )$$

* TotalValue

	$$Token\ Market\ Cap = Price\ (Token\ Price) \times Supply\ (Token\ Supply)$$

* Balance

	Reserve Balance

* CW
  
	$$Constant\ Reserve\ Ratio = Balance\ (Reserve\ Balance) \div TotalValue\ (Token\ Market\ Cap)$$


## Token Purchase

$$Token = Token\ Supply \times ( (1 + EOS\ Payment \div Reserve\ Balance)^{Constant\ Reserve\ Ratio} - 1 ) $$
Example:

```md
Token Supply: 1000
Reserve Balance: 250
Constant Reserve Ratio: 0.5
Using 750 EOS can buy: 1000 * ( (1 + 750 / 250)^0.5 - 1 ) = 1000 tokens
```
### Token Sale
$$EOS = Reserve\ Balance \times (1 - (1 - Tokens\ Sold \div Token\ Supply) ^ {\frac{1}{Constant\ Reserve\ Ratio}} )$$
Example:

```
Token Supply: 1000 + 1000 = 2000
Reserve Balance: 250 + 750 = 1000
Constant Reserve Ratio: 0.5
Selling 1000 tokens can get: 1000 * (1 - (1 - 1000 / 2000) ^ (1 / 0.5) ) = 750
```
### Features
When Constant Reserve Ratio = 100%, EOS and token are pegged; the ratio does not change
When Constant Reserve Ratio = 50%, the ratio between EOS and token changes as the supply changes
