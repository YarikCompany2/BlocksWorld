#include "bw_math.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdio.h>
#include <math.h>

/* ---- Matrices ---- */

void math_mat_fill(int elAmount, float mat[elAmount][elAmount], float initial_value) {
    uint32_t i, j;
    for (i = 0; i < elAmount; i++) {
        for (j = 0; j < elAmount; j++) {
            if (i == j) mat[i][j] = initial_value;
            else mat[i][j] = 0;
        }
    }
}

void math_mat_scalar_prod_calc(int elAmount, float mat[elAmount][elAmount], float scalar) {
    uint32_t i, j;
    for (i = 0; i < elAmount; i++) {
        for (j = 0; j < elAmount; j++) {
            mat[i][j] *= scalar;
        }
    }
}

Matrix4f math_mat4f_rotate(Matrix4f *mat, float radians, Axis axis) {
    Matrix4f rotation_matrix = math_mat4f_create(1.0f);
    switch (axis) {
        case BW_AXIS_X:
            rotation_matrix.data[1][1] = cos(radians);
            rotation_matrix.data[1][2] = -sin(radians);
            rotation_matrix.data[2][1] = sin(radians);
            rotation_matrix.data[2][2] = cos(radians);
            break;
        case BW_AXIS_Y:
            rotation_matrix.data[0][0] = cos(radians);
            rotation_matrix.data[0][2] = sin(radians);
            rotation_matrix.data[2][0] = -sin(radians);
            rotation_matrix.data[2][2] = cos(radians);
            break;
        case BW_AXIS_Z:
            rotation_matrix.data[0][0] = cos(radians);
            rotation_matrix.data[0][1] = -sin(radians);
            rotation_matrix.data[1][0] = sin(radians);
            rotation_matrix.data[1][1] = cos(radians);
            break;
        default: printf("Specified axis doesn't exist\n");
    }

    Matrix4f rotated_matrix = math_mat4f_multiply(mat, &rotation_matrix);

    math_mat4f_print(&rotated_matrix);

    return rotation_matrix;
}

void math_mat_print(int elAmount, float mat[elAmount][elAmount]) {
    uint32_t i, j;
    for (i = 0; i < elAmount; i++) {
        for (j = 0; j < elAmount; j++) {
            printf("%5.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

/* --- float --- */
Matrix4f math_mat4f_create(float initial_value) {
    Matrix4f mat;
    math_mat_fill(4, mat.data, initial_value);

    return mat;
}

void math_mat4f_scalar_prod_calc(Matrix4f* mat, float scalar) {
    math_mat_scalar_prod_calc(4, mat->data, scalar);
}

Matrix4f math_mat4f_multiply(Matrix4f *mat1, Matrix4f *mat2) {
    Matrix4f newMat;
    uint32_t i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            newMat.data[i][j] = 0;
            for (k = 0; k < 4; k++) {
                newMat.data[i][j] += mat1->data[i][k] * mat2->data[k][j];
            }
        }
    }

    return newMat;
}

void math_mat4f_print(Matrix4f* mat) {
    math_mat_print(4, mat->data);
}

/* ---- Conversions ---- */
float math_degrees_to_radians_convert(float degrees) {
    return (M_PI / 180) * degrees;
}
