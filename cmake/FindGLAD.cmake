assert_is_set(EXT_DIR)

add_library(GLAD INTERFACE IMPORTED)

set(GLAD_SRC "${EXT_DIR}/glad/src/glad.c")
set(GLAD_INCLUDE "${EXT_DIR}/glad/include")

set_target_properties(GLAD PROPERTIES INTERFACE_SOURCES "${GLAD_SRC}")
set_target_properties(GLAD PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GLAD_INCLUDE}")

assign_source_group(${EXT_DIR} ${GLAD_SRC})