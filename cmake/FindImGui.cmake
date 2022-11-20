add_library(imgui)

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui/1.88")
set(IMGUI_SRC 
    "${IMGUI_DIR}/imgui.h"   
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.h"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.h"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp")
assign_source_group(${IMGUI_DIR} ${IMGUI_SRC})

target_sources(imgui PRIVATE ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_link_libraries(imgui PRIVATE glad glfw)

set_target_properties(imgui PROPERTIES FOLDER external)