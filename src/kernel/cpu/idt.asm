[GLOBAL idt_load]
[EXTERN idt_descriptor]
idt_load:
  lidt [idt_descriptor]
  ret