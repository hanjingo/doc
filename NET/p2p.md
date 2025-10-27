## P2P file distribution

[TOC]

![dcs_bittorrent](res/dcs_bittorrent.png)

This note summarizes the basic performance model used to compare client–server and peer‑to‑peer (P2P) file distribution. The model and formulas below follow the treatment in Kurose & Ross (Top‑Down Approach) and are intended to make the assumptions and tradeoffs explicit.

Terminology and symbols:

- F: size of the file (bits)
- N: number of peers that want the file (excluding the original server)
- u_s: server upload capacity (bits/sec)
- u_i: upload capacity of peer i (bits/sec)
- d_i: download capacity of peer i (bits/sec)
- d_min = min{d_1, ..., d_N}

Figure: a simplified BitTorrent-like swarm where peers exchange chunks (see image).

### Client–server baseline

In the client–server model the server must supply every byte of the file to each of the N peers; peers do not assist in distribution. Two lower bounds on the distribution time follow directly from resource limits:

- Server upload bound: the server must send NF bits in total, so the distribution time is at least NF/u_s.
- Bottleneck receiver bound: the slowest peer cannot finish faster than F/d_min.

Combining these bounds gives a lower bound on the distribution time D_cs:

$$
D_{cs} \ge \max\left\{\frac{NF}{u_s},\;\frac{F}{d_{min}}\right\}.
$$

For analysis and comparison we take the lower bound as the (approximate) distribution time:

$$
D_{cs} = \max\left\{\frac{NF}{u_s},\;\frac{F}{d_{min}}\right\}. \qquad(2.1)
$$

When N is large the server upload term dominates and the distribution time grows linearly with N (poor scalability).

### P2P (swarm) model

In a P2P swarm peers both download and upload: once a peer has chunks it can upload them to others. A useful lower bound on the distribution time D_p2p uses three constraints:

1) Server must supply at least one full copy of the file to the swarm: time ≥ F/u_s.
2) Slowest peer bound: time ≥ F/d_min.
3) Aggregate upload capacity bound: the swarm (server + peers) together must supply NF bits; with total upload U_total = u_s + sum_{i=1}^N u_i, the time is at least NF / U_total.

Combining these three gives the P2P lower bound:

$$
D_{p2p} \ge \max\left\{\frac{F}{u_s},\;\frac{F}{d_{min}},\;\frac{NF}{u_s+\sum_{i=1}^N u_i}\right\}. \qquad(2.2)
$$

Again we use the lower bound as a practical estimate:

$$
D_{p2p} = \max\left\{\frac{F}{u_s},\;\frac{F}{d_{min}},\;\frac{NF}{u_s+\sum_{i=1}^N u_i}\right\}. \qquad(2.3)
$$

Key intuition:

- If peers collectively contribute significant upload capacity (\sum u_i large), the NF term is divided across many uploaders and distribution time can remain small even for large N.
- The first term (F/u_s) captures the need for the server to inject at least one copy into the system; the second term (F/d_min) captures the slowest receiver; the third term captures aggregate supply vs demand.

### Limiting cases and examples

- If peers have negligible upload (\sum u_i ≈ 0), P2P reduces to client–server and D_p2p ≈ NF/u_s.
- If peer upload dominates (\sum u_i ≫ u_s), the NF/(u_s+∑u_i) term ≈ NF/∑u_i ≈ F·N/∑u_i, which can be much smaller than NF/u_s — this is the scalability benefit of P2P.
- Example: server u_s = 10 Mbps, each of N=100 peers has u_i = 1 Mbps and sufficient download; then U_total = 10 + 100 = 110 Mbps, so NF/U_total ≈ 100·F/110 ≈ 0.91·F (i.e., close to one file-time), while client-server would require 100·F/10 = 10·F (ten times longer).

### Practical considerations (beyond the simple model)

- Chunking and rarepiece selection: protocols like BitTorrent split files into chunks and use piece selection to improve availability and parallelism.
- Incentives and tit‑for‑tat: real P2P systems use incentive mechanisms to encourage peers to upload (share) rather than free‑ride.
- Churn: peer arrival/ departure affects availability; protocols add redundancy and replication strategies to tolerate churn.
- NAT/firewall traversal: peers behind NATs may need STUN/relay mechanisms (TURN) to participate fully.
- Network fairness and ISP constraints: P2P traffic may be shaped or deprioritized by ISPs.

### Summary

The simple model above shows why P2P scales: as long as peers contribute upload bandwidth, the system's aggregate upload grows roughly with N, preventing the server from becoming the bottleneck. The three-term lower bound (server injection, slowest receiver, aggregate upload) gives a compact way to compare deployment scenarios.

## Reference

[1] James F. Kurose, Keith W. Ross. Computer Networking: A Top-Down Approach, 6th ed.

