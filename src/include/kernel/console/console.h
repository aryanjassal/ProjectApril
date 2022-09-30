#pragma once

// Include files that declare the uint_t and struct implementations
#include <stddef.h>
#include <stdint.h>

// Define the maximum number of lines and cells that the VGA console can have in default text mode
#define VGA_CELLS 80
#define VGA_LINES 25

// Define default VGA console colours
#define VGA_COLOUR_BLACK        0
#define VGA_COLOUR_BLUE         1
#define VGA_COLOUR_GREEN        2
#define VGA_COLOUR_CYAN         3
#define VGA_COLOUR_RED          4
#define VGA_COLOUR_MAGENTA      5
#define VGA_COLOUR_BROWN        6
#define VGA_COLOUR_LIGHT_GRAY   7
#define VGA_COLOUR_DARK_GRAY    8
#define VGA_COLOUR_LIGHT_BLUE   9
#define VGA_COLOUR_LIGHT_GREEN  10
#define VGA_COLOUR_LIGHT_CYAN   11
#define VGA_COLOUR_LIGHT_RED    12
#define VGA_COLOUR_PINK         13
#define VGA_COLOUR_YELLOW       14
#define VGA_COLOUR_WHITE        15

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

//? kok could be redundant
// void kok(char *str);

// Logging utilities to print [OK] [INFO] [WARN] and [ERROR] messages
void kinfo(char *str);
void kwarn(char *str);
void kerror(char *str);