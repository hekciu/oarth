#include <stdint.h>
#include "lib/string.h"
#include "lib/memory.h"


extern "C" void log_string(uint32_t pointer);
extern uint8_t memory;


static void log_to_console(const char * value) {
    log_string((uint32_t)value);
};


extern "C" long add(long a, long b) {
    return a + b;
};


extern "C" void run() {
    const char * test_string_stack = "hello from stack";

    log_to_console(test_string_stack);

    const char * test_string = "hello from heap";
    
    const uint32_t string_length = strlen(test_string) + 1;

    char * heap_ptr = (char *)malloc(string_length);

    memcpy((void *)heap_ptr, (void *)test_string, string_length);

    log_to_console(heap_ptr);
};
