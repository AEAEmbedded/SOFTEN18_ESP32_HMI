if(COMMAND idf_component_register)
    # ---- ESP-IDF build ----
    idf_component_register(
        SRCS "src/display_driver.c"
			 "src/touch_driver.c"
        INCLUDE_DIRS "include"    
		REQUIRES esp_lcd lvgl driver esp_lvgl_port esp_lcd_touch esp_lcd_touch_gt911
    )
endif()