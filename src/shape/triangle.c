#include "shape/triangle.h"
#include "renderer/renderer.h"

Triangle triangle_create(Vertex a, Vertex b, Vertex c) {
    Triangle triangle;
    triangle.vertices[0] = a;
    triangle.vertices[1] = b;
    triangle.vertices[2] = c;

    return triangle;
}

void triangle_draw(Renderer *renderer, Triangle *triangle) {
    const uint8_t TRIANGLE_VERTECIES_COUNT = 3;

    if (renderer->buffer_data.size + TRIANGLE_VERTECIES_COUNT > renderer->buffer_data.capacity)
        buffer_data_reallocate(&renderer->buffer_data);

    uint32_t i;
    for (i = 0; i < TRIANGLE_VERTECIES_COUNT; i++) {
        renderer->buffer_data.data[renderer->buffer_data.size + i] = triangle->vertices[i];
    }
    renderer->buffer_data.size += TRIANGLE_VERTECIES_COUNT;
}
