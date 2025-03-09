#include <stdint.h>
#include "lib/string.h"

extern "C" void log_string(uint32_t pointer);
extern uint8_t memory;


static void log_to_console(const char * value) {
    log_string((uint32_t)value);
};


extern "C" long add(long a, long b) {
    return a + b;
};


extern "C" void run() {
    log_to_console("test123");
};
