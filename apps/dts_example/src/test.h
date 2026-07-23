#ifndef TEST_H
#define TEST_H

#define EXAMPLE_DT_GET_TEST_BY_IDX(node_id)                      \
    {                                                            \
        .firstVar = DT_PROP(DT_NODELABEL(node_id), first_var),   \
        .secondVar = DT_PROP(DT_NODELABEL(node_id), second_var), \
    }                                                            \

struct test_config {
    int firstVar;
    int secondVar;
};

void test_func(struct test_config test);

void test_print(void);

#endif
