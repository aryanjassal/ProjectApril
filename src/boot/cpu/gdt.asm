[BITS 16]

; set up the gdt table
gdt_table:
  ; the first entry in the gdt should always be null
  gdt_null:
    dq 0
    dq 0
  
  ; refer to the segment descriptor table found at https://wiki.osdev.org/global_descriptor_table 
  ; this defines the code segment of the gdt
  gdt_code:
    dw 0xffff       ; the limit of the code segment (4gib)
    dw 0            ; the base of the code segment (starts at 0)
    db 0            ; the base address extends further
    db 10011010b    ; setting the access bits (refer to the access byte table using the link above)
    db 11001111b    ; first 4 bits (1111b) is another part of the limit. the rest 4 bits are flags. go to the osdev wiki and look at the flags table.
    db 0            ; this is the final part of the base
  
  ; this defines the data segment of the gdt
  ; basically the same as the code segment except some minor differences
  ; refer to http://www.osdever.net/tutorials/view/the-world-of-protected-mode for more information
  gdt_data:
    dw 0xffff       ; the limit of the code segment (4gib)
    dw 0            ; the base of the code segment (starts at 0)
    db 0            ; the base address extends further
    db 10010010b    ; setting the access bits (refer to the access byte table using the link above)
    db 11001111b    ; first 4 bits (1111b) is another part of the limit. the rest 4 bits are flags. go to the osdev wiki and look at the flags table.
    db 0            ; this is the final part of the base
  
; this is where the gdt table description ends. useful for size calculation during compile time.
gdt_end:

; the actual gdt descriptor table
gdt_desc:
  dw gdt_end - gdt_table - 1    ; this is the total size of the gdt table minus 1 as per the requirements
  dd gdt_table

; Declaring useful GDT variables
CODESEG equ gdt_code - gdt_null
DATASEG equ gdt_data - gdt_null