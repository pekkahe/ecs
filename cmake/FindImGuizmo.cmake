assert_is_set(EXT_DIR)

add_library(IMGUIZMO INTERFACE IMPORTED)

set(IMGUIZMO_SRC "${EXT_DIR}/imguizmo/ImGuizmo.cpp")
set(IMGUIZMO_INCLUDE "${EXT_DIR}/imguizmo")

set_target_properties(IMGUIZMO PROPERTIES INTERFACE_SOURCES "${IMGUIZMO_SRC}")
set_target_properties(IMGUIZMO PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${IMGUIZMO_INCLUDE}")

assign_source_group(${EXT_DIR} ${IMGUIZMO_SRC})