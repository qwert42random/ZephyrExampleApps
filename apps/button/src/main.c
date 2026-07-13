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

    int pin_state = 1;
    write_pin(green, pin_state);

    while(1) {
        if (read_pin(usr_button)) {
            printf("Hello world\n");
            pin_state = !pin_state;
            write_pin(green, pin_state);

            k_msleep(300);
            while (read_pin(usr_button));
        }
    }

    return 0;
}

