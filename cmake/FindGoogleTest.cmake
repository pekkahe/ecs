assert_is_set(EXT_DIR)

if (NOT ${CMAKE_GENERATOR} MATCHES "Win64")
    set(GTEST_DEBUG "${EXT_DIR}/googletest/bin/win32/debug/gmock_maind.lib")
    set(GTEST_RELEASE "${EXT_DIR}/googletest/bin/win32/release/gmock_main.lib")
else ()
    set(GTEST_DEBUG "${EXT_DIR}/googletest/bin/x64/debug/gmock_maind.lib")
    set(GTEST_RELEASE "${EXT_DIR}/googletest/bin/x64/release/gmock_main.lib")
endif ()

set(GTEST_LIB debug ${GTEST_DEBUG} optimized ${GTEST_RELEASE})
set(GTEST_INCLUDE "${EXT_DIR}/googletest/googlemock/include")
set(GMOCK_INCLUDE "${EXT_DIR}/googletest/googletest/include")