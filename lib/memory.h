#pragma once

#include <stdint.h>

extern "C" unsigned char __heap_base;

// TODO remove this
extern "C" void log_int(uint32_t value);

#define NULL 0

#define MEMORY_SIZE 16777216

typedef struct {
    uint32_t size;
    uint32_t prev; //TODO: this could be optimized in case of memory
    uint32_t next;
} chunk_header;


static chunk_header * first_chunk = NULL;


// TODO: write tests


static uint8_t is_enough_space_between(chunk_header * c1, chunk_header * c2, uint32_t size) {
    uint32_t needed_space = sizeof(chunk_header) + size;

    uint32_t first_chunk_end = (uint32_t)c1 + sizeof(chunk_header) + c1->size;
    uint32_t second_chunk_start = (uint32_t)c2;

    return second_chunk_start - first_chunk_end >= needed_space ? 0 : 1;
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
    uint32_t heap_start = (uint32_t)&__heap_base;

    uint32_t heap_end = MEMORY_SIZE - 1;

    uint32_t max = heap_end - heap_start - sizeof(chunk_header);

    // https://surma.dev/things/c-to-webassembly/

    if (size > max) {
        return NULL;
    }

    chunk_header chunk = {};

    if (first_chunk == NULL) {
        chunk.size = size;
        chunk.next = NULL;
        chunk.prev = NULL;

        /*
            copy newly created chunk header from stack to the heap
        */
        void * dest = (void *)heap_start;

        memcpy(dest, (void *)&chunk, sizeof(chunk_header));

        first_chunk = (chunk_header *)dest;

        return (void *)((char *)first_chunk + sizeof(chunk_header));
    }

    if ((uint32_t)heap_start + size + sizeof(chunk_header) < (uint32_t)first_chunk) {
        chunk.size = size;
        chunk.next = (uint32_t)first_chunk;
        chunk.prev = NULL;

        void * dest = (void *)((uint32_t)heap_start);

        memcpy(dest, (void *)&chunk, sizeof(chunk_header));

        first_chunk = (chunk_header *)dest;

        return (void *)((char *)first_chunk + sizeof(chunk_header));
    }

    chunk_header * next_chunk = first_chunk;

    while (next_chunk->next != NULL) {
        chunk_header * c1 = next_chunk;
        chunk_header * c2 = (chunk_header *)c1->next;

        next_chunk = c2;

        if (is_enough_space_between(c1, c2, size) == 0) {
            chunk.size = size;
            chunk.next = (uint32_t)c2;
            chunk.prev = (uint32_t)c1;

            uint32_t c1_end = (uint32_t)c1 + sizeof(chunk_header) + c1->size;

            /*
                copy newly created chunk header from stack to the heap
            */
            void * dest = (void *)(c1_end + 1);

            memcpy(dest, (void *)&chunk, sizeof(chunk_header));
            c1->next = (uint32_t)dest;
            c2->prev = (uint32_t)dest;

            return (void *)((char *)dest + sizeof(chunk_header));
        }
    }

    uint32_t last_chunk_end = (uint32_t)next_chunk + next_chunk->size + sizeof(chunk_header);

    if (heap_end - last_chunk_end >= (size + sizeof(chunk_header))) {
        chunk.size = size;
        chunk.next = NULL;
        chunk.prev = uint32_t(next_chunk);

        void * dest = (void *)(last_chunk_end + 1);

        memcpy(dest, (void *)&chunk, sizeof(chunk_header));
        next_chunk->next = (uint32_t)dest;

        return (void *)((char *)dest + sizeof(chunk_header));
    }
    

    return NULL;
};


void free(void * ptr) {
    chunk_header * chunk = (chunk_header *)((uint32_t)ptr - sizeof(chunk_header));

    chunk_header * next = (chunk_header *)chunk->next;
    chunk_header * prev = (chunk_header *)chunk->prev;

    prev->next = chunk->next;
    next->prev = chunk->prev;


    if (prev == NULL && next == NULL) {
        first_chunk = NULL;
        return;
    }


    if (prev == NULL) {
        first_chunk = next;
    }
};


// TODO: should realloc free pointer is case of not being successful?
void * realloc(void * ptr, uint32_t size) {
    if (ptr == NULL) {
        return malloc(size);
    }


    if (ptr != NULL && size == 0) {
        free(ptr); 
        return NULL;
    }

    chunk_header * chunk = (chunk_header *)((uint32_t)ptr - sizeof(chunk_header));

    if (chunk->size <= size) {
        chunk->size = size;
        return ptr;
    }

    if (chunk->next == NULL) {
        if ((uint32_t)ptr + size < MEMORY_SIZE) {
            chunk->size = size;
            return ptr;
        }

        return NULL;
    }

    log_int(chunk->size);
    log_int(size);

    if (chunk->next - (uint32_t)chunk - sizeof(chunk_header) >= size) {
        chunk->size = size;
        return ptr;
    }

    return NULL;
}
