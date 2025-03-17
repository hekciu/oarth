#pragma once

#include <stdint.h>

#include "memory.h"
#include "string.h"


namespace std {

class string {
public:
    string() {


    };


    string(const char * input) {

    };


private:
    uint32_t length = 0;
    char * data = NULL;
}


}

