#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include "GPIO.hh"

#define MEM_FD "/dev/mem"
#define GPIO_BASE_ADDRESS 0x3F200000
#define MAP_SIZE 4096

RPi3BP_GPIO::RPi3BP_GPIO()
{
    std::cout << "Default constructor has been called" << std::endl;
    perror("Please use the paramaterized constructor");
    pinDirection = GPIO_DIR_NODIR;
    pinNumber = GPIO_PIN_NOPIN;
    initialState = GPIO_PINSTATE_NOSTATE;
}

RPi3BP_GPIO::RPi3BP_GPIO(uint8_t pinNumber, uint8_t pinDirection, uint8_t initialState) : pinNumber(pinNumber), pinDirection(pinDirection), initialState(initialState)
{
    if ((mem_fd = open(MEM_FD, O_RDWR | O_SYNC)) < 0)
    {
        perror("Failed to open /dev/mem");
    }

    // Map GPIO registers
    peripheral_base = mmap(
        NULL,
        MAP_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        GPIO_BASE_ADDRESS);

    if (peripheral_base == MAP_FAILED)
    {
        perror("mmap failed");
        close(mem_fd);
    }

    BCM2837_GPIO_REGISTERS = (BCM2837_strGPIO_REGISTERS_t *)peripheral_base;

    if (pinNumber > GPIO_PIN_27)
    {
        perror("Invalid pin number");
    }
    else if (pinDirection > GPIO_DIR_OUTPUT)
    {
        perror("Invalid pin direction");
    }
    else if (initialState > GPIO_PINSTATE_HIGH)
    {
        perror("Invalid pin state");
    }
    else
    {
        uint8_t gpfsel_reg_index = pinNumber / 10;
        volatile uint32_t *gpfsel_reg = &BCM2837_GPIO_REGISTERS->GPFSEL0 + gpfsel_reg_index;
        if (pinDirection == GPIO_DIR_INPUT)
        {
            CLEAR_PIN_DIR(*gpfsel_reg, pinNumber);
            SET_PIN_DIR_INPUT(*gpfsel_reg, pinNumber);
        }
        else if (pinDirection == GPIO_DIR_OUTPUT)
        {
            CLEAR_PIN_DIR(*gpfsel_reg, pinNumber);
            SET_PIN_DIR_OUTPUT(*gpfsel_reg, pinNumber);
        }

        if (initialState == GPIO_PINSTATE_LOW)
        {
            CLEAR_PIN(BCM2837_GPIO_REGISTERS->GPCLR0, pinNumber);
        }
        else if (initialState == GPIO_PINSTATE_HIGH)
        {
            SET_PIN(BCM2837_GPIO_REGISTERS->GPSET0, pinNumber);
        }
    }
}

void RPi3BP_GPIO::initGPIO(uint8_t pinNumber, uint8_t pinDirection, uint8_t initialState)
{
    this->pinNumber = pinNumber;
    this->pinDirection = pinDirection;
    this->initialState = initialState;

    if (pinNumber > GPIO_PIN_27)
    {
        perror("Invalid pin number");
    }
    else if (pinDirection > GPIO_DIR_OUTPUT)
    {
        perror("Invalid pin direction");
    }
    else if (initialState > GPIO_PINSTATE_HIGH)
    {
        perror("Invalid pin state");
    }
    else
    {
        uint8_t gpfsel_reg_index = pinNumber / 10;
        volatile uint32_t *gpfsel_reg = &BCM2837_GPIO_REGISTERS->GPFSEL0 + gpfsel_reg_index;
        if (pinDirection == GPIO_DIR_INPUT)
        {
            CLEAR_PIN_DIR(*gpfsel_reg, pinNumber);
            SET_PIN_DIR_INPUT(*gpfsel_reg, pinNumber);
        }
        else if (pinDirection == GPIO_DIR_OUTPUT)
        {
            CLEAR_PIN_DIR(*gpfsel_reg, pinNumber);
            SET_PIN_DIR_OUTPUT(*gpfsel_reg, pinNumber);
        }

        if (initialState == GPIO_PINSTATE_LOW)
        {
            CLEAR_PIN(BCM2837_GPIO_REGISTERS->GPCLR0, pinNumber);
        }
        else if (initialState == GPIO_PINSTATE_HIGH)
        {
            SET_PIN(BCM2837_GPIO_REGISTERS->GPSET0, pinNumber);
        }
    }
}

void RPi3BP_GPIO::setPinHigh()
{
    SET_PIN(BCM2837_GPIO_REGISTERS->GPSET0, pinNumber);
}

void RPi3BP_GPIO::setPinLow()
{
    CLEAR_PIN(BCM2837_GPIO_REGISTERS->GPCLR0, pinNumber);
}

void RPi3BP_GPIO::readPin(uint8_t *state)
{
    *state = READ_PIN(BCM2837_GPIO_REGISTERS->GPLEV0, pinNumber);
}

void RPi3BP_GPIO::setPinPullUp()
{
    BCM2837_GPIO_REGISTERS->GPPUD = GPIO_PULLTYPE_PULLUP;
    usleep(150);
    SET_BIT(BCM2837_GPIO_REGISTERS->GPPUDCLK0, pinNumber);
    usleep(150);
    BCM2837_GPIO_REGISTERS->GPPUD = 0;
    BCM2837_GPIO_REGISTERS->GPPUDCLK0 = 0;
}

void RPi3BP_GPIO::setPinPullDown()
{
    BCM2837_GPIO_REGISTERS->GPPUD = GPIO_PULLTYPE_PULLDOWN;
    usleep(150);
    SET_BIT(BCM2837_GPIO_REGISTERS->GPPUDCLK0, pinNumber);
    usleep(150);
    BCM2837_GPIO_REGISTERS->GPPUD = 0;
    BCM2837_GPIO_REGISTERS->GPPUDCLK0 = 0;
}

RPi3BP_GPIO::~RPi3BP_GPIO()
{
    if (peripheral_base != MAP_FAILED)
    {
        std::cout << "Destructor has been called" << std::endl;
    }
    if (mem_fd >= 0)
    {
        close(mem_fd);
    }
    std::cout << "Destructor has been called" << std::endl;
}