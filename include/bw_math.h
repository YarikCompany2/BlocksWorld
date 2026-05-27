#ifndef BW_MATH_INCLUDE
#define BW_MATH_INCLUDE

#include <stdint.h>

/* ---- Vectors ---- */
/* --- floats --- */
typedef struct {
    float x, y;
} Vector2f;

typedef struct {
    float x, y, z;
} Vector3f;

typedef struct {
    float x, y, z, w;
} Vector4f;

/* --- uints --- */
typedef struct {
    uint32_t x, y;
} Vector2u;

typedef struct {
    uint32_t x, y, z;
} Vector3u;

typedef struct {
    uint32_t x, y, z, w;
} Vector4u;

/* --- 4 values --- */
typedef struct {
    int32_t x, y;
} Vector2i;

typedef struct {
    int32_t x, y, z;
} Vector3i;

typedef struct {
    int32_t x, y, z, w;
} Vector4i;

/* ---- Matrices ---- */
/* --- floats --- */
typedef struct {
    float data[2][2];
} Matrix2f;

typedef struct {
    float data[3][3];
} Matrix3f;

typedef struct {
    float data[4][4];
} Matrix4f;

Matrix4f math_matrix4f_create(float initial_value);
void math_matrix4f_print(Matrix4f* mat);

void math_matrix4f_rotate(Matrix4f* mat, float radians, Vector3f vec3f);

/* ---- Conversions ---- */
float math_degrees_to_radians_convert(float degrees);

#endif /* BW_MATH_INCLUDE */
