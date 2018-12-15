assert_is_set(EXT_DIR)

add_library(STB INTERFACE IMPORTED)

set(STB_SRC "${EXT_DIR}/stb/src/stb_image.cpp")
set(STB_INCLUDE "${EXT_DIR}/stb")

set_target_properties(STB PROPERTIES INTERFACE_SOURCES "${STB_SRC}")
set_target_properties(STB PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${STB_INCLUDE}")

assign_source_group(${EXT_DIR} ${STB_SRC})