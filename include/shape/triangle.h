#ifndef TRIANGLE_INCLUDE
#define TRIANGLE_INCLUDE

#include "shape/shape.h"

typedef struct {
    Vertex vertices[3];
} Triangle;

Triangle triangle_create(Vertex a, Vertex b, Vertex c);

void triangle_draw(Triangle *triangle);
void triangle_print(Triangle *triangle, const char* triangle_name);

#endif // TRIANGLE_INCLUDE