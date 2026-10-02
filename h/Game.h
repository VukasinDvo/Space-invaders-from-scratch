//
// Created by vladi on 10/2/2026.
//

#ifndef UNTITLED4_GAME_H
#define UNTITLED4_GAME_H
#include <cstdint>

#include "sprite.h"

struct Alien {
    size_t x,y;
    uint8_t type;
};
struct Player{
    size_t x,y;
    size_t life;

};
struct Game {
    size_t width,height;
    size_t num_aliens;
    Alien* aliens;
    Player player;
};

Game gameInit(Buffer &buffer, Sprite alien_sprite, Sprite player_sprite);
#endif //UNTITLED4_GAME_H