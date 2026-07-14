#ifndef ZEPHYR_DRIVERS_GPIO_H_
#define ZEPHYR_DRIVERS_GPIO_H_

// Ties to the 'compatible = "custom,gpio" node in DeviceTree.
#define DT_DRV_COMPAT custom_test

struct test_config {
    int firstVar;
    int secondVar;
};

int test_func(struct test_config test, uint32_t *output);

int test_print(void);

#endif
