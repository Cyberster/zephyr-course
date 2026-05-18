#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver
#define LED_NODE DT_ALIAS(app_led)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);


static int sample_fetch_my_impl(const struct device *dev,
                                enum sensor_channel chan) {
    LOG_INF("Hello from sample fetch, channel %d", chan);

    if (gpio_pin_set_dt(&led, 1) < 0) return 0;

    return 0;
}

static int channel_get_my_impl(const struct device *dev,
                                enum sensor_channel chan,
                                struct sensor_value *val) {
    LOG_INF("Hello from channel get, channel %d", chan);

    if (gpio_pin_set_dt(&led, 0) < 0) return 0;

    return 0;
}

static DEVICE_API(sensor, api_iomico_lecture) = {
    .sample_fetch = sample_fetch_my_impl,
    .channel_get = channel_get_my_impl
}; 

// Init function
static int init(const struct device *dev) {
    if (IS_ENABLED(CONFIG_GPIO)) {
        LOG_INF("CONFIG_GPIO found\n");
    } else {
        LOG_INF("CONFIG_GPIO not found\n");
    }

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    LOG_INF("Device Initialized!\n");
    return 0;
}

// DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);
#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);

DT_INST_FOREACH_STATUS_OKAY(DEV_INST);