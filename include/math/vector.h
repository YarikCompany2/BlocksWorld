#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

#include "common.h"

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
    u32 x, y;
} Vector2u;

typedef struct {
    u32 x, y, z;
} Vector3u;

typedef struct {
    u32 x, y, z, w;
} Vector4u;

typedef struct {
    i32 x, y;
} Vector2i;

typedef struct {
    i32 x, y, z;
} Vector3i;

typedef struct {
    i32 x, y, z, w;
} Vector4i;

#endif // VECTOR_INCLUDE