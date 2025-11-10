# ascii-lib/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(ascii-lib VERSION 1.0.0 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared library" ON)

# === Library definition ===
file(GLOB_RECURSE ASCII_LIB_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)
add_library(ascii-lib ${ASCII_LIB_SOURCES})

# Set up include paths
target_include_directories(ascii-lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor>
)

target_compile_features(ascii-lib PUBLIC cxx_std_17)

# Set a namespace and library name
set_target_properties(ascii-lib PROPERTIES
    EXPORT_NAME ascii-lib
    OUTPUT_NAME "ascii"
)

# === Install targets ===
include(GNUInstallDirs)
install(TARGETS ascii-lib
    EXPORT ascii-lib-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install public headers
install(DIRECTORY src/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ascii-lib
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# === CMake package export ===
include(CMakePackageConfigHelpers)

# Generate a version file (for find_package version checking)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ascii-lib-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Generate the config file that references the exported targets
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ascii-lib-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/ascii-lib-config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ascii-lib
)

# Install the config and version files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ascii-lib-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ascii-lib-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ascii-lib
)

# Export the targets for the package
install(EXPORT ascii-lib-targets
    NAMESPACE ascii::
    FILE ascii-lib-targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ascii-lib
)
