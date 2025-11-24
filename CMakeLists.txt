cmake_minimum_required(VERSION 3.21.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(pi_pico)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

FILE(GLOB app_sources ${SOURCE_DIR}/*.c )

target_include_directories(app PRIVATE ${SOURCE_DIR})
target_sources(app PRIVATE ${app_sources})

add_subdirectory(drivers/leds/hearbit)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=gnu2x")

zephyr_library_include_directories(.)
