#ifndef TRIANGLE_INCLUDE
#define TRIANGLE_INCLUDE

#include "shape/shape.h"
#include "renderer/renderer.h"

typedef struct {
    Vertex vertices[3];
} Triangle;

Triangle triangle_create(Vertex a, Vertex b, Vertex c);

void triangle_draw(Renderer *renderer, Triangle *triangle);

#endif // TRIANGLE_INCLUDE