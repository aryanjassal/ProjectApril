#include "dev/keyboard.h"
#include "kernel/io/io.h"
#include "kernel/io/console.h"
#include "kernel/io/string.h"
#include "kernel/cpu/idt.h"
#include "kernel/cpu/pic.h"
#include "kernel/utils.h"

// The latest scancode returned by the IRQ
// TODO: Make it an array instead and store multiple keys (upto a limit of course)
uint16_t scancode;

// Handle keyboard interrupts
// void irq_keyboard_handler(irq_registers_t registers) {
void irq_keyboard_handler() {
  char buf[4];
  uint16_t kb_in = inb(0x60);
  if (kb_in != 0xfa) {
    scancode = kb_in;
    kinfo(utoa(scancode, buf, 16));
  }
  // if((inb(0x64) & 1) == 0) scancode = inb(0x60);

  // char buf[4];

  // for(int i = 1000; i > 0; i++) {
  //   // Check if scan code is ready
  //   if((inb(0x64) & 1) == 0) continue;
  //   // Get the scan code
  //   scancode = inb(0x60);
  //   // kinfo(utoa(scancode, buf, 16));
  //   break;
  // }

  pic_send_eoi(1);
}

// Initialise the keyboard input system
void keyboard_init() {
  set_interrupt_gate(0x21, keyboard_handler);
}