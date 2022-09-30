[BITS 16]

; Set up the Global Descriptor Table
gdt_table:
  ; The first entry in the GDT should always be null
  gdt_null:
    dq 0
    dq 0
  
  ; Refer to the segment descriptor table found at https://wiki.osdev.org/global_descriptor_table 
  ; This defines the code segment of the GDT
  gdt_code:
    dw 0xffff       ; The limit of the code segment (4GiB)
    dw 0            ; The base of the code segment (starts at 0)
    db 0            ; The base address extends further
    db 10011010b    ; Setting the access bits (refer to the access byte table using the link above)
    db 11001111b    ; First 4 bits (1111b) is another part of the limit. The rest 4 bits are flags. Go to the osdev wiki and look at the flags table.
    db 0            ; This is the final part of the base
  
  ; This defines the data segment of the GDT
  ; Basically the same as the code segment except some minor differences
  ; Refer to http://www.osdever.net/tutorials/view/the-world-of-protected-mode for more information
  gdt_data:
    dw 0xffff       ; The limit of the code segment (4GiB)
    dw 0            ; The base of the code segment (starts at 0)
    db 0            ; The base address extends further
    db 10010010b    ; Setting the access bits (refer to the access byte table using the link above)
    db 11001111b    ; First 4 bits (1111b) is another part of the limit. The rest 4 bits are flags. Go to the osdev wiki and look at the flags table.
    db 0            ; This is the final part of the base
  
; This is where the GDT table description ends. Useful for size calculation during compile time.
gdt_end:

; The actual GDT descriptor table
gdt_desc:
  dw gdt_end - gdt_table - 1    ; This is the total size of the GDT table minus 1 as per the requirements
  dd gdt_table

; Declaring useful GDT variables
CODESEG equ gdt_code - gdt_null
DATASEG equ gdt_data - gdt_null