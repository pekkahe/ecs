cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
project(ecs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Common)

assert_outsource_build()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(EMSCRIPTEN)
    message(STATUS "Emscripten compiler build")
    message(STATUS "C compiler path: ${CMAKE_C_COMPILER}")
    message(STATUS "C++ compiler path: ${CMAKE_CXX_COMPILER}")
    set(OUTPUT_DIR emcc)
else()
    set(OUTPUT_DIR msvc)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${OUTPUT_DIR}")

add_subdirectory(src/cli)
add_subdirectory(src/lib)

# TODO: Fix unit tests build with Emscripten
if(NOT EMSCRIPTEN)
    add_subdirectory(tests)
endif()