add_executable(DAY3 main.cpp)
target_link_libraries(DAY3 PUBLIC readlines)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
