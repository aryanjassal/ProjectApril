[BITS 16]

; This method reads a given number of sectors from the boot disk
read_disk:
  ; Push the <bx> and <cx> register as they will be used
  push bx
  push cx

  ; Move the parameters into appropriate registers
  mov al, dh              ; The <dh> register should contain the number of sectors to be read from disk
  push dx                 ; Push the <dx> register because this will be used to check for correct number of sectors read

  ; Set registers to prepare for int 0x13
  mov ah, 0x02            ; Tell the BIOS we'll be reading the disk
  mov cl, 0x02            ; Start reading from sector 2 (because sector 1 is where we are now)
  ; mov al, 32              ; Read n number of sectors from disk
  xor ch, ch              ; Cylinder 0
  xor dh, dh              ; Head 0
  ; xor bx, bx              ; Clear the value in <bx>
  ; mov es, bx              ; Set the value of <es> to zero
  ; mov dl, [BOOT_DISK]     ; Read from the disk [boot drive]
  mov bx, SECOND_STAGE    ; Put the new data we read from the disk starting from the specifed location

  int 0x13                ; Read disk interrupt
  jc read_disk_failed     ; Jump to error handler (kinda?) if diskread fails

  ; Check for correct number of sectors read
  pop dx
  cmp al, dh
  jne incorrect_sectors_read

  return:
  ; Pop the pushed registers from the stack before returning from the function
  pop cx
  pop bx

  ret                     ; Return from this function

; Error code 1 (0x01): Disk read error
read_disk_failed:
  ; Move the error code to <ah>
  mov ah, 0x01

  ; Return from the function
  jmp return

; Error code 2 (0x02): Incorrect number of sectors read error
incorrect_sectors_read:
  ; Move the error code to <ah>
  mov ah, 0x02

  ; Return from the function
  jmp return