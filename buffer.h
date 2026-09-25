//
// Created by vladi on 9/25/2026.
//

#ifndef UNTITLED4_BUFFER_H
#define UNTITLED4_BUFFER_H
//
// Created by vladi on 9/25/2026.
//
#include <GLFW/glfw3.h>
#include <cstdint>
struct Buffer {
    size_t width,height;
    uint32_t *data;
};

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);
void buffer_clear(Buffer *buf,uint32_t color);
Buffer buffer_init();

#endif //UNTITLED4_BUFFER_H