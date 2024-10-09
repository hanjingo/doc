# CHAPTER9 Application Design and Development



Browsers use a standardized syntax, the `HyperText Markup Language (HTML)` standard, which supports both formatted display of information, and creation of forms-based interfaces.

A `uniform resource locator (URL)` is a globally unique name for each document that can be accessed on the Web.

A `Web server` is a program running on the server machine, which accepts requests from a Web browser and sends back results in the form of HTML documents.

The `common gateway interface (CGI)` standard defines how the Web server communicates with application programs.

`connectionless` is that most computers have limits on the number of simultaneous connections they can accommodate, and if a large number of sites on the Web open connections to a single server, this limit would be exceeded, denying service to further users.

The Java `servlet` specification defines an application programming interface for communication between the Web server and the application program.

An alternative approach, that of `server-side scripting`, provides a much easier method for creating many applications.

In `SQL injection` attacks, the attacker manages to get an application to execute an SQL query created by the attacker.

A Web site that allows users to enter text, such as a comment or a name, and then stores it and later displays it to other users, is potentially vulnerable to a kind of attack called a `cross-site scripting (XSS)` attack.

Many applications use `two-factor authentication`, where two independent `factor`(that is, pieces of information or processes) are used to identify a user.

A `single sign-on` system further allows the user to be authenticated once, and multiple applications can then verify the user's identity through an authentication service without requiring reauthentication.

The `Security Assertion Markup Language (SAML)` is a standard for exchanging authentication and authorization information between different security domains, to provide cross-organization single sign-on.

An `audit trail` is a log of all changes (inserts, deletes, and updates) to the application data, along with information such as which user performed the change and when the change was performed.

A good encryption technique has the following properties:

- It is relatively simple for authorized users to encrypt and decrypt data.
- It depends not on the secrecy of the algorithm, but rather on a parameter of the algorithm called the `encryption key`, which is used to encrypt data.
- Its decryption key is extremely difficult for an intruder to determine, even if the intruder has access to encrypted data.

The `Advanced Encryption Standard` (AES) is a symmetric-key encryption algorithm that was adopted as an encryption standard by the U.S. government in 2000 and is now widely used.

`Public-key encryption` is an alternative scheme that avoids some of the problems faced by symmetric-key encryption techniques. It is based on two keys: a `public key` and a `private key`.

Encryption of small values, such as identifiers or names, is made complicated by the possibility of `dictionary attacks`, particularly if the encryption key is publicly available.

Dictionary attacks can be deterred by adding extra random bits to the end of the value before encryption (and removing them after decryption). Such extra bits, referred to as an `initialization vector` in AES, or as `salt` bits in other contexts, provide good protection against dictionary attacks.

A more secure scheme involves a `challenge-response` system.

`Smart cards` provide a solution to this problem.

Another interesting application of public-key encryption is in `digital signatures` to verify the authenticity of data; digital signatures play the electronic role of physical signatures on documents.

Digital signatures also serve to ensure `nonrepudiation`.

Authentication can be handled by a system of `digital certificates`, whereby public keys are signed by a certification agency, whose public key is well known.



## Summary

TODO