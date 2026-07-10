#include "shape/shape.h"

#include <stdio.h>

void vertex_print(Vertex *vertex, const char* vertex_name) {
    printf("Vertex %s: x=%f, y=%f, z=%f\n", vertex_name, vertex->x, vertex->y, vertex->z);
}