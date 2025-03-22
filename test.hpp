#pragma once

#include "lib/memory.h"
#include "lib/string.hpp"
#include "lib/js_imports.h"


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
    char * test_ptr_0 = NULL;
    char * test_ptr_1 = NULL;
    char * test_ptr_2 = NULL;

    TEST("[malloc] should allocate memory on the heap", [&]{
        test_ptr_0 = (char *)malloc(2);
        return (uint32_t)test_ptr_0 >= (uint32_t)&__heap_base;
    }());

    free(test_ptr_0);


    TEST("[malloc] following chunks should be placed next to each other", [&]{
        test_ptr_0 = (char *)malloc(2137);
        test_ptr_1 = (char *)malloc(2137);

        uint32_t chunk_header_size = sizeof(chunk_header);

        uint32_t first_chunk_end = (uint32_t)test_ptr_0 + 2137;
        uint32_t second_chunk_start = (uint32_t)test_ptr_1 - chunk_header_size;

        return first_chunk_end + 1 == second_chunk_start;
    }());

    free(test_ptr_0);
    free(test_ptr_1);


    TEST("[malloc] chunk should fit between other chunks when possible", [&]{
        test_ptr_0 = (char *)malloc(2137);
        test_ptr_1 = (char *)malloc(2137);
        test_ptr_2 = (char *)malloc(2137);

        free(test_ptr_1);

        test_ptr_1 = (char *)malloc(2137);
        return ((uint32_t)test_ptr_0 < (uint32_t)test_ptr_1) &&
            ((uint32_t)test_ptr_1 < (uint32_t)test_ptr_2);
    }());

    free(test_ptr_0);
    free(test_ptr_1);
    free(test_ptr_2);

    TEST("[malloc] should return NULL on insufficient memory", [&]{
        /* MEMORY_SIZE should be defined inside lib/memory.h */
        uint32_t all_heap_space = MEMORY_SIZE - (uint32_t)&__heap_base;

        test_ptr_0 = (char *)malloc(all_heap_space);

        return test_ptr_0 == NULL;
    }());


    TEST("[realloc] should allocate memory when no pointer is provided", [&]{
        test_ptr_0 = (char *)malloc(2137);
        test_ptr_1 = (char *)realloc(NULL, 2137);

        uint32_t chunk_header_size = sizeof(chunk_header);

        uint32_t first_chunk_end = (uint32_t)test_ptr_0 + 2137;
        uint32_t second_chunk_start = (uint32_t)test_ptr_1 - chunk_header_size;

        return first_chunk_end + 1 == second_chunk_start;
    }());

    free(test_ptr_0);
    free(test_ptr_1);


    TEST("[realloc] should leave memory chunk untouched when size stays the same", [&]{
        test_ptr_0 = (char *)malloc(2137);
        test_ptr_1 = (char *)realloc(test_ptr_0, 2137);
        test_ptr_2 = (char *)malloc(2137);

        uint32_t chunk_header_size = sizeof(chunk_header);

        uint32_t first_chunk_end = (uint32_t)test_ptr_0 + 2137;
        uint32_t second_chunk_start = (uint32_t)test_ptr_2 - chunk_header_size;

        return test_ptr_0 == test_ptr_1 && first_chunk_end + 1 == second_chunk_start;
    }());

    free(test_ptr_0);
    free(test_ptr_2);


    TEST("[realloc] should shrink memory when requested", [&]{
        test_ptr_0 = (char *)malloc(2137);
        test_ptr_1 = (char *)realloc(test_ptr_0, 69);
        test_ptr_2 = (char *)malloc(2137);

        uint32_t chunk_header_size = sizeof(chunk_header);

        uint32_t first_chunk_end = (uint32_t)test_ptr_0 + 69;
        uint32_t second_chunk_start = (uint32_t)test_ptr_2 - chunk_header_size;

        return test_ptr_0 == test_ptr_1 && first_chunk_end + 1 == second_chunk_start;
    }());

    free(test_ptr_0);
    free(test_ptr_2);


    TEST("[realloc] should return NULL on insufficient memory 1", [&]{
        test_ptr_0 = (char *)malloc(2137);
        test_ptr_1 = (char *)malloc(2137);
        test_ptr_2 = (char *)realloc(test_ptr_0, 2138);

        return test_ptr_2 == NULL;
    }());

    free(test_ptr_0);
    free(test_ptr_1);


    TEST("[realloc] should return NULL on insufficient memory 2", [&]{
        test_ptr_0 = (char *)malloc(2137);
        test_ptr_1 = (char *)malloc(2137);
        test_ptr_2 = (char *)realloc(test_ptr_1, MEMORY_SIZE);

        return test_ptr_2 == NULL;
    }());

    free(test_ptr_0);
    free(test_ptr_1);


    TEST("[realloc] should free memory on size == 0", [&]{
        test_ptr_0 = (char *)malloc(2137);
        test_ptr_1 = (char *)realloc(test_ptr_0, 0);
        test_ptr_2 = (char *)malloc(69);

        return test_ptr_1 == NULL && test_ptr_2 == test_ptr_0;
    }());

    free(test_ptr_2);
};


void test_std_string() {
    TEST("[std::string] -> std::string() should allocate empty string on the heap", [&] {
        std::string test_string = std::string();

        const char * base_str = test_string.c_str();

        return *base_str == '\0';
    }());


    TEST("[std::string] -> std::string(data) should create copy of the data on the heap", [&] {
        const char * data = "hello";

        std::string test_string = std::string(data);

        const char * base_str = test_string.c_str();

        log_string(test_string.c_str());

        return memcmp((const void *)base_str, (const void *)data, strlen(data) + 1) == 0;
    }());
};


extern "C" void run_tests() {
    test_memory();
    test_std_string();

    if (error_count > 0) {
        log_error("some tests failed, number of errors:");
        log_int(error_count);
        error_count = 0;
    } else {
        log_string("all tests passed");
    }
}
