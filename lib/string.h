#include <stdint.h>


uint32_t strlen(const char * input) {
    uint32_t output = 0;

    while (output < UINT32_MAX) {
        if (*(input + output) == '\0') {
            break;
        }

        output++;
    }

    return output;
};
