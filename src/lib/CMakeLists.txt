add_library(lib STATIC)

find_package(glad REQUIRED)
find_package(imgui REQUIRED)
find_package(imguizmo REQUIRED)
find_package(stb REQUIRED)
find_package(OpenGL REQUIRED)

fetch_glm()
fetch_glfw()

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE SRC_SHADER_FILES
    "${CMAKE_SOURCE_DIR}/shaders/*.frag"
    "${CMAKE_SOURCE_DIR}/shaders/*.vert")
list(APPEND ${SRC_FILES} ${SRC_SHADER_FILES})
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})

target_sources(lib PRIVATE ${SRC_FILES})
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(lib PRIVATE
    NOMINMAX
    IMGUI_USER_CONFIG="ui/ImConfig.hpp")
target_link_libraries(lib
    PUBLIC
        glad
        glm
        glfw
        imgui
        imguizmo
        stb
        OpenGL::GL)

set_high_warning_level(lib)