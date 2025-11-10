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

# Discover and register Catch2 tests with CTest
include(Catch)
catch_discover_tests(ascii-tests)
