#include <zephyr/kernel.h>
#include <stdio.h>

#define RCC_ADDR            0x40023800UL
#define RCC_AHB1ENR_OFFSET  0x30UL

#define GPIOA_BASE_ADDR     0x40020000UL
#define MODER_OFFSET        0x00UL
#define GPIO_ODR_OFFSET     0x04UL
#define GPIO_PUPDR_OFFSET   0x0CUL
#define GPIO_IDR_OFFSET     0x10UL
#define GPIO_OSPEEDR_OFFSET 0x08UL

int main(void) {

    // First, enable GPIOA through AHB1.
    uint32_t *ahb1_ptr = (uint32_t *) (RCC_ADDR + RCC_AHB1ENR_OFFSET);
    *ahb1_ptr |= 0b1;

    // Set GPIOA pin 0 (PA) pin mode to input.
    uint32_t *moder_ptr = (uint32_t *) (GPIOA_BASE_ADDR + MODER_OFFSET);
    *moder_ptr &= ~(0b11);

    // Clear PA0 bits (set to pull down only).
    uint32_t *pupdr_ptr = (uint32_t *) (GPIOA_BASE_ADDR + GPIO_PUPDR_OFFSET);
    *pupdr_ptr &= ~(0b11);

    // Read PA0 register.
    volatile uint32_t *idr_ptr = (uint32_t *) (GPIOA_BASE_ADDR + GPIO_IDR_OFFSET);

    while(1) {
        if (*idr_ptr & 0b1) {
            printf("Hello, world!\n");
            k_msleep(100);
            while(*idr_ptr & 0b1);
        }

    }
}
