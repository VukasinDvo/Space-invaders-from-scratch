//
// Created by vladi on 10/2/2026.
//
#include "../h/Game.h"

#include "../h/sprite.h"

Game gameInit(Buffer &buffer,Sprite alien_sprite,Sprite player_sprite) {
    Game game;

    game.width=buffer.width;
    game.height=buffer.height;
    game.num_aliens = 55;
    game.aliens = new Alien[game.num_aliens];

    game.player.x = 112 - 5;
    game.player.y = 32;

    game.player.life = 3;

    for(size_t yi = 0; yi < 5; ++yi)
    {
        for(size_t xi = 0; xi < 11; ++xi)
        {
            game.aliens[yi * 11 + xi].x = 16 * xi + 20;
            game.aliens[yi * 11 + xi].y = 17 * yi + 128;
        }
    }
    for (size_t i = 0; i < game.num_aliens; i++) {
        const Alien &alien = game.aliens[i];
        buffered_sprite_draw(&buffer, alien_sprite,
            alien.x, alien.y, rgb_to_uint32(128, 0, 0));
    }

    buffered_sprite_draw(&buffer, player_sprite, game.player.x, game.player.y, rgb_to_uint32(128, 0, 0));

    return game;

}
