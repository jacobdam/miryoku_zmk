// SPDX-License-Identifier: MIT

#define DT_DRV_COMPAT zmk_behavior_clipboard_toggle

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/behavior.h>
#include <zmk/event_manager.h>

#include <zmk_clipboard_state.h>
#include <zmk/clipboard_state_changed.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

enum clipboard_mode zmk_clipboard_current_mode = CLIPBOARD_MODE_WIN;

static int on_clipboard_toggle_binding_pressed(struct zmk_behavior_binding *binding,
                                               struct zmk_behavior_binding_event event) {
    if (zmk_clipboard_current_mode == CLIPBOARD_MODE_WIN) {
        zmk_clipboard_current_mode = CLIPBOARD_MODE_MAC;
    } else {
        zmk_clipboard_current_mode = CLIPBOARD_MODE_WIN;
    }

    LOG_DBG("clipboard toggle: new mode=%d", zmk_clipboard_current_mode);

    raise_zmk_clipboard_state_changed(
        (struct zmk_clipboard_state_changed){.state = zmk_clipboard_current_mode});

    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_clipboard_toggle_binding_released(struct zmk_behavior_binding *binding,
                                                struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api clipboard_toggle_driver_api = {
    .binding_pressed = on_clipboard_toggle_binding_pressed,
    .binding_released = on_clipboard_toggle_binding_released,
};

#define CBT_INST(n)                                                                                \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL,                                \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &clipboard_toggle_driver_api);

DT_INST_FOREACH_STATUS_OKAY(CBT_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
