[BITS 16]

; This method reads a given number of sectors from the boot disk
read_disk:
  ; Push the <ax>, <bx>, <cx> and the <dx> register as they will be used
  push ax
  push bx
  push cx
  push dx

  mov ah, 0x02            ; Tell the BIOS we'll be reading the disk
  mov cl, 0x02            ; Start reading from sector 2 (because sector 1 is where we are now)
  mov al, 32              ; Read n number of sectors from disk
  mov ch, 0x00            ; Cylinder 0
  mov dh, 0x00            ; Head 0
  xor bx, bx              ; Clear the value in <bx>
  mov es, bx              ; Set the value of <es> to zero
  mov dl, [BOOT_DISK]     ; Read from the disk [boot drive]
  mov bx, SECOND_STAGE    ; Put the new data we read from the disk starting from the specifed location

  int 0x13                ; Read disk interrupt
  jc read_disk_failed     ; Jump to error handler (kinda?) if diskread fails

  ; Pop the pushed registers from the stack before returning from the function
  pop dx
  pop cx
  pop bx
  pop ax

  ret                     ; Return from this function

; Print an error message that the disk was not able to be read properly then hang indefinitely.
read_disk_failed:
  mov si, ERROR_DISKREADERROR
  call bios_print
  jmp $

; ---------------------------------------------
; Code after this point will not get executed
; Use it to make useful functions or variables
; ---------------------------------------------

ERROR_DISKREADERROR db "Disk not found.", 0

%include "console/bios_print.asm"