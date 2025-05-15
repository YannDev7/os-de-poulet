#include <kernel/memory.h>
#include <stdint.h>
#include "kernel.h"

size_t memory_left = 0;

extern uint32_t end_kernel;

void * initial_heap_pointer;
void * heap_ptr;
size_t page_count = 0;


void init_malloc() {
    initial_heap_pointer = (void *) (((uint32_t) &end_kernel / PAGESIZE + 1) * PAGESIZE) ;
    heap_ptr = initial_heap_pointer;
}

void * malloc(size_t size) {

    while (size > memory_left) {
        void * physical_address = page_alloc_phys();

        void * virtual_address = (void *) (initial_heap_pointer + page_count * PAGESIZE);
        map_page(virtual_address, physical_address, 0); // je mets quoi comme flags ?

        ++page_count;
        memory_left += PAGESIZE;
    }

    memory_left -= size;

    void * ans = heap_ptr;
    heap_ptr += size;
    return ans;

}


void free(void * addr) {return;}
