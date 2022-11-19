add_library(imguizmo)

set(IMGUIZMO_DIR "${CMAKE_SOURCE_DIR}/external/imguizmo/1.83")
set(IMGUIZMO_SRC "${IMGUIZMO_DIR}/ImGuizmo.cpp")

target_sources(imguizmo PRIVATE ${IMGUIZMO_SRC})
target_include_directories(imguizmo PUBLIC ${IMGUIZMO_DIR})

set_target_properties(imguizmo PROPERTIES FOLDER external)

assign_source_group(${IMGUIZMO_DIR} ${IMGUIZMO_SRC})