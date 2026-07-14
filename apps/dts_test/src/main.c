#include <zephyr/kernel.h>
#include <stdio.h>

#include "test.h"

int main(void) {
    while(1) {
        int ret = test_print();
        printf("Return value: %d\n", ret);

#if DT_HAS_COMPAT_STATUS_OKAY(custom_compatible)
        printf("Hello there, world\n");
#endif

        k_msleep(1000);
    }
}
