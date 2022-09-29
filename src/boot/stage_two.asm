; Provide the _start symbol globally so the linker doesn't complain
[global _start]
; Include the external C kernel main method
[extern kernel_main]
; Compile this file with the 32-bit instruction set
[bits 32]
; This start label is here just to tell the linker where the executable code startes from
_start:
  ; Move the VGA buffer to <ebx>
  mov ebx, 0xb8000

  call vclear

  mov si, MSG_A20_ENABLED
  call vprintok

  ; Print the [INFO] <message>
  mov dl, 0x09
  mov si, INFO
  call vprint
  mov dl, 0x0f
  mov si, MSG_PROTECTEDMODE
  call vprint

  mov dl, 0x09
  mov si, INFO
  call vprint
  mov dl, 0x0f
  mov si, MSG_CALLINGKERNEL
  call vprint

  call kernel_main

  ; This code should never be called. If this code is executing, it means that the kernel unexpectedly returned.
  ; In that case, print an error message to the user and halt program execution
  mov dl, 0x0c
  mov si, ERROR
  call vprint
  mov dl, 0x0f
  mov si, MSG_KERNELRETURNED
  call vprint
  jmp $

; ---------------------------------------------
; Code after this point will not get executed
; Use it to make useful functions or variables
; ---------------------------------------------

%include "console/vga_print.asm"

; Declaring strings
MSG_A20_ENABLED db "A20 line enabled", 13, 10, 0
MSG_PROTECTEDMODE db "Successfully entered 32-bit protected mode", 13, 10, 0
MSG_CALLINGKERNEL db "Jumping to C kernel...", 13, 10, 0
MSG_KERNELRETURNED db "Kernel returned unexpectedly", 13, 10, 0
