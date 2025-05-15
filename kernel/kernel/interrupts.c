#include <stdint.h>
#include <stdio.h>
#include <sys/io.h>
#include "keyboard_driver.h"
#include "idt.h"

void _interrupt_0 () {
    printf("\nException 0x0 : Divide Error\n");
   // if we just have ring 0 tasks, we just need to halt the computer
   // if we also had ring 3 tasks, and a ring 3 task was the cause of the
   // exception, then we should delete the ring 3 task and continue on
   asm("cli");
   asm("hlt");
}

void _interrupt_2 () {
    printf("\nException 0x2 : Non maskable interrupt\n Quelque chose de très grave est arrivé !!\n");
   asm("cli; hlt");
}

void _interrupt_5 () {
    printf("\nException 0x5 : Bound range exceeded\n");
   asm("cli; hlt");
}

void _interrupt_8 (uint32_t error_code) {
    printf("\nException 0x8 : Double Fault\n");
    printf("Error code : %d\n", error_code);
   asm("cli; hlt");
}

void _interrupt_10 (uint32_t error_code) {
    printf("\nException 0xA : Invalid TSS\n");
    printf("Error code : %d\n", error_code);
   asm("cli; hlt");
}

void _interrupt_11 (uint32_t error_code) {
    printf("\nException 0xB : Segment not present\n");
    printf("Error code : %d\n", error_code);
   asm("cli; hlt");
}

void _interrupt_12 (uint32_t error_code) {
    printf("\nException 0xC : Stack-segment fault\n");
    printf("Error code : %d\n", error_code);
   asm("cli; hlt");
}

void _interrupt_13 (uint32_t error_code) {
    printf("\nException 0xD : General Protection Fault\n");
    printf("Error code : %d\n", error_code);
   asm("cli; hlt");
}

void _interrupt_14 (uint32_t error_code, uintptr_t addr) {
    printf("\nException 0xE : Page Fault\n");
    printf("Error code : %d\n", error_code);
    printf("Page address : %d\n", addr);
   asm("cli");
   asm("hlt");
}

void exception_handler(uint32_t num, uint32_t error_code) {
    if (num == 0)
        _interrupt_0();
    else if (num == 2)
        _interrupt_2();
    else if (num == 5)
        _interrupt_5();
    else if (num == 8)
        _interrupt_8(error_code);
    else if (num == 10)
        _interrupt_10(error_code);
    else if (num == 11)
        _interrupt_11(error_code);
    else if (num == 12)
        _interrupt_12(error_code);
    else if (num == 13)
        _interrupt_13(error_code);
    else {
        printf("Aie aie aie : %d! Error code : %d\n", num, error_code);
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
    keyboard_driver_irq_handler();
    pic_acknowledge(0x21);
}


