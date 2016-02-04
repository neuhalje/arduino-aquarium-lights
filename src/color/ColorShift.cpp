#include <stdio.h>
#include "ColorShift.h"

/**
 * To fade from color 'current' to 'to' in 'steps': How big do these steps need to be?
 */
int16_t color_step(uint16_t current, uint16_t to, uint8_t steps) {

    if (steps == 0) {
        // division by zero.
        return to - current;
    } else {
        const int16_t delta = to - current;

        int16_t delta_per_step = delta / steps;
        return delta_per_step;
    }
}

ColorShift::ColorShift(Color from, Color to, uint8_t steps) : _current(from),  _to(to), _steps_left(steps) {
    hasNextBeenCalled = false;

    r = from.r << 8;
    g = from.g << 8;
    b = from.b << 8;
    w = from.w << 8;

    deltaR = color_step(r, to.r << 8, steps);
    deltaG = color_step(g, to.g << 8, steps);
    deltaB = color_step(b, to.b << 8, steps);
    deltaW = color_step(w, to.w << 8, steps);
};

bool ColorShift::done() {
    return _steps_left == 0;
}

const Color &ColorShift::next() {

    if (!hasNextBeenCalled) {
        // Calling next for the first time delivers the starting color and does not
        // count towards the "steps"
        hasNextBeenCalled = true;
        return _current;
    } else {
        _steps_left--;
        r += deltaR;
        g += deltaG;
        b += deltaB;
        w += deltaW;

        _current.r = r >> 8;
        _current.g = g >> 8;
        _current.b = b >> 8;
        _current.w = w >> 8;

        return _current;
    }
}
