assert_is_set(EXT_DIR)

add_library(GoogleTest STATIC IMPORTED)

set(GTEST_INCLUDE 
    "${EXT_DIR}/googletest/googlemock/include"
    "${EXT_DIR}/googletest/googletest/include")

if (NOT ${CMAKE_GENERATOR} MATCHES "Win64")
    set(GTEST_LIB_DEBUG "${EXT_DIR}/googletest/bin/win32/debug/gmock_maind.lib")
    set(GTEST_LIB_RELEASE "${EXT_DIR}/googletest/bin/win32/release/gmock_main.lib")
else ()
    set(GTEST_LIB_DEBUG "${EXT_DIR}/googletest/bin/x64/debug/gmock_maind.lib")
    set(GTEST_LIB_RELEASE "${EXT_DIR}/googletest/bin/x64/release/gmock_main.lib")
endif ()

set_target_properties(GoogleTest PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE}")
set_target_properties(GoogleTest PROPERTIES IMPORTED_LOCATION_DEBUG "${GTEST_LIB_DEBUG}")
set_target_properties(GoogleTest PROPERTIES IMPORTED_LOCATION_RELEASE "${GTEST_LIB_RELEASE}")