#include "ArduinoPi.h"
#if defined(RPI)

void PInterruptData::attach(function_pointer _func, int _mode)
{

    attached = true;
    func = _func;
    mode = _mode;
}

void PInterruptData::detach()
{
    attached = false;
    func = NULL;
}

bool PInterruptData::isSet()
{
    return (pin > -1);
}

void PInterruptData::check()
{
    if (isSet())
    {
        int readValue = digitalRead(pin);
        trigger(readValue);
    }
}
void PInterruptData::trigger(int readValue)
{

    if (attached && (func != NULL))
    {
        if ((mode == RISING && readValue == 1) ||
            (mode == FALLING && readValue == 0) || (mode == CHANGE))
        {
            func();
        }
    }
}

int PInterrupts::getInitializedIndex(int pin)
{

    for (int n = 0; n < N_PINTERRUPTS; n++)
    {
        if (ints[n].pin == pin)
        {
            return n;
        }
    }
    return -1;
}

int PInterrupts::getIndex(int pin)
{

    for (int n = 0; n < N_PINTERRUPTS; n++)
    {
        if (ints[n].pin == pin || ints[n].pin == -1)
        {
            return n;
        }
    }
    return -1;
}

int PInterrupts::init(int index, int pin)
{
    if (index < 0 || getInitializedIndex(pin) > -1)
    {
        return -1;
    }

    ints[index].pin = pin;
    switch (index)
    {
    case 0:
        wiringPiISR(pin, INT_EDGE_BOTH, &I0);
        break;

    case 1:
        wiringPiISR(pin, INT_EDGE_BOTH, &I1);
        break;
    case 2:
        wiringPiISR(pin, INT_EDGE_BOTH, &I2);

        break;
    case 3:
        wiringPiISR(pin, INT_EDGE_BOTH, &I3);
        break;
    case 4:
        wiringPiISR(pin, INT_EDGE_BOTH, &I5);
        break;
    case 5:
        wiringPiISR(pin, INT_EDGE_BOTH, &I5);
        break;
    case 6:
        wiringPiISR(pin, INT_EDGE_BOTH, &I6);
        break;
    case 7:
        wiringPiISR(pin, INT_EDGE_BOTH, &I7);
        break;
    case 8:
        wiringPiISR(pin, INT_EDGE_BOTH, &I8);
        break;
    case 9:
        wiringPiISR(pin, INT_EDGE_BOTH, &I9);
        break;

    default:
        return -1;
    }

    return index;
}

void PInterrupts::detach(int pin)
{
    int index = getInitializedIndex(pin);
    if (index > -1)
    {
        ints[index].detach();
    }
}

void PInterrupts::attach(int pin, void (*function)(void), int mode)
{

    int index = getIndex(pin);
    if (index > -1)
    {
        if (!ints[index].isSet())
        {
            init(index, pin);
        }
        ints[index].attach(function, mode);
    }
}

void PInterrupts::checkInterrupt(PInterruptData &i)
{
    if (enabled)
    {
        i.check();
    }
}
void PInterrupts::I0()
{
    checkInterrupt(ints[0]);
}
void PInterrupts::I1()
{
    checkInterrupt(ints[1]);
}
void PInterrupts::I2()
{
    checkInterrupt(ints[2]);
}
void PInterrupts::I3()
{
    checkInterrupt(ints[3]);
}
void PInterrupts::I4()
{
    checkInterrupt(ints[4]);
}
void PInterrupts::I5()
{
    checkInterrupt(ints[5]);
}
void PInterrupts::I6()
{
    checkInterrupt(ints[6]);
}
void PInterrupts::I7()
{
    checkInterrupt(ints[7]);
}
void PInterrupts::I8()
{
    checkInterrupt(ints[8]);
}
void PInterrupts::I9()
{
    checkInterrupt(ints[9]);
}
bool PInterrupts::enabled = true;
PInterruptData PInterrupts::ints[N_PINTERRUPTS];

void interrupts()
{
    PInterrupts::enabled = true;
    // piHiPri(99);
}

void noInterrupts()
{
    PInterrupts::enabled = true;
    // piHiPri(0);
}

void detachInterrupt(int pin)
{
    PInterrupts::detach(pin);
}
void attachInterrupt(int pin, void (*function)(void), int mode)
{
    PInterrupts::attach(pin, function, mode);
}

void doLoop(function_pointer func)
{
  while (1)
  {
    func();
  }
}
#endif