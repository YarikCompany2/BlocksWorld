#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

/* ---- WINDOW ---- */
GLFWwindow *app_window_initialize(uint32_t width, uint32_t height, char title[]);
void app_window_run_loop(GLFWwindow *window, float dt);
void app_window_terminate(GLFWwindow *window);
void app_window_process_input(GLFWwindow *window);
/* ---------------- */

/* ---- GLAD ---- */
void app_glad_init(uint32_t width, uint32_t height);
void app_framebuffer_size_callback(GLFWwindow* window, int width, int height);
/* -------------- */

void app_run(void);

#endif /* APP_H */
