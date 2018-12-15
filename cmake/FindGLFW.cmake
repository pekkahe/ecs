assert_is_set(EXT_DIR)

if (NOT ${CMAKE_GENERATOR} MATCHES "Win64")
    set(GLFW_DEBUG "${EXT_DIR}/glfw/bin/win32/debug/glfw3.lib")
    set(GLFW_RELEASE "${EXT_DIR}/glfw/bin/win32/release/glfw3.lib")
else ()
    set(GLFW_DEBUG "${EXT_DIR}/glfw/bin/x64/debug/glfw3.lib")
    set(GLFW_RELEASE "${EXT_DIR}/glfw/bin/x64/release/glfw3.lib")
endif ()

set(GLFW_LIB debug ${GLFW_DEBUG} optimized ${GLFW_RELEASE})
set(GLFW_INCLUDE "${EXT_DIR}/glfw/include")