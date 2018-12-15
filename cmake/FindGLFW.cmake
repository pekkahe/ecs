assert_is_set(EXT_DIR)

add_library(GLFW STATIC IMPORTED)

set(GLFW_INCLUDE "${EXT_DIR}/glfw/include")

if (NOT ${CMAKE_GENERATOR} MATCHES "Win64")
    set(GLFW_LIB_DEBUG "${EXT_DIR}/glfw/bin/win32/debug/glfw3.lib")
    set(GLFW_LIB_RELEASE "${EXT_DIR}/glfw/bin/win32/release/glfw3.lib")
else ()
    set(GLFW_LIB_DEBUG "${EXT_DIR}/glfw/bin/x64/debug/glfw3.lib")
    set(GLFW_LIB_RELEASE "${EXT_DIR}/glfw/bin/x64/release/glfw3.lib")
endif ()

set_target_properties(GLFW PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE}")
set_target_properties(GLFW PROPERTIES IMPORTED_LOCATION_DEBUG "${GLFW_LIB_DEBUG}")
set_target_properties(GLFW PROPERTIES IMPORTED_LOCATION_RELEASE "${GLFW_LIB_RELEASE}")