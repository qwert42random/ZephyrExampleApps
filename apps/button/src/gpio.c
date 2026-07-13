#include <zephyr/kernel.h>

#define RCC_BASE_ADDR(OFFSET)       *((uint32_t *) (0x40023800 + OFFSET))

#define AHB1ENR_OFFSET              0x30UL

#define GPIO_BASE_ADDR              0x40020000

#define MODER_OFFSET                0x00UL
#define ODR_OFFSET                  0x04UL
#define PUPDR_OFFSET                0x0CUL
#define IDR_OFFSET                  0x10UL
#define OSPEEDR_OFFSET              0x08UL

enum PinMode {
    input = 0b00,
    output = 0b01
}

enum OutputType {
    push_pull = 0b0,
    open_drain = 0b1
}

enum Pull {
    none = 0b00,
    pull_up = 0b01,
    pull_down = 0b10
}

enum GpioReg {
    A = 0x40020000,
    B = 0x40020400,
    C = 0x40020800,
    D = 0x40020C00,
    E = 0x40021000,
    F = 0x40021400,
    G = 0x40021800,
    H = 0x40021C00,
    I = 0x40022000,
    J = 0x40022400,
    K = 0x40022800
}

struct Gpio {
    GpioReg reg;
    int pin;
    Pull pull;

    PinMode mode;
    OutputType output;
}

static void enable_gpio(GpioReg gpio) {
    switch(gpio.reg) {
        case A:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 0);
            break;
        case B:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 1);
            break;
        case C:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 2);
            break;
        case D:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 3);
            break;
        case E:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 4);
            break;
        case F:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 5);
            break;
        case G:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 6);
            break;
        case H:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 7);
            break;
        case I:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 8);
            break;
        case J:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 9);
            break;
        case K:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (Ob1 >> 10);
            break;
    }
}

int init_gpio(struct Gpio gpio) {

    // Enable GPIO thorugh AHB1.
    enable_gpio(gpio.reg);

    uint32_t *gpio_base_addr = (uint32_t *) gpio.reg;

    // Set pin to input/output.
    if (gpio.mode == input) {

        // Set mode to input.
        *(gpio_base_addr + MODER_OFFSET) &= ~(0b11);
        *(gpio_base_addr + MODER_OFFSET) |= 0b00;

        // Set pull up/down/none.
        *(gpio_base_addr + PUPDR_OFFSET) &= ~(0b11);
        *(gpio_base_addr + PUPDR_OFFSET) |= gpio.pull;

    } else if (gpio.mode == output) {

        // Set mode to output.
        *(gpio_base_addr + MODER_OFFSET) &= ~(0b00);
        *(gpio_base_addr + MODER_OFFSET) |= 0b01 << gpio.pin;


    } else {
        return -1;
    }

    return 0;
}

int read_pin(Gpio gpio) {
}

int write_pin(Gpio gpio, int state) {
    // TODO: Check if pin is output mode.

    // Write to ODR.
    *((uint32_t *) gpio.reg + ODR_OFFSET) = (state ? 0b1 : 0b0) << gpio.pin;
}
