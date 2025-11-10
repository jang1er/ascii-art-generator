cmake_minimum_required(VERSION 3.16)
project(ascii LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# =====================================
# Common warning and safety settings
# =====================================
function(set_project_warnings target_name)
    if (MSVC)
        # /W4 = high warning level, /permissive- enforces strict standard compliance
        target_compile_options(${target_name} PRIVATE
            /W4
            /permissive-
            /EHsc
            /D_CRT_SECURE_NO_WARNINGS
        )
    else()
        # GCC and Clang
        target_compile_options(${target_name} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wshadow
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
            -Wunused
        )
    endif()
endfunction()


# Build both subprojects
add_subdirectory(ascii-lib)
set_project_warnings(ascii-lib)

add_subdirectory(ascii-cli)
set_project_warnings(ascii-cli)

# --- Fetch Catch2 v3 ---
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.3
)

FetchContent_MakeAvailable(Catch2)

# --- Enable CTest (for running tests) ---
enable_testing()

# --- Add tests subdirectory ---
add_subdirectory(tests)