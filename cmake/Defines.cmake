if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_STANDARD 14)

# Turn on more warnings
list(APPEND CMAKE_CXX_FLAGS "-Wall")

# Enable solution level folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (EMSCRIPTEN)
    message(STATUS "Using Emscripten compilers:
    ${CMAKE_C_COMPILER}
    ${CMAKE_CXX_COMPILER}")  
    
    set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin/emcc")
else ()
    set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin/msvc")
endif ()

# Options
set(OUTPUT_PATH "${OUTPUT_DIR}" CACHE PATH "Path to build output binaries")

# Paths
set(EXT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PATH}")