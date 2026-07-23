cmake_minimum_required(VERSION 3.22)
set(BOARD stm32f4_disco)

set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/example.overlay)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(dts_no_modules)

target_sources(app PRIVATE src/main.c src/test.c src/test.h)
