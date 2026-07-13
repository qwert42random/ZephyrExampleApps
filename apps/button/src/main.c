#include <stdint.h>
#include <zephyr/kernel.h>

#include "gpio.h"

int main(void) {

    struct Gpio green = {
        .reg = D,
        .pin = 12,
        .pull = pull_down,

        .mode = output
    };

    struct Gpio usr_button = {
        .reg = A,
        .pin = 0,
        .pull = pull_down,

        .mode = input
    };

    init_gpio(green);

    init_gpio(usr_button);

    write_pin(green, 1);

    while(1) {
        if (read_pin(usr_button)) {
            printf("Hello world\n");
            k_msleep(100);
            while (read_pin(usr_button));
        }
    }

    return 0;
}

