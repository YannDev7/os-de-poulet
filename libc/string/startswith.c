#include <string.h>

int startswith(const char* pref, const char* str) {
    for (int i=0;;++i) {
        if (pref[i] == 0) return 1;
        if (str[i] != pref[i]) return 0;
    }
}
