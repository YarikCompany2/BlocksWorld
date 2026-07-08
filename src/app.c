#include "app.h"

#include "promise_engine.h"

const uint32_t WIDTH = 800, HEIGHT = 600;

void app_run(void) {
    GLFWwindow *window = window_initialize(WIDTH, HEIGHT, "BlocksWorld");

    Renderer *renderer = renderer_create(window);

    Vertex vertices[3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    Triangle triangle = triangle_create(vertices[0], vertices[1], vertices[2]);

    renderer_start_drawing(window); {
        triangle_draw(renderer, &triangle);
    }
    renderer_end_drawing();

    window_terminate(window); 
}
