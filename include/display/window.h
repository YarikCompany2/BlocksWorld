#ifndef WINDOW_INCLUDE
#define WINDOW_INCLUDE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"

void window_glad_init(u32 width, u32 height);
void window_framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow *window_initialize(u32 width, u32 height, const char *title);
void window_run_loop(GLFWwindow *window, float dt);
void window_terminate(GLFWwindow *window);
void window_process_input(GLFWwindow *window);

#endif // WINDOW_INCLUDE