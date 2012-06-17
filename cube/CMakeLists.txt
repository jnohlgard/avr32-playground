cmake_minimum_required(VERSION "2.6")
project(avr32cube3d CXX C ASM)
get_filename_component(AVR32_CMAKE_DIR "${CMAKE_SOURCE_DIR}/../cmake" ABSOLUTE)
LIST(APPEND CMAKE_MODULE_PATH ${AVR32_CMAKE_DIR})
#~ message(STATUS ${AVR32_CMAKE_DIR})
#~ message(STATUS "${CMAKE_MODULE_PATH}")
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${AVR32_USER_BOARD_DIR})

set(ASF_PLATFORM avr32)
set(ASF_CPU uc3b0_b1)
set(ASF_DRIVERS
    gpio
    intc
    spi
    flashc
    cycle_counter
    )
set(ASF_SERVICES sysclk)
include(atmel-software-framework)
include_directories(${ASF_INCLUDE_DIRS})

add_subdirectory("src")
