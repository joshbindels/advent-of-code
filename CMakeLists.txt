cmake_minimum_required(VERSION 3.1)
project(
    ADVENT_OF_CODE
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(common)
add_subdirectory(aoc2021)
add_subdirectory(aoc2022)

add_custom_target(v ALL)
add_custom_command(
    TARGET v POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_BINARY_DIR}/../compile_commands.json
)
