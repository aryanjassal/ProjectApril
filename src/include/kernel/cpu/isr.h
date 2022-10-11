#pragma once

#include <stdint.h>

// Define a struct that will store the format of the pushed registers for interrupts
typedef struct isr_registers_t {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_num, err_code;
  // Intel manual says to use this method for ring0 but...
  uint32_t eip, cs, eflags;
  // James Molly's tutorial says to use this format
  // uint32_t eip, cs, eflags, user_esp, ss;
} __attribute__((packed))
isr_registers_t;

// Initialise the keyboard input system
// TODO: move it to a more appropriate place
void keyboard_init();