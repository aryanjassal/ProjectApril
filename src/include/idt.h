#include <stdint.h>

// Define useful constants
#define IDT_MAX_SIZE    256
#define GDT_CODE        0x08
// #define IRQ_BASE        32

// Loads the interrupt descriptor table
void idt_load();

// Initialises the first 32 entries within the IDT in accordance to Intel's specifications
void idt_init();

// Set a new entry in the IDT table
// void idt_set_gate(uint8_t num, uint32_t base, uint8_t segment_selector, uint8_t flags);

// Simplified setting up a new interrupt gate
// void set_interrupt_gate(uint8_t num, uint8_t handler);

// Simplified setting up a new trap gate
void set_trap_gate(uint8_t num, uint32_t handler);