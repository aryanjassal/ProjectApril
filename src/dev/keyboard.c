#include "dev/keyboard.h"
#include "kernel/io/io.h"
#include "kernel/io/console.h"
#include "kernel/io/string.h"
#include "kernel/cpu/idt.h"
#include "kernel/cpu/pic.h"
#include "kernel/utils.h"

// Handle keyboard interrupts
// void isr_keyboard(isr_registers_t registers) {
void isr_keyboard() {
  char buf[4];
  kinfo(utoa(inb(0x64), buf, 16));
  // pic_send_eoi(0x20 - registers.int_num);
  pic_send_eoi(1);
}

// Initialise the keyboard input system
void keyboard_init() {
  set_interrupt_gate(0x21, isr_keyboard);
  outb(0x64, 0xae);
  outb(0x64, 0xab);

  // uint8_t response = inb(0x60);
  // switch (response) {
  //   case 0x00:
  //     kok("PS/2 Port 1 self-test passed!");
  //     break;
    
  //   case 0x01:
  //     kerror("PS/2 Port 1 self-test failed: clock line stuck low");
  //     break;
    
  //   case 0x02:
  //     kerror("PS/2 Port 1 self-test failed: clock line stuck high");
  //     break;

  //   case 0x03:
  //     kerror("PS/2 Port 1 self-test failed: data line stuck low");
  //     break;

  //   case 0x04: 
  //     kerror("PS/2 Port 1 self-test failed: data line stuck high");
  //     break;
    
  //   default:
  //     kerror("PS/2 Port 1 self-test failed: undefined result");
  //     break;
  // }

  // outb(0x60, 0xff);
  // if (inb(0x64) == 0xaa) {
  //   kinfo("Keyboard reset");
  //   kok("Keyboard self-test passed!");
  // } else {
  //   kerror("Keyboard failed to initialise");
  //   halt();
  // }

  while(1) {
    char buf[4];
    kinfo(utoa(inb(0x60), buf, 16));
  }
  // kinfo(utoa(inb(0x64), buf, 16));

  // halt();
}