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
            throw new exception();
        }

        const uint32_t new_size = this->_size + sizeof(T);

        T * tmp = (T *)realloc((void *)this->raw, new_size);

        if (tmp != NULL) {
            // TODO: maybe this->raw + this->_size == tmp ????
            memcpy(this->raw + this->_size, &value, sizeof(T));
            this->_size = new_size;

            return;
        }

        tmp = (T *)malloc(new_size);

        if (tmp == NULL) {
            throw new exception();
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
