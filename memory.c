#include "memory.h"

Bloup* empty = NULL;
Bloup* full = NULL;
// todo: merge consecutive empty blocks
// use a segtree or heap to get biggest block, or nearest ? or nearest * 2 ? 

int chepa[2000000];
void* offset = (void*)chepa;
void* heap_ptr = (void*)chepa;

void* malloc(uint32_t size) {
    void* ans = heap_ptr;
    heap_ptr += size;
    return ans;
}

void free(void*);
