#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kernel/tty.h>
#include <sys/io.h>
#include "keyboard_driver.h"
#include "sound.h"

const uint8_t normal_code[424] = {
    [0x01] = KEY_ESC,
    [0x02] = KEY_1,
    [0x03] = KEY_2,
    [0x04] = KEY_3,
    [0x05] = KEY_4,
    [0x06] = KEY_5,
    [0x07] = KEY_6,
    [0x08] = KEY_7,
    [0x09] = KEY_8,
    [0x0A] = KEY_9,
    [0x0B] = KEY_0,
    [0x0E] = KEY_BACKSPACE,
    [0x10] = KEY_Q,
    [0x11] = KEY_W,
    [0x12] = KEY_E,
    [0x13] = KEY_R,
    [0x14] = KEY_T,
    [0x15] = KEY_Y,
    [0x16] = KEY_U,
    [0x17] = KEY_I,
    [0x18] = KEY_O,
    [0x19] = KEY_P,
    [0x1C] = KEY_ENTER,
    [0x1E] = KEY_A,
    [0x1F] = KEY_S,
    [0x20] = KEY_D,
    [0x21] = KEY_F,
    [0x22] = KEY_G,
    [0x23] = KEY_H,
    [0x24] = KEY_J,
    [0x25] = KEY_K,
    [0x26] = KEY_L,
    [0x2C] = KEY_Z,
    [0x2D] = KEY_X,
    [0x2E] = KEY_C,
    [0x2F] = KEY_V,
    [0x30] = KEY_B,
    [0x31] = KEY_N,
    [0x32] = KEY_M,
    [0x38] = KEY_LALT,
    [0x39] = KEY_SPACE,
    [0x2A] = KEY_LSHIFT,
    [0x36] = KEY_RSHIFT,
    [0x3A] = KEY_CAPS_LOCK,
};

uint8_t prefix_code[424] = {
    [0x1D] = KEY_RCTRL,
    [0x38] = KEY_RALT,
    [0x47] = KEY_HOME,
    [0x48] = KEY_UP_ARROW,
    [0x49] = KEY_PAGE_UP,
    [0x4B] = KEY_LEFT_ARROW,
    [0x4D] = KEY_RIGHT_ARROW,
    [0x4F] = KEY_END,
    [0x50] = KEY_DOWN_ARROW,
    [0x51] = KEY_PAGE_DOWN,
    [0x52] = KEY_INSERT,
    [0x53] = KEY_DELETE,
};

typedef struct {
    uint8_t keycode;
    char lower;
} letter_entry;

letter_entry qwerty_letters[] = {
    { KEY_Q, 'q' }, { KEY_W, 'w' }, { KEY_E, 'e' }, { KEY_R, 'r' },
    { KEY_T, 't' }, { KEY_Y, 'y' }, { KEY_U, 'u' }, { KEY_I, 'i' },
    { KEY_O, 'o' }, { KEY_P, 'p' }, { KEY_A, 'a' }, { KEY_S, 's' },
    { KEY_D, 'd' }, { KEY_F, 'f' }, { KEY_G, 'g' }, { KEY_H, 'h' },
    { KEY_J, 'j' }, { KEY_K, 'k' }, { KEY_L, 'l' }, { KEY_Z, 'z' },
    { KEY_X, 'x' }, { KEY_C, 'c' }, { KEY_V, 'v' }, { KEY_B, 'b' },
    { KEY_N, 'n' }, { KEY_M, 'm' },
};

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

    // Handle letters
    for (size_t i = 0; i < sizeof(qwerty_letters) / sizeof(letter_entry); ++i) {
        if (qwerty_letters[i].keycode == key_code) {
            char lower = qwerty_letters[i].lower;
            return (shift ^ caps) ? (lower - 32) : lower;
        }
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

    play_monkey_sound();

    if (key_code == KEY_BACKSPACE && !released) {
        terminal_delete();
    }

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
