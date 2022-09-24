#include "idt.h"
#include "utils.h"
#include "console.h"
#include "exceptions_handler.h"

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

  set_trap_gate(0, (unsigned)_divide_error);
  // set_trap_gate(0, (unsigned)_int00);
  // set_trap_gate(1, (unsigned)_int01);
  // set_trap_gate(2, (unsigned)_int02);
  // set_trap_gate(3, (unsigned)_int03);
  // set_trap_gate(4, (unsigned)_int04);
  // set_trap_gate(5, (unsigned)_int05);
  // set_trap_gate(6, (unsigned)_int06);
  // set_trap_gate(7, (unsigned)_int07);
  // set_trap_gate(8, (unsigned)_int08);
  // set_trap_gate(9, (unsigned)_int09);
  // set_trap_gate(10, (unsigned)_int10);
  // set_trap_gate(11, (unsigned)_int11);
  // set_trap_gate(12, (unsigned)_int12);
  // set_trap_gate(13, (unsigned)_int13);
  // set_trap_gate(14, (unsigned)_int14);
  // set_trap_gate(15, (unsigned)_int15);
  // set_trap_gate(16, (unsigned)_int16);
  // set_trap_gate(17, (unsigned)_int17);
  // set_trap_gate(18, (unsigned)_int18);
  // set_trap_gate(19, (unsigned)_int19);
  // set_trap_gate(20, (unsigned)_int20);
  // set_trap_gate(21, (unsigned)_int21);

  // // TODO: write a reserved handler
  // for (int i = 22; i < 32; i++) {
  //   set_trap_gate(i, _reserved);
  // }
}

// Install a new entry in the IDT table
void idt_set_gate(uint8_t num, uint32_t base, uint8_t segment_selector, uint8_t flags) {
  // Print debug info to the user
  char* buf[255];
  itoa(num, buf, 10);

  console_print_string("Installing IDT Handler #");
  console_print_string(buf);
  console_print_char('\n');

  // Set the corresponding IDT data for the entry
  idt[num].base_low = (base & 0xffff);
  idt[num].base_high = ((base >> 16) & 0xffff);
  idt[num].segment_selector = segment_selector;
  idt[num].reserved = 0;
  idt[num].flags = flags;
}

// Simplified setting up a new interrupt gate
// void set_interrupt_gate(uint8_t num, uint8_t handler) {
//   idt_set_gate(num, 0x00000000, handler, 0b10001110);
// }

// Simplified setting up a new trap gate
void set_trap_gate(uint8_t num, uint32_t handler) {
  idt_set_gate(num, handler, GDT_CODE, 0b10001111);
}

