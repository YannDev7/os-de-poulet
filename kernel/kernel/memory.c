#include <kernel/memory.h>
#include "kernel.h"

size_t memory_left = 0;
void * heap_ptr = (void *) INITIAL_HEAP_ADDRESS;
size_t page_count = 0;


void * malloc(size_t size) {

    while (size > memory_left) {
        void * physical_address = page_alloc_phys();

        void * virtual_address = (void *) (INITIAL_HEAP_ADDRESS + page_count * PAGESIZE);
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








