#include "tty.h"
#include "idt.h"

extern const char testtxt[];

void kmain() {
    print_clear();
    set_cursor_position(0, 0);
    print_string("Hello, world!");
    print_string(0x1234abcd);
    initialize_idt();

    return;
}