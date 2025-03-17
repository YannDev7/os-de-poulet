#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct chunk Chunk;
struct chunk {
    void* pos;
    bool status;
};

typedef struct bloup Bloup;
struct bloup {
    Bloup* nxt;
    Bloup* prev;
    uint32_t* block;
    int len;
};
void* malloc(uint32_t size);
void free();
