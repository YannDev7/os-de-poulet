#include <stdint.h>
#include <stdio.h>
#include <sys/io.h>
#include "idt.h"

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
    if (num == 0) {
        _interrupt_0();
    }
    else {
        printf("Aie aie aie : %d!\n", num);
        __asm__ volatile ("cli; hlt"); // halts the computer
    }
}

// IRQ 0 : timer


uint32_t tick = 0;
void irq_timer_handler() {
    tick++;
    pic_acknowledge(0x20);
}

void sleep(uint32_t centieme_sec) {
    int start = tick;
    while (tick - start < centieme_sec) {
        asm ("hlt");
    }
}

// IRQ 1 : clavier

#define KBD_DATA_PORT 0x60
uint8_t read_scancode() {
    return inb(KBD_DATA_PORT);
}

void irq_kbd_handler() {
    uint8_t scancode = read_scancode();
    printf("Scancode : %d\n", scancode);
    pic_acknowledge(0x21);
}


