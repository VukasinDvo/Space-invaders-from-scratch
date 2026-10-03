//
// Created by vladi on 10/3/2026.
//

#ifndef UNTITLED4_SPRITEANIMATION_H
#define UNTITLED4_SPRITEANIMATION_H
#include <cstdint>
#include <vector>

#include "sprite.h"

struct SpriteAnimation {
    bool loop;
    size_t num_frames;
    size_t frame_durration;
    size_t time;
    Sprite** frames;

};
SpriteAnimation* create_sprite_animation(std::vector<Sprite> frames, bool loop, size_t frame_duration);

#endif //UNTITLED4_SPRITEANIMATION_H