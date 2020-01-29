# LeOS
Operating System for ARMv8 (aarch64) Architecture

* [The Idea](#The-Idea)
* [Hardware](#Hardware)
* [Documentation](#Documentation)
* [Compilation](#Compilation)
* [Run](#Run)
* [Debug](#Debug)
* [Roadmap](#Roadmap)
* [Contribution](#Contribution)

---

## The Idea

LeOS is being developed to be a lightweight desktop operating system for
ARM-based computers, tablets, mobile phones etc. Here are some concepts behind
it:

1. The OS is free with open source codes, distributed under terms of [CC BY-ND 4.0](LICENSE.md).
2. The OS will have POSIX-compliant API.
3. The OS will include graphical system, shell and generic utilities as a part
of it, being designed to work as a solid product.
4. The OS will respect user's privacy and will not track his/her actions and data.
5. The OS will stive to be secure and robust.

## Hardware

Early development is going for **Raspberry PI3** board and its emulation using
**QEMU**.

## Documentation

* [Project structure](docs/project-structure.md)
* [Coding style](docs/coding-style.md)
* Task scheduling
* Memory management

## Compilation

To compile LeOS run `make` from repository root, make sure
[Clang](https://clang.llvm.org/) compiler is installed on your system.

```
$ make
```

Output files will be stored inside newly created `build` folder.

## Run

To run LeOS on QEMU, execute `make run` command for the repository root.

To run LeOS on Raspberry PI3, follow these steps:

1. Compile project and copy `build/kernel8.img` and `config.txt` files to 
Micro SD card
2. Make sure latest `bootcode.bin` and `start.elf` files are copied to the SD card
3. Insert SD card into your Raspberry PI3 and power it up

## Debug

If you have `gdb-multiarch` and **QEMU** installed, then debugging should be as
easy as `make debug`.

## Roadmap

1. Generic kernel features:
	- [x] Loadable Kernel file
	- [x] UART logging
	- [x] Memory pages avalability bitmap
	- [x] Interrupt vectors table
	- [x] Basic task scheduler
	- [x] Context switching
	- [ ] MMU and entering user level
2. Input/output:
	- [ ] Graphical driver
	- [ ] USB driver
	- [ ] Keyboard input driver
	- [ ] Mouse input driver
3. Graphical system
4. Shell and utilities
5. Networking
6. Sound system


## Contribution
