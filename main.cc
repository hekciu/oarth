#include <stdint.h>
#include "lib/string.h"
#include "lib/memory.h"
#include "lib/js_imports.h"

#include "test.hpp"


// extern uint8_t memory;


extern "C" long add(long a, long b) {
    return a + b;
};


extern "C" void run() {
};
