#ifndef LED_HH
#define LED_HH

#include <stdint.h>
#include "GPIO.hh"

typedef enum {
    LED_STATE_NOSTATE = -1,
    LED_STATE_LOW,
    LED_STATE_HIGH
}LED_STATE_t;

typedef enum {
    LED_ConnectionType_Source,
    LED_ConnectionType_Sink
}LED_ConnectionType_t;

class LED : public RPi3BP_GPIO
{
protected:
    LED_ConnectionType_t ledConnection;

public:
    LED();
    LED(uint8_t pinNumber, LED_ConnectionType_t ledConnection, uint8_t initialState);
    void initLED(uint8_t pinNumber, LED_ConnectionType_t ledConnection, uint8_t initialState);
    void turnLedOn();
    void turnLedOff();
    ~LED();
};

#endif //LED_HH