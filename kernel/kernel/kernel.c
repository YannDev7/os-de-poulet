#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <kernel/tty.h>

#include "kernel.h"
#include "gdt.h"
#include "idt.h"

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

extern uint32_t end_kernel;


#define FREE 0
#define USED 1
void *start_frame;
char frame_map[NPAGES];

void init_frame_map(void) {
    start_frame =  (void *) ((uintptr_t) &end_kernel & ~(uintptr_t) 0xfff) + 0x1000;
    for (int i = 0; i < NPAGES; i++)
        frame_map[i] = FREE;
}

/* Trouve l'addresse physique de la première page vide */
void *page_alloc_phys(void) {
    uint32_t i = 0;
    while(frame_map[i] != FREE)
    {
        i++;
        if (i == NPAGES) {abort();}
    }
    frame_map[i] = USED;

    return start_frame + i*PAGESIZE;
}


/*
** Map la pagetable d'indice `pdindex` à une addresse physique, si elle n'en a pas déjà une
 */
void map_pagetable(unsigned long pdindex, uint32_t flags) {
    unsigned long *pd = (unsigned long *) 0xfffff000;
    if (pd[pdindex] & 0x01) {
        printf("la page a déjà une adresse physique");
    } else {
        void *phys_addr = page_alloc_phys();
        pd[pdindex] = (unsigned long) phys_addr | (flags & 0xfff) | 0x1;

        unsigned long *pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
        for (int i = 0; i < 1023; i++)
            pt[i] = 0x00000000;
    }
}

/*
** Renvoie l'addresse physique associée à l'adresse virtuelle `virtualaddr`
 */
void *get_physaddr(void *virtualaddr) {
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;

    unsigned long *pd = (unsigned long *)0xFFFFF000;
    if (!(pd[pdindex] & 0x01)) {
        printf ("page directory index %d is not mapped\n", pdindex);
        abort();
    }

    unsigned long *pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    if (!(pt[ptindex] & 0x01)) {
        printf ("page table index %d is not mapped\n", ptindex);
        abort();
    }

    return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtualaddr & 0xFFF));
}

/*
** Map la page d'addresse virtuelle `virtualaddr` à l'addresse physique
** `physaddr` en spécifiant les permission de `flags`
 */
void map_page(void *virtualaddr, void *physaddr, unsigned int flags) {
    if (((unsigned long) virtualaddr & 0x111) || (unsigned long) physaddr & 0x111) {
        printf("les addresses des pages doivent être alignée à 4KiB");
        abort();
    }

    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;

    unsigned long *pd = (unsigned long *)0xFFFFF000;
    if (!(pd[pdindex] & 0x01))  // check si la pagetable existe, sinon la crée
        map_pagetable(pdindex, 1);

    unsigned long *pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    if (!(pt[ptindex] & 0x01)) {
        printf("Vous essayez de remapper une adresse virtuelle déjà mappée, cela va très sûrement faire n'import quoi\n");
        abort();
    }

    pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01; // Present

    // TODO Now you need to flush the entry in the TLB
    // or you might not notice the change.
}

void init_timer(uint32_t frequency) {
    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36); // lance la commande
    outb(0x40, divisor & 0xff);
    outb(0x40, (divisor >> 8) & 0xff);
}

extern uint32_t getValue();
extern void getIdtptr(struct idt_pointer*);

void handler() {
    printf("coucou je suis l'interruption de test ^^ !\n");
    return;
}

void kernel_main(void) {

    terminal_initialize();
    init_gdt();
    /* _test_gdt(); */



    init_frame_map();
    /** Setup du page directory */
    uint32_t *page_dir = page_alloc_phys();
    for (int i = 0; i < 1024; i++)
        page_dir[i] = 0x00000002;
    // la dernière entrée du page directory est lui-même
    page_dir[1023] = ((unsigned int) page_dir) | 3;
    loadPageDirectory((unsigned int *)page_dir);

    /** Identity map les premiers 4MiB sinon ça marche pas (les adresse du code
     * du kernel ne sont plus mappées) */
    uint32_t *first_page_table = page_alloc_phys();
    unsigned int j;
    for(j = 0; j < 1024; j++)
        first_page_table[j] = (j * 0x1000) | 3; // attributes: supervisor level, read/write, present.
    page_dir[0] = ((unsigned int)first_page_table) | 3;

    /** Lance la paging pour de bon*/
    enablePaging();

    init_pics(0x20, 0x28);
    init_idt();

    toggle_interrupts(1);

    init_timer(100);

    printf("Bienvenue sur BonobOS !\n");

<<<<<<< HEAD
=======
    while (1) {
        asm ("nop");
    }
>>>>>>> origin/yann
}
