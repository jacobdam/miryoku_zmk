// SPDX-License-Identifier: MIT

#pragma once

enum clipboard_mode {
    CLIPBOARD_MODE_WIN = 0,
    CLIPBOARD_MODE_MAC = 1,
};

extern enum clipboard_mode zmk_clipboard_current_mode;
