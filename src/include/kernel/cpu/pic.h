#pragma once

// Define some terms that will be useful later in PIC reprogramming
#define PIC1		      0x20		    // IO base address for master PIC
#define PIC2		      0xA0		    // IO base address for slave PIC
#define PIC1_COMMAND	PIC1        // Port where to send commands for PIC1
#define PIC1_DATA	    (PIC1+1)    // Port where to send data or input to PIC1
#define PIC2_COMMAND	PIC2        // Port where to send commands for PIC2
#define PIC2_DATA	    (PIC2+1)    // Port where to send data or input to PIC1

#define ICW1_SINGLE     0x02      // Single (cascade) mode
#define ICW1_INTERVAL4  0x04      // Call address interval 4 (8)
#define ICW1_LEVEL      0x08      // Level triggered (edge) mode
#define ICW1_INIT       0x11      // The initialization sequence

#define ICW4_8086       0x01      // 8086/88 mode
#define ICW4_AUTO       0x02      // Auto (normal) EOI
// #define ICW4_BUF_SLAVE  0x08      // Buffered mode slave
// #define ICW4_BUF_MASTER 0x0c      // Buffered mode master

#define PIC_EOI         0x20

// Initialise the PIC
void pic_init();

// // Remap the PIC
// void pic_remap(int offset_master, int offset_slave);

// Send the EOI (End Of Interrupt) command to the PIC
void pic_send_eoi(unsigned char irq);