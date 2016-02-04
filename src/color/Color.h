#ifndef AQUARIUM_BRIGHTS_COLOR_H
#define AQUARIUM_BRIGHTS_COLOR_H


#include <stdint.h>

class Color {
public:
    Color(uint32_t color);

    Color(uint8_t r, uint8_t g, uint8_t b);

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

    Color(const Color &other) : r(other.r), g(other.g), b(other.b), w(other.w) { };

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t w;

    uint32_t color() const;

    static const Color OFF,
            WHITE,
            DARK_RED,
            RED,
            BRIGHT_RED,
            DARK_GREEN,
            GREEN,
            BRIGHT_GREEN,
            DARK_BLUE,
            BLUE,
            BRIGHT_BLUE;
};

#endif
