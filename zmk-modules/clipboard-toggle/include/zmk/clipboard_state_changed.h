// SPDX-License-Identifier: MIT

#pragma once

#include <zmk/event_manager.h>
#include <zmk_clipboard_state.h>

struct zmk_clipboard_state_changed {
    enum clipboard_mode state;
};

ZMK_EVENT_DECLARE(zmk_clipboard_state_changed);
