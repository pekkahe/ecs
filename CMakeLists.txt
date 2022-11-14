cmake_minimum_required(VERSION 3.7)

# Disable in-source builds to prevent source tree corruption
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "
        Prevented in-tree built. 
        Please create a build directory outside of the source code and call cmake from there.")
endif ()

project(Uuttu)

# Tell CMake of our custom module directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Import custom scripts
include(Defines)
include(Macros)

# Not recommended: CMakeLists doesn't change when new source files are added
# file(GLOB ENGINE_SRC *.cpp)
# file(GLOB SHADER_SRC *.frag)

#
# Source files
#
set(MAIN_SRC 
    "${SRC_DIR}/Main.cpp")

set(ENGINE_SRC 
    "${SRC_DIR}/Precompiled.cpp"
    "${SRC_DIR}/Precompiled.hpp"
	"${SRC_DIR}/core/Components.hpp"
    "${SRC_DIR}/core/Core.hpp"
    "${SRC_DIR}/core/Datatypes.hpp"
    "${SRC_DIR}/core/Defines.hpp"
    "${SRC_DIR}/core/Engine.cpp"
    "${SRC_DIR}/core/Engine.hpp"
    "${SRC_DIR}/core/Logger.hpp"
    "${SRC_DIR}/core/Math.hpp"
    "${SRC_DIR}/core/Time.cpp"
    "${SRC_DIR}/core/Time.hpp"
    "${SRC_DIR}/core/Traits.hpp"
    "${SRC_DIR}/core/components/Added.hpp"
    "${SRC_DIR}/core/components/Deleted.hpp"
    "${SRC_DIR}/core/components/Updated.hpp"
    "${SRC_DIR}/core/ecs/Database.cpp"
    "${SRC_DIR}/core/ecs/Database.hpp"
    "${SRC_DIR}/core/ecs/EntityId.hpp"
    "${SRC_DIR}/core/ecs/IComponent.hpp"
    "${SRC_DIR}/core/ecs/Query.cpp"
    "${SRC_DIR}/core/ecs/Query.hpp"
    "${SRC_DIR}/core/ecs/Scheduler.cpp"
    "${SRC_DIR}/core/ecs/Scheduler.hpp"
    "${SRC_DIR}/core/ecs/SparseIndex.cpp"
    "${SRC_DIR}/core/ecs/SparseIndex.hpp"
    "${SRC_DIR}/core/ecs/SparseSet.hpp"
    "${SRC_DIR}/core/ecs/System.cpp"
    "${SRC_DIR}/core/ecs/System.hpp"
    "${SRC_DIR}/core/ecs/Table.hpp"
	"${SRC_DIR}/core/scheduler/Job.hpp"
	"${SRC_DIR}/core/scheduler/Scheduler.cpp"
    "${SRC_DIR}/core/scheduler/Scheduler.hpp"
	"${SRC_DIR}/core/scheduler/Worker.cpp"
    "${SRC_DIR}/core/scheduler/Worker.hpp"

	"${SRC_DIR}/editor/Components.hpp"
    "${SRC_DIR}/editor/EditorSystem.cpp"
    "${SRC_DIR}/editor/EditorSystem.hpp"
    "${SRC_DIR}/editor/components/Hovered.hpp"
    "${SRC_DIR}/editor/components/Selected.hpp"
    "${SRC_DIR}/editor/components/TransformGizmo.hpp"

    "${SRC_DIR}/graphics/Components.hpp"
    "${SRC_DIR}/graphics/Id.hpp"
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
    "${SRC_DIR}/graphics/components/AABB.cpp"
    "${SRC_DIR}/graphics/components/AABB.hpp"
    "${SRC_DIR}/graphics/components/Mesh.hpp"
    "${SRC_DIR}/graphics/components/OBB.cpp"
    "${SRC_DIR}/graphics/components/OBB.hpp"

    "${SRC_DIR}/scene/CameraController.cpp"
    "${SRC_DIR}/scene/CameraController.hpp"
    "${SRC_DIR}/scene/CameraSystem.cpp"
    "${SRC_DIR}/scene/CameraSystem.hpp"
    "${SRC_DIR}/scene/Components.hpp"
    "${SRC_DIR}/scene/Scene.cpp"
    "${SRC_DIR}/scene/Scene.hpp"
    "${SRC_DIR}/scene/TransformSystem.cpp"
    "${SRC_DIR}/scene/TransformSystem.hpp"
    "${SRC_DIR}/scene/components/Camera.cpp"
    "${SRC_DIR}/scene/components/Camera.hpp"
    "${SRC_DIR}/scene/components/CameraControl.hpp"
    "${SRC_DIR}/scene/components/Transform.hpp"
    
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
    
set(SHADER_SRC
    "${SHADER_DIR}/fragment.frag"
    "${SHADER_DIR}/fragment_col.frag"
    "${SHADER_DIR}/fragment_single.frag"
    "${SHADER_DIR}/fragment_tex.frag"
    "${SHADER_DIR}/vertex.vert"
    "${SHADER_DIR}/vertex_hilight.vert"
    "${SHADER_DIR}/vertex_pos.vert"
    "${SHADER_DIR}/vertex_tex.vert")

set(TESTS_SRC 
    "${TESTS_DIR}/Main.cpp"
    "${TESTS_DIR}/Precompiled.cpp"
    "${TESTS_DIR}/Precompiled.hpp"
    "${TESTS_DIR}/core/ecs/Test_Query.cpp"
    "${TESTS_DIR}/core/ecs/Test_SparseIndex.cpp"
    "${TESTS_DIR}/core/ecs/Test_Table.cpp"
    "${TESTS_DIR}/core/ecs/TestComponents.hpp"
	"${TESTS_DIR}/core/scheduler/Test_Scheduler.cpp")

#
# Engine core
#
add_library(Engine STATIC ${ENGINE_SRC} ${SHADER_SRC})

target_include_directories(Engine PUBLIC ${SRC_DIR})

find_package(OpenGL REQUIRED)
find_package(Glad REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)
find_package(ImGui REQUIRED)
find_package(ImGuizmo REQUIRED)
find_package(Stb REQUIRED)

target_link_libraries(Engine 
    PUBLIC ${OPENGL_gl_LIBRARY}
    PUBLIC Glad
    PUBLIC GLM
    PUBLIC GLFW
    PUBLIC ImGui
    PUBLIC ImGuizmo
    PUBLIC Stb)    

assign_source_group(${SRC_DIR} ${ENGINE_SRC})
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SHADER_SRC})

#
# Main application
#
add_executable(Main ${MAIN_SRC})

target_link_libraries(Main Engine)

if (EMSCRIPTEN)
    # LINK_FLAGS must be specified as one big string, using CMake's 
    # multiline string syntax creates a list which doesn't work.
    set(_LF "")
    set(_LF "${_LF} -v")
    set(_LF "${_LF} --emrun")
    set(_LF "${_LF} -s DEMANGLE_SUPPORT=1")
    set(_LF "${_LF} -s USE_GLFW=3")
    set(_LF "${_LF} -s USE_WEBGL2=1")
    set(_LF "${_LF} -s FULL_ES3=1")
    set(_LF "${_LF} -o Main.html")

    set_target_properties(Main PROPERTIES
        LINK_FLAGS "${_LF}")
endif ()

assign_source_group(${SRC_DIR} ${MAIN_SRC})

#
# Unit test application (build issue currently with Emscripten)
#
if (NOT EMSCRIPTEN)
    add_executable(Tests ${TESTS_SRC})

    target_include_directories(Tests PRIVATE ${TESTS_DIR})

    find_package(GoogleTest REQUIRED)

    target_link_libraries(Tests
        GoogleTest
        Engine)

    assign_source_group(${TESTS_DIR} ${TESTS_SRC})
endif ()