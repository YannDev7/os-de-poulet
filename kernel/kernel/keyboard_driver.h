#ifndef _KBDRIVER
#define _KBDRIVER
#include <stdint.h>
#include <stddef.h>

#define MAX_KEYB_BUFFER_SIZE 424
#define NORMAL 0
#define PREFIX 1

#define SHIFT_BIT 1
#define CTRL_BIT 2
#define ALT_BIT 3
#define CAPS_BIT 4

#define KEY_NONE         0
#define KEY_ESC          1
#define KEY_1            2
#define KEY_2            3
#define KEY_3            4
#define KEY_4            5
#define KEY_5            6
#define KEY_6            7
#define KEY_7            8
#define KEY_8            9
#define KEY_9            10
#define KEY_0            11
#define KEY_A            30
#define KEY_B            48
#define KEY_C            46
#define KEY_D            32
#define KEY_E            18
#define KEY_F            33
#define KEY_G            34
#define KEY_H            35
#define KEY_I            23
#define KEY_J            36
#define KEY_K            37
#define KEY_L            38
#define KEY_M            50
#define KEY_N            49
#define KEY_O            24
#define KEY_P            25
#define KEY_Q            16
#define KEY_R            19
#define KEY_S            31
#define KEY_T            20
#define KEY_U            22
#define KEY_V            47
#define KEY_W            17
#define KEY_X            45
#define KEY_Y            21
#define KEY_Z            44
#define KEY_SPACE        57
#define KEY_ENTER        28
#define KEY_BACKSPACE    14

// Extended (0xE0-prefixed)
#define KEY_LEFT_ARROW   200
#define KEY_RIGHT_ARROW  201
#define KEY_UP_ARROW     202
#define KEY_DOWN_ARROW   203
#define KEY_DELETE       204
#define KEY_INSERT       205
#define KEY_HOME         206
#define KEY_END          207
#define KEY_PAGE_UP      208
#define KEY_PAGE_DOWN    209
#define KEY_RCTRL        210
#define KEY_RALT         211

#define KEY_LSHIFT       212
#define KEY_RSHIFT       213
#define KEY_LCTRL        214
#define KEY_LALT         215
#define KEY_CAPS_LOCK    216


typedef struct {
    uint8_t code;
    uint8_t msk;
} key_press;

void keyboard_driver_irq_handler(void);
void initialize_sb16(void);
uint8_t* load_raw_file(const char* filename, size_t* size);
void play_wav(const uint8_t* data, size_t length);
#endif
