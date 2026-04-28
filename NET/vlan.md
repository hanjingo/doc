# Virtual LAN (VLAN)

[TOC]



A Virtual LAN (VLAN) is a logical grouping of devices within a network that allows them to communicate as if they are on the same local network, even if they are physically connected to different switches.

## Types

### Access Link

Connects a VLAN-unaware end device (such as a PC) to a VLAN-aware switch. Frames transmitted over an access link are untagged and belong to a single VLAN.

### Trunk Link

Connects VLAN-aware devices such as switch-to-switch or switch-to-router links. It carries traffic from multiple VLANs using IEEE 802.1Q tagging.

### Hybrid Link

Supports both tagged and untagged frames on the same link. It is typically vendor-specific and not part of the IEEE 802.1Q standard.



## VLAN ID

### VLAN ID Cisco Standard

- VLAN 0 and VLAN 4095: Reserved VLAN IDs are defined by IEEE 802.1Q and used internally for protocol operations and cannot be configured or assigned to ports.
- VLAN 1 (Default VLAN): The default VLAN on Cisco switches and all switch ports are assigned to VLAN 1 by default. It cannot be deleted and is commonly used for control and management protocols such as STP, CDP, and VTP.
- VLAN 2 to VLAN 1001 (Normal VLAN Range): This range is used for regular VLAN configuration. VLANs in this range are fully configurable, editable, and delectable, and are stored in the switch’s VLAN database.
- VLAN 1002 to VLAN 1005: Reserved VLANs for legacy network technologies such as FDDI and Token Ring. These VLANs are predefined and cannot be removed, even if the technologies are no longer in use.
- VLAN 1006 to VLAN 4094 (Extended VLAN Range): Designed for large-scale networks requiring a high number of VLANs. VLANs in this range are stored in the `running configuration` and typically require the switch to operate in VTP transparent mode.



## Configuration

![vlan_config](res/vlan_config.png)



## References

[1] Kurose & Ross. Computer Networking: A Top‑Down Approach (VPN and IPsec sections)

[2] [Virtual LAN (VLAN)](https://www.geeksforgeeks.org/computer-networks/virtual-lan-vlan/)
