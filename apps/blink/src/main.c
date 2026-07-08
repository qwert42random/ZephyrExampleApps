#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_PATH(leds, led1), gpios);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void) {

    if (!gpio_is_ready_dt(&led)) {
        return 0;
    }

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) {
        return 0;
    }

    while(1) {
        if (gpio_pin_toggle_dt(&led) < 0) {
            return 0;
        }

        k_msleep(1000);
    }

    return 0;
}

