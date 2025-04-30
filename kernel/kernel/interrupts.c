#include <stdint.h>
#include <stdio.h>

void _interrupt_0 () {
    printf("Exception : Divide Error\n");
   // if we just have ring 0 tasks, we just need to halt the computer
   // if we also had ring 3 tasks, and a ring 3 task was the cause of the
   // exception, then we should delete the ring 3 task and continue on
   asm("cli");
   asm("hlt");
}

void _interrupt_14 (uintptr_t addr) {
    printf("Exception : Page Fault at addresse %d\n", (int) addr);
   // if we just have ring 0 tasks, we just need to halt the computer
   // if we also had ring 3 tasks, and a ring 3 task was the cause of the
   // exception, then we should delete the ring 3 task and continue on
   asm("cli");
   asm("hlt");
}

void exception_handler(uint32_t num) {
    printf("Aie aie aie : %d!\n", num);
    __asm__ volatile ("cli; hlt"); // halts the computer
}
