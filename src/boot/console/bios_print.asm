[BITS 16]

; The BIOS print routine
bios_print:
  push ax         ; Push the <ax> register because it will be used.

  ; This method loops over all characters in a null-terminated string to print them.
  .__bios_print_loop:
    mov al, [si]            ; Move the next character into the <al> register.
    cmp al, 0               ; Check if <al> is 0 (null).
    jnz .__bios_print_char  ; If it is, then we have reached the end of the string. Prepare to exit the method.
    pop ax                  ; Pop the pushed values from the stack, restoring their value
    ret                     ; Safely return back to the memory address from where this function was called.
 
  ; This method prints a single character on the screen
  .__bios_print_char:
    mov ah, 0x0e            ; Tell the BIOS we will be printing a character onto the screen
    int 0x10                ; Call the interrupt to print the character (which should be in the <al> register)
    add si, 1               ; Add 1 to <si> to print the next character in the buffer
    jmp .__bios_print_loop  ; Jump back to the print loop to print the next character