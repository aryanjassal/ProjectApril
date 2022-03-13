# Project April

Project April (aka AprilOS or just April) is an operating system that I am working on. I plan to implement everything from scratch to gain knowledge and insight into how an operating system and computers in general work. When I say *everything* will be made from scratch, I really do mean *everything*. Of course, I am allowed to use existing languages such as Assembly and C/C++. I am also allowed to use external libraries for cases in which it is impractical to build my own implementation. (Example could be UEFI. I haven't looked too much into UEFI, but it seems that there are libraries which give you a UEFI boilerplate)

It should be noted that this is my first time dabbling in anything low-level, basically. I have used a little bit of C++ a while ago, and now I want to really get to know computers, hence this project. It also means that in places, my code could have poor organisation, or just be filled with bad coding practices. In that case, please submit an issue. I am open to suggestions!

Also to note that I am on Arch linux, so there may be some strange quirks while building for other distros.

## Building instructions

Ensure that you have QEmu and Docker installed. This can be installed on Arch-based distributions by running

```bash
sudo pacman -S qemu docker --needed
```

Then, you need to build the docker container. It may take a while. Run

```bash
sudo docker build buildenv -t projectapril
```

After the container is ready, you need to actually enter into the container using the following command.

```bash
sudo docker run --rm -it -v "$(pwd)":/root/env projectapril
```

Then, you need to build the operating system files and binaries. Note that the operating system currently only supports to compile and run x86_64 code. To start the compilation process, run the following command from within the docker container.

```bash
make build
```

Now, either exit from the docker container or open a new terminal to run the operating system using QEmu using the following command.

```bash
make run
```

## Resources worth viewing

- [https://github.com/zszafran/osdev](zszafran's operating system)

## Features of the operating system

- [ ] Phase 1 - Bare Minimum Functionality
  - [-] Create a proper project structure
  - [ ] Create a basic "Hello World" kernel
    - [-] Booting into the kernel
    - [-] Printing character to screen using assembly
    - [-] Entering 32 bit protected mode
    - [ ] Entering 64 bit long mode
    - [ ] Linking C/C++ code to assembly
    - [ ] Echoing user input to screen using assembly
