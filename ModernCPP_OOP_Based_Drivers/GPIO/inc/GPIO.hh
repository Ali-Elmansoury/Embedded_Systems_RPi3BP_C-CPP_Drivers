#ifndef GPIO_HH
#define GPIO_HH

#include <stdint.h>

typedef enum {
    GPIO_PIN_0 = 0,
    GPIO_PIN_1 = 1,
    GPIO_PIN_2 = 2,
    GPIO_PIN_3 = 3,
    GPIO_PIN_4 = 4,
    GPIO_PIN_5 = 5,
    GPIO_PIN_6 = 6,
    GPIO_PIN_7 = 7,
    GPIO_PIN_8 = 8,
    GPIO_PIN_9 = 9,
    GPIO_PIN_10 = 10,
    GPIO_PIN_11 = 11,
    GPIO_PIN_12 = 12,
    GPIO_PIN_13 = 13,
    GPIO_PIN_14 = 14,
    GPIO_PIN_15 = 15,
    GPIO_PIN_16 = 16,
    GPIO_PIN_17 = 17,
    GPIO_PIN_18 = 18,
    GPIO_PIN_19 = 19,
    GPIO_PIN_20 = 20,
    GPIO_PIN_21 = 21,
    GPIO_PIN_22 = 22,
    GPIO_PIN_23 = 23,
    GPIO_PIN_24 = 24,
    GPIO_PIN_25 = 25,
    GPIO_PIN_26 = 26,
    GPIO_PIN_27 = 27,
    GPIO_PIN_NOPIN = -1
}BCM2837_enuGPIO_PIN_t;

typedef enum {
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT,
    GPIO_DIR_NODIR = -1
}BCM2837_enuGPIO_DIR_t;

typedef enum {
    GPIO_PINSTATE_NOSTATE = -1,
    GPIO_PINSTATE_LOW,
    GPIO_PINSTATE_HIGH
}BCM2837_enuGPIO_PINSTATE_t;

typedef enum {
    GPIO_PULLTYPE_NOPULL,
    GPIO_PULLTYPE_PULLDOWN,
    GPIO_PULLTYPE_PULLUP
}BCM2837_enuGPIO_PULLTYPE_t;

typedef struct {
    volatile uint32_t GPFSEL0;
    volatile uint32_t GPFSEL1;
    volatile uint32_t GPFSEL2;
    volatile uint32_t GPFSEL3;
    volatile uint32_t GPFSEL4;
    volatile uint32_t GPFSEL5;
    volatile uint32_t RESERVED0;
    volatile uint32_t GPSET0;
    volatile uint32_t GPSET1;
    volatile uint32_t RESERVED1;
    volatile uint32_t GPCLR0;
    volatile uint32_t GPCLR1;
    volatile uint32_t RESERVED2;
    volatile uint32_t GPLEV0;
    volatile uint32_t GPLEV1;
    volatile uint32_t RESERVED3;
    volatile uint32_t GPEDS0;
    volatile uint32_t GPEDS1;
    volatile uint32_t RESERVED4;
    volatile uint32_t GPREN0;
    volatile uint32_t GPREN1;
    volatile uint32_t RESERVED5;
    volatile uint32_t GPFEN0;
    volatile uint32_t GPFEN1;
    volatile uint32_t RESERVED6;
    volatile uint32_t GPHEN0;
    volatile uint32_t GPHEN1;
    volatile uint32_t RESERVED7;
    volatile uint32_t GPLEN0;
    volatile uint32_t GPLEN1;
    volatile uint32_t RESERVED8;
    volatile uint32_t GPAREN0;
    volatile uint32_t GPAREN1;
    volatile uint32_t RESERVED9;
    volatile uint32_t GPAFEN0;
    volatile uint32_t GPAFEN1;
    volatile uint32_t RESERVED10;
    volatile uint32_t GPPUD;
    volatile uint32_t GPPUDCLK0;
    volatile uint32_t GPPUDCLK1;
    volatile uint32_t RESERVED11[4];
} BCM2837_strGPIO_REGISTERS_t;

class RPi3BP_GPIO
{
protected:
    uint8_t pinNumber;
    uint8_t initialState;
    
private:
    uint8_t pinDirection;
    uint8_t mem_fd;
    void *peripheral_base;
    BCM2837_strGPIO_REGISTERS_t *BCM2837_GPIO_REGISTERS;

public:
    RPi3BP_GPIO();
    RPi3BP_GPIO(uint8_t pinNumber, uint8_t pinDirection, uint8_t initialState);
    void initGPIO(uint8_t pinNumber, uint8_t pinDirection, uint8_t initialState);
    void setPinHigh();
    void setPinLow();
    void setPinPullUp();
    void setPinPullDown();
    void readPin(uint8_t* state);
    ~RPi3BP_GPIO();
};

#define CLEAR           (~(0b111))
#define OUTPUT          (0b001)
#define INPUT           (0b000)

#define SET_PIN_DIR_OUTPUT(REG,PIN) (REG |= (OUTPUT << ((PIN % 10) * 3)))
#define SET_PIN_DIR_INPUT(REG,PIN) (REG |= (INPUT << ((PIN % 10) * 3)))
#define CLEAR_PIN_DIR(REG,PIN) (REG &= (CLEAR << ((PIN % 10) * 3)))

#define SET_PIN(REG,PIN) (REG = (1 << PIN))
#define CLEAR_PIN(REG,PIN) (REG = (1 << PIN))
#define READ_PIN(REG,PIN) ((REG >> PIN) & 0x1)

#define SET_BIT(REG,PIN) (REG = (1 << PIN))

#endif //GPIO_HH