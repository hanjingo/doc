# User Datagram Protocol (UDP)

[TOC]

UDP is a simple, connectionless, datagram‑oriented transport protocol that preserves message boundaries and provides minimal services: multiplexing via ports and an optional checksum. Because UDP is lightweight and offers no built‑in reliability, applications using UDP (DNS, VoIP, streaming, DNS, some VPNs, NAT traversal) implement their own reliability, ordering, or retransmission logic when needed.

## UDP datagram and encapsulation

![udp_ipv4_pack](res/udp_ipv4_pack.png)

A UDP datagram is carried in the payload of an IP datagram (IPv4 or IPv6). The UDP header immediately follows the IP header (or the last IPv6 extension header).

### UDP header (IPv4 / IPv6)

![udp_head_ipv4](res/udp_head_ipv4.png)

- Source Port (16 bits) — optional (0 indicates no source port).
- Destination Port (16 bits) — identifies the receiving application.
- Length (16 bits) — length of UDP header + data in bytes (minimum 8 for UDP).
- Checksum (16 bits) — optional in IPv4 (but recommended); mandatory in IPv6. The checksum covers a pseudo‑header (from IP), the UDP header, and the payload.

The checksum pseudo‑header includes source and destination IP addresses, protocol number, and UDP length. If the payload length is odd, a padding zero byte is appended for checksum calculation; the pad byte is not transmitted.

![udp_checksum](res/udp_checksum.png)

IPv6 UDP header layout is similar (image: `res/udp_head_ipv6.png`); IPv6 requires checksums and supports larger payloads via jumbograms.

## Behavior and semantics

- Connectionless: there is no handshake or connection state at the transport layer.
- Message boundaries: each send corresponds to one datagram; recv returns a single datagram (or a truncated datagram if the application buffer is smaller than the datagram).
- Best‑effort delivery: UDP does not provide retransmission, ordering, congestion control, or flow control.

Applications choose UDP when low latency, multicast support, or simple request/response semantics are more important than built‑in reliability.

## Maximum datagram size and fragmentation

The theoretical maximum IPv4 datagram size is 65,535 bytes (16‑bit total length). With a 20‑byte IPv4 header and an 8‑byte UDP header, the maximum UDP payload is 65,507 bytes. IPv6 payload length and jumbograms can permit larger UDP datagrams when supported end‑to‑end.

In practice, path MTU limits (and intermediate MTU restrictions) make very large UDP datagrams fragile: IP fragmentation may occur, and some networks/firewalls drop fragments. Fragmentation complicates NATs and firewalls because the UDP header appears only in the first fragment.

Example (fragmentation):

![udp_ip_split](res/udp_ip_split.png)

Recommendation: use application‑layer fragmentation (chunking) or PMTUD to avoid IP fragmentation where possible.

## Teredo (IPv6 over UDP tunneling)

Teredo is a transition mechanism that encapsulates IPv6 datagrams inside UDP/IPv4 packets to allow IPv6 connectivity across IPv4 NATs. Teredo clients obtain an IPv6 address in the 2001::/32 prefix; the address encodes the Teredo server IPv4 and client’s mapped port/address (obfuscated) and flags that describe NAT behavior.

![udp_teredo](res/udp_teredo.png)

Teredo messages carry additional fields (origin indication, obfuscated mapped port/address) used to discover NAT mappings and to enable relays to forward traffic between Teredo and native IPv6 hosts.

![udp_teredo_ipv4](res/udp_teredo_ipv4.png)

Teredo is useful when no native IPv6 or simpler transition mechanism is available, but it adds complexity and potential performance costs.

## UDP‑Lite

UDP‑Lite (RFC 3828) is a variation of UDP intended for applications (audio, video) that can tolerate some payload corruption but cannot tolerate retransmission delays. UDP‑Lite allows the sender to indicate the number of payload bytes covered by the checksum (checksum coverage). Bytes beyond the coverage are not protected and may be delivered even if corrupted.

![udp_lite](res/udp_lite.png)

Use UDP‑Lite when partial checksum coverage improves application quality (e.g., media codecs that tolerate minor bit errors better than packet loss).

## Socket API and programming notes

- recvfrom()/sendto() preserve message boundaries; if the application passes a smaller buffer than the datagram, excess bytes are discarded (truncation).
- Applications must set appropriate socket buffer sizes (SO_RCVBUF/SO_SNDBUF) when expecting large or bursty datagrams.
- For high‑throughput/low‑latency UDP, consider using batching APIs (recvmmsg/sendmmsg) where available.

## Security and attacks involving UDP

UDP’s statelessness makes it attractive for several attack types:

- Amplification/magnification DDoS: small spoofed requests (e.g., to DNS, NTP, or memcached) can trigger larger responses toward a victim.
- Reflection attacks: attackers spoof a victim’s IP and send requests to UDP services that reply to the spoofed address.
- Fraggle and smurf: broadcasts or amplification combined with spoofing amplify traffic.
- Teardrop/overlapping fragment attacks: specially crafted fragments with overlapping offsets historically crashed some implementations.

Mitigations:

- Disable or restrict open resolvers and vulnerable services.
- Rate‑limit and filter suspicious traffic, block obvious spoofing at network edges (BCP 38 ingress filtering).
- Use application‑level verification and challenge‑response where appropriate.

## Maximum safe payload guidance

To be robust, prefer UDP payloads smaller than common path MTUs (e.g., 1200 bytes for IPv6/QUIC or ~1472 bytes for IPv4 UDP over Ethernet with 1500 MTU). For new application protocols consider using QUIC (reliable, congestion-controlled, but runs over UDP) which implements connection, retransmission, and multiplexing at user level.

## Attacks and operational notes (summary)

- DoS amplification — harden DNS/NTP servers and avoid responding to arbitrary addresses.
- NAT traversal — UDP works well with STUN/TURN/ICE; Teredo is a legacy fallback.
- Logging and troubleshooting — UDP is connectionless so inspect packet flows and correlate via 5‑tuple and timestamps.

## References

- RFC 768: User Datagram Protocol
- RFC 4380: Teredo: Tunneling IPv6 over UDP through NATs
- RFC 3828: UDP‑Lite for IP Multicast and Real‑Time Multimedia
- K. R. Fall, W. R. Stevens. TCP/IP Illustrated, Volume 1 (relevant sections on UDP/IPv4/IPv6)