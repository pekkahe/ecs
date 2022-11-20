add_executable(cli)

set(SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})

target_sources(cli PRIVATE ${SRC_FILES})
target_link_libraries(cli PRIVATE lib)

if(EMSCRIPTEN)
    target_link_options(cli PRIVATE 
        "-v --emrun"
        "-s DEMANGLE_SUPPORT=1"
        "-s USE_GLFW=3 -s USE_WEBGL2=1"
        "-s FULL_ES3=1"
        "-o Main.html")
endif()

set_high_warning_level(cli)