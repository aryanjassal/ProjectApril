#pragma once

#include <stddef.h>
#include <stdint.h>

// Define an enum that stores all the default VGA console colours
static enum VGA_COLOURS {
  VGA_COLOUR_BLACK = 0,
  VGA_COLOUR_BLUE = 1,
  VGA_COLOUR_GREEN = 2,
  VGA_COLOUR_CYAN = 3,
  VGA_COLOUR_RED = 4,
  VGA_COLOUR_MAGENTA = 5,
  VGA_COLOUR_BROWN = 6,
  VGA_COLOUR_LIGHT_GRAY = 7,
  VGA_COLOUR_DARK_GRAY = 8,
  VGA_COLOUR_LIGHT_BLUE = 9,
  VGA_COLOUR_LIGHT_GREEN = 10,
  VGA_COLOUR_LIGHT_CYAN = 11,
  VGA_COLOUR_LIGHT_RED = 12,
  VGA_COLOUR_PINK = 13,
  VGA_COLOUR_YELLOW = 14,
  VGA_COLOUR_WHITE = 15
};

// Clear the screen by replacing all the characters by spaces and reset the internal cursor position
void console_clear();

// Print one character onto the screen
void console_print_char(char ch);

// Print a string onto the screen and increment the internal cursor position respectively
void console_print_string(char* str);

// Set the foreground and the background colour of the text using two 8-bit integers
void console_set_colour(uint8_t foreground, uint8_t background);

// Set the cursor position to the given x and y value
void console_set_cursor_position(uint8_t x, uint8_t y);
