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
  char buf[80];
  switch (registers.int_num) {
    case 0x0d:
      strcpy(msg, "GENERAL PROTECTION FAULT [CODE: ");
      strcat(msg, utoa(registers.err_code, buf, 2));
      strcat(msg, " (0x");
      strcat(msg, utoa(registers.err_code, buf, 16));
      strcat(msg, ")]");
      kerror(msg);
      // halt();
      break;

    case 0x20:
      kinfo("IRQ0: TICK");
      pic_send_eoi(0);
      break;
    
    default:
      memset(msg, 0, 80);
      strcat(msg, "Unhandled interrupt: 0x");
      strcat(msg, utoa(registers.int_num, buf, 16));
      kwarn(msg);
      break;
  }
}
