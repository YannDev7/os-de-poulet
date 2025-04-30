#ifndef GDT_H_
#define GDT_H_

#include <stdint.h>

#define GDT_SIZE 3

struct gdt_pointer {
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed));

typedef struct gdt_pointer gdt_pointer;

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity; // flags + limit
    uint8_t base_high;
} __attribute__((__packed__));

typedef struct gdt_entry gdt_entry;

extern void loadGDT(gdt_pointer *);
extern void setSegmentRegisters(void);
extern void getGDTaddr(gdt_pointer *);

void init_gdt();
void _test_gdt();

#endif // GDT_H_
