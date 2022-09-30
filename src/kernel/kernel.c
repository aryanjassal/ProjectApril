#include "console/console.h"
#include "utils.h"

void kmain() {
  kinfo("Jumping to C kernel successful!");
  kwarn("Nothing else has been programmed yet.");

  kerror("EOK [END OF KERNEL]");
  halt();
}