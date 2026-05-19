// #include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>
#include "../drivers/our_driver/our_driver_task2.h"

// #define SLEEP_TIME_MS 500

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

namespace {
    void turn_on_led() {
        const struct device *driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
        struct sensor_value val;
        auto ret = sensor_sample_fetch(driver);
        LOG_INF("Channel ret: %d\n", ret);
    }

    void turn_off_led() {
        const struct device *driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
        struct sensor_value val;
        auto ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
        LOG_INF("Channel ret: %d\n", ret);
    }
}

/* ############################## SHELL BEGIN ############################## */
static int cmd_version(const struct shell *sh, size_t argc, char **argv) {
    shell_print(sh, "App version: v1.0.0");
    return 0;
}
SHELL_CMD_REGISTER(version, NULL, "Show app version", cmd_version);

static int cmd_handler(const struct shell *sh, size_t argc, char **argv) {
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    // Simple text output
    shell_print(sh, "Hello from the shell!!");

    // Colored/categorized text output
    shell_info(sh, "Information message!");
    shell_warn(sh, "Warning message!");
    shell_error(sh, "Error message!");

    // Formatted output
    shell_fprintf(sh, SHELL_INFO, "Value: %d\n ", 123);

    return 0;
}
SHELL_CMD_REGISTER(test, NULL, "Test command", cmd_handler);

/* salue sub command action */
static int cmd_demo_salute(const struct shell *sh, size_t argc, char **argv) {
    shell_print(sh, "Good Afternoon!");
    return 0;
}

/* parse sub command action */
static int cmd_demo_parse(const struct shell *sh, size_t argc, char **argv) {
    shell_print(sh, "argc: %d", argc);

    for (size_t i = 0; i < argc; i++) {
        shell_print(sh, "\t argv[%d] = %s", i, argv[i]);
    }

    return 0;
}

/* Create subcommand array for demo command */
SHELL_STATIC_SUBCMD_SET_CREATE(sub_demo,
    SHELL_CMD(salute, NULL, "Print salute message.", cmd_demo_salute),
    SHELL_CMD(parse, NULL, "Print all arguments.", cmd_demo_parse),
    SHELL_SUBCMD_SET_END
);

/* Register root command demo with sub commands */
SHELL_CMD_REGISTER(demo, &sub_demo, "Demo commands", NULL);
/* ############################## SHELL END ############################## */

int main(void) {
    uint32_t counter = 0;

    while (1) {
        // turn_on_led();
        // k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        // turn_off_led();
        // k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        // toggle_led(&counter); // calling from our_driver_task2.h interface, implemented in our_driver.c
        
        LOG_INF("counter: %d\n", counter);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }

    return 0;
}
