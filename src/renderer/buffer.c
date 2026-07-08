#include "renderer/buffer.h"

#include <stdlib.h>
#include <stdio.h>

BufferData buffer_data_create() {
    BufferData bufferData;
    bufferData.capacity = 64;
    bufferData.size = 0;
    bufferData.data = malloc(sizeof(Vertex) * bufferData.capacity);

    printf("sizeof(Vertex) * bufferData.capacity: %lu\n", sizeof(Vertex) * bufferData.capacity);

    return bufferData;
}

void buffer_data_destroy(BufferData bufferData) {
    free(bufferData.data);
}

void buffer_data_reallocate(BufferData *bufferData) {
    bufferData->capacity *= 1.5f;
    bufferData->data = realloc(bufferData->data, sizeof(Vertex) * bufferData->capacity);
}