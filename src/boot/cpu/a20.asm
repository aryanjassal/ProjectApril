[BITS 32]

; This is a method to enable the A20 line required to access more than 1 MiB of memory
; TODO: add proper A20 checking and enabling
fast_a20:
  in al, 0x92
  or al, 2
  out 0x92, al
  ret

; This is a method to check if A20 line is already enabled
check_a20:
  ; Push registers
  pushad

  ; Making up a random signature for <edi> and <esi>
  mov edi, 0x112345
  mov esi, 0x012345

  ; Moving the previously defined signature into the memory address pointed to by the address
  mov [esi], esi
  mov [edi], edi

  ; If the memory values are the same, it means that the A20 line is not set and that the memory for
  ; 0x112345 wrapped around and matched with 0x012345. Otherwise, if they are not equal, then it means
  ; that the memory address did not change, thus indicating that the A20 line is enabled.
  cmpsd

  popad         ; Pop registers
  jne .__a20_on ; Read the explanation above if you don't know what this does

  ; Otherwise...
  clc
  ret

  ; What to do if A20 is actually on?
  .__a20_on:
    stc
    ret