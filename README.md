# Proxy Re-encryption Systems for Identity-based Encryption

The repository contains a prototype implementation of the two *Proxy Re-encryption Systems for Identity-based Encryption* as described in the [paper](https://eprint.iacr.org/2007/361.pdf).
In particular, the paper contains descriptions of the following schemes for the proxy re-encryption systems:
- `Hybrid proxy re-encryption system` that allow ciphertexts encrypted under a CBE public key to be transformed into the different ciphertexts that can be decrypted by an IBE secret key.
- `Identity based proxy re-encryption system` that allow ciphertexts encrypted under one’s IBE public key to be transformed into the different ciphertexts that can be decrypted by the other’s IBE secret key.

The repository also contains the implementation of two other cryptographic schemes involved in the limplementation of the two described Proxy Re-encryption System:
- the ElGamal-type CBE system
- the BB-IBE system

## Requirements

- [PBC](https://crypto.stanford.edu/pbc/)
- [gmp](https://gmplib.org/)
- [gcc](https://gcc.gnu.org/) / [clang](https://clang.llvm.org/)
- [Make](https://www.gnu.org/software/make/)
- [CMake](https://cmake.org/)
- utility libraries made by professor [Mario di Raimondo](https://diraimondo.dmi.unict.it/)

## Directory Structure

The project is structured as follows:

```shell
.
├── bin # contains the executables
├── examples # contains some examples of usage
├── libs-mdr # contains utility libraries made by professor Mario Di Raimondo
├── src # contains the source files of the implementations
└── test # contains the test files that allow benchmarking
```

## Build

Move to the root directory and type:
```shell
make
```

You can change some params in the `CMakeLists.txt` file and rebuild the `Makefile` typing:

```shell
cmake .
```

## Testing and benchmarking

The following tests are available: `test-bb-ibe-system`, `test-cbe-gamal-system`, `test-hybrid-reenc-system`, `test-ibe-reenc-system`.
They can be performed in the following way
```
./bin/[test-name] [sec-level <n>] [pairing-pp t|f] [pow-pp t|f] [type-a|type-a1|type-e]
```
where
- `[test-name]` is the name of the test to be performed
- `[sec-level <n>]` is the level of security required
- `[pairing-pp t|f]` enables or disables precomputation in the pairing application (where possible)
- `[pow-pp t|f]` enables or disables precomputation for exponentiation (where possible)
- `[type-a|type-a1|type-e]` allows you to choose the elliptic curve used

## References

- [Proxy Re-encryption Systems for Identity-based Encryption](https://eprint.iacr.org/2007/361.pdf)
- [PBC](https://crypto.stanford.edu/pbc/)
- [gmp](https://gmplib.org/)
- [Mario di Raimondo](https://diraimondo.dmi.unict.it/)
- [Crypto Engineering](https://diraimondo.dmi.unict.it/teaching/crypto/)