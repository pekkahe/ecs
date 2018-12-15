assert_is_set(EXT_DIR)

add_library(IMGUI INTERFACE IMPORTED)

set(IMGUI_SRC 
    "${EXT_DIR}/imgui/imgui.cpp"
    "${EXT_DIR}/imgui/imgui_demo.cpp"
    "${EXT_DIR}/imgui/imgui_draw.cpp"
    "${EXT_DIR}/imgui/imgui_impl_glfw.cpp"
    "${EXT_DIR}/imgui/imgui_impl_opengl3.cpp"
    "${EXT_DIR}/imgui/imgui_widgets.cpp"
    "${EXT_DIR}/imgui/imconfig.h"
    "${EXT_DIR}/imgui/imgui.h"
    "${EXT_DIR}/imgui/imgui_impl_glfw.h"
    "${EXT_DIR}/imgui/imgui_impl_opengl3.h")

set(IMGUI_INCLUDE "${EXT_DIR}/imgui")

set_target_properties(IMGUI PROPERTIES INTERFACE_SOURCES "${IMGUI_SRC}")
set_target_properties(IMGUI PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${IMGUI_INCLUDE}")

assign_source_group(${EXT_DIR} ${IMGUI_SRC})