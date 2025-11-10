# ascii-cli/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(ascii-cli LANGUAGES CXX)

file(GLOB_RECURSE ASCII_CLI_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(ascii-cli ${ASCII_CLI_SOURCES})

target_link_libraries(ascii-cli PRIVATE ascii-lib)

set_target_properties(ascii-cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
