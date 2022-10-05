#include <stdint.h>
#include "cpu/pic.h"
#include "io/io.h"

// Remap the PIC
// Credit to https://stackoverflow.com/questions/34561275/setting-up-interrupts-in-protected-mode-x86
// Credit to https://wiki.osdev.org/8259_PIC
// There is no need to add io_wait() because we are interleaving between PIC1 and PIC2
void pic_remap(int offset_master, int offset_slave) {
  // Save the mask status of the PIC to restore later
  // uint8_t mask1, mask2;
  // mask1 = inb(PIC1_DATA);
  // mask2 = inb(PIC2_DATA);

  // [ICW1] Send the initialize command to the PICs
  outb(PIC1_COMMAND, ICW1_INIT);
  outb(PIC2_COMMAND, ICW1_INIT);

  // [ICW2] Set the offset of the PICs
  outb(PIC1_DATA, offset_master);
  outb(PIC2_DATA, offset_slave);

  // [ICW3] Declare the master-slave relationship between the PICs
  outb(PIC1_DATA, 0x04);      // [ICW3] Tell PIC1 that it is the master PIC
  outb(PIC2_DATA, 0x02);      // [ICW3] Tell PIC2 that it is the slave PIC

  // [ICW4] Set the mode of both PICs to 8086.
  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  // Restore saved mask status of the PICs
  outb(PIC1_DATA, 0x00);
  outb(PIC2_DATA, 0x00);
}

// Send the interrupt acknowledged (EOI) command to the PICs
// void pic_send_eoi(unsigned char irq)
// {
//   // If the IRQ came from the slave chip, then tell the slave chip about the EOI as well
// 	if(irq >= 8) {
// 		outb(PIC2_COMMAND,PIC_EOI);
//   }

//   // Otherwise, merely informing the master chip is sufficient
// 	outb(PIC1_COMMAND,PIC_EOI);
// }