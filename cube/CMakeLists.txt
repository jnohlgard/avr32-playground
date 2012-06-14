cmake_minimum_required(VERSION "2.6")
project(avr32cube3d CXX C ASM)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${AVR32_USER_BOARD_DIR})

add_subdirectory("src")
