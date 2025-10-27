
# Firewall

[TOC]

This note summarizes firewall concepts and common deployment patterns: goals and placement, basic types (packet filter, stateful, application proxy), policy examples, interactions with NAT, logging/monitoring, and a brief note on modern (next‑generation) firewalls. The content is condensed from Kurose & Ross (A Top‑Down Approach) and organized for quick reference.

## What is a firewall?

A firewall is a combination of hardware and software that enforces a network security policy by controlling traffic between trust boundaries (for example, between an internal LAN and the Internet). It inspects traffic and either permits or blocks connections based on configured rules. The three canonical firewall goals are:

- All traffic between protected and untrusted networks passes through the firewall (single choke point).
- Only authorized traffic, as defined by local policy, is allowed.
- The firewall itself is hardened against attacks.

![firewall](res/firewall.png)

Figure: firewall placement between an administered network and the outside world.

## Common firewall types

1. Packet filter (stateless)

- Examines headers of individual IP packets and makes allow/deny decisions based on fields such as source/destination IP, protocol (TCP/UDP/ICMP), source/destination ports, and TCP flags (SYN, ACK).
- Fast and simple; commonly implemented in routers and early firewalls.
- Lacks context about connection state — rules are applied per packet.

2. Stateful inspection (stateful packet filter)

- Tracks connection state (e.g., TCP handshakes) and allows packets that belong to permitted, established flows.
- Enables policies like “allow established responses to internal connections” while blocking unsolicited inbound attempts.
- Balances performance and security for many use cases.

3. Application‑layer gateway (proxy / application firewall)

- Proxies traffic at the application layer: the firewall terminates the client connection and initiates its own connection to the server, inspecting payload (HTTP, FTP, DNS) and enforcing application‑specific policies.
- Provides fine‑grained control and deep protocol validation but introduces processing overhead and may require application‑specific configuration.

4. Next‑Generation Firewalls (NGFW)

- Combine traditional stateful filtering with features such as application awareness (identify applications regardless of port), intrusion prevention (IPS), URL filtering, and integration with identity systems.

## Policy model and rule examples

Firewall rules are typically ordered and evaluated top‑to‑bottom; the first matching rule determines the action (permit/deny). A minimal policy example for an office network:

- Allow outbound TCP/UDP from internal subnets to the Internet (establishing connections).
- Allow inbound responses for established connections (stateful inspection).
- Deny inbound connections to internal hosts except for explicitly published services (e.g., web server on DMZ).

Example packet‑filter rule fields:

- action: permit/deny
- src_ip, src_port, dst_ip, dst_port
- protocol (TCP/UDP/ICMP)
- interface or zone (which ingress/egress interface applies)

Best practices:

- Default deny (deny by default, explicitly allow required flows).
- Keep rules minimal and specific (avoid overly broad allow rules).
- Organize rules by purpose and document rationale to simplify audits.

## Placement patterns and DMZs

- Single firewall at network edge (simple deployments).
- Two‑firewall DMZ: one firewall separates the Internet from the DMZ, the second separates the DMZ from the internal network — used to host public services while protecting internal hosts.
- Host‑based firewalls: software firewalls on end hosts add an extra layer of defense.

![firewall_gate](res/firewall_gate.png)

Figure: combined application gateway and packet filter placement.

## Interaction with NAT and connection tracking

- Many firewalls perform Network Address Translation (NAT) to map internal private addresses to public IPs. NAT and stateful tracking must cooperate: the firewall keeps NAT mapping and connection state so return traffic can be properly forwarded.
- Port forwarding (DNAT) is used to expose specific internal services to the Internet while keeping other hosts protected.

## Logging, monitoring and auditing

- Log denied and suspicious traffic; monitor for unusual patterns (port scans, repeated failed connection attempts).
- Export logs to a centralized system (SIEM) for correlation and alerting.
- Keep rule change history and use automated tools to detect redundant or shadowed rules.

## Limitations and evasion techniques

- Firewall cannot protect against attacks carried over allowed protocols (e.g., malware over HTTPS) without deeper inspection.
- Encrypted traffic (TLS) limits payload inspection; solutions include TLS interception (proxying) or endpoint controls.
- Attackers can attempt to tunnel disallowed protocols over allowed ones; application awareness and content inspection mitigate this.

## Troubleshooting tips

- If a flow is blocked, test with packet captures on both sides of the firewall to see where drops occur.
- Check rule ordering and explicitly look for matching rules and hit counts.
- Verify NAT and port forwarding rules when external clients cannot reach published services.

## References

[1] James F. Kurose and Keith W. Ross. Computer Networking: A Top‑Down Approach. 6th ed.
