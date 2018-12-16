if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Emscripten
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    message(STATUS "Using emcc and em++ compilers")  

    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_CXX_COMPILER "em++")

    set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin/emcc")
else()
    set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin/msvc")
endif ()

# Options
set(OUTPUT_PATH "${OUTPUT_DIR}" CACHE PATH "Path to build output binaries")

set(CMAKE_CXX_STANDARD 14)
#target_compile_features(Engine PRIVATE cxx_std_11)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#list(APPEND CMAKE_CXX_FLAGS "-Wall")
#target_compile_options(Engine PRIVATE -Werror)

# Enable solution level folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Paths
set(EXT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PATH}")