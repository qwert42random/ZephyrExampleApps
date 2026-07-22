cmake_minimum_required(VERSION 3.22)

set(BOARD stm32f4_disco)

set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/minimal.overlay)
set(ZEPHYR_EXTRA_MODULES "${CMAKE_SOURCE_DIR}/../../modules/custom")

# Finds and loads packages from external project.
# Use the zephyr path.
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(dts_test)

target_sources(app PRIVATE src/main.c)

