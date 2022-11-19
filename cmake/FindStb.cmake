add_library(stb INTERFACE)

set(STB_DIR "${CMAKE_SOURCE_DIR}/external/stb")
set(STB_SRC "${STB_DIR}/stb_image.h")

target_include_directories(stb INTERFACE ${STB_DIR})

set_target_properties(stb PROPERTIES FOLDER external)

assign_source_group(${STB_DIR} ${STB_SRC})