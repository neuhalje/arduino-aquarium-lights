#include <Adafruit_NeoPixel.h>
#include "debug/Debug.h"
#include "color/Color.h"
#include "color/ColorShift.h"

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN_LED_STRIP 6
#define  PIN_DIAGNOSTIC_LED 13

#define NUM_LEDS  77

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN_LED_STRIP, NEO_GRB + NEO_KHZ800);

void colorSet(uint32_t c);

void fade(const Color from, const Color to, uint32_t how_long_ms);


uint32_t minutes_to_ms(uint32_t minutes) {
    return minutes * 60 * 1000;
}

void setup() {
    pinMode(PIN_DIAGNOSTIC_LED, OUTPUT);

    Serial.begin(9600);

    debug(F("initializing LED Strip\n"));
    strip.begin();
    strip.setBrightness(0xff);

    strip.show();

    Color sunset(0x80, 0x20, 0x20),
            morning(0xa0, 0x5e, 0x50),
            noon(0xff, 0xff, 0xff),
            afternoon(0xa0, 0x5e, 0x50),
            night(0x10, 0x15, 0x20);

    // switch on at 6 (use an external timer for that)
    fade(Color::OFF, sunset, minutes_to_ms(45));

    fade(sunset, morning, minutes_to_ms(30));

    fade(morning, noon, minutes_to_ms(45 + 4 * 60));

    fade(noon, noon, minutes_to_ms(4 * 60));

    fade(noon, afternoon, minutes_to_ms(2 * 60));

    fade(afternoon, sunset, minutes_to_ms(45));

    fade(sunset, night, minutes_to_ms( 30));

    fade(night, Color::OFF, minutes_to_ms(30));

}

void loop() {
    delay(10000);
}

/**
 * Fade the strip starting with color 'from' to color 'to'.
 *
 * The whole transformation takes 'how_long_ms' ms.
 */
void fade(const Color from, const Color to, uint32_t how_long_ms) {

    const uint8_t steps = 0xff;
    const uint32_t wait_per_step = how_long_ms / steps;

    debug(String("fade: ") + String(from.color(), 16) + " -> " + String(to.color(), 16) + "\n");

    for (ColorShift shift(from, to, steps); !shift.done();) {
        const Color &next = shift.next();

        uint32_t color = next.color();

        debug(String("\tnext color: ") + String(color, 16) + "\n");

        colorSet(color);
        delay(wait_per_step);
    }
}


void colorSet(uint32_t c) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
    }
    strip.show();
}

