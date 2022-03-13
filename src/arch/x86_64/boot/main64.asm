global long_mode_start
[extern kmain]

[section .text]
[bits 64]
long_mode_start:
    ; Need to load 0 (null) in all the data registers so the CPU instructions will work
    ; properly
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; ; The following code prints 'OK'
    ; mov dword [0xb8000], 0x2f4b2f4f
    call kmain
    hlt
