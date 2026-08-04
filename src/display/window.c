#include "display/window.h"

#include <bw_enums.h>
#include "tool/error_reporting.h"

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

void window_glad_init(uint32_t width, uint32_t height) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        exit(EXIT_FAILURE);
    }
    
    glViewport(0, 0, width, height);
}

void window_framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* window_initialize(uint32_t width, uint32_t height, char title[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, BW_BOOLEAN_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    window_glad_init(width, height);
    glfwSetFramebufferSizeCallback(window, window_framebuffer_size_callback);

    #ifdef DEBUG
    int context_flags = 0;
    glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);

    if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        printf("Debug context created!\n");
        enableReportGlErrors();
    }
    #endif

    return window;
}

void window_terminate(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void window_process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, BW_BOOLEAN_TRUE);
    }
}