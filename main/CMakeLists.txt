idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    REQUIRES esp_lcd driver display_driver example_ui
)
