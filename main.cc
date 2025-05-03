#include <stdint.h>
#include "lib/string.h"
#include "lib/memory.h"
#include "lib/js_imports.h"

#include "test.hpp"


// extern uint8_t memory;


extern "C" uint32_t js_malloc(uint32_t size) {
    char * ptr = (char *)malloc(size);

    if (ptr == NULL) {
        exit_wasm(1);
    }

    return (uint32_t)ptr;
};


extern "C" long add(long a, long b) {
    return a + b;
};


void print_body(const char * output) {
    if (output == NULL) {
        log_string("error has occured");
    }

    log_string("got body:");
    log_string(output);
};


extern "C" void run() {
    char * output = NULL;

    fetch("http://localhost:3000/healthcheck", NULL, &print_body);
};
