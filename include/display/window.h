#ifndef WINDOW_INCLUDE
#define WINDOW_INCLUDE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

void window_glad_init(uint32_t width, uint32_t height);
void window_framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow *window_initialize(uint32_t width, uint32_t height, char title[]);
void window_run_loop(GLFWwindow *window, float dt);
void window_terminate(GLFWwindow *window);
void window_process_input(GLFWwindow *window);

#endif // WINDOW_INCLUDE