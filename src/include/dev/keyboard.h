#pragma once

#include <stdint.h>

// Define IO ports used by the keyboard
#define KB_DATA 0x60
#define KB_CMD  0x64

// The assembly keyboard interrupt handler wrapper
extern void keyboard_handler();

// Initialise the PS/2 keyboard input system
void keyboard_init();

// // Keyboard IRQ registers
// typedef struct irq_registers_t {
//   uint32_t ds;
//   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
//   // uint32_t int_num, err_code;
//   // Intel manual says to use this method for ring0 but...
//   uint32_t eip, cs, eflags;
//   // James Molly's tutorial says to use this format
//   // uint32_t eip, cs, eflags, user_esp, ss;
// } __attribute__((packed))
// irq_registers_t;