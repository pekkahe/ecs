assert_is_set(EXT_DIR)

add_library(ImGui)

set(IMGUI_DIR "${EXT_DIR}/imgui")
set(IMGUI_SRC 
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/imgui_impl_opengl3.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imconfig.h"
    "${IMGUI_DIR}/imgui.h"
    "${IMGUI_DIR}/imgui_impl_glfw.h"
    "${IMGUI_DIR}/imgui_impl_opengl3.h")
set(IMGUI_INCLUDE "${IMGUI_DIR}")

target_sources(ImGui PRIVATE ${IMGUI_SRC})

target_include_directories(ImGui 
    PUBLIC ${IMGUI_INCLUDE})
    #PRIVATE ${Glad_INCLUDE}
    #PRIVATE ${GLFW_INCLUDE}

target_link_libraries(ImGui 
    PRIVATE Glad
    PRIVATE GLFW)

set_target_properties(ImGui PROPERTIES FOLDER "External")

assign_source_group("${IMGUI_DIR}" ${IMGUI_SRC})