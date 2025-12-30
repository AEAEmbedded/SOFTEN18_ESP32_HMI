# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set(IDF_TARGET esp32s3)
set(CMAKE_CXX_STANDARD 17)
set(EXTRA_COMPONENTS example_ui)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(SOFTEN18_ESP32_HMI)


