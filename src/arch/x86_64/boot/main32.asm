global start
extern long_mode_start

[section .text]
[bits 32]
start:
    ; Move the location of the top of the stack to the stack pointer
    mov esp, stack_top

    call check_multiboot
    call check_cpuid
    call check_long_mode

    ; This is to map the memory addresses to somthing like an index
    ; for easier and faster access to the memory addresses
    call setup_page_tables
    call enable_paging

    ; Load the Global Descriptor Table (GDT)
    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:long_mode_start

    hlt

check_multiboot:
    ; The value of <eax> is automatically changed to <0x36d76289> if the 
    ; operating system is multiboot compliant
    cmp eax, 0x36d76289
    jne .no_multiboot
    ret

.no_multiboot:
    mov al, "M"
    jmp error

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

setup_page_tables:
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

; This section declares static variables
[section .bss]
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


; This section is for read-only data
[section .rodata]
gdt64:
    dq 0  ; The GDT section must always start with 0

    .code_segment: equ $ - gdt64  ; Get offset of the code segment from the GDT table 
    ; Enable <executable> flag (bit 43), set <descriptor> flag (bit 44) to 1 for code and data segment,
    ; enable the <present> flag (bit 47), enable <64 bit> flag (bit 53)
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)  ; Setting required flags for code segment, whatever that means

    .pointer:
        dw $ - gdt64 - 1  ; Set length of GDT table first
        dq gdt64  ; Store the pointer

; For more information, visit https://youtu.be/wz9CZBeXR6U?list=PLZQftyCk7_SeZRitx5MjBKzTtvk0pHMtp
