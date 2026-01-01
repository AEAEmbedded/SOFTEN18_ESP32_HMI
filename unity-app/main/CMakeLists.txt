idf_component_register(SRCS "test_app_main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES unity cmock esp_lcd driver example_ui display_driver
                       )