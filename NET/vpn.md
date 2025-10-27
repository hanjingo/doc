# Virtual Private Networks (VPNs)

[TOC]

![vpn](res/vpn.png)

VPNs (Virtual Private Networks) provide private, secure connectivity over shared/public networks. Organizations use VPNs to connect remote users to corporate resources (remote‑access VPNs) or to interconnect branch offices and data centers (site‑to‑site VPNs). This note summarizes common VPN technologies, how they secure traffic, and operational considerations.

## Why use a VPN?

- Confidentiality: encrypt traffic over untrusted networks.
- Integrity and authentication: verify peer identity and detect tampering.
- Remote access and network extension: enable users and sites to appear on a private network from anywhere.
- Policy enforcement and segmentation: apply access control and routing policies across administrative boundaries.

## VPN types — quick taxonomy

- IPsec VPNs (network‑layer): provide protection for IP datagrams (tunnel or transport mode). Widely used for site‑to‑site and remote‑access (with client software or gateways).
- SSL/TLS VPNs (transport/application layer): use TLS to secure application sessions (commonly used for remote access via browsers or thin clients). Examples: HTTPS‑based VPN portals, OpenVPN (TLS over UDP/TCP), and TLS‑based tunnels.
- MPLS VPNs (service‑provider): use provider MPLS to partition traffic into virtual routing/forwarding instances (VRFs); security is achieved by separation rather than encryption.
- WireGuard and modern user‑space VPNs: lightweight, modern cryptographic designs with simpler key models than traditional IPsec.

This note focuses on IPsec and TLS‑based VPNs (most common in Internet VPN deployments).

## IPsec — building blocks

IPsec provides security services at the IP layer via two main protocols:

- Authentication Header (AH): provides integrity and optional authentication of IP packets (does not provide confidentiality). AH is rarely used in practice because it does not work well with NAT.
- Encapsulating Security Payload (ESP): provides confidentiality (encryption), integrity, and optional authentication for IP payloads. ESP is the most commonly used IPsec protocol.

Security Associations (SAs): unidirectional agreement between peers specifying algorithms, keys, lifetimes, and mode. Two SAs (one per direction) are typically used for two‑way secure communication.

Modes:

- Transport mode: IPsec protects only the IP payload (useful for end‑host protection when both endpoints support IPsec).
- Tunnel mode: IPsec encapsulates the entire IP packet within a new IP header and protects the inner packet (commonly used between gateways for site‑to‑site VPNs).

Key management: Internet Key Exchange (IKEv1 / IKEv2) negotiates SAs, authenticates peers (PSK, certificates, or EAP), and establishes session keys. IKE operates in phases (IKEv2 simplified):

- IKE SA establishment (authentication and key exchange).
- Child SA creation (IPsec ESP/AH SAs for traffic protection).

IKE supports rekeying, SA lifetimes, and multiple authentication methods. IKEv2 is recommended over IKEv1 for modern deployments.

## NAT traversal and interoperability

- NAT breaks IPsec ESP in tunnel/ transport modes because ESP lacks ports and NAT rewrites IP addresses. Common solutions:
	- NAT‑T (NAT Traversal): encapsulate ESP in UDP (usually UDP/4500) so NAT devices can translate and maintain mappings.
	- Use IKE to detect NATs and switch to NAT‑T.
- IPsec with certificates and proper policy configuration helps interoperability across heterogeneous gateways and vendors.

## SSL/TLS VPNs (remote access and application proxies)

- TLS‑based VPNs (e.g., OpenVPN, stunnel, some browser portals) use the TLS record and handshake protocols to secure transport. They often operate over TCP or UDP and can traverse NATs and firewalls more easily than raw IPsec.
- Web‑based SSL VPN portals provide controlled access to web apps or launch client‑side tunnels for specific services. They are convenient for end users because they rely on standard TLS stacks (browser or client software).

Tradeoffs between IPsec and TLS VPNs:

- IPsec (network layer) protects all IP traffic transparently and integrates with routing; it is suitable for full‑network tunnels and site‑to‑site connections.
- TLS VPNs (transport/application layer) are easier to deploy through firewalls/NAT and are good for per‑application access or clientless web portals.

## Deployment patterns

- Site‑to‑site VPN: two gateways establish IPsec tunnels (often in tunnel mode) and exchange routing (static routes, BGP, or other protocols) over the secure tunnel.
- Remote‑access VPN: individual clients (laptops, phones) use IPsec or TLS clients to connect to a gateway and obtain protected access to internal networks. Authentication can use certificates, username/password, or multi‑factor approaches (EAP, OTP).
- Hub‑and‑spoke vs full mesh: hub‑and‑spoke reduces the number of tunnels but may add hop latency; full mesh provides direct tunnels between sites at higher management cost.

## Performance, scaling, and operational notes

- Encryption and packet processing add CPU overhead; hardware acceleration (AES‑NI, crypto accelerators) is beneficial for high throughput.
- MTU and path MTU discovery: IPsec encapsulation increases packet size; configure appropriate MTUs and avoid fragmentation (use MSS clamping on gateway for TCP flows).
- Monitoring and logging: collect SA lifetime metrics, rekeys, and authentication events; track throughput, latency, and packet loss across tunnels.

## Security considerations and best practices

- Use modern algorithms and protocols (IKEv2, strong cipher suites, AES‑GCM or ChaCha20‑Poly1305, and ECDHE for key exchange).
- Enforce certificate management and automate rotation (short lifetimes where practical).
- Disable obsolete or weak modes/ciphers (e.g., static RSA key transport without forward secrecy).
- Limit management plane exposure (admin interfaces), use strong authentication (MFA), and segment VPN users by role (least privilege).

## Troubleshooting checklist

1. Verify IKE negotiation and SA establishment (phase 1/phase 2 errors). Check for authentication errors, mismatched proposals, and expired certificates.
2. Check NAT presence: if NAT detected, ensure NAT‑T (UDP/4500) is enabled and port mappings allow traffic.
3. Check routing: ensure traffic selectors and remote subnets match policy; confirm that traffic is being routed into the tunnel.
4. Verify MTU/MSS behavior: if applications experience fragmentation or stalls, reduce MTU or enable MSS clamping on gateways.
5. Monitor rekey events and SA lifetimes: frequent rekeys may indicate clock skew or unstable connectivity.

## Alternatives and modern trends

- WireGuard: a modern VPN with simpler key management and efficient cryptography; easier to audit and often faster than legacy IPsec stacks.
- TLS‑based tunnels and application proxies continue to be popular for user access due to ease of NAT traversal and browser‑based options.

## References

- RFC 4301: Security Architecture for the Internet Protocol
- RFC 5996 / RFC 7296: IKEv2
- RFC 2401–2412: IPsec (historical foundational RFCs)
- WireGuard documentation and modern deployment guides
- Kurose & Ross. Computer Networking: A Top‑Down Approach (VPN and IPsec sections)

