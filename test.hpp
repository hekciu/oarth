#pragma once


extern "C" void log_string(const char * value);
extern "C" void log_int(uint32_t value);
extern "C" void log_error(const char * value);


static uint16_t error_count = 0;

#define TEST(task_name, statement)\
(\
    {\
        log_string("running task:");\
        log_string(task_name);\
        if (statement) {\
            log_string("success");\
        } else {\
            log_error("failure");\
            error_count++;\
        }\
        log_string("\n");\
    }\
)


static void test_memory() {
    TEST("malloc ", []{
        return 1 == 0;
    }());

};


extern "C" void run_tests() {
    test_memory();

    if (error_count > 0) {
        log_error("some tests failed, number of errors:");
        log_int(error_count);
        error_count = 0;
    } else {
        log_string("all tests passed");
    }

    /*
    const char * test_string_stack = "hello from stack";

    log_string(test_string_stack);

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

    log_string(heap_ptr_1);
    log_string(heap_ptr_2);
    log_string(heap_ptr_3);

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

    log_string(heap_ptr_4);
    log_string(heap_ptr_5);
    log_string(heap_ptr_6);


    // nie mozesz tego testowac na tym samym pointerze :<<<
    log_string("heap_ptr_4");
    log_int((uint32_t)heap_ptr_4);
    char * heap_ptr_4_realloc_small = (char *)realloc(heap_ptr_4, 4);
    log_string("heap_ptr_4_realloc_small");
    log_int((uint32_t)heap_ptr_4_realloc_small);
    char * heap_ptr_4_realloc_bigger = (char *)realloc(heap_ptr_4, 440);
    log_string("heap_ptr_4_realloc_bigger");
    log_int((uint32_t)heap_ptr_4_realloc_bigger);
    char * heap_ptr_4_realloc_the_same = (char *)realloc(heap_ptr_4, string_length_4);
    log_string("heap_ptr_4_realloc_the_same");
    log_int((uint32_t)heap_ptr_4_realloc_the_same);


    log_string("heap_ptr_6");
    log_int((uint32_t)heap_ptr_6);
    char * heap_ptr_6_realloc_small = (char *)realloc(heap_ptr_6, 6);
    log_string("heap_ptr_6_realloc_small");
    log_int((uint32_t)heap_ptr_6_realloc_small);
    char * heap_ptr_6_realloc_bigger = (char *)realloc(heap_ptr_6, 440);
    log_string("heap_ptr_6_realloc_bigger");
    log_int((uint32_t)heap_ptr_6_realloc_bigger);
    char * heap_ptr_6_realloc_the_same = (char *)realloc(heap_ptr_6, string_length_6);
    log_string("heap_ptr_6_realloc_the_same");
    log_int((uint32_t)heap_ptr_6_realloc_the_same);
    */
}
