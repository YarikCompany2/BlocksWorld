#include "bw_math.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdio.h>

Matrix4f math_matrix4f_create(float initial_value) {
    Matrix4f mat;
    uint32_t i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) mat.data[i][j] = initial_value;
            else mat.data[i][j] = 0;
        }
    }

    return mat;
}

void math_matrix4f_print(Matrix4f* mat) {
    uint32_t i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%5.2f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

/* ---- Conversions ---- */
float math_degrees_to_radians_convert(float degrees) {
    return (M_PI / 180) * degrees;
}
