#include <stdio.h>
#include <sys/io.h>
#include <stdint.h>
#include "idt.h"

void toggle_interrupts(int on) {
    if(on) asm("sti");
    else asm("cli");
}

static idt_entry idt[256];
static idt_pointer idtr;

void idt_set_descriptor(uint16_t index, void (*handler)(), uint8_t flags) {
    idt_entry *descriptor = &idt[index];
    uintptr_t offset = (uintptr_t) handler;

    /* printf("%d %d | ", index, offset); */

    descriptor->offset_low = offset & 0xffff;
    descriptor->segment_selector = 0x08; // Kernel code segment
    descriptor->zero = 0;
    descriptor->type_attributes = flags;
    descriptor->offset_high = offset >> 16;
}

extern void loadIDT(idt_pointer *);
extern void _isr_0();
extern void _isr_1();
extern void _isr_2();
extern void _isr_3();
extern void _isr_4();
extern void _isr_5();
extern void _isr_6();
extern void _isr_7();
extern void _isr_8();
extern void _isr_9();
extern void _isr_10();
extern void _isr_11();
extern void _isr_12();
extern void _isr_13();
extern void _isr_14();
extern void _isr_15();
extern void _isr_16();
extern void _isr_17();
extern void _isr_18();
extern void _isr_19();
extern void _isr_20();
extern void _isr_21();
extern void _isr_22();
extern void _isr_23();
extern void _isr_24();
extern void _isr_25();
extern void _isr_26();
extern void _isr_27();
extern void _isr_28();
extern void _isr_29();
extern void _isr_30();
extern void _isr_31();

extern void _irq_0();
extern void _irq_1();

void init_idt() {
    idtr.base = (uintptr_t) idt;
    idtr.limit = sizeof(idt);

    idt_set_descriptor(0, _isr_0, 0x8e);
    idt_set_descriptor(1, _isr_1, 0x8e);
    idt_set_descriptor(2, _isr_2, 0x8e);
    idt_set_descriptor(3, _isr_3, 0x8e);
    idt_set_descriptor(4, _isr_4, 0x8e);
    idt_set_descriptor(5, _isr_5, 0x8e);
    idt_set_descriptor(6, _isr_6, 0x8e);
    idt_set_descriptor(7, _isr_7, 0x8e);
    idt_set_descriptor(8, _isr_8, 0x8e);
    idt_set_descriptor(9, _isr_9, 0x8e);
    idt_set_descriptor(10, _isr_10, 0x8e);
    idt_set_descriptor(11, _isr_11, 0x8e);
    idt_set_descriptor(12, _isr_12, 0x8e);
    idt_set_descriptor(13, _isr_13, 0x8e);
    idt_set_descriptor(14, _isr_14, 0x8e);
    idt_set_descriptor(15, _isr_15, 0x8e);
    idt_set_descriptor(16, _isr_16, 0x8e);
    idt_set_descriptor(17, _isr_17, 0x8e);
    idt_set_descriptor(18, _isr_18, 0x8e);
    idt_set_descriptor(19, _isr_19, 0x8e);
    idt_set_descriptor(20, _isr_20, 0x8e);
    idt_set_descriptor(21, _isr_21, 0x8e);
    idt_set_descriptor(22, _isr_22, 0x8e);
    idt_set_descriptor(23, _isr_23, 0x8e);
    idt_set_descriptor(24, _isr_24, 0x8e);
    idt_set_descriptor(25, _isr_25, 0x8e);
    idt_set_descriptor(26, _isr_26, 0x8e);
    idt_set_descriptor(27, _isr_27, 0x8e);
    idt_set_descriptor(28, _isr_28, 0x8e);
    idt_set_descriptor(29, _isr_29, 0x8e);
    idt_set_descriptor(30, _isr_30, 0x8e);
    idt_set_descriptor(31, _isr_31, 0x8e);

    idt_set_descriptor(0x20, _irq_0, 0x8e);
    idt_set_descriptor(0x21, _irq_1, 0x8e);
    outb(0x21, ~(0x3));

    loadIDT(&idtr);
}

/* Fonction du pic qu'il faut sûrement réécrire pour que ça marche */

#define PIC1 0x20
#define PIC2 0xA0

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */ #define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08     /* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C /* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
void init_pics(uint32_t offset1, uint32_t offset2)
{
	outb(PIC1, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	outb(PIC2, ICW1_INIT | ICW1_ICW4);
	outb(PIC1 + 1, offset1);                 // ICW2: Master PIC vector offset
	outb(PIC2 + 1, offset2);                 // ICW2: Slave PIC vector offset
	outb(PIC1 + 1, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(PIC2 + 1, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)

	outb(PIC1 + 1, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	outb(PIC2 + 1, ICW4_8086);

	outb(PIC1+1, 0);
	outb(PIC2+1, 0);
}


#define ACK_SIGNAL 0x20
void pic_acknowledge(uint32_t code) {
    if (code < 0x20 || code >= 0x30)
        return;
    if (code < 0x28) // PIC 1
        outb(0x20, ACK_SIGNAL);
    else
        outb(0x28, ACK_SIGNAL);
}


