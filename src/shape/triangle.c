#include "shape/triangle.h"
#include "renderer/renderer.h"
#include "shape/shape.h"

#include <stdio.h>

Triangle triangle_create(Vertex a, Vertex b, Vertex c) {
    Triangle triangle;
    triangle.vertices[0] = a;
    triangle.vertices[1] = b;
    triangle.vertices[2] = c;

    return triangle;
}

void triangle_draw(Triangle *triangle) {
    const uint8_t TRIANGLE_VERTECIES_COUNT = 3;

    if (promise_renderer->buffer_data.size + TRIANGLE_VERTECIES_COUNT > promise_renderer->buffer_data.capacity)
        buffer_data_reallocate(&promise_renderer->buffer_data);

    uint32_t i;
    for (i = 0; i < TRIANGLE_VERTECIES_COUNT; i++) {
        promise_renderer->buffer_data.data[promise_renderer->buffer_data.size + i] = triangle->vertices[i];
    }
    promise_renderer->buffer_data.size += TRIANGLE_VERTECIES_COUNT;
}

void triangle_print(Triangle *triangle, const char* triangle_name) {
    printf("Triangle %s:\n", triangle_name);
    vertex_print(&triangle->vertices[0], "a");
    vertex_print(&triangle->vertices[1], "a");
    vertex_print(&triangle->vertices[2], "a");
}
