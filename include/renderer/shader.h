#ifndef SHADER_INCLUDE
#define SHADER_INCLUDE

#include <stdint.h>

typedef enum {
    BW_SHADER_VERTEX,
    BW_SHADER_FRAGMENT,
} ShaderType;

typedef struct {
    uint32_t vertex_shader;
    uint32_t frag_shader;
} Shader;

typedef uint32_t ShaderProgram;

char *shader_get_source(const char shader_file[]);
uint32_t shader_compile(const char *shader_source, ShaderType shader_type);
Shader shader_vf_create(const char vertex_shader_file[], const char frag_shader_file[]);
ShaderProgram shader_program_create(Shader *shader);

#endif // SHADER_INCLUDE