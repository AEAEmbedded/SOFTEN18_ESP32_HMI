if(COMMAND idf_component_register)
    # ---- ESP-IDF build ----
    idf_component_register(
        SRCS "src/eez_export/ui.c"
    "src/eez_export/images.c"
    "src/eez_export/screens.c"
    "src/eez_export/styles.c"
    "src/eez_export/ui_image_cappuccino.c"
    "src/eez_export/ui_image_meme.c"
             "src/ui_main.cpp"
             "src/ui_events_prepare_page.cpp"
             "src/ui_events_selection_page.cpp"
             "src/ui_events_pay_page.cpp"
             "src/fsm_logic.cpp"
        INCLUDE_DIRS "include"  "include/eez_export"
  REQUIRES esp_lcd driver lvgl
    )
endif()
