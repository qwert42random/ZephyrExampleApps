#include <zephyr/kernel.h>
#include <stdio.h>

#include "test.h"
#include "gpio.h"

// Get values for struct from device tree.
struct test_config first_test_config = EXAMPLE_DT_GET_TEST_BY_IDX(test1);
struct test_config second_test_config = EXAMPLE_DT_GET_TEST_BY_IDX(test2);

int main2(void) {
    while(1) {
        int ret = test_print();
        printf("Return value: %d\n", ret);
        printf("test_func (first config): %d\n", test_func(first_test_config));
        printf("test_func (second config): %d\n", test_func(second_test_config));

#if DT_HAS_COMPAT_STATUS_OKAY(custom_compatible)
        printf("Hello there, world\n");
#endif

        k_msleep(1000);
    }
}

struct Gpio green = {
    .reg = D,
    .pin = DT_PROP(DT_PATH(test, green_light), pin),
    .pull = pull_down,

    .mode = output
};

struct Gpio usr_button = {
    .reg = A,
    .pin = DT_PROP(DT_PATH(test, button), pin),
    .pull = pull_down,

    .mode = input
};

int main(void) {

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

