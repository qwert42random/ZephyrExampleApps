// Ties to the 'compatible = "custom,test"' node in the Device tree.
#define DT_DRV_COMPAT custom_test

#include <stdint.h>
#include <stdio.h>

#include "test.h"

int test_func(struct test_config config, uint32_t *output) {
    *output = config.firstVar + config.secondVar;
    return 0;
}

int test_print(void) {
    printf("My name is Ozymandias, king of kings: Look on my works, ye Mighty, and despair!\n");
    return 69;
}

