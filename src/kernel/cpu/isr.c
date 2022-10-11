#include "io/console.h"
#include "io/string.h"
#include "io/io.h"
#include "cpu/isr.h"
#include "cpu/pic.h"
#include "cpu/idt.h"
#include "mem.h"
#include "utils.h"

// General ISR handler
// TODO: write proper handlers that handle each individual interrupt properly
void isr_handler(isr_registers_t registers) {
  char msg[80];
  memset(msg, 0, 80);
  strcat(msg, "Unhandled interrupt: 0x");
  char buf[4];
  strcat(msg, utoa(registers.int_num, buf, 16));

  kwarn(msg);
}
