#include "utils.h"
#include <stdint.h>
#include <stddef.h>

// Permanently halt the computer
void halt() {
  asm("cli");
  for(;;) {
    asm("hlt");
  }
}