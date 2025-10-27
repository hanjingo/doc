
# Domain Name System (DNS)

[TOC]

This note summarizes the DNS architecture and protocol: message format, resource records, name resolution process (recursive vs. iterative), caching and TTLs, server roles (root, TLD, authoritative), delegation, a brief note on DNSSEC, and practical troubleshooting tips. The content follows Kurose & Ross (A Top‑Down Approach) and is reorganized for clarity.

## What DNS provides

DNS is a distributed, hierarchical database and an application‑layer protocol that maps human‑friendly names (hostnames) to resource records (most commonly IP addresses). Beyond address resolution, DNS supports services such as mail exchanger records (MX), service discovery (SRV), and other name‑dependent configuration via resource records.

Key uses:

- Hostname → IP address (A/AAAA records).
- Service discovery and load distribution (SRV, multiple A records).
- Delegation of name space across administrators (zones).

## Message format and sections

![dns_msg_fmt](res/dns_msg_fmt.png)

DNS messages (queries and responses) have a fixed header followed by four sections: Question, Answer, Authority, and Additional. Important header fields:

- ID (16 bits): query identifier used to match responses to queries.
- Flags: QR (query/response), Opcode, AA (authoritative answer), TC (truncated), RD (recursion desired), RA (recursion available), RCODE (response code).
- Counts: QDCOUNT, ANCOUNT, NSCOUNT, ARCOUNT indicate the number of entries in each section.

Sections:

- Question section: queried name, type (A, AAAA, MX, NS, CNAME, etc.), and class (IN for Internet).
- Answer section: resource records (RRs) that answer the question. Each RR contains (NAME, TYPE, CLASS, TTL, RDATA).
- Authority section: RRs pointing to authoritative name servers for the zone (NS records, SOA).
- Additional section: helpful RRs (e.g., A records for name servers listed in Authority) to reduce extra lookups.

Notes:

- A reply may contain multiple answers (e.g., multiple A records for load balancing).
- Truncation (TC) indicates the UDP response was too large; the client may retry over TCP.

## Resource records (RRs)

Common RR types:

- A / AAAA — IPv4 / IPv6 address records.
- NS — authoritative name server for a zone.
- CNAME — canonical name (alias) pointing to another name.
- MX — mail exchanger (priority + hostname).
- SOA — start of authority, contains zone metadata and serial numbers.
- TXT, SRV, PTR — various text, service, and reverse lookup records.

Each RR has a TTL field that controls caching lifetime for resolvers and caches.

## Resolution process: recursive vs iterative

There are two common resolution behaviors:

- Recursive resolution (usual for stub resolvers): the client asks a local resolver (often provided by the OS or ISP) to resolve a name; the resolver performs the necessary queries on behalf of the client until a final answer is found.
- Iterative (or non‑recursive) resolution: a DNS server may reply with a referral to other name servers (e.g., root returns TLD servers), and the requester repeats queries toward those servers.

Typical flow for a resolver starting from the root:

1. Query root servers → get referral to TLD servers.
2. Query TLD servers → get referral to authoritative servers for the domain.
3. Query authoritative server → receive final answer (or referral / NXDOMAIN).

Caching at each step (with TTLs) reduces load and latency for repeated queries.

## Hierarchy, delegation, and servers

![dns_serv_hierarchy](res/dns_serv_hierarchy.png)

Server roles:

- Root servers: the global entry points for the DNS hierarchy; return referrals to TLD servers.
- TLD servers: manage top‑level domains (.com, .org, .cn, etc.) and delegate subdomains to authoritative servers.
- Authoritative servers: provide definitive answers for zones they host (primary/master and secondary/slave servers used for redundancy).

Delegation is performed using NS records at the parent zone and glue records (A/AAAA) when the name server's name is inside the delegated zone.

## Caching and TTLs

Resolvers and authoritative servers cache records according to the TTL present in RRs. Lower TTLs reduce cache staleness but increase query load; higher TTLs reduce load but delay propagation of changes. Zone administrators choose TTLs based on update frequency and performance tradeoffs.

## DNSSEC (brief)

DNSSEC adds origin authentication and integrity for DNS data using digital signatures (RRSIG) and public keys (DNSKEY). DNSSEC prevents certain attacks such as cache poisoning by allowing resolvers to validate that records are authentic and unmodified. DNSSEC does not provide confidentiality.

## Operational notes and common issues

- UDP vs TCP: DNS primarily uses UDP for queries; large responses or zone transfers use TCP.
- Message size and EDNS(0): EDNS extends UDP payload size and adds features; large DNSSEC responses often require EDNS/TCP fallback.
- Glue records: required when an authoritative name server's name is inside the delegated child zone.
- Reverse DNS: PTR records map IP → name; usually managed separately by IP block owners.

Troubleshooting tips:

- Use dig or nslookup to query specific servers and inspect flags, answer/authority/additional sections, and TTLs.
- Check serial numbers in SOA to confirm zone propagation between master and slaves.
- Verify glue records when delegation causes resolution failures.
- Monitor for unusual NXDOMAIN or SERVFAIL responses and check DNSSEC validation errors when DNSSEC is enabled.

## References

[1] James F. Kurose and Keith W. Ross. Computer Networking: A Top‑Down Approach. 6th ed.
