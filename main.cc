#include <stdint.h>
#include "lib/string.h"
#include "lib/memory.h"

#include "test.hpp"


extern "C" void log_string(const char * value);
extern "C" void log_int(uint32_t value);
extern "C" void log_error(const char * value);
// extern uint8_t memory;


extern "C" long add(long a, long b) {
    return a + b;
};


extern "C" void run() {
};
