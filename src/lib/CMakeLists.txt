add_library(engine STATIC)

# set(glm_DIR "${CMAKE_SOURCE_DIR}/external/glm/0.9.9.8/cmake/glm")
# find_package(glm REQUIRED)
# set_target_properties(glm::glm PROPERTIES FOLDER external)

find_package(glad REQUIRED)
#find_package(glfw REQUIRED)
find_package(imgui REQUIRED)
find_package(imguizmo REQUIRED)
find_package(stb REQUIRED)
find_package(OpenGL REQUIRED)

fetch_glm()
fetch_glfw()

file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SRC_SHADER_FILES
    ${CMAKE_SOURCE_DIR}/shaders/*.frag
    ${CMAKE_SOURCE_DIR}/shaders/*.vert)
list(APPEND ${SRC_FILES} ${SRC_SHADER_FILES})

target_sources(engine PRIVATE ${SRC_FILES})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(engine PRIVATE IMGUI_USER_CONFIG ui/ImConfig.hpp)
target_link_libraries(engine
    PUBLIC glad
    PUBLIC glm
    PUBLIC glfw
    PUBLIC imgui
    PUBLIC imguizmo
    PUBLIC stb
    PUBLIC OpenGL::GL)

assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})