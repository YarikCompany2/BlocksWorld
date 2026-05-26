#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

#include "bw_math.h"

/* ---- SHADER ---- */
typedef enum {
    RENDERER_SHADER_VERTEX,
    RENDERER_SHADER_FRAGMENT,
} ShaderType;

typedef struct {
    uint32_t vertex_shader;
    uint32_t frag_shader;
} Shader;

typedef uint32_t ShaderProgram;

char *renderer_shader_get_source(const char shader_file[]);
uint32_t renderer_shader_compile(const char *shader_source, ShaderType shader_type);
Shader renderer_shader_vf_create(const char vertex_shader_file[], const char frag_shader_file[]);
ShaderProgram renderer_shader_program_create(Shader *shader);

/* ---- SHAPES ---- */
typedef struct {
    float x, y, z;
} Vertex;

typedef struct {
    Vertex vertices[3];
} Triangle;

Triangle renderer_triangle_create(Vertex a, Vertex b, Vertex c);

void renderer_triangle_draw(Triangle *triangle);

/* ---- BUFFER ---- */
typedef struct {
    uint32_t capacity;
    uint32_t size;
    Vertex* data;
} BufferData;

BufferData renderer_buffer_data_create();
void renderer_buffer_data_reallocate(BufferData *bufferData);

/* ---- RENDERER ---- */
typedef struct {
    GLFWwindow* window;
    uint32_t VAO, VBO;
    BufferData buffer_data;
} Renderer;

Renderer *renderer_create(GLFWwindow *window);

void renderer_start_drawing(GLFWwindow *window);
void renderer_end_drawing();

#endif /* RENDERER_H */
