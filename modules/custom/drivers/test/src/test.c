#include <stdint.h>
#include <stdio.h>

#include "test.h"

int test_func(struct test_config config) {
    return config.firstVar + config.secondVar;
}

int test_print(void) {
    printf("My name is Ozymandias, king of kings: Look on my works, ye Mighty, and despair!\n");
    return 69;
}

