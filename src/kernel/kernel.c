#include "tty.h"

extern const char testtxt[];

void kmain() {
    print_clear();
    set_cursor_position(0, 0);
    print_set_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GRAY);
    print_string("Hello, world!");
    set_cursor_position(1, 1);
    print_string("Hi");
    set_cursor_position(20, 5);
    print_string("This should be roughly centered.");
    set_cursor_position(30, 10);
    print_string(testtxt);

    return;
}