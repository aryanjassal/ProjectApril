#include "io/console.h"
#include "io/string.h"
#include "cpu/idt.h"
#include "cpu/pic.h"
#include "utils.h"

void kmain() {
  kclear();
  kok("Boot successful.");
  idt_init();
  asm("int $3");
  asm("int $4");
  asm("int $15");

  // for (int i = 0; i < 20; i++) {
  //   asm("int $3");
  // }

  kerror("EOK [END OF KERNEL]");
  halt();
}