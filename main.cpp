#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "h/buffer.h"
#include "h/Game.h"
#include "h/render.h"
#include "h/shaders.h"
#include "h/sprite.h"
#include "h/SpriteAnimation.h"

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
    glfwSwapInterval(1);

    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    Buffer buf = buffer_init();

    Sprite alien_sprite = get_alien_sprite();
    Sprite player_sprite = get_ship_sprite();

    SpriteAnimation* alien_animation = create_sprite_animation(
    { get_alien_sprite(), get_alien_sprite2() },
    true,
    10
);

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

    int player_move_dir=1;

    while (!glfwWindowShouldClose(window)) {
        buffer_clear(&buf, 0);

        // Izračunaj trenutni frame animacije
        size_t current_frame = alien_animation->time / alien_animation->frame_durration;
        Sprite* current_alien_sprite = alien_animation->frames[current_frame];

        for (size_t i = 0; i < game.num_aliens; i++) {
            const Alien &alien = game.aliens[i];
            buffered_sprite_draw(&buf, *current_alien_sprite, alien.x, alien.y,
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

        ++alien_animation->time;
        if (alien_animation->time == alien_animation->num_frames * alien_animation->frame_durration) {
            if (alien_animation->loop) {
                alien_animation->time = 0;
            } else {
                delete alien_animation;
                alien_animation = nullptr;
            }
        }

        if(game.player.x + player_sprite.width + player_move_dir >= game.width - 1)
        {
            game.player.x = game.width - player_sprite.width - player_move_dir - 1;
            player_move_dir *= -1;
        }
        else if((int)game.player.x + player_move_dir <= 0)
        {
            game.player.x = 0;
            player_move_dir *= -1;
        }
        else game.player.x += player_move_dir;
    }

    delete[] buf.data;
    delete[] game.aliens;

    glDeleteVertexArrays(1, &fullscreen_triangle_vao);
    glDeleteProgram(shader_id);
    glfwTerminate();
    return 0;
}