#include "GL/glew.h"
//
// Created by vladi on 9/25/2026.
//
#include "../h/render.h"
GLuint create_buffer_texture(const Buffer& buff) {
    GLuint buff_texture;
    glGenTextures(1, &buff_texture);
    glBindTexture(GL_TEXTURE_2D, buff_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, buff.width, buff.height, 0, GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,buff.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return buff_texture;
}