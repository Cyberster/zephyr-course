#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

// #define SLEEP_TIME_MS 500

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(app_led)
// #define LED_NODE DT_NODELABEL(blue_led)
// #define LED_NODE DT_PATH(leds, blue_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    if (IS_ENABLED(CONFIG_GPIO)) {
        LOG_INF("CONFIG_GPIO found\n");
    } else {
        LOG_INF("CONFIG_GPIO not found\n");
    }

    bool led_state = true;

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
