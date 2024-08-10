add_executable(libtest)

fetch_gtest()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})

target_sources(libtest PRIVATE ${SRC_FILES})
#target_include_directories(libtest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(libtest PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(libtest PRIVATE 
    lib
    gtest
    gmock)

set_high_warning_level(libtest)

add_test(ecs-test libtest)