//
// Created by vladi on 9/25/2026.
//

#ifndef UNTITLED4_SHADERS_H
#define UNTITLED4_SHADERS_H
#include "../cmake-build-debug/_deps/glfw-src/src/internal.h"
#include <GL/glew.h>
inline const char* vertex_shader =
    "\n"
    "#version 330\n"
    "\n"
    "noperspective out vec2 TexCoord;\n"
    "\n"
    "void main(void){\n"
    "\n"
    "    TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0;\n"
    "    TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0;\n"
    "    \n"
    "    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);\n"
    "}\n";
inline const char* fragment_shader =
    "\n"
    "#version 330\n"
    "\n"
    "uniform sampler2D buffer;\n"
    "noperspective in vec2 TexCoord;\n"
    "\n"
    "out vec3 outColor;\n"
    "\n"
    "void main(void){\n"
    "    outColor = texture(buffer, TexCoord).rgb;\n"
    "}\n";
void validate_shader(GLuint shader, const char *file=0);
bool validate_program(GLuint program);
void create_vertex_shader(GLuint shader);
void create_fragment_shader(GLuint shader);

#endif //UNTITLED4_SHADERS_H