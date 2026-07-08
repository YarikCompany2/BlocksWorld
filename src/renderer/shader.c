#include "renderer/shader.h"

#include <glad/glad.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const uint8_t MIN_POSSIBLE_SIZE_OF_FILE = 1;

char *shader_get_source(const char shader_file[]) {
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

uint32_t shader_compile(const char *shader_source, ShaderType shader_type) {
    GLenum gl_shader_type;
    char errShader[15];
    switch (shader_type) {
        case BW_SHADER_VERTEX: {
            gl_shader_type = GL_VERTEX_SHADER;
            strcpy(errShader, "vertex");
            break;
        }
        case BW_SHADER_FRAGMENT: {
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

Shader shader_vf_create(const char vertex_shader_file[], const char frag_shader_file[]) {
    char *vertex_shader_source = shader_get_source(vertex_shader_file);
    char *frag_shader_source = shader_get_source(frag_shader_file);

    Shader shader;
    shader.vertex_shader = shader_compile(vertex_shader_source, BW_SHADER_VERTEX);
    shader.frag_shader = shader_compile(frag_shader_source, BW_SHADER_FRAGMENT);

    free(vertex_shader_source);
    free(frag_shader_source);

    return shader;
}

ShaderProgram shader_program_create(Shader *shader) {
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