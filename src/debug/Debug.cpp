#include <HardwareSerial.h>
#include "Debug.h"


void debug(const char *fmt, ...) {
    char buf[128]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt);
#ifdef __AVR__
    vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
#else
    vsnprintf(buf, sizeof(buf), (const char *) fmt, args); // for the rest of the world
#endif
    va_end(args);
    Serial.print(buf);
}

void debug(const String &str) {
    Serial.print(str);
}

void debug(const __FlashStringHelper *fmt, ...) {
    char buf[128]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt);
#ifdef __AVR__
    vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
#else
    vsnprintf(buf, sizeof(buf), (const char *) fmt, args); // for the rest of the world
#endif
    va_end(args);
    Serial.print(buf);
}
