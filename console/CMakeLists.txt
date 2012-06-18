cmake_minimum_required(VERSION "2.6")
project(myproject CXX C ASM)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${AVR32_USER_BOARD_DIR})
get_filename_component(AVR32_CMAKE_DIR "${CMAKE_SOURCE_DIR}/../cmake" ABSOLUTE)
LIST(APPEND CMAKE_MODULE_PATH ${AVR32_CMAKE_DIR})

#~ add_definitions("-nostdlib")

set(ASF_PLATFORM avr32)
set(ASF_CPU uc3b0_b1)
set(ASF_DRIVERS
    gpio
    intc
    spi
    flashc
    cycle_counter
    usart
    tc
    # etc...
    )
set(ASF_SERVICES
    sysclk
    # etc...
    )
include(atmel-software-framework)
include_directories(${ASF_INCLUDE_DIRS})

add_subdirectory("src")
