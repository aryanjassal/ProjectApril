#pragma once
// #include "typedefs.h"
#include <stddef.h>
#include <stdint.h>

enum {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GRAY = 7,
    VGA_COLOR_DARK_GRAY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_PINK = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15
};

void print_clear();
void print_char(char character);
void print_string(char* str);
void print_set_color(uint8_t foreground, uint8_t background);
// void set_cursor_position(uint16_t position);
void set_cursor_position(uint8_t x, uint8_t y);
// uint16_t position_from_coords(uint8_t x, uint8_t y);
