#pragma once

#include <cstdint>

struct rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
    rgb(uint8_t v=0) { r = g = b = v; }
};
