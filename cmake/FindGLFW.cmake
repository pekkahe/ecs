assert_is_set(EXT_DIR)

set(GLFW_DIR "${EXT_DIR}/glfw")
set(GLFW_INCLUDE "${GLFW_DIR}/include")

if (EMSCRIPTEN)
    # Emscripten provides GLFW3
    add_library(GLFW INTERFACE)
else ()
    add_library(GLFW STATIC IMPORTED)
    
    if (NOT ${CMAKE_GENERATOR} MATCHES "Win64")
        set(GLFW_LIB_DEBUG "${GLFW_DIR}/bin/win32/debug/glfw3.lib")
        set(GLFW_LIB_RELEASE "${GLFW_DIR}/bin/win32/release/glfw3.lib")
    else ()
        set(GLFW_LIB_DEBUG "${GLFW_DIR}/bin/x64/debug/glfw3.lib")
        set(GLFW_LIB_RELEASE "${GLFW_DIR}/bin/x64/release/glfw3.lib")
    endif ()

    set_target_properties(GLFW PROPERTIES 
        IMPORTED_LOCATION_DEBUG "${GLFW_LIB_DEBUG}"
        IMPORTED_LOCATION_RELEASE "${GLFW_LIB_RELEASE}")
endif ()

target_include_directories(GLFW INTERFACE "${GLFW_INCLUDE}")
