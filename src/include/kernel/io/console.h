#pragma once

// Include files that declare the uint_t and struct implementations
#include <stddef.h>
#include <stdint.h>

// Define the maximum number of lines and cells that the VGA console can have in default text mode
#define VGA_CELLS 80
#define VGA_LINES 25

// Define default VGA console colours
#define VGA_COLOUR_BLACK        0x0
#define VGA_COLOUR_BLUE         0x1
#define VGA_COLOUR_GREEN        0x2
#define VGA_COLOUR_CYAN         0x3
#define VGA_COLOUR_RED          0x4
#define VGA_COLOUR_MAGENTA      0x5
#define VGA_COLOUR_BROWN        0x6
#define VGA_COLOUR_LIGHT_GRAY   0x7
#define VGA_COLOUR_DARK_GRAY    0x8
#define VGA_COLOUR_LIGHT_BLUE   0x9
#define VGA_COLOUR_LIGHT_GREEN  0xa
#define VGA_COLOUR_LIGHT_CYAN   0xb
#define VGA_COLOUR_LIGHT_RED    0xc
#define VGA_COLOUR_PINK         0xd
#define VGA_COLOUR_YELLOW       0xe
#define VGA_COLOUR_WHITE        0xf

// Create a struct to store the character information as per VGA console requirements
typedef struct vgachar_t {
  uint8_t character;
  uint8_t colour;
} vgachar_t;

// A struct to store console information
// TODO: Add a buffer which is saved to and loaded from while switching console buffers
typedef struct vgaconsole_t {
  uint8_t line;
  uint8_t cell;
  uint8_t colour;
} vgaconsole_t;

// Clear the screen
void kclear();

// Print a character onto the screen
void kputc(char ch);

// Print a string onto the screen
void kputs(char *str);

// // Print a signed 32-bit integer onto the screen
// // !NOT IMPLEMENTED!
// void kputi(int32_t num);

// // Print an unsigned 32-bit integer onto the screen
// // !NOT IMPLEMENTED!
// void kputui(uint32_t num);

// TODO: add methods to set the console colour
// TODO: add methods to individually set the foreground and the background color

// Logging utilities to print [OK] [INFO] [WARN] and [ERROR] messages
void kinfo(char *str);
void kwarn(char *str);
void kerror(char *str);
// Could be redundant
void kok(char *str);