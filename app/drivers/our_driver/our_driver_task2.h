#ifndef OUR_DRIVER_TASK2_H
#define OUR_DRIVER_TASK2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/drivers/gpio.h>

#define LED_NODE DT_ALIAS(app_led)
const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

void toggle_led(uint32_t *counter);

#ifdef __cplusplus
}
#endif

#endif // OUR_DRIVER_TASK2_H