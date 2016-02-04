#include "Color.h"

Color::Color(uint32_t color) : r((color >> 16) & 0xff), g((color >> 8) & 0xff), b(color & 0xff),
                               w((color >> 24) & 0xff) { };

Color::Color(uint8_t inr, uint8_t ing, uint8_t inb) : r(inr), g(ing), b(inb), w(0xff) {
}

Color::Color(uint8_t inr, uint8_t ing, uint8_t inb, uint8_t inw) : r(inr), g(ing), b(inb), w(inw) {
}

uint32_t Color::color() const {
    return ((uint32_t) w << 24) | ((uint32_t) r << 16) | ((uint32_t) g << 8) | b;
}


const Color Color::OFF = Color(0x00, 0x00, 0x00, 0x00),
        Color::WHITE = Color(0xff, 0xff, 0xff),
        Color::DARK_RED = Color(0x40, 0, 0),
        Color::RED = Color(0x80, 0, 0),
        Color::BRIGHT_RED = Color(0xff, 0, 0),
        Color::DARK_GREEN = Color(0, 0x40, 0),
        Color::GREEN = Color(0, 0x80, 0),
        Color::BRIGHT_GREEN = Color(0, 0xff, 0),
        Color::DARK_BLUE = Color(0, 0, 0x40),
        Color::BLUE = Color(0, 0, 0x80),
        Color::BRIGHT_BLUE = Color(0, 0, 0xff);


