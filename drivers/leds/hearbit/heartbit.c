#define DT_DRV_COMPAT custom_heartbit

#include <zephyr/drivers/led.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(led_gpio);


struct heartbit_config {
    uint16_t                   on_time;
    uint16_t                   off_time;
    const struct gpio_dt_spec *led;
};

static int heartbit_init(const struct device *dev) {
    const struct heartbit_config *config = dev->config;
    int                           err    = 0;

    if (!config->on_time) {
        LOG_ERR("%s: On time cannot be zero!", dev->name);
        err = -ENODEV;
    }

    if (!config->off_time) {
        LOG_ERR("%s: Off time cannot be zero!", dev->name);
        err = -ENODEV;
    }

    LOG_INF("%s: Initialized!", dev->name);

    return err;
}

static int heartbit_api_on(const struct device *dev, uint32_t led) {
    (void)dev;
    (void)led;
    return 0;
}

static int heartbit_api_off(const struct device *dev, uint32_t led) {
    (void)dev;
    (void)led;
    return 0;
}

static DEVICE_API(led, api_funcs) = {
    .on  = heartbit_api_on,
    .off = heartbit_api_off,
};

#define HEARTBIT_DEFINE(inst)                                                                                          \
    static const struct gpio_dt_spec gpio_dt_spec_##inst[] = {                                                            \
        DT_INST_FOREACH_CHILD_SEP_VARGS(inst, GPIO_DT_SPEC_GET, (, ), gpios)};                                         \
    static const struct heartbit_config config_##inst = {                                                              \
        /* initialize ROM values as needed. */                                                                         \
        .on_time  = DT_INST_PROP(inst, on_time),                                                                       \
        .off_time = DT_INST_PROP(inst, off_time),                                                                      \
        .led      = gpio_dt_spec_##inst,                                                                               \
    };                                                                                                                 \
    DEVICE_DT_INST_DEFINE(inst, &heartbit_init, NULL, NULL, &config_##inst, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY, &api_funcs);

DT_INST_FOREACH_STATUS_OKAY(HEARTBIT_DEFINE);
