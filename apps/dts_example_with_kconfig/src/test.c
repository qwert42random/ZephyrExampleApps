#include <stdint.h>
#include <stdio.h>

#include "test.h"

void test_func(struct test_config config) {
    printf("First variable: %d\n", config.firstVar);
    printf("Second variable: %d\n", config.secondVar);
    return;
}

#ifdef CONFIG_ALT_TEST_FUNC
void test_print(void) {
    printf("Hello world\n");
    return;
}
#else
void test_print(void) {
    printf("Goodbye world\n");
    return;
}
#endif

