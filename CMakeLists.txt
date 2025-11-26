cmake_minimum_required(VERSION 3.15)
project(PixelSort VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(pixelsort
    src/main.cpp
    src/image.cpp
    src/sorter.cpp
)

target_include_directories(pixelsort PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

# Enable warnings
if(MSVC)
    target_compile_options(pixelsort PRIVATE /W4)
else()
    target_compile_options(pixelsort PRIVATE -Wall -Wextra -pedantic)
endif()

# Tests
enable_testing()
add_executable(test_pixelsort
    tests/test_main.cpp
    src/image.cpp
    src/sorter.cpp
)

target_include_directories(test_pixelsort PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

add_test(NAME PixelSortTests COMMAND test_pixelsort)
