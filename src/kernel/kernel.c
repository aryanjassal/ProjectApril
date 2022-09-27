#include "console/console.h"
// #include "cpu/idt.h"
#include "utils.h"

void kernel_main() {
  // kclear();
  // kset_colour(VGA_COLOUR_LIGHT_BLUE, VGA_COLOUR_BLACK);
  // kputs(":)");
  // kset_colour(VGA_COLOUR_LIGHT_RED, VGA_COLOUR_BLACK);
  // kputs(" yup still works");
  
  // kerror("EOK [END OF KERNEL]");

  console_set_colour(VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  console_clear();
  console_print_string("THIS WORKED\n");
  console_set_colour(VGA_COLOUR_LIGHT_RED, VGA_COLOUR_BLACK);
  console_print_string("THIS WORKED TOO\n");
  console_set_colour(VGA_COLOUR_LIGHT_GREEN, VGA_COLOUR_BLACK);
  console_print_string("SO DID THIS\n");

  halt();
}
