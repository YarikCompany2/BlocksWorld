#include "renderer/renderer.h"

#include "GLFW/glfw3.h"
#include "bw_enums.h"
#include "renderer/buffer.h"
#include "renderer/shader.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static Renderer *s_renderer;

Renderer* renderer_create(GLFWwindow* window) {
    Renderer* renderer = malloc(sizeof(Renderer));
    glGenVertexArrays(1, &renderer->VAO);
    glGenBuffers(1, &renderer->VBO);

    glBindVertexArray(renderer->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);

    renderer->window = window;
    renderer->buffer_data = buffer_data_create();

    return renderer;
}

void renderer_destroy(Renderer *renderer) {
    buffer_data_destroy(renderer->buffer_data);
    free(renderer);
}

void renderer_start_drawing(GLFWwindow *window) {
    if (s_renderer) {
        fprintf(stderr, "You can call renderer_start_drawing() only one time\n");
        exit(EXIT_FAILURE);
    }

    /* uint32_t VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO); */

    s_renderer = renderer_create(window);
}

void renderer_end_drawing() {
    if (!s_renderer) {
        fprintf(stderr, "You can't call renderer_end_drawing() function before renderer_start_drawing()\n");
        exit(EXIT_FAILURE);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, s_renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * s_renderer->buffer_data.size, s_renderer->buffer_data.data, GL_STATIC_DRAW);

    printf("sizeof * buffer_data.size: %lu\n", (sizeof(Vertex) * s_renderer->buffer_data.size));
    printf("buffer_data.size: %d\n", s_renderer->buffer_data.size);

    Shader basic_shader = shader_vf_create("../shaders/basic.vs", "../shaders/basic.fs");
    ShaderProgram basic_program = shader_program_create(&basic_shader);

    int vertex_model_uniform = glGetUniformLocation(basic_program, "model");
    glUseProgram(basic_program);

    while (!glfwWindowShouldClose(s_renderer->window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(basic_program);
        glBindVertexArray(s_renderer->VAO);
        glDrawArrays(GL_TRIANGLES, 0, s_renderer->buffer_data.size);

        glfwSwapBuffers(s_renderer->window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &s_renderer->VAO);
    glDeleteBuffers(1, &s_renderer->VBO);
    glDeleteProgram(basic_program);

    renderer_destroy(s_renderer);
}
