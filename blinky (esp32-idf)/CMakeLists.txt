# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(blinky)

#
# After adding new animations here, add them also 
# in two places in animations.cpp
#
target_add_binary_data(blinky.elf "../hexels/_exchange.bytes" BINARY)
target_add_binary_data(blinky.elf "../hexels/bouncyheart2.bytes" BINARY)
target_add_binary_data(blinky.elf "../hexels/man.bytes" BINARY)
target_add_binary_data(blinky.elf "../hexels/pong.bytes" BINARY)
