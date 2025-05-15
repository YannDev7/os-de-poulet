#include "shell.h"
#include "keyboard_driver.h"


void input(char * buffer) {
    clear_line_buffer();
    char * line = get_line_buffer();

    while (line[0] == 0) {
        asm("nop");
    }
    int i;
    for (i = 0; line[i] != 0; ++i) {
        buffer[i] = line[i];
    }

    buffer[i + 1] = 0;
}



