add_library(lib STATIC)

find_package(Glad REQUIRED)
find_package(ImGui REQUIRED)
find_package(ImGuizmo REQUIRED)
find_package(Stb REQUIRED)
find_package(OpenGL REQUIRED)

fetch_glm()
fetch_glfw()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE SRC_SHADER_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/shaders/*.frag"
    "${CMAKE_SOURCE_DIR}/shaders/*.vert")
list(APPEND ${SRC_FILES} ${SRC_SHADER_FILES})
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})

target_sources(lib PRIVATE ${SRC_FILES})
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(lib PUBLIC
    NOMINMAX
    IMGUI_USER_CONFIG=<ui/ImConfig.hpp>)
target_link_libraries(lib
    PUBLIC
        Glad
        glm
        glfw
        ImGui
        ImGuizmo
        Stb
        OpenGL::GL)

set_high_warning_level(lib)