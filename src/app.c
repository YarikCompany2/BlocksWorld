#include "app.h"

#include "renderer.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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

void app_window_run_loop(GLFWwindow *window, float dt) {
    while (!glfwWindowShouldClose(window)) {
        app_window_process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
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
/* -------------- */

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
/* -------------- */

void app_run(void) {
    GLFWwindow *window = app_window_initialize(WIDTH, HEIGHT, "BlocksWorld");
    app_glad_init(WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, app_framebuffer_size_callback);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    uint32_t VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    Shader basic_shader = renderer_shader_vf_create("../shaders/basic.vs", "../shaders/basic.fs");
    ShaderProgram basic_program = renderer_shader_program_create(&basic_shader);

    app_window_run_loop(window, 5.f);

    app_window_terminate(window);
}
