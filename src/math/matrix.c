#include "math/matrix.h"
#include <math.h>
#include <stdio.h>
#include "common.h"

#define MAT_FILL(type, mat, el_amount, initial_value) \
    do { \
        for (u32 i = 0; (i < el_amount); i++) { \
            for (u32 j = 0; (j < el_amount); j++) { \
                if (i == j) \
                    (mat[i][j] = ((type)initial_value)); \
                else \
                    (mat[i][j] = 0); \
            } \
        } \
    } while(false) \

#define MAT_SCALAR_PRODUCT_CALC(type, mat, el_amount, scalar) \
    do { \
        for (u32 i = 0; (i < el_amount); i++) { \
            for (u32 j = 0; (j < el_amount); j++) { \
                (mat[i][j] *= ((type)scalar)); \
            } \
        } \
    } while(false) \

#define MAT_PRINT(mat, el_amount, print_format) \
    do { \
        for (u32 i = 0; (i < el_amount); i++) { \
            for (u32 j = 0; (j < el_amount); j++) { \
                printf(print_format, mat[i][j]); \
            } \
            printf("\n"); \
        } \
    } while(false) \

#define MAT_MULTIPLY(mat1, mat2, mat_new, el_amount) \
    do { \
        for (u32 i = 0; (i < el_amount); i++) { \
            for (u32 j = 0; (j < el_amount); j++) { \
                mat_new.data[i][j] = 0; \
                for (u32 k = 0; (k < el_amount); k++) { \
                    mat_new.data[i][j] += ((mat1->data[i][k]) * (mat2->data[k][j])); \
                } \
            } \
        } \
    } while(false) \

Matrix4f mat4f_rotate(Matrix4f *mat, float radians, Axis axis) {
    Matrix4f rotation_matrix = mat4f_create(1.0f);
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

    Matrix4f rotated_matrix = mat4f_multiply(mat, &rotation_matrix);

    mat4f_print(&rotated_matrix);

    return rotation_matrix;
}

Matrix4f mat4f_create(float initial_value) {
    Matrix4f mat;
    MAT_FILL(float, mat.data, 4, initial_value);

    return mat;
}

void mat4f_scalar_prod_calc(Matrix4f *mat, float scalar) {
    MAT_SCALAR_PRODUCT_CALC(float, mat->data, 4, scalar);
}

Matrix4f mat4f_multiply(Matrix4f *mat1, Matrix4f *mat2) {
    Matrix4f result_mat;

    MAT_MULTIPLY(mat1, mat2, result_mat, 4);

    return result_mat;
}

void mat4f_print(Matrix4f *mat) {
    MAT_PRINT(mat->data, 4, "%5.2f ");
}