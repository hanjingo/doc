# Distributed Systems - Synchronization

[TOC]



This note summarizes clock synchronization, logical time, global states and related algorithms from chapter 14 of "Distributed Systems: Concepts and Design." It explains practical protocols (Cristian, Berkeley, NTP), logical clocks (Lamport and vector clocks), consistent global states, the Chandy–Lamport snapshot, and techniques for distributed debugging.

## Clocks, events and process states

Each machine has a local hardware clock; clocks differ due to *skew* (instantaneous difference) and *drift* (different ticking rates). These differences mean there is no single global physical time in a distributed system.

Key properties:

- A hardware clock $H$ is often modeled with a bound on drift $
ho>0$:
$$ (1 - \rho)(t' - t) \le H(t') - H(t) \le (1 + \rho)(t' - t). $$
- A weaker requirement is *monotonicity*: $t' > t \Rightarrow C(t') > C(t)$.

Clock faults include crashes (clock stops) and arbitrary failures (incorrect values).



## Synchronizing physical clocks

Two synchronization goals:
- *External synchronization*: synchronize clocks to a reference source (UTC) within bounds $D$: $|S(t) - C_i(t)| < D$.
- *Internal synchronization*: bound pairwise differences: $|C_i(t) - C_j(t)| < D$.

Practical algorithms:

- **Cristian's algorithm**: a client requests time from a time server, measures the round-trip $T_{round}$ and sets the local clock to $t + T_{round}/2$ where $t$ The server time in the reply. Accuracy depends on asymmetric network delays and a lower bound $min$ On one-way delay: the error bound is $\pm(T_{round}/2 - min)$.

- **Berkeley algorithm**: a coordinator polls other machines (slaves), estimates offsets using round-trip times, computes an average, and instructs slaves to adjust clocks. It does not rely on an external UTC source; it keeps clocks *close* to each other.

- **Network Time Protocol (NTP)**: a hierarchical, resilient protocol used on the Internet. NTP peers exchange timestamps to compute an offset $o_i$ and delay $d_i$. Using four timestamps $T_{i-3},T_{i-2},T_{i-1},T_i$ one can estimate:
  $$ d_i = T_{i-2} - T_{i-3} + T_i - T_{i-1}, $$
  $$ o_i = (T_{i - 2} - T_{i - 3} + T_{i - 1} - T_{i})/2, $$
  with $o_i - d_i/2 \le o \le o_i + d_i/2$ (so $d_i$ measures accuracy).

  ![ntp](res/ntp.png)

  *Messages exchanged between a pair of NTP peers*

NTP is robust to intermittent connectivity and provides authentication and algorithms to mitigate malicious or erroneous peers.



## Logical time and logical clocks

Physical clock synchronization is expensive and imperfect. Logical clocks capture ordering (causality) without synchronizing physical clocks.

### Happened-before relation (\(\rightarrow\))

- If two events occur in the same process and $e$ precedes $e'$, then $e \rightarrow e'$. 
- If $send(m)$ and $receive(m)$ are the send and receive events of a message $m$, then $send(m) \rightarrow receive(m)$.
- The relation is transitive.

### Lamport clocks

Each process $p_i$ maintains a counter $L_i$. Rules:

- LC1: increment $L_i$ before each event: $L_i := L_i + 1$.
- LC2: piggyback $L_i$ on outgoing messages; on receive, set $L_j := \max(L_j, t)$ and then increment.

Lamport timestamps satisfy: $e \rightarrow e' \Rightarrow L(e) < L(e')$, but the converse does not hold.

![lamport_timestamp](res/lamport_timestamp.png)

*Lamport timestamps for the events shown in above figure*

### Vector clocks

Vector clocks provide a stronger ordering. Each process $p_i$ keeps vector $V_i[1..N]$:

- VC1: initially all zeros.
- VC2: before the local event, $V_i[i] := V_i[i] + 1$.
- VC3: piggyback $V_i$ on messages.
- VC4: on receive, $V_i[j] := \max(V_i[j], t[j])$ for all components.

Vector clocks can determine concurrency: $V(e) < V(e')$ iff $e \rightarrow e'$. If neither $V(e) \le V(e')$ nor $V(e') \le V(e)$, events are concurrent.

![vector_timestamp](res/vector_timestamp.png)

*Vector timestamps for the events*



## Global states and consistent cuts

A *cut* collects prefixes of each process's event history. A cut is *consistent* if it contains no event without also containing all events that happened before it. A consistent cut corresponds to a feasible global state.

We model execution as a sequence of global states $S_0 \rightarrow S_1 \rightarrow \dots$ and linearizations (total orders consistent with local orders) that pass only through consistent global states.

### The Chandy–Lamport snapshot algorithm

Goal: record a consistent global state (process states and in-transit messages) without stopping normal execution. Assumptions: reliable FIFO channels and no failures during the snapshot.

Algorithm outline:

1. Any process may initiate: it records its local state and sends a special *marker* on all outgoing channels.
2. On receiving a marker for the first time on an incoming channel, a process records its local state, records the channel state for that channel as empty, and then forwards markers on all outgoing channels.
3. For any subsequent marker received on an incoming channel, the process records as the channel state all messages received on that channel since it recorded its local state and before receiving the marker.

The snapshot result is a consistent cut: channel states include messages that were sent but not yet received at the time of the cut.

### Uses of snapshots

- Detecting distributed deadlocks or termination.
- Distributed garbage collection and global invariants.
- Checkpointing and recovery (consistent checkpoints).



## Distributed debugging: possibly and definitely predicates

Given a global predicate $\phi$ In states, we define:

- *Possibly $\phi$*: there exists a consistent global state reachable in some linearization where $\phi$ is true.
- *Definitely $\phi$*: for every linearization, there is a consistent global state where $\phi$ is true.

Algorithms for evaluating these properties traverse the lattice of reachable global states (constructed from per-process state messages), using vector timestamps to ensure consistency conditions.



## Practical advice and pitfalls

- Use logical clocks for ordering and causality when absolute time is unnecessary.
- Prefer NTP for coarse-grained synchronization in production; use logical clocks where correctness depends on causality, not real time.
- Snapshot algorithms require reliable channels (or adaptations) and careful handling when processes/channels can fail.
- Beware asymmetric network delays when using Cristian-style techniques; always account for error bounds.



## References

[1] Coulouris, G., Dollimore, J., Kindberg, T., & Blair, G. Distributed Systems: Concepts and Design.
