#include "math/promise_math.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float math_degrees_to_radians_convert(float degrees) {
    return (M_PI / 180) * degrees;
}
