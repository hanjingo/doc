 # Network Address Translation (NAT)

 [TOC]

 ![nat_example](res/nat_example.png)

 Network Address Translation (NAT) is a technique that allows a network device (usually a router or firewall) to rewrite IP addresses and optionally ports in packet headers as packets pass between two networks. NAT is most commonly used to map private (RFC 1918) addresses used in local networks to one or more public IPv4 addresses. This note summarizes common NAT types, how NAT works, its interaction with other protocols, common issues, and migration considerations for IPv6.

 ## Why NAT?

 - IPv4 address scarcity: NAT allows many hosts to share a small number of public IPv4 addresses.
 - Network isolation and simplified address management for private networks.
 - Policy enforcement and basic topology hiding: NAT can act as a primitive form of access control and conceal internal addressing.

 While NAT solved practical deployment problems for IPv4, it breaks the original end-to-end addressing model and introduces complications for some applications and protocols.

 ## Basic concepts

 - Inside (local) vs outside (global) addresses: NAT translates between internal (private) addresses and external (public) addresses.
 - Mapping: a NAT maintains a mapping table that associates an internal endpoint (IP:port) with an external address (and sometimes port).
 - Types of mappings: one-to-one (static), many-to-one (dynamic, often with port translation), and port-preserving vs port-assigning behaviors.

 ## Common NAT types

 - Static NAT (one-to-one): maps a specific internal IP to a specific external IP. Often used for servers that must be reachable from the public Internet.

 - Dynamic NAT (pool): translates internal addresses to a pool of public addresses on demand. When the pool is exhausted, new connections cannot be created.

 - Port Address Translation (PAT) / NAT overload / masquerading: many internal hosts share a single public address; translations use different external ports to distinguish flows. This is the most common home-router NAT behavior.

 - Destination NAT (DNAT): rewrites the destination IP (and optionally port) of incoming packets, commonly used for port forwarding to internal servers.

 - Source NAT (SNAT): rewrites the source IP of outgoing packets (often used in enterprise or cloud environments).

 - Hairpin NAT (NAT loopback): allows internal hosts to access an internal server using the public IP and have the NAT loop the traffic back inside.

 ## How NAT operates (simplified packet flow)

 1. Outbound packet from an internal host arrives at the NAT device.
 2. NAT consults its mapping table. If no mapping exists, it creates one according to its policy (static, dynamic, or PAT).
 3. NAT rewrites the source IP (and possibly source port) to the external address/port and forwards the packet to the outside network.
 4. Return packets arriving at the external address are matched against the NAT table; the NAT rewrites destination IP/port back to the internal endpoint and forwards the packet.

 Mappings usually include a timeout so that ephemeral entries are removed after inactivity. Long-lived inbound mappings (e.g., for servers) are typically static or explicitly configured.

 ## NAT and transport-level identifiers

 Because NAT may change ports, protocols that embed IP addresses/ports in the application payload (FTP, SIP, H.323, some VPNs) need special handling. Common mitigations:

 - Application-Level Gateways (ALGs): device components that inspect and rewrite application payloads to update embedded addresses/ports.
 - Protocol-aware proxies: terminate and re-establish sessions at the NAT.
 - Use of protocols that support NAT traversal (STUN, TURN, ICE) for peer-to-peer applications.

 ## NAT traversal techniques

 - STUN (Session Traversal Utilities for NAT): discovers the public mapping created by NAT; works with some NAT types but fails with symmetric NAT.
 - TURN (Traversal Using Relays around NAT): relays media through a public server; works reliably but consumes bandwidth on the relay.
 - ICE (Interactive Connectivity Establishment): coordinates candidate addresses (host, reflexive, relay) and attempts connectivity in order of preference.
 - UPnP and NAT-PMP: protocols that let hosts request port mappings from a local NAT device (common on consumer routers).

 ## Interaction with tunneling and VPNs

 NAT interacts with tunneling protocols in different ways:

 - IPsec in tunnel mode: NAT breaks authentication/integrity checks unless NAT-T (NAT Traversal) is used, which encapsulates ESP in UDP.
 - GRE and other tunnels: may require special handling (NAT traversal, port mapping) because tunnels encapsulate original headers.
 - When IP-in-IP or layer-2 tunnels traverse NAT, the outer headers must be translated; this can complicate path MTU discovery.

 ![nat_tunneling](res/nat_tunneling.png)

 ## Problems and limitations

 - Breaks end-to-end connectivity: inbound connections require explicit port forwarding or static mappings.
 - Port exhaustion: with PAT, a single IPv4 address only provides ~65k ports; real usable ports are fewer and can be exhausted under heavy NAT usage.
 - Application incompatibility: protocols embedding addresses in payload often fail without ALGs or proxies.
 - Performance and statefulness: NAT devices must maintain per-flow state, which adds memory and processing overhead and is a scalability concern for very large deployments.
 - Logging and traceability: NAT obscures original internal IPs in public logs unless translations are recorded.

 ## Security considerations

 - NAT provides a modest degree of address hiding, but it is not a security boundary. Relying on NAT alone for security is insufficient; firewall policies and access control are still required.
 - ALGs can introduce vulnerabilities if they are buggy; prefer endpoint-aware traversal (STUN/TURN/ICE) when possible.

 ## NAT and IPv6

 IPv6 was designed to restore end-to-end addressing and avoid the need for IPv4-style NAT. Recommended practices:

 - Prefer native IPv6 addressing without NAT when possible.
 - Use IPv6 Prefix Delegation and proper address planning instead of NAT.
 - For IPv4/IPv6 coexistence, various transition mechanisms exist (NAT64, DNS64, 464XLAT). NAT64 provides protocol translation between IPv6 clients and IPv4 servers by combining DNS64 and a stateful translator.

 ## Practical examples and configuration notes

 - Home router (PAT): a single public address with per-flow port translations. Outbound TCP/UDP flows are automatically mapped; inbound flows require static port forwarding.
 - Data center (SNAT/DNAT): cloud platforms often SNAT instances in private subnets to a set of public IPs and use DNAT/load-balancers for inbound traffic to services.

 When configuring NAT, consider mapping timeouts (short for UDP, longer for TCP), logging of mappings for auditing, and monitoring for port exhaustion.

 ## Troubleshooting checklist

 - Check mapping table on NAT device for expected entry.
 - Ensure required ports are forwarded for incoming services.
 - If an application uses embedded IPs, verify ALGs or use an application proxy.
 - For P2P issues, try STUN/ICE or enable UPnP/NAT-PMP if secure in your environment.

 ## References

 - Jim Kurose, Keith Ross, Computer Networking: A Top-Down Approach
 - RFC 3022: Traditional IP Network Address Translator (Traditional NAT)
 - RFC 2663: IP Network Address Translator (NAT)
 - RFC 6147, RFC 6146: NAT64/DNS64
