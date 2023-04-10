#ifndef _ARDUINOPLATFORMS_H_
#define _ARDUINOPLATFORMS_H_

#ifdef ARDUINO
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#if defined(ESP8266) || defined(ESP32)
// interrupt handlers and related code must be in RAM
// ICACHE_RAM_ATTR is deprecated
#define ISR_ATTR IRAM_ATTR
#else
#define ISR_ATTR
#endif
#endif

#elif defined(RPI)
#include "ArduinoPi.h"
#endif

#endif // _ARDUINOPLATFORMS_H_