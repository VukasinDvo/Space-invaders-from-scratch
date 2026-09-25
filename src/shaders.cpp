//
// Created by vladi on 9/25/2026.
//
#include "../h/shaders.h"

#include <cstdio>


void validate_shader(GLuint shader, const char *file) {
    static const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    GLsizei length;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length,buffer);

    if(length > 0)
    {
        printf("Shader %d(%s) compile error: %s\n",
            shader, (file ? file: ""), buffer);
    }

}

bool validate_program(GLuint program)
{
    static const GLsizei BUFFER_SIZE = 512;
    GLchar buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

    if(length > 0)
    {
        printf("Program %d link error: %s\n", program, buffer);
        return false;
    }

    return true;
}
void create_vertex_shader(GLuint shader) {
    auto shader_vp = glCreateShader(GL_VERTEX_SHADER);


    glShaderSource(shader_vp, 1, &vertex_shader, 0);
    glCompileShader(shader_vp);
    validate_shader(shader_vp, vertex_shader);
    glAttachShader(shader, shader_vp);

    glDeleteShader(shader_vp);

}
void create_fragment_shader(GLuint shader) {
    auto shader_fp = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(shader_fp, 1, &fragment_shader, 0);
    glCompileShader(shader_fp);
    validate_shader(shader_fp, fragment_shader);
    glAttachShader(shader, shader_fp);

    glDeleteShader(shader_fp);

}

