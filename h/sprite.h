//
// Created by vladi on 10/2/2026.
//

#ifndef UNTITLED4_SPRITE_H
#define UNTITLED4_SPRITE_H
#include <cstdint>
#include "buffer.h"

struct Sprite {
    size_t width,height;
    uint8_t *data;
};

void buffered_sprite_draw(Buffer* buffer,const Sprite &sprite,size_t x,size_t y,uint32_t color);

Sprite get_alien_sprite();
Sprite get_ship_sprite();
#endif //UNTITLED4_SPRITE_H