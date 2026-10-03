//
// Created by vladi on 10/3/2026.
//
#include "../h/SpriteAnimation.h"

#include <vector>
SpriteAnimation* create_sprite_animation(std::vector<Sprite> frames, bool loop, size_t frame_duration) {
    SpriteAnimation* animation = new SpriteAnimation;

    animation->loop = loop;
    animation->num_frames = frames.size();
    animation->frame_durration = frame_duration;
    animation->time = 0;

    animation->frames = new Sprite*[frames.size()];
    for (size_t i = 0; i < frames.size(); ++i) {
        animation->frames[i] = new Sprite(frames[i]);
    }

    return animation;
}
