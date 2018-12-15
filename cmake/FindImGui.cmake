assert_is_set(EXT_DIR)

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