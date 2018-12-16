assert_is_set(EXT_DIR)

add_library(Glad)

set(GLAD_DIR "${EXT_DIR}/glad")
set(GLAD_SRC "${GLAD_DIR}/src/glad.c")
set(GLAD_INCLUDE "${GLAD_DIR}/include")

target_sources(Glad PRIVATE ${GLAD_SRC})

target_include_directories(Glad PUBLIC ${GLAD_INCLUDE})

set_target_properties(Glad PROPERTIES FOLDER "External")

assign_source_group("${GLAD_DIR}/src" ${GLAD_SRC})