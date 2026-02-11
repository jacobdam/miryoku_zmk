if ((NOT CONFIG_ZMK_SPLIT) OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  target_sources_ifdef(CONFIG_ZMK_BEHAVIOR_CLIPBOARD_ACTION app PRIVATE src/behavior_clipboard_action.c)
  target_sources_ifdef(CONFIG_ZMK_BEHAVIOR_CLIPBOARD_TOGGLE app PRIVATE src/behavior_clipboard_toggle.c)
  target_sources_ifdef(CONFIG_ZMK_BEHAVIOR_CLIPBOARD_TOGGLE app PRIVATE src/clipboard_state_changed.c)
endif()

if (CONFIG_ZMK_DISPLAY)
  target_sources_ifdef(CONFIG_ZMK_WIDGET_CLIPBOARD_STATUS app PRIVATE src/widgets/clipboard_status.c)
  target_sources_ifdef(CONFIG_ZMK_WIDGET_CLIPBOARD_STATUS app PRIVATE src/widgets/custom_status_screen.c)
endif()

zephyr_include_directories(include)
