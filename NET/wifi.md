# Wi‑Fi (IEEE 802.11) — concise overview

[TOC]

![wireless_network](res/wireless_network.png)

This note summarizes key wireless LAN concepts relevant for system design and operations. It covers physical‑layer differences from wired links, basic MAC behavior (contention, carrier sense, and collision avoidance), rate adaptation, and practical deployment considerations. The goal is a short, clear reference — preserving the figures while improving structure and clarity.

## What’s different about wireless links?

- Shared medium: the air is a broadcast medium; transmissions are heard by multiple receivers and interference is common.
- Variable channel quality: signal strength and noise change over time and space (path loss, shadowing, fading, mobility).
- Multipath propagation: reflections cause multiple delayed copies of the signal, producing intersymbol interference and fast fading.
- Noisy and interference‑prone: other devices, co‑channel networks, and non‑Wi‑Fi interferers affect throughput and error rates.

Elements of a wireless LAN

- Wireless links (radio channel)
- Access point (base station / AP)
- Network infrastructure (bridging to wired LAN, authentication servers, DHCP, etc.)

## Signal quality and its effects

![snr](res/snr.png)

- Signal‑to‑Noise Ratio (SNR): ratio of received signal power to noise power. Higher SNR generally yields lower bit‑error rates (BER).
- BER vs rate tradeoff: for a given modulation/coding scheme, raising the data rate tends to increase BER at the same SNR. Adaptive modulation and coding allow devices to trade rate for reliability.
- Fading and mobility: small‑scale fading causes rapid SNR variations; devices and APs often use rate adaptation and retransmissions to maintain good performance.

## PHY basics (short)

- Common PHYs: OFDM (used in 802.11a/g/n/ac/ax) and DSSS/CCK (older 802.11b). OFDM divides the channel into subcarriers, making the system more robust to multipath.
- Channel width and throughput: wider channels (20/40/80/160 MHz) increase peak throughput but can be more sensitive to interference and reduce spectral reuse.

## MAC layer: CSMA/CA and collision avoidance

- Carrier Sense Multiple Access with Collision Avoidance (CSMA/CA) is the basic medium access method: before transmitting, a station senses the channel; if idle for a Distributed InterFrame Space (DIFS), it transmits after a random backoff. If busy, it defers and continues backing off.
- Acknowledgements (ACKs): successful frames are acknowledged by the receiver; missing ACKs trigger retransmission.
- RTS/CTS: optional Request‑to‑Send / Clear‑to‑Send handshake reduces collisions caused by hidden terminals (two stations that cannot hear each other but both interfere at the AP).
- Frame aggregation and block ACK: modern 802.11 versions aggregate frames to amortize MAC overhead and improve throughput.

## Rate adaptation and reliability

- Devices choose modulation and coding (MCS) based on measured link quality (SNR, frame error rate). Algorithms (e.g., Minstrel, SampleRate) probe higher rates and fall back on failures.
- Retransmissions at the MAC layer hide transient errors from higher layers but increase latency. Transport protocols (TCP) see the effects as packet loss or delay variation.

## Practical deployment notes

- Coverage vs capacity: increase AP transmit power or add APs for coverage; add more APs (with careful channel planning) for capacity and spatial reuse.
- Channel planning: avoid co‑channel interference by assigning non‑overlapping channels where possible; in dense deployments, use automatic RF management and power control.
- MTU and fragmentation: avoid excessive fragmentation; prefer aggregation (A‑MPDU / A‑MSDU) in modern networks for efficiency.
- Security: use WPA2/WPA3; avoid WEP/TKIP. Use 802.1X (RADIUS) for enterprise authentication when possible.

## Monitoring and troubleshooting tips

- Measure SNR, RSSI, and frame error rates per client.
- Look for repeated retransmissions, high retry rates, or low PHY rates—these indicate link problems.
- Use spectrum analysis to find non‑Wi‑Fi interference (microwaves, cordless phones, Bluetooth).

## References

- Kurose & Ross — Computer Networking: A Top‑Down Approach (wireless chapters)
- IEEE 802.11 family specifications and vendor deployment guides
