#ifndef BUFFER_INCLUDE
#define BUFFER_INCLUDE

#include "shape/shape.h"
#include "shape/triangle.h"
#include "promise_enums.h"

#include <stdint.h>

// counts in float
typedef struct {
    uint32_t capacity;
    uint32_t size;
    float* data;
} BufferData;

BufferData buffer_data_create();
void buffer_data_reallocate(BufferData *bufferData);
void buffer_data_destroy(BufferData bufferData);

// Inserting Data
void buffer_data_add_float(BufferData *buffer_data, float data);
void buffer_data_add_vertex(BufferData *buffer_data, const Vertex *data);
void buffer_data_add_triangle(BufferData *buffer_data, const Triangle *data);

// Logic
PromiseBoolean buffer_data_has_enough_space_for(BufferData *buffer_data, uint32_t size);

// Debug
void buffer_print_data(BufferData *buffer_data);


#endif // BUFFER_INCLUDE