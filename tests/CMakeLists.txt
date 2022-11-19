#set(GTEST_DIR ${CMAKE_SOURCE_DIR}/external/googletest/1.12.1/googletest)
# set(GOOGLETEST_VERSION "1.12.1")

# add_subdirectory(
#     ${CMAKE_SOURCE_DIR}/${GOOGLETEST_DIR}
#     ${CMAKE_BINARY_DIR}/${GOOGLETEST_DIR})

# set (GTEST_ROOT ${CMAKE_SOURCE_DIR}/external/googletest/1.12.1/googletest)
# set (GTEST_LIBRARY ${CMAKE_SOURCE_DIR}/external/googletest/1.12.1/googletest)
# set (GTEST_MAIN_LIBRARY ${CMAKE_SOURCE_DIR}/external/googletest/1.12.1/googletest)
# set (GTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/googletest/1.12.1/googletest)
# find_package(GTest REQUIRED)
    
fetch_gtest()



file(GLOB_RECURSE SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(tests ${SRC_FILES})

target_include_directories(tests 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests 
    PRIVATE gtest
    PRIVATE engine)

assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_FILES})