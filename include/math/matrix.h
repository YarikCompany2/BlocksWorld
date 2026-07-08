#ifndef MATRIX_INCLUDE
#define MATRIX_INCLUDE

#include <stdint.h>

typedef enum {
    BW_AXIS_X, BW_AXIS_Y, BW_AXIS_Z
} Axis;

typedef struct {
    float data[2][2];
} Matrix2f;

typedef struct {
    float data[3][3];
} Matrix3f;

typedef struct {
    float data[4][4];
} Matrix4f;

static void mat_fill(uint32_t elAmount, float mat[elAmount][elAmount], float scalar);
static void mat_scalar_prod_calc(uint32_t elAmount, float mat[elAmount][elAmount], float scalar);
static void mat_print(uint32_t elAmount, float mat[elAmount][elAmount]);

Matrix4f mat4f_create(float initial_value);

void mat4f_scalar_prod_calc(Matrix4f *mat, float scalar);
Matrix4f mat4f_rotate(Matrix4f *mat, float radians, Axis axis);
Matrix4f mat4f_multiply(Matrix4f *mat1, Matrix4f *mat2);

void mat4f_print(Matrix4f* mat);

#endif // MATRIX_INCLUDE