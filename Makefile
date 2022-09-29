BOOTLOADER_SRC_DIR := src/boot
BOOTLOADER_BUILD_DIR := dist/boot

KERNEL_SRC_DIR := src/kernel
INCLUDE_DIR := src/include
KERNEL_BUILD_DIR := dist/kernel
KERNEL_INCLUDE_DIR := $(INCLUDE_DIR)/kernel

BOOTLOADER_SRC_FILES := $(shell find $(BOOTLOADER_SRC_DIR) -name "*.asm")
BOOTLOADER_OBJECT_FILES := $(patsubst $(BOOTLOADER_SRC_DIR)/%.asm, $(BOOTLOADER_BUILD_DIR)/%.bin, $(BOOTLOADER_SRC_FILES))

KERNEL_C_SRC_FILES := $(shell find $(KERNEL_SRC_DIR) -name "*.c")
KERNEL_ASM_SRC_FILES := $(shell find $(KERNEL_SRC_DIR) -name "*.asm")
KERNEL_C_OBJECT_FILES := $(patsubst $(KERNEL_SRC_DIR)/%.c, $(KERNEL_BUILD_DIR)/%.o, $(KERNEL_C_SRC_FILES))
KERNEL_ASM_OBJECT_FILES := $(patsubst $(KERNEL_SRC_DIR)/%.asm, $(KERNEL_BUILD_DIR)/%.asmo, $(KERNEL_ASM_SRC_FILES))

BOOTLOADER_OUTPUT_BIN := dist/bootloader.bin
KERNEL_OUTPUT_BIN := dist/kernel.bin
OUTPUT_BIN := dist/project_april.bin
LINKERFILE := src/linker.ld

ASMC := @nasm
QEMU := @qemu-system-x86_64
ECHO := @echo
MKDIR := @mkdir -p
CAT := @cat
LD := @ld
GCC := @gcc
CLEAR := @clear

ASMFLAGS := -I $(BOOTLOADER_SRC_DIR)
QEMUFLAGS := -drive file=$(OUTPUT_BIN),if=floppy,index=0,media=disk,format=raw -no-reboot
GCCFLAGS := -m32 -ffreestanding -fno-stack-protector -nostdlib -mno-red-zone -I $(KERNEL_INCLUDE_DIR) -fno-pie -Ofast -Wall -Wextra -Werror -O2 -c
LDFLAGS := -n -m elf_i386 -Ttext 0x8000 -T $(LINKERFILE) -o $(KERNEL_OUTPUT_BIN)

.PHONY: all build exec compile_bootloader

all: compile_bootloader build exec

build: $(KERNEL_C_OBJECT_FILES) $(KERNEL_ASM_OBJECT_FILES) compile_bootloader
	$(ECHO) "Compiling..."
	$(LD) $(LDFLAGS) $(BOOTLOADER_BUILD_DIR)/stage_two.o $(KERNEL_C_OBJECT_FILES) $(KERNEL_ASM_OBJECT_FILES)
	$(CAT) $(BOOTLOADER_BUILD_DIR)/stage_one.bin $(KERNEL_OUTPUT_BIN) > $(OUTPUT_BIN)
	$(ECHO) "Compilation done."

exec:
	$(ECHO) "Executing Project April in QEMU..."
	$(QEMU) $(QEMUFLAGS)
	$(CLEAR)

compile_bootloader:
	$(MKDIR) $(BOOTLOADER_BUILD_DIR)
	$(ASMC) $(ASMFLAGS) -f bin $(BOOTLOADER_SRC_DIR)/stage_one.asm -o $(BOOTLOADER_BUILD_DIR)/stage_one.bin
	$(ASMC) $(ASMFLAGS) -f elf32 $(BOOTLOADER_SRC_DIR)/stage_two.asm -o $(BOOTLOADER_BUILD_DIR)/stage_two.o

$(KERNEL_C_OBJECT_FILES): $(KERNEL_BUILD_DIR)/%.o : $(KERNEL_SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(GCC) $(GCCFLAGS) $(patsubst $(KERNEL_BUILD_DIR)/%.o, $(KERNEL_SRC_DIR)/%.c, $@) -o $@

$(KERNEL_ASM_OBJECT_FILES): $(KERNEL_BUILD_DIR)/%.asmo : $(KERNEL_SRC_DIR)/%.asm
	$(MKDIR) $(dir $@)
	$(ASMC) $(ASMFLAGS) -f elf32 $(patsubst $(KERNEL_BUILD_DIR)/%.asmo, $(KERNEL_SRC_DIR)/%.asm, $@) -o $@