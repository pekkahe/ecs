assert_is_set(EXT_DIR)

add_library(Stb)

set(STB_DIR "${EXT_DIR}/stb")
set(STB_SRC "${STB_DIR}/src/stb_image.cpp")
set(STB_INCLUDE "${STB_DIR}")

target_sources(Stb PRIVATE ${STB_SRC})

target_include_directories(Stb PUBLIC ${STB_INCLUDE})

set_target_properties(Stb PROPERTIES FOLDER "External")

assign_source_group("${STB_DIR}/src" ${STB_SRC})