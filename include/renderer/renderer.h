#ifndef RENDERER_H
#define RENDERER_H

#include "renderer/buffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

typedef struct {
    GLFWwindow* window;
    uint32_t VAO, VBO;
    BufferData buffer_data;
} Renderer;

Renderer *renderer_create(GLFWwindow *window);

void renderer_start_drawing(GLFWwindow *window);
void renderer_end_drawing();

#endif // RENDERER_H
