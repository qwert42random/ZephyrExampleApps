#include <zephyr/kernel.h>
#include <stdio.h>

int main(void) {
    while(1) {
        printf("Hello, world!\n");
        k_msleep(1000);
    }
}
