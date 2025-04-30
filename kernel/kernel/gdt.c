#include <stdint.h>
#include <stdio.h>

#include "gdt.h"

static gdt_pointer gdtr;
static gdt_entry gdt_table[GDT_SIZE];

/*
** Met en place la gdt et modifie les registres de segment.
** TODO : ajouter les segments user_code et user_data
*/
void init_gdt() {
    gdt_entry null                   = {0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00},
              kernel_code_segment    = {0xffff, 0x0000, 0x00, 0x9A, 0xCF, 0x00},
              kernel_data_segment    = {0xffff, 0x0000, 0x00, 0x92, 0xCF, 0x00};
    gdt_table[0] = null;                  // NULL descriptor
    gdt_table[1] = kernel_code_segment; // Kernel Code Segment
    gdt_table[2] = kernel_data_segment; // Kernel Data Segment

    gdtr.base = (uintptr_t) gdt_table;
    gdtr.limit = GDT_SIZE*sizeof(gdt_entry);


    loadGDT(&gdtr);
    setSegmentRegisters();
}

void _test_gdt() {
    gdt_pointer ptr;
    getGDTaddr(&ptr);

    printf("expected GDT : %d\n", (uint32_t) gdt_table);
    printf("GDT addr/limit : %d %d\n", ptr.base, ptr.limit);
}
