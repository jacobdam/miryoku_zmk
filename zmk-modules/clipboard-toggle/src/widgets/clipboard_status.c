// SPDX-License-Identifier: MIT

#include <zmk/display/widgets/clipboard_status.h>
#include <zmk/clipboard_state_changed.h>
#include <zmk_clipboard_state.h>
#include <zmk/display.h>
#include <zmk/event_manager.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct clipboard_status_state {
    enum clipboard_mode mode;
};

static void clipboard_status_update_cb(struct clipboard_status_state state) {
    struct zmk_widget_clipboard_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
        const char *text = (state.mode == CLIPBOARD_MODE_MAC) ? "MAC" : "WIN";
        lv_label_set_text(widget->obj, text);
    }
}

static struct clipboard_status_state clipboard_status_get_state(const zmk_event_t *eh) {
    return (struct clipboard_status_state){.mode = zmk_clipboard_current_mode};
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_clipboard_status, struct clipboard_status_state,
                            clipboard_status_update_cb, clipboard_status_get_state)

ZMK_SUBSCRIPTION(widget_clipboard_status, zmk_clipboard_state_changed);

int zmk_widget_clipboard_status_init(struct zmk_widget_clipboard_status *widget,
                                     lv_obj_t *parent) {
    widget->obj = lv_label_create(parent);
    lv_label_set_text(widget->obj, "WIN");

    sys_slist_append(&widgets, &widget->node);
    widget_clipboard_status_init();

    return 0;
}

lv_obj_t *zmk_widget_clipboard_status_obj(struct zmk_widget_clipboard_status *widget) {
    return widget->obj;
}
