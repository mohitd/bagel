cmake_minimum_required(VERSION 3.16)
project(bagel-tests)

set(INSTALL_GTEST OFF)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(test_timer chrono/test_timer.cpp)
target_link_libraries(test_timer
    PRIVATE
        bagel::bagel
        GTest::gtest_main
)
gtest_discover_tests(test_timer)


# create example dynamic library to load as part of test
add_library(dynamic_lib_example dynamic_lib_example.cpp)
# change output extension to have consistent test across OS arches
set_target_properties(dynamic_lib_example PROPERTIES SUFFIX ".my_lib")
add_executable(test_dynamic_library test_dynamic_library.cpp)
target_link_libraries(test_dynamic_library
    PRIVATE
        bagel::bagel
        GTest::gtest_main
        ${CMAKE_DL_LIBS}
)
gtest_discover_tests(test_dynamic_library)

