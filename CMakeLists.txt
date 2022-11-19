cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
project(ecs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Common)

assert_outsource_build()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to Debug as none was specified")
    set(CMAKE_BUILD_TYPE Debug)
endif()

list(APPEND CMAKE_CXX_FLAGS "-Wall")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(EMSCRIPTEN)
    message(STATUS "Emscripten compiler build")
    message(STATUS "C compiler path: ${CMAKE_C_COMPILER}")
    message(STATUS "C++ compiler path: ${CMAKE_CXX_COMPILER}")
    set(OUTPUT_DIR emcc)
else()
    set(OUTPUT_DIR msvc)
endif()

#set(OUTPUT_PATH ${OUTPUT_DIR} CACHE PATH "Path to build output binaries")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${OUTPUT_DIR})

add_subdirectory(src/cli)
add_subdirectory(src/lib)

# Unit test application does not build with Emscripten currently
if(NOT EMSCRIPTEN)
    add_subdirectory(tests)
endif()