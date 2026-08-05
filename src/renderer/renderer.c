#include "renderer/renderer.h"

#include "GLFW/glfw3.h"
#include "display/window.h"
#include "promise_enums.h"
#include "renderer/buffer.h"
#include "renderer/shader.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static Renderer *promise_renderer = NULL;

void renderer_create(GLFWwindow* window) {
    promise_renderer = malloc(sizeof(Renderer));
    glGenVertexArrays(1, &promise_renderer->VAO);
    glGenBuffers(1, &promise_renderer->VBO);

    glBindVertexArray(promise_renderer->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, promise_renderer->VBO);

    promise_renderer->window = window;
    promise_renderer->buffer_data = buffer_data_create();
}

void renderer_destroy(Renderer *renderer) {
    buffer_data_destroy(renderer->buffer_data);
    free(renderer);
}

Renderer *renderer_get() {
    if (promise_renderer) {
        return promise_renderer;
    } else {
        fprintf(stderr, "You can't call uninitialized renderer\n");
        exit(EXIT_FAILURE);
    }
}

void renderer_start_drawing(GLFWwindow *window) {
    if (promise_renderer) {
        fprintf(stderr, "You can call renderer_start_drawing() only one time\n");
        exit(EXIT_FAILURE);
    }

    renderer_create(window);
}

void renderer_end_drawing() {
    if (!promise_renderer) {
        fprintf(stderr, "You can't call renderer_end_drawing() function before renderer_start_drawing()\n");
        exit(EXIT_FAILURE);
    }

    glBindBuffer(GL_ARRAY_BUFFER, promise_renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * promise_renderer->buffer_data.size, promise_renderer->buffer_data.data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    printf("buffer data size: %d\n", promise_renderer->buffer_data.size);
    buffer_print_data(&promise_renderer->buffer_data);

    Shader basic_shader = shader_vf_create("../shaders/basic.vs", "../shaders/basic.fs");
    ShaderProgram basic_program = shader_program_create(&basic_shader);

    int vertex_model_uniform = glGetUniformLocation(basic_program, "model");
    glUseProgram(basic_program);

    while (!glfwWindowShouldClose(promise_renderer->window)) {
        window_process_input(promise_renderer->window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(basic_program);
        glBindVertexArray(promise_renderer->VAO);
        glDrawArrays(GL_TRIANGLES, 0, promise_renderer->buffer_data.size / 3);

        glfwSwapBuffers(promise_renderer->window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &promise_renderer->VAO);
    glDeleteBuffers(1, &promise_renderer->VBO);
    glDeleteProgram(basic_program);

    renderer_destroy(promise_renderer);
}
