[GLOBAL keyboard_handler]
[EXTERN irq_keyboard_handler]
keyboard_handler:
  ; cli
  pushad
  ; push byte 0
  ; push byte 33
  ; pusha
  ; mov ax, ds
  ; push eax
  ; mov ax, 0x10
  ; mov ds, ax
  ; mov es, ax
  ; mov fs, ax
  ; mov gs, ax

  cld
  call irq_keyboard_handler

  ; pop eax
  ; mov ds, ax
  ; mov es, ax
  ; mov fs, ax
  ; mov gs, ax

  ; popa
  ; add esp, 0x08
  popad
  ; sti
  iret