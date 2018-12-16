option(PRINT_SOURCE_GROUPS "Print debug information of project source file grouping" OFF)

function (assign_source_group ROOT_PATH)
    if (PRINT_SOURCE_GROUPS)
        message(STATUS "Grouping files in \"${ROOT_PATH}\"")
    endif()

    foreach (_source IN ITEMS ${ARGN})
        file(RELATIVE_PATH _source_rel "${ROOT_PATH}" "${_source}")
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")

        if (PRINT_SOURCE_GROUPS)
            message(STATUS "  '${_source_path_msvc}': ${_source}")
        endif()
    endforeach ()

    if (PRINT_SOURCE_GROUPS)
        message(STATUS "")
    endif()
endfunction ()

function (assert_is_set VAR)
    if (NOT DEFINED ${VAR})
        message(FATAL_ERROR "Variable ${VAR} is undefined")
    endif ()
endfunction ()