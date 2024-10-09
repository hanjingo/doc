# CHAPTER8 Relational Database Design



We can use the following three rules to find logically implied functional dependencies. By applying these rules `repeatedly`, we can find all of $F^+$, given $F$. This collection of rules is called `Armstrong's axioms` in honor of the person who first proposed it:

- `Reflexivity rule`. If $\alpha$ is a set of attributes and $\beta \subseteq \alpha$, then $\alpha \rightarrow \beta$ holds.
- `Augmentation rule`. If $\alpha \rightarrow \beta$ holds and $r$ is a set of attributes, then $r \alpha \rightarrow r \beta$ holds.
- `Transitivity rule`. If $\alpha \rightarrow \beta$ holds and $\beta \rightarrow r$ holds, then $\alpha \rightarrow r$ holds.

To simplify matters further, we list additional rules. It is possible to use Armstrong's axioms to prove that these rules are sound:

- `Union rule`. If $\alpha \rightarrow \beta$ holds and $\alpha \rightarrow r$ holds, then $\alpha \rightarrow \beta r$ holds.
- `Decomposition rule`. If $\alpha \rightarrow \beta r$ holds, then $\alpha \rightarrow \beta$ holds and $\alpha \rightarrow r$ holds.
- `Pseudotransitivity rule`. If $\alpha \rightarrow \beta$ holds and $r \beta \rightarrow \delta$ holds.

We say that an attribute $B$ is `functionally determined` by $\alpha$ if $\alpha \rightarrow B$.

The 3NF algorithm ensures the preservation of dependencies by explicitly building a schema for each dependency in a canonical cover. It ensures that the decomposition is a lossless decomposition by guaranteeing that at least one schema contains a candidate key for the schema being decomposed.



## Summary

TODO