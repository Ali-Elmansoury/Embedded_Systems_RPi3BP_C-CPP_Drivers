#include<iostream>
#include <stdlib.h>
#include "LED.hh"

LED::LED()
{
    std::cout << "Default constructor has been called" << std::endl;
    perror("Please use the paramaterized constructor");
    pinNumber = GPIO_PIN_NOPIN;
    initialState = GPIO_PINSTATE_NOSTATE;
}

LED::LED(uint8_t pinNumber, LED_ConnectionType_t ledConnection, uint8_t initialState):RPi3BP_GPIO(pinNumber, OUTPUT, initialState), ledConnection(ledConnection)
{
    if (ledConnection > LED_ConnectionType_Sink)
    {
        perror("Invalid led connection");
    }
}

void LED::initLED(uint8_t pinNumber, LED_ConnectionType_t ledConnection, uint8_t initialState)
{
    this->pinNumber = pinNumber;
    this->ledConnection = ledConnection;
    this->initialState = initialState;

    initGPIO(pinNumber, OUTPUT, initialState);

    if (ledConnection > LED_ConnectionType_Sink)
    {
        perror("Invalid led connection");
    }
}

void LED::turnLedOn()
{
    if (ledConnection == LED_ConnectionType_Source)
    {
        setPinHigh();
    }
    else
    {
        setPinLow();
    }
}

void LED::turnLedOff()
{
    if (ledConnection == LED_ConnectionType_Source)
    {
        setPinLow();
    }
    else
    {
        setPinHigh();
    }
}

LED::~LED()
{
    std::cout << "Destructor has been called" << std::endl;
}