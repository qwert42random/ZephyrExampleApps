#include <stdint.h>
#include <stdio.h>

#include "test.h"

void test_func(struct test_config config) {
    printf("First variable: %d\n", config.firstVar);
    printf("Second variable: %d\n", config.secondVar);
    return;
}

void test_print(void) {
    printf("Hello world\n");
    return;
}

