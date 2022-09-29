#include "console/console.h"
#include "utils.h"

void kernel_main() {
  // kclear();
  kok("Jumping to C kernel successful!");
  // kinfo("Go download a real os");
  // kwarn("Terminal implementation currently incomplete");
  // kerror("EOK [END OF KERNEL]");
  halt();
}