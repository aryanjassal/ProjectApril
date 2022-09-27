#pragma once

#include <stdint.h>

// Define useful constants
#define IDT_MAX_SIZE    256
#define GDT_CODE        0x08

// Externs for low-level interrupt handlers
void reserved_handler(void);
void divide_error_handler(void);
void debug_interrupt_handler(void);
void nmi_handler(void);
void breakpoint_handler(void);
void overflow_handler(void);
void bound_exceeded_handler(void);
void undefined_opcode_handler(void);
void device_not_available_handler(void);
void double_fault_handler(void);
void coprocessor_segment_overrun_handler(void);
void invalid_tss_handler(void);
void segment_not_present_handler(void);
void stack_segment_fault_handler(void);
void general_protection_fault_handler(void);
void page_fault_handler(void);
// --- ---------------------- (RESERVED)
void math_fault_handler(void);
void alignment_check_handler(void);
void machine_check_handler(void);
void floating_point_exception_handler(void);
void virtualisation_exception_handler(void);
void control_protection_exception_handler(void);

// C code to handle interrupts
void c_reserved_handler();
void c_divide_error_handler();
void c_debug_interrupt_handler();
void c_nmi_handler();
void c_breakpoint_handler();
void c_overflow_handler();
void c_bound_exceeded_handler();
void c_undefined_opcode_handler();
void c_device_not_available_handler();
void c_double_fault_handler();
void c_coprocessor_segment_overrun_handler();
void c_invalid_tss_handler();
void c_segment_not_present_handler();
void c_stack_segment_fault_handler();
void c_general_protection_fault_handler();
void c_page_fault_handler();
void c_math_fault_handler();
void c_alignment_check_handler();
void c_machine_check_handler();
void c_floating_point_exception_handler();
void c_virtualisation_exception_handler();
void c_control_protection_exception_handler();

// Loads the interrupt descriptor table
void idt_load();

// Initialises the first 32 entries within the IDT in accordance to Intel's specifications
void idt_init();

// Set a new entry in the IDT table
// void idt_set_gate(uint8_t num, uint32_t base, uint8_t segment_selector, uint8_t flags);

// Simplified setting up a new interrupt gate
void set_interrupt_gate(uint8_t num, uint32_t handler);

// Simplified setting up a new trap gate
// void set_trap_gate(uint8_t num, uint32_t handler);