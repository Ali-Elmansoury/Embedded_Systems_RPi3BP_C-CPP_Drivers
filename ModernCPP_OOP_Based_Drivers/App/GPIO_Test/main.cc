/*#include <iostream>
#include <unistd.h>
#include "GPIO.hh"

int main()
{
    RPi3BP_GPIO gpio17(GPIO_PIN_17, OUTPUT, GPIO_PINSTATE_LOW);
    RPi3BP_GPIO gpio27(GPIO_PIN_27, INPUT, GPIO_PINSTATE_LOW);

    while (1)
    {
        gpio27.setPinPullUp();
        uint8_t pinState = 0;
        gpio27.readPin(&pinState);
        if (pinState == 0)
        {
            gpio17.setPinHigh();
        }
        
        // usleep(1000000);
        // gpio17.setPinLow();
        // usleep(1000000);
    }
    return 0;
}*/

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include "GPIO.hh"

std::atomic<bool> keepRunning(true);

void gpioHandler()
{
    RPi3BP_GPIO gpio17(GPIO_PIN_17, OUTPUT, GPIO_PINSTATE_LOW);
    RPi3BP_GPIO gpio27(GPIO_PIN_27, INPUT, GPIO_PINSTATE_LOW);

    while (keepRunning)
    {
        gpio27.setPinPullUp();
        uint8_t pinState = 0;
        gpio27.readPin(&pinState);

        if (pinState == 0)
        {
            gpio17.setPinHigh();
        }
        else
        {
            gpio17.setPinLow();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    std::thread gpioThread(gpioHandler);

    std::cout << "Press Enter to stop..." << std::endl;
    std::cin.get();  // Wait for user input

    keepRunning = false;
    gpioThread.join();  // Wait for the thread to finish

    return 0;
}
