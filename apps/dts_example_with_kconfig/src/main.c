#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include "test.h"

int main(void) {
    while(1) {
        test_print();
        k_msleep(1000);
    }
    return 0;
}

