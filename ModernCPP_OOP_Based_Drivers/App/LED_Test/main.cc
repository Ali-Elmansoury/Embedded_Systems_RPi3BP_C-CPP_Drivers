#include <iostream>
#include <unistd.h>
#include "LED.hh"
#include "GPIO.hh"

int main()
{
    LED led1(GPIO_PIN_17, LED_ConnectionType_Source, GPIO_PINSTATE_LOW);
    RPi3BP_GPIO button1(GPIO_PIN_27, INPUT, GPIO_PINSTATE_LOW);
    while (1)
    {
        button1.setPinPullUp();
        uint8_t pinState = 0;
        button1.readPin(&pinState);
        if (pinState == 0)
        {
            led1.turnLedOn();
        }
        else
        {
            led1.turnLedOff();
        }
    }
    return 0;
}