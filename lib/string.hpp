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


    uint32_t length() const {
        return strlen(this->raw);
    }


    const char * c_str() const {
        return this->raw;
    };


    string& operator=(const char * value) {
        char * ptr = (char *)realloc(this->raw, strlen(value) + 1);
        if (ptr == NULL) {
            if (this->raw != NULL) {
                free(this->raw);
            }

            this->init_data(value);
            return *this;
        }

        memcpy((void *)this->raw, (void *)value, strlen(value) + 1);

        return *this;
    }


    string& operator=(const string & str) {
        const char * value = str.c_str();

        char * ptr = (char *)realloc(this->raw, strlen(value) + 1);
        if (ptr == NULL) {
            if (this->raw != NULL) {
                free(this->raw);
            }

            this->init_data(value);
            return *this;
        }

        memcpy((void *)this->raw, (void *)value, strlen(value) + 1);

        return *this;
    }


    string operator+(const string & str) {
        const char * c_str1 = this->c_str();
        const char * c_str2 = str.c_str();

        const uint32_t output_size = strlen(c_str1) + strlen(c_str2) + 1;

        char * tmp = (char *)malloc(output_size);
        memcpy((void *)tmp, (void *)c_str1, strlen(c_str1));
        memcpy((void *)(tmp + strlen(c_str1)), (void *)c_str2, strlen(c_str2));

        *(tmp + strlen(c_str1) + strlen(c_str2)) = '\0';

        string out = tmp;

        free(tmp);

        return out;
    }
private:
    char * raw = NULL;

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

