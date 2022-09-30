#include "console/console.h"
#include "cpu/idt.h"
#include "utils.h"

// Link external assembly code implementation
extern void asm_load_idt();

// Define the struct to store the individual IDT entries
struct IDT_ENTRY {
  uint16_t base_low;
  uint16_t segment_selector;
  uint8_t reserved;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));

// Define the struct that will actually install the IDT
struct IDT_DESCRIPTOR {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

// Declare IDT variables
struct IDT_ENTRY idt[IDT_MAX_SIZE];
struct IDT_DESCRIPTOR idt_descriptor;

// Loads the interrupt descriptor table
void idt_load() {
  // Set the actual table parameters up
  idt_descriptor.limit = (sizeof (struct IDT_ENTRY) * 256) - 1;
  idt_descriptor.base = (uint32_t) &idt;

  // Clear out the interrupt table, setting it all to zeroes
  memset(&idt, 0, sizeof(struct IDT_ENTRY) * 356);

  // Call the assembly code to install the IDT
  asm_load_idt();
}

// Initialise the Interrupt Descriptor Table
void idt_init() {
  idt_load();

  set_interrupt_gate(0, (uint32_t)&divide_error_handler);
  set_interrupt_gate(1, (uint32_t)&debug_interrupt_handler);
  set_interrupt_gate(2, (uint32_t)&nmi_handler);
  set_interrupt_gate(3, (uint32_t)&breakpoint_handler);
  set_interrupt_gate(4, (uint32_t)&overflow_handler);
  set_interrupt_gate(5, (uint32_t)&bound_exceeded_handler);
  set_interrupt_gate(6, (uint32_t)&undefined_opcode_handler);
  set_interrupt_gate(7, (uint32_t)&device_not_available_handler);
  set_interrupt_gate(8, (uint32_t)&double_fault_handler);
  set_interrupt_gate(9, (uint32_t)&coprocessor_segment_overrun_handler);
  set_interrupt_gate(10, (uint32_t)&invalid_tss_handler);
  set_interrupt_gate(11, (uint32_t)&segment_not_present_handler);
  set_interrupt_gate(12, (uint32_t)&stack_segment_fault_handler);
  set_interrupt_gate(13, (uint32_t)&general_protection_fault_handler);
  set_interrupt_gate(14, (uint32_t)&page_fault_handler);
  set_interrupt_gate(15, (uint32_t)&reserved_handler);
  set_interrupt_gate(16, (uint32_t)&math_fault_handler);
  set_interrupt_gate(17, (uint32_t)&alignment_check_handler);
  set_interrupt_gate(18, (uint32_t)&machine_check_handler);
  set_interrupt_gate(19, (uint32_t)&floating_point_exception_handler);
  set_interrupt_gate(20, (uint32_t)&virtualisation_exception_handler);
  set_interrupt_gate(21, (uint32_t)&control_protection_exception_handler);

  for (int i = 22; i < 32; i++) {
    set_interrupt_gate(i, (uint32_t)&reserved_handler);
  }
}

// Install a new entry in the IDT table
void idt_set_gate(uint8_t num, uint32_t base, uint8_t segment_selector, uint8_t flags) {
  // // Print debug info to the user
  // char buf[255];
  // char intbuf[255];
  // strcat(buf, "Installing IDT Handler #");
  // strcat(buf, utoa(num, intbuf, 10));

  // kinfo(buf);

  // Set the corresponding IDT data for the entry
  idt[num].base_low = (base & 0xffff);
  idt[num].base_high = ((base >> 16) & 0xffff);
  idt[num].segment_selector = segment_selector;
  idt[num].reserved = 0;
  idt[num].flags = flags;
}

// Simplified setting up a new interrupt gate
void set_interrupt_gate(uint8_t num, uint32_t handler) {
  idt_set_gate(num, handler, GDT_CODE, 0b10001110);
}

// C code to handle interrupts
void c_reserved_handler() {
  // kputs("[INTERRUPT] RESERVED");
}
void c_divide_error_handler() {
  // kputs("[INTERRUPT] DIVIDE ERROR");
}
void c_debug_interrupt_handler() {
  // kputs("[INTERRUPT] DEBUG INTERRUPT");
}
void c_nmi_handler() {
  // kputs("[INTERRUPT] NMI");
}
void c_breakpoint_handler() {
  // kputs("[INTERRUPT] BREAKPOINT");
}
void c_overflow_handler() {
  // kputs("[INTERRUPT] OVERFLOW");
}
void c_bound_exceeded_handler() {
  // kputs("[INTERRUPT] BOUND EXCEEDED");
}
void c_undefined_opcode_handler() {
  // kputs("[INTERRUPT] UNDEFINED OPCODE");
}
void c_device_not_available_handler() {
  // kputs("[INTERRUPT] DEVICE NOT AVAILABLE");
}
void c_double_fault_handler() {
  // kputs("[INTERRUPT] DOUBLE FAULT");
}
void c_coprocessor_segment_overrun_handler() {
  // kputs("[INTERRUPT] COPROCESSOR SEGMENT OVERRUN");
}
void c_invalid_tss_handler() {
  // kputs("[INTERRUPT] INVALID TSS");
}
void c_segment_not_present_handler() {
  // kputs("[INTERRUPT] SEGMENT NOT PRESENT");
}
void c_stack_segment_fault_handler() {
  // kputs("[INTERRUPT] STACK SEGMENT FAULT");
}
void c_general_protection_fault_handler() {
  // kputs("[INTERRUPT] GENERAL PROTECTION FAULT");
}
void c_page_fault_handler() {
  // kputs("[INTERRUPT] PAGE FAULT");
}
void c_math_fault_handler() {
  // kputs("[INTERRUPT] MATH FAULT");
}
void c_alignment_check_handler() {
  // kputs("[INTERRUPT] ALIGNMENT CHECK INTERRUPT");
}
void c_machine_check_handler() {
  // kputs("[INTERRUPT] MACHINE CHECK INTERRUPT");
}
void c_floating_point_exception_handler() {
  // kputs("[INTERRUPT] FLOATING POINT EXCEPTION");
}
void c_virtualisation_exception_handler() {
  // kputs("[INTERRUPT] VIRTUALISATION EXCEPTION");
}
void c_control_protection_exception_handler() {
  // kputs("[INTERRUPT] CONTROL PROTECTION EXCEPTION");
}