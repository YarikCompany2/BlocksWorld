#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

#include <stdint.h>

typedef struct {
    float x, y;
} Vector2f;

typedef struct {
    float x, y, z;
} Vector3f;

typedef struct {
    float x, y, z, w;
} Vector4f;

typedef struct {
    uint32_t x, y;
} Vector2u;

typedef struct {
    uint32_t x, y, z;
} Vector3u;

typedef struct {
    uint32_t x, y, z, w;
} Vector4u;

typedef struct {
    int32_t x, y;
} Vector2i;

typedef struct {
    int32_t x, y, z;
} Vector3i;

typedef struct {
    int32_t x, y, z, w;
} Vector4i;

#endif // VECTOR_INCLUDE