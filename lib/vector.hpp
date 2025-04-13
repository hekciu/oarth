#pragma once

#include <stdint.h>
#include "memory.h"
#include "exception.hpp"

namespace std {

// contiguous storage is guaranteed
template<typename T>
class vector {
public:
    vector() {
        this->raw = NULL;
        this->_size = 0;
    }

    vector(uint32_t count) {
        this->_size = count;
        this->raw = (T *)malloc(sizeof(T));

        if (this->raw == NULL) {
            exit_wasm(1);
        }

        for (uint32_t i = 0; i < count; i++) {
            // new (this->raw + i) T();
            *(this->raw + i) = T();
        }
    }

    ~vector() {
        free(this->raw);
    }

    T * data () {
        return this->raw;
    }

    const T * data () const {
        return this->raw;
    }

    uint32_t size() const {
        return this->_size;
    }

    // provides strong exception guarantee
    void push_back(const T & value) {
        if (MEMORY_SIZE - sizeof(T) >= this->size) {
            exit_wasm(1);
        }

        const uint32_t new_size = this->_size + sizeof(T);

        T * tmp = (T *)realloc((void *)this->raw, new_size);

        if (tmp != NULL) {
            memcpy(tmp, &value, sizeof(T));
            this->_size = new_size;

            return;
        }

        tmp = (T *)malloc(new_size);

        if (tmp == NULL) {
            exit_wasm(1);
        }

        memcpy(tmp, this->raw, this->_size);
        memcpy(tmp + this->_size, &value, sizeof(T));

        free(this->raw);

        this->raw = tmp;
    }

    // provides strong exception guarantee
    void push_back(T && value) {

    }
private:
    T * raw;
    uint32_t _size;
};

}
