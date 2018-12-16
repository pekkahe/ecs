assert_is_set(EXT_DIR)

add_library(ImGuizmo)

set(IMGUIZMO_DIR "${EXT_DIR}/imguizmo")
set(IMGUIZMO_SRC "${IMGUIZMO_DIR}/ImGuizmo.cpp")
set(IMGUIZMO_INCLUDE "${IMGUIZMO_DIR}")

target_sources(ImGuizmo PRIVATE ${IMGUIZMO_SRC})

target_include_directories(ImGuizmo PUBLIC ${IMGUIZMO_INCLUDE})

set_target_properties(ImGuizmo PROPERTIES FOLDER "External")

assign_source_group("${IMGUIZMO_DIR}" ${IMGUIZMO_SRC})