#include "io/console.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "io/string.h"
#include "mem.h"
#include "utils.h"

// Declare IDT variables
idt_entry_t idt[IDT_MAX_SIZE];
idt_descriptor_t idt_descriptor;

// Initialise the Interrupt Descriptor Table
void idt_init() {
  // Set the actual table parameters up
  idt_descriptor.limit = (sizeof (struct idt_entry_t) * IDT_MAX_SIZE) - 1;
  idt_descriptor.base = (uint32_t) &idt;

  // Clear out the interrupt table, setting it all to zeroes
  memset(&idt, 0, sizeof(idt_entry_t) * IDT_MAX_SIZE);

  set_interrupt_gate(0, isr0);
  set_interrupt_gate(1, isr1);
  set_interrupt_gate(2, isr2);
  set_interrupt_gate(3, isr3);
  set_interrupt_gate(4, isr4);
  set_interrupt_gate(5, isr5);
  set_interrupt_gate(6, isr6);
  set_interrupt_gate(7, isr7);
  set_interrupt_gate(8, isr8);
  set_interrupt_gate(9, isr9);
  set_interrupt_gate(10, isr10);
  set_interrupt_gate(11, isr11);
  set_interrupt_gate(12, isr12);
  set_interrupt_gate(13, isr13);
  set_interrupt_gate(14, isr14);
  set_interrupt_gate(15, isr15);
  set_interrupt_gate(16, isr16);
  set_interrupt_gate(17, isr17);
  set_interrupt_gate(18, isr18);
  set_interrupt_gate(19, isr19);
  set_interrupt_gate(20, isr20);
  set_interrupt_gate(21, isr21);
  set_interrupt_gate(22, isr22);
  set_interrupt_gate(23, isr23);
  set_interrupt_gate(24, isr24);
  set_interrupt_gate(25, isr25);
  set_interrupt_gate(26, isr26);
  set_interrupt_gate(27, isr27);
  set_interrupt_gate(28, isr28);
  set_interrupt_gate(29, isr29);
  set_interrupt_gate(30, isr30);
  set_interrupt_gate(31, isr31);

  idt_load();
  kinfo("IDT successfully installed");

  asm("sti");
  kinfo("Interrupts enabled");
}

// Install a new entry in the IDT table
void idt_set_gate(uint8_t num, void *base, uint8_t flags) {
  // // Print debug info to the user
  // char msg[80];
  // char buf[4];
  // strcpy(msg, "Installing IDT Handler #");
  // strcat(msg, utoa(num, buf, 10));
  // kinfo(msg);

  uint32_t isr = (uint32_t) base;

  // Set the corresponding IDT data for the entry
  // NOTE: You cannot change the segment selector as of yet
  // NOTE: The segment selector must be 0x10, or the GDT data selector for some reason
  idt[num].base_low = isr & 0xffff;
  idt[num].base_high = (isr >> 16) & 0xffff;
  idt[num].segment_selector = GDT_DATA;
  idt[num].reserved = 0;
  idt[num].flags = flags;
}

// Simplified setting up a new interrupt gate
void set_interrupt_gate(uint8_t num, void *handler) {
  idt_set_gate(num, handler, 0b10001110);
}