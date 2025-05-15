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
    uint8_t code;
    uint8_t msk;
} key_press;
