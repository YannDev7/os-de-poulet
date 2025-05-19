#include <kernel/memory.h>
#include <stdint.h>
#include "kernel.h"
#include <stdio.h>
size_t memory_left = 0;

extern uint32_t end_kernel;

typedef struct block_header {
    size_t size;
    struct block_header * next;
    struct block_header * prev;
} bh;


void * initial_heap_pointer;

bh * start_header;


size_t page_count = 0;


void init_malloc() {
    initial_heap_pointer = (void *) (((uint32_t) &end_kernel / PAGESIZE + 1) * PAGESIZE) ;
    
    void * physical_address = page_alloc_phys();
    void * virtual_address = (void *) (initial_heap_pointer + page_count * PAGESIZE);
    map_page(virtual_address, physical_address, 0); // je mets quoi comme flags ?
    ++page_count;

    bh * addr = (bh* ) initial_heap_pointer;

    addr->next = 0;
    addr->prev = 0;
    addr->size = sizeof(bh);

    start_header = addr;
    
}

void * malloc(size_t size) {
    if (size == 0) {
        return (void *) 0;
    }
    bh * header;
    size_t free_section;
    for (header = start_header;; header = header->next) {
        if (header->next == 0) {
            free_section = (size_t) initial_heap_pointer + page_count * PAGESIZE 
                - (size_t) header - header->size;
        } else {
            free_section = (size_t) header->next - (size_t) header - header->size;
        }

        //printf("free section: %d  t %d\n", free_section, header->next);

        if (size + sizeof(bh) <= free_section) {
            bh * addr = (bh*) ((size_t) header + header->size);
            addr->next = header->next;
            header->next = addr;
            addr->prev = header;

            addr->size = size + sizeof(bh);

            //printf("yay ! %d    %d   %d\n", page_count, (void *) addr, (void *) header);

            return ((void *) addr) + sizeof(bh); 
        }

        if (header->next == 0) break;

    }

    while (size + sizeof(bh) > free_section) {
        void * physical_address = page_alloc_phys();
        void * virtual_address = (void *) (initial_heap_pointer + page_count * PAGESIZE);
        map_page(virtual_address, physical_address, 0); // je mets quoi comme flags ?
        ++page_count;

        free_section += PAGESIZE;
    }

    bh * addr = (bh*) ((size_t) header + header->size);
    addr->next = header->next;
    header->next = addr;
    addr->prev = header;

    addr->size = size + sizeof(bh);

    return ((void *) addr) + sizeof(bh); 
}


void free(void * addr) {
    bh * header_addr = (bh*)    ( (size_t) addr - sizeof(bh));

    header_addr->prev->next = header_addr->next;

}
