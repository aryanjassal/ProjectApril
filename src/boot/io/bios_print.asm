[BITS 16]

; The BIOS print routine
bios_print:
  push ax         ; Push the <ax> register because it will be used.

  ; This method loops over all characters in a null-terminated string to print them.
  .__bios_print_loop:
    mov al, [si]            ; Move the current character into the <al> register.
    cmp al, 0               ; Check if <al> is 0 (null).
    jnz .__bios_print_char  ; If it is, then we have reached the end of the string. Prepare to exit the method.
    pop ax                  ; Pop the pushed values from the stack, restoring their value
    ret                     ; Safely return back to the memory address from where this function was called.
 
  ; This method prints a single character on the screen
  .__bios_print_char:
    mov ah, 0x0e            ; Tell the BIOS we will be printing a character onto the screen
    int 0x10                ; Call the interrupt to print the character (which should be in the <al> register)
    inc si                  ; Increment the <si> to load the next character in the buffer
    jmp .__bios_print_loop  ; Jump back to the print loop to print the next character

; The BIOS routine to print info messages
;! REDUNDANT
; TODO: remove everything beneath this line
binfo:
  push si 
  mov si, MSG_INFO
  mov bl, COL_INFO
  call bios_print
  pop si
  mov bl, COL_MSG
  call bios_print
  mov si, TEXT_NEWLINE
  call bios_print
  ret

berror:
  push si 
  mov si, MSG_ERROR
  mov bl, COL_ERROR
  call bios_print
  pop si
  mov bl, COL_MSG
  call bios_print
  mov si, TEXT_NEWLINE
  call bios_print
  ret

; Declaring useful string literals
MSG_OK    db "[OK]    ", 0
MSG_INFO  db "[INFO]  ", 0
MSG_WARN  db "[WARN]  ", 0
MSG_ERROR db "[ERROR] ", 0

COL_MSG   db 0x0f
COL_OK    db 0xaf
COL_INFO  db 0x9f
COL_WARN  db 0xef
COL_ERROR db 0xcf

TEXT_NEWLINE db 13, 10, 0