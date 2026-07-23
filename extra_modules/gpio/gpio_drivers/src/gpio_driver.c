// Ties to the 'compatible = "custom,gpio"' node in the Device tree.
#define DT_DRV_COMPAT custom_gpio

#include <stdint.h>

#include "gpio_driver.h"

#define RCC_BASE_ADDR(OFFSET)       *((uint32_t *) (0x40023800 + OFFSET))

#define AHB1ENR_OFFSET              0x30UL

#define GPIO_BASE_ADDR              0x40020000

#define MODER_OFFSET                0x00UL
#define ODR_OFFSET                  0x14UL
#define PUPDR_OFFSET                0x0CUL
#define IDR_OFFSET                  0x10UL
#define OSPEEDR_OFFSET              0x08UL

static void enable_gpio(enum GpioReg gpio) {
    switch(gpio) {
        case A:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 0);
            break;
        case B:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 1);
            break;
        case C:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 2);
            break;
        case D:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 3);
            break;
        case E:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 4);
            break;
        case F:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 5);
            break;
        case G:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 6);
            break;
        case H:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 7);
            break;
        case I:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 8);
            break;
        case J:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 9);
            break;
        case K:
            RCC_BASE_ADDR(AHB1ENR_OFFSET) |= (0b1 << 10);
            break;
    }
}

int init_gpio(struct Gpio gpio) {

    // Enable GPIO thorugh AHB1.
    enable_gpio(gpio.reg);

    uint32_t gpio_base_addr = gpio.reg;

    // Set pin to input/output.
    if (gpio.mode == input) {

        // Set mode to input.
        *((uint32_t *) (gpio_base_addr + MODER_OFFSET)) &= ~(0b11);
        *((uint32_t *) (gpio_base_addr + MODER_OFFSET)) |= 0b00;

        // Set pull up/down/none.
        *((uint32_t *) (gpio_base_addr + PUPDR_OFFSET)) &= ~(0b11);
        *((uint32_t *) (gpio_base_addr + PUPDR_OFFSET)) |= gpio.pull;

    } else if (gpio.mode == output) {

        // Set mode to output.
        *((uint32_t *) (gpio_base_addr + MODER_OFFSET)) &= ~(0b11 << (gpio.pin * 2));
        *((uint32_t *) (gpio_base_addr + MODER_OFFSET)) |= (0b01 << (gpio.pin * 2));

        // Set pull up/down/none.
        *((uint32_t *) (gpio_base_addr + PUPDR_OFFSET)) &= ~(0b11);
        *((uint32_t *) (gpio_base_addr + PUPDR_OFFSET)) |= gpio.pull;

    } else {
        return -1;
    }

    return 0;
}

int read_pin(struct Gpio gpio) {
    volatile uint32_t *idr_addr;

    if (gpio.mode == input) {
        idr_addr = (uint32_t *) (gpio.reg + IDR_OFFSET);
    } else if (gpio.mode == output) {
        idr_addr = (uint32_t *) (gpio.reg + ODR_OFFSET);
    } else {
        return -1;
    }

    return *idr_addr & (0b1 << gpio.pin);
}

int write_pin(struct Gpio gpio, int state) {
    // TODO: Check if pin is output mode?

    // Write to ODR.
    uint32_t *output_reg = (uint32_t *) (gpio.reg + ODR_OFFSET);
    if (state) {
        *output_reg |= (0b1 << gpio.pin);
    } else {
        *output_reg &= ~(0b1 << gpio.pin);
    }

    return 0;
}

