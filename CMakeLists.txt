function (assign_source_group ROOT_PATH)
    foreach (_source IN ITEMS ${ARGN})
        file(RELATIVE_PATH _source_rel "${ROOT_PATH}" "${_source}")
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
        #message("${_source_path_msvc} ${_source}")
    endforeach ()
endfunction (assign_source_group)

#
# anon-engine
#

cmake_minimum_required(VERSION 3.7)

# Disable in-source builds to prevent source tree corruption
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "
        Prevented in-tree built. 
        Please create a build directory outside of the source code and call cmake from there.
    ")
endif ()

project(anon-engine)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Use emcc compiler for Emscripten configuration
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_C_COMPILER "emcc")
endif ()

#
# External dependencies class library project
#
set(EXT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(GLAD_SRC "${EXT_DIR}/glad/src/glad.c")
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
set(IMGUIZMO_SRC "${EXT_DIR}/imguizmo/ImGuizmo.cpp")
set(STB_SRC "${EXT_DIR}/stb/src/stb_image.cpp")

add_library(External STATIC 
    ${GLAD_SRC}
    ${IMGUI_SRC}
    ${IMGUIZMO_SRC}
    ${STB_SRC})

target_include_directories(External
    PUBLIC "${EXT_DIR}/glad/include"
    PUBLIC "${EXT_DIR}/glfw/include"
    PUBLIC "${EXT_DIR}/glm"
    PUBLIC "${EXT_DIR}/imgui"
    PUBLIC "${EXT_DIR}/imguizmo"
    PUBLIC "${EXT_DIR}/stb")

find_package(OpenGL REQUIRED)

if (NOT ${CMAKE_GENERATOR} MATCHES "Win64")
    set(GLFW_DEBUG "${EXT_DIR}/glfw/bin/win32/debug/glfw3.lib")
    set(GLFW_RELEASE "${EXT_DIR}/glfw/bin/win32/release/glfw3.lib")
else ()
    set(GLFW_DEBUG "${EXT_DIR}/glfw/bin/x64/debug/glfw3.lib")
    set(GLFW_RELEASE "${EXT_DIR}/glfw/bin/x64/release/glfw3.lib")
endif ()

target_link_libraries(External 
    PUBLIC ${OPENGL_gl_LIBRARY}
    PUBLIC debug ${GLFW_DEBUG} 
    PUBLIC optimized ${GLFW_RELEASE})

assign_source_group(${EXT_DIR} ${GLAD_SRC})
assign_source_group(${EXT_DIR} ${IMGUI_SRC})
assign_source_group(${EXT_DIR} ${IMGUIZMO_SRC})
assign_source_group(${EXT_DIR} ${STB_SRC})

#
# Engine class library project
#
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(ENGINE_SRC 
    "${SRC_DIR}/Precompiled.cpp"
    "${SRC_DIR}/Precompiled.hpp"
    "${SRC_DIR}/component/Database.cpp"
    "${SRC_DIR}/component/Database.hpp"
    "${SRC_DIR}/component/EntityId.hpp"
    "${SRC_DIR}/component/IComponent.hpp"
    "${SRC_DIR}/component/Query.cpp"
    "${SRC_DIR}/component/Query.hpp"
    "${SRC_DIR}/component/SparseIndex.cpp"
    "${SRC_DIR}/component/SparseIndex.hpp"
    "${SRC_DIR}/component/SparseSet.hpp"
    "${SRC_DIR}/component/System.cpp"
    "${SRC_DIR}/component/System.hpp"
    "${SRC_DIR}/component/Table.hpp"
    "${SRC_DIR}/core/Added.hpp"
    "${SRC_DIR}/core/Datatypes.hpp"
    "${SRC_DIR}/core/Defines.hpp"
    "${SRC_DIR}/core/Deleted.hpp"
    "${SRC_DIR}/core/Engine.cpp"
    "${SRC_DIR}/core/Engine.hpp"
    "${SRC_DIR}/core/Logger.hpp"
    "${SRC_DIR}/core/Math.hpp"
    "${SRC_DIR}/core/Time.cpp"
    "${SRC_DIR}/core/Time.hpp"
    "${SRC_DIR}/core/Traits.hpp"
    "${SRC_DIR}/core/Updated.hpp"
    "${SRC_DIR}/graphics/AABB.cpp"
    "${SRC_DIR}/graphics/AABB.hpp"
    "${SRC_DIR}/graphics/Id.hpp"
    "${SRC_DIR}/graphics/Mesh.hpp"
    "${SRC_DIR}/graphics/OBB.cpp"
    "${SRC_DIR}/graphics/OBB.hpp"
    "${SRC_DIR}/graphics/OldRenderer.cpp"
    "${SRC_DIR}/graphics/OldRenderer.hpp"
    "${SRC_DIR}/graphics/Raycast.cpp"
    "${SRC_DIR}/graphics/Raycast.hpp"
    "${SRC_DIR}/graphics/RenderSystem.cpp"
    "${SRC_DIR}/graphics/RenderSystem.hpp"
    "${SRC_DIR}/graphics/Shader.cpp"
    "${SRC_DIR}/graphics/Shader.hpp"
    "${SRC_DIR}/graphics/Texture.cpp"
    "${SRC_DIR}/graphics/Texture.hpp"
    "${SRC_DIR}/scene/Camera.cpp"
    "${SRC_DIR}/scene/Camera.hpp"
    "${SRC_DIR}/scene/CameraControl.hpp"
    "${SRC_DIR}/scene/CameraController.cpp"
    "${SRC_DIR}/scene/CameraController.hpp"
    "${SRC_DIR}/scene/CameraSystem.cpp"
    "${SRC_DIR}/scene/CameraSystem.hpp"
    "${SRC_DIR}/scene/EditorSystem.cpp"
    "${SRC_DIR}/scene/EditorSystem.hpp"
    "${SRC_DIR}/scene/Hovered.hpp"
    "${SRC_DIR}/scene/Scene.cpp"
    "${SRC_DIR}/scene/Scene.hpp"
    "${SRC_DIR}/scene/Selected.hpp"
    "${SRC_DIR}/scene/Transform.hpp"
    "${SRC_DIR}/scene/TransformGizmo.hpp"
    "${SRC_DIR}/scene/TransformSystem.cpp"
    "${SRC_DIR}/scene/TransformSystem.hpp"
    "${SRC_DIR}/ui/FrameInput.cpp"
    "${SRC_DIR}/ui/FrameInput.hpp"
    "${SRC_DIR}/ui/ImGui.cpp"
    "${SRC_DIR}/ui/ImGui.hpp"
    "${SRC_DIR}/ui/InputBindings.cpp"
    "${SRC_DIR}/ui/InputBindings.hpp"
    "${SRC_DIR}/ui/InputListener.hpp"
    "${SRC_DIR}/ui/InputSystem.cpp"
    "${SRC_DIR}/ui/InputSystem.hpp"
    "${SRC_DIR}/ui/Window.cpp"
    "${SRC_DIR}/ui/Window.hpp")

# GLOB alternative
# file(GLOB_RECURSE ENGINE_SOURCE 
#     "${SRC_DIR}/*.cpp" 
#     "${SRC_DIR}/*.hpp")

set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADER_SRC
    "${SHADER_DIR}/fragment.frag"
    "${SHADER_DIR}/fragment_col.frag"
    "${SHADER_DIR}/fragment_single.frag"
    "${SHADER_DIR}/fragment_tex.frag"
    "${SHADER_DIR}/vertex.vert"
    "${SHADER_DIR}/vertex_hilight.vert"
    "${SHADER_DIR}/vertex_pos.vert"
    "${SHADER_DIR}/vertex_tex.vert")

add_library(Engine STATIC ${ENGINE_SRC} ${SHADER_SRC})
target_include_directories(Engine PUBLIC ${SRC_DIR})
target_link_libraries(Engine PUBLIC External)    

assign_source_group(${SRC_DIR} ${ENGINE_SRC})
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SHADER_SRC})

#
# Console application project
#
set(MAIN_SRC "${SRC_DIR}/Main.cpp")

add_executable(Main ${MAIN_SRC})
target_link_libraries(Main Engine)

assign_source_group(${SRC_DIR} ${MAIN_SRC})

#
# Test application project
#
set(TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(TESTS_SRC 
    "${TESTS_DIR}/Main.cpp"
    "${TESTS_DIR}/Precompiled.cpp"
    "${TESTS_DIR}/Precompiled.hpp"
    "${TESTS_DIR}/component/Test_Query.cpp"
    "${TESTS_DIR}/component/Test_SparseIndex.cpp"
    "${TESTS_DIR}/component/Test_Table.cpp"
    "${TESTS_DIR}/component/TestComponents.hpp")

add_executable(Tests ${TESTS_SRC})

# Google Test + Google Mock
set(GTEST_DIR "${EXT_DIR}/googletest")

if (NOT ${CMAKE_GENERATOR} MATCHES "Win64")
    set(GTEST_DEBUG "${GTEST_DIR}/bin/win32/debug/gmock_maind.lib")
    set(GTEST_RELEASE "${GTEST_DIR}/bin/win32/release/gmock_main.lib")
else ()
    set(GTEST_DEBUG "${GTEST_DIR}/bin/x64/debug/gmock_maind.lib")
    set(GTEST_RELEASE "${GTEST_DIR}/bin/x64/release/gmock_main.lib")
endif ()

target_include_directories(Tests 
    PRIVATE "${TESTS_DIR}"
    PRIVATE "${GTEST_DIR}/googlemock/include"
    PRIVATE "${GTEST_DIR}/googletest/include")

target_link_libraries(Tests
    External 
    Engine
    debug "${GTEST_DEBUG}"
    optimized "${GTEST_RELEASE}")

assign_source_group(${TESTS_DIR} ${TESTS_SRC})