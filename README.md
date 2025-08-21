# TODO: HEADER

## Folder Contents:
- `README.md` - The Markdown source of this file that explains how to use
- `cache_miss` folder contains source files necessary to build each kernel image.
- `images` folder contains the executables that will be tested for worst case cache misses.
- `bin` folder contains scripts for building and executing empirical evaluation
    - `build-img.sh` - Builds all of the images initially. (WIP)
    - `trials.sh` - Runs a RISC-V image at to create table of cache misses based of a stack offset
    - `qemu.sh` - Runs a RISC-V simulated machine given a kernel image.
