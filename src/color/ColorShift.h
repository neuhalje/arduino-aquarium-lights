#ifndef AQUARIUM_LIGHTS_COLORSHIFT_H
#define AQUARIUM_LIGHTS_COLORSHIFT_H


#include "Color.h"

class ColorShift {
public:
    /**
     *
     * The first color is 'from'. After calling 'next' for 'steps' times 'to' is reached.
     *
     * @param from:     starting color
     * @param to:       final color
     * @param steps:    how many steps should be used for the transition
     */
    ColorShift(Color from, Color to, uint8_t steps);

    const Color &next();

    bool done();

private:
    Color _current;
    Color _to;
    uint8_t _steps_left;

    // The current values for r,g,b,w  ad the delta per step are stored as 16 bit fixed point floats
    // with the lower 8 bits denoting the fraction, and the higher 8 bits the integer part.

    // deltaX denotes the delta of each step (deltaX * steps) == final color
    // fixed point
    int16_t deltaR, deltaG, deltaB, deltaW;

    // current values for r,g,b,w in fixed point
    uint16_t r,g,b,w;

    bool hasNextBeenCalled;

};


// for testing
int16_t color_step(uint16_t current, uint16_t to, uint8_t steps_left);


#endif //AQUARIUM_LIGHTS_COLORSHIFT_H
