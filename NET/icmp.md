# Internet Control Message Protocol (ICMP)

[TOC]

This note summarizes ICMP: its purpose, message format, common message types (Echo, Destination Unreachable, Time Exceeded, Redirect, Router Advertisement/Discovery), use cases (ping, traceroute, router discovery), Mobile IP extensions referenced in some texts, security considerations, and troubleshooting tips. The content is adapted from Kurose & Ross (A Top‑Down Approach) and organized for practical clarity.

## Purpose and role

ICMP (Internet Control Message Protocol) is used by IP hosts and routers to report errors and provide operational information about the network. ICMP is not used to exchange application data; instead it carries control messages such as "destination unreachable" or "time exceeded" that help diagnose and manage the network.

Common uses:

- Echo Request/Reply (ping) for reachability and basic RTT measurement.
- Time Exceeded for traceroute-style path discovery.
- Destination Unreachable to signal routing or delivery problems.
- Redirect messages to suggest a better first-hop router.
- Router Advertisement/Discovery for hosts to learn local routers (and for some Mobile IP scenarios).

## ICMP message format (IPv4)

An ICMP message typically includes:

- Type (8 bits): identifies the message type.
- Code (8 bits): refines the meaning of the type.
- Checksum (16 bits): covers the ICMP message and payload.
- Rest of header (32 bits): type‑dependent fields (for example, identifier/sequence for Echo messages, MTU in fragmentation needed messages, or unused fields).

Some ICMP messages carry a portion of the original IP datagram (header + leading data) so the sender can correlate the error with a particular packet.

## Important ICMP types (selected)

- Type 0 / 8 — Echo Reply (0) / Echo Request (8): used by the ping utility to test reachability and measure round‑trip time.
- Type 3 — Destination Unreachable: codes indicate reasons (network unreachable, host unreachable, protocol unreachable, port unreachable, fragmentation needed and DF set, etc.).
- Type 4 — Source Quench (deprecated): historically used to request rate reduction; not recommended.
- Type 5 — Redirect: ask the host to use a different router for a destination.
- Type 11 — Time Exceeded: used by traceroute and when a packet's TTL expires in transit.
- Type 12 — Parameter Problem: malformed header fields.
- Type 13 / 14 — Timestamp / Timestamp Reply: time synchronization/testing (rare today).
- Router Discovery/Advertisement (Types 9/10 in older RFCs, or ICMP Router Advertisement/ICMP Router Solicitation): used by hosts to discover local routers. Some texts include Mobile IP extensions that add fields such as Home/Foreign agent bits and care‑of addresses; these are protocol extensions rather than core ICMP functionality.

## Tools and examples

- ping: sends ICMP Echo Requests and reports loss and RTT statistics.
- traceroute (Linux) / tracert (Windows): uses TTL manipulation and ICMP Time Exceeded replies (or UDP/TCP probes depending on implementation) to discover the path to a destination.

Examples:

- ping example: `ping -c 4 example.com` reports packet loss and round‑trip times.
- basic traceroute: `traceroute example.com` (Linux) shows routers along the path by collecting ICMP Time Exceeded messages.

## Mobile IP notes (router advertisement with mobility extensions)

Some references (including older discussion in textbooks) describe ICMP router discovery messages extended to carry mobility information for Mobile IP. Those extensions may include bits and fields such as:

- Home agent (H) and Foreign agent (F) bits to indicate agent roles.
- Registration required (R) bit to indicate whether mobile nodes must register with the foreign agent.
- Encapsulation bits (M, G) describing encapsulation behavior.
- Lists of care‑of addresses (COA) provided by a foreign agent so mobile nodes can select a COA when registering with their home agent.

These mobility extensions are historically interesting but are not part of the ICMP core used for routine network diagnostics. If you are documenting Mobile IP specifically, include the relevant RFCs and note that modern deployments of mobility tend to use other mechanisms.

## Security considerations

- ICMP can be abused for reconnaissance (ping sweeps) or reflection/amplification attacks. Network operators commonly rate‑limit ICMP and filter unnecessary ICMP types at network boundaries.
- Blocking all ICMP is not recommended: some ICMP types (Destination Unreachable, Fragmentation Needed) are necessary for correct IP operation (PMTUD relies on ICMP Fragmentation Needed messages unless using robust alternatives).
- Use ingress/egress filtering, rate limiting, and selective blocking (allow essential types) instead of blanket deny policies.

## Troubleshooting tips

- Use `ping` to verify basic reachability and measure RTT and packet loss.
- Use `traceroute` or `tracert` to identify where packets are being dropped along a path.
- Inspect ICMP replies in packet captures (tcpdump/Wireshark) to see the embedded original IP header and identify which flow triggered the error.

## References

[1] James F. Kurose and Keith W. Ross. Computer Networking: A Top‑Down Approach. 6th ed.
[2] RFC 792 — Internet Control Message Protocol (ICMP)
