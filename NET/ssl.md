## TLS / SSL — concise overview

[TOC]

![ssl](res/ssl.png)

Note: “SSL” historically refers to the Secure Sockets Layer. TLS (Transport Layer Security) is its modern successor; in most current contexts people use the term TLS even when they say “SSL.” This note uses the terms interchangeably but focuses on TLS concepts and practical behavior.

### What TLS provides

TLS provides three core security services to applications that run over TCP (most commonly HTTPS):

- Confidentiality — encrypts payloads to prevent passive eavesdropping.
- Integrity — ensures messages are not silently altered (using MACs or AEAD).
- Authentication — typically server authentication via X.509 certificates; optional client authentication.

TLS operates between the application layer and the transport layer (TCP) and exposes a socket-like API to applications.

### High-level structure

TLS is usually described in two logical layers:

- The Record Layer: fragments, compresses (optional), applies message authentication and encryption, and multiplexes higher-level protocol messages.
- The Handshake Protocol: negotiates version, cipher suite, authenticates peers, and establishes session keys.

### Handshake (simplified)

1. ClientHello: the client sends supported TLS versions, a list of cipher suites, and a random nonce.
2. ServerHello: the server selects TLS version and cipher suite and returns its random nonce.
3. Certificate: server sends its X.509 certificate chain (unless using PSK or anonymous cipher suites).
4. (Optional) ServerKeyExchange: when ephemeral key exchange is used (e.g., ECDHE), server provides key material.
5. (Optional) CertificateRequest: server may request client certificate.
6. ServerHelloDone.
7. ClientKeyExchange: client sends pre-master secret or key-exchange material; with ECDHE this conveys ephemeral public key.
8. (Optional) CertificateVerify: client proves possession of private key when client certificate was used.
9. Both sides compute master secret and derive symmetric keys.
10. Client and server send Finished messages encrypted with the negotiated keys to verify the handshake integrity.

Key points:

- Ephemeral Diffie–Hellman (DHE/ECDHE) provides forward secrecy: compromise of long-term keys does not recover past session keys.
- RSA key transport (older) is less favored today because it lacks forward secrecy.

### Cipher suites and primitives

Cipher suites specify the key-exchange algorithm, the symmetric encryption algorithm, and the MAC/AEAD mode. Example: ECDHE-RSA-AES128-GCM-SHA256 means ECDHE key exchange, RSA for authentication, AES-128 in GCM AEAD mode, and SHA-256 for certain PRFs.

Modern recommendations:

- Prefer TLS 1.2+ and TLS 1.3.
- Prefer AEAD ciphers (AES-GCM, CHACHA20-POLY1305).
- Prefer ECDHE for key exchange for forward secrecy.

### TLS versions and evolution

- SSLv2/SSLv3: obsolete and insecure.
- TLS 1.0/1.1: deprecated.
- TLS 1.2: widely deployed, supports AEAD via extensions.
- TLS 1.3: a substantial simplification of the handshake (fewer round trips), mandates forward secrecy, and removes many legacy options.

### Certificates and authentication

- Servers present X.509 certificate chains that a client validates: chain of trust to a trusted root CA, validity period, hostname matching, and revocation checks (CRL/OCSP).
- Certificate validation pitfalls: expired certs, mismatched hostnames, missing intermediate CA, and CRL/OCSP unavailability.
- Certificate pinning and short-lived certificates can reduce risk of CA compromise but require careful management.

### Session resumption and performance

- Session IDs (TLS <=1.2) and session tickets allow clients to resume prior sessions and avoid costly full handshakes.
- TLS 1.3 improves resumption (0-RTT) but 0-RTT introduces replay risks that must be considered for idempotent operations.

### TLS + HTTP = HTTPS

- Most web security depends on TLS for transport security; HTTPS uses TLS to secure HTTP semantics (headers, cookies, bodies).
- Practical considerations: HSTS, certificate chains, OCSP stapling, secure cookie flags, and ALPN (Application-Layer Protocol Negotiation) for choosing HTTP/2 or HTTP/3.

### Common pitfalls and attacks

- Man-in-the-middle (MITM) with forged certificates — mitigated by correct certificate validation and CA hygiene.
- Downgrade attacks — protocol/version/cipher negotiation must resist forced downgrades (TLS 1.3 and proper server config help).
- Insecure cipher suites or weak key sizes — enforce modern cipher selection.
- Misconfigured intermediaries (proxies, TLS-terminating load balancers) that mishandle certificates or break end-to-end security.

### Tools and diagnostics

- OpenSSL: `openssl s_client -connect host:443` to inspect certs and handshake.
- `ssllabs.com` or similar scanners for server configuration checks.
- Browser devtools show certificate chains and TLS details.

### Practical deployment notes

- Use TLS 1.3 where possible; support TLS 1.2 with modern cipher suites for older clients.
- Prefer HSTS, OCSP stapling, and secure default configurations (forward secrecy, AEAD ciphers).
- Monitor certificate expiry and automate renewal (Let's Encrypt / ACME).

## References

- RFC 8446: TLS 1.3
- RFC 5246: TLS 1.2
- Practical guides: OWASP TLS/SSL best practices, Mozilla TLS configuration recommendations.