#ifndef ZEPHYR_DRIVERS_GPIO_H_
#define ZEPHYR_DRIVERS_GPIO_H_

// TODO: Try and figure out why this is necessary.
// Ties to the 'compatible = "custom,gpio" node in DeviceTree.
#define DT_DRV_COMPAT custom_gpio

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

    // TODO: This needs to be implemented.
    enum OutputType output;
};

int init_gpio(struct Gpio gpio);
int read_pin(struct Gpio gpio);
int write_pin(struct Gpio gpio, int state);

#endif
