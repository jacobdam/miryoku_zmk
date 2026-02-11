// SPDX-License-Identifier: MIT

#define DT_DRV_COMPAT zmk_behavior_clipboard_action

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/behavior.h>
#include <zmk/events/keycode_state_changed.h>

#include <zmk_clipboard_state.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

struct behavior_clipboard_action_config {
    uint32_t mac_keycode;
    uint32_t win_keycode;
};

struct behavior_clipboard_action_data {
    uint32_t active_keycode;
};

static int on_clipboard_action_binding_pressed(struct zmk_behavior_binding *binding,
                                               struct zmk_behavior_binding_event event) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct behavior_clipboard_action_config *cfg = dev->config;
    struct behavior_clipboard_action_data *data = dev->data;

    uint32_t keycode;
    if (zmk_clipboard_current_mode == CLIPBOARD_MODE_MAC) {
        keycode = cfg->mac_keycode;
    } else {
        keycode = cfg->win_keycode;
    }

    data->active_keycode = keycode;

    LOG_DBG("clipboard action pressed: mode=%d keycode=0x%08x", zmk_clipboard_current_mode,
            keycode);

    return raise_zmk_keycode_state_changed_from_encoded(keycode, true, event.timestamp);
}

static int on_clipboard_action_binding_released(struct zmk_behavior_binding *binding,
                                                struct zmk_behavior_binding_event event) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    struct behavior_clipboard_action_data *data = dev->data;

    uint32_t keycode = data->active_keycode;

    LOG_DBG("clipboard action released: keycode=0x%08x", keycode);

    return raise_zmk_keycode_state_changed_from_encoded(keycode, false, event.timestamp);
}

static const struct behavior_driver_api clipboard_action_driver_api = {
    .binding_pressed = on_clipboard_action_binding_pressed,
    .binding_released = on_clipboard_action_binding_released,
};

#define CBA_INST(n)                                                                                \
    static struct behavior_clipboard_action_data cba_data_##n = {};                                \
    static const struct behavior_clipboard_action_config cba_config_##n = {                        \
        .mac_keycode = DT_INST_PROP(n, mac_keycode),                                               \
        .win_keycode = DT_INST_PROP(n, win_keycode),                                               \
    };                                                                                             \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, &cba_data_##n, &cba_config_##n, POST_KERNEL,            \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &clipboard_action_driver_api);

DT_INST_FOREACH_STATUS_OKAY(CBA_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
