#ifndef _ARDUINOPI_H_
#define _ARDUINOPI_H_

#if defined(RPI)

#include <cstdlib>
#include <string.h>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <cstdint>
#include <limits.h>
#include <wiringPi.h>

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#ifndef PROGMEM
#define PROGMEM
#endif
#ifndef FPSTR
#define FPSTR
#endif
#ifndef ISR_ATTR
#define ISR_ATTR
#endif

// #ifndef constrain
// #define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
// #endif

// #define min(a,b) ((a)<(b)?(a):(b))
// #define max(a,b) ((a)>(b)?(a):(b))
// #define abs(x) ((x)>0?(x):-(x))
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
// #define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
// #define radians(deg) ((deg)*DEG_TO_RAD)
// #define degrees(rad) ((rad)*RAD_TO_DEG)
// #define sq(x) ((x)*(x))

#define lowByte(w) ((uint8_t)((w)&0xff))
#define highByte(w) ((uint8_t)((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef bool boolean;
typedef uint8_t byte;

#define RISING INT_EDGE_RISING
#define FALLING INT_EDGE_FALLING
#define CHANGE INT_EDGE_BOTH

typedef void (*function_pointer)(void);
void doLoop(function_pointer func);
#define N_PINTERRUPTS 10

struct PInterruptData
{
    int pin = -1;
    int mode;
    bool attached = false;
    bool initialized = false;
    function_pointer func = 0;

    void attach(function_pointer _func, int _mode);

    void detach();

    bool isSet();

    void check();
    void trigger(int readValue);
};

class PInterrupts
{
private:
    static int getInitializedIndex(int pin);
    static int getIndex(int pin);

    static int init(int index, int pin);

public:
    static bool enabled;
    static PInterruptData ints[N_PINTERRUPTS];

    static void detach(int pin);

    static void attach(int pin, void (*function)(void), int mode);

    static void checkInterrupt(PInterruptData &i);
    static void I0();
    static void I1();
    static void I2();
    static void I3();
    static void I4();
    static void I5();
    static void I6();
    static void I7();
    static void I8();
    static void I9();
};

void interrupts();

void noInterrupts();

void detachInterrupt(int pin);
void attachInterrupt(int pin, void (*function)(void), int mode);

#endif

#endif // _ARDUINOPI_H_