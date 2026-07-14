#include <zephyr/kernel.h>
#include <stdio.h>

#include "test.h"

int main(void) {
    while(1) {
        int ret = test_print();
        printf("Return value: %d\n", ret);
        k_msleep(1000);
    }
}
