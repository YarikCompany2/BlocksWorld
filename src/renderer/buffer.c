#include "renderer/buffer.h"

#include "shape/shape.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const uint32_t VERTEX_AMOUNT_IN_FLOAT = 3;

BufferData buffer_data_create() {
    BufferData buffer_data;
    buffer_data.capacity = 64;
    buffer_data.size = 0;
    buffer_data.data = malloc(sizeof(float) * buffer_data.capacity);

    return buffer_data;
}

void buffer_data_destroy(BufferData buffer_data) {
    free(buffer_data.data);
}

void buffer_data_reallocate(BufferData *buffer_data) {
    buffer_data->capacity *= 1.5f;
    buffer_data->data = realloc(buffer_data->data, sizeof(float) * buffer_data->capacity);
}

// Inserting Data
void buffer_data_add_data(BufferData *buffer_data, const void *data, uint32_t amount) {
    memcpy(buffer_data->data, data, sizeof(float) * amount);
    buffer_data->size += amount;
}

void buffer_data_add_float(BufferData *buffer_data, float data) {
    buffer_data_add_data(buffer_data, &data, 1);
}

void buffer_data_add_vertex(BufferData *buffer_data, const Vertex *data) {
    buffer_data_add_data(buffer_data, &data, VERTEX_AMOUNT_IN_FLOAT);
}

void buffer_data_add_triangle(BufferData *buffer_data, const Triangle *data) {
    buffer_data_add_data(buffer_data, &data->vertices, VERTEX_AMOUNT_IN_FLOAT * 3);
}

// Logic
PromiseBoolean buffer_data_has_enough_space_for(BufferData *buffer_data, uint32_t size) {
    return buffer_data->size + size > buffer_data->capacity ? PROMISE_B_TRUE : PROMISE_B_FALSE;
}

// Debug
void buffer_print_data(BufferData *buffer_data) {
    printf("Buffer data: ");
    for (uint32_t i = 0; i < buffer_data->size; i++) {
        printf("%f ", buffer_data->data[i]);
    }
    printf("\n");
}