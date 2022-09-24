#include "console.h"
#include "utils.h"

void kernel_main() {
  // Test out various screen features and print basic debug information
  console_set_cursor_position(0, 0);
  console_set_colour(VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  console_clear();
  console_print_string("Hello, world!\n");
  console_print_string("Welcome to my C kernel!\n");

  // Halt the kernel when it reaches end of execution because it should normally never happen
  for(;;);
}
