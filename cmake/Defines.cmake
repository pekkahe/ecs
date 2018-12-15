if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Use emcc compiler for Emscripten configuration
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_C_COMPILER "emcc")
endif ()

set(CMAKE_CXX_STANDARD 14)
#target_compile_features(Engine PRIVATE cxx_std_11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#list(APPEND CMAKE_CXX_FLAGS "-Wall")
#target_compile_options(Engine PRIVATE -Werror)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Paths
set(EXT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")