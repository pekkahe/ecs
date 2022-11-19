add_executable(cli)

file(GLOB_RECURSE SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

target_sources(cli PRIVATE ${SRC_FILES})
target_link_libraries(cli PRIVATE engine)

if(EMSCRIPTEN)
    target_link_options(cli 
        PRIVATE "-v --emrun"
        PRIVATE "-s DEMANGLE_SUPPORT=1"
        PRIVATE "-s USE_GLFW=3 -s USE_WEBGL2=1"
        PRIVATE "-s FULL_ES3=1"
        PRIVATE "-o Main.html")
endif()

assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})