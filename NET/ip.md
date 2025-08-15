# The Internet Protocol

[TOC]



IP is the workhorse protocol of the TCP/IP protocol suite. All TCP, UDP, ICMP, and IGMP data are transmitted as IP datagrams. IP provides a best-effort, connectionless datagram delivery service.

## IPv4

![ipv4_head_struct](res/ipv4_head_struct.png)

- `Version`, it contains the version number of the IP datagram: 4 for IPv4 and 6 for IPv6.
- `Internet Header Length (IHL)`, is the number of 32-bit words in the IPv4 header, including any options.
- `Differentiated Services Field (DSField)`
- `Explicit Congestion Notification (ECN)`
- `Total Length` is the total length of the IPv4 datagram in bytes.
- `Identification` helps identify each datagram sent by an IPv4 host.
- `Flags` 
- `Fragment Offset`
- `Time-to-Live(TTL)` sets an upper limit on the number of routers through which a datagram can pass.
- `Protocol` field in the IPv4 header contains a number indicating the type of data found in the payload portion of the datagram.
- `Header Checksum` field is calculated over the IPv4 header only.
- `Source IP Address` of the sender of the datagram.
- `Destination IP Address` of where the datagram is destined.
- `Options(If Any)` 
- `IP Data(If Any)`



## IPv6

### Headers

![ipv6_head_struct](res/ipv6_head_struct.png)

- `Version`. This 4-bit field identifies the IP version number.
- `DSField`. This 8-bit field is similar in spirit to the TOS field we saw in IPv4.
- `ECN`
- `Flow Label`. As discussed above, this 20-bit field is used to identify a flow of datagrams.
- `Payload Length`. This 16-bit value is treated as an unsigned integer giving the number of bytes in the IPv6 datagram following the fixed-length, 40-byte datagram header.
- `Next Header`. This field identifies the protocol to which the contents (data field) of this datagram will be delivered (for example, to TCP or UDP). The field uses the same values as the protocol field in the IPv4 header.
- `Hop Limit`. The contents of this field are decremented by one by each router that forwards the datagram. If the hop limit count reaches zero, the datagram is discarded.
- `Source IP Address`, `Destination IP Address`. The various formats of the IPv6 128-bit address are described in RFC 4291.



## Internet Checksum

The Internet checksum is a 16-bit mathematical sum used to determine, with reasonably high probability, whether a received message or portion of a message matches the one sent. Note that the Internet checksum algorithm is not the same as the common `cyclic redundancy check (CRC)`[PB61], which offers stronger protection.

When an IPv4 datagram is received, a checksum is computed across the whole header, including the value of the `Checksum` field itself. Assuming there are no errors, the computed checksum value is always 0 (a one's complement  of the value `FFFF`).

For example:

![ip_verify](res/ip_verify.png)



## Mobile IP

TODO



## Reference

[1] James F. Kurose, Keith W. Ross . COMPUTER NETWORKING: A Top-Down Approach . 6ED

