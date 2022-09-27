; TODO: this is shitty code with a lot of code repetition. make it beautiful and elegant

; Load the Interrupt Descriptor Table as provided by the idt_descriptor
[GLOBAL asm_load_idt]
[EXTERN idt_descriptor]
asm_load_idt:
  lidt[idt_descriptor]
  sti
  ret

; Handle reserved interrupts
[GLOBAL reserved_handler]
[EXTERN c_reserved_handler]
reserved_handler:
  pushad
  cld
  call c_reserved_handler
  popad
  iret

; Handle interrupt 0 (divide by zero)
[GLOBAL divide_error_handler]
[EXTERN c_divide_error_handler]
divide_error_handler:
  pushad
  cld
  call c_divide_error_handler
  popad
  iret

; Handle interrupt 1 (debug)
[GLOBAL debug_interrupt_handler]
[EXTERN c_debug_interrupt_handler]
debug_interrupt_handler:
  pushad
  cld
  call c_debug_interrupt_handler
  popad
  iret

; Handle interrupt 2 (non-maskable interrupt or NMI)
[GLOBAL nmi_handler]
[EXTERN c_nmi_handler]
nmi_handler:
  pushad
  cld
  call c_nmi_handler
  popad
  iret

; Handle interrupt 3 (breakpoint)
[GLOBAL breakpoint_handler]
[EXTERN c_breakpoint_handler]
breakpoint_handler:
  pushad
  cld
  call c_breakpoint_handler
  popad
  iret

; Handle interrupt 4 (overflow)
[GLOBAL overflow_handler]
[EXTERN c_overflow_handler]
overflow_handler:
  pushad
  cld
  call c_overflow_handler
  popad
  iret

; Handle interrupt 5 (BOUND exceeded)
[GLOBAL bound_exceeded_handler]
[EXTERN c_bound_exceeded_handler]
bound_exceeded_handler:
  pushad
  cld
  call c_bound_exceeded_handler
  popad
  iret

; Handle interrupt 6 (undefined opcode)
[GLOBAL undefined_opcode_handler]
[EXTERN c_undefined_opcode_handler]
undefined_opcode_handler:
  pushad
  cld
  call c_undefined_opcode_handler
  popad
  iret

; Handle interrupt 7 (no math coprocessor / device unavailable)
[GLOBAL device_not_available_handler]
[EXTERN c_device_not_available_handler]
device_not_available_handler:
  pushad
  cld
  call c_device_not_available_handler
  popad
  iret

; Handle interrupt 8 (double fault)
[GLOBAL double_fault_handler]
[EXTERN c_double_fault_handler]
double_fault_handler:
  pushad
  cld
  call c_double_fault_handler
  popad
  iret

; Handle interrupt 9 (coprocessor segment overrun)
[GLOBAL coprocessor_segment_overrun_handler]
[EXTERN c_coprocessor_segment_overrun_handler]
coprocessor_segment_overrun_handler:
  pushad
  cld
  call c_coprocessor_segment_overrun_handler
  popad
  iret

; Handle interrupt 10 (invalid TSS)
[GLOBAL invalid_tss_handler]
[EXTERN c_invalid_tss_handler]
invalid_tss_handler:
  pushad
  cld
  call c_invalid_tss_handler
  popad
  iret

; Handle interrupt 11 (segment not present)
[GLOBAL segment_not_present_handler]
[EXTERN c_segment_not_present_handler]
segment_not_present_handler:
  pushad
  cld
  call c_segment_not_present_handler
  popad
  iret

; Handle interrupt 12 (stack segment fault)
[GLOBAL stack_segment_fault_handler]
[EXTERN c_stack_segment_fault_handler]
stack_segment_fault_handler:
  pushad
  cld
  call c_stack_segment_fault_handler
  popad
  iret

; Handle interrupt 13 (general protection fault)
[GLOBAL general_protection_fault_handler]
[EXTERN c_general_protection_fault_handler]
general_protection_fault_handler:
  pushad
  cld
  call c_general_protection_fault_handler
  popad
  iret

; Handle interrupt 14 (page fault)
[GLOBAL page_fault_handler]
[EXTERN c_page_fault_handler]
page_fault_handler:
  pushad
  cld
  call c_page_fault_handler
  popad
  iret

; Handle interrupt 16 (math fault)
[GLOBAL math_fault_handler]
[EXTERN c_math_fault_handler]
math_fault_handler:
  pushad
  cld
  call c_math_fault_handler
  popad
  iret

; Handle interrupt 17 (alignment fault)
[GLOBAL alignment_check_handler]
[EXTERN c_alignment_check_handler]
alignment_check_handler:
  pushad
  cld
  call c_alignment_check_handler
  popad
  iret

; Handle interrupt 18 (machine check)
[GLOBAL machine_check_handler]
[EXTERN c_machine_check_handler]
machine_check_handler:
  pushad
  cld
  call c_machine_check_handler
  popad
  iret

; Handle interrupt 19 (floating point exception)
[GLOBAL floating_point_exception_handler]
[EXTERN c_floating_point_exception_handler]
floating_point_exception_handler:
  pushad
  cld
  call c_floating_point_exception_handler
  popad
  iret

; Handle interrupt 20 (virtualisation exception)
[GLOBAL virtualisation_exception_handler]
[EXTERN c_virtualisation_exception_handler]
virtualisation_exception_handler:
  pushad
  cld
  call c_virtualisation_exception_handler
  popad
  iret

; Handle interrupt 21 (control protection exception)
[GLOBAL control_protection_exception_handler]
[EXTERN c_control_protection_exception_handler]
control_protection_exception_handler:
  pushad
  cld
  call c_control_protection_exception_handler
  popad
  iret