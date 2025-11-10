idf_component_register(
    SRCS "main.cpp"
         "display_driver/display_driver.c"
         "touch_driver/touch_driver.c"
    INCLUDE_DIRS "."
    REQUIRES esp_lcd driver
)
