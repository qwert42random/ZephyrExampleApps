#include <stdint.h>

#define RCC_BASE_ADDR(OFFSET)       *((uint32_t *) (0x40023800 + OFFSET))

#define AHB1ENR_OFFSET              0x30UL

#define GPIO_BASE_ADDR              0x40020000

#define MODER_OFFSET                0x00UL
#define ODR_OFFSET                  0x14UL
#define PUPDR_OFFSET                0x0CUL
#define IDR_OFFSET                  0x10UL
#define OSPEEDR_OFFSET              0x08UL

enum PinMode {
    input = 0b00,
    output = 0b01
};

enum OutputType {
    push_pull = 0b0,
    open_drain = 0b1
};

enum Pull {
    none = 0b00,
    pull_up = 0b01,
    pull_down = 0b10
};

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
};

struct Gpio {
    enum GpioReg reg;
    int pin;
    enum Pull pull;

    enum PinMode mode;
    enum OutputType output;
};

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


    } else {
        return -1;
    }

    return 0;
}

int read_pin(struct Gpio gpio) {
    return 0;
}

int write_pin(struct Gpio gpio, int state) {
    // TODO: Check if pin is output mode.

    // Write to ODR.
    *((uint32_t *) (gpio.reg + ODR_OFFSET)) |= (state ? 0b1 : 0b0) << gpio.pin;

    return 0;
}

#define GPIOD_BASE_ADDR         0x40020C00UL    // Address for setting GPIO D.
#define RCC_AHB1ENR_ADDR        0x40023830UL    // Address for AHB1 Bus settings.

int main1(void) {

    enable_gpio(D);
    // uint32_t *AHB1_ptr = (uint32_t *) RCC_AHB1ENR_ADDR;
    // *AHB1_ptr |= 0b1000;

	// Set all pins to push-pull.
	uint32_t *moder_ptr = (uint32_t*) (GPIOD_BASE_ADDR + MODER_OFFSET);
	*moder_ptr |= (0b01010101) << 24;

	// Set bits in ODR (Output address register).
	uint32_t *odr_ptr = (uint32_t*) (GPIOD_BASE_ADDR + ODR_OFFSET);
	*odr_ptr |= 0b1 << 12;	// Turn on green LED.
	*odr_ptr |= 0b1 << 13;	// Turn on orange LED.
	*odr_ptr |= 0b1 << 14;	// Turn on red LED.
	*odr_ptr |= 0b1 << 15;	// Turn on blue LED.

    for (;;) { };


    return 0;
}

int main(void) {

    struct Gpio gpio_d = {
        .reg = D,
        .pin = 13,
        .pull = pull_down,

        .mode = output,
        .output = 0
    };

    init_gpio(gpio_d);
    write_pin(gpio_d, 1);

    return 0;
}
