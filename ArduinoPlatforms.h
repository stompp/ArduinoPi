#ifndef _ARDUINOPLATFORMS_H_
#define _ARDUINOPLATFORMS_H_

#ifdef ARDUINO
#include <Arduino.h>
#elif defined(RPI)
#include "ArduinoPi.h"
#endif

#endif // _ARDUINOPLATFORMS_H_