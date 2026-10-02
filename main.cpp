#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "h/buffer.h"
#include "h/Game.h"
#include "h/render.h"
#include "h/shaders.h"
#include "h/sprite.h"

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

int main() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW.\n");
        glfwTerminate();
        return -1;
    }
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    Buffer buf = buffer_init();

    Sprite alien_sprite = get_alien_sprite();
    Sprite player_sprite = get_ship_sprite();

    Game game = gameInit(buf,alien_sprite,player_sprite);

    GLuint fullscreen_triangle_vao;
    glGenVertexArrays(1, &fullscreen_triangle_vao);
    glBindVertexArray(fullscreen_triangle_vao);

    GLuint shader_id = glCreateProgram();

    create_fragment_shader(shader_id);
    create_vertex_shader(shader_id);

    glLinkProgram(shader_id);

    if (!validate_program(shader_id)) {
        fprintf(stderr, "Error while validating shader.\n");
        glfwTerminate();
        glDeleteVertexArrays(1, &fullscreen_triangle_vao);
        delete[] buf.data;
        return -1;
    }

    glUseProgram(shader_id);

    auto buffer_texture = create_buffer_texture(buf);

    GLint location = glGetUniformLocation(shader_id, "buffer");
    glUniform1i(location, 0);

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(fullscreen_triangle_vao);
    uint32_t clear_color = rgb_to_uint32(0, 128, 0);

    while (!glfwWindowShouldClose(window)) {
        buffer_clear(&buf, 0);

        for (size_t i = 0; i < game.num_aliens; i++) {
            const Alien &alien = game.aliens[i];
            buffered_sprite_draw(&buf, alien_sprite, alien.x, alien.y,
                rgb_to_uint32(128, 0, 0));
        }

        buffered_sprite_draw(&buf, player_sprite, game.player.x, game.player.y,
            rgb_to_uint32(128, 0, 0));

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, buf.width, buf.height,
                         GL_RGBA, GL_UNSIGNED_BYTE, buf.data);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete[] buf.data;
    delete[] game.aliens;

    glDeleteVertexArrays(1, &fullscreen_triangle_vao);
    glDeleteProgram(shader_id);
    glfwTerminate();
    return 0;
}