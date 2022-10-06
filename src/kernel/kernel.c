#include "console/console.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "utils.h"
#include "io/string.h"

void kmain() {
  kinfo("Jumping to C kernel successful!");
  idt_init();
  asm("int $4");
  asm("int $3");
  asm("int $15");
  asm("int $31");

  kerror("EOK [END OF KERNEL]");
  halt();
}