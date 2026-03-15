English | [中文版](arp_zh.md)

# ARP Protocol

[TOC]

`ARP (Address Resolution Protocol)` is used to map IP addresses to MAC addresses.

## ARP Frame Format

| DST  | SRC  | Length/Type | Hardware Type | Protocol Type | Hardware Size | Protocol Size | Op   | Sender Hardware Addr | Sender Protocol Addr | Target Hardware Addr | Target Protocol Addr | Padding | FCS  |
| ---- | ---- | ----------- | ------------- | ------------- | ------------- | ------------- | ---- | ------------------- | ------------------- | ------------------- | ------------------- | ------- | ---- |
| 6    | 6    | 2           | 2             | 2             | 1             | 1             | 2    | 6                   | 4                   | 6                   | 4                   | 18      | 4    |

- MAC (Ethernet) header:
	- DST: Destination address, all host bits set to 1 means broadcast address.
	- SRC: Source address
	- Length/Type: Identifies the type of data that follows. For ARP, this field is 0x0806.

- Fixed size:

	- Hardware Type: Type of hardware address.
		- 1 means Ethernet address
	- Protocol Type: Type of protocol address to map.
		- 0x0800 means IP address
	- Hardware Size: Hardware address length (bytes). For ARP, this field is 6.
	- Protocol Size: Protocol address length (bytes). For ARP, this field is 4.
	- Op: Operation field.
		- 1: ARP request
		- 2: ARP reply
		- 3: RARP request
		- 4: RARP reply

- Variable size:
	- Sender hardware address
	- Sender protocol address
	- Target hardware address
	- Target protocol address
- Padding (not to scale)
- FCS


## ARP Command

```sh
arp 
```

- `-a` Show all entries in the ARP cache
- `-d` Delete an entry from the ARP cache
- `-s` Add an entry to the ARP cache


## ARP Proxy

If an ARP request is sent from a host on one network to a host on another network, the router connecting the two networks can answer the request. This process is called delegated ARP or ARP proxy.
