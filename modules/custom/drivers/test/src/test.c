#include <stdint.h>
#include <stdio.h>

#include "test.h"

#ifdef CONFIG_ALT_TEST_FUNC
int test_func(struct test_config config) {
    return config.firstVar * config.secondVar;
}
#else
int test_func(struct test_config config) {
    return config.firstVar + config.secondVar;
}
#endif

#ifdef CONFIG_ALT_PRINT_FUNC
int test_print(void) {
    printf("Alternative print statement\n");
    return 72;
}
#else
int test_print(void) {
    printf("Original print statement\n");
    return 69;
}
#endif

