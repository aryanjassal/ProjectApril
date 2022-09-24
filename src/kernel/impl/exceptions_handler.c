#include "exceptions_handler.h"
#include "console.h"
#include "pic.h"

void _divide_error() {
  console_set_colour(VGA_COLOUR_WHITE, VGA_COLOUR_RED);
  console_print_string("ERROR: cannot divide by zero");
  pic_send_eoi(0);
}