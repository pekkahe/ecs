assert_is_set(EXT_DIR)

add_library(GoogleTest STATIC IMPORTED)

set(GTEST_DIR "${EXT_DIR}/googletest")
set(GTEST_INCLUDE 
    "${GTEST_DIR}/googlemock/include"
    "${GTEST_DIR}/googletest/include")

if (NOT ${CMAKE_GENERATOR} MATCHES "Win64")
    set(GTEST_LIB_DEBUG "${GTEST_DIR}/bin/win32/debug/gmock_maind.lib")
    set(GTEST_LIB_RELEASE "${GTEST_DIR}/bin/win32/release/gmock_main.lib")
else ()
    set(GTEST_LIB_DEBUG "${GTEST_DIR}/bin/x64/debug/gmock_maind.lib")
    set(GTEST_LIB_RELEASE "${GTEST_DIR}/bin/x64/release/gmock_main.lib")
endif ()

target_include_directories(GoogleTest INTERFACE ${GTEST_INCLUDE})

set_target_properties(GoogleTest PROPERTIES 
    IMPORTED_LOCATION_DEBUG "${GTEST_LIB_DEBUG}"
    IMPORTED_LOCATION_RELEASE "${GTEST_LIB_RELEASE}")