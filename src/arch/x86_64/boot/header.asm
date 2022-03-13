section .multiboot_header
header_start:
    ; Enter the magic number responsible to tell the CPU that this code here
    ; is part of an operating system.
    dd 0xe85250d6  ; This tells the CPU that the OS is multiboot2 compilant

    ; Now we need to provide some basic architechture information about our operating system
    dd 0  ; This means that we are currently in <protected mode i386> whatever that means

    ; We need to provide the total length of the header for some reason, so this is how to do it
    dd header_end - header_start

    ; Checksum here
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; End tag tells the CPU that this is where the operating system code ends
    ; Don't ask how it works because even I don't know
    dw 0
    dw 0 
    dd 8

header_end:

; For resources on the source of this code, visit https://youtu.be/FkrpUaGThTQ?list=PLZQftyCk7_SeZRitx5MjBKzTtvk0pHMtp
