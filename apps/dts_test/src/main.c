#include <zephyr/kernel.h>
#include <stdio.h>

#include "test.h"

// Get values for struct from device tree.
struct test_config first_test_config = EXAMPLE_DT_GET_TEST_BY_IDX(test1);
struct test_config second_test_config = EXAMPLE_DT_GET_TEST_BY_IDX(test2);

int main(void) {
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
