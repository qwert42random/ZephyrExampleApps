#include <zephyr/kernel.h>
#include <zephyr/app_version.h>
#include <stdio.h>

#include "test.h"
#include "gpio.h"

// Get values for struct from device tree.
struct test_config first_test_config = EXAMPLE_DT_GET_TEST_BY_IDX(test1);
struct test_config second_test_config = EXAMPLE_DT_GET_TEST_BY_IDX(test2);

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
            test_print();

            pin_state = !pin_state;
            write_pin(green, pin_state);

            // APP_VERSION_EXTENDED_STRING is a macro provided by Zephyr.
            // It is the extended string version format as read in VERSION file.
            printf("Version number: %s\n", APP_VERSION_EXTENDED_STRING);

            printf("First test config: %d\n", test_func(first_test_config));
            printf("Second test config: %d\n", test_func(second_test_config));

            if (DT_HAS_COMPAT_STATUS_OKAY(custom_compatible)) {
                printf("custom,compatible in device tree\n");
            }

            k_msleep(300);
            while (read_pin(usr_button));
        }
    }

    return 0;
}

