# Multivariate Polynomial Public Key Digital Signature Trefoil Knot Algorithm

WORK IN PROGRESS

## Directory Structure

Does not include CMake files, build directories, or other build artifacts.

```plaintext
├── README.md           # This file
├── Build.script        # Build script. Same script is used on both CMD and Shell.
├── src                 # C source code
│   ├── mppktk.h
│   ├── mppktk.c
│   ├── mppktk_config.c
├── python              # Python reference implementation
│   ├── mppktk.py
├── lib                 # Libraries
│   ├── random          # Sample random number generator (not cryptographically secure)
│   │   ├── random.h
│   │   ├── random.c
│   ├── hash            # Hash functions
│   │   ├── SHAKE256    # SHAKE256
│   │   │   ├── FIPS202.h
│   │   │   ├── FIPS202.c
│   │   |   ├── armv8
│   │   |   |   ├── KECCAK.h
│   │   |   |   ├── KECCAK.S
```

# Build Instructions

Run the `Build.script` script to build the project. The script cleverly works
on both CMD and Shell. It will create a `build` directory and compile the
source code into it. 

```shell
# Shell
./Build.script

# CMD
Build.script
```


