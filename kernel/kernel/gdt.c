#include <stdint.h>
#include <stdio.h>
#include <string.h>
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
              kernel_data_segment    = {0xffff, 0x0000, 0x00, 0x92, 0xCF, 0x00},
              user_code_segment      = {0xffff, 0x0000, 0x00, 0xFA, 0xCF, 0x00},
              user_data_segment      = {0xffff, 0x0000, 0x00, 0xF2, 0xCF, 0x00};
    gdt_table[0] = null;
    gdt_table[1] = kernel_code_segment;
    gdt_table[2] = kernel_data_segment;
    gdt_table[3] = user_code_segment;
    gdt_table[4] = user_data_segment;

    gdtr.base = (uintptr_t) gdt_table;
    gdtr.limit = GDT_SIZE*sizeof(gdt_entry) - 1;

    loadGDT(&gdtr);
    setSegmentRegisters();

    install_tss(&gdt_table[5]);
}

void _test_gdt() {
    gdt_pointer ptr;
    getGDTaddr(&ptr);

    printf("expected GDT : %d\n", (uint32_t) gdt_table);
    printf("GDT addr/limit : %d %d\n", ptr.base, ptr.limit);
}

tss_entry entry;

void install_tss(gdt_entry *g) {
  uint32_t base = (uint32_t) &entry;
  uint32_t limit = sizeof(entry);


  g->limit_low = limit & 0xffff;
  g->base_low = base & 0xffff;
  g->base_middle = (base >> 16) & 0xff;
  g->access = 0x89;
  g->granularity = 0x0f;
  g->base_high = (base >> 24) & 0xff;

  memset(&entry, 0,  sizeof(entry));

  entry.ss0 = 0x10; // Kernel data segment
  register void *esp asm("%sp");
  entry.esp0 = (uintptr_t) esp;

  /* load the tss into the register */
  asm ("mov $0x28, %eax \n\
        ltr %eax");
}

void set_kernel_stack(uint32_t stack) {
  entry.esp0 = stack;
}
