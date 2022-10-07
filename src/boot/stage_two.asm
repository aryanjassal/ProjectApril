[BITS 32]

; Externs to  C kernel functions
[EXTERN kmain]
[EXTERN kclear]
[EXTERN kinfo]
[EXTERN kwarn]
[EXTERN kerror]

[GLOBAL _start]
_start:
  call kclear

  ; TODO: put the enable A20 code here instead, with support for proper logging
  ; A20 will always be enabled by the first stage for us
  ; push MSG_A20_ENABLED
  ; call kinfo

  ; We will also be in protected mode by default in the second stage
  push MSG_PROTECTEDMODE
  call kinfo

  ; Go to the higher-level C kernel
  call kmain

  ; -------------------------------------------------
  ; The code below this line should never be called.
  ; It means that the kernel returned unexpectedly.
  ; So, print the user an error message and halt.
  ; -------------------------------------------------
  push MSG_KERNELRETURNED
  call kerror
  cli
  jmp $

; ---------------------------------------------
; Code after this point will not get executed
; Use it to make useful functions or variables
; ---------------------------------------------

; Declaring strings
;! Currently redundant (until a20-log is fixed)
; MSG_A20_ENABLED     db "A20 line enabled", 0
MSG_PROTECTEDMODE   db "Successfully entered protected mode", 0
MSG_KERNELRETURNED  db "Kernel returned unexpectedly", 0
