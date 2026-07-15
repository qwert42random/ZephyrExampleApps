#ifndef ZEPHYR_DRIVERS_TEST_H_
#define ZEPHYR_DRIVERS_TEST_H_

// Ties to the 'compatible = "custom,test" node in DeviceTree.
#define DT_DRV_COMPAT custom_test

#define EXAMPLE_DT_GET_TEST_BY_IDX(node_id)                      \
    {                                                            \
        .firstVar = DT_PROP(DT_NODELABEL(node_id), first_var),   \
        .secondVar = DT_PROP(DT_NODELABEL(node_id), second_var), \
    }                                                            \

struct test_config {
    int firstVar;
    int secondVar;
};

int test_func(struct test_config test);

int test_print(void);

#endif
