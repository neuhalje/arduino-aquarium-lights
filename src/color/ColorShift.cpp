#include "ColorShift.h"


#define FIX_POINT_BITS 7

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

ColorShift::ColorShift(Color from, Color to, uint8_t steps) : _current(from), _to(to), _steps_left(steps) {
    hasNextBeenCalled = false;

    r = from.r << FIX_POINT_BITS;
    g = from.g << FIX_POINT_BITS;
    b = from.b << FIX_POINT_BITS;
    w = from.w << FIX_POINT_BITS;

    deltaR = color_step(r, to.r << FIX_POINT_BITS, steps);
    deltaG = color_step(g, to.g << FIX_POINT_BITS, steps);
    deltaB = color_step(b, to.b << FIX_POINT_BITS, steps);
    deltaW = color_step(w, to.w << FIX_POINT_BITS, steps);

    // printf("deltaR := %i  (from: %i (%x) -> %i (%x) in %i steps\n", deltaR, r, r, to.r << FIX_POINT_BITS, to.r << FIX_POINT_BITS, steps);
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

        _current.r = r >> FIX_POINT_BITS;
        _current.g = g >> FIX_POINT_BITS;
        _current.b = b >> FIX_POINT_BITS;
        _current.w = w >> FIX_POINT_BITS;

        return _current;
    }
}
