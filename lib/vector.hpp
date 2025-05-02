#pragma once

#include <stdint.h>
#include "memory.h"
#include "exception.hpp"
#include "initializer_list.hpp"

namespace std {


// continuous storage is guaranteed
template<typename T>
class vector {
public:
    vector() {
        this->raw = NULL;
        this->_size = 0;
    }

    // template<typename... Args>
    // vector(Args... elements) {
    vector(initializer_list<T> i_list) {
        this->raw = NULL;
        this->_size = 0;

        for (auto itr = i_list.begin(); itr != i_list.end(); itr++) {
            this->push_back(*itr);
        }

        // this->add_elements(elements...);
    }

    vector(int count) {
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
    /*
    void add_elements(T element) {
        this->push_back(element);
    }

    template<typename... Args>
    void add_elements(T element, Args... elements) {
        this->push_back(element);

        this->add_elements(elements...);
    }
    */

    T * raw;
    uint32_t _size;
};


}
