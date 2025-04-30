#ifndef KERNEL_H_
#define KERNEL_H_

#define MEMSIZE_PHYSICAL 0x2000000

#define PAGESIZE         0x1000

#define NPAGES            (MEMSIZE_PHYSICAL / PAGESIZE)

#endif // KERNEL_H_
