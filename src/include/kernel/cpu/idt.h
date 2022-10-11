#pragma once

#include <stdint.h>

// Define useful constants
#define IDT_MAX_SIZE    256
#define GDT_DATA        0x10

// Link external assembly code implementation
// extern void idt_load(uint32_t idt_ptr);
extern void idt_load();

// Define the struct to store the individual IDT entries
typedef struct idt_entry_t {
  uint16_t base_low;
  uint16_t segment_selector;
  uint8_t reserved;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed))
idt_entry_t;

// Define the struct that will actually install the IDT
typedef struct idt_descriptor_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed))
idt_descriptor_t;

// void isr_handler(isr_registers_t registers);
void isr_handler();

// Externs for the software interrupt handlers
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// Initialises the first 32 entries within the IDT in accordance to Intel's specifications
void idt_init();

// Simplified setting up a new interrupt gate
void set_interrupt_gate(uint8_t num, void *handler);