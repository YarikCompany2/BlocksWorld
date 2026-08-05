#include "shape/triangle.h"
#include "renderer/buffer.h"
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
    const uint8_t TRIANGLE_FLOAT_COUNT = 3 * 3;

    if (buffer_data_has_enough_space_for(&renderer_get()->buffer_data, TRIANGLE_FLOAT_COUNT))
        buffer_data_reallocate(&renderer_get()->buffer_data);

    buffer_data_add_triangle(&renderer_get()->buffer_data, triangle);
}

void triangle_print(Triangle *triangle, const char* triangle_name) {
    printf("Triangle %s:\n", triangle_name);
    vertex_print(&triangle->vertices[0], "a");
    vertex_print(&triangle->vertices[1], "b");
    vertex_print(&triangle->vertices[2], "c");
}
