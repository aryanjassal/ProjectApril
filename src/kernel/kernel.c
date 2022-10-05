#include "console/console.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "utils.h"
#include "io/string.h"

void kmain() {
  kinfo("Jumping to C kernel successful!");
  kwarn("Nothing else has been programmed yet.");
  idt_init();
  // asm("int $4");
  // halt();

  kerror("EOK [END OF KERNEL]");
  halt();
}