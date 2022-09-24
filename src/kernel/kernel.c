#include "console.h"
#include "utils.h"
// #include "idt.h"
// #include "pic.h"

void kernel_main() {
  // Test out various screen features and print basic debug information
  console_set_cursor_position(0, 0);
  console_set_colour(VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  console_clear();
  console_print_string("Hello, world!\n");
  console_print_string("Welcome to my C kernel!\n");

  // Load the interrupt descriptor table
  // idt_load();

  // Remap the PICs
  // The typical offset values used are 0x20 for the master chip and 0x28 for the slave chip
  // pic_remap(0x20, 0x28);

  // Initialise the IDT with the default 32 entries
  // idt_init();

  // Testing if the first (zeroth) interrupt works
  // int i = 0 / 0;
  // console_print_string("\nhow did i just divide by zero?");

  // Halt the kernel when it reaches end of execution because it should normally never happen
  for(;;);
}
