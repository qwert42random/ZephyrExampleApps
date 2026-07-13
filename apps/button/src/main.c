#include <stdint.h>

#include "gpio.h"

int main(void) {

    struct Gpio gpio_d = {
        .reg = D,
        .pin = 14,
        .pull = pull_down,

        .mode = output
    };

    init_gpio(gpio_d);
    write_pin(gpio_d, 1);

    return 0;
}

