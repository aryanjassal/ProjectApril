// TODO: reorganise the project structure... yet again...
#include "dev/keyboard.h"
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
  keyboard_init();

  // The main program loop to test out interrupts
  for(;;);

  // The computer should never reach this part of the kernel
  // If it did, then notify the kernel and halt the computer
  kerror("EOK [END OF KERNEL]");
  halt();
}