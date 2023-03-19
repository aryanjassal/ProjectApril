#ifndef __DEV_KEYBOARD_H__
#define __DEV_KEYBOARD_H__

#include <stdint.h>

// Define IO ports used by the keyboard
#define KB_DATA 0x60
#define KB_CMD  0x64

// The assembly keyboard interrupt handler wrapper
extern void keyboard_handler();

// Initialise the PS/2 keyboard input system
void keyboard_init();

// Initialise the default keyboard map
static const char kbmap_default[128] = {
  // -------------ROW 1--------------------
  0, /* null key */
  0x1b, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  // -------------ROW 2--------------------
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  // -------------ROW 3--------------------
  0, /* left control pressed */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
  0, /* left shift pressed */
  '\\',
  // -------------ROW 4--------------------
  'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
  0, /* right shift pressed */
  '*',
  // -------------ROW 5--------------------
  0, /* left alt pressed */
  ' ',
  0, /* caps lock */
  // -------------ROW 6--------------------
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* function keys 1-10 */
  // -------------ROW 7--------------------
  0, /* numlock pressed */
  0, /* scroll lock pressed */
  // -------------KEYPD--------------------
  '7', '8', '9', '-',
  '4', '5', '6', '+',
  '1', '2', '3', '0', '.',
  // -------------NUMLK--------------------
  0, 0, 0, /* null keys */
  // -------------FN HI--------------------
  0, 0, /* function keys 11 and 12 */
  // -------------OTHER--------------------
  0 /* other keys are undefined */
};

#endif