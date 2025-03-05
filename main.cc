#include <stdint.h>

extern "C" void console_log(uint32_t value);
extern uint8_t memory;


static void print(uint32_t value) {
    console_log(value);
};


extern "C" long add(long a, long b) {
    return a + b;
};


extern "C" void run() {
    console_log(2137);
};
