[ORG 0x7c00]        ; Set the origin of the bootloader
; TODO: Perform a far-jump to set the CS:IP registers properly
; Refer here https://wiki.osdev.org/My_Bootloader_Does_Not_Work#You_are_assuming_a_wrong_CS:IP_value

; Tell the compiler to compile the following instructions in 16-bit format
[BITS 16]
start:
  ; Initialise all the registers
  xor ax, ax
  mov es, ax
  mov ds, ax
  mov ss, ax
  mov sp, 0x7c00
  mov bp, sp
  mov [BOOT_DISK], dl

  ; Load the second stage of the bootloader into the memory
  ; TODO: state number of sectors to be read
  ; TODO: first try hard drive then try floppy
  call read_disk

  ; Prepare to enter 32-bit protected mode
  cli                   ; Clear BIOS interrupts
  lgdt [gdt_desc]       ; Load the Global Descriptor Table

  ; Set PE (Protection Enable) bit in <cr0> (Control Register 0)
  mov eax, cr0          ; We cannot directly modify the value of <cr0>, so first load it in the <eax> register
  or eax, 1             ; Then, set the first bit in the <eax> register
  mov cr0, eax          ; Finally, move the <eax> with the PE bit set back into <cr0>

  jmp CODESEG:clear_pipe    ; Perform a far-jump to clear the garbage 16-bit instructions and ready code for 32-bit architecture

; Tell the compiler to compile the following instructions in 32-bit format
[BITS 32]
clear_pipe:
  ; Store the correct address in the segment registers
  ; Refer here for the tutorial: http://www.osdever.net/tutorials/view/the-world-of-protected-mode
  mov ax, DATASEG   ; Store the data segment value in the <ax> register
  mov ds, ax        ; Store proper value in the <ds> register (<ds> register stores variables)
  mov ss, ax        ; Store proper value in the <ss> regsiter (<ss> register is the stack segment)
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ebp, 0x90000  ; Start the stack at memory address 0x90000 (refer to the memory address table in the aforementioned site)
  mov esp, ebp

  jmp SECOND_STAGE

  ; call check_a20
  ; je .__boot_a20_enabled

  ; call fast_a20
  ; call check_a20
  ; je .__boot_a20_enabled

  ; Halt indefinitely if A20 line cannot be enabled
  ; TODO: Print an actual error message to the user
  ; TODO: Make this concept actually work
  ; jmp $
  
  ; .__boot_a20_enabled:
  ; Jump to the second stage of the bootloader

; ---------------------------------------------
; Code after this point will not get executed
; Use it to make useful functions or variables
; ---------------------------------------------

; TODO: Add a BIOS error printing method with colour and same formatting as normal logs
%include "disk/floppy.asm"
%include "cpu/a20.asm"
%include "cpu/gdt.asm"

; Declaring disk-reading-related variables
; This is needed to be declared in order to not make the disk reading module fail
BOOT_DISK db 0
SECOND_STAGE equ 0x8000

; Pad the entire bootloader with zeroes because the bootloader must be exactly 512 bytes in size
times 510-($-$$) db 0

; The magic signature which tells the computer that this file is bootable
dw 0xaa55