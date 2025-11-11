file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

if(NOT TEST_SOURCES)
    message(FATAL_ERROR "No test source files found in ${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# Create executable for tests
add_executable(ascii-tests ${TEST_SOURCES})

# Link your library + Catch2 main
target_link_libraries(ascii-tests
    PRIVATE
        ascii-lib
        Catch2::Catch2WithMain
)

# Include headers from your library
target_include_directories(ascii-tests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/ascii-lib/src
)

# Collect all image files inside tests/test-images
file(GLOB TEST_IMAGES "${CMAKE_CURRENT_SOURCE_DIR}/test-images/*")

# Define the output directory in the build tree
set(TEST_IMAGE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/test-images")
file(MAKE_DIRECTORY "${TEST_IMAGE_OUTPUT_DIR}")

add_custom_target(copy_test_images ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/test-images"
            "${CMAKE_CURRENT_BINARY_DIR}/test-images"
    COMMENT "Copying test images to build directory"
)

# Provide a preprocessor macro with the test image path
add_compile_definitions(TEST_IMAGE_DIR="${TEST_IMAGE_OUTPUT_DIR}")

# Discover and register Catch2 tests with CTest
include(Catch)
catch_discover_tests(ascii-tests)
