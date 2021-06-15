# PoRep

## 定义

### PublicParams

```rust
/// The parameters shared between the prover and verifier.
#[derive(Clone, Debug)]
pub struct PublicParams {
    /// How many leaves the underlying merkle tree has.
    pub leaves: usize,
    pub private: bool,
}

```
