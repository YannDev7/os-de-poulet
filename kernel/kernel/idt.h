#ifndef IDT_H_
#define IDT_H_

#include <stdint.h>

struct idt_pointer {
    uint16_t limit;
    uintptr_t base;
} __attribute__((__packed__));

typedef struct idt_pointer idt_pointer;

struct idt_entry {
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_high;
} __attribute__((__packed__));

typedef struct idt_entry idt_entry;

void toggle_interrupts(int);
void idt_set_descriptor(uint16_t, void (*handler)(), uint8_t flags);
void init_idt(void);
void init_pics(uint32_t, uint32_t);
void pic_acknowledge(uint32_t);

#endif // IDT_H_
