
add_executable(day7_22 main.cpp)
target_link_libraries(day7_22 PUBLIC readlines)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
