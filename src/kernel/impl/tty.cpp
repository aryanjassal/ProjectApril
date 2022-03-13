#include "tty.h"
#include "io.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;

// This keeps track of current column, row, and color 
size_t col = 0;
size_t row = 0;
uint8_t color = VGA_COLOR_YELLOW | VGA_COLOR_DARK_GRAY << 4;

void set_cursor_position(uint8_t x, uint8_t y) {
    uint16_t position = x + NUM_COLS * y;

    outb(0x3d4, 0x0f);
    outb(0x3d5, (unsigned char)(position & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (unsigned char)((position >> 8) & 0xff));

    row = y;
    col = x;
}

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }    
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 1; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col > NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color
    };

    col++;
}

void print_string(char* str) {
    for (size_t i = 0;; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

char* hex_to_string_output[128];
template<typename T>
const char* hex_to_string(T value) {
    T* val_pointer = &value;
    uint8_t *ptr;
    uint8_t temp;
    uint8_t size = *(sizeof(T)) * 2 - 1;

    for (uint8_t i = 0; i < size; i++) {
        ((uint8_t*)val_pointer + i);
        temp = ((*ptr & 0xf0) >> 4);
        hex_to_string_output[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
        temp = (*ptr & 0x0f);
        hex_to_string_output[size - (i * 2)] = temp + (temp > 9 ? 55 : 48);
    }
    hex_to_string_output[size + 1] = 0;

    return hex_to_string_output;
}
