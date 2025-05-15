#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tty.h>
#include "keyboard_driver.h"

key_press buf_keys[MAX_KEYB_BUFFER_SIZE];
uint8_t buf_idx = 0;
uint8_t state = 0;

bool shift;
bool ctrl;
bool alt;
bool caps;

void init_keyboard() {
    buf_idx = 0;
    state = 0;
    shift = ctrl = alt = caps = false;
}

uint8_t code_to_kernel(uint8_t code) {
    if (state == PREFIX)
        return code < 424 ? prefix_code[code] : KEY_NONE;
    return code < 424 ? normal_code[code] : KEY_NONE;
}

char keycode_to_char(uint8_t key_code, uint8_t msk) {
    bool is_shift = (msk >> SHIFT_BIT) & 1;
    bool is_caps  = (msk >> CAPS_BIT) & 1;

    if (key_code >= KEY_A && key_code <= KEY_Z) {
        char base = 'a' + (key_code - KEY_A);
        if (shift ^ caps)
            return base - 32; // Uppercase
        return base;         // Lowercase
    }

    switch (key_code) {
        case KEY_1: return shift ? '!' : '1';
        case KEY_2: return shift ? '@' : '2';
        case KEY_3: return shift ? '#' : '3';
        case KEY_4: return shift ? '$' : '4';
        case KEY_5: return shift ? '%' : '5';
        case KEY_6: return shift ? '^' : '6';
        case KEY_7: return shift ? '&' : '7';
        case KEY_8: return shift ? '*' : '8';
        case KEY_9: return shift ? '(' : '9';
        case KEY_0: return shift ? ')' : '0';
        case KEY_SPACE: return ' ';
        case KEY_ENTER: return '\n';
        case KEY_BACKSPACE: return '\b';
        default: return 0;
    }
}

// todo update msk when ctrl or smthg else is pressed
void keyboard_driver_irq_handler() {
    // 0x60 = keyboard data port
    uint8_t code = inb(0x60);

    // reads prefix byte
    if (code == 0xE0) {
        state = PREFIX;
        return;
    }

    uint8_t first_bit = (1 << 7);
    bool released = code & first_bit;
    uint8_t scan_code = code & (first_bit - 1);
    uint8_t key_code = code_to_kernel(scan_code);

    state = NORMAL;

    if (key_code == KEY_LSHIFT || key_code == KEY_RSHIFT)
        shift = !released;

    if (key_code == KEY_LCTRL || key_code == KEY_RCTRL)
        ctrl = !released;

    if (key_code == KEY_LALT || key_code == KEY_RALT)
        alt = !released;

    if (key_code == KEY_CAPS_LOCK && !released)
        caps = !caps;

    if (released || key_code == KEY_NONE)
        return;

    key_press bench_press;
    bench_press.code = key_code;
    bench_press.msk = (shift << SHIFT_BIT) |
                    (ctrl << CTRL_BIT) |
                    (alt << ALT_BIT) |
                    (caps << CAPS_BIT);
    
    buf_keys[buf_idx] = bench_press;

    char coccinelle = keycode_to_char(key_code, bench_press.msk);
    if (coccinelle)
        terminal_putchar(coccinelle);

    buf_idx++;
    // micro opti
    if (buf_idx >= MAX_KEYB_BUFFER_SIZE)
        buf_idx -= MAX_KEYB_BUFFER_SIZE;
}
