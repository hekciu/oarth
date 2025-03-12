#include <stdint.h>

extern "C" unsigned char __heap_base;

#define NULL 0

#define OARTH_HEAP_OFFSET 1

typedef struct {
    uint32_t start;
    uint32_t size;
    void * next;
} chunk_header;


static chunk_header first_chunk = {
    NULL,
    NULL,
    NULL
};


void * memcpy(void * dest, void * src, uint32_t size) {
    uint8_t * dest_int = (uint8_t *) dest;
    uint8_t * src_int = (uint8_t *) src;

    for (uint32_t i = 0; i < size; i++) {
        *(dest_int + i) = *(src_int + i);
    }

    return dest;
};


void * malloc(uint32_t size) {
    uint32_t max = UINT32_MAX - __heap_base - sizeof(chunk_header);

    // https://surma.dev/things/c-to-webassembly/

    if (size > max) {
        return NULL;
    }

    if (first_chunk.start == NULL) {
        uint32_t start = OARTH_HEAP_OFFSET;

        first_chunk.start = start;
        first_chunk.size = size;
        first_chunk.next = NULL;

        return (void *)(&(__heap_base) + start + sizeof(chunk_header));
    }

    return NULL;
};
