# CHAPTER 7 Key Length

[TOC]



## SYMMETRIC KEY LENGTH

One of the consequences of the second law of thermodynamics is that a certain amount of energy is necessary to represent information. To record a single bit by changing the state of a system requires an amount of energy no less than $kT$, where $T$ is the absolute temperature of the system and $k$ is the Boltzman constant.



## PUBLIC-KEY KEY LENGTH

### DNA Computing

By definition, an instance of any **NP-complete** problem can be transformed, in polynomial time, into an instance of any other **NP-complete** problem, and therefore into an instance of the directed Hamiltonian path problem.



## COMPARING SYMMETRIC AND PUBLIC-KEY KEY LENGTH

A system is going to be attacked at its weakest point. If you are designing a system that uses both symmetric and public-key cryptography, the key lengths for each type of cryptography should be chosen so that it is equally difficult to attack the system via each mechanism.



## BIRTHDAY ATTACKS AGAINST ONE-WAY HASH FUNCTIONS

There are two brute-force attacks against a one-way hash function. The first is the most obvious: Given the hash of message, $H(M)$, an adversary would like to be able to create another document, $M'$, such that $H(M) = H(M')$. The second attack is more subtle: An adversary would like to find two random messages, $M$, and $M'$, such that $H(M) = H(M')$. This is called a **collision**, and it is a far easier attack than the first one.

