# Terminology

- Network designers organize protocols--and the network hardware and software that implement the protocols in layers. The protocols of the various layers are called the **protocol stack**.
- In a client-server architecture, there is an always-on host, called the **server**, which services requests from many other hosts, called **clients**.
- In a `P2P architecture`, there is minimal (or no) reliance on dedicated servers in data centers. Instead, the application exploits direct communication between pairs of intermittently connected hosts, called **peers**.
- A **Web cache**, also called a **proxy server** is a network entity that satisfies HTTP requests on behalf of an origin Web server. The Web cache has its own disk storage and keeps copies of recently requested objects in this storage.
- TCP provides flow control by having the sender maintain a variable called the **receive window**. 
- The maximum amount of data that a link-layer frame can carry is called the **maximum transmission unit (MTU)**. 
- Before encrypting the message (or the stream of data), the sender generates a random $k$-bit string, called the **Initialization Vector (IV)**. 
- Before sending IPsec datagrams from the source entity to the destination entity, the source and destination entities create a network-layer logical connection. This logical connection is called a **security association (SA)**.
- IPsec has two different packet forms, one for the so-called **tunnel mode** and the other for the so-called **transport mode**.

