cmake_minimum_required(VERSION "2.6")
project(myproject CXX C ASM)
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
    pdca
    # etc...
    )
set(ASF_SERVICES
    sysclk
    # etc...
    )
include(atmel-software-framework)
include_directories(${ASF_INCLUDE_DIRS})

add_subdirectory("src")
