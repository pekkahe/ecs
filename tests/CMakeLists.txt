add_executable(tests)

fetch_gtest()

file(GLOB_RECURSE SRC_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})

target_sources(tests PRIVATE ${SRC_FILES})
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests PRIVATE engine gtest)

set_high_warning_level(tests)