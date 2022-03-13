; This file contains all the 32 bit assembly code, which prepares our system to enter into 64 bit long mode

; This code file now contains code that did not work for some apparent reason. Need to look into it later.

; global start

section .text
[bits 32]
start:
    ; Set up stack
    mov ebp, stack_top
    mov esp, ebp

    ; Disable Interrupts to prepare for 32 bit protected mode
    cli

    ; Load the GDT table described later down the page
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Don't move this value into the virtual memory to remove the [bits 32] for the start function
    ; mov dword [0xb8000], 0x4f524f45
    
    jmp codeseg:start_protected_mode

gdt_nulldesc:
    ; The first value in GDT needs to be zero or null
    dd 0
    dd 0

gdt_codedesc:
    ; base =0 x0 , limit =0 xfffff ,
    ; 1 st flags : ( present )1 ( privilege )00 ( descriptor type )1 -> 1001 b
    ; type flags : ( code )1 ( conforming )0 ( readable )1 ( accessed )0 -> 1010 b
    ; 2 nd flags : ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0 -> 1100 b
    dw 0xffff       ; Limit         Maximum limit of codedesc
    dw 0x0000       ; Base (low)    Minimum limit of codedesc
    db 0x00         ; Base (medium) Minimum limit of codedesc (cont.)
    db 10011010b    ; Flags         First and Type flags
    db 11001111b    ; Flags + Limit Second flags
    db 0x00         ; Base (high)   Minimum limit of codedesc (even more cont.)

gdt_datadesc:
    ; The same as <gdt_codedesc>, but the code flag is set to 0
    dw 0xffff       ; Limit         Maximum limit of codedesc
    dw 0x0000       ; Base (low)    Minimum limit of codedesc
    db 0x00         ; Base (medium) Minimum limit of codedesc (cont.)
    db 10010010b    ; Flags         First and Type flags
    db 11001111b    ; Flags + Limit Second flags
    db 0x00         ; Base (high)   Minimum limit of codedesc (even more cont.)

gdt_end:

gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_nulldesc - 1
        dq gdt_nulldesc

codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc

check_cpuid:
    ; <fd> is the flags register
    ; The 21st bit should be flipped then put into the flags register
    ; If it remains flipped, then our CPU supports CPUID
    ; Otherwise, no support for CPUID
    pushfd
    ; Pop the next value from the stack (which is <fd>) to <eax>
    pop eax
    ; Duplicate the value of <eax> to test against later
    mov ecx, eax
    ; <1 << 21> just means that we are accessing the value of the 21st bit,
    ; which will be flipped later on.
    xor eax, 1 << 21
    push eax
    ; Load flags back into the flags register
    popfd

    ; Load flags back into the <eax> register
    pushfd
    pop eax

    ; Return the value of the flags register to what it was prior to 
    ; testing for CPUID
    push ecx
    popfd

    ; Compare the old, unchanged value to the corresponding flags bit
    cmp eax, ecx
    je .no_cpuid
    ret

.no_cpuid:
    mov al, "C"
    jmp error

check_long_mode:
    ; CPUID is also used as a function, and takes the value of the <eax> register
    ; as in implicit argument. If the value of <eax> is <0x80000000>, then the CPU
    ; will change it to a value greater than it.
    ; It then takes another argument of <eax> register. If the <eax> register has the
    ; value of 0x80000001, then the 29th bit should be set (or flipped). If that is not
    ; the case, then our CPU does not support long or 64-bit mode
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode
    ret

.no_long_mode:
    mov al, "L"
    jmp error

set_up_page_tables:
    mov eax, page_table_l3
    or eax, 0x11  ; Flags for <present, writable>
    ; Move the flags modified above to the first entry of the L4 paging table
    mov [page_table_l4], eax

    mov eax, page_table_l2
    or eax, 0x11  ; Flags for <present, writable>
    ; Move the flags modified above to the first entry of the L3 paging table
    mov [page_table_l3], eax

    ; Now create a <for> loop to map 1 GB of physical RAM directly to virtual paging tables
    mov ecx, 0
    .loop:
        mov eax, 0x200000  ; 2 MiB
        mul ecx  ; Multipy value of <ecx> by <eax> to get the value of the next page
        or eax, 0b10000011  ; Same as before with additional flags, setting flags <present, writable, huge page>

        ; The (* 8) is there because each entry takes 8 bits of storage, offset by the current index
        mov [page_table_l2 + ecx * 8], eax  ; Actually move the page value into the page table offset to the correct index

        inc ecx
        cmp ecx, 512  ; Check if all 1 GB is filled (512 loops)
        jne .loop
        ret

enable_paging:
    ; Pass the page table location to the CPU
    ; The CPU looks for the page table in the register <cr3>
    mov eax, [page_table_l4]
    mov cr3, eax

    ; Enable Physical Address Extension (PAE), required for 64 bit operating system
    ; Just need to enable the PAE flag in the <cr4> register (which is the 5th bit)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Enable long mode
    mov ecx, 0xc0000080
    ; Read Model-Specific Register into the <eax> register
    rdmsr
    ; Flip 8th bit to enable long mode, then write it back to the model-specific register
    or eax, 1 << 8
    ; Write to Model-Specific Register
    wrmsr

    ; Finally, enable paging
    ; Do this my enabling the <paging> flag (which is bit 31) in the <cr0> register
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret

error:
    ; This subroutine is to print an error in the format "ERR: X" where <x> is
    ; the error code stored in the <al> register
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte [0xb800a], al
    hlt

start_protected_mode:
    mov ax, dataseg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; mov dword [0xb8000], 0x07650748
    ; mov dword [0xb8004], 0x076c076c
    ; mov dword [0xb8008], 0x072c076f
    ; mov dword [0xb800c], 0x07770720
    ; mov dword [0xb8010], 0x0772076f
    ; mov dword [0xb8014], 0x0764076c
    ; mov dword [0xb8018], 0x07210000

    call check_cpuid
    call check_long_mode
    call set_up_page_tables
    call enable_paging

    jmp codeseg:long_mode_start

[bits 64]
extern kmain
long_mode_start:
    ; Hi
    ; mov dword [0xb8000], 0x07690748

    call kmain
    hlt

; This section declares static variables
section .bss
align 4096

page_table_l4:
    resb 4096
page_table_l3:
    resb 4096
page_table_l2:
    resb 4096

stack_bottom:
    resb 4096 * 4
stack_top:

; Source for this code can be found here https://youtu.be/pXzortxPZR8?list=PLxN4E629pPnKKqYsNVXpmCza8l0Jb6l8-&t=560
