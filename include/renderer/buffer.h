#ifndef BUFFER_INCLUDE
#define BUFFER_INCLUDE

#include "shape/shape.h"

#include <stdint.h>

typedef struct {
    uint32_t capacity;
    uint32_t size;
    Vertex* data;
} BufferData;

BufferData buffer_data_create();
void buffer_data_reallocate(BufferData *bufferData);
void buffer_data_destroy(BufferData bufferData); // <-- Check its parameter

#endif // BUFFER_INCLUDE