//
// Created by vladi on 9/25/2026.
//
#include <GLFW/glfw3.h>
#include <cstdint>
#include "buffer.h"

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b) {
    return (r<<24)|(g<<16)|(b<<8)|255;
}
void buffer_clear(Buffer *buf,uint32_t color) {
    for (uint32_t i=0; i<buf->width*buf->height; i++) {
        buf->data[i]=color;
    }
}

Buffer buffer_init() {
    uint32_t clear_color = rgb_to_uint32(0,255,0);
    Buffer buf;
    buf.width=640;
    buf.height=480;
    buf.data=new uint32_t[buf.width*buf.height];
    buffer_clear(&buf,clear_color);
    return buf;
}
