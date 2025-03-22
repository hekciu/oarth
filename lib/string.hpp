#pragma once

#include <stdint.h>

#include "memory.h"
#include "string.h"


namespace std {

class string {
public:
    string() {
        const char * content = "";

        this->init_data(content);
    };


    string(const char * input) {
        this->init_data(input);
    };


    ~string() {
        free(this->raw);
    };


    const char * c_str() {
        return this->raw;
    };
private:
    uint32_t length = 0;
    char * raw;

    void init_data(const char * data) {
        uint32_t size = strlen(data) + 1;

        this->raw = (char *)malloc(size);

        if (this->raw == NULL) {
            exit_wasm(1);
        }

        memcpy((void *)this->raw, (void *)data, size);
    }
};


}

