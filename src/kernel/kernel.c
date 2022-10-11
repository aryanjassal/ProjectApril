#include "io/console.h"
#include "io/string.h"
#include "cpu/pic.h"
#include "cpu/isr.h"
#include "cpu/idt.h"
#include "utils.h"

void kmain() {
  // Print debug logs and messages to the user
  kclear();
  kok("Boot successful.");

  // Initialise interrupts
  idt_init();
  pic_init();
  // keyboard_init();

  // Testing interrupts
  asm("int $3");
  asm("int $4");
  asm("int $15");

  // The computer should never reach this part of the kernel
  // If it did, then notify the kernel and halt the computer
  kerror("EOK [END OF KERNEL]");
  halt();
}