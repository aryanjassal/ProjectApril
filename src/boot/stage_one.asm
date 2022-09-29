[org 0x7c00]        ; Set the origin of the bootloader

; Move the boot disk into a variable which will be used when reading from disk
mov [BOOT_DISK], dl       ; Store the boot disk for later use

; Initialise the stack at 0x7c00
mov bp, 0x7c00    ; Move the stack base pointer at the memory address 0x7c00
mov sp, bp        ; Move the current stack pointer to the base (stack is empty)

; Load the second stage of the bootloader into the memory
; TODO: state number of sectors to be read
call read_disk

; Prepare to enter 32-bit protected mode
cli                   ; Clear BIOS interrupts

; We need to first initialise the <ds> register before loading the GDT
xor ax, ax            ; Basically the same as <mov ax, 0> but preferred for some reason
mov ds, ax            ; Initialise <ds> register with a null value
lgdt [gdt_desc]       ; Load the Global Descriptor Table

; Set PE (Protection Enable) bit in <cr0> (Control Register 0)
mov eax, cr0          ; We cannot directly modify the value of <cr0>, so first load it in the <eax> register
or eax, 1             ; Then, set the first bit in the <eax> register
mov cr0, eax          ; Finally, move the <eax> with the PE bit set back into <cr0>

jmp CODESEG:clear_pipe    ; Perform a far-jump to clear the garbage 16-bit instructions and ready code for 32-bit architecture

; Tell the compiler to compile the following instructions in 32-bit format
[bits 32]
clear_pipe:
  ; Store the correct address in the segment registers
  ; Refer here for the tutorial: http://www.osdever.net/tutorials/view/the-world-of-protected-mode
  mov ax, DATASEG   ; Store the data segment value in the <ax> register
  mov ds, ax        ; Store proper value in the <ds> register (<ds> register stores variables)
  mov ss, ax        ; Store proper value in the <ss> regsiter (<ss> register is the stack segment)
  mov esp, 0x90000  ; Start the stack at memory address 0x90000 (refer to the memory address table in the aforementioned site)

  call check_a20
  je .__boot_a20_enabled

  call fast_a20
  call check_a20
  je .__boot_a20_enabled
  
  .__boot_a20_enabled:
    ; Jump to the second stage of the bootloader
    jmp SECOND_STAGE

; ---------------------------------------------
; Code after this point will not get executed
; Use it to make useful functions or variables
; ---------------------------------------------

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
