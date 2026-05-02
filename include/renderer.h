#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <stdint.h>

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
/* ----------------- */


#endif /* RENDERER_H */
