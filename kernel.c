#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "string.h"
#include "terminal.h"
#include "io.h"
#include "memory.h"
// i686-elf-g++ -c kernel.c++ -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
// x86_64-elf-g++ -c kernel.c++ -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. 
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif */

/* Hardware text mode color constants. */


void kernel_main(void) 
{


	//char memory[100000] = {0};


	/* Initialize terminal interface */
	terminal_initialize();
	printf("bloup %d bloup", 10);
	// /* Newline support is left as an exercise. */
	// for (size_t i = 0; i < 30; ++i) {
	// 	terminal_writestring("Hello, kernel World!\nBloup");
	// 	printf("truc: %d\n", i);
	// }
	// while (1) {

	// }

	//int* t = (int*)(0xFF);
	//*t = 42;
	/*uint32_t* truc = (uint32_t*)0x1;
	*truc = 42;*/
	//printf("china town %d", *t);
	
	/*for (int i = 0; i < 10000000; i++) {
		*t = 42;
		t += 4;
	}*/

	for (int i = 0; i < 1000; i++) {
		malloc(42 * i);
	}
}