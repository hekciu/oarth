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

    template<typename I = int>
    vector(I count) {
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

    template<typename... Args>
    vector(Args... elements) {
        this->raw = NULL;
        this->_size = 0;

        this->add_elements(elements...);
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

    // TODO: provides strong exception guarantee, check that
    void push_back(const T & value) {
        if (MEMORY_SIZE - sizeof(T) <= this->_size) {
            exit_wasm(1);
        }

        const uint32_t new_size = this->_size + sizeof(T);

        T * tmp = (T *)realloc((void *)this->raw, new_size);

        if (tmp != NULL) {
            this->raw = tmp;

            memcpy(this->raw + this->_size, (void *)&value, sizeof(T));
            this->_size++;

            return;
        }

        tmp = (T *)malloc(new_size);

        if (tmp == NULL) {
            exit_wasm(1);
        }

        memcpy(tmp, this->raw, this->_size);
        memcpy(tmp + this->_size, (void *)&value, sizeof(T));

        free(this->raw);

        this->raw = tmp;
    }

    // provides strong exception guarantee
    /*
    void push_back(T && value) {

    }
    */

private:
    void add_elements(T element) {
        this->push_back(element);
    }

    template<typename... Args>
    void add_elements(T element, Args... elements) {
        this->push_back(element);

        this->add_elements(elements...);
    }

    T * raw;
    uint32_t _size;
};

}
