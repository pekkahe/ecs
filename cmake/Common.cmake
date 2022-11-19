function(assert_outsource_build)
    if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
        message(FATAL_ERROR "
            Prevented in-source build. 
            Please create and use a build directory outside of the source code.")
    endif()
endfunction()

function(assign_source_group ROOT)
    foreach(_SOURCE_FILE IN ITEMS ${ARGN})
        file(RELATIVE_PATH _REL_PATH "${ROOT}" "${_SOURCE_FILE}")
        get_filename_component(_SOURCE_DIR "${_REL_PATH}" DIRECTORY)
        if(MSVC)
            string(REPLACE "/" "\\" _SOURCE_DIR "${_SOURCE_DIR}")
        endif()
        source_group("${_SOURCE_DIR}" FILES "${_SOURCE_FILE}")
    endforeach()
endfunction()

include(FetchContent)
    
function(fetch_gtest)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.12.0
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set_target_properties(gmock PROPERTIES FOLDER "external/googletest")
    set_target_properties(gmock_main PROPERTIES FOLDER "external/googletest")
    set_target_properties(gtest PROPERTIES FOLDER "external/googletest")
    set_target_properties(gtest_main PROPERTIES FOLDER "external/googletest")
endfunction()

function(fetch_glm)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 0.9.9.8
    )
    FetchContent_MakeAvailable(glm)
endfunction()

function(fetch_glfw)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.3.8
    )
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(glfw)
    set_target_properties(glfw PROPERTIES FOLDER "external/glfw3")
    set_target_properties(update_mappings PROPERTIES FOLDER "external/glfw3")
endfunction()