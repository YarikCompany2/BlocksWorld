#include "app.h"
#include "math/matrix.h"
#include "shape/triangle.h"

const uint32_t WIDTH = 800, HEIGHT = 600;

void app_run(void) {
    GLFWwindow *window = window_initialize(WIDTH, HEIGHT, "BlocksWorld");

    Vertex vertices[3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    Triangle triangle = triangle_create(vertices[0], vertices[1], vertices[2]);

    Matrix4f mat = mat4f_create(1.0f);
    mat4f_scalar_prod_calc(&mat, 4);

    Matrix4f mat2 = mat4f_create(3.0f);
    Matrix4f mat_result = mat4f_multiply(&mat, &mat2);
    
    mat4f_print(&mat_result);

    renderer_start_drawing(window);
        triangle_draw(&triangle);
    renderer_end_drawing();

    window_terminate(window); 
}
