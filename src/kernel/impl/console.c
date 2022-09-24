#include "console.h"
#include "io.h"
#include <stdint.h>

// Create a struct to store the character information as per VGA console requirements
typedef struct {
  uint8_t character;
  uint8_t colour;
} Char;

// Use the character struct to parse the VGA memory to a variable
static Char *vgamem = (Char *) 0xb8000;

// Create a struct to store important information regarding the tty information
typedef struct {
  uint16_t row;
  uint16_t col;
  uint16_t max_rows;
  uint16_t max_cols;
  uint8_t colour;
} Console;

// Create a new console, which stores information about the current terminal environment
Console console = (Console) {
  row: 0,
  col: 0,
  max_rows: 25,
  max_cols: 80,
  colour: VGA_COLOUR_WHITE | VGA_COLOUR_BLACK << 4
};

// Sets the cursor position to the specified coordinates
void console_set_cursor_position(uint8_t x, uint8_t y) {
  // Get the absolute linear position to set the cursor to
  uint16_t position = x + console.max_cols * y;

  // Set the lower half of the cursor position to 0
  outb(0x3d4, 0x0f);
  outb(0x3d5, (unsigned char)(position & 0xff));

  // Set the higher half of the cursor position to 0
  outb(0x3d4, 0x0e);
  outb(0x3d5, (unsigned char)((position >> 8) & 0xff));

  // Update the current row and column in the console struct
  console.row = y;
  console.col = x;
}

// Clear a row as per the provided argument
void console_clear_row(uint8_t row) {
  // Create the space character using the struct
  Char space;
  space.character = ' ';
  space.colour = console.colour;

  // For each column in the row, replace it with a space character
  for (size_t col = 0; col < console.max_cols; col++) {
    vgamem[col + (console.max_cols * row)] = space;
  }

  console_set_cursor_position(0, row);
}

// Clears the screen by filling the VGA buffer up with empty spaces
void console_clear() {
  // For each row in the terminal, clear the row
  for (size_t row = 0; row < console.max_rows; row++) {
    console_clear_row(row);
  }

  console_set_cursor_position(0, 0);
}

// Print a newline in the terminal. If it is the last line, scroll down.
void console_print_newline() {
  // Set the column to zero
  console.col = 0;

  // If the current row is less than the maximum number of rows in the console, then just clear the row
  // and increment the console row counter
  if (console.row < console.max_rows - 1) {
    console.row++;
    console_clear_row(console.row);
    console_set_cursor_position(0, console.row);
    return;
  }
  
  // Otherwise, shift all lines up by one to clear up the last row
  for (size_t row = 0; row < console.max_rows; row++) {
    for (size_t col = 0; col < console.max_cols; col++) {
      Char ch = vgamem[col + (console.max_cols * row)];
      vgamem[col + (console.max_cols * (row - 1))] = ch;
    }
  }

  // Then clear the last row
  console_clear_row(console.row);
  console_set_cursor_position(0, console.max_rows - 1);
}

// Print a singular character onto the screen
void console_print_char(char ch) {
  // If the character is newline, the print a newline and return
  if (ch == '\n') {
    console_print_newline();
    return;
  }
  
  // Otherwise, if the current number of column is greater than the maximum number of columns,
  // then print the char in the nex line
  if (console.col > console.max_cols) {
    console_print_newline();
  }

  // Create the character from the Char struct
  Char character;
  character.character = ch;
  character.colour = console.colour;

  // Put the character in the memory address pointed to by the internal row and column counter
  vgamem[console.col + (console.max_cols * console.row)] = character;
  console.col++;
  console_set_cursor_position(console.col, console.row);
}

// Print a string to the console output
void console_print_string(char* str) {
  for (size_t i = 0; ; i++) {
    char ch = str[i];

    // If the next character in the string is a null character (\0), then return 
    if (ch == '\0') {
      return;
    }

    // Print the character onto the screen
    console_print_char(ch);
  }
}

// Set the foreground and background colour of the console
void console_set_colour(uint8_t foreground, uint8_t background) {
  console.colour = foreground | background << 4;
}