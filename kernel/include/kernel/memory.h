#ifndef _MEMORY_H
#define _MEMORY_H 1

#include <sys/cdefs.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INITIAL_HEAP_ADDRESS PAGESIZE

void * malloc(size_t size);
void free(void * addr);

#ifdef __cplusplus
}
#endif

#endif
