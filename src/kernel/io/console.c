#include <stdint.h>
#include "io/console.h"
#include "io/io.h"
#include "utils.h"
#include "mem.h"

#include "io/string.h"

// Use the character struct to parse the VGA memory to a variable
static vgachar_t *vgamem = (vgachar_t *)0xb8000;

// Create a new console, which stores information about the current terminal
vgaconsole_t console = { 0, 0, 0x0f };

// Sets the cursor position to the specified coordinates
void kset_cursor(uint8_t x, uint8_t y) {
  uint16_t position = x + VGA_CELLS * y;

  outb(0x3d4, 0x0f);
  outb(0x3d5, (int8_t)(position & 0xff));
  outb(0x3d4, 0x0e);
  outb(0x3d5, (uint8_t)((position >> 8) & 0xff));

  console.line = y;
  console.cell = x;
}

// Clears the screen by filling the VGA buffer up with empty spaces
void kclear() {
  vgachar_t space = { ' ', console.colour };
  for (uint16_t cell = 0; cell < VGA_CELLS * VGA_LINES; cell++) {
    vgamem[cell] = space;
  }
  kset_cursor(0, 0);
}

// Print a newline in the terminal. If it is the last line, scroll down.
void kputnl() {
  console.cell = 0;

  if (console.line < VGA_LINES - 1) {
    console.line++;
    kset_cursor(0, console.line);
    return;
  }

  for (uint16_t i = 0; i < (VGA_CELLS * VGA_LINES); i++) {
    vgamem[i] = vgamem[i + VGA_CELLS];
  }

  kset_cursor(0, console.line);
  vgachar_t char_space;
  char_space.character = ' ';
  char_space.colour = console.colour;

  for (uint8_t i = 0; i < VGA_CELLS; i++) {
    vgamem[i + (VGA_CELLS * VGA_LINES)] = char_space;
  }
}

// Print a single character onto the screen
void kputc(char ch) {
  if (ch == '\n') {
    kputnl();
    return;
  }

  if (ch == '\b') {
    if (console.cell > 0) {
      console.cell--;
    } else if (console.line > 0) {
      console.cell = VGA_CELLS - 1;
      console.line--;
    }
    vgachar_t char_space = { ' ', console.colour };
    vgamem[console.cell + (VGA_CELLS * console.line)] = char_space;
    kset_cursor(console.cell, console.line);
    return;
  }
  
  if (console.cell >= VGA_CELLS) {
    kputnl();
  }

  vgachar_t character;
  character.character = ch;
  character.colour = console.colour;

  vgamem[console.cell + (VGA_CELLS * console.line)] = character;
  console.cell++;
  kset_cursor(console.cell, console.line);
}

// Print a string to the screen
void kputs(char *str) {
  for (uint16_t i = 0; ; i++) {
    char ch = str[i];

    if (ch == '\0') {
      return;
    }

    kputc(ch);
  }
}

// Logging utility to print [OK] messages
void kok(char *str) {
  console.colour = 0x0a;
  kputs("[OK]    ");
  console.colour = 0x0f;
  kputs(str);
  kputc('\n');
}

// Logging utility to print [INFO] messages
void kinfo(char *str) {
  console.colour = 0x09;
  kputs("[INFO]  ");
  console.colour = 0x0f;
  kputs(str);
  kputc('\n');
}

// Logging utility to print [WARN] messages
void kwarn(char *str) {
  console.colour = 0x0e;
  kputs("[WARN]  ");
  console.colour = 0x0f;
  kputs(str);
  kputc('\n');
}

// Logging utility to print [ERROR] messages
void kerror(char *str) {
  console.colour = 0x0c;
  kputs("[ERROR] ");
  console.colour = 0x0f;
  kputs(str);
  kputc('\n');
}