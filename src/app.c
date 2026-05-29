#include "app.h"

#include "renderer.h"
#include "bw_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint32_t WIDTH = 800, HEIGHT = 600;

/* ---- WINDOW ---- */
GLFWwindow* app_window_initialize(uint32_t width, uint32_t height, char title[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    return window;
}

void app_window_terminate(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void app_window_process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, BWB_TRUE);
    }
}

/* ---- GLAD ---- */
void app_glad_init(uint32_t width, uint32_t height) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        exit(EXIT_FAILURE);
    }
    
    glViewport(0, 0, width, height);
}

void app_framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void app_run(void) {
    Matrix4f mat;
    Matrix4f mat2;

    float data[4][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 14, 15, 16 },
    };

    memcpy(mat.data, data, sizeof(data));
    memcpy(mat2.data, data, sizeof(data));

    /* Matrix4f result = math_mat4f_multiply(&mat, &mat2); */

    math_mat4f_print(&mat);
    math_mat4f_print(&mat2);

    Matrix4f resultMat = math_mat4f_multiply(&mat, &mat2);

    math_mat4f_print(&resultMat);

    /* GLFWwindow *window = app_window_initialize(WIDTH, HEIGHT, "BlocksWorld");
    app_glad_init(WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, app_framebuffer_size_callback);

    Vertex vertices[3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    Vertex vertices2[3] = {
        -1.0f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0,
        0.0f, 0.5f, 0.0f,
    };

    Triangle triangle = renderer_triangle_create(vertices[0], vertices[1], vertices[2]);
    Triangle triangle2 = renderer_triangle_create(vertices2[0], vertices2[1], vertices2[2]);

    renderer_start_drawing(window); {
        renderer_triangle_draw(&triangle);
        renderer_triangle_draw(&triangle2);
    }
    renderer_end_drawing();


    app_window_terminate(window); */
}
