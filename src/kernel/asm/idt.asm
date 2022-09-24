[GLOBAL asm_load_idt]
[EXTERN idt_descriptor]

asm_load_idt:
  lidt[idt_descriptor]
  sti
  ret
