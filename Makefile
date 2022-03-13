# To be honest, all this is just black magic to me. They somehow work. That is all there is to it.

kernel_source_files := $(shell find src/kernel -name *.c)
kernel_object_files := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find src/arch/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst src/arch/x86_64/%.c, build/arch/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/arch/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/arch/x86_64/%.asm, build/arch/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

$(kernel_object_files): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/include/kernel -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(x86_64_c_object_files): build/arch/x86_64/%.o : src/arch/x86_64/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/include -ffreestanding $(patsubst build/arch/x86_64/%.o, src/arch/x86_64/%.c, $@) -o $@

$(x86_64_asm_object_files): build/arch/x86_64/%.o : src/arch/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/arch/x86_64/%.o, src/arch/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64 build
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso

build: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso

run-docker:
	sudo docker run --rm -it -v "$(pwd)":/root/env projectapril

run:
	qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso
