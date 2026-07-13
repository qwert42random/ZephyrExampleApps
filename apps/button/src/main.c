#include <stdint.h>

#include "gpio.h"

int main(void) {

    struct Gpio green = {
        .reg = D,
        .pin = 12,
        .pull = pull_down,

        .mode = output
    };

    struct Gpio orange = {
        .reg = D,
        .pin = 13,
        .pull = pull_down,

        .mode = output
    };

    init_gpio(green);
    init_gpio(orange);

    write_pin(green, 1);
    write_pin(orange, 1);

    return 0;
}

