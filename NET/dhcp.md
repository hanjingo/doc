
# DHCP (Dynamic Host Configuration Protocol)

[TOC]

This note summarizes DHCP fundamentals with a practical focus: how clients obtain network configuration, key message types and fields, lease management, common deployment modes (server, relay), brief notes on DHCPv6, security considerations, and troubleshooting tips. Content and terminology follow Kurose & Ross (A Top‑Down Approach).

## What DHCP does

DHCP automates the assignment of IP addresses and other network configuration parameters (subnet mask, default gateway, DNS servers, etc.) to hosts. DHCP evolved from BOOTP and adds dynamic lease management and richer option encoding.

Primary goals:

- Let clients obtain IP configuration automatically when they join a network.
- Support dynamic allocation (leases) and renewal to reuse address pools.
- Provide a flexible mechanism to convey configuration via options.

## Basic DORA message exchange (IPv4)

The common sequence between a client and server is called DORA:

1. DHCPDISCOVER — client broadcasts to locate available DHCP servers.
2. DHCPOFFER — server replies with an offer that includes an IP, lease time, and options.
3. DHCPREQUEST — client requests the selected offer (broadcast or unicast).
4. DHCPACK — server acknowledges and commits the lease; DHCPNAK on failure.

This exchange uses UDP: client port 68, server port 67. The initial DISCOVER/REQUEST may be broadcast because the client has no address yet.

![dhcp_cs_interaction](res/dhcp_cs_interaction.png)

Figure: client–server DHCP interaction (DORA).

## Packet fields and key options

DHCP messages are carried in UDP and share a header with BOOTP. Important fields include:

- op, htype, hlen, hops — basic BOOTP header fields.
- xid — transaction identifier used to match requests and replies.
- ciaddr, yiaddr, siaddr, giaddr — client, your (offered) address, server, and gateway (relay) addresses.
- chaddr — client hardware (MAC) address.
- options — variable-length field carrying DHCP options (option 53 = message type, option 50 = requested IP, option 51 = lease time, option 54 = server identifier, option 82 = relay agent information, etc.).

Common options convey subnet mask, router (gateway), DNS servers, domain name, NTP servers, and vendor‑specific information.

## Lease lifecycle and timers

A DHCP lease associates an IP address with a client for a finite time. Typical fields and timers:

- Lease time (option 51): how long the client may use the address before renewal.
- T1 (renewal) — fraction of lease (commonly 50%): client attempts unicast renewal with the leasing server.
- T2 (rebinding) — later fraction (commonly 87.5%): if renewal fails, client broadcasts to any server to rebind before lease expiry.

If the client fails to renew or rebind before the lease expires, it must stop using the address (and typically returns to the initialization state to obtain a new lease).

## Allocation modes

- Dynamic allocation: server assigns an address from a pool for a limited lease period (most common).
- Automatic allocation: server permanently assigns a specific address to a client but records the mapping (similar to reserved dynamic assignment).
- Static/manual allocation: administrator configures an IP-to-MAC mapping in the server (often called DHCP reservation).

## DHCP relay (agent) and GIADDR

Routers typically do not forward broadcasts across subnets, so a DHCP relay agent (often a router with DHCP relay enabled) forwards client broadcasts to a DHCP server on another subnet. The relay sets the giaddr (gateway IP) field to the client's subnet address so the server can select an appropriate pool and return replies via the relay.

DHCP relay also supports option 82 (agent information) to carry relay-specific metadata.

## DHCPv6 (brief)

DHCPv6 serves IPv6 with protocol differences (uses UDP ports 546 client / 547 server) and a different message format. IPv6 also supports Stateless Address Autoconfiguration (SLAAC) via Router Advertisements; DHCPv6 is commonly used to provide additional configuration (DNS, NTP) or stateful address assignment when SLAAC is insufficient.

## Security and operational considerations

- DHCP spoofing: an attacker can run a rogue DHCP server and hand out malicious configuration. Mitigations include DHCP snooping on switches, port security, and network segmentation.
- DHCP starvation: attackers exhaust the pool by requesting many addresses; DHCP snooping and rate limits can help.
- Authentication: standard DHCP lacks strong authentication; network access control (802.1X) or IPSec/PKI solutions are needed for secure provisioning.
- Logging and monitoring: track lease activity and unusual patterns to detect issues.

## Troubleshooting tips

- If clients fail to get an address, check DHCP server/service status and address pool exhaustion.
- Verify relay (giaddr) configuration on routers when clients and servers are on different subnets.
- Use packet traces (tcpdump/Wireshark) to observe DHCPDISCOVER/OFFER/REQUEST/ACK and check options and transaction ID (xid) matching.
- Confirm no IP conflicts (static assignment overlaps) and check lease database for stale entries.

## References

[1] James F. Kurose and Keith W. Ross. Computer Networking: A Top‑Down Approach. 6th ed.

