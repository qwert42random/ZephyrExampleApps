#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include "test.h"

// Get values for struct from device tree.
struct test_config first_test_config = EXAMPLE_DT_GET_TEST_BY_IDX(test1);
struct test_config second_test_config = EXAMPLE_DT_GET_TEST_BY_IDX(test2);

int main(void) {
    while(1) {
        test_func(first_test_config);
        test_func(second_test_config);
        k_msleep(1000);
    }
    return 0;
}

