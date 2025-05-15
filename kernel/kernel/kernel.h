#ifndef KERNEL_H_
#define KERNEL_H_

#define MEMSIZE_PHYSICAL 0x2000000

#define PAGESIZE         0x1000

#define NPAGES            (MEMSIZE_PHYSICAL / PAGESIZE)

void * page_alloc_phys(void);

void map_page(void *virtualaddr, void *physaddr, unsigned int flags);




#endif // KERNEL_H_
