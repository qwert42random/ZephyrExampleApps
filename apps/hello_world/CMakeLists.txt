cmake_minimum_required(VERSION 3.22)
set(BOARD stm32f4_disco)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE src/main.c)

