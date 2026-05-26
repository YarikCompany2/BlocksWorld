#include "renderer.h"
#include "GLFW/glfw3.h"
#include "app.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t MIN_POSSIBLE_SIZE_OF_FILE = 1;

/* ---- SHADER ---- */
char *renderer_shader_get_source(const char shader_file[]) {
    FILE *file = fopen(shader_file, "r");
    if (!file) {
        fprintf(stderr, "Failed to open shader file\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0L, SEEK_END);
    uint32_t size = ftell(file) + 1;
    rewind(file);

    char* shader_source = malloc(sizeof(char) * size);
    if (!shader_source) {
        printf("Failed to allocate shader_text\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t elements_read = fread(shader_source, sizeof(char), size, file);
    if (elements_read <= MIN_POSSIBLE_SIZE_OF_FILE)
        printf("Specified shader file %s is empty\n", shader_file);

    shader_source[size - 1] = '\0';

    fclose(file);

    return shader_source;
}

uint32_t renderer_shader_compile(const char *shader_source, ShaderType shader_type) {
    GLenum gl_shader_type;
    char errShader[15];
    switch (shader_type) {
        case RENDERER_SHADER_VERTEX: {
            gl_shader_type = GL_VERTEX_SHADER;
            strcpy(errShader, "vertex");
            break;
        }
        case RENDERER_SHADER_FRAGMENT: {
            gl_shader_type = GL_FRAGMENT_SHADER;
            strcpy(errShader, "fragment");
            break;
        }
        default: fprintf(stderr, "Unknown shader_type was passed\n");
    }

    uint32_t shader = glCreateShader(gl_shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "Error occured during %s shader compilation\n%s", errShader, infoLog);
    }

    return shader;
}

Shader renderer_shader_vf_create(const char vertex_shader_file[], const char frag_shader_file[]) {
    char *vertex_shader_source = renderer_shader_get_source(vertex_shader_file);
    char *frag_shader_source = renderer_shader_get_source(frag_shader_file);

    Shader shader;
    shader.vertex_shader = renderer_shader_compile(vertex_shader_source, RENDERER_SHADER_VERTEX);
    shader.frag_shader = renderer_shader_compile(frag_shader_source, RENDERER_SHADER_FRAGMENT);

    free(vertex_shader_source);
    free(frag_shader_source);

    return shader;
}

ShaderProgram renderer_shader_program_create(Shader *shader) {
    ShaderProgram shader_program = glCreateProgram();
    glAttachShader(shader_program, shader->vertex_shader);
    glAttachShader(shader_program, shader->frag_shader);
    glLinkProgram(shader_program);

    int success;
    char infoLog[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        fprintf(stderr, "Error occured during shader program linking\n%s", infoLog);
    }

    glDeleteShader(shader->vertex_shader);
    glDeleteShader(shader->frag_shader);

    return shader_program;
}

/* ---- SHAPES ---- */
static Renderer *s_renderer;

Triangle renderer_triangle_create(Vertex a, Vertex b, Vertex c) {
    Triangle triangle;
    triangle.vertices[0] = a;
    triangle.vertices[1] = b;
    triangle.vertices[2] = c;

    return triangle;
}

void renderer_triangle_draw(Triangle *triangle) {
    const uint8_t TRIANGLE_VERTECIES_COUNT = 3;

    if (s_renderer->buffer_data.size + TRIANGLE_VERTECIES_COUNT > s_renderer->buffer_data.capacity)
        renderer_buffer_data_reallocate(&s_renderer->buffer_data);

    uint32_t i;
    for (i = 0; i < TRIANGLE_VERTECIES_COUNT; i++) {
        s_renderer->buffer_data.data[s_renderer->buffer_data.size + i] = triangle->vertices[i];
    }
    s_renderer->buffer_data.size += TRIANGLE_VERTECIES_COUNT;
}

/* ---- BUFFER ---- */
BufferData renderer_buffer_data_create() {
    BufferData bufferData;
    bufferData.capacity = 64;
    bufferData.size = 0;
    bufferData.data = malloc(sizeof(Vertex) * bufferData.capacity);

    printf("sizeof(Vertex) * bufferData.capacity: %lu\n", sizeof(Vertex) * bufferData.capacity);

    return bufferData;
}

void renderer_buffer_data_destroy(BufferData bufferData) {
    free(bufferData.data);
}

void renderer_buffer_data_reallocate(BufferData *bufferData) {
    bufferData->capacity *= 1.5f;
    bufferData->data = realloc(bufferData->data, sizeof(Vertex) * bufferData->capacity);
}

/* ---- RENDERER ---- */
Renderer* renderer_create(GLFWwindow* window) {
    Renderer* renderer = malloc(sizeof(Renderer));
    glGenVertexArrays(1, &renderer->VAO);
    glGenBuffers(1, &renderer->VBO);

    glBindVertexArray(renderer->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);

    renderer->window = window;
    renderer->buffer_data = renderer_buffer_data_create();

    return renderer;
}

void renderer_destroy(Renderer *renderer) {
    renderer_buffer_data_destroy(renderer->buffer_data);
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

    Shader basic_shader = renderer_shader_vf_create("../shaders/basic.vs", "../shaders/basic.fs");
    ShaderProgram basic_program = renderer_shader_program_create(&basic_shader);

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
