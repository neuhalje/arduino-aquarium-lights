#ifndef AQUARIUM_LIGHTS_DEBUG_H
#define AQUARIUM_LIGHTS_DEBUG_H

#ifndef __AVR__

#define debug( ...)

#else // DEBUG:ON
#include <WString.h>
void debug(const String &str);

void debug(const char *fmt, ...);

void debug(const __FlashStringHelper *fmt, ...);
#endif

#endif
