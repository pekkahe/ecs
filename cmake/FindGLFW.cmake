set(GLFW_DIR "${CMAKE_SOURCE_DIR}/external/glfw/3.3.8")

if(EMSCRIPTEN)
    # Emscripten provides GLFW3 
    # TODO: Use repo version? 
    add_library(glfw INTERFACE)
    
    # target_include_directories(glfw INTERFACE "${GLFW_DIR}/include")
else()
    add_library(glfw STATIC IMPORTED)

    target_include_directories(glfw INTERFACE "${GLFW_DIR}/include")
    set_target_properties(glfw PROPERTIES 
        IMPORTED_LOCATION "${GLFW_DIR}/lib-vc2022/glfw3.lib")
endif()
