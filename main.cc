#include <stdint.h>
#include "lib/string.h"
#include "lib/memory.h"


extern "C" float test;

extern "C" void log_string(uint32_t pointer);
extern "C" void log_int(uint32_t value);
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

    const char * test_string_1 = "hello from heap 1";
    const char * test_string_2 = "hello from heap 2";
    const char * test_string_3 = "hello from heap 3";
    
    const uint32_t string_length_1 = strlen(test_string_1) + 1;
    const uint32_t string_length_2 = strlen(test_string_2) + 1;
    const uint32_t string_length_3 = strlen(test_string_3) + 1;

    char * heap_ptr_1 = (char *)malloc(string_length_1);
    char * heap_ptr_2 = (char *)malloc(string_length_2);
    char * heap_ptr_3 = (char *)malloc(string_length_3);

    log_int((uint32_t)heap_ptr_1);
    log_int((uint32_t)heap_ptr_2);
    log_int((uint32_t)heap_ptr_3);

    memcpy((void *)heap_ptr_1, (void *)test_string_1, string_length_1);
    memcpy((void *)heap_ptr_2, (void *)test_string_2, string_length_2);
    memcpy((void *)heap_ptr_3, (void *)test_string_3, string_length_3);

    log_to_console(heap_ptr_1);
    log_to_console(heap_ptr_2);
    log_to_console(heap_ptr_3);

    // free(heap_ptr_1);
    // free(heap_ptr_2);
    free(heap_ptr_3);


    const char * test_string_4 = "hello from heap 45555";
    const char * test_string_5 = "hello from heap 5";
    const char * test_string_6 = "hello from heap 6";

    const uint32_t string_length_4 = strlen(test_string_4) + 1;
    const uint32_t string_length_5 = strlen(test_string_5) + 1;
    const uint32_t string_length_6 = strlen(test_string_6) + 1;

    char * heap_ptr_4 = (char *)malloc(string_length_4);
    char * heap_ptr_5 = (char *)malloc(string_length_5);
    char * heap_ptr_6 = (char *)malloc(string_length_6);

    log_int((uint32_t)heap_ptr_4);
    log_int((uint32_t)heap_ptr_5);
    log_int((uint32_t)heap_ptr_6);

    memcpy((void *)heap_ptr_4, (void *)test_string_4, string_length_4);
    memcpy((void *)heap_ptr_5, (void *)test_string_5, string_length_5);
    memcpy((void *)heap_ptr_6, (void *)test_string_6, string_length_6);

    log_to_console(heap_ptr_4);
    log_to_console(heap_ptr_5);
    log_to_console(heap_ptr_6);
};
