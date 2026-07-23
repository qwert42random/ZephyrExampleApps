#include <zephyr/kernel.h>
#include <stdio.h>

#include "gpio_driver.h"

struct Gpio green = {
    .reg = DT_STRING_TOKEN(DT_PATH(test, green_light), gpio_port),
    .pin = DT_PROP(DT_PATH(test, green_light), pin),
    .pull = DT_STRING_TOKEN(DT_PATH(test, green_light), pull_type),
    .mode = DT_STRING_TOKEN(DT_PATH(test, green_light), output)
};

struct Gpio usr_button = {
    .reg = DT_STRING_TOKEN(DT_PATH(test, button), gpio_port),
    .pin = DT_PROP(DT_PATH(test, button), pin),
    .pull = DT_STRING_TOKEN(DT_PATH(test, button), pull_type),
    .mode = DT_STRING_TOKEN(DT_PATH(test, button), output)
};

int main(void) {
    init_gpio(green);
    init_gpio(usr_button);

    int pin_state = 1;
    write_pin(green, pin_state);

    while(1) {

        if (read_pin(usr_button)) {

            pin_state = !pin_state;
            write_pin(green, pin_state);
            printf("Button pressed\n");

            k_msleep(300);
            while (read_pin(usr_button));
        }
    }

    return 0;
}

