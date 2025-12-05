cmake_minimum_required(VERSION 3.15)
project(Timer LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Build library (INTERFACE for header-only, STATIC if src present)
file(GLOB LIB_SRC CONFIGURE_DEPENDS src/*.cpp)

if (LIB_SRC)
    add_library(Timer STATIC ${LIB_SRC})

    # These settings are only valid for a STATIC target
    target_include_directories(Timer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) # Changed PUBLIC to PRIVATE for the BUILD_INTERFACE part of the original line

    # Warnings and optimization flags
    target_compile_options(Timer PRIVATE
        -Wall -Wextra -Werror
        -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
        -Wunused -Wpedantic -Wconversion -Wsign-conversion
        -Wnull-dereference -Wdouble-promotion -Wformat=2
        -Wimplicit-fallthrough
    )
    target_compile_options(Timer PRIVATE
        \$<$<CONFIG:Debug>:-O0>
        \$<$<CONFIG:Release>:-O3 -DNDEBUG>
        \$<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
        \$<$<CONFIG:RelWithDebInfo>:-O2 -DNDEBUG>
    )
    target_link_options(Timer PRIVATE
        \$<$<CONFIG:Debug>:-g>
        \$<$<CONFIG:RelWithDebInfo>:-g>
    )
else()
    add_library(Timer INTERFACE)
endif()

# Use target properties for output directories
set_target_properties(Timer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(Timer INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

option(Timer_BUILD_TESTS "Build tests" ON)
if (Timer_BUILD_TESTS)
    enable_testing()
    add_executable(TimerTests tests/test_main.cpp)
    target_include_directories(TimerTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(TimerTests PRIVATE Timer)

    # Apply the same strict warnings
    target_compile_options(TimerTests PRIVATE
        -Wall -Wextra -Werror -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
        -Wunused -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2
        -Wimplicit-fallthrough
    )

    # Apply configuration-specific optimization/debug flags
    target_compile_options(TimerTests PRIVATE
        \$<$<CONFIG:Debug>:-O0>
        \$<$<CONFIG:Release>:-O3 -DNDEBUG>
        \$<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
        \$<$<CONFIG:RelWithDebInfo>:-O2 -DNDEBUG>
    )

    # Apply configuration-specific link/debug flags
    target_link_options(TimerTests PRIVATE
        \$<$<CONFIG:Debug>:-g>
        \$<$<CONFIG:RelWithDebInfo>:-g>
    )
    add_test(NAME TimerTests COMMAND TimerTests)
endif()
