#ifndef SHAPE_INCLUDE
#define SHAPE_INCLUDE

typedef struct {
    float x, y, z;
} Vertex;

void vertex_print(Vertex *vertex, const char* vertex_name);

#endif // SHAPE_INCLUDE